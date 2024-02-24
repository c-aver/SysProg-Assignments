#!/bin/bash
ERROR_COLOR='\033[0;31m'
WARNING_COLOR='\033[0;33m'
NOTE_COLOR='\033[0;32m'
NO_COLOR='\033[0m'
ERROR="${ERROR_COLOR}ERROR:${NO_COLOR}"
WARNING="${WARNING_COLOR}WARNING:${NO_COLOR}"
NOTE="${NOTE_COLOR}NOTE:${NO_COLOR}"

src_dir=$1
inputs_dir=$2
outputs_dir=$3
test_outputs_dir=$4

if [ $# -ne 4 ]
then
	echo "USAGE: $0 <source-dir> <inputs-dir> <outputs-dir> <test-outputs-dir>"
	echo -e "${NOTE} Filling missing parameters with default values"
	if [ -z $1 ]; then
		src_dir='./src'
		echo -e "${WARNING} First parameter (source-dir) is important, default is ./src"
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

if [ ! -d $src_dir ]; then
	echo -e "${ERROR} Source directory not found, move source files to ./src or provide source path in arguments"
	exit 1
fi

echo ""
mkdir -p $test_outputs_dir

test-clang-tidy() {
	if [ ! -f $src_dir/$1 ]; then
		echo -e "${ERROR} $1 not found in $src_dir, neccessary for checking"
		return
	fi
	echo -e "${NOTE} Running clang-tidy on $1:"
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
	echo -e "${NOTE}: clang-tidy not found, skipping checks (maybe try installing with sudo apt install clang-tidy)"
	echo ""
fi

make -C $src_dir
if [ $? -ne 0 ]; then
	echo -e "${ERROR}: make failed"
	exit 1
fi
echo ""

if [ ! -f $src_dir/StrList ]; then
	echo -e "${ERROR}: executable StrList not found in $src_dir after make"
	exit 1
fi

if [ ! -d $inputs_dir ]; then
	echo -e "${ERROR}: Inputs directory not found, move input files to ./inputs or provide path in arguments"
	exit 1
fi

if [ ! -d $outputs_dir ]; then
	echo -e "${ERROR}: Outputs directory not found, move output files to ./outputs or provide path in arguments"
	exit 1
fi

compare-files() {
	if [ $(file $1 | grep CRLF | wc -l) -ne $(file $2 | grep CRLF | wc -l) ]; then
		echo -e "${WARNING}: $1 and $2 have different line terminators, diff might show all lines as different for no appearant reason"
	fi
	diff -s $1 $2
}

test-valgrind() {
	echo -e "${NOTE} Running valgrind with input #$1:"
	valgrind --log-file="$test_outputs_dir/valgrind-output-$1.txt" -s $src_dir/StrList < $inputs_dir/input$1.txt > $test_outputs_dir/my_output$1.txt
	echo "Done, output can be found in $test_outputs_dir/valgrind-output-$1.txt"
	echo "Comparing to output:"
	compare-files $outputs_dir/output$1.txt $test_outputs_dir/my_output$1.txt
	echo ""
}

test-prog() {
	echo -e "${NOTE} Running program with input #$1:"
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
	echo -e "${NOTE} valgrind not found, running regular checks (maybe try installing with sudo apt install valgrind)"
	test-prog 1
	test-prog 2
fi

echo -e "${NOTE} All checks finished, make sure to look at output files in $test_outputs_dir to see how they went"
