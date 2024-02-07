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

def test_all(prog, input_dir, output_dir):
    test_output_vs_expected(prog , input_dir + "/input1.txt" , output_dir + "/output1.txt")
    test_output_vs_expected(prog , input_dir + "/input2.txt" , output_dir + "/output2.txt")
    test_output_vs_expected(prog , input_dir + "/input3.txt" , output_dir + "/output3.txt")
    if prog == "my_graph":  # hack
        test_output_vs_expected(prog , input_dir + "/input4.txt" , output_dir + "/output4.txt")

def main():
    test_all("src/my_graph", "./inputs", "./outputs")
    test_all("src/my_Knapsack", "./inputs_2", "./outputs_2")

    if passed == 1:
        print("You have PASSED the initial checks.")
    else:
        print("You have FAILED the initial checks. go fix your code.")
    


if __name__ == "__main__":
    main()
