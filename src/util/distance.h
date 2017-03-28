#ifndef DISTANCE_H
#define DISTANCE_H

#include <dungeon/dungeon.h>

typedef struct {
    int row;
    int col;
} Coordinate;

typedef struct {
    int d[DUNGEON_HEIGHT][DUNGEON_WIDTH];
} Distances;

Distances dijkstra(void *context, int start_row, int start_col, int (*length)(void *context, Coordinate* from, Coordinate* to));

#endif