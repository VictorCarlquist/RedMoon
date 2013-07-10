#! /bin/bash

g++ -c src/main.cpp -o obj/main.o -llua5.2 -lSDL -lGL
g++ -c src/object/object.cpp -o obj/object.o  -llua5.2 -I/usr/include/lua5.2
g++ -c src/render/render.cpp -o obj/render.o -llua5.2 -lSDL -lGL -lSOIL -lglut -lGLU -lGLEW 
g++ -c src/scene/scene.cpp -o obj/scene.o    -llua5.2 -I/usr/include/lua5.2
g++ -c src/wavefront/wavefront.cpp -o obj/wavefront.o  -llua5.2 -lSDL -lGL -lSOIL -lglut -lGLU -lGLEW -I/usr/include/lua5.2
g++ -c src/material/material.cpp -o obj/material.o  -llua5.2 -I/usr/include/lua5.2
g++ -c src/locate/locate.cpp -o obj/locate.o  -llua5.2 -I/usr/include/lua5.2
g++ -c src/keyboard/keyboard.cpp -o obj/keyboard.o -llua5.2 -lSDL -lGL
g++ -c src/camera/camera.cpp -o obj/camera.o  -llua5.2 -I/usr/include/lua5.2
g++ -c src/light/lightLamp.cpp -o obj/lightLamp.o  -llua5.2 -I/usr/include/lua5.2

g++ obj/main.o obj/object.o obj/render.o obj/scene.o obj/wavefront.o obj/keyboard.o obj/material.o  obj/locate.o obj/camera.o obj/lightLamp.o -o  redMoon -Wall -lglut -lGLU -ldl -llua5.2 -lSDL -lGL -lSOIL -lGLEW -I/usr/include/lua5.2 -pthread -Wall
