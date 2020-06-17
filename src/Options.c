//
// Created by chorm on 2020-06-12.
//

#include <Map.h>
#include <stdlib.h>
#include "Options.h"
#include <string.h>
#include <Configure.h>

bool strless(const void* k1,const void* k2){
    return strcmp((const char*)k1, (const char*)k2) < 0;
}

void print_help();

struct Options* loadoptions(int argc, char** argv){
    struct Options* ret = malloc(sizeof(struct Options));
    ret->with = map_new(NULL, strless, NULL, NULL);
    ret->enable = map_new(NULL, strless, NULL, NULL);
    ret->prefix = LCONF_DEFAULT_PREFIX;
    ret->module_path = NULL;
    ret->generator = LCONF_DEFAULT_GENERATOR;
    ret->srcdir = NULL;
    ret->target = "host";
    for(int i = 0;i<argc-1;i++){
        char* arg = argv[i];
        if((*arg == '-') && (*++arg == '-')){
            arg++;
            char* begin = strtok(arg,"=");
            if(strcmp(begin, "prefix") == 0){
                ret->prefix = strtok(NULL, "");
                if(!ret->prefix){
                    print_help();
                    exit(1);
                }
            } else if (strcmp(begin,"module-path")==0){
                ret->module_path = strtok(NULL,"");
            } else if (strcmp(begin,"target")==0){
                ret->target = strtok(NULL,"");
                if(!ret->target){
                    print_help();
                    exit(1);
                }
            } else if(strcmp(begin,"generator")==0){
                ret->generator = strtok(NULL,"");
                if(!ret->generator){
                  print_help();
                  exit(1);
                }
            } else if(strncmp(begin,"with",4)==0) {
                char* value = strtok(NULL,"");
                strtok(begin,"-");
                const char* key = strtok(NULL,"");
                map_put(ret->with,key,value);
            } else if(strncmp(begin,"without",7)==0){
                const char* key = strtok(NULL,"");
                map_put(ret->with,key,"off");
            }else if(strncmp(begin,"enable",6)==0){
                const char* key = strtok(NULL,"");
                map_put(ret->enable,key,"on");
            }else if(strncmp(begin,"disable",7)==0){
                const char* key = strtok(NULL,"");
                map_put(ret->enable,key,"off");
            }else if(strcmp(begin,"build-dir")==0){
                ret->builddir = strtok(NULL,"");
                if(!ret->builddir){
                    print_help();
                    exit(1);
                }
            }
        }else{
            print_help();
            exit(1);
        }
    }
    if(argc == 0){
        print_help();
        exit(1);
    }else{
        ret->srcdir = argv[argc-1];
    }
    return ret;
}

int opt_enable(lua_State *L);
int opt_with(lua_State *L);
int opt_generator(lua_State *L);
int opt_target(lua_State *L);
int opt_install_path(lua_State *L);
int opt_build_type(lua_State *L);

int opt_index(lua_State *L);

void load_optlib(lua_State *L, struct Options* opts){
    int top = lua_gettop(L);
    lua_pushlightuserdata(L,opts);
    lua_newtable(L);
    lua_pushcfunction(L,opt_index);
    lua_setfield(L,top+2,"__index");
    lua_setmetatable(L,top+1);
    lua_setglobal(L,"options");
}

int opt_index(lua_State* L){
    int top = lua_gettop(L);
    if(top<2){
        lua_pushliteral(L,"index called with incorrect arguments");
        return lua_error(L);
    }
    const char* str = lua_tostring(L,2);
    if(strcmp(str,"with")==0)
        return opt_with(L);
    else if(strcmp(str,"enable")==0)
        return opt_enable(L);
    else if(strcmp(str,"generator")==0)
        return opt_generator(L);
    else if(strcmp(str,"install_path")==0)
        return opt_install_path(L);
    else if(strcmp(str,"target")==0)
        return opt_target(L);
    else if(strcmp(str,"build_type")==0)
        return opt_build_type(L);
    else{
        lua_pushfstring(L,"Unknown field: %s",str);
        return lua_error(L);
    }
}

