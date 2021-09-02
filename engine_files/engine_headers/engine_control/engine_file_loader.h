#ifndef H_FILE_LOADER
#define H_FILE_LOADER
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <tuple>
#include <filesystem>
#include <cmath>
//////////////////////////////////
// Project Headers
#include <freeimage\FreeImage.h>
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers     
#include "engine_structures\engine_animation.h"
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
	CO_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// Class Name: pw::ie::File_Loader
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Loads different types of files
		//  and translates them to engine objects.
		// //////////////////////////////////////////////////
		class PW_CONTROL_API File_Loader {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// Enum Name: pw::ie::File_Loader::Default_Colors
			// //////////////////////////////////////////////////																				 
			// Purpose:
			//  A structure that holds default color data.
			// //////////////////////////////////////////////////
			enum class Default_Colors {
				//LIT_RED				#ff 80 80 
				//RED					#ff 00 00 
				//DRK_RED				#80 00 00	
				LIGHT_RED,		RED,	DARK_RED,
				//LIT_GREEN				#80 ff 80 
				//GREEN					#00 ff 00 
				//DRK_GREEN				#00 80 00 
				LIGHT_GREEN,	GREEN,	DARK_GREEN,
				//LIT_BLUE				#80 80 ff 
				//BLUE					#00 00 ff 
				//DRK_BLUE				#00 00 80
				LIGHT_BLUE,		BLUE,	DARK_BLUE,
				//LIT_YELLOW			#ff ff 80 
				//YELLOW				#ff ff 00 
				//DRK_YELLOW			#80 80 00
				LIGHT_YELLOW,	YELLOW,	DARK_YELLOW,
				//LIT_PINK				#ff 80 ff 
				//PINK					#ff 00 ff 
				//DRK_PINK				#80 00 80
				LIGHT_PINK,		PINK,	DARK_PINK,
				//LIT_CYAN				#80 ff ff 
				//CYAN					#00 ff ff 
				//DRK_CYAN				#00 80 80
				LIGHT_CYAN,		CYAN,	DARK_CYAN,
				//LIT_LIME				#80 ff 80 
				//LIME					#80 ff 00 
				//DRK_LIME				#40 80 00
				LIGHT_LIME,		LIME,	DARK_LIME,
				//LIT_ORANGE			#ff bf 80 
				//ORANGE				#ff 80 00 
				//DRK_ORANGE			#cc 60 00
				LIGHT_ORANGE,	ORANGE,	DARK_ORANGE,
				//LIT_AZURE				#80 bf ff 
				//AZURE					#00 80 ff 
				//DRK_AZURE				#00 40 80
				LIGHT_AZURE,	AZURE,	DARK_AZURE,
				//LIT_PURPLE			#bf 80 ff 
				//PURPLE				#80 00 ff 
				//DRK_PURPLE			#40 00 80
				LIGHT_PURPLE,	PURPLE,	DARK_PURPLE,
				//LIT_BROWN				#80 5c 40 
				//BROWN					#80 40 00 
				//DRK_BROWN				#40 20 00
				LIGHT_BROWN,	BROWN,	DARK_BROWN,
				//LIT_GREY				#c0 c0 c0
				//GREY					#80 80 80 
				//DRK_GREY				#40 40 40
				LIGHT_GREY,		GREY,	DARK_GREY,
				//WHITE					#ff ff ff
				//BLACK					#00 00 00
				//COUNT					38
				WHITE,			BLACK,	Color_Count
			};
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// UTILITY File_Loader::Load_Texture_File
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA File.
			//  Available types: PNG, BMP, JPEG
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY Texture& Load_Texture_File(PW_CSTRING file_name);
			// Function: File_Loader::Load_Animation_File
			//
			// Purpose: Loads a 32 bit RGBA File.
			//	Available types: GIF
			//  Note: You must create the model and finish initialization of the animation using the function Finish_Init.
			//
			USER_INTERACTION
			static UTILITY std::tuple<Texture*, Animation*> Load_Animation_File(PW_CSTRING file_name);
			// Function: File_Loader::Load_Icon
			//
			// Purpose: Loads a 32 bit RGBA PNG.
			//	Available types: PNG
			//
			USER_INTERACTION
			static UTILITY GLFWimage& Load_Icon(PW_CSTRING file_name);
			// Function: File_Loader::Unload_Icon
			//
			// Purpose: Unload the icon after its use.
			//
			USER_INTERACTION
			static UTILITY PW_VOID Unload_Icon();
			// Accessors
			USER_INTERACTION
			static ACCESSOR glm::vec4 Default_Color(Default_Colors color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			// Function: File_Loader::Load_PNG
			//
			// Purpose: Loads a 32 bit RGBA PNG.
			//
			static UTILITY Texture& Load_PNG(PW_CSTRING file_location);
			// Function: File_Loader::Load_BMP
			//
			// Purpose: Loads a 32 bit RGBA BMP.
			//
			static UTILITY Texture& Load_BMP(PW_CSTRING file_location);
			// Function: File_Loader::Load_JPEG
			//
			// Purpose: Loads a 32 bit RGBA JPEG.
			//
			static UTILITY Texture& Load_JPEG(PW_CSTRING file_location);
			// Function: File_Loader::Load_GIF
			//
			// Purpose: Loads a 32 bit RGBA GIF.
			//
			static UTILITY std::tuple<Texture&, Animation&> Load_GIF(PW_CSTRING file_location);
		// Private Variables        
		private:
			static FIBITMAP* current_icon; // Current icon to be unloaded

			static PW_CSTRING texture_dir; // The directory of the texture depository
			static PW_CSTRING icon_dir; // The directory of the icon depository
			static glm::vec4 Engine_Colors[(PW_UINT)Default_Colors::Color_Count];
		};
		// Functions      
		// Macros / Definitions
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_FILE_LOADER