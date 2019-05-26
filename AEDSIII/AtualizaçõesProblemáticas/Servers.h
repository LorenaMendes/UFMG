#ifndef __SERVERS__
#define __SERVERS__

typedef struct Server{
	int id;
	int color;
	int updated;
	int pos;
	int degree;
	struct Server * next;
} Server;

Server * NewServer(int id);
void InsertConection(Server * vec_servers, int s1, int s2);
void Print(Server * vec_servers, int num_servers);
int FindColors(Server * vec_servers, int num_servers);
int SearchVertex(Server * vec_servers, int num_servers, int id);
int SearchColor(Server * vec_servers, int num_servers, int pos);
void ChangeColor(Server * vec_servers, int pos, int num_servers, int color);
int SearchVertex(Server * vec_servers, int num_servers, int id);
void InsertPos(Server * vec_servers, int num_servers);

#endif