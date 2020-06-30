//
// Created by chorm on 2020-06-16.
//

#ifndef LCONF_LUAAPI_H
#define LCONF_LUAAPI_H

#include <lua.h>


void lua_loadlconf(lua_State *L);

int lconf_findprogram(lua_State *L);
int lconf_executeprocess(lua_State *L);

#endif //LCONF_LUAAPI_H
