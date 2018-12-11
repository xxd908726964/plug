#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "load_dll_from_config.h"

void load_dll_from_config(struct dl_fun_arry *p, const char *config_path)
{
    FILE *f = fopen(config_path, "r");
    int i = 0;
    for (;;)
    {
        if (p->num == p->size)
        {
            struct dl_fun_arry *temp = realloc(p, sizeof(struct dl_fun_arry) + sizeof(struct dl_fun) * (p->size + 5));
            if (!temp)
            {
                perror("realloc error");
                exit(0);
            }
            p->size += 5;
        }
        char fun_name[30] = {0};
        while (i != -1)
        {
            fun_name[i] = getc(f);
            if (fun_name[i] == '#') //遇到#表示注释，从此字符起到行末忽略
            {
                fun_name[i] = '\0';
                char temp;
                while (1)
                {
                    temp = getc(f);
                    if (temp == '\n')
                        break;
                    if (temp == EOF)
                        break;
                }
            }
            if (fun_name[i] == ' ') //遇到空格，跳过
                continue;
            if (fun_name[i] == '\n') //到了行末
            {
                fun_name[i] = '\0';
                i = 0;
                break;
            }
            if (fun_name[i] == EOF) //到了文件末尾
            {
                fun_name[i] = '\0';
                i = -1;
                return;
            }
            i++;
        }
        if (strlen(fun_name) == 0)
            continue;
        *strchr(fun_name, '=') = '\0';
        strncpy(p->dll_load[p->num].fun_name, fun_name, strlen(fun_name));
        strncpy(p->dll_load[p->num].dl_path, fun_name + strlen(fun_name) + 1, strlen(fun_name + strlen(fun_name) + 1));
        p->dll_load[p->num].handle = dlopen(p->dll_load[p->num].dl_path, RTLD_LAZY);
        if (!(p->dll_load[p->num].handle))
            continue;
        p->dll_load[p->num].fun_point = (void (*)(void *))dlsym(p->dll_load[p->num].handle, p->dll_load[p->num].fun_name);
        p->num++;
        if (i == -1)
            break;
    }
}

