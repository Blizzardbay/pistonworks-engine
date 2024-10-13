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
#ifndef H_CONTROL
#define H_CONTROL
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <memory>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <AL\alut.h>
#ifndef __glew_h__
#include <GL\glew.h>
#endif // !__glew_h__
#define GLFW_EXPOSE_NATIVE_WIN32
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\constant.h"
//////////////////////////////////
// Engine Control Headers
#include "control\queue.h"
#include "control\file_loader.h"
#include "control\input.h"
#include "control\console_manip.h"
#include "control\shader.h"
#include "control\multi_scope_timer.h"
#include "control\async_timer.h"
//////////////////////////////////
// Engine Structures Headers
#include "structures\event.h"
#include "structures\model.h"
#include "structures\texture.h"
#include "structures\game_scene.h"
#include "structures\camera.h"
#include "structures\text.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
// Engine Extensions Headers
#include "extensions\user_interface.h"
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Control {
		// Default Class Structures
		public:
			/* Error List: NONE */
			Control();

			Control(const Control&) = delete;
			Control& operator= (const Control&) = delete;
		private:
		// Public Functions/Macros
		public:
			/* Error List: PW_FUNCTION_ERROR, PW_GLFW_ERROR, PW_GL_ERROR, PW_AL_ERROR */
			void Initialize_Engine(int argc, char* argv[], const std::wstring& p_window_name, const int32_t p_window_width, const int32_t p_window_height, const bool p_require_game_path);

			/* Error List: PW_FUNCTION_ERROR, PW_GLFW_ERROR, PW_GL_ERROR */
			void Run_Engine();
			/* Error List: NONE */
			void Release_Engine();
			
			/* Error List: PW_GLFW_ERROR, PW_FI_ERROR */
			void Create_Callbacks() const;
			/* Error List: PW_GLFW_ERROR */
			void Update_Engine_State();
			/* Error List: NONE */
			bool Should_Close() const;

			/* Error List: PW_POSSIBLE_ERROR */
			void Pre_Load();
			/* Error List: PW_POSSIBLE_ERROR */
			void Initialize_Game();
			/* Error List: PW_POSSIBLE_ERROR */
			void Before_Queue();
			/* Error List: PW_POSSIBLE_ERROR */
			void After_Queue();
			/* Error List: PW_POSSIBLE_ERROR */
			void Release_Game();

			/* Error List: PW_POSSIBLE_ERROR */
			void Pre_Scene_Load(const std::wstring& p_scene);
			/* Error List: PW_POSSIBLE_ERROR */
			void Pre_Scene_Change(const std::wstring& p_scene);
			/* Error List: PW_POSSIBLE_ERROR */
			void Pre_Scene_Removal(const std::wstring& p_scene);

			/* Error List: PW_POSSIBLE_ERROR */
			void Post_Scene_Load(const std::wstring& p_scene);
			/* Error List: PW_POSSIBLE_ERROR */
			void Post_Scene_Change(const std::wstring& p_scene);
			/* Error List: PW_POSSIBLE_ERROR */
			void Post_Scene_Removal(const std::wstring& p_scene);

			/* Error List: NONE */
			const bool No_Error() const;
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			// For running without scene loading
			bool m_require_game_path;
			// For termination of the engine
			bool m_no_error;
			bool m_has_terminated;
			// Initialization failures
			bool m_console_complete;
			bool m_glfw_complete;
			// Loaded font
			bool m_font_complete;
			// Loaded queue
			bool m_queue_complete;
			// Loaded Alut
			bool m_alut_complete;

			std::unique_ptr<GLFWwindow, pw::cm::Destroy_GLFW> m_main_window;

			#ifdef PW_DEBUG_MODE
				static std::chrono::steady_clock::time_point m_debug_load_time;
			#endif // PW_DEBUG_MODE
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END

#define USE_DEFAULT_ENGINE_CONTROL													\
	void pw::co::Control::Pre_Load() {												\
	}																				\
	void pw::co::Control::Initialize_Game() {										\
	}																				\
	void pw::co::Control::Before_Queue() {											\
	}																				\
	void pw::co::Control::After_Queue() {											\
	}																				\
	void pw::co::Control::Release_Game() {											\
	}																				\
	void pw::co::Control::Pre_Scene_Load(const std::wstring& p_scene) {				\
		UNUSED(p_scene);															\
	}																				\
	void pw::co::Control::Pre_Scene_Change(const std::wstring& p_scene) {			\
		UNUSED(p_scene);															\
	}																				\
	void pw::co::Control::Pre_Scene_Removal(const std::wstring& p_scene) {			\
		UNUSED(p_scene);															\
	}																				\
	void pw::co::Control::Post_Scene_Load(const std::wstring& p_scene) {			\
		UNUSED(p_scene);															\
	}																				\
	void pw::co::Control::Post_Scene_Change(const std::wstring& p_scene) {			\
		UNUSED(p_scene);															\
	}																				\
	void pw::co::Control::Post_Scene_Removal(const std::wstring& p_scene) {			\
		UNUSED(p_scene);															\
	}
#define USE_PISTONWORKS_ENGINE(p_window_size_x, p_window_size_y, p_require_game_path)		\
	int main(int argc, char* argv[]) {														\
		pw::co::Control engine{};															\
		PW_CALL(engine.Initialize_Engine(argc, argv, L"Pistonworks Window",					\
			TO_UINT32(p_window_size_x), TO_UINT32(p_window_size_y),							\
			TO_BOOL(p_require_game_path)), false);											\
		if (engine.No_Error() == false) {													\
			engine.Release_Engine();														\
			return 1;																		\
		}																					\
		else {																				\
			PW_CALL(engine.Run_Engine(), false);											\
			engine.Release_Engine();														\
			return 0;																		\
		}																					\
		return 0;																			\
	}															

#endif // !H_CONTROL