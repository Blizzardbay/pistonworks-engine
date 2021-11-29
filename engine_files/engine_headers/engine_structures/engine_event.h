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
#include <functional>
#include <type_traits>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers
#include "engine_structures\engine_game_header.h"
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
		// PW_STRUCTURES_API Class Name: pw::st::Event_Base
		// //////////////////////////////////////////////////
		// Purpose:
		//  A base class that handles basic event information
		//  .
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Event_Base {
		// Default Class Structures
		public:
			Event_Base(bool p_play_once, PW_INPUT_TYPE p_trigger, PW_INPUT_TYPE p_resolution);
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Event_Base::Trigger_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Triggers the function that the event has on
			//  callback.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			virtual CORE void Trigger_Event();
			// //////////////////////////////////////////////////
			// CORE Function: Event_Base::Find_Resolution
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
			PW_INPUT_TYPE Find_Resolution(PW_INPUT_TYPE trigger);
			// Accessors
			PW_INPUT_TYPE Trigger();
			PW_INPUT_TYPE Resolution();
			bool Play_State();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables    
		private:
			bool m_play_once;
			PW_INPUT_TYPE m_trigger;
			PW_INPUT_TYPE m_resolution;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Event
		// //////////////////////////////////////////////////
		// Purpose:
		//  A class to handle all different types of events.
		// //////////////////////////////////////////////////
		template<class function_type, class mem_class, class type, class ...args>
		class PW_STRUCTURES_API Event : public Event_Base {
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
			Event() :
				Event_Base(NULL, NULL, NULL), m_function(nullptr), m_object(nullptr) {
			}
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
			Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(std::function<type(args...)>) trigger_function, bool play_once, args... arguments) :
				Event_Base(play_once, trigger, Find_Resolution(trigger)), m_function(std::bind(*trigger_function.get(), std::move(arguments)...)), m_object( nullptr ) {
			}
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Event::Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Initializes and finds a trigger for the event.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) PW_INPUT_TYPE trigger;
			// Purpose: 
			//  The type of interaction that triggers the
			//  callback function.
			// (2) bool play_once;
			// Purpose: 
			//  Should we only play the event once or until the
			//  trigger stops.
			// (3) std::_Mem_fn<function> function;
			// Purpose: 
			//  The function to be triggered once a event is
			//  called.
			// (4) mem_class& object;
			// Purpose: 
			//  The object the function belongs to.
			// (5) args... arguments;
			// Purpose: 
			//  Arguments for the function.
			// //////////////////////////////////////////////////
			Event(PW_INPUT_TYPE trigger, bool play_once, std::_Mem_fn<function_type> function, mem_class& object, args... arguments) :
				Event_Base(play_once, trigger, Find_Resolution(trigger)), m_function(std::bind(function, &object, std::move(arguments)...)), m_object( &object ) {
			}
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
			void Trigger_Event() override {
				if (m_function.type() == typeid(std::_Binder<struct std::_Unforced, class std::function<void __cdecl(void)>&>)) {
					std::any_cast<std::_Binder<struct std::_Unforced, class std::function<void __cdecl(void)>&>>(m_function)();
				}
				else {
					if (m_function.type() == typeid(std::_Binder<struct std::_Unforced, class std::_Mem_fn<void (pw::st::AActor_Model::*)(class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t> >, bool)> &, class pw::st::AActor_Model*, class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t> > const, bool>)) {
						std::any_cast<std::_Binder<struct std::_Unforced, class std::_Mem_fn<void (pw::st::AActor_Model::*)(class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t> >, bool)>&, class pw::st::AActor_Model*, class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t> > const, bool>>(m_function)();
					}
					else {
						if (m_function.type() == typeid(std::_Binder<struct std::_Unforced, class std::_Mem_fn<void (pw::st::AActor_Model::*)(void)> &, class pw::st::AActor_Model*>)) {
							std::any_cast<std::_Binder<struct std::_Unforced, class std::_Mem_fn<void (pw::st::AActor_Model::*)(void)>&, class pw::st::AActor_Model*>>(m_function)();
						}
						else {
							if (m_function.type() == typeid(std::_Binder<std::_Unforced, std::function<void(std::wstring, bool)>&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>const, bool>)) {
								std::any_cast<std::_Binder<std::_Unforced, std::function<void(std::wstring, bool)>&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>const, bool>>(m_function)();
							}
							else {
								if (m_function.type() == typeid(std::_Binder<std::_Unforced, std::function<void(std::wstring)> &, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>const>)) {
									std::any_cast<std::_Binder<std::_Unforced, std::function<void(std::wstring)>&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>const>>(m_function)();
								}
							}
						}
					}
				}
			}
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables    
		private:
			std::any m_function;
			mem_class* m_object;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Mouse_Event
		// //////////////////////////////////////////////////
		// Purpose:
		//  To handle mouse centered button events.
		// //////////////////////////////////////////////////
		template<class type, class ...args>
		class PW_STRUCTURES_API Mouse_Event : public Event<int, int, type, args...> {
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
			CLASS_FUNCTION Mouse_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(std::function<type(args...)>) trigger_function, bool play_once) :
					Event<int, int, type, args...>(trigger, trigger_function, play_once) {
			}
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
		template<class type, class ...args>
		class PW_STRUCTURES_API Keyboard_Event : public Event<int, int, type, args...>
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
			CLASS_FUNCTION Keyboard_Event(PW_BUTTON_CODE button, PW_INPUT_TYPE trigger, PW_SRD_PTR(std::function<type(args...)>) trigger_function, bool play_once) :
					Event<int, int,type, args...>(trigger, trigger_function, play_once), m_button(button) {
			}
		private:
		// Public Functions/Macros 
		public:
			// Accessors
			USER_INTERACTION
			ACCESSOR PW_BUTTON_CODE Button() {
				return m_button;
			}
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables 
		private:
			PW_BUTTON_CODE m_button;
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