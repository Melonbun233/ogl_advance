#version 330 core

uniform vec3 outline_color;
out vec4 FragColor;

void main()
{
	FragColor = vec4(outline_color, 1.0);
}