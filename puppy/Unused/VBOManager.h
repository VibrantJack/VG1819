#pragma once

//-----------------------------------------------------------------------------
// File:			VBOManager.h
// Original Author:	Callum MacKenzie
//
// Class that handles the binding of buffers
// 
//-----------------------------------------------------------------------------

#include <map>
#include "../P_Common.h"

namespace puppy
{

	//Could be a singleton instead of static
	class VBOManager
	{
	private:
		static std::map<const int, const GLuint*> sm_boundBuffer;
		static std::map<const int, bool> sm_enabledBuffer;

		VBOManager();
	public:
		static void enable(const GLuint* p_buffer, const int* p_place, const int p_dimensions, const int p_type);
		static void bind(const GLuint* p_buffer, const int* p_place);
		static void removeAll();
	};
}