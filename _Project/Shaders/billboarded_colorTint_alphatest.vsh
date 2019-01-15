#version 150

uniform mat4 mView;
uniform mat4 mViewProj;
uniform vec3 centerPos;
uniform vec2 size;

in vec4 a_position;
in vec2 a_uv1;
out vec2 v_uv1;

void main()
{
    vec3 camRight = vec3(mView[0][0], mView[1][0], mView[2][0]);
	vec3 camUp = vec3(mView[0][1], mView[1][1], mView[2][1]);
	
	vec4 billboardedPos = vec4(centerPos + (camRight * a_position.x * size.x) + (camUp * a_position.y * size.y), a_position.w);
	
    gl_Position = mViewProj * billboardedPos;
	v_uv1 = a_uv1;
}
