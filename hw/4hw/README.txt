HOMEWORK 4: TOOL RENTAL LISTS


NAME:  < Kirsten Szeto >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< w3schools, cpp.com, geeksforgeeks >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file:
O(i^2) - insert depends on making each inventory item (i) and looping through a max of i elements to find where to sort it 

Rental event:
O(i*c) - loops through to find tool and find if a customer exists

Return event - no pending customer(s):
O(i*c) - loops through to find tool and find if customer exists

Return event - with pending customer(s):
O(i*c*p) - loops through to find tool and find if customer exists + loops through to find any pending candidates

Entire program:

O(i^2 + c^2) - not really sure



MISC. COMMENTS TO GRADER:
(optional, please be concise!)
all functions and attributes of inventory class have "t_" in front of names
all functions and attributes of customer class have "c_" in front of names
sorry about my customer parsing function being so long