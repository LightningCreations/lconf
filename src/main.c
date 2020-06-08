//
// Created by chorm on 2020-06-07.
//

#include <lua.h>
#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>

void* alloc(void *ud, void *mem, size_t osz, size_t nsz){
    if(mem) {
        if(nsz==0){
            free (mem);
            return NULL;
        }else
            return realloc(mem,nsz);
    } else
        return malloc(nsz);
}

void load_lua_libs(lua_State* state,int argc,char** argv);

const char HELP[] = "Usage: %s <configure|build>\n"
                    "%1$s configure [options] <src-dir>\n"
                    "%1$s build [options] <bin-dir> ";

int main(int argc, char** argv){
    if(argc<2){
        printf(HELP,argv[0]);
    }
    lua_State* state = lua_newstate(alloc,NULL);
    load_lua_libs(state,argc,argv);

}