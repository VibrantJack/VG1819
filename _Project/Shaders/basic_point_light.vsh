#version 150
uniform mat4 mWVP;

in vec4 a_position;
in vec2 a_uv1;
in vec3 a_normal;

out vec2 v_uv1;

void main()
{
    gl_Position = mWVP * a_position;
	v_uv1 = a_uv1;
}
