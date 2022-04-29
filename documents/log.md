## What goals you had set for the week and whether they were accomplished or not
Week 1: Our primary goal was reading csv file and constuct graph. We were able to read csv file in and implement RoadGraph class constructor. We made two different structs called Edge and RoadNode. 

Week 2: Our goal is to find shortest path between two nodes using Dijkstra's algorithm. To be honest, everything went smoothly. Since we are farmiliar with Dijkstra's algorithm, we were able to accomplish successfully. When we run it, we get expected output.

Week 3: Our goal was to implement the approximate traveling salesman algorithm. We went ahead and implemented the travelling salesman by finding the shortest path between each node in our vector of nodes to compute the travelling salesman path between. Then, we found each permutation of the salesman path and returned the optimal path between each vertices. 

Week 4: Our goal was to implement A* algorithm and to add test cases for Djikstra, Salesment, and A* algorithms. We successfully were able to successfully accomplished implementing plenty of test cases. We also checked that all test cases passed and A* algorithm is 50% faster than Djikstra algorithm.

Week 5: Our goal for this week was to finalize our project including making visualization of our graph. We successfully were able to acoomplished visualizing grpah using OpenLayers, which is an open-source JavaScript library for displaying map data in web browsers. 


## What specific tasks each member of your team accomplished in the week

Week 1: Since this week was pretty light workload, read data file in and construct RoadGraph, we did together using one laptop. All group members downloaded required packages/libraries. 

Week 2: Similiar to last week, this week workload is pretty light and there was not much thing to divide work. We did together using one laptop. All group members discussed and actively participated to implement shortestPath function. 

Week 3: Every week, we work together at Grainger and code what we need to get done collaboratively on someone's computer. This week, we all worked together to implement the travelling salesman algorithm.

Week 4: Nick and Akshay implemented A* algorithm and test cases for comparing time efficiency between Djikstra and A* algorithms. Jeewon implemented test casees for comparing if Djikstra and A* algorithm returns the same output.

Week 5: Same as past few weeks, we work together at Grainger library and code what we need to get done collaboratively on someone's computer. This week, we implemented basic structure of visualization using OpenLayers using Nick's computer. Then, Nick focused on compiling our application on browser, Akshay focused on moving all the points from Africa to America. Jeewon wrote log.md and fix some fonts on browser.

## What problems you encountered (if any) that prevented you from meeting your goals

Week 1: We encountered problem when we tried to download some packages for reading data in as csv file. The problem was cmake package was too old. However, we solved this problem by using docker container. 

Week 2: The only problems we had were with a merge conflict because we failed to pull the feedback change. After implementing Dijkstra's, we realized we forgot to handle the case where the start and end nodes are disjoint, that was an easy change. As it is right now, we think everything works properly.

Week 3: We realized that our current implementation of the shortest path could be (potentially) a lot more efficient if we used A* search instead of Dijkstra's since we could use the Euclidean distance between two nodes as the heuristic for the search. This is much better than Dijkstra's since we smartly explore nodes that are physically closer as opposed to arbitrary neighbors of the current node in Dijkstra's. 

Week 4: Coordinates approximation for constructing Graph was not accurate. Because of this A* returns inaccurate outputs. We solved this problem using actual dataset since the coordinates are accurate. 

Week 5: Problems we encountered were loading c++ code into a browser so that it compiles without any problem. Also, Jeewon was not able to connect github (cannot add, commit, pull or push anything). I tried several different ways to resolve but couldn't figure it out. Jeewon had to re-clone the whole repo again.

## What you plan to accomplish next week

Week 2 Goal: Find shortest path between two nodes using travsal.

Week 3 Goal: Implement the approximate traveling salesman algorithm

Week 4 Goal: Implement A* search to (hopefully) greatly improve the run time of our shortest path algorithm and if we have enough time, get started or finish the visualization of our shortest path algorithms. 

Week 5 Goal: Finalize existing algorithms and do visualization for graph. 

Week 6 Goal: Prepare final presentation. 