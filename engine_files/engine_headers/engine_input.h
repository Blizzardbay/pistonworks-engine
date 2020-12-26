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
#include "internal_engine_headers\ie_default_event.h"
#include "internal_engine_headers\ie_camera.h"
#include "internal_engine_headers\ie_player.h"
#include "engine_constant.h"
/* Engine Macro Includes */
#include "engine_error.h"
/* Engine Macros         */
/*************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (Input_Event)                               ]
	 For handling events in the engine.
	*/
	struct Input_Event_Key {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		Input_Event_Key() : event_(NULL), key(NULL), is_pressed(false), only_on_press(false) {}
		Input_Event_Key(PW_VOID(* event_)()) : event_(NULL), key(NULL), is_pressed(false), only_on_press(false) { this->event_ = event_; }
		~Input_Event_Key() { event_ = nullptr; }

		PW_VOID Hit() { is_pressed = true; }
		PW_BOOL Get_Pressed_State() { return is_pressed; }

		GLint Get_Key() { return key; }
		PW_VOID Set_Key(GLint new_key) { key = new_key; }

		PW_BOOL Get_Press_Setting() { return only_on_press; }
		PW_VOID Set_Press_Setting(bool setting_state) { only_on_press = setting_state; }

		PW_VOID(*event_)();
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		GLint key;
		PW_BOOL is_pressed;

		PW_BOOL only_on_press;
	};
	/*[ (Engine_Input)                              ]
	 For handling input events in the engine.
	*/
	class Engine_Input {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static PW_VOID Init_Default_Binds();

		static PW_VOID Handle_Keys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode);
		static PW_VOID Handle_Mouse(GLFWwindow* window, GLdouble mouse_xpos, GLdouble mouse_ypos);
		// Note that this callback function requires type int instead of type PW_INT
		static PW_VOID Handle_Resize(GLFWwindow* window, int window_width, int window_height);

		static glm::vec2 Get_Cursor_Position();

		static PW_FLOAT Get_Cursor_X_Pos() { return cursor_last_xpos; }
		static PW_FLOAT Get_Cursor_Y_Pos() { return cursor_last_ypos; }

		static PW_VOID Handle_Events(GLint key, GLint action);

		static PW_BOOL Is_Key(GLint key);

		static PW_VOID Poll_Active_Events();

		static PW_VOID Create_New_Bind(GLint key_code, PW_VOID(*function_ptr)(), PW_BOOL only_play_once = false);

		static PW_VOID Set_Default_Binds(PW_BOOL state) { has_default_binds = state; }

/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static PW_INT current_key_code;

		static PW_FLOAT cursor_last_xpos;
		static PW_FLOAT cursor_last_ypos;

		static PW_FLOAT cursor_pos_xchange;
		static PW_FLOAT cursor_pos_ychange;

		static PW_BOOL startup_state;

		static PW_BOOL has_default_binds;

		static Input_Event_Key keys[1024];

		static std::map<PW_UINT, Input_Event_Key> current_active_keys;
	};
/* Functions                */
}
#endif // !H_ENGINE_INPUT