int opt_generator(lua_State *L){
    struct Options* opt = (struct Options*)lua_touserdata(L,1);
    lua_pushstring(L,opt->generator);
    return 1;
}

int opt_build_type(lua_State *L){
    struct Options* opt = (struct Options*)lua_touserdata(L,1);
    lua_pushstring(L,opt->build_type);
    return 1;
}

int opt_target(lua_State *L){
    struct Options* opt = (struct Options*)lua_touserdata(L,1);
    lua_pushstring(L,opt->target);
    return 1;
}

int opt_call_install_path(lua_State *L){
    int top = lua_gettop(L);
    const char* obj = *(const char**)lua_touserdata(L,1);
    const char* str = lua_tostring(L,top+1);
    lua_pushfstring(L,"%s/%s",obj,str);
    return 1;
}

int opt_install_path(lua_State *L){
    struct Options* opt = (struct Options*)lua_touserdata(L,1);
    int top = lua_gettop(L);
    const char** obj = (const char**)lua_newuserdata(L,sizeof(const char));
    *obj = opt->prefix;
    lua_newtable(L);
    lua_pushcfunction(L,opt_call_install_path);
    lua_setfield(L,top+2,"__call");
    lua_setmetatable(L,top+1);
    return 1;
}

struct Option{
    const char* value;
    const char* default_;
};



int opt_default_value(lua_State *L){
    struct Option* opt = lua_touserdata(L,1);
    int top = lua_gettop(L);
    opt->default_ = lua_tostring(L,2);
    lua_copy(L,1,top+1);
    return 1;
}

#include <ctype.h>

int streq_case_insensitive(const char* s1,const char* s2){
    for(;*s1&&*s2;s1++,s2++)
        if(tolower(*s1)!=tolower(*s2))
            return 0;
    if(*s1||*s2)
        return 0;
    return 1;
}


int opt_get_value(lua_State *L){
    struct Option* opt = lua_touserdata(L,1);
    const char* val;
    if(opt->value)
        val = opt->value;
    else
        val = opt->default_;

    if(!val)
        lua_pushnil(L);
    else if(streq_case_insensitive(val,"off"))
        lua_pushboolean(L,0);
    else if(streq_case_insensitive(val,"on"))
        lua_pushboolean(L,1);
    else
        lua_pushstring(L,val);
    return 1;
}

int opt_option_index(lua_State *L){
    const char* str = lua_tostring(L,2);
    if(strcmp(str,"default")==0)
        lua_pushcfunction(L,opt_default_value);
    else if(strcmp(str,"get")==0)
        lua_pushcfunction(L,opt_get_value);
    else {
        lua_pushfstring(L,"No such field %s",str);
        return lua_error(L);
    }
    return 1;
}

int opt_enable(lua_State* L){
    struct Options* opt = lua_touserdata(L,1);
    const char* item = lua_tostring(L,2);
    const char* val = map_get(opt->enable,item);
    int top = lua_gettop(L);
    struct Option* n_opt = lua_newuserdata(L,sizeof(struct Option));
    n_opt->value = val;
    n_opt->default_ = NULL;
    lua_newtable(L);
    lua_pushcfunction(L,opt_option_index);
    lua_setfield(L,top+2,"__get");
    lua_setmetatable(L,top+1);
    return 1;
}

int opt_with(lua_State* L){
    struct Options* opt = lua_touserdata(L,1);
    const char* item = lua_tostring(L,2);
    const char* val = map_get(opt->with,item);
    int top = lua_gettop(L);
    struct Option* n_opt = lua_newuserdata(L,sizeof(struct Option));
    n_opt->value = val;
    n_opt->default_ = NULL;
    lua_newtable(L);
    lua_pushcfunction(L,opt_option_index);
    lua_setfield(L,top+2,"__get");
    lua_setmetatable(L,top+1);
    return 1;
}