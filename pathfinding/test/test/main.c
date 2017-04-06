/**
 * @file    pathfinding.c
 * @author  Urwien George
 * @date    31-03-2017
 * @brief   Deze file is verantwoordelijk voor het vinden van het kortste pad op de map: 
 *          https://cursussen.sharenode.hu.nl/fnt/51/TICT-V1GP-15/Studiemateriaal/Groepsproject%20TI/parcours2.jpg
 * 
 */

#include <stdbool.h>
#include <stdio.h>

/** Het aantal nodes in de breedte (horizontaal) van de map. */
#define GRAPH_BREADTH 5

/** Het aantal nodes in de diepte (verticaal) van de map. */
#define GRAPH_DEPTH 5

/** Het maximale aantal verbindingen dat een node kan hebben. */
#define MAX_NUM_EDGES 4

/** Het totale aantal nodes. */
#define NUM_NODES 25

/** Deze define wordt gebruikt om aan tegeven dat een verbinding niet bestaat. */
#define NONE -1

/** Dit is de initieele afstand tussen alle nodes voordat het pad algoritme wertk. */
#define INFINITY -2

/**
 * @struct node_t
 * @brief Deze struct stelt een node/vertex voor op map.
 * @var node_t::distance
 * De member distance stelt de afstand van de node voor tenopzichte van de rootnode (startpunt).
 * @var node_t::edges
 * Een node heeft maximaal MAX_NUM_EDGES edges (verbindingen) met andere nodes.
 * @var node_t::is_visited
 * Een boolean flag die aangeeft of deze node al eerder is voorgekomen in het pad zoek algoritme.
 */
typedef struct
{
    int distance;
    int edges[MAX_NUM_EDGES];
    bool is_visited;
} node_t;

/**
 * @struct queue_t
 * @brief De queue (FIFO) wordt gebruikt voor het pad zoek algoritme. De queue bevat alle nodes op de map.
 * @var queue_t::nodes
 * De array met alle nodes op de map.
 * @var queue_t::head
 * Het begin van de queue.
 * @var queue_t::tail
 * Het einde van de queue.
 */
typedef struct 
{
    node_t nodes[NUM_NODES];
    int head;
    int tail;
} queue_t;

// functie prototypen
void init_node(node_t *);
void init_queue(queue_t *);
void enqueue(queue_t *, node_t);
node_t dequeue(queue_t *);
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
        node_t node;
        
        // initialiseer node
        init_node(&node);
        
        enqueue(&node_queue, node);
    }
        
    // toon de queue
    display_queue(&node_queue);
    
    return 0;
}

/**
 * @brief Deze methode geeft een node zijn initieele waarden (een afstand van oneindig, geen verbindingen en nog niet bezocht). 
 * @param node 
 * De node die geinitialiseerd moet worden.
 */
void init_node(node_t *node)
{
    node->distance = INFINITY;  // de afstand tussen nodes is in eerste instantie nog onbekend.
    
    for (int i = 0; i < MAX_NUM_EDGES; i++)
        node->edges[i] = NONE;  // alle nodes hebben in het begin nog geen verbindingen (edges). 
    
    node->is_visited = false;   // node is nog niet bezocht door algoritme.
}

/**
 * @brief Initialiseert de queue voor de nodes.
 * @param queue
 * De queue die geinitialiseerd moet worden.
 */
void init_queue(queue_t *queue)
{
    // de queue is in eerste instantie leeg.
    queue->head = NONE; 
    queue->tail = NONE;
}

/**
 * @brief Voegt een node aan de queue toe. De node wordt achteraan (tail) de queue toegevoegd.
 * @param queue 
 * De queue waarde de node aan toegevoegd moet worden. Dit stelt de map voor. 
 * @param node
 * Een node (punt op de map) die aan de queue wordt toegevoegd.
 */
void enqueue(queue_t *queue, node_t node)
{
    // controleer if de queue niet vol is
    if (queue->tail < (NUM_NODES + 1))
    {
        // plaatst de eerste node vooraan
        if (queue->head == NONE)
            queue->head++;
            
        // plaatst de andere nodes achteraan en verhoog de tail
        queue->nodes[++(queue->tail)] = node;
    }
}

/**
 * @brief Haalt de node vooraan (head) de queue van de queue af geeft deze terug.
 * @param queue
 * De queue waar de node vandaan wordt gehaald.
 * @return 
 * De node achteraan de queue.
 */
node_t dequeue(queue_t *queue)
{
    // controleer of de queue niet leeg is
    //if (queue->head > NONE)
    return queue->nodes[queue->head++];
}

/**
 * @brief Toont de inhoud van de queue.
 * @param queue
 * De queue waarvan de inhoud getoont moet worden.
 */
void display_queue(queue_t *queue)
{
    int test_display_var = 0;
    
    for (int i = queue->head; i <= queue->tail; i++)
    {
        printf("(%d)", queue->nodes[i].distance);
        
        // voor de output
        test_display_var++;
        
        if (test_display_var == 5)
        {
            putchar('\n');
            test_display_var = 0;
        }
    }
}