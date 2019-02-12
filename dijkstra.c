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
	int step = 0;
	
	int iArr_distance[NODE_COUNT] = {INF};
	//int temp_distance = 0;
	
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
	
	
	
	//user_string = argc;
	user_src = atoi(&argc[0]) -1;/*adjusting for actual numeric index*/
	user_dst = atoi(&argc[2]) -1;
	
	matrix[user_src][user_src] = 0;	
	iArr_distance[user_src] = 0;
	
	enq_main(user_src);
	/*Not worrying about catching invalid user input right now.*/
	//enq_main(source);
	while(queue != NULL)/*Visiting neighbors*/
	{
		source = deq_main();
		//if(source == dest)
		//	break;
			
		//temp_distance = INF;
		for(dest = 0; dest < NODE_COUNT; dest++)
		{
			if((matrix[source][dest] != INF) && (visited[dest] == 'F'))
			{	
				step = matrix[source][dest] + iArr_distance[source];
				if(step <= iArr_distance[dest])
				{
					iArr_distance[dest] = step;
					vertex.src = source;
					vertex.dst = dest;
					enq_main(dest);
				}				
					//visited[dest] = 'T';
			}		
		}
		visited[source] = 'T';
		//iArr_distance[vertex.dst] += temp_distance;
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



