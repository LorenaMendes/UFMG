#ifndef __SERVERS__
#define __SERVERS__

typedef struct Server{
	int id;
	int color;
	int updated;
	int degree;
	struct Server * next;
} Server;

void Print(Server * vec_servers, int num_servers);
Server * NewServer(int id);
void InsertConection(Server * vec_servers, int s1, int s2);
int FindColors(Server * vec_servers, int num_servers);

#endif