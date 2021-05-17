#include <iostream>
#include "WinApp.h"
#include <memory>

WinApp::WinApp()
{
    triangle = std::make_unique<Triangle>();
    rectangle = std::make_unique<Rectangle>();
}

int WinApp::StartOpenGL()
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

    // 创建顶点缓冲对象
    glGenBuffers(1, &VBO);
    // 创建顶点数组对象
    glGenVertexArrays(1, &VAO);
    // 创建索引缓冲对象
    glGenBuffers(1, &EBO);

    // 一直渲染屏幕，直到用户退出程序
    while (!glfwWindowShouldClose(window))
    {
        // 检测用户输入
        processInput(window);

        // triangle->RenderTriangle(&VAO, &VBO, &EBO);
        // rectangle->RenderRectangle(&VAO, &VBO, &EBO);

        // 交换缓冲区输出在屏幕上（双缓冲原理）
        glfwSwapBuffers(window);
        // 检测触发事件（鼠标、键盘）并调用回调函数
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glfwTerminate();
    return 0;
}