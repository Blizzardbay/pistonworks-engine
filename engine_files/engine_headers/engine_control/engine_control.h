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
#ifndef H_ENGINE_CONTROL
#define H_ENGINE_CONTROL
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>
//////////////////////////////////
// Project Headers
#include <freeimage\FreeImage.h>
#include <box2d\b2_fixture.h>
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_constant.h"
//////////////////////////////////
// Engine Control Headers
#include "engine_control\engine_queue.h"
#include "engine_control\engine_file_loader.h"
#include "engine_control\engine_input.h"
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
// Engine Macros
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// //////////////////////////////////////////////////
		// PW_CONTROL_API Class: pw::co::Engine_Control
		// //////////////////////////////////////////////////
		// Purpose:
		//  The main point of the application. Runs all
		//  events and calculations that take place in the
		//  engine.
		// //////////////////////////////////////////////////
		class PW_CONTROL_API Engine_Control : protected pw::cm::Engine_Constant {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// PW_CONTROL_API CLASS_FUNCTION: Engine_Control::Engine_Control
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a instance of the engine.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Engine_Control();
			// //////////////////////////////////////////////////
			// PW_CONTROL_API CLASS_FUNCTION: Engine_Control::~Engine_Control
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes memory of the engine object.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Engine_Control();
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Init_Engine
			// //////////////////////////////////////////////////
			// Purpose: 
			//	Init engine make all of the default glew and glfw
			//	init's that are needed for the application to
			//	work. Also init's engine constants and runtime
			//	variables on top of shader control.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) const wchar_t* display_name;
			// Purpose: 
			//  The name of the application.
			// (2) int32_t display_width = 800;
			// Purpose: 
			//  The width of the application.
			// (3) int32_t display_height = 608;
			// Purpose: 
			//  The height of the application.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Init_Engine(const wchar_t* display_name, int32_t display_width = 800, int32_t display_height = 608);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Run_Engine
			// //////////////////////////////////////////////////
			// Purpose:
			//	Runs the engine queue system and makes sure the
			//	runtime exceptions are handled and that runtime
			//	variables are up to date when used. Check/handles
			//	input and if the window should close.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Run_Engine();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Terminate_Engine
			// //////////////////////////////////////////////////
			// Purpose:
			//	Destroys and deallocates all of the engine.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Terminate_Engine();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Create_Callbacks
			// //////////////////////////////////////////////////
			// Purpose:
			//	Creates the input callbacks.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Create_Callbacks() const;
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Update_Engine_State
			// //////////////////////////////////////////////////
			// Purpose:
			//	Swaps opengl buffers.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Update_Engine_State();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Should_Close
			// //////////////////////////////////////////////////
			// Purpose:
			//	Tests if the window should close or not.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE bool Should_Close() const;
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Init_Game
			// //////////////////////////////////////////////////
			// Purpose:
			//  User determined.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual OVERLOAD CORE void Init_Game();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Before_Queue
			// //////////////////////////////////////////////////
			// Purpose:
			//  User determined.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual OVERLOAD CORE void Before_Queue();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::After_Queue
			// //////////////////////////////////////////////////
			// Purpose:
			//  User determined.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
				virtual OVERLOAD CORE void After_Queue();

		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			PW_DUNI_PTR(GLFWwindow, Engine_Constant::Destroy_GLFW) main_window;
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONTROL