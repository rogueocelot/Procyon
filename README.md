# Procyon

This is a simple game made in SFML, mostly to demonstrate random tile generation and pathfinding.

## Running
To run, first [install SFML](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)  
To compile: (assuming SFML is in the default location)
```bash
make
```
To run:
```bash
./procyon
```
To remove:
```bash
make clean
```

## About
When the game starts, a 50x50 grid of isometric tiles is randomly generated. It can contain a blank space, an "organic matter" space, or a rock. To control the rover, click on a grid square to pathfind to it. When on an organic space, press the spacebar to "discover".

![Example usage](example.png?raw=true)  
