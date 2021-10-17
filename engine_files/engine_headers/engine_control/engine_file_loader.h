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
#include <functional>
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include <CSV\csv.h>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
// Exception to format to fix <Windows.h> bug
#ifndef PW_FI_H
#define PW_FI_H
#include "freeimage\FreeImage.h"
#endif // PW_FI_H 
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_game_scene.h"
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
			// LOADER File_Loader::Load_Texture_File
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA File.
			//  Available types: PNG, BMP, JPEG
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) const wchar_t* file_name;
			// Purpose: 
			//  The name of the file to be loaded.
			// (2) bool engine_dir;
			// Purpose: 
			//  Should the engine use the game dir or the engine
			//  dir?
			// (3) const wchar_t* override_dir;
			// Purpose: 
			//  For single image animations it needs to be loaded
			//  as a texture from the animation directory.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static LOADER st::Texture& Load_Texture_File(const wchar_t* file_name, bool engine_dir, const wchar_t* override_dir);
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_Animation_File
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA File.
			//	Available types: GIF
			//  Note: You must create the model and finish
			//  initialization of the animation using the function
			//  Finish_Init.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_name;
			// Purpose: 
			//  The name of the file to be loaded.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static LOADER std::tuple<st::Texture*, st::Animation*> Load_Animation_File(const wchar_t* file_name);
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_Icon
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA PNG.
			//	Available types: PNG
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_name;
			// Purpose: 
			//  The name of the file to be loaded.
			// (2) bool engine_dir;
			// Purpose: 
			//  Should the engine use the game dir or the engine
			//  dir?
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static LOADER GLFWimage& Load_Icon(const wchar_t* file_name, bool engine_dir);
			// //////////////////////////////////////////////////
			// LOADER  File_Loader::Unload_Icon
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Unload the icon after its use.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static LOADER void Unload_Icon();
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_Project_File
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads the project file information for the queue.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_location;
			// Purpose: 
			//  The location of the file to be loaded.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static LOADER PW_PROJECT_FILE Load_Project_File(const wchar_t* file_location, std::wstring path_to_animations,
				std::wstring path_to_data, std::wstring path_to_fonts, std::wstring path_to_icon, std::wstring path_to_linker_files, std::wstring path_to_textures);
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_Scene_File
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a scene.csv file with the scene's content
			//  information.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_location;
			// Purpose: 
			//  The location of the file to be loaded.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static LOADER st::Game_Scene* Load_Scene_File(const wchar_t* file_name);
			// Accessors
			USER_INTERACTION
			static ACCESSOR glm::vec4 Default_Color(Default_Colors color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_PNG
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA PNG.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_location;
			// Purpose: 
			//  The location of the file to be loaded.
			// //////////////////////////////////////////////////
			static LOADER st::Texture& Load_PNG(const wchar_t* file_location);
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_BMP
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA BMP.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_location;
			// Purpose: 
			//  The location of the file to be loaded.
			// //////////////////////////////////////////////////
			static LOADER st::Texture& Load_BMP(const wchar_t* file_location);
			// //////////////////////////////////////////////////
			// LOADER File_Loader::Load_JPEG
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a 32 bit RGBA JPEG.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* file_location;
			// Purpose: 
			//  The location of the file to be loaded.
			// //////////////////////////////////////////////////
			static LOADER st::Texture& Load_JPEG(const wchar_t* file_location);
		// Private Variables        
		private:
			static FIBITMAP* current_icon; // Current icon to be unloaded

			static bool loaded_project; // Once a project is loaded you can load other textures

			static std::wstring animation_location;
			static std::wstring data_location;
			static std::wstring font_location;
			static std::wstring icon_location;
			static std::wstring linker_location;
			static std::wstring texture_location;

			static std::wstring engine_icon_dir; // The directory of the icon depository
			static std::wstring engine_texture_dir; // The directory of the texture depository
			
			static glm::vec4 Engine_Colors[(uint32_t)Default_Colors::Color_Count];
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