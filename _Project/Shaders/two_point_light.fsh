#version 150

// Light1 Info
uniform vec4 Light1Ambient;
uniform vec4 Light1Specular;
uniform vec4 Light1Diffuse;
uniform vec3 Light1Pos;
uniform vec3 Light1Attenuation;
uniform float Light1Range;

// Light2 Info
uniform vec4 Light2Ambient;
uniform vec4 Light2Specular;
uniform vec4 Light2Diffuse;
uniform vec3 Light2Pos;
uniform vec3 Light2Attenuation;
uniform float Light2Range;

// Material info
uniform vec4 MatAmbient;
uniform vec4 MatSpecular;
uniform vec4 MatDiffuse;

// texture(s)
uniform sampler2D texture1;

// Varyings
in vec3 v_normal;
in vec4 v_pos;
in vec2 v_uv1;

out vec4 PixelColor;

void main()
{
	vec3 n = normalize( v_normal );

	vec3 Light1Dir = Light1Pos - v_pos.xyz;
	vec3 Light2Dir = Light2Pos - v_pos.xyz;
	
	float distance1 = length(Light1Dir);
	float distance2 = length(Light2Dir);
	
	// Light1
	
	vec4 light1Out;
	
	if( distance1 < Light1Range )
	{
		// normalize it
		Light1Dir /= distance1;

		// Ambient
		vec4 ambient = MatAmbient * Light1Ambient;

		// Diffuse
		vec4 diffuse = MatDiffuse * Light1Diffuse * max(0.0,dot(n, Light1Dir));


		// Combine the components
		//vec4 Light1 = clamp(ambient + diffuse, 0, 1);
		vec4 Light1 = clamp(ambient + diffuse, 0, 1);
		
		// Attenuate the Light1
		float att = 1.0 / dot(Light1Attenuation, vec3(1.0, distance1, distance1*distance1));
		Light1 *= att;

		light1Out = vec4( Light1.rgb, 1.0);
	}
	else
	{
		light1Out = MatAmbient * Light1Ambient;
	}
	
	if( distance2 < Light2Range )
	{
		// normalize it
		Light2Dir /= distance2;

		// Ambient
		vec4 ambient = MatAmbient * Light2Ambient;

		// Diffuse
		vec4 diffuse = MatDiffuse * Light2Diffuse * max(0.0,dot(n, Light2Dir));

		// Combine the components
		//vec4 Light2 = clamp(ambient + diffuse, 0, 1);
		vec4 Light2 = clamp(ambient + diffuse, 0, 1);

		// Attenuate the Light2
		float att = 1.0 / dot(Light2Attenuation, vec3(1.0, distance2, distance2*distance2));
		Light2 *= att;

		PixelColor = texture(texture1, v_uv1) * (light1Out + vec4( Light2.rgb, 1.0));
	}
	else
	{
		PixelColor =  texture(texture1, v_uv1) * ((light1Out) + (MatAmbient * Light2Ambient));
	}
	
}
