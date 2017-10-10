## Unix Shell

This repository contains the code for a unix shell, that can execute commands, pipe, and change directory. The background tasks were tried to be implemented but it wasnt possible for me  to do so.

This directory contains the following files:
     mytoc.c: Tokenizer used for parsing.
     mytoc.h: Header for tokenizer.
     shell.c: The code for implementing the shell.
     Makefile: Standard Makefile.

## IMPORTANT NOTICE:
~~~
The shell does not pass the test provided by the instructors. However, after reviewing the contents with Adrian we found out it was because a bizarre prompt was printing out when there was a interchangeable running of bash and the shell. By this I mean that, while on bash, if I export the variable PS1 as "" I will have no trouble and behavior would be as it should be, but when running the way the test script works, a weird prompt is printed out. Neither me nor Adrian could figure out the reason for this bug. Adrian suggested testing manuallyto account for this. He also exclamaied that this was a really bizarre error. 
~~~

To compile:
~~~
$ make all
~~~~

To delete binaries:
~~~
$ make clean
~~~