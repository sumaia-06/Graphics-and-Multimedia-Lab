# Visualize

https://github.com/user-attachments/assets/db3a9677-60bf-4e67-b2d4-eb4c53d2e7f5


# Setup

## 1.  Windows ##

   * ### Download glfw libray from https://www.glfw.org/download.html. Download *64-bit Windows binaries* from *Windows pre-compiled binaries*. ###  
   * ### Create **build** and **lib** folder in Code Repo. Put *glfw3.dll* from *lib-mingw-w64* folder of glfw library to **build** and **lib** folder.  ###
   * ### For C++ compiler and make, Download MSYS2 Package Manager from https://www.msys2.org/ . ###  
   * ### Run following commands in MSYS2 terminal: ```pacman -S base-devel``` and ```pacman -S gcc``` . ### 
   * ### add your bin folder (which includes g++.exe and make.exe) PATH (C:\msys64\usr\bin) of msys64 installation directory in your environment variable.
   * ### Run ```make win``` in Terminal. ###
   * ### ```.exe``` file will be in **build** folder. ###
   * ### if your code does not run, then you have to check openGL version by installing GLview from http://www.realtech-vr.com/home/glview . If your openGL version is below 3.3, then update windows. ### 
​
## 2. Linux ##

   * ### Run following command in Terminal:  ```sudo apt-get install libglfw3-dev``` ###  
   * ### Create **build** and **lib** folder in Code Repo. ###
   * ### Run ```make linux``` in terminal. ###
   * ### executable file will be in **build** folder. ###


   # 🎮 Jumping Jhapak (OpenGL Game)

A simple 2D endless-jump style game built using **OpenGL (GLFW + GLAD)** and **C++**.  
The player controls a small star-like character that must avoid moving obstacles and survive as long as possible to increase score.

---

## 🧠 Features

- Smooth real-time animation using OpenGL
- Gravity-based jumping physics
- Randomized moving obstacles
- Score system with increasing difficulty
- Collision detection (Game Over system)
- Keyboard + mouse input support
- Restart and quit functionality

---

## 🕹️ Controls

| Key / Input | Action |
|-------------|--------|
| `↑ Arrow`   | Jump |
| `Left Click` | Jump |
| `R`         | Restart game |
| `Q`         | Quit game |

---

## 📦 Requirements

Make sure you have the following installed:

- C++ compiler (GCC / MSVC / Clang)
- GLFW
- GLAD
- OpenGL (3.3 Core Profile)
- GLM

---

## 🏗️ Build Instructions

### 🔧 Using g++ (Example)

```bash
g++ main.cpp glad.c -o game -lglfw -lGL -ldl -lX11 -lpthread

