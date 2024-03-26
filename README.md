# El Pacmaño

A pacman game with working score and lives.

## Group memebers.
- Kacper Lewandowski
- Artūrs Umbraško

## Setup instruction
Setup of the project should be as easy as making labs run. Simply use CMake on the CMakeLists.txt in the root folder of repository.
In case this doesn't work properly for some reason, you can:
- (Windows) Manually configure all required .cpp files and headers in ./external and ./headers in your Visual Studio. (specified below)
- (Linux) Use G++ and link all .cpp files and include .h files properly. A compile bash script that I used is provided. Up to date Linux compiled binary is also provided, just in case.
    
*IMPORTANT NOTICE*: we are using Sleep() function in the code. This only works on Windows. If you use Linux and want to compile and run the code, you need to uncomment #include <unistd.h> and line 168 (sleep(1)) in main.cpp, and comment out line 169 (Sleep(1000)). They are marked with comments in that file.
- Create an issue

On our PC's it worked properly, but sometimes it do be like that. 

## Ingame controls
Press on the start game button and navigate Pacman using arrow buttons **NOT WASD**
You can enter main menu again anytime by pressing ESC

## Features
- Fully functioning level and tilemap
- More tilemaps can be added simply by creating new maps
- Ghosts move and can kill pacman
- Pacman collects points (called pizzas in our game, we still haven't decided if he's Spanish or Italian)
- GUI that shows lives, score, and has a main menu
- Pacman has a texture

## Currently known bugs
- Pacman can sometimes enter a wall. He will not get stuck, as you can leave the wall, but ghosts can't catch him if he's in a wall
- Sometimes pacman can phase through ghosts, i.e. they do not kill him
- Pacman hugs walls visually,but that does not hinder his movement
- Pacman has a white square around him
- Memory leaks a bit, if you reset the game a lot memory usage will grow
- One of the ghosts phases through wall in the beginning of the game

### Required files by folder
- All CPP files from root/src
- all H files from root/headers
- GFX - root/external/gfx/src and root/external/gfx/include
- GLAD - root/external/Glad/stc and root/external/Glad/include (only glad.h needed)
- STB - root/external/stb and root/external/stb/include
- Imgui - root/external/imgui and files: imconfig.h, imgui.cpp, imgui.h, imgui_draw.cpp, imgui_impl_glfw.cpp, imgui_impl_glfw.h, imgui_impl_opengl3.cpp, imgui_impl_opengl3.h, imgui_internal.h, imgui_widgets.cpp. Basically all files from imconfig.h to imgui_widgets.cpp

### Required .cpp and .h files whole list
| File name | .h | .cpp |
| --------- | -- | ---- |
| entity | yes | yes |
| gfx | yes | yes |
| ghost | yes | yes |
| glad | yes | yes (.c) |
| glutil | yes | yes |
| imgui | yes | yes |
| imgui_draw | no | yes |
| imgui_impl_glfw | yes | yes |
| imgui_impl_opengl3 | yes | yes |
| imgui_widgets | no | yes |
| imconfig | yes | no |
| imgui_internal | yes | no |
| main | no | yes |
| manager | yes | yes |
| pacman  | yes | yes |
| pizza | yes | yes |
| stb_image_impl | no | yes |
| stb_image | yes | no |
| wall | yes | yes |
