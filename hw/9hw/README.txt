HOMEWORK 9: MINIBLAST


NAME:  < Kirsten Szeto >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< ds_hashset class, cplusplus.com, w3schools, geeksforgeeks, David Chong >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 >


HASH FUNCTION DESCRIPTION
hash function is the same as from lab 11



HASH TABLE IMPLEMENTATION
hash table is a vector of pairs, pairs have the kmer key and a list of positions that the key can be found at.
Extra n_occ variable (lab11 does not have it) to keep tract of occupancy ratio






ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?

O(L - k) pairs of (string, list<int>) at the maximum and O((L-k)*p) list size
Together, all the pairs will require O((L-k) * (1 + p)) memory


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

genome - O(L)
table_size - O(1)
occupancy - O(1)
kmer - O((L-k)*(L-k)) == O((L-k)^2)
query - O(qp)
quit - O(1)

insert - O(L-k)
find - O(L-k)
resize - O(L-k)




EXTRA CREDIT
Add a new command to implement the database using one of the other
data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.

none

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

