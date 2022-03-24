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
#ifndef H_ENGINE_INPUT
#define H_ENGINE_INPUT
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
#include <vector>
#include <map>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4201)
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_event.h"
#include "engine_structures\engine_camera.h"
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
		class Engine_Input {
		// Default Class Structures
		public:
			Engine_Input();
			Engine_Input(
				std::vector<st::Event_Base*> p_current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> p_key_events,
				std::vector<st::Event_Base*> p_current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> p_mouse_events,
				std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> p_scroll_events);
			~Engine_Input();

			static void Initialize_Input();
			static void Release_Input();
		private:
		// Public Functions/Macros
		public:
			void Poll_Active_Events();

			static void Handle_Keyboard(GLFWwindow* p_window, int p_key, int p_code, int p_action, int p_mode);
			static void Handle_Mouse_Movement(GLFWwindow* p_window, double p_mouse_xpos, double p_mouse_ypos);
			static void Handle_Mouse_Button(GLFWwindow* p_window, int p_button, int p_action, int p_mods);
			static void Handle_Mouse_Scroll(GLFWwindow* p_window, double p_xoffset, double p_yoffset);
			static void Handle_Resize(GLFWwindow* p_window, int p_window_width, int p_window_height);

			void Create_Event_Keyboard(const PW_INPUT_TYPE& p_action, const PW_KEY_CODE& p_key_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once = false);
			void Create_Event_Mouse(const PW_INPUT_TYPE& p_action, const PW_BUTTON_CODE& p_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once = false);
			void Create_Event_Scroll(const PW_SCROLL_ACTION& p_action, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once = false);
			
			static void Register_Function(const std::wstring& p_function_name, std::shared_ptr<PW_FUNCTION> p_function);
			
			static void Set_Current_Input(co::Engine_Input* p_new_input);

			static void Set_Scene_Event_Function(const COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)& p_new_scene_event_function);

			static co::Engine_Input* Current_Input();
			
			static std::shared_ptr<PW_FUNCTION> Access_Function(const std::wstring& p_function_name);
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
			std::vector<st::Event_Base*> m_current_key_events;
			std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> m_key_events;
			std::vector<st::Event_Base*> m_current_mouse_events;
			std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> m_mouse_events;
			std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> m_scroll_events;
			uint64_t m_event_id_assigner;

			// This is a pointer to the current input that we are using.
			static co::Engine_Input* m_current_input;
			static std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>* m_function_register;
			static COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) m_scene_event_function;
		};
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////               
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_INPUT