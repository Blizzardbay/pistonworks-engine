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
		static PW_VOID Init_Default_Input_Callbacks();
		static PW_FLOAT Get_Move_Increment() { return move_increment; }
/* Public Variables         */
	public:
		static PW_VOID(*function_arr[(PW_INT)Default_Functions::DEFAULT_FUCNTION_COUNT])();
/* Private Functions/Macros */
	private:
		static PW_VOID Move_Right();
		static PW_VOID Move_Left();
		static PW_VOID Move_Up();
		static PW_VOID Move_Down();

		static PW_VOID Change_Scene();
/* Private Variables        */
	private:
		static PW_FLOAT move_increment;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_DEFAULT_EVENT
