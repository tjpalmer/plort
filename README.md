Building on Windows, given correct environment:

```
ion -o bin\plort.c plort && cl /Fe:bin\plort /Fo:bin\plort bin\plort.c /I import\sdl2\include /link /LIBPATH:import\sdl2\lib\x64 SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
```

Change the subsystem to WINDOWS to dodge the console.
