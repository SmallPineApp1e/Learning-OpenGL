#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

uniform float alpha;

void main()
{
	color = texture(ourTexture1, vec2(TexCoord.x, 1.0f - TexCoord.y));
}