# MobileBlox
Mobile Blox Android 32 bits Executor Roblox Open Source, version 2.555.874

Only has loadstring and uses a simple Lua UI as giving away a whole executor with
Lots of script support wouldn't be good.

Addresses located at globals.hpp
Should be easy to update if you know how.

To inject in Roblox just compile the source, then get the library
`libmobileblox.so`

And put it in Roblox's APK folder `lib/`
Now decompile the Roblox's classes.dex and go to 
`com/roblox/client/ActivityNativeMain`

In there find the `OnCreate` method and just below it Paste this

```
const-string v0, "mobileblox"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```
