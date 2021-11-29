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
#include "engine_structures\engine_event.h"
#include "engine_structures\engine_camera.h"
//////////////////////////////////
// Engine Macro Includes
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Macros 
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// //////////////////////////////////////////////////
		// PW_CONTROL_API Class Name: pw::Engine_Input
		// //////////////////////////////////////////////////
		// Purpose:
		//  For handling input
		//  events in the engine.
		// //////////////////////////////////////////////////
		class PW_CONTROL_API Engine_Input {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Engine_Input::Engine_Input
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a input structure for the engine to use.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Engine_Input();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Engine_Input::Engine_Input
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a input structure for the engine to use.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) std::map<PW_INPUT_TYPE, st::Keyboard_Event>* current_key_events;
			// Purpose: 
			//  A pointer to the current key events the
			//  structure any have.
			// (2) std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, st::Keyboard_Event>>* key_events;
			// Purpose: 
			//  A pointer to the key events the structure any
			//  have.
			// Parameters: 2
			// (3) std::map<PW_INPUT_TYPE, st::Mouse_Event>* current_mouse_events;
			// Purpose: 
			//  A pointer to the current mouse events the
			//  structure any have.
			// (4) std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, st::Mouse_Event>>* mouse_events;
			// Purpose: 
			//  A pointer to the mouse events the structure any
			//  have.
			// (5) std::map<PW_SCROLL_ACTION, st::Mouse_Event>* scroll_events;
			// Purpose: 
			//  A pointer to the scroll events the structure
			//  any have.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Engine_Input(
				std::vector<st::Event_Base*> p_current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> p_key_events,
				std::vector<st::Event_Base*> p_current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> p_mouse_events,
				std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> p_scroll_events);
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete all of the related members.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Handle_Keyboard
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Acts as a callback to a glfw input function.
			//  Note that this callback function requires default
			//  types.
			// //////////////////////////////////////////////////
			// Parameters: CALLBACK EXCEPTION
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Keyboard(GLFWwindow* window, int key, int code, int action, int mode);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Handle_Mouse_Movement
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Acts as a callback to a glfw input function.
			//  Note that this callback function requires default
			//  types.
			// //////////////////////////////////////////////////
			// Parameters: CALLBACK EXCEPTION
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Mouse_Movement(GLFWwindow* window, double mouse_xpos, double mouse_ypos);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Handle_Mouse_Button
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Acts as a callback to a glfw input function.
			//  Note that this callback function requires default
			//  types.
			// //////////////////////////////////////////////////
			// Parameters: CALLBACK EXCEPTION
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Mouse_Button(GLFWwindow* window, int button, int action, int mods);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Handle_Resize
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Acts as a callback to a glfw input function.
			//  Note that this callback function requires default
			//  types.
			// //////////////////////////////////////////////////
			// Parameters: CALLBACK EXCEPTION
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Resize(GLFWwindow* window, int window_width, int window_height);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Handle_Mouse_Scroll
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Acts as a callback to a glfw input function.
			//  Note that this callback function requires default
			//  types.
			// //////////////////////////////////////////////////
			// Parameters: CALLBACK EXCEPTION
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Mouse_Scroll(GLFWwindow* window, double xoffset, double yoffset);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Poll_Active_Events
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Polls the input structure for the playing of any
			//  events that are active.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Poll_Active_Events();
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Create_Event_Keyboard
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a keyboard event for the input structure.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) PW_INPUT_TYPE action;
			// Purpose:
			//  The type of action that will trigger the event.
			//  GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
			// (2) PW_KEY_CODE key_code;
			// Purpose:
			//  The key code of the key that will be pressed.
			//  Must be a ASCII standard keyboard code.
			// (3) PW_SRD_PTR(PW_FUNCTION) function_ptr;
			// Purpose:
			//  A pointer to the function that will be called on
			//  triggering of the event.
			// (4) bool only_play_once;
			// Purpose:
			//  Should this event only be played once or until
			//  its termination of action. Per frame basis.
			//  GLFW_PRESS ends with GLFW_RELEASE eta.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Create_Event_Keyboard(PW_INPUT_TYPE action, PW_KEY_CODE key_code, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Create_Event_Mouse
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a mouse event for the input structure.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) PW_INPUT_TYPE action;
			// Purpose:
			//  The type of action that will trigger the event.
			//  GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
			// (2) PW_BUTTON_CODE code;
			// Purpose:
			//  The GLFW button code.
			// (3) PW_SRD_PTR(PW_FUNCTION) function_ptr;
			// Purpose:
			//  A pointer to the function that will be called on
			//  triggering of the event.
			// (4) bool only_play_once;
			// Purpose:
			//  Should this event only be played once or until
			//  its termination of action. Per frame basis.
			//  GLFW_PRESS ends with GLFW_RELEASE eta.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Create_Event_Mouse(PW_INPUT_TYPE action, PW_BUTTON_CODE code, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Create_Event_Mouse
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a mouse event for the input structure.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_INPUT_TYPE action;
			// Purpose:
			//  The type of action that will trigger the event.
			//  In the case of the scroll wheel it can only be
			//  moved.
			//  GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
			// (2) PW_SRD_PTR(PW_FUNCTION) function_ptr;
			// Purpose:
			//  A pointer to the function that will be called on
			//  triggering of the event.
			// (3) bool only_play_once;
			// Purpose:
			//  Should this event only be played once or until
			//  its termination of action. Per frame basis.
			//  GLFW_PRESS ends with GLFW_RELEASE eta.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Create_Event_Scroll(PW_SCROLL_ACTION action, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once);
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Input::Register_Function
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Registers a function for use for once loaded 
			//  scene input.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) std::string function_name;
			// Purpose:
			//  The exact name of the function being registered.
			// (2) PW_SRD_PTR(PW_FUNCTION) function;
			// Purpose:
			//  A pointer to the function that will be called on
			//  triggering of the event.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static CORE void Register_Function(std::string function_name, PW_SRD_PTR(PW_FUNCTION) function);
			// Accessors
			USER_INTERACTION
			static ACCESSOR Engine_Input* Current_Input();
			USER_INTERACTION
			static ACCESSOR PW_SRD_PTR(PW_FUNCTION) Access_Function(std::string function_name);
			// Mutators
			USER_INTERACTION
			static MUTATOR void Set_Current_Input(Engine_Input* new_input);
			USER_INTERACTION
			static MUTATOR void Set_Refresh_Function(PW_FUNCTION new_refresh);
			USER_INTERACTION
			static MUTATOR void Set_Scene_Event_Function(COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) new_scene_event_function);
		// Public Variables       
		public:
			std::vector<st::Event_Base*> current_key_events;
			std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> key_events;
			std::vector<st::Event_Base*> current_mouse_events;
			std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> mouse_events;
			std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> scroll_events;
			uint64_t event_id_assigner;
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
			// This is a pointer to the current input that we are using.
			static Engine_Input* current_input;
			static std::map<std::string, PW_SRD_PTR(PW_FUNCTION)> function_register;
			static PW_FUNCTION refresh_function;
			static COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) scene_event_function;
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////               
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_INPUT