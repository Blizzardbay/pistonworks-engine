#include "engine_headers\engine_input.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	// Engine_Input
	// Static Declarations
		std::map<PW_INT, ie::Keyboard_Event> Engine_Input::current_key_events;
		std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, ie::Keyboard_Event>> Engine_Input::key_events;
		std::map<PW_INT, ie::Mouse_Event> Engine_Input::current_mouse_events;
		std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, ie::Mouse_Event>> Engine_Input::mouse_events;
		std::map<PW_SCROLL_ACTION, ie::Mouse_Event> Engine_Input::scroll_events;
	// Class Members
		PW_VOID Engine_Input::Init_Default_Binds() {
		
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_SPACE,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Scene_Player::Move_Up),
				true);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_S,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Scene_Player::Move_Down),
				false);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_D,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Scene_Player::Move_Right),
				false);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_A,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Scene_Player::Move_Left),
				false);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_E,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) Change_Scene),
				true);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_UP,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Camera::Camera_Up),
				false);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_DOWN,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Camera::Camera_Down),
				false);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_RIGHT,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Camera::Camera_Right),
				false);
			Engine_Input::Create_Event_Keyboard(
				GLFW_PRESS, GLFW_KEY_LEFT,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Camera::Camera_Left),
				false);
			Engine_Input::Create_Event_Scroll(
				Engine_Constant::PW_SCROLL_WHEEL_FROWARD,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Camera::Scroll_Forward),
				true);
			Engine_Input::Create_Event_Scroll(
				Engine_Constant::PW_SCROLL_WHEEL_BACKWARD,
				std::make_shared<PW_FUNCTION>((PW_FUNCTION) ie::Camera::Scroll_Backward),
				true);
		}
		PW_VOID Engine_Input::Handle_Keyboard(GLFWwindow* window, int key, int code, int action, int mode) {
			// For gaining access to the current window using callbacks
			//Engine_Input* this_window = static_cast<Engine_Input*>(glfwGetWindowUserPointer(window));
			// For when a key is pressed by the user
		
			if (key_events.count(action) == 1) {
				auto it = key_events.at(action).find(key);
				if (it != key_events.at(action).end()) {
					it->second.Trigger_Event();
					if (!(it->second.Play_State())) {
						current_key_events.insert(std::make_pair(key,it->second));
					}
				}
			}
			else {
				if (!(current_key_events.empty())) {
					if (current_key_events.count(key) != 0) {
						if (current_key_events.at(key).Resolution() == action) {
							current_key_events.erase(key);
						}
					}
				}
			}
			if (action == GLFW_PRESS) {
				if (key == GLFW_KEY_ESCAPE) {
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
			}
		}
		PW_VOID Engine_Input::Handle_Mouse_Movement(GLFWwindow* window, double mouse_xpos, double mouse_ypos) {
			//printf("X pos: %.2f\n", mouse_xpos);
			//printf("Y pos: %.2f\n", Engine_Constant::Window_Height() - mouse_ypos);

			Engine_Constant::Set_Mouse_Coords((PW_INT)mouse_xpos, (PW_INT)(Engine_Constant::Window_Height() - mouse_ypos));
		}
		PW_VOID Engine_Input::Handle_Mouse_Button(GLFWwindow* window, int button, int action, int mods) {
			if (mouse_events.count(action) >= 1) {
				auto it = mouse_events.at(action).find(button);
				if (it != mouse_events.at(action).end()) {
					it->second.Trigger_Event();
					if (!(it->second.Play_State())) {
						current_mouse_events.insert(std::make_pair(button,it->second));
					}
				}
			}
			if (!(current_mouse_events.empty())) {
				if (current_mouse_events.count(button) != 0) {
					if (current_mouse_events.at(button).Resolution() == action) {
						current_mouse_events.erase(button);
					}
				}
			}
		}
		PW_VOID Engine_Input::Handle_Mouse_Scroll(GLFWwindow* window, double xoffset, double yoffset) {
			PW_SCROLL_ACTION action = NULL;
			if (yoffset >= 1) {
				action = Engine_Constant::PW_SCROLL_WHEEL_FROWARD;
			}
			else {
				action = Engine_Constant::PW_SCROLL_WHEEL_BACKWARD;
			}
			if (scroll_events.count(action) >= 1) {
				scroll_events.at(action).Trigger_Event();
			}
		}
		PW_VOID Engine_Input::Handle_Resize(GLFWwindow* main_window, int window_width, int window_height) {
			PW_GL_VOID_CALL(glViewport(0, 0, window_width, window_height), false);

			PW_GL_VOID_CALL(glClearColor(0.0f, 0.16f, 0.16f, 1.0f), false);
			PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
		
			PW_INT buffer_width = window_width;
			PW_INT buffer_height = window_height;

			// For retrieving the buffer sizes for our given window
			PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height));

			Engine_Constant::Set_Window_Width(buffer_width);
			Engine_Constant::Set_Window_Height(buffer_height);
			Engine_Constant::Set_Hafe_Window_Width(buffer_width / 2);
			Engine_Constant::Set_Hafe_Window_Height(buffer_height / 2);

			Engine_Queue::Refresh_Queue();

			PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window));
		}
		PW_VOID Engine_Input::Poll_Active_Events() {
			if (current_key_events.size() != 0) {
				for (auto i = current_key_events.begin(); i != current_key_events.end(); i++) {
					current_key_events.at(i->first).Trigger_Event();
				}
			}
			if (current_mouse_events.size() != 0) {
				for (auto i = current_mouse_events.begin(); i != current_mouse_events.end(); i++) {
					current_mouse_events.at(i->first).Trigger_Event();
				}
			}
		}
		PW_VOID Engine_Input::Create_Event_Scroll(PW_SCROLL_ACTION action, PW_SRD_PTR(PW_FUNCTION) function_ptr, PW_BOOL only_play_once = false) {
			if (scroll_events.count(action) < 1) {
				scroll_events.insert(std::make_pair(action, ie::Mouse_Event(action, function_ptr, only_play_once)));
			}
		}
		PW_VOID Engine_Input::Create_Event_Mouse(PW_INPUT_TYPE action, PW_BUTTON_CODE code, PW_SRD_PTR(PW_FUNCTION) function_ptr, PW_BOOL only_play_once = false) {
			if (mouse_events.count(action) < 1) {
				std::map<PW_BUTTON_CODE, ie::Mouse_Event> map = std::map< PW_BUTTON_CODE, ie::Mouse_Event>();
				map.insert(std::make_pair(code, ie::Mouse_Event(action, function_ptr, only_play_once)));
				mouse_events.insert(std::make_pair(action, map));
			}
			else {
				auto it = mouse_events.at(action).find(code);
				if (it == mouse_events.at(action).end()) {
					mouse_events.at(action).insert(std::make_pair(code, ie::Mouse_Event(action, function_ptr, only_play_once)));
				}
			}
		}
		PW_VOID Engine_Input::Create_Event_Keyboard(PW_INPUT_TYPE action, PW_KEY_CODE key_code, PW_SRD_PTR(PW_FUNCTION) function_ptr, PW_BOOL only_play_once = false) {
			if (key_events.count(action) < 1) {
				std::map<PW_KEY_CODE, ie::Keyboard_Event> map = std::map< PW_KEY_CODE, ie::Keyboard_Event>();
				map.insert(std::make_pair(key_code, ie::Keyboard_Event(action, function_ptr, only_play_once)));
				key_events.insert(std::make_pair(action, map));
			}
			else {
				auto it = key_events.at(action).find(key_code);
				if (it == key_events.at(action).end()) {
					key_events.at(action).insert(std::make_pair(key_code, ie::Keyboard_Event(action, function_ptr, only_play_once)));
				}
			}
		}
		PW_VOID Engine_Input::Change_Scene() {
			Engine_Queue::Change_Scene(Engine_Queue::Scene_Index() + 1);
		}
	// End of Class Members
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////