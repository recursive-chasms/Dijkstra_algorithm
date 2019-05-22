#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <signal.h>

#define NODE_COUNT 8  /*<-Increased to represent actual graph*/
#define EDGE_COUNT 12
#define INF 0x7FFFFFFF
#define MAX_NODES 20

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
	int stack[MAX_NODES];
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
	char int_string[10];
	
	TAILQ_HEAD(stailhead, neighbor_struct) neighbor_head = TAILQ_HEAD_INITIALIZER(neighbor_head);
	TAILQ_HEAD(stailhead_p, path_struct) path_head = TAILQ_HEAD_INITIALIZER(path_head);
	
	TAILQ_INIT(&neighbor_head);
	TAILQ_INIT(&path_head);
	
	int index = 0;
	int bindex = 0;
	int stacktop = 0;
	int previous = 0;
	int source = 0;
	int dest = 0;
	int up_dest = 0;

	int weight = 0;
	int step = 0;
	char update_bool = 'F';
	
	predecessor iArr_distance[NODE_COUNT];
	//predecessor prev_tmp;
	int* curr_tmp;
	
	for(;index < NODE_COUNT; index++)
	{
		iArr_distance[index].distance = INF;
		iArr_distance[index].index = 0;
		for(bindex = 0; bindex < MAX_NODES; bindex++)
			iArr_distance[index].stack[bindex] = 0;
			
		for(bindex = 0; bindex < NODE_COUNT; bindex++)
		{
			matrix[index][bindex] = INF;
			visited[index][bindex] = 'F';
		}
	}
	
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
	
	
	user_src = 1;//atoi(argv[0]) -1;/*adjusting for actual numeric index*/
	user_dst = 6;//atoi(argv[2]) -1;
	
	//Initializations for first node.
	matrix[user_src][user_src] = 0;	
	iArr_distance[user_src].distance = 0;
	for(index = 0; index < MAX_NODES; index++)
		iArr_distance[index].stack[0] = user_src;
	visited[user_src][user_src] = 'T';
	
	path_struct* path_node = NULL;

	neighbor_struct* neighbor_node = NULL;
	neighbor_node = malloc(sizeof(neighbor_struct));
	neighbor_node->i = user_src;
	TAILQ_INSERT_HEAD(&neighbor_head, neighbor_node, neighbors);

	/*Not worrying about catching invalid user input right now.*/
	while(!TAILQ_EMPTY(&neighbor_head))/*Visiting neighbors*/
	{	
		index = 0;	
		neighbor_node = TAILQ_FIRST(&neighbor_head);
		if(source == 4)
			raise(SIGTRAP);
		TAILQ_REMOVE(&neighbor_head, neighbor_node, neighbors);
		source = neighbor_node->i;
		
		free(neighbor_node);
		if(source == 4)
			raise(SIGTRAP);
		neighbor_node = NULL;
		for(dest = 0; dest < NODE_COUNT; dest++)
		{
			if((matrix[source][dest] != INF) && (visited[source][dest] == 'F'))
			{	
				step = matrix[source][dest] + iArr_distance[source].distance;
				//if(iArr_distance[source].stack[0] == 4)
				//	raise(SIGTRAP);
				
				if(step <= iArr_distance[dest].distance)
				{
					//Copy the source predecessor stack to the dest predecessor stack
					
					//if(source == 4)
					//	raise(SIGTRAP);
					
					stacktop = iArr_distance[source].index;
					for(index = 0; index < stacktop; index++)
						iArr_distance[dest].stack[index] = iArr_distance[source].stack[index];		
					
					update_bool = 'T';
					neighbor_node = malloc(sizeof(neighbor_struct));
					neighbor_node->i = up_dest = dest;
					TAILQ_INSERT_TAIL(&neighbor_head, neighbor_node, neighbors);
					
					iArr_distance[dest].distance = step;
					iArr_distance[dest].stack[stacktop] = dest;
					stacktop++;
					iArr_distance[dest].index = stacktop;					
				}				
			}		
		}
		visited[source][up_dest] = 'T';
		/*
		if(update_bool == 'T')
		{
			neighbor_node = TAILQ_FIRST(&neighbor_head);

			path_node = malloc(sizeof(path_struct));
			path_node->src = source;
			path_node->dst = neighbor_node->i;

			TAILQ_INSERT_TAIL(&path_head, path_node, path_vertices);
			
			neighbor_node = NULL;
			path_node = NULL;
			update_bool = 'F';
		}
		*/
	}
	
	printf("Distances from starting point to every node:\n");
	
	for(index = 0; index < NODE_COUNT; index++)
		printf("%i -> %i | %i\n", user_src, index, iArr_distance[index].distance);
	
	/*
	printf("ROUTE--Start to finish: \n");
	
	path_node = TAILQ_FIRST(&path_head);
	
	while(!TAILQ_EMPTY(&path_head))
	{
		TAILQ_FOREACH_REVERSE(path_node, &path_head, stailhead_p, path_vertices)
		{
			printf("%i -> %i \n", path_node->src, path_node->dst);
			TAILQ_REMOVE(&path_head, path_node, path_vertices);
			free(path_node);
		}	
	}
	*/
	
	puts("\nACTUAL ROUTE:");
	curr_tmp = iArr_distance[user_dst].stack;
	stacktop = iArr_distance[user_dst].index;
	for(index = 0; index < stacktop; index++)
		printf("%i -> ", curr_tmp[index]);
	putchar('\n');

Finish:
	fclose(ptr);

	return 0;
}

/*
Note: Actual route from 1 to 6:

1 -> 4 -> 7 -> 6

Supposed route: 
7 -> 6 
3 -> 5 
4 -> 5 
2 -> 4 
1 -> 2 

The nodes of the actual route exist in the output. Need to find a means of eliminating the redundant ones. Probably won't be very efficient. May help to refactor the linked lists into arrays. Maybe just removing the macros will be better, though, since it'll be easier to remove nodes. Or maybe just don't print the indices that have been blanked out. In any case, it'll probably necessitate iterating through the whole path at every turn.

Once shortest distances are finalized, just choose the shortest path at each connected node. Simple. (I think.) This is something that's done after the initial sequence--not during.

Each point in iArr_distance needs to contain a stack of predecessor nodes/distances in addition to the total distance. Every update is not only going to add to the distance. It's also going to involve removing at least one value from the stack. 

Actually, each update for the stack is going to involve copying over the entire predecessor stack. Look at the update for the distance of node 5: It goes from 12 to 3, and the entire stack is replaced. 

I seem to be running into some kind of undefined behavior once source == 4. This seems to happen as soon as it's dequeued. Probably some sort of memory error that's overwriting iArr_distance[4].stack[0]. Hopefully refactoring to an array-based stack (as opposed to depending on this hideous BSD macro) will take care of the problem.
*/




