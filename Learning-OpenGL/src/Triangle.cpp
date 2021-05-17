#include "Triangle.h"

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

void Triangle::RenderTriangle(const unsigned int* VAO, const unsigned int* VBO, const unsigned int* EBO)
{
	// ���붥����ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// ������ɫ���������Ӷ�����ɫ����Ƭ����ɫ��
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// ����Ƿ����ӳɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader Program Linked Failed! " << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	/*һ�׻�������*/
	// 1. �󶨶����������
	glBindVertexArray(*VAO);
	// 2. �Ѷ������鸴�Ƶ����㻺���й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. ���ö�������ָ�룬��OpenGL֪�������Щ��������Բ��֣�pos, color, normal��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 4. ��������
	glUseProgram(shaderProgram);
	glBindVertexArray(*VAO);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}