Author          : Zongyi Li, Zhiquan Zhang

Created         : 12/01/2018

Last Modified   : 12/01/2018

Affiliation          : Electrical and Computer Engineering Department, Georgia Institute of Technology


Description  
-------------

These programs is for 18 fall cse6010’s assignment5. The program can read and check a configuration file for generating a simulation program for simulating the virus spread and control model. 

Installation
------------

To install,  in 'src' file you can run the following orders and you will get files named 'sim'. The file’s name after ‘-o’ could be assigned.

	gcc hashtable.c main.c  read.c virusSpread_medical.c dijkstra.c -std=c99 -o sim -lm
    
The file sim can execute the reading and simulation. Note that you should add '-lm' at the end to use 'math.h'. The distance.c file is used to generate distance file when developer needs. It doesn't need to be compiled.

Execution
-----------

Execute file 'sim'.The order should be like below. Note that there should be 4 parameters, the first is the program's name, the second one is the name of 1st configuration file, which contains the basic information of cities like name, location and population. The third file is the name of 2nd configuration file, which contains the traffic data between cities. The last parameter is the mode type, which can be either 1 or 0, represents emergency mode and distance mode separately. Note that this simulation program is designed for 10 cities. The configuration files **'Basic.txt' and 'Distance.txt'** are based on a lot of data and they are in the 'src' folder. They can not be modified without valid data.
    
    ./sim Basic.txt Distance.txt 0
Or
     
    ./sim Basic.txt Distance.txt 1
After execution, it will create a file named "Statics.csv". It contains the number of infectious people of all cities every time step(500 in total).