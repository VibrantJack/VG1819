#version 150
uniform mat4 world;
uniform mat4 proj;

in vec4 a_position;
in vec2 a_uv1;
out vec2 v_uv1;

void main()
{
    gl_Position = proj * world * a_position;
	v_uv1 = a_uv1;
}
