//
// Created by chorm on 2020-06-07.
//

#include <lua.h>
#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>
#include "Options.h"
#include <string.h>
#include <Configure.h>

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
                    "\tconfigure [options] <src-or-build-dir>\n"
                    "\t\tOptions:\n\n"
                    "\t\t--prefix=<path>: Sets the root of the installation tree to <path>. Defaults to " LCONF_DEFAULT_PREFIX "\n"
                    "\t\t--module-path=<path>: Sets the lua search path for lconf modules. Defaults to " LCONF_MODULE_PATH "\n"
                    "\t\t--generator=<generator>: Sets the generator to use for the build. Defaults to " LCONF_DEFAULT_GENERATOR "\n"
                    "\t\t--build-type=<build>: Sets the build type (debug, release, relwithdebuginfo) for the build. Defaults to debug\n"
                    "\t\t--target=host|<tuple>: Sets the target for cross compilation. Defaults to host\n"
                    "\t\t--with-<option>=<value>: Sets the <option> to <value>.\n"
                    "\t\t--without-<option>: Sets the <option> to off\n"
                    "\t\t--enable-<option>: Sets the boolean <option> to on\n"
                    "\t\t--disable-<option>: Sets the boolean <option> to on\n"
                    "\tbuild [options] [bin-dir] [-- [build tool options]]\n"
                    "\t\t--build=<targets...>: Builds only the named targets (except that if any target is named all, all targets are built), separated by semicolons. In a multiproject build <project>/<target> selects <target> built by <project>\n"
                    "\t\t--jobs=<jobs>: In buildsystems that support multiple jobs, sets the number of jobs to use to build the project\n"
                    "\t\t--status|--no-status: Enables or disables status indicators on generators that support them (Default on for such targets)\n"
                    "\t\t--reconfigure: Forces lconf to rerun the configuration, even if it is not out-of-date.\n"
                    "\t\t--no-reconfigure: Prevents lconf from rerunning the configuration, even if it is out of date.\n"
                    "\tinstall [options] [bin-dir] [-- [build tool options]]\n"
                    "\t\t--install=<targets...>: Installs only the named targets.";

void print_help(){

}

int main(int argc, char** argv){
    if(argc<2){

        return 1;
    }else if(strcmp(argv[1],"configure")==0){
        struct Options* opts = loadoptions(argc-2,argv+2);

    }


}

void load_lua_libs(lua_State* state,int argc,char** argv){

}
