#include "../inc/pathfinder.h"
void mx_result(t_strings *str) {
    mx_printstr(str->str);
    mx_printstr(str->routeA);
    mx_printstr(str->routeNum);
    mx_printstr(mx_itoa(str->route_length));
    mx_printstr("\n");
    mx_printstr("========================================");
    mx_printstr("\n");
    //if(str->routeNum != NULL)
    
}
