#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <string.h>
#include <signal.h>

#define NODE_COUNT 8  /*<-Increased to represent actual graph*/
#define EDGE_COUNT 12
#define INF 0x7FFFFFFF
#define MAX_RECON_STACK 20
#define MAX_QUEUE 50
#define INPUT_SIZE 10
#define CENTER 25
#define NUMERIC_OFFSET 48

struct path_struct
{
	int src;
	int dst;
	TAILQ_ENTRY(path_struct) path_vertices;
};
typedef struct path_struct path_struct;

struct recon
{
	int distance;
	int index;
	int stack[MAX_RECON_STACK];
};
typedef struct recon predecessor;

struct neighbor_struct 
{	
	int i;
	TAILQ_ENTRY(neighbor_struct) neighbors;
};
typedef struct neighbor_struct neighbor_struct;


int main(int argc, char * argv [])
{	
	int matrix[NODE_COUNT][NODE_COUNT];
	char visited[NODE_COUNT][NODE_COUNT];
	FILE* ptr;
	char int_string[INPUT_SIZE];
	
	int queue[MAX_QUEUE];
	//TAILQ_HEAD(stailhead, neighbor_struct) neighbor_head = TAILQ_HEAD_INITIALIZER(neighbor_head);
	//TAILQ_HEAD(stailhead_p, path_struct) path_head = TAILQ_HEAD_INITIALIZER(path_head);
	
	//TAILQ_INIT(&neighbor_head);
	//TAILQ_INIT(&path_head);
	
	int index = 0;
	int bindex = 0;
	int path_top = 0;
	int head = 0;
	int tail = 0;
	int previous = 0;
	int source = 0;
	int dest = 0;
	int up_dest = 0;

	int weight = 0;
	int step = 0;
	int update_bool = 0;
	
	predecessor iArr_distance[NODE_COUNT];
	//predecessor prev_tmp;
	int* curr_tmp;
	
	for(;index < NODE_COUNT; index++)
	{
		iArr_distance[index].distance = INF;
		iArr_distance[index].index = 0;
		for(bindex = 0; bindex < MAX_RECON_STACK; bindex++)
			iArr_distance[index].stack[bindex] = 0;
			
		for(bindex = 0; bindex < NODE_COUNT; bindex++)
		{
			matrix[index][bindex] = INF;
			visited[index][bindex] = 'F';
		}
	}
	
	for(index = 0; index < MAX_QUEUE; index++)
		queue[index] = -1;
	
	int user_src = 0;
	int user_dst = 0;
	
	/*
	if(user_src == user_dst)
	{
		printf("ALREADY THERE!\n");
		goto Finish;
	}
	*/
	ptr = fopen("input.txt", "r");
	
	for(index = 0; index <= EDGE_COUNT; index++)
	{
		fgets(int_string, 8, ptr);
		
		source = atoi(&int_string[0]);
		dest = atoi(&int_string[2]);
		weight = atoi(&int_string[4]);
		
		matrix[source][dest] = weight;
	}
	index = 0;
	source = 0;
	dest = 0;
	weight = 0;	
	
	//strncpy(int_string, argv[1], INPUT_SIZE);
	
	//printf("String: %s\n", int_string);
	
	//user_src = (int)argv[1] - NUMERIC_OFFSET;
	//user_dst = (int)int_string[2] - NUMERIC_OFFSET;
	
	if(!argv[1] || !argv[2])
	{
		puts("Required usage: ./a.out [source] [destination]\n");
		exit(0);
	}
	
	user_src = atoi(argv[1]);
	user_dst = atoi(argv[2]);
	
	//printf("Source: %i\nDest: %i\n", user_src, user_dst);
	
	//Initializations for first node.
	matrix[user_src][user_src] = 0;	
	iArr_distance[user_src].distance = 0;
	for(index = 0; index < NODE_COUNT; index++)
		iArr_distance[index].stack[0] = user_src;
	visited[user_src][user_src] = 'T';
	
	//path_struct* path_node = NULL;

	//neighbor_struct* neighbor_node = NULL;
	//neighbor_node = malloc(sizeof(neighbor_struct));
	//neighbor_node->i = user_src;
	//TAILQ_INSERT_HEAD(&neighbor_head, neighbor_node, neighbors);

	tail++;
	queue[0] = user_src;

	/*Not worrying about catching invalid user input right now.*/
	while(head != tail)/*Visiting neighbors*/
	{	
		index = 0;	
		source = queue[head];
		queue[head] = -1;
		if(head < MAX_QUEUE) head++;
		else { puts("ERROR: Queue overflow.\n"); exit(1); }
		//if(source == 4)
		//	raise(SIGTRAP);
		//TAILQ_REMOVE(&neighbor_head, neighbor_node, neighbors);
		//source = neighbor_node->i;
		
		//free(neighbor_node);
		//if(source == 4)
		//	raise(SIGTRAP);
		//neighbor_node = NULL;
		for(dest = 0; dest < NODE_COUNT; dest++)
		{
			if((matrix[source][dest] != INF) && (visited[source][dest] == 'F'))
			{	
				step = matrix[source][dest] + iArr_distance[source].distance;
				
				if(step <= iArr_distance[dest].distance)
				{
					//Copy the source predecessor stack to the dest predecessor stack
					
					path_top = iArr_distance[source].index;

					for(index = 0; index <= path_top; index++)
					{
						iArr_distance[dest].stack[index] = iArr_distance[source].stack[index];	
						update_bool = 1;
					}	
					iArr_distance[dest].distance = step;
					path_top++;
					iArr_distance[dest].stack[path_top] = dest;
					iArr_distance[dest].index = path_top;

					up_dest = dest;
					queue[tail] = dest;
					if(tail < MAX_QUEUE) tail++;
					else { puts("ERROR: Queue overflow.\n"); exit(1); }				
				}				
			}		
		}
		visited[source][up_dest] = 'T';

	}
	
	printf("Distances from starting point to every node:\n");
	
	for(index = 0; index < NODE_COUNT; index++)
	{
		if(iArr_distance[index].distance != INF)
			printf("%i -> %i | %i\n", user_src, index, iArr_distance[index].distance);
	}
	
	puts("\nACTUAL ROUTE:");
	curr_tmp = iArr_distance[user_dst].stack;
	path_top = iArr_distance[user_dst].index;
	for(index = 0; index <= path_top; index++)
	{
		//if(curr_tmp[index] != INF)
			printf("%i ", curr_tmp[index]);
		if(index < path_top)
			printf("-> ");
	}
	putchar('\n');

Finish:
	fclose(ptr);

	return 0;
}

/*
Each point in iArr_distance needs to contain a stack of predecessor nodes/distances in addition to the total distance. Every update is not only going to add to the distance. It's also going to involve removing at least one value from the stack. 

Actually, each update for the stack is going to involve copying over the entire predecessor stack. Look at the update for the distance of node 5: It goes from 12 to 3, and the entire stack is replaced. 

I seem to be running into some kind of undefined behavior once source == 4. This seems to happen as soon as it's dequeued. Probably some sort of memory error that's overwriting iArr_distance[4].stack[0]. Hopefully refactoring to an array-based stack (as opposed to depending on this hideous BSD macro) will take care of the problem.
*/




