#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

typedef struct s_strings {
    char *str;
    char *routeA;
    char *routeNum;
    int route_length;
}              t_strings;
typedef struct s_ints {
    int fr;
    int to;
    int count;
}              t_ints;

int mx_find_count(char* file);
int mx_find_min(int *routes, bool *isToched, int count);
void mx_result(t_strings *str);
void mx_path(t_strings *str,char **islenames,int *routes, int *matrix, t_ints ints);

#endif

