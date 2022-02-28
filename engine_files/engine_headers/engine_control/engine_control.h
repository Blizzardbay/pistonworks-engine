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
			void Init_Engine(int argc, char* argv[], const std::wstring& p_window_name, const int32_t& p_window_width = 800, const int32_t& p_window_height = 608);

			void Run_Engine();
			void Terminate_Engine();
			
			void Create_Callbacks() const;
			void Update_Engine_State();
			bool Should_Close() const;

			void Pre_Load();
			void Init_Game();
			void Before_Queue();
			void After_Queue();
			void Terminate_Game();

			void Pre_Scene_Load(const std::wstring& p_scene);
			void Pre_Scene_Change(const std::wstring& p_scene);
			void Pre_Scene_Removal(const std::wstring& p_scene);

			void Post_Scene_Load();
			void Post_Scene_Change();
			void Post_Scene_Removal();

			const bool& No_Error() const;
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
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
		};
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONTROL