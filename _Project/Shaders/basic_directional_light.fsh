#version 150

in vec2 v_uv1;
in vec3 v_normal;
in vec3 v_pixelPos;

uniform sampler2D tex;

uniform vec3 lightPos;
uniform vec3 lightDirectionalColor;
uniform vec3 lightAmbient;

uniform vec3 matAmbient;

out vec4 PixelColor;

void main()
{	
	// Ambient Lighting
	vec3 ambient = lightAmbient * matAmbient;
	
	// Directional lighting
	vec3 normal = normalize(v_normal);
	vec3 lightPos = normalize(lightPos - v_pixelPos);
	
	float angle = max(dot(normal, lightPos), 0);
	vec3 directional = angle * lightDirectionalColorColor;
	
	// Final colour
	PixelColor = texture(tex, v_uv1) * (ambient + directional);
}
