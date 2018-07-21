To build on Windows, given the correct environment, run `build`.
Change the subsystem to WINDOWS to dodge the console.

Some extra setup that's handy once you've defined `IONHOME`:

```
set IONOS=win32
set IONBIN=%IONHOME%\bin
path %IONBIN%;%PATH%
vsenv -arch=x64
```

Calling vsenv explicitly up front will muddy your environment but make
subsequent builds faster, since setting up a vs environment takes a bit of time
(just a second, but eh).
