# HashTable-In-C

Hash Tables are amazing data structures, here is an attempt to implement a Hash Table from scratch in C.
Sailent feature of this implementation:
- Generic Programming in C
- Growing of Hash Table at runtime.

## How to run?

Here, `program.c` contains the driver function. To build the codebase, run `make`. To run the program:

`./program 1000`

This program takes 1 argument - the number of key-values to be inserted. This will automatically perform insertion and fetch operations on the hash table and return the results.

It is advisable to run this program with a timeout when dealing with huge number of insertions.
Example: `timeout 20 ./program 100000` Although it depends on sytem hardware, 20 seems to be an ideal time limit.

