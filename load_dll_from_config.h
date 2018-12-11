#ifndef LOAD_DLL_FROM_CONFIG_H
#define LOAD_DLL_FROM_CONFIG_H
struct dl_fun{
    void (*fun_point)(void*);
    void *handle;
    char dl_path[80];
    char fun_name[20];
};
struct dl_fun_arry{
    int size;
    int num;
    struct dl_fun dll_load[0];
};


void load_dll_from_config(struct dl_fun_arry* p,const char *config_path);

#endif