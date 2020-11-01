#ifndef H_DEFAULT_EVENT
#define H_DEFAULT_EVENT

//(DUAL_FILE)

/* C++ Headers              */
#include <vector>
/* Project Headers          */
#include <glm\glm.hpp>
/* Engine Headers           */
#include "engine_headers\engine_queue.h"
#include "ie_event.h"
#include "ie_player.h"
#include "engine_headers\engine_constant.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (IE_Default_Event)                                  ]
	 A static class for handling default callbacks.
	*/
	class IE_Default_Event {
/* Default Class Structures */
	public:
		enum class Default_Functions {
			MOVE_RIGHT,
			MOVE_LEFT,
			MOVE_UP,
			MOVE_DOWN,
			CHANGE_SCENE,
			DEFAULT_FUCNTION_COUNT
		};
	private:
/* Public Functions/Macros  */
	public:
		static void Init_Default_Input_Callbacks();
/* Public Variables         */
	public:
		static void (*function_arr[(int)Default_Functions::DEFAULT_FUCNTION_COUNT])();
/* Private Functions/Macros */
	private:
		static void Move_Right();
		static void Move_Left();
		static void Move_Up();
		static void Move_Down();

		static void Change_Scene();
/* Private Variables        */
	private:
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_DEFAULT_EVENT
