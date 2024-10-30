// Based on templates from learnopengl.com
#define GLEW_STATIC
#define GLEW_BUILD



// Based on templates from learnopengl.com
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <cmath>

#include <iostream>
#include "Surface.h"
#include "Camera.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Light.h"
//#include <HitRecord.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
 float xoffset = 0; //translation
 float yoffset = 0; //translation
 //add zoffset?
 float xRot = 0;
 float zRot = 0;
 float rotMod = 0;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"void main()\n"
"{\n"
"   FragColor = texture(texture1, TexCoord);\n"
"}\n\0";

 bool keyPressed = false;
 bool colorChange = false;
 bool camKeyPresseed = false;
 bool perspective = false;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Display RGB Array", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
  //  glfwSetKeyCallback(window, keyCallBack);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // GLEW: load all OpenGL function pointers
    glewInit();

    // build and compile the shaders
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Create the image (RGB Array) to be displayed
    const int width = 512; // keep it in powers of 2!
    const int height = 512; // keep it in powers of 2!
    unsigned char image[width * height * 3];
   

    float Inf = std::numeric_limits<float>::infinity();
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 center2 = glm::vec3(100.0f, 100.0f, 0.0f);
    glm::vec3 center3 = glm::vec3(0.0f, -10050.0f, 0.0f);
    Sphere sphere(50.0f, center);
    Sphere sphere2(50.0f, center2);
    Sphere plane(10000.0f, center3);
    sphere.setColor(255, 0, 0);
    sphere2.setColor(0, 255, 0);
    plane.setColor(0, 255, 255);
    sphere.name = "s1";
    sphere2.name = "s2";


    std::vector<Sphere> spheres;
    spheres.push_back(sphere);
    spheres.push_back(sphere2);
    spheres.push_back(plane);

    glm::vec3 origin = glm::vec3(-100.0f, 0.0f, -20.0f); //origin of camera
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 1.0f); //where camera points: center of sphere (x direction
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float aspect_ratio = width / height;
    float fov = 90.f;  
    HitRecord rec;
    OrthographicCamera ortho_camera(origin, target, up, fov, aspect_ratio);
    PerspectiveCamera persp_camera(origin, target, up, fov, aspect_ratio);
    Light diffuseLight;
    Light specularLight;
    Ray lightRay(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //use these to move object around with keys (translation)
    
    //rotation movement

    //add offset for direction
  


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
     processInput(window);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int r = 0;
                int g = 0;
                int b = 0;
                int t = -1;
                int index = 0;
                float diffuse = 0;
                float specular = 0;
                glm::vec3 localNormal;

                glm::vec3 origin = glm::vec3((float)j - 256.0f + 0.5f + xoffset, (float)i - 256.0f + 0.5f + yoffset, -20.0f);
                glm::vec3 direction = glm::vec3((float)j - 256.0f + 0.5f + xoffset, (float)i - 256.0f + 0.5f + yoffset, -20.0f);
                if (perspective) {
                    Ray ray(glm::vec3(0.0f + xRot, 0.0f, 1.0f + zRot), direction);

                for (int k = 0; k < spheres.size(); k++) {
                    if (colorChange) {
                        spheres[k].setColor(255, 255, 255);
                    }
                    bool hit = spheres[k].Intersect(ray, spheres[k], normal);
                    if ((hit && t < spheres[k].t) || (hit && t == -1)) { //-1 mean no value checked
                        t = spheres[k].t; //updates t, holds closest pt to camera
                        index = k;
                        r = spheres[k].color.r;
                        g = spheres[k].color.g;
                        b = spheres[k].color.b;
                        //pass the index to each light func
                        //localNormal = normal;
                    }

                    //set base pts of objs and add offset when keys are pressed (add modifier to offset that depends on how close obj is to camera to create paralax effect - slower if closer)
                    
                }

                diffuse = diffuseLight.DiffuseLight(lightRay, spheres[index], t);
                specular = specularLight.SpecularLight(lightRay, spheres[index], t);
                

                
                int idx = (i * width + j) * 3;


                //draw white
            //ambient  = r*0.25f
                image[idx] = r * diffuse + specular + r * 0.15f;
                image[idx + 1] = g * diffuse + specular + g * 0.15f;
                image[idx + 2] = b * diffuse + specular + b * 0.15f;
              //  image[idx] = r * diffuse +  r * 0.25f;
                //image[idx + 1] = g * diffuse +  g * 0.25f;
                //image[idx + 2] = b * diffuse + b * 0.25f;

                /*else {
                    //draw black
                    image[idx] = 0;
                    image[idx + 1] = 0;
                    image[idx + 2] = 0;
                }
                */
                }
                else {
                    Ray ray(origin, glm::vec3(0.0f + xRot, 0.0f, 1.0f + zRot));
                    // Ray lightRay(origin, )
              // ray.origin = glm::vec3((float)j - 256.0f + 0.5f, (float)i - 256.0f + 0.5f, -20.0f);
               //ray.direction = glm::vec3(0.0f, 0.0f, 1.0f);
             //  Ray ray = ortho_camera.GetRay(i, j, width, height);



                    for (int k = 0; k < spheres.size(); k++) {
                        if (colorChange) {
                            spheres[k].setColor(255, 255, 255);
                        }
                        bool hit = spheres[k].Intersect(ray, spheres[k], normal);
                        if ((hit && t < spheres[k].t) || (hit && t == -1)) { //-1 mean no value checked
                            t = spheres[k].t; //updates t, holds closest pt to camera
                            index = k;
                            r = spheres[k].color.r;
                            g = spheres[k].color.g;
                            b = spheres[k].color.b;
                            //pass the index to each light func
                            //localNormal = normal;
                        }

                        //set base pts of objs and add offset when keys are pressed (add modifier to offset that depends on how close obj is to camera to create paralax effect - slower if closer)
                        //extra credit (change color based on keypress)
                    }

                    diffuse = diffuseLight.DiffuseLight(lightRay, spheres[index], t);
                    specular = specularLight.SpecularLight(lightRay, spheres[index], t);


                    // bool hit2 = sphere2.Intersect(ray, 0, Inf, sphere2);
                    // std::cout << hit << std::endl;
                    int idx = (i * width + j) * 3;


                    //draw white
                //ambient  = r*0.25f
                    image[idx] = r * diffuse + specular + r * 0.15f;
                    image[idx + 1] = g * diffuse + specular + g * 0.15f;
                    image[idx + 2] = b * diffuse + specular + b * 0.15f;
                    //  image[idx] = r * diffuse +  r * 0.25f;
                      //image[idx + 1] = g * diffuse +  g * 0.25f;
                      //image[idx + 2] = b * diffuse + b * 0.25f;
                }
            }
        }

        unsigned char* data = &image[0];
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        // input
        // -----
        

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        yoffset += 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        yoffset -= 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xoffset -= 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xoffset += 10.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        rotMod -= 10;
        xRot = cos(rotMod);
        zRot = sin(rotMod);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << colorChange << std::endl;
        rotMod += 10;
        xRot = cos(rotMod);
        zRot = sin(rotMod);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !keyPressed) {
        //std::cout << colorChange << std::endl;
        keyPressed = !keyPressed;
        colorChange = true;
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

void keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_UP :
            yoffset +=10.0f;
        case GLFW_KEY_DOWN:
            yoffset -= 10.0f;
        case GLFW_KEY_RIGHT:
            xoffset += 10.0f;
        case GLFW_KEY_LEFT:
            xoffset -= 10.0f;
        case GLFW_KEY_A:
            rotMod -= 10;
            xRot = cos(rotMod);
            zRot = sin(rotMod);
        case GLFW_KEY_D:
            rotMod += 10;
            xRot = cos(rotMod);
            zRot = sin(rotMod);
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !keyPressed) {
            std::cout << colorChange << std::endl;
            keyPressed = !keyPressed;
            colorChange = true;
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !camKeyPresseed) {
            camKeyPresseed = !camKeyPresseed;
            perspective = true;
        }

    }
   // std::cout << yoffset << std::endl;
}