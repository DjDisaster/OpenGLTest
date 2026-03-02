#include <filesystem>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp    = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;

float sensitivity = 0.1f;

bool firstMouse = true;
double lastX = 960.0 / 2.0;
double lastY = 540.0 / 2.0;


static void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = (float)(xpos - lastX);
    float yoffset = (float)(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(front);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);

    // setup da glew
    if (glewInit() != GLEW_OK) {
        std::cout << "glew error: " << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    /*
    float positions[] = {
         -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    */

    // <3 AI for generating this shit
    float positions[] = {
        // Front (+Z)
        -0.5f,-0.5f, 0.5f,  0,0,1,  0,0,
         0.5f,-0.5f, 0.5f,  0,0,1,  1,0,
         0.5f, 0.5f, 0.5f,  0,0,1,  1,1,
        -0.5f, 0.5f, 0.5f,  0,0,1,  0,1,

        // Back (-Z)
        -0.5f,-0.5f,-0.5f,  0,0,-1, 0,0,
         0.5f,-0.5f,-0.5f,  0,0,-1, 1,0,
         0.5f, 0.5f,-0.5f,  0,0,-1, 1,1,
        -0.5f, 0.5f,-0.5f,  0,0,-1, 0,1,

        // Left (-X)
        -0.5f,-0.5f,-0.5f, -1,0,0,  0,0,
        -0.5f,-0.5f, 0.5f, -1,0,0,  1,0,
        -0.5f, 0.5f, 0.5f, -1,0,0,  1,1,
        -0.5f, 0.5f,-0.5f, -1,0,0,  0,1,

        // Right (+X)
         0.5f,-0.5f,-0.5f,  1,0,0,  0,0,
         0.5f,-0.5f, 0.5f,  1,0,0,  1,0,
         0.5f, 0.5f, 0.5f,  1,0,0,  1,1,
         0.5f, 0.5f,-0.5f,  1,0,0,  0,1,

        // Top (+Y)
        -0.5f, 0.5f,-0.5f,  0,1,0,  0,0,
         0.5f, 0.5f,-0.5f,  0,1,0,  1,0,
         0.5f, 0.5f, 0.5f,  0,1,0,  1,1,
        -0.5f, 0.5f, 0.5f,  0,1,0,  0,1,

        // Bottom (-Y)
        -0.5f,-0.5f,-0.5f,  0,-1,0, 0,0,
         0.5f,-0.5f,-0.5f,  0,-1,0, 1,0,
         0.5f,-0.5f, 0.5f,  0,-1,0, 1,1,
        -0.5f,-0.5f, 0.5f,  0,-1,0, 0,1,
    };

    unsigned int indices[] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        8,9,10, 10,11,8,
        12,13,14, 14,15,12,
        16,17,18, 18,19,16,
        20,21,22, 22,23,20
    };


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    VertexArray va;
    VertexBuffer vb(positions, 24 * 8 * sizeof(float));
    VertexBufferLayout layout;

    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

    float floorVerts[] = {
        -10.0f, -1.0f, -10.0f,  0,1,0,   0,0,
         10.0f, -1.0f, -10.0f,  0,1,0,   1,0,
         10.0f, -1.0f,  10.0f,  0,1,0,   1,1,
        -10.0f, -1.0f,  10.0f,  0,1,0,   0,1,
    };
    unsigned int floorIdx[] = { 0,1,2, 2,3,0 };

    VertexArray floorVA;
    VertexBuffer floorVB(floorVerts, 4 * 8 * sizeof(float));
    VertexBufferLayout floorLayout;
    floorLayout.Push<float>(3);
    floorLayout.Push<float>(3);
    floorLayout.Push<float>(2);
    floorVA.AddBuffer(floorVB, floorLayout);
    IndexBuffer floorIB(floorIdx, 6);

    IndexBuffer ib(indices, 36);

    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f),
        1920.0f / 1080.0f,
        0.1f,
        100.0f
    );

    Shader shader("../resources/shaders/Basic.shader");
    Texture texture("../resources/textures/frieren.jpeg");
    Texture white("../resources/textures/gray.png");


    shader.Bind();

    Renderer renderer;

    int frameCount = 0;
    float camSpeed = 2.5f;
    double lastFrame = glfwGetTime();
    double lastTime = glfwGetTime();

    glm::mat4 floorModel = glm::mat4(1.0f);


    while (!glfwWindowShouldClose(window)) {

        double currentFrame = glfwGetTime();
        float deltaTime = (float)(currentFrame - lastFrame);
        lastFrame = currentFrame;

        float velocity = camSpeed * deltaTime;

        glm::vec3 camRight = glm::normalize(glm::cross(camFront, camUp));

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camPos += camFront * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camPos -= camFront * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camPos -= camRight * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camPos += camRight * velocity;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camPos += camUp * velocity;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camPos -= camUp * velocity;

        glm::mat4 view = glm::lookAt(camPos, camPos + camFront, camUp);
        glm::mat4 model = glm::rotate(
            glm::mat4(1.0f),
            (float)glfwGetTime(),
            glm::vec3(0.5f, 1.0f, 0.0f)
        );

        glViewport(0, 0, 1920, 1080);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.Bind();

        // cube
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);

        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        renderer.draw(va, ib, shader);

        // floor
        glm::mat4 floorMVP = proj * view * floorModel;
        shader.SetUniformMat4f("u_MVP", floorMVP);

        white.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        renderer.draw(floorVA, floorIB, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double currentTime = glfwGetTime();
        frameCount++;

        if (currentTime - lastTime >= 10.0) {
            double fps = double(frameCount) / (currentTime - lastTime);
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
            lastTime = currentTime;
        }
    }
    glfwTerminate();
    return 0;
}
