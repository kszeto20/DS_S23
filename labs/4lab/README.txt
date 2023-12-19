1. How does the output from your memory debugger differ when you compile your program with the -g
flag compared to when you leave it out?

Gives more detailed info about where the error occured and what types of objects are causing the error to be thrown

2. How would you rewrite the for loop in part 2 to use the bracket [] operator instead of pointer syntax?

array[*numElements + i] --> increment i;

3. For DrMemory users, you would’ve encountered all of these errors in parts 1, 2, or 3 of Checkpoint 2:
UNITIALIZED READ
UNADDRESSABLE ACCESS
INVALID HEAP ARGUMENT
LEAK
4. For Valgrind users, the errors you will have seen are:
Use of uninitialised value
Invalid write
Invalid read
Conditional jump or move depends on uninitialised value(s)
Mismatched free() / delete / delete []
? bytes in ? blocks are definitely lost in loss record ? of ?
5. What do you think each of these errors mean?