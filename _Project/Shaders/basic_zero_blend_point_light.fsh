#version 150

in vec3 v_normal;
in vec3 v_pixelPos;
in vec2 v_uv1;

uniform sampler2D tex;
uniform float blendWeight0;

// Lights

uniform vec3 lightPos;
uniform vec4 lightDiffuse;
uniform vec4 lightAmbientColor;
uniform vec3 lightAttenuation;
uniform float lightRange;

// material
uniform vec4 matAmbient;
uniform vec4 matDiffuse;

out vec4 PixelColor;

void main()
{
	// ---- Lighting -----
	vec4 lightOut;
	
	vec4 ambient = lightAmbientColor * matAmbient;
	
	vec3 lightDir = lightPos - v_pixelPos;
	float lightDist = length(lightDir);
	
	//Point lighting

	if(lightDist < lightRange)
	{
		//normalizing
		vec3 normal = normalize(v_normal);
		lightDir /= lightDist;
		
		vec4 diffuse = matDiffuse * lightDiffuse * max(0.0, dot(normal, lightDir));
		lightOut = clamp(ambient + diffuse, 0, 1);
		
		//attenuation
		float atten = 1.0 / dot(lightAttenuation, vec3(1.0, lightDist, lightDist*lightDist));
		
		lightOut *= atten;
		
		lightOut += ambient;
		
		//set alpha to 1.0
		lightOut.w = 1.0;
	}
	else
	{
		lightOut = ambient;
	}
	
	// Blending
	vec4 firstTex = texture(tex, v_uv1);
	
	firstTex *= blendWeight0;
	
	PixelColor = firstTex;
	PixelColor *= lightOut;
}
