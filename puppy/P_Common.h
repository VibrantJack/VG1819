#pragma once

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#define WORLD_VIEW_PROJ_UNIFORM_NAME "mWVP"
#define COLOR_TINT_UNIFORM_NAME "colorTint"
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
	enum ShaderType { sprite, alphaTest, particles, basic, 
		texture_blend_zero, texture_blend_one = texture_blend_zero+1, texture_blend_two = texture_blend_one+1, texture_blend_three = texture_blend_two+1, texture_blend_four=texture_blend_three+1, 
		colorTint_alphaTest, SHADERTYPE_MAX = colorTint_alphaTest };

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