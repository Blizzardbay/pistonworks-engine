// BSD 3 - Clause License
//
// Copyright(c) 2021-2023, Darrian Corkadel
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
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <tuple>
#include <filesystem>
#include <functional>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <CSV\csv.h>
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <AL\alut.h>
#include <glm\detail\type_vec4.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
// Exception to format to fix <Windows.h> bug
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#ifndef PW_FI_H
#define PW_FI_H
#include <freeimage\FreeImage.h>
#endif // PW_FI_H 
#pragma warning(pop)
//////////////////////////////////
// Engine Control Headers
#include "control\file_finder.h"
#include "control\listener.h"
//////////////////////////////////
// Engine Structures Headers
#include "structures\game_scene.h"
//////////////////////////////////
// Engine Utility Headers
#include "utility\color.h"
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class File_Loader : public pw::co::Listener {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: NONE */
			static void Initialize_Loader(const std::function<void(const std::wstring&, const bool&)>& p_add_scene_function,
											const std::function<void(const std::wstring&)>& p_change_scene_function,
											const std::function<void(const std::wstring&)>& p_remove_scene_function,
											const std::function<void(const std::wstring&, const std::wstring&, const bool&)>& p_sub_scene_render);
			/* Error List: NONE */
			static void Release();

			/* Error List: PW_FI_ERROR, PW_FI_UNKNOWN_FILE_TYPE, PW_FUNCTION_ERROR, PW_FI_UNSUPPORTED_FILE_TYPE */
			static st::Texture* Load_Texture_File(const std::wstring& p_file_name,
				const bool& p_repeat, const bool& p_linear, const bool& p_engine_dir = false, std::wstring* p_override_dir = nullptr);

			/* Error List: PW_FI_ERROR, PW_FI_UNKNOWN_FILE_TYPE, PW_FUNCTION_ERROR, PW_FI_UNKNOWN_FILE_TYPE */
			static std::tuple<st::Texture*, st::Animation*> Load_Animation_File(const std::wstring& p_file_name,
				const bool& p_repeat, const bool& p_linear, const bool& p_is_async, const bool& p_engine_dir = false, std::wstring* p_override_dir = nullptr);

			/* Error List: PW_FUNCTION_ERROR, PW_FI_ERROR, PW_FI_UNKNOWN_FILE_TYPE, PW_FI_FILE_LOAD_FAILURE */
			static GLFWimage* Load_Icon(const std::wstring& p_file_name, const bool& p_engine_dir);
			/* Error List: NONE */
			static void Unload_Icon();
			/* Error List: PW_FUNCTION_ERROR */
			static PW_PROJECT_FILE Load_Project_File(const std::filesystem::path& p_file_location, const std::wstring& p_path_to_animations,
				const std::wstring& p_path_to_data, const std::wstring& p_path_to_fonts, const std::wstring& p_path_to_icon, const std::wstring& p_path_to_linker_files,
				const std::wstring& p_path_to_textures, const std::wstring& p_path_to_sounds);
			/* Error List: PW_FUNCTION_ERROR */
			static st::Game_Scene* Load_Scene_File(const std::wstring& p_file_name);
			/* Error List: PW_FUNCTION_ERROR, PW_UNSUPPORTED_ANIMATION_EXTENSION */
			static void Load_Data_File(std::vector<st::Actor*>& p_scene_models,
				std::vector<st::Actor*>& p_collision_models,
				std::vector<std::tuple<std::wstring, st::Actor*, int32_t>>& p_s_id_holder,
				std::map<std::wstring, st::Sub_Scene_Structure*>& p_sub_scene_structures,
				std::filesystem::path& p_location, uint32_t& p_has_physics_factory, st::Physics_Factory* p_physics_factory,
				std::string& p_main_scene, std::vector<std::string>& p_sub_scenes, std::vector<std::tuple<std::wstring, st::Actor*, glm::vec2>>& p_model_attachments);
			
			/* Error List: PW_AL_ERROR, PW_FUNCTION_ERROR */
			static st::Sound* Load_Audio_File(const std::wstring& file_name, const bool& p_loops, const float& p_volume, const bool& p_windows_style);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			/* Error List: PW_FI_ERROR, PW_FI_FILE_LOAD_FAILURE, PW_FUNCTION_ERROR, PW_FI_NO_PIXELS */
			static st::Texture* Load_PNG(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear);
			/* Error List: PW_FI_ERROR, PW_FI_FILE_LOAD_FAILURE, PW_FUNCTION_ERROR, PW_FI_NO_PIXELS */
			static st::Texture* Load_BMP(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear);
			/* Error List: PW_FI_ERROR, PW_FI_FILE_LOAD_FAILURE, PW_FUNCTION_ERROR, PW_FI_NO_PIXELS */
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
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_FILE_LOADER