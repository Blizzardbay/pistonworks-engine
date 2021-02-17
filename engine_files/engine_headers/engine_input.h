#ifndef H_ENGINE_INPUT
#define H_ENGINE_INPUT

//(DUAL_FILE)

/* C++ Headers           */
#include <vector>
#include <map>
/* Project Headers       */
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
/* Engine Headers        */
#include "internal_engine_headers\ie_camera.h"
#include "internal_engine_headers\ie_player.h"
#include "internal_engine_headers\ie_event.h"
#include "engine_queue.h"
#include "engine_constant.h"
/* Engine Macro Includes */
#include "engine_error.h"
/* Engine Macros         */
/*************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
/* Classes                  */
//
	/* -Engine_Input
	 For handling input events in the engine.
	*/
	class Engine_Input {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static PW_VOID Init_Default_Binds();
		// Note that this callback function requires default types
		static PW_VOID Handle_Keyboard(GLFWwindow* window, int key, int code, int action, int mode);
		// Note that this callback function requires default types
		static PW_VOID Handle_Mouse_Movement(GLFWwindow* window, double mouse_xpos, double mouse_ypos);
		// Note that this callback function requires default types
		static PW_VOID Handle_Mouse_Button(GLFWwindow* window, int button, int action, int mods);
		// Note that this callback function requires default types
		static PW_VOID Handle_Resize(GLFWwindow* window, int window_width, int window_height);
		// Note that this callback function requires default types
		static PW_VOID Handle_Mouse_Scroll(GLFWwindow* window, double xoffset, double yoffset);

		static PW_VOID Poll_Active_Events();

		static PW_VOID Create_Event_Keyboard(PW_INPUT_TYPE action, PW_KEY_CODE key_code, void(*function_ptr)(), PW_BOOL only_play_once);

		static PW_VOID Create_Event_Mouse(PW_INPUT_TYPE action, PW_BUTTON_CODE code, void(*function_ptr)(), PW_BOOL only_play_once);
		static PW_VOID Create_Event_Scroll(PW_SCROLL_ACTION action, void(*function_ptr)(), PW_BOOL only_play_once);

/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		static PW_VOID Move_Right() {
			ie::Player::Set_Player_X_Position(ie::Player::Player_X_Position() + 120 * (Engine_Constant::Delta_Time().count() / 1000));
		}
		static PW_VOID Move_Left() {
			ie::Player::Set_Player_X_Position(ie::Player::Player_X_Position() - 120 * (Engine_Constant::Delta_Time().count() / 1000));
		}
		static PW_VOID Move_Up() {
			ie::Player::Set_Player_Y_Position(ie::Player::Player_Y_Position() + 120 * (Engine_Constant::Delta_Time().count() / 1000));
		}
		static PW_VOID Move_Down() {
			ie::Player::Set_Player_Y_Position(ie::Player::Player_Y_Position() - 120 * (Engine_Constant::Delta_Time().count() / 1000));
		}
		static PW_VOID Change_Scene() {
			Engine_Queue::Change_Scene(Engine_Queue::Scene_Index() + 1);
		}
/* Private Variables        */
	private:
		static std::map<PW_INT, ie::Keyboard_Event> current_key_events;
		static std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, ie::Keyboard_Event>> key_events;
		static std::map<PW_INT, ie::Mouse_Event> current_mouse_events;
		static std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, ie::Mouse_Event>> mouse_events;
		static std::map<PW_SCROLL_ACTION, ie::Mouse_Event> scroll_events;
	};
/* Functions                */
}
#endif // !H_ENGINE_INPUT