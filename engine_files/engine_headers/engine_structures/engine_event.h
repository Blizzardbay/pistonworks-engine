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
#ifndef H_ENGINE_EVENT
#define H_ENGINE_EVENT
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers  
#include <queue>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers    
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
	// Internal Engine              //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Event
		// //////////////////////////////////////////////////
		// Purpose:
		//  A class to handle all different types of events.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Event {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Event::Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Initializes all event variables, does not find
			//  trigger.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Event();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Event::Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Initializes and finds a trigger for the event.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_INPUT_TYPE trigger;
			// Purpose: 
			//  The type of interaction that triggers the
			//  callback function.
			// (2) PW_SRD_PTR(PW_FUNCTION) trigger_function;
			// Purpose: 
			//  The function to be triggered once a event is
			//  called.
			// (3) bool play_once;
			// Purpose: 
			//  Should we only play the event once or until the
			//  trigger stops.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once);
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Event::Trigger_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Triggers the function that the event has on
			//  callback.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Trigger_Event();
			// //////////////////////////////////////////////////
			// CORE Function: Event::Find_Resolution
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Triggers the function that the event has on
			//  callback.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_INPUT_TYPE trigger;
			// Purpose:
			//  Find the resolution to a trigger, this finds
			//  what the state the event would be in when it is
			//  not to be triggered. Not every event has a
			//  resolution. 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE PW_INPUT_TYPE Find_Resolution(PW_INPUT_TYPE trigger);
			// Mutator
			USER_INTERACTION
			MUTATOR void Set_Function(PW_SRD_PTR(PW_FUNCTION) new_function);
			// Accessors
			USER_INTERACTION
			ACCESSOR PW_INPUT_TYPE Trigger();
			USER_INTERACTION
			ACCESSOR PW_INPUT_TYPE Resolution();
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(PW_FUNCTION) Function();
			USER_INTERACTION
			ACCESSOR bool Play_State();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables    
		private:
			PW_SRD_PTR(PW_FUNCTION) function;
			bool play_once;
			PW_INPUT_TYPE trigger;
			PW_INPUT_TYPE resolution;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Mouse_Event
		// //////////////////////////////////////////////////
		// Purpose:
		//  To handle mouse centered button events.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Mouse_Event : public Event {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Mouse_Event::Mouse_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Initializes a mouse event. Automatically finds
			//  trigger resolution.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_INPUT_TYPE trigger;
			// Purpose: 
			//  The type of interaction that triggers the
			//  callback function.
			// (2) PW_SRD_PTR(PW_FUNCTION) trigger_function;
			// Purpose: 
			//  The function to be triggered once a event is
			//  called.
			// (3) bool play_once;
			// Purpose: 
			//  Should we only play the event once or until the
			//  trigger stops.
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Mouse_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once);
		private:
		// Public Functions/Macros  
		public:
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables     
		private:
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Keyboard_Event
		// //////////////////////////////////////////////////
		// Purpose:
		//  To handle keyboard centered events.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Keyboard_Event : public Event
		{
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Keyboard_Event::Keyboard_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Initializes the keyboard event structure along
			//  with a standard event structure.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_INPUT_TYPE trigger;
			// Purpose: 
			//  The type of interaction that triggers the
			//  callback function.
			// (2) PW_SRD_PTR(PW_FUNCTION) trigger_function;
			// Purpose: 
			//  The function to be triggered once a event is
			//  called.
			// (3) bool play_once;
			// Purpose: 
			//  Should we only play the event once or until the
			//  trigger stops.
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Keyboard_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once);
		private:
		// Public Functions/Macros 
		public:
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables 
		private:
		};
		// Functions              
		// Macros / Definitions                 
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_EVENT