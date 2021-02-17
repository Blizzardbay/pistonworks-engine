#ifndef H_IE_EVENT
#define H_IE_EVENT

//(HEADER_ONLY)

/* C++ Headers              */
#include <queue>
/* Project Headers          */
/* Engine Headers           */
#include "engine_headers\engine_constant.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
	/* Classes                  */
	//
		/* -Event
		 A class to handle all different types of events.
		*/
		class Event {
	/* Default Class Structures */
		public:
			typedef void(*function_return_)();

			Event() :
				function(NULL), play_once(NULL), trigger(NULL), resolution(NULL) {};
			Event(PW_INPUT_TYPE trigger, void(*trigger_function)(), PW_BOOL play_once) :
				function(NULL), play_once(play_once), trigger(trigger), resolution(NULL) {
				function = trigger_function;
				resolution = Find_Resolution(trigger);
			}
		private:
	/* Public Functions/Macros  */
		public:
			void Trigger_Event() {
				function();
			}
			PW_INPUT_TYPE Trigger() { return trigger; }
			PW_INPUT_TYPE Resolution() { return resolution; }

			PW_INPUT_TYPE Find_Resolution(PW_INPUT_TYPE trigger) {
				if (trigger == PW_CONDIONAL_EVENT) {
					return PW_ACONDIONAL_EVENT;
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
				default:
					return NULL;
				}
			}

			function_return_ Function() {
				return function;
			}
			bool Play_State() { return play_once; }
			void Set_Function(void(*new_function)()) {
				function = new_function;
			}

	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			void(*function)();
			PW_BOOL play_once;
			PW_INPUT_TYPE trigger;
			PW_INPUT_TYPE resolution;
		};
		/* -Mouse_Event
		 To handle mouse centered button events.
		*/
		class Mouse_Event : public Event {
	/*Default Class Structures*/
		public:
			struct Mouse_Coord_Vec2 {
		/*Default Class Structures*/
			public:
				Mouse_Coord_Vec2(PW_INT x, PW_INT y) :
					x(x), y(y) {
				}
			private:
		/* Public Functions/Macros  */
			public:
		/* Public Variables         */
			public:
				PW_INT x;
				PW_INT y;
		/* Private Functions/Macros */
			private:
		/* Private Variables        */
			private:
			};

			Mouse_Event(PW_INPUT_TYPE trigger, void(*trigger_function)(), PW_BOOL play_once) :
				Event(trigger, trigger_function, play_once), mouse_coords(NULL, NULL) {
			}
		private:
	/* Public Functions/Macros  */
		public:
			void Trigger_Function() {
				this->Function()();
				mouse_coords.x = Engine_Constant::Mouse_X_Coord();
				mouse_coords.x = Engine_Constant::Mouse_Y_Coord();
			}

			void Set_Mouse_Coord(PW_INT x, PW_INT y) { mouse_coords.x = x; mouse_coords.y = y; }
			Mouse_Coord_Vec2 Mouse_Coord() { return mouse_coords; }
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			Mouse_Coord_Vec2 mouse_coords;
		};
		/* -Keyboard_Event
		 To handle keyboard centered events.
		*/
		class Keyboard_Event : public Event {
	/*Default Class Structures*/
		public:
			Keyboard_Event(PW_INPUT_TYPE trigger, void(*trigger_function)(), PW_BOOL play_once) :
				Event(trigger, trigger_function, play_once) {
			}
		private:
	/* Public Functions/Macros  */
		public:
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_EVENT