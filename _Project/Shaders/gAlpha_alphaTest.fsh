#version 150
in vec2 v_uv1;

uniform sampler2D tex;
uniform float gAlpha;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(tex, v_uv1);
	PixelColor.a = PixelColor.a * gAlpha;
	if( PixelColor.a < 0.01 )
		discard;
}