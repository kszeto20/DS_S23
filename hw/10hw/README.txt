HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Kirsten Szeto >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< w3schools, cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



NAIVE ALGORITHM:

Order Notation: O((w*h)^2)

Timing Experiment Data:
-- time ./out tiny_5x5.ppm out.ppm naive_method grey_bands
    real    0m0.003s
    user    0m0.001s
    sys     0m0.000s

-- time ./out tiny_10x10.ppm out.ppm naive_method grscale
    real    0m0.003s
    user    0m0.003s
    sys     0m0.000s

-- time ./out squiggle_30x30.ppm out.ppm naive_method greyscale
    real    0m0.013s
    user    0m0.013s
    sys     0m0.001s

-- time ./out lines_100x100.ppm out.ppm naive_method greyscale
    real    0m1.180s
    user    0m1.180s
    sys     0m0.000s

Discussion:

It seems like as if the user values are properly and as expecting increasing as a multiple
of the square of the amount of squares increase.

For example, 5 --> 10 = 10/5 = 2 --> 2^2 = 4 * 1 (original time for 5) = 4 which is around 3
Another example, 30 --> 100 = 100 / 30 ~= 3.-- --> 3 ^ 3 = 9 * 13 (original time for 30) = 117 which is around 118


IMPROVED ALGORITHM:

Order Notation: O((w*h) + (w*h*b)) -- b = number of black squares

Timing Experiment Data:

- squiggle_30x30:
    - native:
        real    0m0.014s
        user    0m0.013s
        sys     0m0.000s
    
    - improved:
        real    0m0.005s
        user    0m0.005s
        sys     0m0.000s

- lines_100x100:
    - naive:
        real    0m1.065s
        user    0m1.064s
        sys     0m0.001s

    - improved:
        real    0m0.052s
        user    0m0.052s
        sys     0m0.000s

- data_structures_300x300:
    - naive: 
        real    0m13.184s
        user    0m13.173s
        sys     0m0.011s

    - improved:
        real    0m0.052s
        user    0m0.052s
        sys     0m0.000s


Discussion:

The improved algorithm is much faster than the naive algorithm. For the cases that I tested, 
the improved algorithm runs in a fraction of the time that the naive runs in. 

5x5 and 10x10 cases are too small to have a huge difference like in the 30x30, 100x100, 300x300


FAST MARCHING METHOD (with a map):

Order Notation: O( (w*h)log(w*h) )             

Timing Experiment Data:
-  time ./out tiny_5x5.ppm out.ppm pq_with_map greyscale
    real    0m0.003s
    user    0m0.003s
    sys     0m0.000s

- time ./out squiggle_30x30.ppm out.ppm pq_with_map greyscale
    real    0m0.010s
    user    0m0.000s
    sys     0m0.010s

- time ./out lines_100x100.ppm out.ppm pq_with_map greyscale
    real    0m0.092s
    user    0m0.092s
    sys     0m0.000s

- time ./out data_structures_300x300.ppm out.ppm pq_with_map greyscale
    real    0m1.061s
    user    0m1.050s
    sys     0m0.010s
Discussion:

The fast marching method is extremely fast and it is very noticable especially in the larger cases
For the 300x300 it's takes 1/13 the time of the time of even the improved naive version
For the 100x100 cause it take less that 1/100 of the time the naive takes to solve the same problem

DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:



FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!





