//Peter Carle

/*
This is my most current implementation of Dijkstra's algorithm.

It is essentially a bare-bones navigation program which
finds the shortest distances between the starting point
and the rest of the points on the map. It also finds the
specific shortest path from the starting point to the
destination point. 

In computer science terms:

-- "graph" means "map" (...within this context. In
reality, a graph data structure can represent many kind 
of relationships--not just physical distances.)
-- "node" means "point/location on the map"

I originally wrote a C++ version for one of the later
assignments in my Data Structures class in Fall of 2017.
It wasn't that great. So in preparation for an interview
earlier this year, I started rewriting it from scratch. 

This version came out much better than the 2017 version.
Since finding the shortest path within a graph is a
fundamental computing task, I saw fit to include it in my
public portfolio. 

More detailed documentation may be found within the inline
comments, especially starting at line 147.

§ Peter Carle §
May 28th, 2019

*/

#include <stdio.h>
#include <stdlib.h>

enum constants
{
	NODE_COUNT = 8, 
	EDGE_COUNT = 12,

	INF = 0x7FFFFFFF,

	MAX_RECON_STACK = 20,
	MAX_QUEUE = 50,
	MAX_NODE = 7,
	MAX_INPUT_LINE = 8,
	MIN_NODE = 1,

	INPUT_SIZE = 10,
};

/*A data structure used to store both the distance associated
with a particular node--and the path taken thus far to arrive
at this node.*/
struct reconstruct
{
	/*The distance traveled thus far.*/
	int distance;
	
	/*Index to the top of the stack.*/
	int index;
	
	/*A stack used to store the path traveled thus far.*/
	int stack[MAX_RECON_STACK];
};
typedef struct reconstruct predecessor;


int 
main(int argc, char * argv [])
{	
	int matrix[NODE_COUNT][NODE_COUNT];
	int visited[NODE_COUNT][NODE_COUNT];	
	int queue[MAX_QUEUE];
	char int_string[INPUT_SIZE];
	predecessor distances[NODE_COUNT];
	
	FILE* ptr = NULL;	
	int* curr_tmp = NULL;
	
	int index = 0;
	int bindex = 0;
	
	int user_src = 0;
	int user_dst = 0;
	
	int path_top = 0;
	int head = 0;
	int tail = 0;
	
	int source = 0;
	int dest = 0;
	int updest = 0;
	int weight = 0;
	int step = 0;
	
	/*Initializing everything to default values.*/
	for (;index < NODE_COUNT; index++)
	{
		distances[index].distance = INF;
		distances[index].index = 0;
		for (bindex = 0; bindex < MAX_RECON_STACK; bindex++)
			distances[index].stack[bindex] = 0;
			
		for (bindex = 0; bindex < NODE_COUNT; bindex++)
		{
			matrix[index][bindex] = INF;
			visited[index][bindex] = 0;
		}
	}

	/*Full disclosure: input.txt happens to be the same input
	file as the one originally provided by my Data Structures
	professor in 2017. I needed a reference point to easily
	verify correctness during testing.*/

	ptr = fopen("input.txt", "r");
	
	if (!ptr)
	{
		puts("File read failed.");
		exit(1);
	}
	
	/*
	Input file format: 
	
	column 0: source node
	column 1: destination node
	column 2: distance/weight
	*/		
	
	for (index = 0; index <= EDGE_COUNT; index++)
	{
		fgets(int_string, MAX_INPUT_LINE, ptr);
		
		source = atoi(&int_string[0]);
		dest = atoi(&int_string[2]);
		weight = atoi(&int_string[4]);
		
		matrix[source][dest] = weight;
	}
	index = source = dest = weight = 0;
	
	if (!argv[1] || !argv[2])
	{
		puts("Required usage: ./a.out [source] [destination]");
		exit(0);
	}
	
	/*Input validation handled primarily by atoi() in this
	simple application.*/
	user_src = atoi(argv[1]);
	user_dst = atoi(argv[2]);
	
	if (user_src > MAX_NODE || user_src < MIN_NODE
		 || user_dst > MAX_NODE || user_dst < MIN_NODE)
	{
		printf("Currently defined values for source and destination must be between %i and %i.\n", MIN_NODE, MAX_NODE);
		exit(0);
	}
	
	/*Initializations for first node.*/
	matrix[user_src][user_src] = 0;	
	distances[user_src].distance = 0;
	for (index = 0; index < NODE_COUNT; index++)
		distances[index].stack[0] = user_src;
	visited[user_src][user_src] = 1;
	
	/*Queue implemented as an array with head and tail indices.*/
	tail++;
	queue[0] = user_src;
	
	/*
	Dijkstra's algorithm finds the set of shortest distances
	from the starting node to every other reachable node on the
	graph. This implementation of it also prints out the list
	of actual nodes visited for the shortest path from the
	source node to the destination node. 
	
	While the algorithm is effective at finding the shortest
	distance from the starting point to the ending point, it
	can also be inefficient. If my understanding is correct,
	the introduction of a heuristic to Dijkstra's algorithm
	turns it into the potentially much faster A* algorithm,
	which, while not guaranteed to find the *shortest* path,
	should be able to find a path in a complex graph while
	retaining reasonable performance. 
	
	Due to time constraints, I have not implemented the A*
	algorithm for this project. 
	*/
	
	while (head != tail)/*Visiting neighbors.*/
	{	
		index = 0;	
		source = queue[head];
		if (head < MAX_QUEUE) head++;
		else { puts("ERROR: Queue overflow."); exit(1); }

		/*Performs a breadth-first search for each node's set
		of neighbors.*/
		for (dest = 0; dest < NODE_COUNT; dest++)
		{
			/*Checks whether an unvisited node exists here.*/
			if (matrix[source][dest] != INF && !visited[source][dest])
			{	
				/*step is the prospective distance from the
				previous node to the current node.*/
				step = matrix[source][dest] + distances[source].distance;
				if (step <= distances[dest].distance) /*UPDATE THE ARRAY OF DISTANCES*/
				{	/*
					Each node's index in the distance array has
					a stack in which each visited node is
					placed. This stack represents the sequence
					of nodes visited to get this far.
				 	
					If the distance has been updated, the entire
					source predecessor stack is copied to the
					dest predecessor stack. This is because 	
					the source,	with its associated distance 	
					and predecessor	stack, represents the 
					shortest distance found thus far. The 
					preexisting dest predecessor stack may be 
					completely invalid until it's overwritten 
					with the source predecessor stack. 
					*/
			
					path_top = distances[source].index;
					for (index = 0; index <= path_top; index++)
						distances[dest].stack[index] = distances[source].stack[index];		
					distances[dest].distance = step;
					path_top++;
					distances[dest].stack[path_top] = dest;
					distances[dest].index = path_top;

					updest = dest;
					queue[tail] = dest;
					if (tail < MAX_QUEUE) tail++;
					else { puts("ERROR: Queue overflow."); exit(1); }				
				}				
			}		
		}
		visited[source][updest] = 1;
	}
	
	puts("\nDistances from starting point to every node:");
	
	for (index = 0; index < NODE_COUNT; index++)
	{
		if (distances[index].distance != INF)
			printf("%i -> %i | %i\n", user_src, index, distances[index].distance);
	}
	
	puts("\nACTUAL ROUTE:");
	curr_tmp = distances[user_dst].stack;
	path_top = distances[user_dst].index;
	for (index = 0; index <= path_top; index++)
	{
		printf("%i ", curr_tmp[index]);
		if (index < path_top)
			printf("-> ");
	}
	putchar('\n');

	if (ptr) fclose(ptr);
	ptr = NULL;

	return 0;
}



