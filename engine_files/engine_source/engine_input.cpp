#include "engine_headers\engine_input.h"
namespace pw {
/* Engine_Input             */
/* Static Declarations      */
	GLint Engine_Input::current_key_code;

	GLfloat Engine_Input::cursor_last_xpos;
	GLfloat Engine_Input::cursor_last_ypos;

	GLfloat Engine_Input::cursor_pos_xchange;
	GLfloat Engine_Input::cursor_pos_ychange;

	bool Engine_Input::startup_state;
	bool Engine_Input::has_default_binds = true;

	Input_Event_Key Engine_Input::keys[1024] = { Input_Event_Key() };

	std::map<unsigned int, Input_Event_Key> Engine_Input::current_active_keys = std::map<unsigned int, Input_Event_Key>();

/* Class Members            */
	void Engine_Input::Init_Default_Binds() {
		for (size_t i = 0; i < 1024; i++) {
			keys[i].Set_Key(NULL);
		}
		if (has_default_binds == true) {
			IE_Default_Event::Init_Default_Input_Callbacks();

			Engine_Input::Create_New_Bind((int)'D', IE_Default_Event::function_arr[(int)IE_Default_Event::Default_Functions::MOVE_RIGHT]);
			Engine_Input::Create_New_Bind((int)'A', IE_Default_Event::function_arr[(int)IE_Default_Event::Default_Functions::MOVE_LEFT]);
			Engine_Input::Create_New_Bind((int)'W', IE_Default_Event::function_arr[(int)IE_Default_Event::Default_Functions::MOVE_UP]);
			Engine_Input::Create_New_Bind((int)'S', IE_Default_Event::function_arr[(int)IE_Default_Event::Default_Functions::MOVE_DOWN]);

			Engine_Input::Create_New_Bind((int)'E', IE_Default_Event::function_arr[(int)IE_Default_Event::Default_Functions::CHANGE_SCENE], true);
		}	
	}
	void Engine_Input::Handle_Keys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode) {
		/* For gaining access to the current window using callbacks */
		Engine_Input* this_window = static_cast<Engine_Input*>(glfwGetWindowUserPointer(window));
		// For when a key is pressed by the user
		
		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_ESCAPE) {
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
			// For when a key is hit set the key that was hit to true
			if (key >= 0 && key <= 1024) {
				if (Is_Key(key) == true) {
					Handle_Events(key, action);
				}
			}
		}
		else {
			// For when a key is released by the user
			if (action == GLFW_RELEASE) {
				if (keys[key].Get_Press_Setting() != true) {
					if (Is_Key(key)) {
						current_active_keys.at(key).~Input_Event_Key();
						current_active_keys.erase(key);
					}
				}
			}
		}
	}
	void Engine_Input::Handle_Mouse(GLFWwindow* window, GLdouble mouse_xpos, GLdouble mouse_ypos) {
		//printf("X pos: %.f\n", mouse_xpos);
		//printf("Y pos: %.f\n", Engine_Constant::Window_Height() - mouse_ypos);
		/* For gaining access to the current window using callbacks */
		Engine_Input* this_window = static_cast<Engine_Input*>(glfwGetWindowUserPointer(window));
		// For the first time running of the function
		if (this_window->startup_state) {
			this_window->cursor_last_xpos = (GLfloat)mouse_xpos;
			this_window->cursor_last_ypos = (GLfloat)mouse_ypos;
			this_window->startup_state = false;
		}
		// For computing the change in the x position
		this_window->cursor_pos_xchange = (GLfloat)mouse_xpos - this_window->cursor_last_xpos;
		// For computing  the change in the y position
		this_window->cursor_pos_ychange = this_window->cursor_last_ypos - (GLfloat)mouse_ypos;
		// For resetting the values for next function call
		this_window->cursor_last_xpos = (GLfloat)mouse_xpos;
		this_window->cursor_last_ypos = (GLfloat)mouse_ypos;
	}
	void Engine_Input::Handle_Resize(GLFWwindow* main_window, int window_width, int window_height) {
		glViewport(0, 0, window_width, window_height);

		glClearColor(0.0f, 0.16f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLint buffer_width = window_width;
		GLint buffer_height = window_height;

		PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height));

		Engine_Constant::Set_Window_Width(buffer_width);
		Engine_Constant::Set_Window_Height(buffer_height);
		Engine_Constant::Set_Hafe_Window_Width(buffer_width / 2);
		Engine_Constant::Set_Hafe_Window_Height(buffer_height / 2);

		glfwSwapBuffers(main_window);
	}
	glm::vec2 Engine_Input::Get_Cursor_Position() {
		glm::vec2 positions(1.0f);
		positions.x = cursor_last_xpos;
		positions.y = Engine_Constant::Window_Height() - cursor_last_ypos;
		return positions;
	}
	void Engine_Input::Handle_Events(GLint key, GLint action) {
		if (keys[key].Get_Press_Setting() == true && action == GLFW_PRESS) {
			keys[key].event_();
		}
		else {
			keys[key].event_();
			current_active_keys.insert(std::make_pair(key, keys[key]));
		}
	}
	bool Engine_Input::Is_Key(GLint key) {
		if (keys[key].Get_Key() != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	void Engine_Input::Poll_Active_Events() {
		for (auto i = current_active_keys.begin(); i != current_active_keys.end(); i++) {
			current_active_keys.at(i->first).event_();
		}
	}
	void Engine_Input::Create_New_Bind(GLint key_code, void(*function_ptr)(), bool only_play_once) {
		keys[(key_code)].Set_Key(key_code);
		keys[(key_code)].event_ = function_ptr;
		keys[(key_code)].Set_Press_Setting(only_play_once);
	}
}