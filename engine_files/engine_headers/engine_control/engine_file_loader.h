// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
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
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <tuple>
#include <filesystem>
#include <functional>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4458)
#pragma warning (push)
#pragma warning (disable:4267)
#pragma warning (push)
#pragma warning (disable:4244)
#pragma warning (push)
#pragma warning (disable:4189)
#include <CSV\csv.h>
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <AL\alut.h>
#include <glm\detail\type_vec4.hpp>
#pragma warning (pop)
#pragma warning (pop)
#pragma warning (pop)
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
// Exception to format to fix <Windows.h> bug
#pragma warning(push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#ifndef PW_FI_H
#define PW_FI_H
#include <freeimage\FreeImage.h>
#endif // PW_FI_H 
#pragma warning(pop)
//////////////////////////////////
// Engine Control Headers
#include "engine_control\engine_file_finder.h"
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_game_scene.h"
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
		class File_Loader {
		// Default Class Structures 
		public:
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
			static void Initialize_Loader();
			static void Initialize_Loader(const std::function<void(const std::wstring&, const bool&)>& p_add_scene_function,
											const std::function<void(const std::wstring&)>& p_change_scene_function,
											const std::function<void(const std::wstring&)>& p_remove_scene_function,
											const std::function<void(const std::wstring&, const std::wstring&, const bool&)>& p_sub_scene_render);
			static void Release_Loader();

			static st::Texture* Load_Texture_File(const std::wstring& p_file_name,
				const bool& p_repeat, const bool& p_linear, const bool& p_engine_dir = false, std::wstring* p_override_dir = nullptr);

			static std::tuple<st::Texture*, st::Animation*> Load_Animation_File(const std::wstring& p_file_name,
				const bool& p_repeat, const bool& p_linear, const bool& p_is_async, const bool& p_engine_dir = false, std::wstring* p_override_dir = nullptr);

			static GLFWimage* Load_Icon(const std::wstring& p_file_name, const bool& p_engine_dir);
			static void Unload_Icon();
			
			static PW_PROJECT_FILE Load_Project_File(const std::filesystem::path& p_file_location, const std::wstring& p_path_to_animations,
				const std::wstring& p_path_to_data, const std::wstring& p_path_to_fonts, const std::wstring& p_path_to_icon, const std::wstring& p_path_to_linker_files,
				const std::wstring& p_path_to_textures, const std::wstring& p_path_to_sounds);

			static st::Game_Scene* Load_Scene_File(const std::wstring& p_file_name);

			static void Load_Data_File(std::vector<st::Actor*>& p_scene_models,
				std::vector<st::Actor*>& p_collision_models,
				std::vector<std::tuple<std::wstring, st::Actor*, int32_t>>& p_s_id_holder,
				std::map<std::wstring, st::Sub_Scene_Structure*>& p_sub_scene_structures,
				std::filesystem::path& p_location, uint32_t& p_has_physics_factory, st::Physics_Factory* p_physics_factory,
				std::string& p_main_scene, std::vector<std::string>& p_sub_scenes, std::vector<std::tuple<std::wstring, st::Actor*, glm::vec2>>& p_model_attachments);
			
			static glm::vec4 Default_Color(const Default_Colors& p_color);

			static st::Sound* Load_Audio_File(const std::wstring& file_name, const bool& p_loops, const float& p_volume, const bool& p_windows_style);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			static st::Texture* Load_PNG(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear);
			static st::Texture* Load_BMP(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear);
			static st::Texture* Load_JPEG(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear);
		// Private Variables        
		private:
			static FIBITMAP* m_current_icon; // Current icon to be unloaded

			static bool m_loaded_project; // Once a project is loaded you can load other textures

			static std::wstring m_animation_location;
			static std::wstring m_data_location;
			static std::wstring m_font_location;
			static std::wstring m_icon_location;
			static std::wstring m_linker_location;
			static std::wstring m_texture_location;
			static std::wstring m_sound_location;

			static std::wstring m_engine_icon_dir; // The directory of the icon depository
			static std::wstring m_engine_texture_dir; // The directory of the texture depository
			static std::wstring m_engine_animation_dir; // The directory of the animation depository

			static std::function<void(const std::wstring&, const bool&)> m_add_scene_function;
			static std::function<void(const std::wstring&)> m_change_scene_function;
			static std::function<void(const std::wstring&)> m_remove_scene_function;
			static std::function<void(const std::wstring&, const std::wstring&, const bool&)> m_sub_scene_render;

			static std::map<std::wstring, st::Texture*>* m_texture_repository;

			static glm::vec4 m_engine_colors[(uint32_t)Default_Colors::Color_Count];
		};
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_FILE_LOADER