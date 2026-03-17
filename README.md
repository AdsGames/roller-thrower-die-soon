# Roller Thrower Die Soon

[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=AdsGames_roller-thrower-die-soon&metric=reliability_rating)](https://sonarcloud.io/summary/new_code?id=AdsGames_roller-thrower-die-soon)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=AdsGames_roller-thrower-die-soon&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=AdsGames_roller-thrower-die-soon)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=AdsGames_roller-thrower-die-soon&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=AdsGames_roller-thrower-die-soon)

Throw guests to their death for fun. Roller Thrower Die Soon is our submission to Tojam in Allegro 5, converted to use SDL w/ ASW wrapper.

## Demo

[Web Demo](https://adsgames.github.io/roller-thrower-die-soon/)

## Setup

### CMake

```bash
cmake --preset debug
cmake --build --preset debug
```

### Build Emscripten

```bash
emcmake cmake --preset debug
cmake --build --preset debug
```
