// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_ENGINE_TEXTURE
#define H_ENGINE_TEXTURE
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers              
#include <cassert>
//////////////////////////////////
// Project Headers
#include <glm\glm.hpp>
//////////////////////////////////
// Engine Headers           
//////////////////////////////////
// Engine Macro Includes    
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Macros           
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes
		
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class: pw::st::Texture
		// //////////////////////////////////////////////////
		// Purpose:
		//  Handles textures in opengl. 
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Texture {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a uninitialized texture. Will not draw.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture();
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a texture from data.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) BYTE* tex_data;
			// Purpose:
			//  The pixel data of the function in a specified
			//  format.
			// (2) uint32_t tex_width;
			// Purpose:
			//  The width of the texture in pixels.
			// (3) uint32_t tex_height;
			// Purpose:
			//  The height of the texture in pixels.
			// (4) int32_t internal_format;
			// Purpose:
			//  The internal format the pixel data is. When
			//  loading the texture using another function not
			//  from Pistonworks make sure to know the internal
			//  format of the data you are loading.
			// (5) int32_t format;
			// Purpose:
			//  The external format of the pixel data. On Windows
			//  it is BGRA usually. Most API's ignore windows 
			//  specific formats and load RGBA. Be careful. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture(BYTE* tex_data, uint32_t tex_width, uint32_t tex_height, int32_t internal_format, int32_t format);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a texture from data.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) BYTE* tex_data;
			// Purpose:
			//  The pixel data of the function in a specified
			//  format.
			// (2) uint32_t target;
			// Purpose:
			//  The type of OpenGL texture you want to create.
			//  Normally it is a GL_TEXTURE_2D.
			// (3) uint32_t tex_width;
			// Purpose:
			//  The width of the texture in pixels.
			// (4) uint32_t tex_height;
			// Purpose:
			//  The height of the texture in pixels.
			// (5) int32_t internal_format;
			// Purpose:
			//  The internal format the pixel data is. When
			//  loading the texture using another function not
			//  from Pistonworks make sure to know the internal
			//  format of the data you are loading.
			// (6) int32_t format;
			// Purpose:
			//  The external format of the pixel data. On Windows
			//  it is BGRA usually. Most API's ignore windows 
			//  specific formats and load RGBA. Be careful. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture(BYTE* tex_data, uint32_t target, uint32_t tex_width, uint32_t tex_height, int32_t internal_format, int32_t format);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a texture from data.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) PW_SRD_PTR(BYTE*) tex_data;
			// Purpose:
			//  The pixel data of the function in a specified
			//  format.
			// (2) uint32_t tex_width;
			// Purpose:
			//  The width of the texture in pixels.
			// (3) uint32_t tex_height;
			// Purpose:
			//  The height of the texture in pixels.
			// (4) int32_t internal_format;
			// Purpose:
			//  The internal format the pixel data is. When
			//  loading the texture using another function not
			//  from Pistonworks make sure to know the internal
			//  format of the data you are loading.
			// (5) int32_t format;
			// Purpose:
			//  The external format of the pixel data. On Windows
			//  it is BGRA usually. Most API's ignore windows 
			//  specific formats and load RGBA. Be careful. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture(PW_SRD_PTR(BYTE*) tex_data, uint32_t tex_height, uint32_t tex_length, int32_t internal_format, int32_t format);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::~Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates the texture memory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION ~Texture();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Texture::Bind
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Draws the texture to the screen.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) uint32_t unit;
			// Purpose:
			//  Usually 0. Binds the texture to a grouping to be
			//  rendered by OpenGL. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Bind(uint32_t unit);
			// //////////////////////////////////////////////////
			// CORE Function: Texture::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes the allocated memory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			uint32_t texture_id;

			uint32_t texture_width;
			uint32_t texture_height;
		};                  
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_TEXTURE