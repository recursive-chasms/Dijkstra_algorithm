#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#define NODE_COUNT 7
#define EDGE_COUNT 12

int main()
{	
	int matrix[NODE_COUNT][NODE_COUNT];
	FILE* ptr;
	char int_string[5];
	char c;
	
	int index = 0;
	int source = 0;
	int dest = 0;
	int weight = 0;
	
	ptr = fopen("input.txt", "r");
	
	//fread(int_string, EDGE_COUNT, 1, ptr);
	
	for(index = 0; index < EDGE_COUNT; index++)
	{
		fgets(int_string, 5, ptr);
		
		source = atoi(&int_string[0]);
		dest = atoi(&int_string[2]);
		weight = atoi(&int_string[4]);
		
		matrix[source][dest] = weight;
	}
/*
NOTES:

Ought to be able to replicate Dijkstra search much more cleanly using the queue library. The one tricky part may be keeping a queue of pointers to the previous edges in the path for printing the shortest path. 

Just visit all the neighbors in a BFS style thing. Enqueue them all, and consult with an array to see whether they've already been visited. A simple check to see which is the shortest path. String together pointers of shortest paths simultaneously. 


*/	



	
	
	fclose(ptr);

	return 0;
}



