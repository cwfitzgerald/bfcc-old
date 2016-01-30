# bfcc
An optimizing brainfuck interpreter/C Compiler written in C++

## Compilation
Before anything, check the makefile to make sure that CXX is set to the proper command for a C++14 complient compiler on your machine.

You can just run ```make``` to get an optimized version or ```make debug``` for -Og and -g flags on the compiler. This is currently only compatiable with C++14 due to how I initalize structs, so you need clang++ >= 3.4 or g++ >= 5. The compilation will produce the binary bfcc.

## Running
###Basic
```
./bfcc helloworld.bf
```
It will then take any inputs from stdin as data for the program, and will print output on STDOUT.

###Advanced
#####```-h or -H```
Prints help.

#####```-i```
The argument after the ```-i``` flag marks the file of the program to be read. The ```-i``` flag will always overule a naked filename argument. The last -i flag that is found will be used.

#####```-o```
If this flag is specified, all program output will be written to a file instead of STDOUT.

#####```-On```
This turns off the optimizer, making it interpret or compile a raw translation of the original code.

#####```-c```
This switches from interpreting to compiling. Outputs ANSI C complient code. 

#####```-v(1/2) or -V(1/2)```
Turns on verbose output. With -V1, it prints execution time at the bottom of the program output. With -V2, it prints compiled instruction set before running or compiling the program.

## Optimizations
####Combine adjecent operations
```++++++--``` turns into ```(+,4)```

####Remove non-operations
```+++---``` gets removed

###Loop Optimizations:
####Clear loops
```[-] or [++-]``` turn into ```(CLR)```

####Find until empty loops:
```[>] or [>>>>]``` turn into ```(FIND,1) or (FIND,4)```

####Multiply and copy loops:
```[->+-] or [->>>+>+>++<<<<<]``` turn into ```(CP,1)(CLR) or (CP,3)(CP,4)(MUL,5,2)(CLR)```

####Print move loops:
```[.>] or [>.>] or [>>>>.>]``` turn into ```(FPRNT,0,1) or (FPRNT,1,1) or (FPRNT,4,1)```
