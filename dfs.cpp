#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>

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

	//node current_edge = start;
	//float* dot_products = (float*)malloc(num_edges*sizeof(float));
	std::vector<float> dot_products;
	for(int ui =0 ; ui < start.num_edges; ui++){
		point to_dest = subtract(end, start.pos);
		point to_next = subtract(start.edges[ui]->pos, start.pos);
		float result_value = dot_prod(to_dest, to_next);
		dot_products.push_back(result_value);
	}
	for(int ui; ui< start.num_edges; ui++){
		if(dfs(*start.edges[ui], end) != NULL){
			printf("%d, %d", start.pos.x, start.pos.y);
			return start.edges[ui];
		}
	}
	return NULL;
};

//Waxman model?
void generate_map(node *p_node, point* p_end){
	printf("started\n");
	int num = 10;
	node* map = new node[num];//(node*)malloc(num*sizeof(node*));
	for(int ui=0;ui<num;ui++){
		map[ui].pos.x = float(rand() % 100);
		map[ui].pos.y = float(rand() % 100);
		map[ui].num_edges = 0;
		map[ui].edges = (node**)malloc(10*sizeof(node*));

		//printf("%d %d\n", ui, map[ui].num_edges);
		//printf("%d has addy = %d\n", ui, &map[ui]);

		//map[ui].edges = std::vector<node*>();
	}
	//Find the maximum distance between any 2 nodes
	printf("more\n");
	float maxL = 0;
	for(int ui=0;ui<num;ui++){
	//	printf("%d edges  before : %d\n", ui, map[ui].num_edges);
		for(int uj=0;uj<num;uj++){
			if(ui != uj){
				float dij = dist(map[ui].pos, map[uj].pos);
				if(dij > maxL)
					maxL = dij;
			}
		}
	//	printf("%d edges  after : %d\n", ui, map[ui].num_edges);
	}

	//if < Be(-d/L/a), create edge 
	printf("edges\n");
	float beta = 50.0;
	float alpha = 1.5;
	for(int ui=0;ui<num;ui++){
	//	printf("%d edges  outer : %d\n", ui, map[ui].num_edges);
		for(int uj=0;uj<num;uj++){
	//		printf("%d edges  inner : %d\n", uj, map[uj].num_edges);

			if(ui != uj){
				float dij = dist(map[ui].pos, map[uj].pos);
				float prob = beta*exp(-dij/maxL/alpha);
			//	printf("%f\n", prob);
				if(rand()%100 < prob){
					//create link
			//		printf("%d has addy = %d\n", uj, &map[uj]);
					map[ui].edges[map[ui].num_edges] = &map[uj];
					map[ui].num_edges += 1;
			//		printf("p1 (%f,%f) to p2 (%f, %f)\n",map[ui].pos.x, map[ui].pos.y,map[uj].pos.x, map[uj].pos.y);
			//		printf("edges count : %d\n", map[ui].num_edges);
				}
			}
		}
	}
	printf("start-end\n");
	int start = rand() % 10;
	int end = rand() % 10;
	while(end == start)
		end = rand() % 10;
	p_node = &map[start];
	p_end = &map[end].pos;
	printf("end\n");
}

int main(){

	node * start = NULL;
	point *end = NULL;

	generate_map(start, end);

	printf("final");
	//starting_edge = node();
	//ending_position_x, ending_position_y;
	return 0;
}