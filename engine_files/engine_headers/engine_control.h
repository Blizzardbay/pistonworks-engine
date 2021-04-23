#ifndef H_ENGINE_CONTROL
#define H_ENGINE_CONTROL
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <stdio.h>
#include <chrono>
#include <iostream>
//////////////////////////////////
// Project Headers
#include <box2d\b2_fixture.h>
//////////////////////////////////
// Engine Headers
#include "engine_queue.h"
#include "internal_engine_headers\ie_event.h"
#include "internal_engine_headers\ie_shader.h"
#include "internal_engine_headers\ie_model.h"
#include "internal_engine_headers\ie_texture.h"
#include "internal_engine_headers\ie_game_scene.h"
#include "internal_engine_headers\ie_camera.h"
#include "internal_engine_headers\ie_game_scene.h"
#include "engine_input.h"
#include "engine_constant.h"
//////////////////////////////////
// Engine Macro Includes
//////////////////////////////////
// Engine Macros
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Classes

	//////////////////////////////////
	// Class Name: pw::Engine_Control
	//
	// Purpose: The main point of the application. Runs all
	//    events and calculations that take place in
	//	  the engine.
	//
	class PW_ENGINE_API Engine_Control {
	// Default Class Structures
	public:
		struct PW_INTERNAL_DATA_API Destroy_GLFW {
			public:
				PW_VOID operator()(GLFWwindow* window);
		};
		// Function: Engine_Control::Engine_Control
		//
		// Purpose: Basic constructor and destructor for
		//    this class. They are here purely for and object
		//    that controls the engine.
		//
		Engine_Control();
		// Function: Engine_Control::~Engine_Control
		//
		// Purpose: Basic constructor and destructor for
		//    this class. They are here purely for and object
		//    that controls the engine.
		//
		~Engine_Control();
	private:
    // Public Functions/Macros
	public:
		// Function: Engine_Control::Init_Engine
		//
		// Purpose: Init engine make all of the default glew and glfw
		//    init's that are needed for the application to work.
		//    Also init's engine constants and runtime variables
		//    on top of shader control.
		//
		PW_VOID Init_Engine(PW_CSTRING display_name, PW_SINT display_width = 800, PW_SINT display_height = 608);
		//////////////////////////////////
		// Function: Engine_Control::Run_Engine
		//
		// Purpose: Runs the engine queue system and makes sure the runtime exceptions are handled
		//    and that runtime variables are up to date when used.
		//	  Check / handles input and if the window should close.
		//
		PW_VOID Run_Engine();
		// Function: Engine_Control::Create_Player
		//
		// Purpose: Creates the player character.
		//
		PW_VOID Create_Player();
		// Function: Engine_Control::Terminate_Engine
		//
		// Purpose: Destroys and deallocates all engine.
		//
		PW_VOID Terminate_Engine();
		// Function: Engine_Control::Create_Callbacks
		//
		// Purpose: Creates the input callbacks. 
		//
		PW_VOID Create_Callbacks() const;
		// Function: Engine_Control::Update_Engine_State
		//
		// Purpose: Swaps opengl buffers. 
		//
		PW_VOID Update_Engine_State();
		// Function: Engine_Control::Should_Close
		//
		// Purpose: Tests if the window should close or not.
		//
		PW_BOOL Should_Close() const;
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		PW_DUNI_PTR(GLFWwindow, Destroy_GLFW) main_window;
	};
	// Functions
	// Macros
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONTROL