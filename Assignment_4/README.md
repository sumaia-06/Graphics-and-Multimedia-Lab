## Assignment Objective
Create an OpenGL program that draws a single triangle **Initially Colored Cyan** gradually animates and transitions to **Magenta** 

---


## Description

This project is an OpenGL program using GLFW and GLAD that renders a single triangle with animated color transitions and keyboard interaction.

The triangle starts with a color transition between **cyan** and **magenta**. Users can control the triangle color using keyboard inputs.

## Features

* Draws a single triangle using OpenGL.
* Smooth color animation between cyan and magenta.
* Temporary white color while holding the **W** key.
* Permanent red color when pressing the **R** key.
* Window title set to the student ID.
* Pressing the first letter of the user's name closes the window.

## Controls

| Key | Action                                   |
| --- | ---------------------------------------- |
| W   | Turns triangle white while holding       |
| R   | Turns triangle red permanently           |
| S   | Closes the window (first letter of name) |

## Requirements

To run this project, you need:

* C++ Compiler (GCC/MinGW or MSVC)
* OpenGL 3.3+
* GLFW Library
* GLAD Loader

## How to Run

1. Install GLFW and GLAD.
2. Compile the project:

```bash
g++ main.cpp -o triangle -lglfw -lglad -lopengl32
```

3. Run the executable:

```bash
./triangle
```

## Project Structure

* `main.cpp` → Main source code
* `glad.h` → OpenGL loader header
* `glfw3.h` → GLFW library header

## Output Behavior

* On startup, the triangle animates between cyan and magenta.
* Holding **W** changes the triangle to white.
* Releasing **W** resumes animation.
* Pressing **R** changes the triangle to red permanently.
* Pressing **S** closes the application.


