#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Rectangle
{
public:
	float vertices[12] = {
	0.5f, 0.5f, 0.0f,   // срио╫г
	0.5f, -0.5f, 0.0f,  // сроб╫г
	-0.5f, -0.5f, 0.0f, // вСоб╫г
	-0.5f, 0.5f, 0.0f   // вСио╫г
	};
	unsigned int rectangleIndices[6] = {
		0, 1, 3,
		1, 2, 3
	};

public:
	void RenderRectangle(const unsigned int* VAO, const unsigned int* VBO, const unsigned int* EBO);
};