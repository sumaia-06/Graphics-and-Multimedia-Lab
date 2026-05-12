Overview

This project demonstrates basic 2D transformations and color animation in OpenGL using GLFW, GLAD, and GLM. A rectangle is created using two triangles and animated over time.

The rectangle performs the following operations:

Gradually changes color from red to white
Continuously magnifies (scales) with time
Continuously rotates in the XY plane
Technologies Used
OpenGL
GLFW
GLAD
GLM
C++
Features
1. Color Animation

The rectangle smoothly transitions between red and white using the sine function and shader uniforms.

float greenValue = (sin(timeValue) / 2.0 + 0.5);
glUniform4f(vertexColorLocation, 1.0f, greenValue, greenValue, 1.0f);
Color Transition
(1,0,0) → Red
(1,1,1) → White
2. Magnifying (Scaling)

The rectangle continuously increases and decreases in size over time.

float scaleFactor = sin(glfwGetTime()) * 0.5f + 1.0f;

transform = glm::scale(transform,
            glm::vec3(scaleFactor, scaleFactor, 1.0f));
Scaling Range
Minimum Scale = 0.5
Maximum Scale = 1.5
3. Rotation in XY Plane

The rectangle rotates continuously around the Z-axis.

transform = glm::rotate(transform,
            (float)glfwGetTime(),
            glm::vec3(0.0f, 0.0f, 1.0f));

Since rotation occurs around the Z-axis, the rectangle appears to rotate in the XY plane.

Vertex Shader

The vertex shader applies the transformation matrix to the rectangle vertices.

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0);\n"
    "}\0";
Fragment Shader

The fragment shader controls the animated color.

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";
Rectangle Construction

The rectangle is built using two triangles.

float vertices[] = {

     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,

     0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
Program Workflow
Initialize GLFW and GLAD
Create shaders
Create rectangle vertices
Configure VAO and VBO
Apply:
Color animation
Scaling transformation
Rotation transformation
Render the animated rectangle continuously
Output

The program displays:

A rotating rectangle
Continuous magnification effect
Smooth color transition from red to white
Conclusion

This project demonstrates the use of:

Shader uniforms
Transformation matrices
Scaling
Rotation
Time-based animation in OpenGL

It is a simple but effective example of combining multiple transformations and dynamic color effects in modern OpenGL.
