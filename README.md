# Routing
Depth First Search for graph pathfinding

Using gnuplot:
>  plot 'map_junctions.dat' using 1:2 with points pointtype 7 lt rgb 'black',\   
>'route_map.dat' using 1:2:3:4 with vectors arrowstyle 1,\                     
>'best_route.dat' using 1:2:3:4 with vectors arrowstyle 2,\                    
>'start_end.dat' using 1:2 with points pointtype 8 lt rgb 'red' pointsize 4

![alt tag](https://raw.github.com/veeskochill/routing/master/dfs_path.png)
