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
    // ��ʼ��GLAD��������OpenGL�ĺ���ָ��
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // �����ӿڴ�С�������½�Ϊ(0, 0)�����Ͻ�Ϊ(width, height)
    glViewport(0, 0, 800, 600);
    // ע��ߴ�仯�ص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // �������㻺�����
    glGenBuffers(1, &VBO);
    // ���������������
    glGenVertexArrays(1, &VAO);
    // ���������������
    glGenBuffers(1, &EBO);

    // һֱ��Ⱦ��Ļ��ֱ���û��˳�����
    while (!glfwWindowShouldClose(window))
    {
        // ����û�����
        processInput(window);

        // triangle->RenderTriangle(&VAO, &VBO, &EBO);
        // rectangle->RenderRectangle(&VAO, &VBO, &EBO);

        // �����������������Ļ�ϣ�˫����ԭ��
        glfwSwapBuffers(window);
        // ��ⴥ���¼�����ꡢ���̣������ûص�����
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glfwTerminate();
    return 0;
}