// BSD 3 - Clause License
//
// Copyright(c) 2021-2024, Darrian Corkadel
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
#ifndef H_QUEUE
#define H_QUEUE
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <iostream>
#include <filesystem>
#include <fstream>
#include <corecrt_wstring.h>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
#include "control\file_loader.h"
//////////////////////////////////
// Engine Structures Headers
#include "control\shader.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Engine_Queue : pw::co::Text_Renderer, pw::st::Model {
		// Friends
			friend class pw::co::Control;
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			/* Error List: PW_FUNCTION_ERROR */
			static void Add_Scene(const std::wstring& p_scene_name, const bool p_set_current = false);
			/* Error List: PW_FUNCTION_ERROR */
			static void Set_Current_Scene(const std::wstring& p_scene_name);
			/* Error List: PW_FUNCTION_ERROR */
			static void Remove_Scene(std::wstring p_scene_name);
			
			/* Error List: NONE */
			static void Set_Scene_Functions(const std::function<void(const std::wstring&)>& p_pre_add,
				const std::function<void(const std::wstring&)>& p_post_add,
				const std::function<void(const std::wstring&)>& p_pre_change,
				const std::function<void(const std::wstring&)>& p_post_change,
				const std::function<void(const std::wstring&)>& p_pre_remove,
				const std::function<void(const std::wstring&)>& p_post_remove);
			/* Error List: NONE */
			static void Set_User_Debug_Function(const std::function<void()>& p_debug_function);

			/* Error List: NONE */
			static void Set_Sub_Scene_Render(const std::wstring& p_base_scene, const std::wstring& p_sub_scene, const bool p_state);

			/* Error List: NONE */
			static st::Game_Scene* Get_Scene(const std::wstring& p_scene_name);
			/* Error List: NONE */
			static st::Game_Scene* Current_Scene();
		// Public Variables      
		public:
		// Private Functions/Macros
		private:
			/* Error List: PW_FUNCTION_ERROR */
			static void Pre_Queue();
			/* Error List: PW_FUNCTION_ERROR */
			static void Run_Queue();

			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: PW_FUNCTION_ERROR */
			static void Release();

			/* Error List: PW_FUNCTION_ERROR */
			static void Print_Debug_Stats();

			/* Error List: PW_GAME_PATH_NOT_FOUND, PW_DIRECTORY_NOT_FOUND, PW_FUNCTION_ERROR, PW_GLFW_ERROR */
			static void Load_From_Dir(std::unique_ptr<GLFWwindow, pw::cm::Destroy_GLFW>& p_main_window, std::shared_ptr<PW_FUNCTION> p_state_function);
		// Private Variables       
		private:
			// Has the pwproject file been loaded
			static bool m_loaded_project;
			// Data to be loaded from the game
			static std::wstring m_project_name;

			static std::wstring m_current_scene;

			static std::map<std::wstring, st::Game_Scene*>* m_scene_directory;

			static std::function<void(const std::wstring&)> m_pre_scene_add;
			static std::function<void(const std::wstring&)> m_post_scene_add;

			static std::function<void(const std::wstring&)> m_pre_scene_change;
			static std::function<void(const std::wstring&)> m_post_scene_change;

			static std::function<void(const std::wstring&)> m_pre_scene_remove;
			static std::function<void(const std::wstring&)> m_post_scene_remove;

			// Open Debug Slots 11 - 35
			static std::function<void()> m_user_debug_function;
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_QUEUE