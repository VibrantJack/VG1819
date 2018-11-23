#version 150
uniform mat4 mWVP;

in vec4 a_position;
in vec4 a_color;
in vec2 a_uv1;

out vec2 v_uv1;
out vec4 v_color;

void main()
{
    gl_Position = mWVP * a_position;
	v_uv1 = a_uv1;
	v_color = a_color;
}
