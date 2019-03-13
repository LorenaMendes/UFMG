#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

//sorts an Edge vector by it's weight
void SortByWeight(Edge * edges, int size){
 	int i, j;

 	//returns if the vector's size is zero
 	if (size == 0) return;
 	
 	Edge aux;
 
 	//changes positions for each unsorted item
 	for (i = 1; i < size; i++)
 	{
 		aux = edges[i];
 		for (j = i - 1; j >= 0 && aux.weight < edges[j].weight; j--)
 		{
 			edges[j + 1] = edges[j];
 		}
 		edges[j + 1] = aux;
 	}
}

//creates an adjacence list
Vertex * CreateAdjacenceList(int size){
	int i;

	Vertex * list = malloc(size * sizeof(Vertex));

	//sets a default value for each item
	for (i = 0; i < size; ++i)
	{
		list[i].index = i;
		list[i].flag = 0;
		list[i].neighbor_l = NULL;
		list[i].neighbor_r = NULL;
	}

	return list;
}

//inserts a new vertex two times (a in b, b in a)
void Insert(Vertex * list, Edge edges){
	Insertion(list, edges.vertex1, edges.vertex2, edges.weight);
	Insertion(list, edges.vertex2, edges.vertex1, edges.weight);
}

//inserting vertex2 in vertex1
void Insertion(Vertex * list, Vertex vertex1, Vertex vertex2, int weight){
	int v1 = vertex1.index;
	int v2 = vertex2.index;

	//creates auxiliar vertices
	Vertex * auxA = list[v1].neighbor_r;
	Vertex * auxB = &list[v1];

	//creates a new vertex with vertex2's values ans neighbor nulls
	Vertex * new_vertex = malloc(sizeof(Vertex));
	new_vertex->index = vertex2.index;
	new_vertex->neighbor_r = NULL;
	new_vertex->neighbor_l = NULL;
	new_vertex->neighborhood_weight = weight;

	//inserts the new vertex directly in the right neighbor if there ins't a right neighbor 
	if(!list[v1].neighbor_r)
	{
		list[v1].neighbor_r = new_vertex;
		new_vertex->neighbor_l = &list[v1];
		return;
	} 

	//if there are already right neighbors, searchs the good position to insert (it's sorted)
	while(auxA)
	{
		if(auxA->index > vertex2.index)
		{
			auxB->neighbor_r = new_vertex;
			new_vertex->neighbor_l = auxB;
			new_vertex->neighbor_r = auxA;
			auxA->neighbor_l = new_vertex;
			return;
		} 

		//looks to the next neighbor
		else
		{
			auxA = auxA->neighbor_r;
			auxB = auxB->neighbor_r;
		}
	}

	//if arrives to the end (vertex2's index is the biggest one)
	auxB->neighbor_r = new_vertex;
	new_vertex->neighbor_l = auxB;
}

//Function to find out if two vertices belong to the same tree or not
int Find(Vertex * list, Vertex vertex1, Vertex vertex2){
	
	//creares a value to return from recursive function
	int value = 0;

	//returns from recursion if the vertex was already serched
	if(list[vertex1.index].flag){
		return 0;
	}

	//makes that vertex be already searched
	else list[vertex1.index].flag = 1;	
	
	//creates auxiliar vertices
	Vertex * new_vertex = list[vertex1.index].neighbor_r;
	Vertex * auxiliar = new_vertex;
	
	while(new_vertex)
	{
		//returns 1 if it finds out if the trees are the same
		if(new_vertex->index == vertex2.index)
		{
			return 1;
		}
		//otherwise, it searches in the right neighbor
		else
		{
			new_vertex = new_vertex->neighbor_r;
		}
	}

	while(auxiliar)
	{
		//this case looks for the correspondent tree through each right neighbor
		if(value = Find(list, list[auxiliar->index], vertex2) == 1)
		{
			//returns 1 if the trees are the same (calls recursively)
			return value;
		}
		//otherwise, searches in the right neighbor
		else auxiliar = auxiliar->neighbor_r; 
	}
	return value;
}