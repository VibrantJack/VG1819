#version 150
in vec2 v_uv1;

uniform sampler2D tex;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

uniform float blendWeight0;
uniform float blendWeight1;
uniform float blendWeight2;
uniform float blendWeight3;

out vec4 PixelColor;

void main()
{
	vec4 firstTex = texture(tex, v_uv1);
	vec4 secondTex = texture(tex1, v_uv1);
	vec4 thirdTex = texture(tex2, v_uv1);
	vec4 fourthTex = texture(tex3, v_uv1);
	
	firstTex *= blendWeight0;
	secondTex *= blendWeight1;
	thirdTex *= blendWeight2;
	fourthTex *= blendWeight3;
	
	PixelColor = firstTex + secondTex + thirdTex + fourthTex;
}
