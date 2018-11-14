#version 150
in vec2 v_uv1;

uniform sampler2D tex;
uniform vec2 texOffset;

out vec4 PixelColor;

void main()
{
	vec2 offsetUV = v_uv1 + texOffset;
	
    PixelColor = texture(tex, offsetUV);
	
	if(PixelColor.a < 0.1)
		discard;
}