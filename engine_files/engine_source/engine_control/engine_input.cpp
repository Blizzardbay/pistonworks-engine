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
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_UP,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Up),
					false);
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_DOWN,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Down),
					false);
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_RIGHT,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Right),
					false);
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_LEFT,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Left),
					false);
				this->Create_Event_Scroll(
					cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Scroll_Forward),
					true);
				this->Create_Event_Scroll(
					cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Scroll_Backward),
					true);
			}
			Engine_Input::Engine_Input(
				std::vector<st::Event_Base*> p_current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> p_key_events,
				std::vector<st::Event_Base*> p_current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> p_mouse_events,
				std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> p_scroll_events) :
					current_key_events(p_current_key_events), key_events(p_key_events), current_mouse_events(p_current_mouse_events),
					mouse_events(p_mouse_events), scroll_events(p_scroll_events), event_id_assigner{ 0 }{
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_UP,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Up),
					false);
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_DOWN,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Down),
					false);
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_RIGHT,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Right),
					false);
				this->Create_Event_Keyboard(
					GLFW_PRESS, GLFW_KEY_LEFT,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Camera_Left),
					false);
				this->Create_Event_Scroll(
					cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Scroll_Forward),
					true);
				this->Create_Event_Scroll(
					cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD,
					std::make_shared<PW_FUNCTION>((PW_FUNCTION)st::Camera::Scroll_Backward),
					true);
			}
			/*
			std::map<int32_t, st::Event_Base*> current_key_events;
			std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, st::Event_Base*>> key_events;
			std::map<int32_t, st::Event_Base*> current_mouse_events;
			std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, st::Event_Base*>> mouse_events;
			std::map<PW_SCROLL_ACTION, st::Event_Base*> scroll_events;
			*/
			void Engine_Input::Delete() {
				for (auto i = current_key_events.begin(); i != current_key_events.end(); i++) {
					*i._Ptr = nullptr;
				}
				for (auto i = key_events.begin(); i != key_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							pw::Engine_Memory::Deallocate<st::Event_Base>(k->second);
						}
					}
				}
				for (auto i = current_mouse_events.begin(); i != current_mouse_events.end(); i++) {
					*i._Ptr = nullptr;
				}
				for (auto i = mouse_events.begin(); i != mouse_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							pw::Engine_Memory::Deallocate<st::Event_Base>(k->second);
						}
					}
				}
				for (auto i = scroll_events.begin(); i != scroll_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						pw::Engine_Memory::Deallocate<st::Event_Base>(j->second);
					}
				}
			}
			void Engine_Input::Handle_Keyboard(GLFWwindow* window, int key, int code, int action, int mode) {
				// For gaining access to the current window using callbacks
				//Engine_Input* this_window = static_cast<Engine_Input*>(glfwGetWindowUserPointer(window));
				// For when a key is pressed by the user
				if (current_input != nullptr) {
					if (current_input->key_events.count(action) == 1) {
						auto it = current_input->key_events.at(action).find(key);
						if (it != current_input->key_events.at(action).end()) {
							for (auto i = it->second.begin(); i != it->second.end(); i++) {
								i->second->Trigger_Event();
								if (!(i->second->Play_State())) {
									current_input->current_key_events.push_back(i->second);
								}
							}
						}
						else {
							if (scene_event_function != nullptr) {
								scene_event_function(cm::Engine_Constant::PW_KEYBOARD_EVENT, key, action);
							}
						}
					}
					else {
						if (!current_input->current_key_events.empty()) {
							for (auto i = current_input->current_key_events.begin(); i != current_input->current_key_events.end(); i++) {
								if ((*i._Ptr)->Resolution() == action) {
									if (static_cast<st::Keyboard_Event<void>*>(*i._Ptr)->Button() == key) {
										current_input->current_key_events.erase(i);
										if (current_input->current_key_events.size() > 1) {
											i = current_input->current_key_events.begin();
										}
										else {
											break;
										}
									}
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
					cm::Engine_Constant::Set_Mouse_Coords((int32_t)mouse_xpos + TO_INT64((st::Camera::Camera_Position_Raw().x / 2.0f) * cm::Engine_Constant::Window_Width()),
						(int32_t)(cm::Engine_Constant::Window_Height() - (mouse_ypos - TO_INT64((st::Camera::Camera_Position_Raw().y / 2.0f) * cm::Engine_Constant::Window_Height()))));
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
							for (auto i = it->second.begin(); i != it->second.end(); i++) {
								i->second->Trigger_Event();
								if (!(i->second->Play_State())) {
									current_input->current_mouse_events.push_back(i->second);
								}
							}
						}
					}
					if (!(current_input->current_mouse_events.empty())) {
						for (auto i = current_input->current_mouse_events.begin(); i != current_input->current_mouse_events.end(); i++) {
							if ((*i._Ptr)->Resolution() == action) {
								current_input->current_mouse_events.erase(i);
								if (current_input->current_mouse_events.size() > 1) {
									i = current_input->current_mouse_events.begin();
								}
								else {
									break;
								}
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
						for (auto i = current_input->scroll_events.at(action).begin(); i != current_input->scroll_events.at(action).end(); i++) {
							i->second->Trigger_Event();
						}
					}
				}
			}
			void Engine_Input::Handle_Resize(GLFWwindow* main_window, int window_width, int window_height) {
				PW_GL_VOID_CALL(glViewport(0, 0, window_width, window_height), false);

				PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
				PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
				int32_t buffer_width = 1;
				int32_t buffer_height = 1;
				if (window_width > 0) {
					buffer_width = window_width;
				}
				if (window_height > 0) {
					buffer_height = window_height;
				}

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height));

				if (buffer_width != 0 && buffer_height != 0) {
					cm::Engine_Constant::Set_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width)));
					cm::Engine_Constant::Set_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height)));
					buffer_width = TO_INT32(ceilf((float)buffer_width / 2));
					cm::Engine_Constant::Set_Hafe_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width)));
					buffer_height = TO_INT32(ceilf((float)buffer_height / 2));
					cm::Engine_Constant::Set_Hafe_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height)));
				}

				if (refresh_function != nullptr) {
					refresh_function();
				}

				PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window));
			}
			void Engine_Input::Poll_Active_Events() {
				if (current_key_events.size() != 0) {
					for (auto i = current_key_events.begin(); i != current_key_events.end(); i++) {
						(*i._Ptr)->Trigger_Event();
					}
				}
				if (current_mouse_events.size() != 0) {
					for (auto i = current_mouse_events.begin(); i != current_mouse_events.end(); i++) {
						(*i._Ptr)->Trigger_Event();
					}
				}
			}
			void Engine_Input::Create_Event_Scroll(PW_SCROLL_ACTION action, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once = false) {
				if (scroll_events.count(action) < 1) {
					std::map<PW_ID, st::Event_Base*> id_event{ std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Keyboard_Event<void>, bool>(action, action, function_ptr, only_play_once)) };

					event_id_assigner = event_id_assigner + 1;

					scroll_events.insert(std::make_pair(action, id_event));
				}
				else {
					scroll_events.at(action).insert(std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Keyboard_Event<void>, bool>(action, action, function_ptr, only_play_once)));
					event_id_assigner = event_id_assigner + 1;
				}
			}
			void Engine_Input::Register_Function(std::string function_name, PW_SRD_PTR(PW_FUNCTION) function) {
				function_register.insert(std::make_pair(function_name, function));
			}
			void Engine_Input::Create_Event_Mouse(PW_INPUT_TYPE action, PW_BUTTON_CODE code, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once = false) {
				if (mouse_events.count(action) < 1) {
					std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Mouse_Event<void>, bool>(action, function_ptr, only_play_once)) };

					event_id_assigner = event_id_assigner + 1;

					std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>> button_event{ std::make_pair(code, íd_event) };

					mouse_events.insert(std::make_pair(action, button_event));
				}
				else {
					auto v_button_found = mouse_events.at(action).find(code);
					if (v_button_found != mouse_events.at(action).end()) {
						mouse_events.at(action).at(code).insert(std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Mouse_Event<void>, bool>(action, function_ptr, only_play_once)));

						event_id_assigner = event_id_assigner + 1;
					}
					else {
						std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Mouse_Event<void>, bool>(action, function_ptr, only_play_once)) };

						event_id_assigner = event_id_assigner + 1;

						mouse_events.at(action).insert(std::make_pair(code, íd_event));
					}
				}
			}
			void Engine_Input::Create_Event_Keyboard(PW_INPUT_TYPE action, PW_KEY_CODE key_code, PW_SRD_PTR(PW_FUNCTION) function_ptr, bool only_play_once = false) {
				if (key_events.count(action) < 1) {
					std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Keyboard_Event<void>, bool>(key_code, action, function_ptr, only_play_once)) };

					event_id_assigner = event_id_assigner + 1;

					std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>> button_event{ std::make_pair(key_code, íd_event) };

					key_events.insert(std::make_pair(action, button_event));
				}
				else {
					auto v_button_found = key_events.at(action).find(key_code);
					if (v_button_found != key_events.at(action).end()) {
						key_events.at(action).at(key_code).insert(std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Keyboard_Event<void>, bool>(key_code, action, function_ptr, only_play_once)));

						event_id_assigner = event_id_assigner + 1;
					}
					else {
						std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(event_id_assigner, pw::Engine_Memory::Allocate<st::Keyboard_Event<void>, bool>(key_code, action, function_ptr, only_play_once)) };

						event_id_assigner = event_id_assigner + 1;

						key_events.at(action).insert(std::make_pair(key_code, íd_event));
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
					return nullptr;
				}
			}
			void Engine_Input::Set_Current_Input(Engine_Input* new_input) {
				if (current_input != nullptr) {
					current_input->current_key_events.clear();
					current_input->current_mouse_events.clear();
				}
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