//
// Created by chorm on 2020-06-07.
//

#ifndef LCONF_OPTIONS_H
#define LCONF_OPTIONS_H

#include <lstate.h>

void loadoptions(lua_State* into,int argc,char** argv);

int opt_enable(lua_State* L);
int opt_with(lua_State* L);
int opt_generator(lua_State* L);
int opt_target(lua_State* L);
int opt_host(lua_State* L);

#endif //LCONF_OPTIONS_H
