#pragma once

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#define WORLD_VIEW_PROJ_UNIFORM_NAME "mWVP"
#define COLOR_TINT_UNIFORM_NAME "colorTint"

#define SIZE_OF_TEXTURED_VERTEX 20
#define SIZE_OF_NORMAL_VERTEX 32
#define SIZE_OF_PARTICLE_VERTEX 36
#define SIZE_OF_GLFLOAT 4
#define SIZE_OF_GLSHORT 2

#define PI 3.14159265359
#define DEG_TO_RAD_FACTOR 0.01745329251


#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace puppy
{
	enum ShaderType { basic, sprite, alphaTest, particles, colorTint_alphaTest, SHADERTYPE_MAX = colorTint_alphaTest };
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