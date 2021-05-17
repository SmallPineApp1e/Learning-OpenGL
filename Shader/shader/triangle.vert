#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 color; // color����������λ��ֵ��1
out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���

uniform vec3 offset;

void main()
{
    gl_Position = vec4(position + offset, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
    vertexColor = gl_Position; // �����ɫ�ǴӶ������������õ���ɫ
}