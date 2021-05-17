#version 330 core
layout (location = 0) in vec3 position; // position变量的属性位置值为0
layout (location = 1) in vec3 color; // color变量的属性位置值是1
out vec4 vertexColor; // 为片段着色器指定一个颜色输出

uniform vec3 offset;

void main()
{
    gl_Position = vec4(position + offset, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    vertexColor = gl_Position; // 输出颜色是从顶点数据那里获得的颜色
}