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
#ifndef H_ENGINE_CONTROL
#define H_ENGINE_CONTROL
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
#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <memory>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4005)
#include <AL\alut.h>
#ifndef __glew_h__
#include <GL\glew.h>
#endif // !__glew_h__
#define GLFW_EXPOSE_NATIVE_WIN32
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_constant.h"
//////////////////////////////////
// Engine Control Headers
#include "engine_control\engine_queue.h"
#include "engine_control\engine_file_loader.h"
#include "engine_control\engine_input.h"
#include "engine_control\engine_console_manip.h"
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_event.h"
#include "engine_structures\engine_shader.h"
#include "engine_structures\engine_model.h"
#include "engine_structures\engine_texture.h"
#include "engine_structures\engine_game_scene.h"
#include "engine_structures\engine_camera.h"
#include "engine_structures\engine_text.h"
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		class Engine_Control {
		// Default Class Structures
		public:
			Engine_Control();
		private:
		// Public Functions/Macros
		public:
			void Initialize_Engine(int argc, char* argv[], const std::wstring& p_window_name, const int32_t& p_window_width, const int32_t& p_window_height, const bool& p_require_game_path);

			void Run_Engine();
			void Release_Engine();
			
			void Create_Callbacks() const;
			void Update_Engine_State();
			bool Should_Close() const;

			void Pre_Load();
			void Initialize_Game();
			void Before_Queue();
			void After_Queue();
			void Release_Game();

			void Pre_Scene_Load(const std::wstring& p_scene);
			void Pre_Scene_Change(const std::wstring& p_scene);
			void Pre_Scene_Removal(const std::wstring& p_scene);

			void Post_Scene_Load(const std::wstring& p_scene);
			void Post_Scene_Change(const std::wstring& p_scene);
			void Post_Scene_Removal(const std::wstring& p_scene);

			const bool& No_Error() const;
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

			std::unique_ptr<GLFWwindow, cm::Destroy_GLFW> m_main_window;

			#ifdef PW_DEBUG_MODE
				static std::chrono::system_clock::time_point m_debug_load_time;
			#endif // PW_DEBUG_MODE
		};
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////

#define USE_DEFAULT_ENGINE_CONTROL													\
	void pw::co::Engine_Control::Pre_Load() {										\
	}																				\
	void pw::co::Engine_Control::Initialize_Game() {								\
	}																				\
	void pw::co::Engine_Control::Before_Queue() {									\
	}																				\
	void pw::co::Engine_Control::After_Queue() {									\
	}																				\
	void pw::co::Engine_Control::Release_Game() {									\
	}																				\
	void pw::co::Engine_Control::Pre_Scene_Load(const std::wstring& p_scene) {		\
	}																				\
	void pw::co::Engine_Control::Pre_Scene_Change(const std::wstring& p_scene) {	\
	}																				\
	void pw::co::Engine_Control::Pre_Scene_Removal(const std::wstring& p_scene) {	\
	}																				\
	void pw::co::Engine_Control::Post_Scene_Load(const std::wstring& p_scene) {		\
	}																				\
	void pw::co::Engine_Control::Post_Scene_Change(const std::wstring& p_scene) {	\
	}																				\
	void pw::co::Engine_Control::Post_Scene_Removal(const std::wstring& p_scene) {	\
	}
#define USE_PISTONWORKS_ENGINE(p_window_size_x, p_window_size_y, p_require_game_path)		\
	int main(int argc, char* argv[]) {														\
		pw::co::Engine_Control engine{};													\
		engine.Initialize_Engine(argc, argv, L"Pistonworks Window",							\
			TO_UINT32(p_window_size_x), TO_UINT32(p_window_size_y),							\
			TO_BOOL(p_require_game_path));													\
		if (engine.No_Error() == false) {													\
			engine.Release_Engine();														\
			return 1;																		\
		}																					\
		else {																				\
			engine.Run_Engine();															\
			engine.Release_Engine();														\
			return 0;																		\
		}																					\
		return 0;																			\
	}															

#endif // !H_ENGINE_CONTROL