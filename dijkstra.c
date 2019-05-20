#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <signal.h>

#define NODE_COUNT 8  /*<-Increased to represent actual graph*/
#define EDGE_COUNT 12
#define INF 0x7FFFFFFF

struct path_struct
{
	int src;
	int dst;
	//int distance;
	TAILQ_ENTRY(path_struct) path_vertices;
};
typedef struct path_struct path_struct;

struct neighbor_struct 
{	
	int i;
	//int distance;
	TAILQ_ENTRY(neighbor_struct) neighbors;
};
typedef struct neighbor_struct neighbor_struct;


int main(int arc, char * argv [])
{	
	int matrix[NODE_COUNT][NODE_COUNT];
	char visited[NODE_COUNT][NODE_COUNT];// = {'F'};
	FILE* ptr;
	char int_string[10];
	//char user_string[5];
	//char c;
	
	TAILQ_HEAD(stailhead, neighbor_struct) neighbor_head = TAILQ_HEAD_INITIALIZER(neighbor_head);
	TAILQ_HEAD(stailhead_p, path_struct) path_head = TAILQ_HEAD_INITIALIZER(path_head);
	
	TAILQ_INIT(&neighbor_head);
	TAILQ_INIT(&path_head);
	
	int index = 0;
	int bindex = 0;
	int source = 0;
	int dest = 0;
	int up_dest = 0;
	//int final_dest = 0;
	//int final_distance = 0;
	int weight = 0;
	int step = 0;
	char update_bool = 'F';
	
	int iArr_distance[NODE_COUNT];
	
	for(;index < NODE_COUNT; index++)
	{
		iArr_distance[index] = INF;	
		//visited[index] = 'F';
		for(bindex = 0; bindex < NODE_COUNT; bindex++)
		{
			matrix[index][bindex] = INF;
			visited[index][bindex] = 'F';
		}
	}
	
	
	//int temp_distance = 0;
	
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
	
	//fread(int_string, EDGE_COUNT, 1, ptr);
	
	for(index = 0; index <= EDGE_COUNT; index++)
	{
		//if(index == 11)
		//	raise(SIGTRAP);
	
		fgets(int_string, 8, ptr);
		
		source = atoi(&int_string[0]);/* -1;/*adjusting for actual numeric index*/
		dest = atoi(&int_string[2]);// -1;
		weight = atoi(&int_string[4]);
		
		matrix[source][dest] = weight;
	}
	index = 0;
	source = 0;
	dest = 0;
	weight = 0;	
	
	//user_string = argc;
	user_src = 1;//atoi(argv[0]) -1;/*adjusting for actual numeric index*/
	user_dst = 6;//atoi(argv[2]) -1;
	
	matrix[user_src][user_src] = 0;	
	iArr_distance[user_src] = 0;
	visited[user_src][user_src] = 'T';
	
	path_struct* path_node = NULL;
	//path_struct* tmp_node = NULL;
	neighbor_struct* neighbor_node = NULL;
	neighbor_node = malloc(sizeof(neighbor_struct));
	neighbor_node->i = user_src;
	TAILQ_INSERT_HEAD(&neighbor_head, neighbor_node, neighbors);
	//enq_main(user_src);
	/*Not worrying about catching invalid user input right now.*/
	//enq_main(source);
	while(!TAILQ_EMPTY(&neighbor_head))/*Visiting neighbors*/
	{
		//source = deq_main();
		//if(source == dest)
		//	break;
			
		//temp_distance = INF;
		
		neighbor_node = TAILQ_FIRST(&neighbor_head);
		TAILQ_REMOVE(&neighbor_head, neighbor_node, neighbors);
		source = neighbor_node->i;
		free(neighbor_node);
		neighbor_node = NULL;
		for(dest = 0; dest < NODE_COUNT; dest++)
		{
			//if(source == 7 && dest == 6)
			//		raise(SIGTRAP);
			if((matrix[source][dest] != INF) && (visited[source][dest] == 'F'))
			{	
				step = matrix[source][dest] + iArr_distance[source];
				//update_bool = 'T';
				if(step <= iArr_distance[dest])
				{
					update_bool = 'T';
					neighbor_node = malloc(sizeof(neighbor_struct));
					neighbor_node->i = up_dest = dest;
					//neighbor_node->distance = step;
					TAILQ_INSERT_TAIL(&neighbor_head, neighbor_node, neighbors);
					
					//final_dest = dest;
					//final_distance = step;
					
					/*
					if(iArr_distance[dest] == INF || iArr_distance[dest] == 0)
					{
						//path_node = malloc(sizeof(path_struct));
						path_node->src = source;
						path_node->dst = dest;
						TAILQ_INSERT_TAIL(&path_head, path_node, path_vertices);
					}
					else
					{
						path_node = TAILQ_LAST(&path_head, stailhead_p);
						path_node->src = source;
						path_node->dst = dest;		
					}
					*/
					iArr_distance[dest] = step;					
					//enq_main(dest);
				}				
					//visited[dest] = 'T';
			}		
		}
		visited[source][up_dest] = 'T';
		if(update_bool == 'T')
		{
			neighbor_node = TAILQ_FIRST(&neighbor_head);
			//if(matrix[source][neighbor_node->i] != INF)
			//{
				path_node = malloc(sizeof(path_struct));
				path_node->src = source;
				path_node->dst = neighbor_node->i;
				//path_node->distance = neighbor_node->distance;
				TAILQ_INSERT_TAIL(&path_head, path_node, path_vertices);
			//}
			
			neighbor_node = NULL;
			path_node = NULL;
			update_bool = 'F';
		}
		//iArr_distance[vertex.dst] += temp_distance;
		//enq_path(vertex);
	}
	
	printf("Distances from starting point to every node:\n");
	
	for(index = 0; index < NODE_COUNT; index++)
		printf("%i -> %i : %i\n", user_src, index, iArr_distance[index]);
	
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

Finish:
	fclose(ptr);

	return 0;
}





