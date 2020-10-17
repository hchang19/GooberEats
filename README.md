# GooberEats!

# Description
All delivery services leverage delivery logistics systems, and Goober Corp. needs one built for
their service. A delivery logistics system is one that takes one or more delivery requests (e.g.,
deliver pasta primavera to the corner of Veteran and Strathmore and a double-double to the
corner of Westwood and Wilshire, etc.), optimizes the delivery order (to reduce driving time and
ensure the food doesn’t cool too much) and generates turn-by-turn navigation and delivery
instructions for a delivery robot so it can deliver all of its food efficiently. The more deliveries per
day that a delivery robot can make and the less energy it uses, the better – so route
optimization is key.

# Steps
 1.) The program first parse and load the coordinates of the surrounding area. In this case, the coordinates used
 are the locations of turns and stops near UCLA. The program then proceeds to link the coordinates to form
 streets. 
 
 2.) The user can provide a list of items to deliver, starting location,and whether or not they wish to 
     return the original starting point.

 3.) Using A* (A star) algorithm, the program attempts to find an optimal path from point A to point B, until the entire
 has been traversed and all items delivered. Essentially, it attempts to find a path. 
 
 4.) Using simulating annealing, the program tests multiple possibilities of A* and attempt to find the most optimal route
 to deliver all the items.
