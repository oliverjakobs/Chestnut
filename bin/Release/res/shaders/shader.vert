#version 330 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 uPosition;
uniform vec2 uTexPos;

out vec2 texCoord;

void main()
{
	gl_Position = view * model * vec4(vPosition, 0.0f, 1.0f);
	texCoord = uTexPos + vTexCoord;
}