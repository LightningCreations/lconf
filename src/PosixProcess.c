//
// Created by chorm on 2020-06-16.
//

#include "LuaApi.h"

#include <unistd.h>
#include <lua.h>
#include <stdlib.h>
#include <ltable.h>
#include <string.h>

static _Bool find_program(lua_State *L,const char *path){
    if(strstr(path,"/")){
        if(access(path,X_OK)) {
            lua_pushstring(L, path);
            return 1;
        } else{
            return 0;
        }
    }
    char* env = getenv("PATH");
    char* s = malloc(strlen(env)+1);
    strcpy(s,env);
    for(char* root = strtok(s,":");root;root = strtok(NULL,":")){
        size_t p = strlen(root)-1;
        if(p<0)
            continue;
        if(root[p]=='/')
            root[p] = 0;
        char* prg = malloc(strlen(root)+strlen(path)+2);
        strcpy(prg,root);
        strcat(prg,"/");
        strcat(prg,path);
        if(access(prg,X_OK)){
            lua_pushstring(L,prg);
            free(prg);
            free(s);
            return 1;
        }else{
            free(prg);
            continue;
        }
    }
    free(s);
    return 0;
}

int lconf_findprogram(lua_State *L){
    if(lua_istable(L,1)){
        int top = lua_gettop(L);
        int idx = 1;
        while(lua_geti(L,1,idx++),!lua_isnil(L,top+1))
            if(find_program(L,lua_tostring(L,top+1)))
                return 1;
        return 0;
    }else{
        const char* prg = lua_tostring(L,1);
        return find_program(L,prg);
    }
}