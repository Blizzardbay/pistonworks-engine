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
#include <freeimage\FreeImage.h>
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
			CLASS_FUNCTION Texture() = default;
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a texture from data.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) PW_BYTE* tex_data;
			// Purpose:
			//  The pixel data of the function in a specified
			//  format.
			// (2) PW_UINT tex_width;
			// Purpose:
			//  The width of the texture in pixels.
			// (3) PW_UINT tex_height;
			// Purpose:
			//  The height of the texture in pixels.
			// (4) PW_INT internal_format;
			// Purpose:
			//  The internal format the pixel data is. When
			//  loading the texture using another function not
			//  from Pistonworks make sure to know the internal
			//  format of the data you are loading.
			// (5) PW_INT format;
			// Purpose:
			//  The external format of the pixel data. On Windows
			//  it is BGRA usually. Most API's ignore windows 
			//  specific formats and load RGBA. Be careful. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture(PW_BYTE* tex_data, PW_UINT tex_width, PW_UINT tex_height, PW_INT internal_format, PW_INT format);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a texture from data.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) PW_BYTE* tex_data;
			// Purpose:
			//  The pixel data of the function in a specified
			//  format.
			// (2) PW_UINT target;
			// Purpose:
			//  The type of OpenGL texture you want to create.
			//  Normally it is a GL_TEXTURE_2D.
			// (3) PW_UINT tex_width;
			// Purpose:
			//  The width of the texture in pixels.
			// (4) PW_UINT tex_height;
			// Purpose:
			//  The height of the texture in pixels.
			// (5) PW_INT internal_format;
			// Purpose:
			//  The internal format the pixel data is. When
			//  loading the texture using another function not
			//  from Pistonworks make sure to know the internal
			//  format of the data you are loading.
			// (6) PW_INT format;
			// Purpose:
			//  The external format of the pixel data. On Windows
			//  it is BGRA usually. Most API's ignore windows 
			//  specific formats and load RGBA. Be careful. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture(PW_BYTE* tex_data, PW_UINT target, PW_UINT tex_width, PW_UINT tex_height, PW_INT internal_format, PW_INT format);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Texture::Texture
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a texture from data.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) PW_SRD_PTR(PW_BYTE*) tex_data;
			// Purpose:
			//  The pixel data of the function in a specified
			//  format.
			// (2) PW_UINT tex_width;
			// Purpose:
			//  The width of the texture in pixels.
			// (3) PW_UINT tex_height;
			// Purpose:
			//  The height of the texture in pixels.
			// (4) PW_INT internal_format;
			// Purpose:
			//  The internal format the pixel data is. When
			//  loading the texture using another function not
			//  from Pistonworks make sure to know the internal
			//  format of the data you are loading.
			// (5) PW_INT format;
			// Purpose:
			//  The external format of the pixel data. On Windows
			//  it is BGRA usually. Most API's ignore windows 
			//  specific formats and load RGBA. Be careful. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Texture(PW_SRD_PTR(PW_BYTE*) tex_data, PW_UINT tex_height, PW_UINT tex_length, PW_INT internal_format, PW_INT format);
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
			// (1) PW_UINT unit;
			// Purpose:
			//  Usually 0. Binds the texture to a grouping to be
			//  rendered by OpenGL. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Bind(PW_UINT unit);
			// //////////////////////////////////////////////////
			// CORE Function: Texture::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes the allocated memory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Delete();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_UINT texture_id;

			PW_UINT texture_width;
			PW_UINT texture_height;
		};                  
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_TEXTURE