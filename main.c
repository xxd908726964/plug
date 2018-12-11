#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/stat.h>
#include "load_dll_from_config.h"

int main(int argc, char const *argv[])
{

    struct dl_fun_arry *fum_arr = malloc(sizeof(struct dl_fun_arry) + sizeof(struct dl_fun) * 5);
    fum_arr->num = 0;
    fum_arr->size = 5 ;
    load_dll_from_config(fum_arr,"./config.ini");
    for(int i=0;i<fum_arr->num;i++)
    (fum_arr->dll_load[i].fun_point)(NULL);
    
    free(fum_arr);
    return 0;
}
