#include "internal_engine_headers\ie_event.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// Event               
		// Static Declarations   
		// Class Members        
			Event::Event() :
					function(NULL), play_once(NULL), trigger(NULL), resolution(NULL) {
			}
			Event::Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once) :
					function(NULL), play_once(play_once), trigger(trigger), resolution(NULL) {

				function = trigger_function;
				resolution = Find_Resolution(trigger);
			}
			PW_VOID Event::Trigger_Event() {
				(*function)();
			}
			PW_INPUT_TYPE Event::Find_Resolution(PW_INPUT_TYPE trigger) {
				if (trigger == Engine_Constant::PW_CONDIONAL_EVENT) {
					return Engine_Constant::PW_ACONDIONAL_EVENT;
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
			PW_VOID Event::Set_Function(PW_SRD_PTR(PW_FUNCTION) new_function) {
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
			PW_BOOL Event::Play_State() {
				return play_once;
			}
		// End of Class Members
		// Mouse_Event       
		// Static Declarations  
		// Class Members
			// Mouse_Coord_Vec2
			// Static Declarations
			// Class Members
				Mouse_Event::Mouse_Coord_Vec2::Mouse_Coord_Vec2(PW_INT x, PW_INT y) :
						x(x), y(y) {
				}
			// End of Class Members
			Mouse_Event::Mouse_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once) :
					Event(trigger, trigger_function, play_once), mouse_coords(NULL, NULL) {
			}
			PW_VOID Mouse_Event::Trigger_Function() {
				(*Function())();
				mouse_coords.x = Engine_Constant::Mouse_X_Coord();
				mouse_coords.x = Engine_Constant::Mouse_Y_Coord();
			}
			PW_VOID Mouse_Event::Set_Mouse_Coord(PW_INT x, PW_INT y) {
				mouse_coords.x = x;
				mouse_coords.y = y;
			}
			Mouse_Event::Mouse_Coord_Vec2 Mouse_Event::Mouse_Coord() {
				return mouse_coords;
			}
		// End of Class Members
		// Keyboard_Event       
		// Static Declarations  
			Keyboard_Event::Keyboard_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once) :
					Event(trigger, trigger_function, play_once) {
			}
		// End of Class Members
		// Model_Event              
		// Static Declarations     
		// Class Members           
			Model_Event::Model_Event(PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once) :
					Event(NULL, trigger_function, play_once) {
			}
		// End of Class Members
		// Collision_Event        
		// Static Declarations    
		// Class Members          
			Collision_Event::Collision_Event(PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once) :
					Model_Event(trigger_function, play_once) {
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////