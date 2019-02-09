#version 150
in vec2 v_uv1;

uniform sampler2D tex;
uniform float healthPercent;

out vec4 PixelColor;

void main()
{
	if(v_uv1.x > healthPercent)
	{
		PixelColor = vec4(1,0,0,1);
	}
	else
	{
		PixelColor = texture(tex, v_uv1);
	}
    
}
