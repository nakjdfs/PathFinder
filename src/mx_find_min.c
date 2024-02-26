#include "../inc/pathfinder.h"
int mx_find_min(int *routes, bool *isToched, int count){
    int index = 0;
    int min = __INT_MAX__;
    for (int i = 0; i < count; i++) {
        if (min > routes[i]&&isToched[i]==false){
            index = i;
            min = routes[i];
        }
    }
    return index;
}
