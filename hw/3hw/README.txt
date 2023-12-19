HOMEWORK 3: MATRIX CLASS


NAME:  < Kirsten Szeto >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< w3schools.com, tutorialspoint.com  >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6hrs >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(2) - because arrays have linear search; 1 (search for specific row) + 1 (search for specific element in row)

set: O(2) - because arrays have linear search; 1 (search for specific row) + 1 (search for specific element in row)

num_rows - O(1) just returns a value (no look up)

get_column - O(m^2)

operator<< - O(m*n)

quarter - O(4(m*n))

operator== - O(m*n)

operator!= - O(m*n)

swap_rows - O(n)

rref (provided in matrix_main.cpp) - O(m*n)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used valgrind to check for memory leaks. The way I wrote the code initially I genuinely did not have memory leaks. 
I wrote my clear() function almost immediately after starting to build my matrix class. The only issue was not having an officially declared destructor which I fixed by declaring it and calling my clear function.

If I were to have memory issues I would just look at the lines that were fed out from valgrind and then I would trace my program to see what memory was being dealt with and then figure out where I need to add delete calls.


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

I implemented the resize()
O(2m+n+(m*n))

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

did not put that many comments becauase all functions are described in homework instructions except resize()