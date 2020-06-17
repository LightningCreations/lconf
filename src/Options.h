//
// Created by chorm on 2020-06-07.
//

#ifndef LCONF_OPTIONS_H
#define LCONF_OPTIONS_H

#include <lstate.h>
#include <Map.h>
#include <List.h>
#include <stdint.h>

struct Options {
    const char *prefix;
    const char *target;
    const char *module_path;
    const char *generator;
    const char *build_type;
    const char *srcdir;
    const char *builddir;
    // Safety: Map const char*->const char*. UB to modify pointed to values (May be string literals)
    TreeMap *with;
    // Safety: Map const char* -> const char*. UB to modify pointed to values (May be string literals)
    TreeMap *enable;
};


struct Options* loadoptions(int argc, char **argv);

void freeoptions(struct Options*);

void load_optlib(lua_State *L, struct Options*);




#endif //LCONF_OPTIONS_H
