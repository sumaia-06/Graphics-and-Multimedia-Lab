## Assignment Objective
Create a cyan-colored window with the user's **full name as the window title**.  
When the user presses the keyboard key corresponding to the **first letter of the name**, the window should close.

---

## Technologies Used
- **C++**
- **OpenGL 3.3 Core Profile**
- **GLFW** (Window & Input Handling)
- **GLAD** (OpenGL Function Loader)

## Window Details
- **Window Title:** `Sumaia Bintey Ismail (0432320005101103)`
- **Window Size:** 800 × 600
- **Background Color:** Cyan
- **Exit Key:** `S`

### Windows (MinGW / MSYS2)
```bash
g++ main.cpp -o app -lglfw3 -lopengl32 -lgdi32
