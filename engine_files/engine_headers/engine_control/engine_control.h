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
			CLASS_FUNCTION Engine_Control() = default;
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
			// (1) PW_CSTRING display_name;
			// Purpose: 
			//  The name of the application.
			// (2) PW_INT display_width = 800;
			// Purpose: 
			//  The width of the application.
			// (3) PW_INT display_height = 608;
			// Purpose: 
			//  The height of the application.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Init_Engine(PW_CSTRING display_name, PW_INT display_width = 800, PW_INT display_height = 608);
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
			CORE PW_VOID Run_Engine();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Terminate_Engine
			// //////////////////////////////////////////////////
			// Purpose:
			//	Destroys and deallocates all of the engine.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Terminate_Engine();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Create_Callbacks
			// //////////////////////////////////////////////////
			// Purpose:
			//	Creates the input callbacks.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Create_Callbacks() const;
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Update_Engine_State
			// //////////////////////////////////////////////////
			// Purpose:
			//	Swaps opengl buffers.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Update_Engine_State();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Control::Should_Close
			// //////////////////////////////////////////////////
			// Purpose:
			//	Tests if the window should close or not.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_BOOL Should_Close() const;
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