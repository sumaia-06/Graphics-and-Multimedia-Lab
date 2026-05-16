#include "glad.h"
#include "glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <cstdlib>  // For rand() function
#include <ctime>    // For srand() function

const char *vertexShaderSource ="#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//game variables
float starY     = 0.0f;
float starVelY  = 0.0f;
bool  onGround  = true;
bool  gameOver  = false;
int   score     = 0;
bool  scored    = false;
// frozen variable 
float frozenXOffset  = 0.0f;
float frozenRedValue = 0.5f;

// random movement variables
float rectX     =  1.5f;    // Starting x position (off-screen to the right)
float rectDir   = -1.0f;    // -1 = left, +1 = right
float rectSpeed =  0.8f;

const float GRAVITY    = -3.5f;
const float JUMP_FORCE =  2.2f;
const float GROUND     =  0.0f;

int main()
{
    srand((unsigned int)time(0)); // random seed

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Jumping Jhapak | Score: 0", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Obstacle rectangle vertices
    float vertices[] = {
         0.5f,-0.5f,0.0f,
         0.5f,-0.8f,0.0f,
         0.45f,-0.8f,0.0f,

         0.5f,-0.5f,0.0f,
         0.45f,-0.8f,0.0f,
         0.45f,-0.5f,0.0f
    };

    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // Star vertices
    float vertices1[] = {
        0.05f,-0.7f,0.0f,
        -0.05f,-0.7f,0.0f,
        0.0f,-0.61f,0.0f,

        0.05f,-0.65f,0.0f,
        -0.05f,-0.65f,0.0f,
        0.0f,-0.74f,0.0f
    };

    unsigned int VAO1,VBO1;
    glGenVertexArrays(1,&VAO1);
    glGenBuffers(1,&VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO1);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // Ground vertices
    float groundVerts[] = {
        -1.0f, -0.8f, 0.0f,
         1.0f, -0.8f, 0.0f
    };
    unsigned int VAO2, VBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVerts), groundVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    double lastTime = glfwGetTime();

    while(!glfwWindowShouldClose(window))
    {
        double now = glfwGetTime();
        float dt = (float)(now - lastTime);
        lastTime = now;

        processInput(window);

        if (!gameOver)
        {
            // rectangle linear movement
            rectX += rectDir * rectSpeed * dt;

            // If it goes outside the screen, it will reappear again from a random direction
            if (rectX > 1.6f || rectX < -1.6f)
            {
                scored = false; // new round, score reset
                int randDir = rand() % 2;
                if (randDir == 0) {
                    rectX   =  1.6f;  // from right side
                    rectDir = -1.0f;
                } else {
                    rectX   = -1.6f;  // from left side
                    rectDir =  1.0f;
                }
                rectSpeed += 0.05f; // faster each round
            }

            // Update frozen variables for rendering
            frozenXOffset  = rectX;
            frozenRedValue = (float)(sin(glfwGetTime()) / 2.0f + 0.5f);

            // Gravity
            starVelY += GRAVITY * dt;
            starY    += starVelY * dt;

            if (starY <= GROUND) {
                starY    = GROUND;
                starVelY = 0.0f;
                onGround = true;
            }

            // Score count
            if (!scored) {
                if (rectDir < 0 && (frozenXOffset + 0.5f) < -0.05f) {
                    score++;
                    scored = true;
                    std::string title = "Jumping Jhapak | Score: " + std::to_string(score);
                    glfwSetWindowTitle(window, title.c_str());
                    std::cout << "Score: " << score << std::endl;
                }
    
                if (rectDir > 0 && (frozenXOffset + 0.45f) > 0.05f) {
                    score++;
                    scored = true;
                    std::string title = "Jumping Jhapak | Score: " + std::to_string(score);
                    glfwSetWindowTitle(window, title.c_str());
                    std::cout << "Score: " << score << std::endl;
                }
            }

            // Collision
            float rectLeft   = frozenXOffset + 0.45f;
            float rectRight  = frozenXOffset + 0.5f;
            float rectTop    = -0.5f;
            float rectBottom = -0.8f;

            float starLeft   = -0.05f;
            float starRight  =  0.05f;
            float starTop    =  starY - 0.61f;
            float starBottom =  starY - 0.74f;

            bool xOverlap = starRight > rectLeft && starLeft < rectRight;
            bool yOverlap = starTop   > rectBottom && starBottom < rectTop;

            if (xOverlap && yOverlap) {
                gameOver = true;
                std::cout << "GAME OVER! Final Score: " << score << std::endl;
                std::string title = "GAME OVER! Score: " + std::to_string(score) + " |  R to reset | Press J to quit ";
                glfwSetWindowTitle(window, title.c_str());
            }
        }

        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        int colorLoc     = glGetUniformLocation(shaderProgram,"ourColor");
        int transformLoc = glGetUniformLocation(shaderProgram,"transform");

        // Obstacle Rectangle
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform,glm::vec3(frozenXOffset,0.0f,0.0f));
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform));
        glUniform4f(colorLoc,1.0f,frozenRedValue,frozenRedValue,1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,6);

        // Player Star
        glm::mat4 transform1 = glm::mat4(1.0f);
        transform1 = glm::translate(transform1, glm::vec3(0.0f, starY, 0.0f));
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform1));
        if (gameOver)
            glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
        else
            glUniform4f(colorLoc,0.0f,1.0f,1.0f,1.0f);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES,0,6);

        // Ground Line
        glm::mat4 identity = glm::mat4(1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(identity));
        glUniform4f(colorLoc, 0.8f, 0.8f, 0.8f, 1.0f);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);  glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO1); glDeleteBuffers(1,&VBO1);
    glDeleteVertexArrays(1,&VAO2); glDeleteBuffers(1,&VBO2);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        // J = quit
        if (key == GLFW_KEY_J)
            glfwSetWindowShouldClose(window, true);

        // R = reset
        if (key == GLFW_KEY_R)
        {
            starY          = 0.0f;
            starVelY       = 0.0f;
            onGround       = true;
            gameOver       = false;
            score          = 0;
            scored         = false;
            rectX          = 1.5f;
            rectDir        = -1.0f;
            rectSpeed      = 0.8f;
            frozenXOffset  = 0.0f;
            frozenRedValue = 0.5f;
            glfwSetWindowTitle(window, "Jumping Japak | Score: 0");
        }
      
        //Up Arrow = jump
        if (key == GLFW_KEY_UP)
            if (!gameOver && onGround) {
                starVelY = JUMP_FORCE;
                onGround = false;
            }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        if (!gameOver && onGround) {
            starVelY = JUMP_FORCE;
            onGround = false;
        }
}

void processInput(GLFWwindow *window)
{
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}
