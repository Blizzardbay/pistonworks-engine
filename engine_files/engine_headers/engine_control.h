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
		Engine_Control() : main_window{ 0 } {}
		~Engine_Control() {}
	private:
/* Public Functions/Macros  */
	public:
		void Init_Engine(const char* display_name, short int display_width = 800, short int display_height = 608);
		void Run_Engine();
		void Terminate_Engine();
		void Create_Callbacks() const;
		void Update_Engine_State();
		bool Should_Close() const { return !glfwWindowShouldClose(this->main_window); }
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