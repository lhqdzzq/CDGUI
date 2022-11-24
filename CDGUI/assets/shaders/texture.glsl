#type vertex
layout(location = 0) in vec3 a_Position; // 位置变量的属性位置值为0
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoord);
}