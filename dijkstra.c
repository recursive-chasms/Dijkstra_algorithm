#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#define NODE_COUNT 7
#define EDGE_COUNT 12
#define INF -1

struct path_struct
{
	int src;
	int dst;
	TAILQ_ENTRY(path_struct) path_vertices;
};
typedef struct path_struct path_struct;

struct neighbor_struct 
{	
	int i;
	TAILQ_ENTRY(neighbor_struct) neighbors;
};
typedef struct neighbor_struct neighbor_struct;


int main(int arc, char * argv [])
{	
	int matrix[NODE_COUNT][NODE_COUNT] = {INF};
	char visited[NODE_COUNT] = {'F'};
	FILE* ptr;
	char int_string[5];
	//char user_string[5];
	//char c;
	
	TAILQ_HEAD(stailhead, neighbor_struct) neighbor_head = TAILQ_HEAD_INITIALIZER(neighbor_head);
	TAILQ_HEAD(stailhead_p, path_struct) path_head = TAILQ_HEAD_INITIALIZER(path_head);
	
	TAILQ_INIT(&neighbor_head);
	TAILQ_INIT(&path_head);
	
	int index = 0;
	int source = 0;
	int dest = 0;
	int weight = 0;
	int step = 0;
	
	int iArr_distance[NODE_COUNT] = {INF};
	//int temp_distance = 0;
	
	int user_src = 0;
	int user_dst = 0;
	
	if(user_src == user_dst)
	{
		printf("ALREADY THERE!\n");
		goto Finish;
	}
	
	ptr = fopen("input.txt", "r");
	
	//fread(int_string, EDGE_COUNT, 1, ptr);
	
	for(index = 0; index < EDGE_COUNT; index++)
	{
		fgets(int_string, 5, ptr);
		
		source = atoi(&int_string[0]) -1;/*adjusting for actual numeric index*/
		dest = atoi(&int_string[2]) -1;
		weight = atoi(&int_string[4]) -1;
		
		matrix[source][dest] = weight;
	}
	index = 0;
	source = 0;
	dest = 0;
	weight = 0;	
	
	//user_string = argc;
	user_src = atoi(&argv[0]) -1;/*adjusting for actual numeric index*/
	user_dst = atoi(&argv[2]) -1;
	
	matrix[user_src][user_src] = 0;	
	iArr_distance[user_src] = 0;
	
	path_struct* path_node = NULL;
	//path_struct* tmp_node = NULL;
	neighbor_struct* neighbor_node = NULL;
	neighbor_node = malloc(sizeof(neighbor_struct));
	neighbor_node->i = user_src;
	TAILQ_INSERT_HEAD(&neighbor_head, neighbor_node, neighbors));
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
		TAILQ_REMOVE_HEAD(&neighbor_head, neighbors);
		source = neighbor_node->i;
		free(neighbor_node);
		neighbor_node = NULL;
		for(dest = 0; dest < NODE_COUNT; dest++)
		{
			if((matrix[source][dest] != INF) && (visited[dest] == 'F'))
			{	
				step = matrix[source][dest] + iArr_distance[source];
				if(step <= iArr_distance[dest])
				{
					iArr_distance[dest] = step;
					
					neighbor_node = malloc(sizeof(neighbor_struct));
					neighbor_node->i = dest;
					TAILQ_INSERT_TAIL(&neighbor_head, neighbor_node, neighbors))
					
					if(iArr_distance[dest] == INF)
					{
						path_node = malloc(sizeof(path_struct));
						TAILQ_INSERT_TAIL(&path_head, path_node, path_vertices);
					}
					else
						path_node = TAILQ_LAST(&path_head);
						
					path_node->src = source;
					path_node->dst = dest;
										
					//enq_main(dest);
				}				
					//visited[dest] = 'T';
			}		
		}
		visited[source] = 'T';
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
		TAILQ_FOREACH(path_node, &path_head, path_vertices)
		{
			printf("node: %i | distance: %i \n", path_node->src, matrix[path_node->src][path_node->dst]);
			TAILQ_REMOVE_HEAD(&path_head, path_vertices);
			free(path_node);
		}	
	}

Finish:

	fclose(ptr);

	return 0;
}





