#ifndef H_IE_EVENT
#define H_IE_EVENT
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
#include "engine_headers\engine_constant.h"
//////////////////////////////////
// Engine Macro Includes 
#include "engine_headers\engine_error.h"
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
	IE_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		//////////////////////////////////
		// Class Name: pw::ie::Event
		//																				 
		// Purpose: A class to handle all different types of events.
		//
		class PW_INTERNAL_API Event {
		// Default Class Structures
		public:
			// Function: Event::Event
			//
			// Purpose: Initializes all event variables, does not find trigger.
			//
			Event();
			// Function: Event::Event
			//
			// Purpose: Initializes and finds a trigger for the event.
			//
			Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
		private:
		// Public Functions/Macros 
		public:
			// Function: Event::Trigger_Event
			//
			// Purpose: Triggers the function that the event has on callback.
			//
			PW_VOID Trigger_Event();
			// Function: Event::Find_Resolution
			//
			// Purpose: Find the resolution to a trigger, this finds
			//  what the state the event would be in when it is not
			//  to be triggered. Not every event has a resolution.
			//
			PW_INPUT_TYPE Find_Resolution(PW_INPUT_TYPE trigger);
			// Function: Event::Set_Function
			//
			// Purpose: Sets the function for the event to callback to when triggered.
			//
			PW_VOID Set_Function(PW_SRD_PTR(PW_FUNCTION) new_function);
			// Function: Event::Trigger
			//
			// Purpose: Returns the trigger type used.
			//
			PW_INPUT_TYPE Trigger();
			/// Function: Event::Resolution
			//
			// Purpose: Returns the resolution type used.
			//
			PW_INPUT_TYPE Resolution();
			// Function: Event::Function
			//
			// Purpose: Returns the function callback.
			//
			PW_SRD_PTR(PW_FUNCTION) Function();
			// Function: Event::Play_State
			//
			// Purpose: Returns the current play state of the event.
			//
			PW_BOOL Play_State();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables    
		private:
			PW_SRD_PTR(PW_FUNCTION) function;
			PW_BOOL play_once;
			PW_INPUT_TYPE trigger;
			PW_INPUT_TYPE resolution;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Mouse_Event
		//																				 
		// Purpose: To handle mouse centered button events.
		//
		class PW_INTERNAL_API Mouse_Event : public Event {
		// Default Class Structures
		public:
			//////////////////////////////////
			// Struct Name: pw::ie::Mouse_Event::Mouse_Coord_Vec2
			//																				 
			// Purpose: Holds mouse information at the time of event.
			//
			struct Mouse_Coord_Vec2 {
			// Default Class Structures
			public:
				// Function: Mouse_Coord_Vec2::Mouse_Coord_Vec2
				//
				// Purpose: Initializes the mouse coords.
				//
				Mouse_Coord_Vec2(PW_INT x, PW_INT y);
			private:
			// Public Functions/Macros 
			public:
			// Public Variables        
			public:
				PW_INT x;
				PW_INT y;
			// Private Functions/Macros 
			private:
			// Private Variables     
			private:
			};
			// Function: Mouse_Event::Mouse_Event
		    //
		    // Purpose: Initializes a mouse event. Automatically finds trigger resolution.
			//
			Mouse_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
		private:
		// Public Functions/Macros  
		public:
			// Function: Mouse_Event::Trigger_Function
			//
			// Purpose: Triggers the event's function callback when it is activated.
			//
			PW_VOID Trigger_Function();
			// Function: Mouse_Event::Set_Mouse_Coord
			//
			// Purpose: Sets the mouse coords to some new value.
			//
			PW_VOID Set_Mouse_Coord(PW_INT x, PW_INT y);
			// Function: Mouse_Event::Mouse_Coord
			//
			// Purpose: Gets the mouse coords at the activation point of the event.
			//
			Mouse_Coord_Vec2 Mouse_Coord();
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables     
		private:
			Mouse_Coord_Vec2 mouse_coords;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Keyboard_Event
		//																				 
		// Purpose: To handle keyboard centered events..
		//
		class Keyboard_Event : public Event
		{
		// Default Class Structures
		public:
			// Function: Keyboard_Event::Keyboard_Event
			//
			// Purpose: Initializes the keyboard event structure along with a standard event structure.
			//
			Keyboard_Event(PW_INPUT_TYPE trigger, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
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
		//////////////////////////////////
		// Class Name: pw::ie::Model_Event
		//																				 
		// Purpose: DEPRESHATED
		//
		class PW_INTERNAL_API Model_Event : public Event
		{
		// Default Class Structures
		public:
			// Function: Model_Event::Model_Event
			//
			// Purpose: Used to initialize a model event. 
			//
			Model_Event(PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
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
		//////////////////////////////////
		// Class Name: pw::ie::Collision_Event
		//																				 
		// Purpose: DEPRESHATED
		//
		class Collision_Event : public Model_Event
		{
		// Default Class Structures
		public:
			// Function: Collision_Event::Collision_Event
			//
			// Purpose: Used to initialize a new model collision event.
			//
			Collision_Event(PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
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
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_EVENT