#include <stdio.h>


#define INFINITY 999
#define INVALID_COOR -1
#define DEPTH 5
#define BREADTH 5
#define MAX_NODES 25

typedef struct
{
	int predecessor;
	int distance;
} vertex_t;

typedef struct
{
	vertex_t array[MAX_NODES]; 
	int head;
	int tail;
} queue_t;

void init_vertices(vertex_t [][BREADTH]);
void init_queue(queue_t *);
void enqueue(queue_t *, vertex_t);
node_t dequeue(queue_t *);
void display_queue(queue_t *);


int main(void)
{
	/* vertex_t vertex0, vertex1, vertex2, vertex3, vertex4,
			 vertex5, vertex6, vertex7, vertex8, vertex9,
			 vertex10, vertex11, vertex12, vertex13, vertex14,
			 vertex15, vertex16, vertex17, vertex18, vertex19,
			 vertex20, vertex21, vertex22, vertex23, vertex24;
	 */		 
	vertex_t empty_vertex;
	
	empty_vertex.predecessor = INVALID_COOR;
	empty_vertex.distance = INVALID_COOR;
	
	// set vertices
	vertex_t vertices[DEPTH][BREADTH];
	
	for (int i = 0; i < DEPTH; i++)
	{
		for (int j = 0; j < BREADTH; j++)
		{
			vertex_t vertex;
			vertices[i][j] = vertex; 
		}
	}
		
	// initialiseer de vertices
	init_vertices(vertices);
	

	vertex_t graph[25][4] =
	{
		{ vertices[1], vertices[5], empty_vertex, empty_vertex }, 	// 0
		{ vertices[0], vertices[2], vertices[6], empty_vertex },  	// 1
		{ vertices[1], vertices[3], vertices[7], empty_vertex }, 	// 2
		{ vertices[2], vertices[4], vertices[8], empty_vertex }, 	// 3
		{ vertices[3], vertices[9], empty_vertex, empty_vertex }, 	// 4
		
		{ vertices[0], vertices[6], vertices[10], empty_vertex }, 	// 5
		{ vertices[1], vertices[5], vertices[7], vertices[11] }, 	// 6
		{ vertices[2], vertices[6], vertices[8], vertices[12] }, 	// 7
		{ vertices[3], vertices[7], vertices[9], vertices[13] }, 	// 8
		{ vertices[4], vertices[8], vertices[14], empty_vertex }, 	// 9
		
		{ vertices[5], vertices[11], vertices[15], empty_vertex },  // 10	
		{ vertices[6], vertices[10], vertices[12], vertices[16] },  // 11
		{ vertices[7], vertices[11], vertices[13], vertices[17] },	// 12
		{ vertices[8], vertices[12], vertices[14], vertices[18] },  // 13
		{ vertices[9], vertices[13], vertices[19], empty_vertex },  // 14
		
		{ vertices[10], vertices[16], vertices[20], empty_vertex }, // 15
		{ vertices[11], vertices[15], vertices[17], vertices[21] }, // 16
		{ vertices[12], vertices[16], vertices[18], vertices[22] }, // 17
		{ vertices[13], vertices[17], vertices[19], vertices[23] }, // 18
		{ vertices[14], vertices[18], vertices[24], empty_vertex }, // 19
		
		{ vertices[15], vertices[21], empty_vertex, empty_vertex }, // 20		
		{ vertices[16], vertices[20], vertices[22], empty_vertex }, // 21
		{ vertices[17], vertices[21], vertices[23], empty_vertex }, // 22
		{ vertices[18], vertices[22], vertices[24], empty_vertex }, // 23
		{ vertices[19], vertices[23], empty_vertex, empty_vertex }  // 24
	};
	
	
	return 0;
}

void init_vertices(vertex_t vertices[][BREADTH])
{
	int coor = 0;
	
	for (int i = 0; i < DEPTH; i ++)
	{
		for(int j = 0; j < BREADTH; j++)
		{
			vertices[i][j].predecessor = 0; // 0
			vertices[i][j].distance = INFINITY;
		}
	}
}

