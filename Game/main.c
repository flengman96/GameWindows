#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <cglm.h>   /* for library call (this also includes cglm.h) */

#include "triangle.h"
#include "menu.h"
#include "texture.h"
#include "initShaders.h"
#include "vertexCoords.h"

/*
//  TODO:
//  1. Build Menu/ Decide top, bottom, left or right
//
//
//
//
//
                                    */
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"   gl_Position = model * vec4(aPos,1);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
triangle tri;
// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1000;
mat4 projection = GLM_MAT4_IDENTITY_INIT;
//mat4 model = GLM_MAT4_IDENTITY_INIT;
mat4 lookAt = GLM_MAT4_IDENTITY_INIT;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // What does this do?
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Initialise and compile the Shaders
    int myProgram = initShaders(vertexShaderSource, fragmentShaderSource);
   // unsigned int* VAO, * VBO, * EBO;

    unsigned int * VAO = malloc(sizeof(unsigned int) * 1);
    unsigned int* VAO2 = malloc(sizeof(unsigned int) * 1);
    unsigned int * VBO = malloc(sizeof(unsigned int) * 1);
    unsigned int * EBO = malloc(sizeof(unsigned int) * 1);
    
    vec3 eye = { 0, 0, 1 };
    vec3 center = { 0, 0, 0 };
    vec3 up = { 0, 1, 0 };
    glm_lookat(eye, center, up, lookAt);

    tri.one.x = 0.5f;
    tri.one.y = 0.5f;
    tri.one.z = 0.0f;
    tri.two.x = 0.5f;
    tri.two.y = -0.5f;
    tri.two.z = 0.0f;
    tri.three.x = 0.0f;
    tri.three.y = 0.5f;
    tri.three.z = 0.0f;
    // Send the projection matrix to the shader
   
    //drawTriangle(VAO, VBO, EBO, myProgram);

    //unsigned int texture1 = initTexture(myProgram, "C:\\Users\\scomi\\Desktop\\tex3.jpg");
    //unsigned int texture0 = initTexture(myProgram, "C:\\Users\\scomi\\Desktop\\tex.jpg");
    
    
    //glUniform1i(glGetUniformLocation(myProgram, "texture1"), 0);
   
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    //glUseProgram(myProgram); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    //glUniform1i(glGetUniformLocation(myProgram, "texture1"), 0);
    // render loop
    // -----------
    vec3 newLoc = { 0.0f, 0.0f, -0.5f};
    //glm_rotate_z(model, 270.0f, model);
    //glm_translate(model, newLoc);
   //glm_ortho(-(2.0f), 2.0f, 2.0f, -2.0f, -1.0f, 1.0f, projection);
 
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
       // glUniformMatrix4fv(glGetUniformLocation(myProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        

       
       // glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture1);
        //glBindTexture(GL_TEXTURE_2D, texture1);
        // render container
        //glBindVertexArray(VAO); 
        //glBindVertexArray(VAO); 
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, texture0);
        
       // triangle tri;
       
        
        drawTriangle(tri, myProgram);

   
       // initMenu(myProgram);
        //glUniformMatrix4fv(glGetUniformLocation(myProgram, "view"), 1, GL_FALSE, &lookAt[0][0]);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        tri.one.x += -0.1f;
        tri.one.y += -0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        tri.one.x += 0.1f;
        tri.one.y += 0.1f;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double x;
        double y;
        double modelX = getModelX();
        double modelY = getModelY();

        // Get current Object in use Somehow

        glfwGetCursorPos(window, &x, &y);
       // printf("\n x: %lf, y: %lf\n", x, y);
        if (x == 0.000000f) {
            x = (double)0.000001f;
        }
        else if (y == 0.000000f) {
            y = (double)0.000001f;
        }

        else if (modelX == 0.000000f) {
            modelX = 0.000001f;
        }
        else if (modelY == 0.000000f) {
            modelY = 0.000001f;
        }
        // upto 800. so range [1600, 800] / 1600 * -2 = [-1, -1]
        // No values between [0, -1]
        if (x <= 800) {
            //printf("\nmodel: %lf, position: %lf\n ", model[3][0], (((800 - x) / 1600)) * -2);
            x = (double)(((800 - x) / 800)) * -1;
        }
        else {
            // > 800
            x = (double)((x - 800) / 800) * 1;
           // printf("\nx: %lf\n ", x);
        }
        if (y <= 500) {
            y = (double)(((500 - y) / 500)) * 1;
           // printf("\ny: %lf\n ", y);
        }
        else {
            y = (double)((y - 500) / 500) * -1;
           // printf("\ny: %lf\n ", y);
        }
        setModel((float)x, (float)y);
        //model[3][0] = (float)x;
        //model[3][1] = (float)y;
        return;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}