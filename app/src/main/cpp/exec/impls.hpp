#pragma once

#include "funcs.hpp"

// i chose this way of organization as i think its a bit more readable
// but of course its not the best one, find a better way
// all thanks to android studio not letting me use .cpp files

static int loadstring(lua_State* ls);

void regImpls(lua_State* thread){
    // Should wrap this into a registerfunction kind of macro or func
    lua_pushcclosure(thread,loadstring,"loadstring",0);
    lua_setfield(thread,-10002,"loadstring");
}

int loadstring(lua_State* ls){
    const char* s = lua_tostring(ls,1);

    bytecode_encoder_t encoder;
    auto bc = Luau::compile(s,{},{},&encoder);

    const char* chunkname{};
    if (lua_gettop(ls) == 2) chunkname = lua_tostring(ls, 2);
    else chunkname = "insertrandomgeneratedstring";

    if (rluau_load(ls, chunkname, bc.c_str(), bc.size(), 0))
    {
        lua_pushnil(ls);
        lua_pushstring(ls, lua_tostring(ls, -2));
        return 2;
    }
    return 1;
}