# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("mobileblox" CXX)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        mobileblox

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        luau/lapi.cpp
        luau/laux.cpp
        luau/lbaselib.cpp
        luau/lbitlib.cpp
        luau/lbuiltins.cpp
        luau/lcorolib.cpp
        luau/ldblib.cpp
        luau/ldebug.cpp
        luau/ldo.cpp
        luau/lfunc.cpp
        luau/lgc.cpp
        luau/lgcdebug.cpp
        luau/linit.cpp
        luau/lmathlib.cpp
        luau/lmem.cpp
        luau/lnumprint.cpp
        luau/lobject.cpp
        luau/loslib.cpp
        luau/lperf.cpp
        luau/lstate.cpp
        luau/lstring.cpp
        luau/lstrlib.cpp
        luau/ltable.cpp
        luau/ltablib.cpp
        luau/ltm.cpp
        luau/ludata.cpp
        luau/lutf8lib.cpp
        luau/lvmexecute.cpp
        luau/lvmload.cpp
        luau/lvmutils.cpp
        luau/Ast.cpp
        luau/BuiltinFolding.cpp
        luau/Builtins.cpp
        luau/BytecodeBuilder.cpp
        luau/Compiler.cpp
        luau/Confusables.cpp
        luau/ConstantFolding.cpp
        luau/CostModel.cpp
        luau/lcode.cpp
        luau/Lexer.cpp
        luau/Location.cpp
        luau/Parser.cpp
        luau/StringUtils.cpp
        luau/TableShape.cpp
        luau/TimeTrace.cpp
        luau/ValueTracking.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)
find_package(Dobby REQUIRED CONFIG)

include_directories(prefab/modules/dobby/include)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries( # Specifies the target library.
        mobileblox
        dobby::dobby

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})