#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
			
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main() {
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core
			
in vec4 v_Color;

uniform vec4 u_Color;

layout(location = 0) out vec4 color;

void main() {
	color = u_Color;
}