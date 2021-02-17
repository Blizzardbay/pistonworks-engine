#ifndef H_IE_COMPLEX_EVENT
#define H_IE_COMPLEX_EVENT

//(HEADER_ONLY)

/* C++ Headers              */
/* Project Headers          */
/* Engine Headers           */
#include "ie_event.h"
/* Engine Macro Includes    */
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
		/* -Complex_Event
		 Events that happen when models or other processes
		 are triggered.
		*/
		class Complex_Event : public Event {
	/* Default Class Structures */
		public:
			Complex_Event(PW_VOID(*trigger_function)(), PW_BOOL play_once) :
					Event(NULL, trigger_function, play_once) {
			}
		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Event_Callback() {}
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
		};
		/* -Model_Hover_Event
		 Events that happen when models are hovered over.
		*/
		class Model_Hover_Event : public Complex_Event {
	/* Default Class Structures */
		public:
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
		/* -Model_Click_Event
		 Events that happen when models are clicked.
		*/
		class Model_Click_Event : public Model_Hover_Event {
	/* Default Class Structures */
		public:
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
		/* -Model_Collision_Event
		 Events that happen when models collide with one and another.
		*/
		class Model_Collision_Event : public Complex_Event {
	/* Default Class Structures */
		public:
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
		/* -Model_Change_Event
		 Events that happen when models changes a certain variable.
		*/
		class Model_Change_Event : public Complex_Event {
	/* Default Class Structures */
		public:
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
#endif // !H_IE_COMPLEX_EVENT