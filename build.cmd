@echo off
bion -o bin\out_plort.c plort ^
    && cl /Fe:bin\plort /Fo:bin\plort bin\out_plort.c ^
    /I import\angle\include /I import\sdl2\include /link ^
    /LIBPATH:import\sdl2\lib\x64 /LIBPATH:import\angle\lib\x64 ^
    SDL2.lib SDL2main.lib libEGL.lib libGLESv2.lib /SUBSYSTEM:CONSOLE
