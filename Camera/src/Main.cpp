#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

float memoryAlpha = 0.0f;
// 按键数组
bool keys[1024];
bool firstMouse = true;
GLfloat deltaTime;
GLfloat lastFrameTime;
GLfloat MouseSensitivity = 0.1f;
GLfloat offsetX, offsetY;
GLfloat lastX = 400.0f, lastY = 300.0f;
GLfloat pitch = 0.0f, yaw = 0.0f;
GLfloat aspect = 45.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

void check_keys(Camera* camera, GLfloat deltaTime)
{
    if (keys[GLFW_KEY_W])
        camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) // 这个bool变量一开始是设定为true的
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    offsetX = xpos - lastX;
    offsetY = ypos - lastY;
    lastX = xpos;
    lastY = ypos;
    
    offsetX *= MouseSensitivity;
    offsetY *= MouseSensitivity;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (aspect >= 1.0f && aspect <= 45.0f)
        aspect -= yoffset;
    if (aspect <= 1.0f)
        aspect = 1.0f;
    if (aspect >= 45.0f)
        aspect = 45.0f;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 初始化GLAD用来管理OpenGL的函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 设置视口大小，从左下角为(0, 0)到右上角为(width, height)
    glViewport(0, 0, 800, 600);
    // 注册尺寸变化回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // 创建顶点缓冲对象
    glGenBuffers(1, &VBO);
    // 创建顶点数组对象
    glGenVertexArrays(1, &VAO);
    // 创建索引缓冲对象
    glGenBuffers(1, &EBO);

    float vertices[180] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
          glm::vec3(0.0f,  0.0f,  0.0f),
    };

    // 编译顶点着色器和片段着色器
    Shader shader("shader/triangle.vert", "shader/triangle.frag");
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0); // 位置属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); // 纹理坐标属性
    glEnableVertexAttribArray(1);

    // ============Texture1=============
    int width, height;
    GLuint texture;
    // 创建纹理对象
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 设置纹理的uv方向重复级别
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置纹理的mipmap级别以及两级之间的插值取值方法
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char* image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    
    // 摄像机
    Camera camera(cameraPos, cameraUp);

    // 一直渲染屏幕，直到用户退出程序
    while (!glfwWindowShouldClose(window))
    {
        // 检测触发事件（鼠标、键盘）并调用回调函数
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLfloat currFrameTime = glfwGetTime();
        deltaTime = currFrameTime - lastFrameTime;
        lastFrameTime = currFrameTime;
        
        check_keys(&camera, deltaTime);
        camera.ProcessMouseMovement(offsetX, offsetY, GL_TRUE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
        shader.Use();
        
        // 观察矩阵
        glm::mat4 viewMat = camera.GetViewMatrix();

        GLint view = glGetUniformLocation(shader.Program, "view");
        glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMat));

        glm::mat4 View2ProjectionMat = glm::mat4(1.0f);
        View2ProjectionMat = glm::perspective(aspect, (float)800 / (float)600, 0.1f, 100.f);
        GLint projection = glGetUniformLocation(shader.Program, "projection");
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(View2ProjectionMat));

        glBindVertexArray(VAO);
        GLint model = glGetUniformLocation(shader.Program, "model");
        for (GLuint i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
        {
            glm::mat4 Model2WorldMat = glm::mat4(1.0f);
            Model2WorldMat = glm::translate(Model2WorldMat, cubePositions[i]);
            Model2WorldMat = glm::rotate(Model2WorldMat, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            
            glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Model2WorldMat));
            glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float) / 5);
        }
        glBindVertexArray(0);
        GLint alpha = glGetUniformLocation(shader.Program, "alpha");
        glUniform1f(alpha, memoryAlpha);
        // 开启z值深度测试
        glEnable(GL_DEPTH_TEST);

        // 交换缓冲区输出在屏幕上（双缓冲原理）
        glfwSwapBuffers(window);

        offsetX = 0.0f, offsetY = 0.0f;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}