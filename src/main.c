//
// Created by chorm on 2020-06-07.
//

#include <lua.h>
#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>
#include "Options.h"
#include <string.h>

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

const char HELP[] = "Usage: %s <configure|build|install>\n"
                    "configure [options] <src-dir>\n"
                    "build [options] <bin-dir>\n"
                    "install [options] <bin-dir>\n";

int main(int argc, char** argv){
    if(argc<3){
        printf(HELP,argv[0]);
        return 1;
    }else if(strcmp(argv[1],"configure")==0){
        struct Options* opts = loadoptions(argc-2,argv+2);
    }


}

void load_lua_libs(lua_State* state,int argc,char** argv){

}
