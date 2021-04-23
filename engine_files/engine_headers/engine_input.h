#ifndef H_ENGINE_INPUT
#define H_ENGINE_INPUT
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <vector>
#include <map>
//////////////////////////////////
// Project Headers
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
//////////////////////////////////
// Engine Headers 
#include "internal_engine_headers\ie_camera.h"
#include "internal_engine_headers\ie_event.h"
#include "internal_engine_headers\ie_game_scene.h"
#include "engine_queue.h"
#include "engine_constant.h"
//////////////////////////////////
// Engine Macro Includes
#include "engine_error.h"
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
	// Class Name: pw::Engine_Input
	//
	// Purpose: For handling input
	//    events in the engine.
	//
	class PW_ENGINE_API Engine_Input {
	// Default Class Structures
	public:
	private:
	// Public Functions/Macros
	public:
		// Function: Engine_Input::Init_Default_Binds
		//
		// Purpose: Initializes default keys pre-set for the engine. 
		//
		static PW_VOID Init_Default_Binds();
		// Function: Engine_Input::Handle_Keyboard
		//
		// Purpose: Acts as a callback to a glfw input function.
		//    Note that this callback function requires default types.
		static PW_VOID Handle_Keyboard(GLFWwindow* window, int key, int code, int action, int mode);
		// Function: Engine_Input::Handle_Mouse_Movement
		//
		// Purpose: Acts as a callback to a glfw input function.
		//    Note that this callback function requires default types.
		static PW_VOID Handle_Mouse_Movement(GLFWwindow* window, double mouse_xpos, double mouse_ypos);
		// Function: Engine_Input::Handle_Mouse_Button
		//
		// Purpose: Acts as a callback to a glfw input function.
		//    Note that this callback function requires default types.
		static PW_VOID Handle_Mouse_Button(GLFWwindow* window, int button, int action, int mods);
		// Function: Engine_Input::Handle_Resize
		//
		// Purpose: Acts as a callback to a glfw input function.
		//    Note that this callback function requires default types.
		static PW_VOID Handle_Resize(GLFWwindow* window, int window_width, int window_height);
		// Function: Engine_Input::Handle_Mouse_Scroll
		//
		// Purpose: Acts as a callback to a glfw input function.
		//    Note that this callback function requires default types.
		static PW_VOID Handle_Mouse_Scroll(GLFWwindow* window, double xoffset, double yoffset);
		// Function: Engine_Input::Poll_Active_Events
		//
		// Purpose: Initializes default keys pre-set for the engine. 
		//
		static PW_VOID Poll_Active_Events();
		// Function: Engine_Input::Create_Event_Keyboard
		//
		// Purpose: Initializes default keys pre-set for the engine. 
		//
		static PW_VOID Create_Event_Keyboard(PW_INPUT_TYPE action, PW_KEY_CODE key_code, PW_SRD_PTR(PW_FUNCTION) function_ptr, PW_BOOL only_play_once);
		// Function: Engine_Input::Create_Event_Mouse
		//
		// Purpose: Initializes default keys pre-set for the engine. 
		//
		static PW_VOID Create_Event_Mouse(PW_INPUT_TYPE action, PW_BUTTON_CODE code, PW_SRD_PTR(PW_FUNCTION) function_ptr, PW_BOOL only_play_once);
		// Function: Engine_Input::Create_Event_Scroll
		//
		// Purpose: Initializes default keys pre-set for the engine. 
		//
		static PW_VOID Create_Event_Scroll(PW_SCROLL_ACTION action, PW_SRD_PTR(PW_FUNCTION) function_ptr, PW_BOOL only_play_once);
	// Public Variables       
	public:
	// Private Functions/Macros 
	private:
		// Function: Engine_Input::Change_Scene
		//
		// Purpose: Changes the current scene. 
		//
		static PW_VOID Change_Scene();
	// Private Variables
	private:
		static std::map<PW_INT, ie::Keyboard_Event> current_key_events;
		static std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, ie::Keyboard_Event>> key_events;
		static std::map<PW_INT, ie::Mouse_Event> current_mouse_events;
		static std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, ie::Mouse_Event>> mouse_events;
		static std::map<PW_SCROLL_ACTION, ie::Mouse_Event> scroll_events;
	};
	// Functions               
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_INPUT