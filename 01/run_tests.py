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
        print("command failed: " + cmd)
        print(inst)
        exit(1)

def test_output_vs_expected(prog , input_f , expected_f):
    global passed
    run_cmd("./%s < %s > tmp_out.txt"%(prog ,input_f ))
    if not filecmp.cmp('tmp_out.txt',expected_f ):
        print("difference found in ./%s < %s vs "%(prog ,input_f) ,expected_f)
        run_cmd("vimdiff %s %s"%('tmp_out.txt', expected_f))
        sys.exit(1)
        passed = 0
        run_cmd("cat tmp_out.txt")
        run_cmd("cat " + expected_f )
    run_cmd("rm tmp_out.txt" , 0)

def test_all(prog):
    test_output_vs_expected(prog , "./inputs/input1.txt" , "./outputs/output1.txt")
    test_output_vs_expected(prog , "./inputs/input2.txt" , "./outputs/output2.txt")
    test_output_vs_expected(prog , "./inputs/input3.txt" , "./outputs/output3.txt")
    test_output_vs_expected(prog , "./inputs/input4.txt" , "./outputs/output4.txt")
    test_output_vs_expected(prog , "./inputs/input5.txt" , "./outputs/output5.txt")

def main():
    test_all("src/mains")
    test_all("src/maindloop")
    test_all("src/maindrec")

    if passed == 1:
        print("You have PASSED the initial checks.")
    else:
        print("You have FAILED the initial checks. go fix your code.")
    


if __name__ == "__main__":
    main()
