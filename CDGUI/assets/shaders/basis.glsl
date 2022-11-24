#type vertex
layout(location = 0) in vec3 a_Position; // 位置变量的属性位置值为0
layout(location = 1) in vec3 a_color;

uniform mat4 u_ViewProjection;
out vec3 v_color;

void main()
{
	v_color = a_color;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;

in vec3 v_color;

void main()
{
	FragColor = vec4(v_color, 1.0f);
}