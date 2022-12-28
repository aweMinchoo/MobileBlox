#include <thread>
#include <dobby.h>
#include <unistd.h>

#include "hooks/hooks.hpp"
#include "memory/mem.hpp"
#include "exec/funcs.hpp"

void mainfunc(){
    // Only start when roblox is loaded
    while (!isLibraryLoaded("libroblox.so")) sleep(1);

    // Init our function pointers
    initfuncs();

    // Thanks to no memcheck we can just hook StartScript and steal first arg to get script context
    DobbyHook(reinterpret_cast<void*>(getAddress(startscript_addy)), (void*)&hkstartscript, (void**)&origstartscript);

    // testing execution
    //sleep(80);
    //executescript(eL,"loadstring(\"print('hi')\")()");
}

[[maybe_unused]] __attribute__((constructor))
void EntryPoint(){ std::thread{mainfunc}.detach(); }