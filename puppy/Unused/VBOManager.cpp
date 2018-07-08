#include "VBOManager.h"
#include <iostream>

namespace puppy
{
	std::map<const int, const GLuint*> VBOManager::sm_boundBuffer;
	std::map<const int, bool> VBOManager::sm_enabledBuffer;



	//I believe the below method is the biggest performance issue cause.
	//Would VAOs per object speed things up?  
	//
	//Objects could also change uv buffer data
	//once per frame instead of enabling per frame; but that sounds
	//slower to me by feeling.

	//(static)
	void VBOManager::enable(const GLuint* p_buffer, const int* p_place, const int p_dimensions, const int p_type)
	{
		if (VBOManager::sm_boundBuffer.find(*p_place) == VBOManager::sm_boundBuffer.end()) //If no buffer is bound
		{
			//Bind this buffer and enable
			glBindBuffer(GL_ARRAY_BUFFER, *p_buffer);
			glVertexAttribPointer(*p_place, p_dimensions, p_type, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(*p_place);

			//Add it to the map
			VBOManager::sm_boundBuffer.insert(std::make_pair(*p_place, p_buffer));
			VBOManager::sm_enabledBuffer.insert(std::make_pair(*p_place, true));
		}
		else
		{
			//Something is bound here, if it isn't this buffer -- bind it!
			if (VBOManager::sm_boundBuffer[*p_place] != p_buffer)
			{
				//and enable
				glBindBuffer(GL_ARRAY_BUFFER, *p_buffer);
				glVertexAttribPointer(*p_place, p_dimensions, p_type, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(*p_place);

				//Overwrite what is bound there
				VBOManager::sm_boundBuffer[*p_place] = p_buffer;
				VBOManager::sm_enabledBuffer[*p_place] = true;
			}
			else
			{
				//BUffer is bound, is it enabled?
				if (VBOManager::sm_enabledBuffer[*p_place] == false)
				{
					glVertexAttribPointer(*p_place, p_dimensions, p_type, GL_FALSE, 0, 0);
					glEnableVertexAttribArray(*p_place);

					//Set status to enabled
					VBOManager::sm_enabledBuffer[*p_place] = true;
				}
			}
		}
	}

	//static
	void VBOManager::bind(const GLuint* p_buffer, const int* p_place)
	{
		if (VBOManager::sm_boundBuffer.find(*p_place) == VBOManager::sm_boundBuffer.end()) //If no buffer is bound
		{
			//Bind this buffer
			glBindBuffer(GL_ARRAY_BUFFER, *p_buffer);
			//Add it to the map
			VBOManager::sm_boundBuffer.insert(std::make_pair(*p_place, p_buffer));
			VBOManager::sm_enabledBuffer.insert(std::make_pair(*p_place, false));
		}
		else
		{
			//Something is bound here, if it isn't this buffer -- bind it!
			if (VBOManager::sm_boundBuffer[*p_place] != p_buffer)
			{
				glBindBuffer(GL_ARRAY_BUFFER, *p_buffer);

				//Overwrite what is bound there
				VBOManager::sm_boundBuffer[*p_place] = p_buffer;
				VBOManager::sm_enabledBuffer[*p_place] = false;
			}
		}
	}

	//static
	void VBOManager::removeAll()
	{
		VBOManager::sm_boundBuffer.clear();
	}
}