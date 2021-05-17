#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Triangle
{
public:
	float vertices[15] = {
	-1.0f, -0.5f, 0.0f,
	 0.0f, -0.5f, 0.0f,
	 -0.5f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	 1.0f, -0.5f, 0.0f
	};
	unsigned int indices[6] = {
		0, 1, 2,
		1, 4, 3
	};

public:
	void RenderTriangle(const unsigned int* VAO, const unsigned int* VBO, const unsigned int* EBO);
};