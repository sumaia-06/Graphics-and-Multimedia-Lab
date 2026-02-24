## Assignment Objective
Draw **One Cyan Colored Star (built only with triangles)** with **yellow background** 

---

## Program Description
This program uses **OpenGL 3.3 Core Profile** with **GLFW** and **GLAD** to render five triangles on the screen.
- Both triangles are drawn using a **single VAO and VBO**
- Rendering is done using **vertex and fragment shaders**
- 
## Star Construction
- The star is constructed using **5 triangles**
- All vertices are manually defined in **Normalized Device Coordinates (NDC)**

## Geometry
The vertex buffer contains **15 vertices**, forming **5 triangles**:
Each triangle is defined using **three vertices**, and OpenGL renders them using:
- Rendering mode:  
  ```cpp
  glDrawArrays(GL_TRIANGLES, 0, 15);

## Rendering Details
- **Background Color:** Yellow  
- **Triangle Color:** Cyan  
- **Primitive Used:** `GL_TRIANGLES`  
- **Coordinate System:** Normalized Device Coordinates (−1 to +1)


