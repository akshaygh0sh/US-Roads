### Output and Correctness of the Algorithm

* We created several test cases with the dataset that we used for our actual program. The first set of cases tested the accuracy of our implementation of Dijkstra's algorithm; we made sure that our algorithm worked for several paths and made sure to include edge cases (for example, if there were multiple possible paths, we made sure we returned the shortest). 

* A few weeks after our project proposal, we thought we could probably significantly speed up the path generation by using A* search, which utilizes a heuristic to find the shortest path between two nodes (essentially searching for the destination node starting from the start node). For our heuristic, we simply used the Euclidean distance between two nodes since our dataset included this information. This resulted in a speed up of about 1.5x that of the speed of Dijkstra's; this was because our heuristic was "smartly" adding nodes to the priority queue based on their distance to the ending node, thus found the shortest path much faster. 

* To test the accuracy of our implementation of A* to find the shortest path, we just tested to see if the output of the shortest path calculated using the A* algorithm matched that of the one calculated using Dijkstra's algorithm (which we wrote actual test cases for). If Dijkstra's passed our handwritten test cases and the output of the A* path matched that of Dijkstra's, it would be safe to assume that A* was working correctly. 

* Our test cases also include the benchmarks of the two separate algorithms, which is a good way concretely seeing the signficant speed up that A* has versus Dijkstra's. 

### Answer to Leading Question - 

## Our Leading Question 

What is the most efficient way to traverse the United States by road? Given a starting and ending intersection, find the shortest route between the two nodes. Additionally, what is an efficient route for visiting several nodes in any order?

* The most efficient way to traverse the U.S. by road is to use either Dijkstra's or A* (or any other similar time complexity single source shortest path) algorithms. It turns out that Google Maps is actually implemented using a combination of Dijkstra's algorithm and the A* algorithm (this is completely coincidental, we didn't know this prior to implementing the algorithms ourselves)

* Visiting several nodes in the most optimal order is quite a difficult problem to solve quickly. We decided that for our use case, generating an optimal path that visits all nodes in the graph in a given order would be most easily achieved by going through all the N! (where N is the number of nodes in the path) possible paths, and then choosing the one with the best cost. This turns out to be fast enough for our program, although the speed of the generation of the path scales quite poorly with the number of nodes.  

* Overall, we believe our project was a success and was quite fun to complete. We realize that our solution for finding the shortest path containing a subset of nodes in the graph may be suboptimal, but, as we stated before, it is plenty efficient for our use cases and runs quite fast. In fact, the slowest part of our project is loading all the nodes into our JavaScript GUI, and we there's no great way for us to speed that process up.