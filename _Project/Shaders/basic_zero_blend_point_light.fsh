#version 150

in vec2 v_uv1;

uniform sampler2D tex;

uniform float blendWeight0;

out vec4 PixelColor;

void main()
{
	vec4 firstTex = texture(tex, v_uv1);
	
	firstTex *= blendWeight0;
	
	PixelColor = firstTex;//vec4(v_uv1, 0, 1);
}
