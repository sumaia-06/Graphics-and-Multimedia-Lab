## Assignment Objective
Draw **two obtuse triangles** at **two distant corners of the screen** using **Modern OpenGL**.  
The background color should be **orange**, and the triangles should be **cyan colored**.

---

## Program Description
This program uses **OpenGL 3.3 Core Profile** with **GLFW** and **GLAD** to render two obtuse triangles on the screen.

- One obtuse triangle is placed at the **top-right corner**
- Another obtuse triangle is placed at the **bottom-left corner**
- Both triangles are drawn using a **single VAO and VBO**
- Rendering is done using **vertex and fragment shaders**


## Technologies Used
- **C++**
- **OpenGL 3.3 (Core Profile)**
- **GLFW** – window creation and input handling
- **GLAD** – OpenGL function loader


## Rendering Details
- **Background Color:** Orange  
- **Triangle Color:** Cyan  
- **Primitive Used:** `GL_TRIANGLES`  
- **Coordinate System:** Normalized Device Coordinates (−1 to +1)


## Geometry
The vertex buffer contains **6 vertices**, forming **2 obtuse triangles**:
- Triangle 1 → Top-right corner
- Triangle 2 → Bottom-left corner

Each triangle is defined using **three vertices**, and OpenGL renders them using:
```cpp
glDrawArrays(GL_TRIANGLES, 0, 6);
