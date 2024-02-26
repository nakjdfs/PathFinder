#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    if (argc != 2){
		mx_printerr("usage: ./pathfinder [filename]\n");
		exit(0);
	}
    char c;
    int f;
    int numofisles = mx_find_count(argv[1]);
    bool k = true;
    int c_of_isle = 0;
    int i = 0;
    char *islesnames[numofisles+1];
    for(int i = 0; i < numofisles+1; i++){
        islesnames[i] =  NULL;
    }
    int sum_of = 0;
    int matrixPath[numofisles][numofisles];
    for(int i = 0; i < numofisles; i++){
        for (int j = 0; j < numofisles; j++)
        {
            matrixPath[i][j] = -1;
        }
    }
    while (k){
        if((f =open(argv[1],O_RDONLY))== -1){
            mx_printerr("error: file ");
            mx_printerr(argv[1]);
            mx_printerr(" does not exist\n");
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        int count = 0;
        //int r = i + 1;
        bool comma = false;
        int reading;
        for (int r = i + 1;r > 0; r--)
        {
            read(f, &c, 1);
            while (c != '\n') {
                read(f, &c, 1);
            }
            
        }
        while((reading = read(f,&c,1)) == 1){
           if(c =='\n') break;
            //printf("%c",c);
            if (c == ',')
            {
                comma = true;
            }
            if(comma ==false){
                count++;
            }
        }
        reading = read(f,&c,1);
        if(reading <= 0){
            k = false;
        }
        if(comma == false){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        close(f);

        
        //printf("=============\n");
        //printf("count - %d\n",count);
        
        if((f =open(argv[1],O_RDONLY))== -1){
            mx_del_arr((char**)islesnames);
            mx_printerr("error: file ");
            mx_printerr(argv[1]);
            mx_printerr(" does not exist\n");
        }
        //r = i + 1;
        char *islesroute = mx_strnew(count);
        int j = 0;
        comma = false;
        int num = 0;
        for (int r = i + 1;r >= 0; r--)
        {
            if(r == 0){
                while((reading = read(f,&c,1)) == 1){
                    if(c=='\n'){
                        break;
                    }
                    if(comma){
                        if(mx_isdigit(c)){
                        num*=10;
                        num += c -'0';
                        }else{
                            mx_printerr("error: line ");
                            mx_printerr(mx_itoa(i + 2));
                            mx_printerr(" is not valid\n");
                            mx_strdel(&islesroute);
                            mx_del_arr((char**)islesnames);
                            close(f);
                            exit(0);
                        }
                    }
                    if(c == ','){
                        comma = true;

                    }
                    if(!comma) {
                        islesroute[j]=c;
                        j++;
                    }
                }
                


            }else{
                read(f, &c, 1);
                while (c != '\n') {
                    read(f, &c, 1);
                }
            }
        }
        close(f);
        sum_of += num;
        if(sum_of < 0){
            mx_printerr("error: sum of bridges lengths is too big\n");
            mx_strdel(&islesroute);
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        int c_of_tir = 0;
        int index_of_tir = 0;

        for (int y = 0; y < mx_strlen(islesroute); y++)
        {
            if(islesroute[y]=='-'){
                c_of_tir++;
                index_of_tir = y;
            }
        }
        if(c_of_tir != 1){
            
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            mx_strdel(&islesroute);
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        if(islesroute[0]=='-'){
            
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            mx_strdel(&islesroute);
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        if(islesroute[mx_strlen(islesroute) - 1]=='-'){
            
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 2));
            mx_printerr(" is not valid\n");
            mx_strdel(&islesroute);
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        char *firstIsle =mx_strndup(islesroute,index_of_tir);
        //printf("%s\n",firstIsle);
        for (int y = 0; y < mx_strlen(firstIsle); y++)
        {
            if(!mx_islower(firstIsle[y])&&!mx_isupper(firstIsle[y])){
                
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i + 2));
                mx_printerr(" is not valid\n");
                mx_strdel(&firstIsle);
                mx_strdel(&islesroute);
                mx_del_arr((char**)islesnames);
                exit(0);
            }
        }
        
        char *secondIsle =mx_strndup(&islesroute[index_of_tir + 1],(mx_strlen(islesroute) - index_of_tir));
        //printf("%s\n",secondIsle);
        for (int y = 0; y < mx_strlen(secondIsle); y++)
        {
            if(!mx_islower(secondIsle[y])&&!mx_isupper(secondIsle[y])){
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i + 2));
                mx_printerr(" is not valid\n");
                mx_strdel(&islesroute);
                mx_strdel(&firstIsle);
                mx_strdel(&secondIsle);
                mx_del_arr((char**)islesnames);
                exit(0);
            }
        }
        if(mx_strlen(firstIsle)==mx_strlen(secondIsle)){
            if(mx_strncmp(secondIsle,firstIsle,mx_strlen(firstIsle)) == 0){
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i + 2));
                mx_printerr(" is not valid\n");
                mx_strdel(&islesroute);
                mx_strdel(&firstIsle);
                mx_strdel(&secondIsle);
                mx_del_arr((char**)islesnames);
                exit(0);
            }
        }
        bool isFirstIsl = false;
        bool isSecondIsl = false;
        //int freeInd = -1;
        for (int y = 0; y < numofisles; y++)
        {
            if(islesnames[y] == NULL){
                //freeInd = y;
                continue;
            }
            if(mx_strncmp(islesnames[y],firstIsle,mx_strlen(firstIsle)) == 0){
                isFirstIsl = true;
            }
            if(mx_strncmp(islesnames[y],secondIsle,mx_strlen(secondIsle)) == 0){
                isSecondIsl = true;
            }
        }

        if(c_of_isle >= numofisles&&(!isFirstIsl || !isSecondIsl)){
            int temp = c_of_isle;
            if(!isFirstIsl)
                temp++;
            if(!isSecondIsl)
                temp++;
            if(temp >= numofisles){
                mx_printerr("error: invalid number of islands\n");
                mx_strdel(&firstIsle);
                mx_strdel(&secondIsle);
                mx_strdel(&islesroute);
                mx_del_arr((char**)islesnames);
                exit(0);
            }
        }
        if(!isFirstIsl){
            //mx_strdel(&islesnames[freeInd]);
            islesnames[c_of_isle] = mx_strndup(islesroute,index_of_tir);//mx_strdup(firstIsle);
            c_of_isle++;
        }
        if (!isSecondIsl)
        {
            islesnames[c_of_isle] = mx_strndup(&islesroute[index_of_tir + 1],(mx_strlen(islesroute) - index_of_tir));//mx_strdup(secondIsle);
            c_of_isle++;
        }
        int ind1 ,ind2;
        for (ind1 = 0; ind1 < numofisles; ind1++) {
            if(islesnames[ind1] == NULL){
                continue;
            }
            if (mx_strncmp(firstIsle,islesnames[ind1], mx_strlen(firstIsle)) == 0) {
                break;
            }
        }
        for (ind2 = 0; ind2 < numofisles; ind2++) {
             if(islesnames[ind2] == NULL){
                continue;
            }
            if (mx_strncmp(secondIsle, islesnames[ind2], mx_strlen(secondIsle)) == 0) {
                break;
            }
        }
        if (matrixPath[ind1][ind2] == -1) {
            matrixPath[ind1][ind2] = num;
            matrixPath[ind2][ind1] = num;
        }else{
            mx_printerr("error: duplicate bridges\n");
            mx_strdel(&firstIsle);
            mx_strdel(&secondIsle);
            mx_strdel(&islesroute);
            mx_del_arr((char**)islesnames);
            exit(0);
        }
        i++;
        mx_strdel(&islesroute);
        mx_strdel(&firstIsle);
        mx_strdel(&secondIsle);
    }
    for(int j = 0; j < numofisles; j++){
        if(islesnames[j]==NULL){
            mx_printerr("error: invalid number of islands\n");
            mx_del_arr((char**)islesnames);
            exit(0);
        }
    }
    int matrixOneDemision[numofisles * numofisles];
    for (int r = 0; r < numofisles; r++)
    {
        for (int j = 0; j < numofisles; j++)
        {
            matrixOneDemision[r*numofisles + j] = matrixPath[r][j];
        }
        
    }
    
   
    for (int it = 0; it < numofisles; it++)
    {
        for (int j = it + 1; j < numofisles; j++)
        {
            int routes[numofisles];
            bool isToched[numofisles];
            for (int r = 0; r < numofisles; r++) {
                routes[r] = __INT_MAX__;
                isToched[r] = false;
            }
            routes[j] = 0;
            int index = j;
            int c = 0;
            while(c < numofisles) {
                isToched[index] = true;
                for (int r = 0; r < numofisles; r++) {
                    if (matrixPath[index][r] != -1
                    &&routes[r] > (matrixPath[index][r] + routes[index])
                    &&isToched[r]==false) {
                        routes[r] = matrixPath[index][r] + routes[index];
                    }
                }
                index = mx_find_min(routes, isToched, numofisles);
                c++;
            }
            t_strings s;
            s.str = mx_strnew(40 + 7 + mx_strlen(islesnames[it]) 
            + 4 + mx_strlen(islesnames[j]));
            mx_strcpy(s.str, "========================================");
            mx_strcat(s.str, "\nPath: ");
            mx_strcat(s.str, islesnames[it]);
            mx_strcat(s.str, " -> ");
            mx_strcat(s.str, islesnames[j]);
            s.routeA = mx_strnew(8 + mx_strlen(islesnames[it]));
            mx_strcat(s.routeA, "\nRoute: ");
            mx_strcat(s.routeA, islesnames[it]);
            s.routeNum = mx_strnew(11);
            mx_strcpy(s.routeNum, "\nDistance: ");
            s.route_length = routes[it];
            t_ints ints;
            ints.count = numofisles;
            ints.fr=it;
            ints.to = j;
            mx_path(&s, islesnames, routes,matrixOneDemision,ints);
            mx_strdel(&s.str);
            mx_strdel(&s.routeA);
            mx_strdel(&s.routeNum);
        }
        
    }
    mx_del_arr((char**)islesnames);
    return 0;
}
