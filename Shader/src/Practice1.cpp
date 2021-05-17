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

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // �������㻺�����
    glGenBuffers(1, &VBO);
    // ���������������
    glGenVertexArrays(1, &VAO);
    // ���������������
    glGenBuffers(1, &EBO);

    float vertices[18] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // ���½�
         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // ���½�
         0.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // ���Ͻ�
    };

    // ���붥����ɫ����Ƭ����ɫ��
    Shader shader("shader/triangle.vert", "shader/triangle.frag");

    // һֱ��Ⱦ��Ļ��ֱ���û��˳�����
    while (!glfwWindowShouldClose(window))
    {
        // ����û�����
        processInput(window);

        /*һ�׻�������*/
        // 1. �󶨶����������
        glBindVertexArray(VAO);
        // 2. �Ѷ������鸴�Ƶ����㻺���й�OpenGLʹ��
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 3. ���ö�������ָ�룬��OpenGL֪�������Щ��������Բ��֣�pos, color, normal��������
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); // λ������
        // �������ͣ�
        // 1. ����ɫ��������λ�ã����� layout (location = ?)
        // 2. ָ���������ж��ٸ�ֵ����ɫcolor��vector3��������3��ֵ
        // 3. ÿ������ֵ������������ʲô��color��ÿ��ֵ���� float ����
        // 4. �Ƿ��������滯���������True��Ὣ����ӳ�䵽[0, 1]�������壬����һ��ͶӰ�����Ч��
        // 5. ����ֵ֮���������ϵ�ƫ���ֽ�����point(vec3f pos, vec3f color)������ÿ��������ɫֵ֮�䶼����6��float�ֽ�
        // 6. ��һ������ֵ�������Ͼ�����ʼλ�õ�ƫ���ֽ��������������һ��Ԫ�ص�ǰ3��float��pos����3��float������ɫ��������ʼcolorƫ����12���ֽ�
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); // ��ɫ����
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // 4. ��������
        shader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

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