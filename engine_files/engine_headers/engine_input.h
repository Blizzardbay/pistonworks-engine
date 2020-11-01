#ifndef H_ENGINE_INPUT
#define H_ENGINE_INPUT

//(DUAL_FILE)

/* C++ Headers           */
#include <vector>
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
		Input_Event_Key(void(* event_)()) : event_(NULL), key(NULL), is_pressed(false), only_on_press(false) { this->event_ = event_; }
		~Input_Event_Key() { event_ = nullptr; }

		void Hit() { is_pressed = true; }
		bool Get_Pressed_State() { return is_pressed; }

		GLint Get_Key() { return key; }
		void Set_Key(GLint new_key) { key = new_key; }

		bool Get_Press_Setting() { return only_on_press; }
		void Set_Press_Setting(bool setting_state) { only_on_press = setting_state; }

		void(*event_)();
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		GLint key;
		bool is_pressed;

		bool only_on_press;
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
		static void Init_Default_Binds();

		static void Handle_Keys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode);
		static void Handle_Mouse(GLFWwindow* window, GLdouble mouse_xpos, GLdouble mouse_ypos);
		static void Handle_Resize(GLFWwindow* window, int window_width, int window_height);

		static glm::vec2 Get_Cursor_Position();

		static float Get_Cursor_X_Pos() { return cursor_last_xpos; }
		static float Get_Cursor_Y_Pos() { return cursor_last_ypos; }

		static void Handle_Events(GLint key, GLint action);

		static bool Is_Key(GLint key);

		static void Poll_Active_Events();

		static void Create_New_Bind(GLint key_code, void(*function_ptr)(), bool only_play_once = false);

		static void Set_Default_Binds(bool state) { has_default_binds = state; }

/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static GLint current_key_code;

		static GLfloat cursor_last_xpos;
		static GLfloat cursor_last_ypos;

		static GLfloat cursor_pos_xchange;
		static GLfloat cursor_pos_ychange;

		static bool startup_state;

		static bool has_default_binds;

		static Input_Event_Key keys[1024];

		static std::vector<Input_Event_Key> current_active_keys;
	};
/* Functions                */
}
#endif // !H_ENGINE_INPUT