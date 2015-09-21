# Routing
Depth First Search for graph pathfinding

Given a set of pathways (one-way or bi-directional), what is the best route to travel from an initial point to a final position when restricted to these pathways?

A set of nodes are randomly generate. A pathway between any two nodes, from node A, to node B is created with a probability
beta*exp(-d/L/alpha), 

where d is the distance between the two nodes |B-A|,

L is the largest distance between any nodes,

beta, and alpha are constants.



This algorithm computes the dot product of two vectors, from the current node to the final position, and from the current node to each valid destination along one of the pathways. The normalized dot product with the greatest value is the pathway most directed towards the target destination, and is chosen recursively until the final position is reached.

Using gnuplot:
>  plot 'map_junctions.dat' using 1:2 with points pointtype 7 lt rgb 'black',\   
>'route_map.dat' using 1:2:3:4 with vectors arrowstyle 1,\                     
>'best_route.dat' using 1:2:3:4 with vectors arrowstyle 2,\                    
>'start_end.dat' using 1:2 with points pointtype 8 lt rgb 'red' pointsize 4

![alt tag](https://raw.github.com/veeskochill/routing/master/dfs_path.png)
