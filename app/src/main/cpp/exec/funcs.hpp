#pragma once

#include <string>
#include "../globals.hpp"
#include "../memory/mem.hpp"

#include "../luau/lua.h"
#include "../luau/lstate.h"
#include "../luau/Luau/Compiler.h"
#include "../luau/Luau/BytecodeBuilder.h"

class bytecode_encoder_t : public Luau::BytecodeEncoder {
    std::uint8_t encodeOp(const std::uint8_t Opcode) override
    { return Opcode * 227; }
};

lua_State* (*rlua_getmainstate)(std::uintptr_t scriptcontext, std::uintptr_t identity, std::uintptr_t script);
lua_State* (*rlua_newthread)(lua_State* rL);
int (*rluau_load)(lua_State* rL, const char* chunkname, const char* code, size_t codesize, int env);
int (*rspawn)(lua_State* rL);

void initfuncs(){
    rlua_getmainstate = reinterpret_cast<lua_State*(*)(std::uintptr_t,std::uintptr_t,std::uintptr_t)>(getAddress(getstate_addy));
    rlua_newthread = reinterpret_cast<lua_State*(*)(lua_State*)>(getAddress(newthread_addy));
    rluau_load = reinterpret_cast<int(*)(lua_State*,const char*,const char*,size_t,int)>(getAddress(luauload_addy));
    rspawn = reinterpret_cast<int(*)(lua_State*)>(getAddress(spawn_addy));
}

void executescript(lua_State* ls,const std::string& script){
    bytecode_encoder_t encoder;
    auto bc = Luau::compile(script,{},{},&encoder);

    rluau_load(ls,"",bc.c_str(),bc.size(),0);
    rspawn(ls);
}