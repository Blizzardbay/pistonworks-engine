#include "engine_structures\engine_event.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Event               
		// Static Declarations   
		// Class Members        
			Event::Event() :
					function(NULL), play_once(NULL), trigger(NULL), resolution(NULL) {
			}
			Event::Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once) :
					function(NULL), play_once(play_once), trigger(trigger), resolution(NULL) {

				function = trigger_function;
				resolution = Find_Resolution(trigger);
			}
			void Event::Trigger_Event() {
				(*function)();
			}
			PW_INPUT_TYPE Event::Find_Resolution(PW_INPUT_TYPE trigger) {
				if (trigger == cm::Engine_Constant::PW_CONDIONAL_EVENT) {
					return cm::Engine_Constant::PW_ACONDIONAL_EVENT;
				}
				switch (trigger) {
					case GLFW_PRESS: {
						return GLFW_RELEASE;
					}
					case GLFW_RELEASE: {
						return GLFW_PRESS;
					}
					case GLFW_REPEAT: {
						return GLFW_PRESS | GLFW_RELEASE;
					}
					default: {
						return NULL;
					}
				}
			}
			void Event::Set_Function(PW_SRD_PTR(PW_FUNCTION) new_function) {
				function = new_function;
			}
			PW_INPUT_TYPE Event::Trigger() { 
				return trigger;
			}
			PW_INPUT_TYPE Event::Resolution() {
				return resolution;
			}
			PW_SRD_PTR(PW_FUNCTION) Event::Function() {
				return function;
			}
			bool Event::Play_State() {
				return play_once;
			}
		// End of Class Members
		// Mouse_Event       
		// Static Declarations  
		// Class Members
			Mouse_Event::Mouse_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once) :
					Event(trigger, trigger_function, play_once) {
			}
		// End of Class Members
		// Keyboard_Event       
		// Static Declarations  
			Keyboard_Event::Keyboard_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once) :
					Event(trigger, trigger_function, play_once) {
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////