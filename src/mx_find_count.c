#include "../inc/pathfinder.h"
int mx_find_count(char* file){
    char c;
    int f;
    if((f =open(file,O_RDONLY))== -1){
        mx_printerr("error: file ");
        mx_printerr(file);
        mx_printerr(" does not exist\n");
        exit(0);
    }
    int numofisles = 0;
    bool k = true;
    bool isFirst = true;
    while(k){
        if(isFirst){
            if((read(f,&c,1)) != 1){
                close(f);
                mx_printerr("error: file ");
                mx_printerr(file);
                mx_printerr(" is empty\n");
                exit(0);
            }
        }else{
            isFirst = false;
            if((read(f,&c,1)) != 1){
                close(f);
                mx_printerr("error: line 1 is not valid\n");
                exit(0);
            }
        }

        
        if(c!='\n'){
            if(mx_isdigit(c)){
            numofisles*=10;
            numofisles += c -'0';
            }else{
                close(f);
                mx_printerr("error: line 1 is not valid\n");
                exit(0);
            }
            
        }else{
            k = false;
        }
    }
    close(f);
    return numofisles;
}
