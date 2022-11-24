#type vertex
layout(location = 0) in vec3 a_Position; // λ�ñ���������λ��ֵΪ0

uniform mat4 u_ViewProjection;
uniform vec3 u_color;

out vec3 v_color;

void main()
{
	v_color = u_color;
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