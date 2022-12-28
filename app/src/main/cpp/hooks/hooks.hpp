#include <cstdint>
#include "../globals.hpp"
#include "../exec/funcs.hpp"
#include "../exec/impls.hpp"
#include "../LuaUI.hpp"
#include "../luau/lualib.h"

// have to keep everything in a header else a crash occurs
int (*origstartscript)(std::uintptr_t thiz, std::uintptr_t script);
int hkstartscript(std::uintptr_t thiz, std::uintptr_t rscript){
    // Lazy way of checking if the game changed
    if (ScriptContext != thiz){
        ScriptContext = thiz;

        int id[2] = {8,0};
        int script[] = { NULL,NULL };

        rL = rlua_getmainstate(thiz, reinterpret_cast<uintptr_t>(id),reinterpret_cast<uintptr_t>(script));
        eL = rlua_newthread(rL);

        luaL_sandboxthread(eL); // sandbox our globals
        // We set our identity/level to 8 by changing the value of eL->userdata->contextidentity
        *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>((std::uintptr_t)(eL) + 72) + 24) = 8;

        // Make the _G Table
        lua_createtable(eL, 0,0);
        lua_setfield(eL, -10002, "_G");

        // register our implementations
        regImpls(eL);

        // Execute a Lua UI
        executescript(eL, LuaUI);
    }

    return origstartscript(thiz,rscript);
}