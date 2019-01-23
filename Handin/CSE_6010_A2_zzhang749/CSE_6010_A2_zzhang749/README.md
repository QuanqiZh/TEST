Author          : Zhiquan Zhang

Created         : 9/26/2018

Last Modified   : 9/29/2018

Affiliation          : Electrical and Computer Engineering Department, Georgia Institute of Technology


Description  
-------------

These programs is for 18 fall cse6010’s assignment2. The program can generate a adjacency list and then analyze importnat information about it like the number of components, the average size of components, the largest component's area, the histogram of the components. Some changes has been made and they are recorded in the file "Sept 29.log".


Installation
------------

To install, you can in 'src' file run the following orders and you will get files named ’generate’ and 'analyze'. The file’s name after ‘-o’ could be assigned.

    gcc pro1graph.c pro1main.c -o generate
    
    gcc graph.c main.c -o analyze 
    
The file "generate" can generate a file containing adjacency list. The file "analyze" can analyze the information of the adjacency list file.

Execution
-----------

The first executable file of your program is called “generate”, for example, in 'src' file run it using(note: don't include".txt"!)

    ./generate 1000 0.6 topology

You will then get a file named "topology.txt", which contains a adjacency list and the number of the vertexes in the graph.

The second executable file of your program is called “analyze”, run it using(note: don't include".txt"!)

    ./analyze topology result
    
You will then get a file named "result.txt", which contains the number of components, the average size of components, the largest component's area, the histogram of the components.