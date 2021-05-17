#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Triangle.h"
#include "Rectangle.h"

class WinApp
{
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
public:
	WinApp();
	int StartOpenGL();
private:
	std::unique_ptr<Triangle> triangle;
	std::unique_ptr<Rectangle> rectangle;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};