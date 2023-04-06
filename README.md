
# Maze Project 2.0

This is the second version of the maze project I wrote to demonstrate `ray casting` in C using SDL2. You can find the compressed first version in `versions/v1.0.zip`.

Ray casting is a rendering technique capable of transforming a limited form of data (usually two-dimensional) into a three-dimensional projection by tracing projected rays from the view point into the viewing area. 

Ray casting is different from ray tracing. Ray casting is a rendering algorithm which is much simpler to implement, which in turn makes it faster than raytracing.

## Directories

`src` contains the C source files 
`headers` contains the header files
`maps` contains the map files
`textures` contains the textures
`versions` contains the zipped files of the earlier versions
`screenshots` contains the project screenshots

## Flowchart

*Flowchart goes here*

## Setup

To setup this project locally, follow these steps
- Install SDL2 and SDL2_Image
- Clone this repository
- Access the 3D-Maze directory
- Compile the files by running `make all`
- Run the executable by running `./3D-Maze`
- Tryout other maps by running `./3D-Maze maps/map_2` or `./3D-Maze maps/map_clone`

You can also run betty checks by running `make betty`. To find out more about betty, click [here](https://github.com/holbertonschool/Betty).

## Controls
- `↑` or `w`: Move Forward
- `↓` or `s`: Move Backward
- `←` or `a`: Turn Left
- `→` or `d`: Turn Right
- `q`: Strafe Left
- `e`: Strafe Right
- `Mouse scroll left`: Turn Left
- `Mouse scroll right`: Turn Right
- `f`: Toggle Fullscreen and Windowed mode
- `ESC`: Quit

## Features and Screenshots
- [x] Walls
- [x] Orientation
- [x] Rotation
- [x] Move
- [x] Ouch
- [x] Parser
- [ ] Draw the Map
- [x] Betty
- [x] Textures
- [x] Multitask
- [x] Textures 2
- [ ] Weapons
- [x] Enemies
- [ ] Rain
- [x] Extras


![Screenshot](https://github.com/pelu-mi/3D-Maze/blob/master/screenshots/shot.png)

![Screenshot2](https://github.com/pelu-mi/3D-Maze/blob/master/screenshots/shot2.png)


## Next Steps

- Implement a Load screen
- Implement 2D map view
- Weapons
- Change in weather
- Enemy movement

## Resources

Here are the links to the tutorials that can help:

- Install SDL2: click [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
- LazyFoo SDL2 tutorials: click [here](https://lazyfoo.net/tutorials/SDL/)
- Permadi Raycasting tutorial: click [here](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- Lodev Raycasting tutorial: click [here](https://lodev.org/cgtutor/raycasting.html)
- SDL2 Library: click [here](https://wiki.libsdl.org/SDL2/CategoryAPI)



## Note
**This project was implemented using SDL2 not SDL1 or 1.2**

## Author
Fadolapo Oluwapelumi
[Email](mailto:pelumifadolapo7@gmail.com) [LinkedIn](https://www.linkedin.com/in/oluwapelumi-fadolapo/) [HashNode](https://hashnode.com/@pelumi7) [Medium](https://medium.com/@lumi_codes)
