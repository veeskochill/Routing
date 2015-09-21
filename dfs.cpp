#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <algorithm>

//2D Vector/Point
struct point{
	float x, y;
};

//Vector Subtraction
point subtract(point p1, point p2)
{
	point result;
	result.x = p2.x - p1.x;
	result.y = p2.y - p1.y;
	return result;
};

//Euclidian Distance
float dist(point p1, point p2)
{
	return pow(pow(p2.x - p1.x,2) + pow(p2.y- p1.y, 2),0.5);
};

float dot_prod(point p1, point p2)
{
	return p1.x*p2.x + p1.y+p2.y;
}

struct node{
	point pos;
	int num_edges;
	node** edges = NULL;
};

node* dfs(node start, point end){

	if(start.pos.x == end.x && start.pos.y == end.y)
		return NULL;
	
	std::ofstream myfile;
	myfile.open("best_route.dat", std::ofstream::out | std::ofstream::app);
	//node current_edge = start;
	//float* dot_products = (float*)malloc(num_edges*sizeof(float));
	std::vector<float> dot_products;
	for(int ui =0 ; ui < start.num_edges; ui++){
		point to_dest = subtract(start.pos, end);
		point to_next = subtract(start.pos, start.edges[ui]->pos);
		float result_value = dot_prod(to_dest, to_next)/sqrt(dot_prod(to_dest,to_dest))/sqrt(dot_prod(to_next,to_next));
		dot_products.push_back(result_value);
	}
	int ui = std::distance(dot_products.begin(),std::max_element(dot_products.begin(), dot_products.begin()+start.num_edges));
	//for(int ui=0;ui<start.num_edges;ui++)
	//	printf("%f\n", dot_products[ui]);
	//for(int ui=0; ui< start.num_edges; ui++){
		//printf("%d\n", ui);
	printf("%d : %f, %f --> %f, %f\n", ui, start.pos.x, start.pos.y, start.edges[ui]->pos.x, start.edges[ui]->pos.y);
	point diff = subtract(start.pos, start.edges[ui]->pos);
	myfile << start.pos.x << " " << start.pos.y << " " << diff.x << " " << diff.y << " " << std::endl;
	
		if(dfs(*start.edges[ui], end) != NULL){
			myfile.close();
			//printf("%d : %d, %d\n", ui, start.pos.x, start.pos.y);
			return start.edges[ui];
		}
	//}
	myfile.close();
	return NULL;
};

//Waxman model?
node* generate_map(){

	printf("started\n");
	std::ofstream myfile1;
	myfile1.open("map_junctions.dat");

	int num = 10;
	node* map = new node[num];//(node*)malloc(num*sizeof(node*));
	for(int ui=0;ui<num;ui++){
		map[ui].pos.x = float(rand() % 100);
		map[ui].pos.y = float(rand() % 100);
		map[ui].num_edges = 0;
		map[ui].edges = (node**)malloc(10*sizeof(node*));
		myfile1 << map[ui].pos.x << " " << map[ui].pos.y << std::endl;
		//printf("%d %d\n", ui, map[ui].num_edges);
		//printf("%d has addy = %d\n", ui, &map[ui]);

		//map[ui].edges = std::vector<node*>();
	}
	myfile1.close();
	printf("size = %d\n", sizeof(map));
	//Find the maximum distance between any 2 nodes
	printf("more\n");
	float maxL = 0;
	for(int ui=0;ui<num;ui++){
	//	printf("%d edges  before : %d\n", ui, map[ui].num_edges);
		for(int uj=0;uj<num;uj++){
			if(ui != uj){
				float dij = abs(dist(map[ui].pos, map[uj].pos));
				if(dij > maxL)
					maxL = dij;
			}
		}
	//	printf("%d edges  after : %d\n", ui, map[ui].num_edges);
	}

	std::ofstream myfile;
	myfile.open("route_map.dat");

	//if < Be(-d/L/a), create edge 
	printf("edges\n");
	float beta = 50.0;
	float alpha = 1.5;
	for(int ui=0;ui<num;ui++){
	//	printf("%d edges  outer : %d\n", ui, map[ui].num_edges);
		for(int uj=0;uj<num;uj++){
	//		printf("%d edges  inner : %d\n", uj, map[uj].num_edges);

			if(ui != uj){
				float dij = abs(dist(map[ui].pos, map[uj].pos));
				float prob = beta*exp(-dij/maxL/alpha);
				printf("%d %d %f\n", ui, uj, prob);
				if(rand()%100 < prob){
					//create link
			//		printf("%d has addy = %d\n", uj, &map[uj]);
					map[ui].edges[map[ui].num_edges] = &map[uj];
					map[ui].num_edges += 1;
					printf("%d %d\n", ui, map[ui].num_edges);
					point diff = subtract(map[ui].pos, map[uj].pos);
					myfile << map[ui].pos.x << " " << map[ui].pos.y << " " << diff.x << " " << diff.y << " " << std::endl;
			//		printf("p1 (%f,%f) to p2 (%f, %f)\n",map[ui].pos.x, map[ui].pos.y,map[uj].pos.x, map[uj].pos.y);
			//		printf("edges count : %d\n", map[ui].num_edges);
				}
			}
		}
	}
	myfile.close();
	printf("start-end\n");

	printf("end\n");
	return map;
}

int main(){

	node* map = generate_map();
	printf("%f %f\n", map->pos.x, map->pos.y);
	printf("size = %d\n", sizeof(map));


	int start = rand() % 10;
	int end = rand() % 10;
	while(end == start)
		end = rand() % 10;
	node* p_node = &map[start];
	point* p_end = &map[end].pos;
	printf("%d :%f, %f\n", start, p_node->pos.x, p_node->pos.y);
	printf("%d :%f, %f\n", end, p_end->x, p_end->y);
	std::ofstream myfile;
	myfile.open("start_end.dat");
	myfile << p_node->pos.x << " " << p_node->pos.y << std::endl;
	myfile << p_end->x << " " << p_end->y << std::endl;
	myfile.close();



	printf("JUST DOIT\n");
	dfs(*p_node, *p_end);

	delete[] map;

	printf("final");
	//starting_edge = node();
	//ending_position_x, ending_position_y;
	return 0;
}