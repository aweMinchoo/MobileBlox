#pragma once

#include <cstdint>
#include "luau/lua.h"
#include "luau/lstate.h"

static std::uintptr_t ScriptContext{};// Roblox's scriptcontext
static lua_State* rL{}; // Roblox's lstate
static lua_State* eL{}; // didn't know what to namethis but its the exploits lstate

// addresses, easy to update if in here
// due to a stack issue related to thumb in 32 bits roblox you need to add a 1 to function addresses
static constexpr int startscript_addy = 0x12C993D;
static constexpr int getstate_addy = 0x12B495D;
static constexpr int newthread_addy = 0x27A68F1;
static constexpr int luauload_addy = 0x27BEBB1;
static constexpr int spawn_addy = 0x12B66E9;