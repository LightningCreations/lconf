//
// Created by chorm on 2020-06-07.
//

#ifndef LCONF_OPTIONS_H
#define LCONF_OPTIONS_H

#include <lstate.h>
#include <Map.h>

struct Options{
    const char* prefix;
    const char* target;
    const char* module_path;
    const char* generator;
    const char* srcdir;
    TreeMap* with;
    TreeMap* enable;
};

struct Options* loadoptions(int argc,char** argv);

void freeoptions(struct Options*);

void load_optlib(lua_State* L,struct Options*);

int opt_enable(lua_State* L);
int opt_with(lua_State* L);
int opt_generator(lua_State* L);
int opt_target(lua_State* L);
int opt_host(lua_State* L);

#endif //LCONF_OPTIONS_H
