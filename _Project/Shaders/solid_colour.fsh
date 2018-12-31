#version 150
in vec2 v_uv1;

uniform vec4 colour;

out vec4 PixelColor;

void main()
{
    PixelColor = colour;
}
