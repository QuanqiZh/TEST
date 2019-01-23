Author          : Zongyi Li, Zhiquan Zhang

Created         : 10/18/2018

Last Modified   : 10/18/2018

Affiliation          : Electrical and Computer Engineering Department, Georgia Institute of Technology


Description  
-------------

These programs is for 18 fall cse6010’s assignment3. The program can read and check a configuration file for generating a queueing system and set up a system, simulate the process and analyse some useful information about the system.

Installation
------------

To install,  in 'src' file you can run the following orders and you will get files named 'sim'. The file’s name after ‘-o’ could be assigned.

    gcc application.c config.c engine.c random.c -std=c99 -o sim -lm
    
The file sim can execute the reading and simulation. Note that you should add '-lm' at the end to use 'math.h'.

Execution
-----------

Execute file 'sim'.The order should be like below. Note that there should be 4 parameters, the first is the program's name, the second one is the simulation time, the third one is the name of the configuration file(don't include '.txt'!) and the fourth one is the name of the output file(don't include '.txt'!). Be sure to put the file 'config.txt' in the same folder as sim!

    ./sim 240.0 config output

