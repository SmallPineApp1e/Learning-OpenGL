#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float memoryAlpha = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        memoryAlpha += 0.01f;
        memoryAlpha = memoryAlpha > 1.0f ? 1.0f : memoryAlpha;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        memoryAlpha -= 0.01f;
        memoryAlpha = memoryAlpha < 0.0f ? 0.0f : memoryAlpha;
    }
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

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // �������㻺�����
    glGenBuffers(1, &VBO);
    // ���������������
    glGenVertexArrays(1, &VAO);
    // ���������������
    glGenBuffers(1, &EBO);

    float vertices[32] = {
        // Positions          // Colors           // Texture Coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };
    unsigned int indices[6] = { 0, 1, 3, 1, 2, 3 };

    // ���붥����ɫ����Ƭ����ɫ��
    Shader shader("shader/triangle.vert", "shader/triangle.frag");
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0); // λ������
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); // ��ɫ����
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT))); // ������������
    glEnableVertexAttribArray(2);

    // ==========Texture1=========
    GLuint texture1;
    // �����������
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // ���������uv�����ظ�����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // ���������mipmap�����Լ�����֮��Ĳ�ֵȡֵ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    unsigned char* image1 = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image1);
    // ============Texture2=============
    GLuint texture2;
    // �����������
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // ���������uv�����ظ�����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // ���������mipmap�����Լ�����֮��Ĳ�ֵȡֵ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char* image2 = SOIL_load_image("doge.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image2);
    
    // һֱ��Ⱦ��Ļ��ֱ���û��˳�����
    while (!glfwWindowShouldClose(window))
    {
        // ��ⴥ���¼�����ꡢ���̣������ûص�����
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);
        shader.Use();
        // ����任����Ϊ��z����ʱ����ת90�Ȳ�����Ϊԭ����0.5��
        glm::mat4 transformMatrix = glm::mat4(1.0f);
        GLfloat time = glfwGetTime();
        GLfloat scaleFactor = sin(time) / 4;
        transformMatrix = glm::rotate(transformMatrix, glm::radians(time * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transformMatrix = glm::scale(transformMatrix, glm::vec3(scaleFactor + 0.5f, scaleFactor + 0.5f, 1.0f));
        GLint trans = glGetUniformLocation(shader.Program, "transformMatrix");
        glUniformMatrix4fv(trans, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        GLint alpha = glGetUniformLocation(shader.Program, "alpha");
        glUniform1f(alpha, memoryAlpha);

        // �����������������Ļ�ϣ�˫����ԭ��
        glfwSwapBuffers(window);
        // ����û�����
        processInput(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}