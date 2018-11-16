#version 150
in vec2 v_uv1;

uniform sampler2D tex;
uniform sampler2D tex1;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(tex, v_uv1);
	PixelColor += texture(tex1, v_uv1);
}
