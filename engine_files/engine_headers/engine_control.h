#ifndef H_ENGINE_CONTROL
#define H_ENGINE_CONTROL

//(DUAL_FILE)

/* C++ Headers              */
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
/* Project Headers          */
#include "GL\glew.h"
#include "GLFW\glfw3.h"
/* Engine Headers           */
#include "engine_queue.h"
#include "internal_engine_headers\ie_event.h"
#include "internal_engine_headers\ie_shader.h"
#include "internal_engine_headers\ie_model.h"
#include "internal_engine_headers\ie_texture.h"
#include "internal_engine_headers\ie_game_scene.h"
#include "internal_engine_headers\ie_camera.h"
#include "internal_engine_headers\ie_player.h"
#include "engine_input.h"
#include "engine_constant.h"
/* Engine Macro Includes    */
#include "engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (Engine_Control)                            ]
	 The main point of the application. Runs all
	 events and calculations that take place in
	 the engine.
	*/
	class Engine_Control {
/* Default Class Structures */
	public:
		/*	(Engine_Control & ~Engine_Control)
		 Purpose: Basic constructor and destructor for
		  this class. They are here purely for and object
		  that controls the engine.
		 Other: N/A
		*/
		Engine_Control() : main_window{ 0 } {}
		/*	(Engine_Control & ~Engine_Control)
		 Purpose: Basic constructor and destructor for
		  this class. They are here purely for and object
		  that controls the engine.
		 Other: N/A
		*/
		~Engine_Control() {}
	private:
/* Public Functions/Macros  */
	public:
		/*	(Init_Engine)
		 Purpose: Init engine make all of the default glew and glfw
		  init's that are needed for the application to work.
		 Other: Also init's engine constants and runtime variables on top of shader control.
		*/
		PW_VOID Init_Engine(PW_CSTRING display_name, PW_SINT display_width = 800, PW_SINT display_height = 608);
		/*	(Run_Engine)
		 Purpose: Runs the engine queue system and makes sure the runtime exceptions are handled
		  and that runtime variables are up to date when used.
		 Other: Check / handles input and if the window should close.
		*/
		PW_VOID Run_Engine();
		PW_VOID Terminate_Engine();
		PW_VOID Create_Callbacks() const;
		PW_VOID Update_Engine_State();
		PW_BOOL Should_Close() const { return !glfwWindowShouldClose(this->main_window); }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		GLFWwindow* main_window;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_ENGINE_CONTROL