#version 330 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 mvp;

uniform vec2 uFramePos;

out vec2 texCoord;

void main()
{
	gl_Position = mvp * vec4(vPosition, 0.0f, 1.0f);
	texCoord = vTexCoord + uFramePos;
}