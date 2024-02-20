#!/bin/bash
src_dir=$1
inputs_dir=$2
outputs_dir=$3
test_outputs_dir=$4

if [ $# -ne 4 ]
then
	echo "USAGE: $0 <source-dir> <inputs-dir> <outputs-dir> <test-outputs-dir>"
	echo "Filling missing parameters with default values"
	if [ -z $1 ]; then
		src_dir='./src'
		echo "Warning: first paramter (source-dir) is important, default is ./src"
		echo "It should point to the directory where your makefile and source files are located"
	fi
	if [ -z $2 ]; then
		inputs_dir='./inputs'
	fi
	if [ -z $3 ]; then
		outputs_dir='./outputs'
	fi
	if [ -z $4 ]; then
		test_outputs_dir='./test_outputs'
	fi
fi

echo ""
mkdir $test_outputs_dir

test-clang-tidy() {
	echo "Running clang-tidy on $1:"
	touch $test_outputs_dir/clang-tidy-output-$1.txt
	clang-tidy -checks=-*,clang-analyzer-* $src_dir/$1 -- > $test_outputs_dir/clang-tidy-output-$1.txt
	echo "Done, output can be found in clang-tidy-output-$1.txt"
	echo ""
}

if command -v clang-tidy >/dev/null
then
	test-clang-tidy Main.c
	test-clang-tidy StrList.h
	test-clang-tidy StrList.c
else
	echo "clang-tidy not found, skipping checks (maybe try installing with sudo apt install clang-tidy)"
	echo ""
fi

make -C $src_dir
echo ""

compare-files() {
	diff -s $1 $2
}

test-valgrind() {
	echo "Running valgrind with input #$1:"
	valgrind --log-file="$test_outputs_dir/valgrind-output-$1.txt" -s $src_dir/StrList < $inputs_dir/input$1.txt > $test_outputs_dir/my_output$1.txt
	echo "Done, output can be found in $test_outputs_dir/valgrind-output-$1.txt"
	echo "Comparing to output:"
	compare-files $outputs_dir/output$1.txt $test_outputs_dir/my_output$1.txt
	echo ""
}

test-prog() {
	echo "Running program with input #$1:"
	$src_dir/StrList < $inputs_dir/input$1.txt > $test_outputs_dir/my_output$1.txt
	echo "Done"
	echo "Comparing to output:"
	compare-files $outputs_dir/output$1.txt $test_outputs_dir/my_output$1.txt
	echo ""
}

if command -v valgrind >/dev/null
then
	test-valgrind 1
	test-valgrind 2
else
	echo "valgrind not found, running regular checks (maybe try installing with sudo apt install valgrind)"
	test-prog 1
	test-prog 2
fi

echo ""
echo "All checks finished"
