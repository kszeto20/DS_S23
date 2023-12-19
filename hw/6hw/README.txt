HOMEWORK 6: INVERSE WORD SEARCH


NAME:  < Kirsten Szeto >


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< w3schools, cplusplus.com, geeksforgeeks.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
w = wanted words
r = rows
c = cols

O( (w(r*c))^8 )

for each word, go through each space in the board (row*col), check 8 directions for insert


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

Given test cases: 
I think the longest runtime I had on one of the puzzles was 3 seconds so there is probably optimizations to be made
Most of the boards run in under half a second

I think my test cases run pretty efficiently

Own test cases:
Test Case #1: take 9 milliseconds; finishes with 192 solutions
5 3
+ hello
+ off
+ at
+ jello

Test Case #2: take 6 milliseconds; finishes with no solutions
5 3
+ hello
+ off
+ at
+ jello
- jello

Test Case #3: runs in 8 milliseconds; finishes with 88 solutions
5 3
+ hello
+ off
+ at
+ jello
- hj
- oo


MISC. COMMENTS TO GRADER:  
Optional, please be concise