/**
 * @file    pathfinding.c
 * @author  Urwien George
 * @date    31-03-2017
 * @brief   Deze file is verantwoordelijk voor het vinden van het kortste pad op de map: 
 *          https://cursussen.sharenode.hu.nl/fnt/51/TICT-V1GP-15/Studiemateriaal/Groepsproject%20TI/parcours2.jpg
 * 
 *          Het programma maakt gebruik van een 2d-array die een abstractie voorstelt van de map. Deze array wordt gevuld met node
 *          structs.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAPH_BREADTH 5
#define GRAPH_DEPTH 5
#define MAX_NUM_EDGES 4
#define NUM_NODES 25
#define NONE -1
#define INFINITY -2

typedef struct
{
    int distance;
    int edges[MAX_NUM_EDGES];
    bool is_visited;
} node_t;

typedef struct 
{
    node_t *nodes[NUM_NODES];
    int head;
    int tail;
} queue_t;

void init_node(node_t *);

void init_queue(queue_t *);
void enqueue(queue_t *, node_t *);
node_t *dequeue(queue_t *);
void display_queue(queue_t *);
void free_queue(queue_t *);

int main(void)
{
    // creeer de queue
    queue_t node_queue;
    
    init_queue(&node_queue);
    
    // creeer de nodes
    for (int i = 0; i < NUM_NODES; i++)
    {
        node_t *node = malloc(sizeof(node_t));
        
        // initialiseer node
        init_node(node);
        
        enqueue(&node_queue, node);
    }
        
    // toon de queue
    display_queue(&node_queue);
    
    // dealloceer het geheugen
    free_queue(&node_queue);
    
    return 0;
}

void init_node(node_t *node)
{
    node->distance = INFINITY;
    
    for (int i = 0; i < MAX_NUM_EDGES; i++)
        node->edges[i] = NONE; 
    
    node->is_visited = false;
}

void init_queue(queue_t *queue)
{
    queue->head = NONE;
    queue->tail = NONE;
}

void enqueue(queue_t *queue, node_t *node)
{
    // controleer if de queue niet vol is
    if (queue->tail < (NUM_NODES - 1))
    {
        // plaatst de eerste node vooraan
        if (queue->head == NONE)
            queue->head++;
            
        // plaatst de andere nodes achteraan en verhoog de tail
        queue->nodes[queue->tail++] = node;
    }
}

node_t *dequeue(queue_t *queue)
{
    // controleer of de queue niet leeg is
    if (queue->head > NONE)
    {
        node_t *node = queue->nodes[queue->head++];
        return node;
    }
    
    // null pointer als de queue leeg is
    return NULL;
}

void display_queue(queue_t *queue)
{
    for (int i = queue->head; i <= queue->tail; i++)
    {
        printf("(%d)", queue->nodes[i]->distance);
        
        if (i % GRAPH_BREADTH == 0)
            putchar('\n');
    }
}

void free_queue(queue_t *queue)
{
    for (int i = 0; i < NUM_NODES; i++)
        free(queue->nodes[i]);
}