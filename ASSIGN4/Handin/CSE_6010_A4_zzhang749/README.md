Author          : Zhiquan Zhang

Created         : 10/31/2018

Last Modified   : 10/31/2018

Affiliation          : Electrical and Computer Engineering Department, Georgia Institute of Technology


Description  
-------------

These programs is for 18 fall cse6010’s assignment4. The program can use parallel method and regular sequential method to calculate the multiplication of two matrix. It also record the time that different methods use.

Installation
------------

To install,  in 'src' file you can run the following orders and you will get files named 'main'. The file’s name after ‘-o’ could be assigned.

	gcc -fopenmp main.c -std=c99 -o main
    
Execution
-----------

Execute file 'main'.The order should be like below. Note that there should be 3 parameters. The first one is name of the executable file, the second one is number of threads, the third one is the size of matrix. For example, if we want to test on 10 threads, 800x800 matrix. We can use following order:

    ./main 8 100
    
Then it will output a file named "analisys.txt", which record the analysis data of test.