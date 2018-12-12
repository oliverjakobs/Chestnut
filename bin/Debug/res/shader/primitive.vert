#version 330

layout(location = 0) in vec2 v_position;
layout(location = 1) in vec4 v_color;

uniform mat4 view;
out vec4 f_color;

void main(void)
{
	gl_Position = view * vec4(v_position, 0.0f, 1.0f);
	f_color = v_color;
}