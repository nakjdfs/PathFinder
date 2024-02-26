#include "../inc/pathfinder.h"
void mx_path(t_strings *str, char **islenames,int *routes, int *matrix, t_ints ints) {
    
    if (ints.fr == ints.to) {
        mx_result(str);
        //mx_strdel(&str->str);
        mx_strdel(&str->routeA);
        mx_strdel(&str->routeNum);
        return;
    }
    for (int i = 0; i < ints.count; i++) {
        int k = ints.fr * ints.count + i;
        if ((routes[ints.fr] - routes[i]) == matrix[k]&&matrix[k]!=-1){
            char *t = mx_strnew(4 + mx_strlen(islenames[i]) + mx_strlen(str->routeA));
            mx_strcpy(t, str->routeA);
            mx_strcat(t, " -> ");
            mx_strcat(t, islenames[i]);
            
            char *t2;
            if (i == ints.to && str->route_length == routes[ints.fr]) {
                t2 = mx_strndup(str->routeNum,mx_strlen(str->routeNum));
            }else{
                int temp = matrix[k];
                int c = 0;
                while(temp > 0){
                    temp /= 10;
                    c++;
                }
                t2 = mx_strnew(c + 3 + mx_strlen(str->routeNum));
                mx_strcpy(t2, str->routeNum);                
                mx_strcat(t2,mx_itoa(matrix[k]));
                if (i == ints.to){
                    mx_strcat(t2, " = ");
                }
                else{
                    mx_strcat(t2, " + ");
                }
                
            }//mx_strdel(&str->routeNum);
            t_strings newstr;
            newstr.str = str->str;//mx_strdup(str->str);
            newstr.routeA = t;//mx_strdup(t);
            //mx_strdel(&t);
            newstr.route_length =str->route_length;
            newstr.routeNum = t2;
            t_ints ints2;
            ints2.count = ints.count;
            ints2.fr = i;
            ints2.to = ints.to;
            mx_path(&newstr,islenames,routes, matrix, ints2);
        }
    }
    //mx_strdel(&str->str);
    mx_strdel(&str->routeA);
    mx_strdel(&str->routeNum);
    
    return;

}
