#include "engine_control\engine_input.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// Engine_Input
		// Static Declarations
		Engine_Input* Engine_Input::current_input = nullptr;
		std::map<std::string, PW_SRD_PTR(PW_FUNCTION)> Engine_Input::function_register;
		PW_FUNCTION Engine_Input::refresh_function;
		COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) Engine_Input::scene_event_function;
		// Class Members
			Engine_Input::Engine_Input() :
				current_key_events(), key_events(), current_mouse_events(),
				mouse_events(), scroll_events() {
			}
			Engine_Input::Engine_Input(
				std::map<int32_t, st::Keyboard_Event> current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, st::Keyboard_Event>> key_events,
				std::map<int32_t, st::Mouse_Event> current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, st::Mouse_Event>> mouse_events,
				std::map<PW_SCROLL_ACTION, st::Mouse_Event> scroll_events) :
					current_key_events(current_key_events), key_events(key_events), current_mouse_events(current_mouse_events),
					mouse_events(mouse_events), scroll_events(scroll_events) {	
			}
			/*void Engine_Input::Init_Default_Binds() {


				/*Engine_Input::Create_Event_Keyboard(
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
			} */
			void Engine_Input::Handle_Keyboard(GLFWwindow* window, int key, int code, int action, int mode) {
				// For gaining access to the current window using callbacks
				//Engine_Input* this_window = static_cast<Engine_Input*>(glfwGetWindowUserPointer(window));
				// For when a key is pressed by the user
				if (current_input != nullptr) {
					if (current_input->key_events.count(action) == 1) {
						auto it = current_input->key_events.at(action).find(key);
						if (it != current_input->key_events.at(action).end()) {
							it->second.Trigger_Event();
							if (!(it->second.Play_State())) {
								current_input->current_key_events.insert(std::make_pair(key, it->second));
							}
						}
					}
					else {
						if (!(current_input->current_key_events.empty())) {
							if (current_input->current_key_events.count(key) != 0) {
								if (current_input->current_key_events.at(key).Resolution() == action) {
									current_input->current_key_events.erase(key);
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
			}
			void Engine_Input::Handle_Mouse_Movement(GLFWwindow* window, double mouse_xpos, double mouse_ypos) {
				//printf("X pos: %.2f\n", (mouse_xpos + ((ie::Camera::Camera_Position().x / 2.0f) * Engine_Constant::Window_Width())));
				//printf("Y pos: %.2f\n", Engine_Constant::Window_Height() - (mouse_ypos - ((ie::Camera::Camera_Position().y / 2.0f) * Engine_Constant::Window_Height())));
				if (current_input != nullptr) {
					cm::Engine_Constant::Set_Mouse_Coords((int32_t)mouse_xpos + TO_32INT((st::Camera::Camera_Position().x / 2.0f) * cm::Engine_Constant::Window_Width()),
						(int32_t)(cm::Engine_Constant::Window_Height() - (mouse_ypos - TO_32INT((st::Camera::Camera_Position().y / 2.0f) * cm::Engine_Constant::Window_Height()))));
					if (scene_event_function != nullptr) {
						scene_event_function(cm::Engine_Constant::PW_HOVER_EVENT, 0, 1);
					}
				}
			}
			void Engine_Input::Handle_Mouse_Button(GLFWwindow* window, int button, int action, int mods) {
				if (current_input != nullptr) {
					if (current_input->mouse_events.count(action) >= 1) {
						auto it = current_input->mouse_events.at(action).find(button);
						if (it != current_input->mouse_events.at(action).end()) {
							it->second.Trigger_Event();
							if (!(it->second.Play_State())) {
								current_input->current_mouse_events.insert(std::make_pair(button, it->second));
							}
						}
					}
					if (!(current_input->current_mouse_events.empty())) {
						if (current_input->current_mouse_events.count(button) != 0) {
							if (current_input->current_mouse_events.at(button).Resolution() == action) {
								current_input->current_mouse_events.erase(button);
							}
						}
					}
					if (action == GLFW_PRESS) {
						if (scene_event_function != nullptr) {
							scene_event_function(cm::Engine_Constant::PW_CLICK_EVENT, button, action);
						}
					}
				}
			}
			void Engine_Input::Handle_Mouse_Scroll(GLFWwindow* window, double xoffset, double yoffset) {
				if (current_input != nullptr) {
					PW_SCROLL_ACTION action = NULL;
					if (yoffset >= 1) {
						action = cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD;
					}
					else {
						action = cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD;
					}
					if (current_input->scroll_events.count(action) >= 1) {
						current_input->scroll_events.at(action).Trigger_Event();
					}
				}
			}
			void Engine_Input::Handle_Resize(GLFWwindow* main_window, int window_width, int window_height) {
				PW_GL_VOID_CALL(glViewport(0, 0, window_width, window_height), false);

				PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
				PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
		
				int32_t buffer_width = window_width;
				int32_t buffer_height = window_height;

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height));

				cm::Engine_Constant::Set_Window_Width((uint32_t*)&buffer_width);
				cm::Engine_Constant::Set_Window_Height((uint32_t*)&buffer_height);
				buffer_width = buffer_width / 2;
				cm::Engine_Constant::Set_Hafe_Window_Width((uint32_t*)&buffer_width);
				buffer_height = buffer_height / 2;
				cm::Engine_Constant::Set_Hafe_Window_Height((uint32_t*)&buffer_height);

				if (refresh_function != nullptr) {
					refresh_function();
				}

				PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window));
			}
			void Engine_Input::Poll_Active_Events() {
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
			void Engine_Input::Create_Event_Scroll(PW_SCROLL_ACTION action, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once = false) {
				if (scroll_events.count(action) < 1) {
					scroll_events.insert(std::make_pair(action, st::Mouse_Event(action, function_ptr, only_play_once)));
				}
			}
			void Engine_Input::Register_Function(std::string function_name, PW_SRD_PTR(PW_FUNCTION) function) {
				function_register.insert(std::make_pair(function_name, function));
			}
			void Engine_Input::Create_Event_Mouse(PW_INPUT_TYPE action, PW_BUTTON_CODE code, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once = false) {
				if (mouse_events.count(action) < 1) {
					std::map<PW_BUTTON_CODE, st::Mouse_Event> map = std::map< PW_BUTTON_CODE, st::Mouse_Event>();
					map.insert(std::make_pair(code, st::Mouse_Event(action, function_ptr, only_play_once)));
					mouse_events.insert(std::make_pair(action, map));
				}
				else {
					auto it = mouse_events.at(action).find(code);
					if (it == mouse_events.at(action).end()) {
						mouse_events.at(action).insert(std::make_pair(code, st::Mouse_Event(action, function_ptr, only_play_once)));
					}
				}
			}
			void Engine_Input::Create_Event_Keyboard(PW_INPUT_TYPE action, PW_KEY_CODE key_code, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once = false) {
				if (key_events.count(action) < 1) {
					std::map<PW_KEY_CODE, st::Keyboard_Event> map = std::map< PW_KEY_CODE, st::Keyboard_Event>();
					map.insert(std::make_pair(key_code, st::Keyboard_Event(action, function_ptr, only_play_once)));
					key_events.insert(std::make_pair(action, map));
				}
				else {
					auto it = key_events.at(action).find(key_code);
					if (it == key_events.at(action).end()) {
						key_events.at(action).insert(std::make_pair(key_code, st::Keyboard_Event(action, function_ptr, only_play_once)));
					}
				}
			}
			Engine_Input* Engine_Input::Current_Input() {
				return current_input;
			}
			PW_SRD_PTR(PW_FUNCTION) Engine_Input::Access_Function(std::string function_name) {
				if (function_register.find(function_name) != function_register.end()) {
					return function_register.at(function_name);
				}
				else {
					nullptr;
				}
			}
			void Engine_Input::Set_Current_Input(Engine_Input* new_input) {
				current_input = new_input;
			}
			void Engine_Input::Set_Refresh_Function(PW_FUNCTION new_refresh) {
				refresh_function = new_refresh;
			}
			void Engine_Input::Set_Scene_Event_Function(COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) new_scene_event_function) {
				scene_event_function = new_scene_event_function;
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////  
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////