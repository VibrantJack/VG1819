#version 150

uniform mat4 mWVP;
uniform mat3 worldIT;

in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;

out vec2 v_uv1;
out vec3 v_normal;
out vec3 v_pixelPos;

void main()
{
    gl_Position = mWVP * a_position;
	v_uv1 = a_uv1;
	
	v_normal = worldIT * a_normal;
	v_pixelPos = vec3(worldIT * a_position.xyz);
}
