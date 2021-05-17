#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 color; // color����������λ��ֵ��1
layout (location = 2) in vec2 texCoord;

out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
    vertexColor = vec4(color, 1.0f); // �����ɫ�ǴӶ������������õ���ɫ
    TexCoord = texCoord;
}