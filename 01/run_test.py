import glob, os , sys
import shutil
import subprocess
import re
import filecmp
import difflib
passed = 1

def run_cmd(cmd , verbos = 1):
    if verbos == 1:
        print("running: " ,cmd)
    try:
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE , stderr=subprocess.PIPE)
        proc.wait()
        if proc.returncode != 0:
           raise Exception(" failed p.returncode= " + str(proc.returncode))
    except Exception as inst:
        print("command fained")
        print(inst)
        exit(1)

def test_output_vs_expected(prog , input_f , expected_f):
    global passed
    run_cmd("./%s < %s > tmp_out.txt"%(prog ,input_f ))
    if not filecmp.cmp('tmp_out.txt',expected_f ):
        print("difference found in ./%s < %s vs "%(prog ,input_f) ,expected_f)
        with open('tmp_out.txt', "r") as f1, open(expected_f, "r") as f2:
            diff = difflib.unified_diff(f1.readlines(), f2.readlines(), fromfile=input_f, tofile=expected_f)

        for line in diff:
            print(line)
        passed = 0
        run_cmd("cat tmp_out.txt")
        run_cmd("cat " + expected_f )
    # run_cmd("rm tmp_out.txt" , 0)

def main():
    test_output_vs_expected("src/mains" , "./inputs/input1.txt" , "./outputs/output1_less.txt")
    # test_output_vs_expected("src/maindloop" , "./inputs/input2.txt" , "./outputs/output2.txt")
    # test_output_vs_expected("src/maindrec" , "./inputs/input3.txt" , "./outputs/output3.txt")
    # test_output_vs_expected("src/maindrec" , "./inputs/input4.txt" , "./outputs/output4.txt")

    if passed == 1:
        print("You have PASSED the initial checks.")
    else:
        print("You have FAILED the initial checks. go fix your code.")
    


if __name__ == "__main__":
    main()
