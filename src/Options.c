//
// Created by chorm on 2020-06-12.
//

#include <Map.h>
#include <stdlib.h>
#include "Options.h"
#include <string.h>
#include <Configure.h>

bool strless(const void* k1,const void* k2){
    return strcmp((const char*)k1,(const char*)k2)<0;
}

void print_help();

struct Options* loadoptions(int argc,char** argv){
    struct Options* ret = malloc(sizeof(struct Options));
    ret->with = map_new(NULL,strless,NULL,NULL);
    ret->enable = map_new(NULL,strless,NULL,NULL);
    ret->prefix = LCONF_DEFAULT_PREFIX;
    ret->module_path = LCONF_MODULE_PATH;
    ret->generator = LCONF_DEFAULT_GENERATOR;
    ret->srcdir = NULL;
    ret->target = "host";
    for(int i = 0;i<argc;i++){
        char* arg = argv[i];
        if(*arg=='-'&&*++arg=='-'){
            arg++;
            char* begin = strtok(arg,"=");
            if(strcmp(begin,"prefix")==0){
                ret->prefix =
            }
        }
    }
    return ret;
}
