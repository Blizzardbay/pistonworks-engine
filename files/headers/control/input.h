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
#ifndef H_INPUT
#define H_INPUT
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <vector>
#include <map>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "structures\event.h"
#include "structures\camera.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
CO_NAMESPACE_SRT
		class Custom_Input {
		// Friends
		// Default Class Structures
		public:
		private:
		// Protected Functions/Macros
		public:
			/* Error List: NONE */
			static void Add(const std::wstring& p_identifier, const COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)& p_function);
			/* Error List: NONE */
			static void Remove(const std::wstring& p_identifier);
		// Protected Variables       
		public:
		// Protected Functions/Macros
		protected:
			/* Error List: PW_FUNCTION_ERROR */
			static void Use(PW_EVENT_ID p_event_id, PW_BUTTON_CODE p_button_code, PW_STATE p_state);
		// Protected Variables       
		protected:
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
			static std::map<std::wstring, COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)> m_custom_handlers;
		};
		class Input : public Custom_Input {
		// Friends
			friend class pw::co::Control;
		// Default Class Structures
		public:
			/* Error List: NONE */
			Input();
			/* Error List: NONE */
			Input(
				std::vector<st::Event_Base*> p_current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> p_key_events,
				std::vector<st::Event_Base*> p_current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> p_mouse_events,
				std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> p_scroll_events);
			/* Error List: NONE */
			~Input();
		private:
		// Public Functions/Macros
		public:
			/* Error List: PW_FUNCTION_ERROR */
			void Create_Event_Keyboard(const PW_INPUT_TYPE p_action, const PW_KEY_CODE& p_key_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool p_only_play_once = false);
			/* Error List: PW_FUNCTION_ERROR */
			void Create_Event_Mouse(const PW_INPUT_TYPE p_action, const PW_BUTTON_CODE& p_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool p_only_play_once = false);
			/* Error List: PW_FUNCTION_ERROR */
			void Create_Event_Scroll(const PW_SCROLL_ACTION& p_action, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool p_only_play_once = false);
			
			/* Error List: NONE */
			static void Register_Function(const std::wstring& p_function_name, std::shared_ptr<PW_FUNCTION> p_function);
			
			/* Error List: NONE */
			static void Set_Current_Input(co::Input* p_new_input);

			/* Error List: NONE */
			static void Set_Scene_Event_Function(const COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)& p_new_scene_event_function);

			/* Error List: NONE */
			static co::Input* Current_Input();
			
			/* Error List: NONE */
			static std::shared_ptr<PW_FUNCTION> Access_Function(const std::wstring& p_function_name);
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
			/* Error List: PW_FUNCTION_ERROR */
			void Poll_Active_Events();

			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Keyboard(GLFWwindow* p_window, int p_key, int p_code, int p_action, int p_mode) noexcept;
			/* Error List: NONE */
			static void Handle_Mouse_Movement(GLFWwindow* p_window, double p_mouse_xpos, double p_mouse_ypos) noexcept;
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Mouse_Button(GLFWwindow* p_window, int p_button, int p_action, int p_mods) noexcept;
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Mouse_Scroll(GLFWwindow* p_window, double p_xoffset, double p_yoffset) noexcept;
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			static void Handle_Resize(GLFWwindow* p_window, int p_window_width, int p_window_height) noexcept;

			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: NONE */
			static void Release();
		// Private Variables
		private:
			std::vector<st::Event_Base*> m_current_key_events;
			std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> m_key_events;
			std::vector<st::Event_Base*> m_current_mouse_events;
			std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> m_mouse_events;
			std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> m_scroll_events;
			uint64_t m_event_id_assigner;

			// This is a pointer to the current input that we are using.
			static co::Input* m_current_input;
			static std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>* m_function_register;
			static COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) m_scene_event_function;
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_INPUT