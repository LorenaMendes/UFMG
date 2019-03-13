#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char const *argv[])
{
	int i, j = 0;
	int v, e, v1, v2, w;

	//reads argv's inputs
	const char * input_txt = argv[1];
	const char * output_txt = argv[2];

	//creates and opens a file on read mode
	FILE * input_ = fopen(input_txt, "r");
	fscanf(input_, "%d %d", &v, &e);

	//allocs an Edge object with 'e' positions
	Edge * edges = malloc(e * sizeof(Edge));

	//reads each value from the file and puts in a space
	for (i = 0; i < e; i++)
	{
		fscanf(input_, "%d %d %d", &v1, &v2, &w);
		edges[i].vertex1.index = v1;
		edges[i].vertex2.index = v2;
		edges[i].weight = w;
	}


	//closes the file
	fclose(input_);

	//sorts edges by weight
	SortByWeight(edges, e);

	//crates an adjacency list with the edges
	Vertex * list = CreateAdjacenceList(v);

	//find out if the trees aren't the same
	for (i = 0; i < e; ++i)
	{
		if(!Find(list, edges[i].vertex1, edges[i].vertex2))
		{
			//if so, inserts a new vertex
			Insert(list, edges[i]);
			j++;
			//resets each flag 
			for (int i = 0; i < v; ++i)
			{
				list[i].flag = 0;
			}
		}
		//if not, doens't insert
		else
		{
			//resets each flag
			for (int i = 0; i < v; ++i)
			{
				list[i].flag = 0;
			}
		}
	}

	//opens an output file
	FILE * output_ = fopen(output_txt, "w");
	
	//writes vertex's and edge's numbers in the first file's row
	fprintf(output_, "%d %d\n", v, j);
	
	//creates a vector that contais each edge
	Edge * output_vector = malloc(j * sizeof(Edge));
	
	//veriable that counts neighbor's
	w = 0;
	
	for (int i = 0; i < j; ++i)
	{
		//creates an auxiliar
		Vertex * aux = list[i].neighbor_r;
		//sets vertex's flag
		list[i].flag = 1;
		
		//while there's a neighbor, inserts it in the vector
		while(aux)
		{
			//only if the flag isn't high
			if(!list[aux->index].flag)
			{
				//defines it's wight, vertex1 and vertex2
				output_vector[w].weight = aux->neighborhood_weight;
				output_vector[w].vertex1.index = i;
				output_vector[w].vertex2.index = aux->index;
				w++;
			}
			//looks to the other neighbor
			aux = aux->neighbor_r;
		}
	}

	//writes the edges in the output file (vertex1, vertex2 and weight)
	for (i = 0; i < j; ++i)
	{
		fprintf(output_, "%d %d %d\n", output_vector[i].vertex1.index, output_vector[i].vertex2.index, output_vector[i].weight);
	}

	//closes output file
	fclose(output_);
	
	//free allocated vectors
	free(edges);
	free(output_vector);

	return 0;
}