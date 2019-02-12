#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#define NODE_COUNT 7
#define EDGE_COUNT 12
#define INF -1

struct vertex
{
	int src;
	int dst;
};
typedef struct vertex vertex;


int main(char* argc, int argv)
{	
	int matrix[NODE_COUNT][NODE_COUNT] = {INF};
	char visited[NODE_COUNT] = {'F'};
	FILE* ptr;
	char int_string[5];
	//char user_string[5];
	//char c;
	
	int index = 0;
	int source = 0;
	int dest = 0;
	int weight = 0;
	
	int total_distance = 0;
	int temp_distance = 0;
	
	int user_src = 0;
	int user_dst = 0;
	
	if(user_src == user_dst)
		goto Finish;
	
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
	
	matrix[source][source] = 0;
	
	//user_string = argc;
	user_src = atoi(&argc[0]) -1;/*adjusting for actual numeric index*/
	user_dst = atoi(&argc[2]) -1;
	
	enq_main(user_src);
	/*Not worrying about catching invalid user input right now.*/
	//enq_main(source);
	while(queue != NULL)/*Visiting neighbors*/
	{
		source = deq_main();
		//if(source == dest)
		//	break;
			
		temp_distance = INF;
		for(dest = 0; dest < NODE_COUNT; dest++)
		{
			if(matrix[source][dest] != INF)
			{
				if(visited[dest] == 'F')
				{
					//enq_main(dest);
					
					if(matrix[source][dest] <= temp_distance)
					{
						temp_distance = matrix[source][dest];
						vertex.src = source;
						vertex.dst = dest;
						enq_main(dest);
					}				
					//visited[dest] = 'T';
				}
			}		
		}
		visited[source] = 'T';
		total_distance += temp_distance;
		enq_path(vertex);
	}
	

Finish:

	
	
/*
NOTES:

Ought to be able to replicate Dijkstra search much more cleanly using the queue library. The one tricky part may be keeping a queue of pointers to the previous edges in the path for printing the shortest path. 

Just visit all the neighbors in a BFS style thing. enq_mainueue them all, and consult with an array to see whether they've already been visited. A simple check to see which is the shortest path. String together pointers of shortest paths simultaneously. 


*/	



	
	
	fclose(ptr);

	return 0;
}



