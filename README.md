# bfcc
A (soon to be) optimizing brainfuck interpreter written in C++

# Compilation
You can just run ```make``` to get an optimized version and ```make debug``` for -Og and -g flags on the compiler. This is currently only compatiable with C++14 due to how I initalize structs, so you need clang++ >= 3.4 or g++ >= 4.9. The compilation will produce the binary bfcc.

# Running
```
./bfcc helloworld.bf
```
It will then take any inputs from stdin as data for the program. 
