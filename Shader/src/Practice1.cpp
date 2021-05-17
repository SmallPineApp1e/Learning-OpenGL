#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // 创建顶点缓冲对象
    glGenBuffers(1, &VBO);
    // 创建顶点数组对象
    glGenVertexArrays(1, &VAO);
    // 创建索引缓冲对象
    glGenBuffers(1, &EBO);

    float vertices[18] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下角
         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下角
         0.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // 正上角
    };

    // 编译顶点着色器和片段着色器
    Shader shader("shader/triangle.vert", "shader/triangle.frag");

    // 一直渲染屏幕，直到用户退出程序
    while (!glfwWindowShouldClose(window))
    {
        // 检测用户输入
        processInput(window);

        /*一套绘制流程*/
        // 1. 绑定顶点数组对象
        glBindVertexArray(VAO);
        // 2. 把顶点数组复制到顶点缓冲中供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 3. 设置顶点属性指针，让OpenGL知道如何这些顶点的属性布局（pos, color, normal···）
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); // 位置属性
        // 参数解释：
        // 1. 绑定着色器的属性位置，就是 layout (location = ?)
        // 2. 指定该属性有多少个值，颜色color是vector3，所以有3个值
        // 3. 每个属性值的数据类型是什么，color的每个值都是 float 类型
        // 4. 是否启动正规化，如果填入True则会将坐标映射到[0, 1]的正方体，就是一个投影矩阵的效果
        // 5. 属性值之间在数组上的偏移字节数，point(vec3f pos, vec3f color)，所以每个属性颜色值之间都隔了6个float字节
        // 6. 第一个属性值在数组上距离起始位置的偏移字节数，由于数组第一个元素的前3个float是pos，后3个float才是颜色，所以起始color偏移了12个字节
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); // 颜色属性
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // 4. 绘制物体
        shader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

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