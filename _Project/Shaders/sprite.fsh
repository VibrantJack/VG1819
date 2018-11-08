#version 150
in vec2 v_uv1;

uniform sampler2D tex;
uniform vec2 texOffset;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(tex, v_uv1+texOffset);
	if( PixelColor.a < 0.1 )
		discard;
}