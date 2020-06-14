//
// Created by chorm on 2020-06-12.
//

#include <Map.h>
#include <stdlib.h>
#include "Options.h"
#include <string.h>



bool strless(const void* k1,const void* k2){
    return strcmp((const char*)k1,(const char*)k2)<0;
}

struct Options* loadoptions(int argc,char** argv){
    struct Options* ret = malloc(sizeof(struct Options));
    ret->with = map_new(NULL,strless,NULL,NULL);
    ret->enable = map_new(NULL,strless,NULL,NULL);

}