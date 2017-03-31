/**
 * @file    pathfinding.c
 * @author  Urwien George
 * @date    31-03-2017
 * @brief   Deze file is verantwoordelijk voor het vinden van het kortste pad op de map: 
 *          https://cursussen.sharepoint.hu.nl/fnt/51/TICT-V1GP-15/Studiemateriaal/Groepsproject%20TI/parcours2.jpg
 * 
 *          Het programma maakt gebruik van een 2d-array die een abstractie voorstelt van de map. Deze array wordt gevuld met point
 *          structs die een x en y coordinaat hebben. De map wordt gezien als een grafiek met het begin van de x en y assen
 *          rechtsboven in de hoek (0, 0). Dit is tevens het start punt van de robot.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief De breedte van de map. Deze is altijd vier.
 */
#define GRID_ROWS 4

/**
 * @brief De hoogte van de map. Deze is altijd vier.
 */
#define GRID_COLUMNS 4

/**
 * @brief De start x-coordinaat van de robot.
 */
#define START_X 0

/**
 * @brief De start y-coordinaat van de robot.
 */
#define START_Y 0

/**
 * @brief Een obstakel op de map.
 */
#define OBSTACLE -1

/**
 * @brief   De points die op de map zitten. Elke point zit op een kruispunt en
 *          heeft een x en y coordinaat. Een waarde van OBSTACLE (-1) voor de x en y
 *          coordinaten geven aan dat er een obstakel aanwezig is op dat kruispunt.
 * @param x De x-ccordinaat van de point.
 * @param y De y-coordinaat van de point. 
 */
typedef struct
{
	int x, y;
} coor_t;

/**
 * @brief               De abstractie van robot. 
 * @param current_pos   Dit is de huidige positie van de robot. Deze wordt gebruikt om de positie op de map
 *                      van de robot te bepalen.
 */
typedef struct 
{
    coor_t *current_pos;
} robot_t;

// functie prototypen
coor_t *create_point(int, int);
void delete_pointer(coor_t *);
void show_points(coor_t *[][GRID_COLUMNS]);
void init_point_map(coor_t *[][GRID_COLUMNS]);
void delete_point_map(coor_t *[][GRID_COLUMNS]);
void place_obstacle(coor_t *);

robot_t *create_robot(void);
void init_robot(robot_t *);
void destroy_robot(robot_t *);
void update_position(robot_t *, coor_t*);

// deze main method komt niet in de ROBOTC code. Hoeft niet gedocumenteerd worden.
int main(void)
{
    // De robot op de map
    robot_t *robot = create_robot();
    
    // De map waar de robot op rijdt
	coor_t *map[GRID_ROWS][GRID_COLUMNS];
    
    // initialiseer de verschillende punten op de map met hun standaard waarden
	init_point_map(map);

    // toon de map
    show_points(map);

    // plaats een obstakel op punt (2, 3)
    place_obstacle(map[2][3]);

    putchar('\n');
    
    // toon de map
    show_points(map);

    // geef het geheugen weer vrij
    delete_point_map(map);
    
    // vernietig de robot
    destroy_robot(robot);
    
	return 0;
}

/**
 * @brief   Deze methode creeert een punt dat later in de map array wordt gestopt.
 *          Het geheugen wordt dynamisch gealloceerd en dient na het programma dit geheugen
 *          weer vrij te geven.
 * @param x Het x-coordinaat van de point.
 * @param y Het x-coordinaat van de point.
 * @return  Pointer naar de point struct die gecreerd is.
 */
coor_t *create_point(int x, int y)
{
    // alloceer genoeg geheugen voor een point 
	coor_t *point = malloc(sizeof(coor_t));

    // set x en y-coordinaat.
	point->x = x;
	point->y = y;

    // geef het adres naar de point terug
	return point;
}

/**
 * @brief       Geeft het geheugen vrij dat voor een point gealloceerd is.
 * @param point Het adres van het geheugen dat weer vrij gegeven moet worden.
 */
void delete_pointer(coor_t *point)
{
    // dealloceer het geheugen waar de pointer point naar wijst
	free(point);
}

/**
 * @brief       Testmethode om de coordinaten op de map (array) te tonen.
 * @param point Het punt op de map dat zijn coordinaten moet laten zien.
 */
void show_points(coor_t *map[][GRID_COLUMNS])
{
    for (int y = 0; y < GRID_ROWS; y++)
	{
		for (int x = 0; x < GRID_COLUMNS; x++)
		{
			coor_t *point = map[x][y];
            
            printf("(%d, %d)", point->x, point->y);
		}
        
        putchar('\n');
	}
}

/**
 * @brief       Methode om de map te initialiseren met standaardwaarden. Dit zijn de coordinaten
 *              van de verschillende points.
 * @param grid  De map waar de point van geinitialiseerd moeten worden.
 */
void init_point_map(coor_t *grid[][GRID_COLUMNS])
{
    // initialiseer de coordinaten. Links boven is x =0 , y = 0. 
    // Rechts onder is x = 4, y = 4.
	for (int y = 0; y < GRID_ROWS; y++)
	{
		for (int x = 0; x < GRID_COLUMNS; x++)
		{
			grid[x][y] = create_point(x, y);
		}
	}
}

/**
 * @brief       Deze methode gaat door de map heen en dealloceert al het geheugen dat
 *              door de point gealloceerd zijn.
 * @param grid  De map met gealloceerde points.
 */
void delete_point_map(coor_t *grid[][GRID_COLUMNS])
{
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLUMNS; j++)
            delete_pointer(grid[i][j]);
}

/**
 * @brief       Plaatst een obstakel op de point (het kruispunt)
 * @param point Het punt waar het obstakel moet staan.
 */
void place_obstacle(coor_t *point)
{
    point->x = OBSTACLE;
    point->y = OBSTACLE;
}

robot_t *create_robot(void)
{
    robot_t *robot = malloc(sizeof(robot_t));
    
    // zet de robot op zij start positie
    init_robot(robot);
    
    return robot;
}

/**
 * @brief       Zet de robot op de startpositie
 * @param robot De robot die op de startpositie geplaats moet worden
 */
void init_robot(robot_t *robot)
{
    // zie de defines voor de startwaarden (default: 0,0)
    robot->current_pos = create_point(START_X, START_Y);
}

/**
 * @brief       Verwijdert de robot door het geheugen weer vrij te geven.
 * @param robot De robot die vernietigd moet worden.        
 */
void destroy_robot(robot_t *robot)
{
    free(robot);
}

/**
 * @brief       Deze methode werkt de huidige positie van de robot bij. Er wordt in eerste instantie vanuit gegaan dat de robot 
 *              begint op (0, 0) en naar boven kijkt.
 * @param robot De robot waarvan zijn huidige positie geupdate moet worden.
 * @param point De nieuwe positie.
 */
void update_position(robot_t *robot, coor_t*point)
{
    robot->current_pos->x = point->x;
    robot->current_pos->y = point->y;
}