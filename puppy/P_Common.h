#pragma once

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#define WORLD_VIEW_PROJ_UNIFORM_NAME "mWVP"
#define COLOR_TINT_UNIFORM_NAME "colorTint"
#define GENERAL_ALPHA_UNIFORM_NAME "gAlpha"
#define TEXTURE_OFFSET_UNIFORM_NAME "texOffset"
#define TEXTURE_BLEND_WEIGHT_UNIFORM_NAME "blendWeight"

#define SIZE_OF_TEXTURED_VERTEX 20
#define SIZE_OF_NORMAL_VERTEX 32
#define SIZE_OF_PARTICLE_VERTEX 36
#define SIZE_OF_GLFLOAT 4
#define SIZE_OF_GLSHORT 2

#define MAX_BLEND_TEXTURES 4
#define SAMPLER2D_NAME "tex"

#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include "util\MathUtil.h"
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace puppy
{	
	enum ShaderType { 
		//misc
		sprite, particles, basic, billboarded_u_scale, basic_directional_light, solid_color, solid_color_directional_light, healthbar,

		//Texture blended
		texture_blend_zero, texture_blend_one = texture_blend_zero+1, texture_blend_two = texture_blend_one+1, texture_blend_three = texture_blend_two+1, texture_blend_four=texture_blend_three+1, 

		//Texture blended, with point light
		texture_blend_zero_point_light, texture_blend_one_point_light = texture_blend_zero_point_light + 1, 
		texture_blend_two_point_light = texture_blend_one_point_light + 1, texture_blend_three_point_light = texture_blend_two_point_light + 1, 
		texture_blend_four_point_light = texture_blend_three_point_light + 1,

		//alpha test
		alphaTest, point_light_alphaTest, billboarded_colorTint_alphaTest, colorTint_alphaTest, gAlpha_alphaTest,

		SHADERTYPE_MAX = colorTint_alphaTest};

	enum VertexType { textured, normal};

	struct TexturedVertex
	{
		GLfloat x, y, z;	//Coords
		GLfloat u, v;		//uvs
	};

	struct NormalVertex
	{
		GLfloat x, y, z;	// Coords
		GLfloat nx, ny, nz;	// Normals
		GLfloat u, v;		// uvs
	};

	struct ParticleVertex
	{
		GLfloat x, y, z;	// Coords
		GLfloat u, v;		// uvs
		GLfloat r, g, b, a; // Tint
	};
}