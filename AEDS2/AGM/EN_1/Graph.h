//struct Vertex, that represents a vertex of a graph
typedef struct Vertex{
	int index;
	int flag;
	struct Vertex * neighbor_l;
	struct Vertex * neighbor_r;
	int neighborhood_weight;
}Vertex;

//struct Edge, that represents an Edge of a graph
typedef struct Edge{
	Vertex vertex1;
	Vertex vertex2;
	int weight;
}Edge;

//Graph's functions

//sort an Edge vector by weight
void SortByWeight(Edge * edges, int size);
//creates an adjacence list
Vertex * CreateAdjacenceList(int size);
//inserts a new vertex two times (a in b, b in a)
void Insert(Vertex * list, Edge edges);
//inserting vertex2 in vertex1
void Insertion(Vertex * list, Vertex vertex1, Vertex vertex2, int weight);
//Function to find out if two vertices belong to the same tree or not
int Find(Vertex * list, Vertex vertex1, Vertex vertex2);