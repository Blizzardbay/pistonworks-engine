#ifndef H_IE_TEXTURE
#define H_IE_TEXTURE
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers              
#include <cassert>
//////////////////////////////////
// Project Headers          
#include <glm\glm.hpp>
#include <stb_image.h>
//////////////////////////////////
// Engine Headers           
//////////////////////////////////
// Engine Macro Includes    
#include "engine_headers\engine_error.h"
//////////////////////////////////
// Engine Macros           
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Internal Engine              //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes
	
		//////////////////////////////////
		// Class Name: pw::ie::Texture
		//																				 
		// Purpose: Handles textures in opengl.
		//
		class Texture {
		// Default Class Structures 
		public:
			//////////////////////////////////
			// Enum Name: pw::ie::Texture::Default_Texture
			//																				 
			// Purpose: A structure that holds default color data.
			//
			enum class Default_Texture {
				RED, GREEN, BLUE, YELLOW,
				PINK, CYAN, ORANGE, MAGENTA,
				WHITE, BLACK, LIME, DARK_CYAN,
				PURPLE, LIGHT_BLUE, BROWN,
				DARK_GREY, GREY, Color_Count
			};
			// Function: Texture::Texture
			//
			// Purpose: Creates a uninitialized texture. Will not draw.
			//
			Texture();
			// Function: Texture::Texture
			//
			// Purpose: Loads a texture from a png.
			//
			Texture(PW_CSTRING file_location);
			// Function: Texture::~Texture
			//
			// Purpose: Deallocates the texture memory.
			//
			~Texture() {};
		private:
		// Public Functions/Macros  
		public:
			// Function: Texture::Bind
			//
			// Purpose: Draws the texture to the screen. 
			//
			PW_VOID Bind(PW_UINT unit);
			// Function: Texture::Delete
			//
			// Purpose: Deletes the allocated memory.
			//
			PW_VOID Delete();
			// Function: Texture::Find_Texture
			//
			// Purpose: Finds the texture based off the name.
			//  Must set the directory first.
			//
			static PW_STRING Find_Texture(PW_CSTRING name);
			// Function: Texture::Find_Color_Texture
			//
			// Purpose: Find a color texture. REDACTED
			//
			static PW_STRING Find_Color_Texture(PW_CSTRING d_bits, Default_Texture id, glm::vec3& color);
			// Function: Texture::Change_Texture_Dir
			//
			// Purpose: Change the texture dir for loading.
			//
			static PW_VOID Change_Texture_Dir(PW_CSTRING new_dir);
			// Function: Texture::Color
			//
			// Purpose: Returns the color from the default texture enum.
			//
			static glm::vec3 Color(Default_Texture color_id);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_UINT texture_id;

			PW_UINT texture_width;
			PW_UINT texture_height;

			PW_INT texture_bit_depth;

			static PW_BOOL has_user_dir_changed;
			static PW_CSTRING user_dir;

			static glm::vec3 Engine_Colors[(PW_UINT)Default_Texture::Color_Count];
		};
		//////////////////////////////////
		// Class Name: pw::ie::Icon
		//																				 
		// Purpose: Handles icons in opengl.
		//
		class Icon {
		// Default Class Structures 
		public:
			// Function: Icon::Icon
			//
			// Purpose: Creates a uninitialized icon.
			//
			Icon();
			// Function: Icon::Icon
			//
			// Purpose: Creates a icon from a specified dir.
			//
			Icon(PW_CSTRING file_location);
			// Function: Icon::~Icon
			//
			// Purpose: Deallocates all icon memory.
			//
			~Icon();
		private:
		// Public Functions/Macros  
		public:
			// Function: Icon::Delete
			//
			// Purpose: Deletes allocated icon memory. 
			//
			PW_VOID Delete();
			// Function: Icon::Find_Icon
			//
			// Purpose: Finds the file location of the Icon png.
			//
			static PW_STRING Find_Icon(PW_CSTRING name);
			// Function: Icon::Change_Icon_Dir
			//
			// Purpose: Change the loading dir for the icon.
			//
			static PW_VOID Change_Icon_Dir(PW_CSTRING new_dir);
			// Function: Icon::Data
			//
			// Purpose: Returns the icon information.
			//
			PW_BYTE* Data();
			// Function: Icon::Width
			//
			// Purpose: Returns the width of the png.
			//
			PW_UINT Width();
			// Function: Icon::Height
			//
			// Purpose: Returns the height of the png.
			//
			PW_UINT Height();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_UINT icon_width;
			PW_UINT icon_height;

			PW_INT icon_bit_depth;

			PW_SRD_PTR(PW_BYTE PW_SMART_ARRAY) icon_data;

			static PW_BOOL has_user_dir_changed;
			static PW_CSTRING user_dir;
		};
		// Functions                
		// Macros                   
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_TEXTURE