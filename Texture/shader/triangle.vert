#version 330 core
layout (location = 0) in vec3 position; // position变量的属性位置值为0
layout (location = 1) in vec3 color; // color变量的属性位置值是1
layout (location = 2) in vec2 texCoord;

out vec4 vertexColor; // 为片段着色器指定一个颜色输出
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    vertexColor = vec4(color, 1.0f); // 输出颜色是从顶点数据那里获得的颜色
    TexCoord = texCoord;
}