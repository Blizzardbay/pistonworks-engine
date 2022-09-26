#include "engine_control\engine_input.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// Engine_Input
		// Static Declarations
		co::Engine_Input* Engine_Input::m_current_input{ nullptr };
		std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>* Engine_Input::m_function_register{ nullptr };
		COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) Engine_Input::m_scene_event_function{};
		// Class Members
			Engine_Input::Engine_Input() :
					m_current_key_events{}, m_key_events{}, m_current_mouse_events{},
					m_mouse_events{}, m_scroll_events{}, m_event_id_assigner{ 0 } {
			}
			Engine_Input::Engine_Input(
				std::vector<st::Event_Base*> p_current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> p_key_events,
				std::vector<st::Event_Base*> p_current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> p_mouse_events,
				std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> p_scroll_events) :
					m_current_key_events{ p_current_key_events }, m_key_events{ p_key_events }, m_current_mouse_events{ p_current_mouse_events },
					m_mouse_events{ p_mouse_events }, m_scroll_events{ p_scroll_events }, m_event_id_assigner{ 0 } {
			}
			Engine_Input::~Engine_Input() {
				for (auto i = m_current_key_events.begin(); i != m_current_key_events.end(); i++) {
					*i._Ptr = nullptr;
				}
				for (auto i = m_key_events.begin(); i != m_key_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							if (pw::Engine_Memory::Deallocate<pw::st::Event_Base>(k->second) == false) {
								if (k->second != nullptr) {
									delete k->second;
									k->second = nullptr;
								}
							}
						}
					}
				}
				m_key_events.clear();
				for (auto i = m_current_mouse_events.begin(); i != m_current_mouse_events.end(); i++) {
					*i._Ptr = nullptr;
				}
				for (auto i = m_mouse_events.begin(); i != m_mouse_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							if (pw::Engine_Memory::Deallocate<pw::st::Event_Base>(k->second) == false) {
								if (k->second != nullptr) {
									delete k->second;
									k->second = nullptr;
								}
							}
						}
					}
				}
				m_mouse_events.clear();
				for (auto i = m_scroll_events.begin(); i != m_scroll_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						if (pw::Engine_Memory::Deallocate<pw::st::Event_Base>(j->second) == false) {
							if (j->second != nullptr) {
								delete j->second;
								j->second = nullptr;
							}
						}
					}
				}
				m_scroll_events.clear();
			}
			void Engine_Input::Initialize_Input() {
				m_function_register = pw::Engine_Memory::Allocate<std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>>();
			}
			void Engine_Input::Release_Input() {
				if (pw::Engine_Memory::Deallocate<std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>>(m_function_register) == false) {
					if (m_function_register != nullptr) {
						delete m_function_register;
						m_function_register = nullptr;
					}
				}

				m_scene_event_function.~function();
			}
			void Engine_Input::Poll_Active_Events() {
				cm::Engine_Constant::Set_Mouse_Coord((int32_t)cm::Engine_Constant::Mouse_X_Coord_Raw() + TO_INT64(st::Camera::Camera_Position().x),
					(int32_t)(TO_INT64(st::Camera::Camera_Position().y) - (int32_t)cm::Engine_Constant::Mouse_Y_Coord_Raw()));

				if (m_current_key_events.size() != 0) {
					for (auto i = m_current_key_events.begin(); i != m_current_key_events.end(); i++) {
						(*i._Ptr)->Trigger_Event();
					}
				}
				if (m_current_mouse_events.size() != 0) {
					for (auto i = m_current_mouse_events.begin(); i != m_current_mouse_events.end(); i++) {
						(*i._Ptr)->Trigger_Event();
					}
				}
			}
			void Engine_Input::Handle_Keyboard(GLFWwindow* p_window, int p_key, int p_code, int p_action, int p_mode) {
				// For gaining access to the current window using callbacks
				//co::Engine_Input* this_window = static_cast<co::Engine_Input*>(glfwGetWindowUserPointer(window));
				// For when a key is pressed by the user
				UNUSED(p_window)
				UNUSED(p_code)
				UNUSED(p_mode)
				if (m_current_input != nullptr) {
					if (m_current_input->m_key_events.count(p_action) == 1) {
						auto it = m_current_input->m_key_events.at(p_action).find(p_key);
						if (it != m_current_input->m_key_events.at(p_action).end()) {
							for (auto i = it->second.begin(); i != it->second.end(); i++) {
								i->second->Trigger_Event();
								if (!(i->second->Play_State())) {
									m_current_input->m_current_key_events.push_back(i->second);
								}
							}
						}
					}
					else {
						if (!m_current_input->m_current_key_events.empty()) {
							for (auto i = m_current_input->m_current_key_events.begin(); i != m_current_input->m_current_key_events.end(); i++) {
								if ((*i._Ptr)->Resolution() == p_action) {
									if ((*i._Ptr)->Button() == p_key) {
										m_current_input->m_current_key_events.erase(i);
										if (m_current_input->m_current_key_events.size() > 1) {
											i = m_current_input->m_current_key_events.begin();
										}
										else {
											break;
										}
									}
								}
							}
						}
					}
				}
				if (m_scene_event_function != nullptr) {
					m_scene_event_function(cm::Engine_Constant::PW_KEYBOARD_EVENT, p_key, p_action);
				}
			}
			void Engine_Input::Handle_Mouse_Movement(GLFWwindow* p_window, double p_mouse_xpos, double p_mouse_ypos) {
				UNUSED(p_window)
				if (m_current_input != nullptr) {
					cm::Engine_Constant::Set_Mouse_Coord_Raw(p_mouse_xpos, p_mouse_ypos);
				}
			}
			void Engine_Input::Handle_Mouse_Button(GLFWwindow* p_window, int p_button, int p_action, int p_mods) {
				UNUSED(p_window)
				UNUSED(p_mods)
				if (m_current_input != nullptr) {
					if (m_current_input->m_mouse_events.count(p_action) >= 1) {
						auto it = m_current_input->m_mouse_events.at(p_action).find(p_button);
						if (it != m_current_input->m_mouse_events.at(p_action).end()) {
							for (auto i = it->second.begin(); i != it->second.end(); i++) {
								i->second->Trigger_Event();
								if (!(i->second->Play_State())) {
									m_current_input->m_current_mouse_events.push_back(i->second);
								}
							}
						}
					}
					if (!(m_current_input->m_current_mouse_events.empty())) {
						for (auto i = m_current_input->m_current_mouse_events.begin(); i != m_current_input->m_current_mouse_events.end(); i++) {
							if ((*i._Ptr)->Resolution() == p_action) {
								m_current_input->m_current_mouse_events.erase(i);
								if (m_current_input->m_current_mouse_events.size() > 1) {
									i = m_current_input->m_current_mouse_events.begin();
								}
								else {
									break;
								}
							}
						}
					}
					if (p_action == GLFW_PRESS) {
						if (m_scene_event_function != nullptr) {
							m_scene_event_function(cm::Engine_Constant::PW_MOUSE_EVENT, p_button, p_action);
							m_scene_event_function(cm::Engine_Constant::PW_CLICK_EVENT, p_button, p_action);
						}
					}
				}
			}
			void Engine_Input::Handle_Mouse_Scroll(GLFWwindow* p_window, double p_xoffset, double p_yoffset) {
				UNUSED(p_window)
				UNUSED(p_xoffset)
				if (m_current_input != nullptr) {
					PW_SCROLL_ACTION action = NULL;
					if (p_yoffset >= 1) {
						action = cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD;
					}
					else {
						action = cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD;
					}
					if (m_current_input->m_scroll_events.count(action) >= 1) {
						for (auto i = m_current_input->m_scroll_events.at(action).begin(); i != m_current_input->m_scroll_events.at(action).end(); i++) {
							i->second->Trigger_Event();
						}
					}
				}
			}
			void Engine_Input::Handle_Resize(GLFWwindow* p_main_window, int p_window_width, int p_window_height) {
				PW_GL_VOID_CALL(glViewport(0, 0, p_window_width, p_window_height), false);

				PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
				PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
				int32_t buffer_width = 1;
				int32_t buffer_height = 1;
				if (p_window_width > 0) {
					buffer_width = p_window_width;
				}
				if (p_window_height > 0) {
					buffer_height = p_window_height;
				}

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(p_main_window, &buffer_width, &buffer_height));

				if (buffer_width != 0 && buffer_height != 0) {
					cm::Engine_Constant::Set_Window_Width(TO_UINT32(buffer_width));
					cm::Engine_Constant::Set_Window_Height(TO_UINT32(buffer_height));
					buffer_width = TO_INT32(ceilf((float)buffer_width / 2));
					cm::Engine_Constant::Set_Hafe_Window_Width(TO_UINT32(buffer_width));
					buffer_height = TO_INT32(ceilf((float)buffer_height / 2));
					cm::Engine_Constant::Set_Hafe_Window_Height(TO_UINT32(buffer_height));
				}

				PW_GLFW_VOID_CALL(glfwSwapBuffers(p_main_window));
			}
			void Engine_Input::Create_Event_Keyboard(const PW_INPUT_TYPE& p_action, const PW_KEY_CODE& p_key_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once) {
				if (p_function_ptr != nullptr) {
					if (m_key_events.count(p_action) < 1) {
						std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(m_event_id_assigner, 
							pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_key_code, p_action, p_function_ptr, p_only_play_once)) };

						m_event_id_assigner = m_event_id_assigner + 1;

						std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>> button_event{ std::make_pair(p_key_code, íd_event) };

						m_key_events.insert(std::make_pair(p_action, button_event));
					}
					else {
						auto v_button_found = m_key_events.at(p_action).find(p_key_code);
						if (v_button_found != m_key_events.at(p_action).end()) {
							m_key_events.at(p_action).at(p_key_code).insert(std::make_pair(m_event_id_assigner, 
								pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_key_code, p_action, p_function_ptr, p_only_play_once)));

							m_event_id_assigner = m_event_id_assigner + 1;
						}
						else {
							std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(m_event_id_assigner, 
								pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_key_code, p_action, p_function_ptr, p_only_play_once)) };

							m_event_id_assigner = m_event_id_assigner + 1;

							m_key_events.at(p_action).insert(std::make_pair(p_key_code, íd_event));
						}
					}
				}
			}
			void Engine_Input::Create_Event_Mouse(const PW_INPUT_TYPE& p_action, const PW_BUTTON_CODE& p_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once) {
				if (p_function_ptr != nullptr) {
					if (m_mouse_events.count(p_action) < 1) {
						std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(m_event_id_assigner, 
							pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_code, p_action, p_function_ptr, p_only_play_once)) };

						m_event_id_assigner = m_event_id_assigner + 1;

						std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>> button_event{ std::make_pair(p_code, íd_event) };

						m_mouse_events.insert(std::make_pair(p_action, button_event));
					}
					else {
						auto v_button_found = m_mouse_events.at(p_action).find(p_code);
						if (v_button_found != m_mouse_events.at(p_action).end()) {
							m_mouse_events.at(p_action).at(p_code).insert(std::make_pair(m_event_id_assigner, 
								pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_code, p_action, p_function_ptr, p_only_play_once)));

							m_event_id_assigner = m_event_id_assigner + 1;
						}
						else {
							std::map<PW_ID, st::Event_Base*> íd_event{ std::make_pair(m_event_id_assigner, 
								pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_code, p_action, p_function_ptr, p_only_play_once)) };

							m_event_id_assigner = m_event_id_assigner + 1;

							m_mouse_events.at(p_action).insert(std::make_pair(p_code, íd_event));
						}
					}
				}
			}
			void Engine_Input::Create_Event_Scroll(const PW_SCROLL_ACTION& p_action, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once) {
				if (p_function_ptr != nullptr) {
					if (m_scroll_events.count(p_action) < 1) {															  
						std::map<PW_ID, st::Event_Base*> id_event{ std::make_pair(m_event_id_assigner, 
							pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_action, p_action, p_function_ptr, p_only_play_once)) };

						m_event_id_assigner = m_event_id_assigner + 1;

						m_scroll_events.insert(std::make_pair(p_action, id_event));
					}
					else {
						m_scroll_events.at(p_action).insert(std::make_pair(m_event_id_assigner, 
							pw::Engine_Memory::Allocate<st::Event<void>, bool>(p_action, p_action, p_function_ptr, p_only_play_once)));
						m_event_id_assigner = m_event_id_assigner + 1;
					}
				}
			}
			void Engine_Input::Register_Function(const std::wstring& p_function_name, std::shared_ptr<PW_FUNCTION> p_function) {
				if (p_function != nullptr) {
					m_function_register->insert(std::make_pair(p_function_name, p_function));
				}
			}
			void Engine_Input::Set_Current_Input(co::Engine_Input* p_new_input) {
				if (m_current_input != nullptr) {
					m_current_input->m_current_key_events.clear();
					m_current_input->m_current_mouse_events.clear();
				}
				m_current_input = p_new_input;
			}
			void Engine_Input::Set_Scene_Event_Function(const COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)& p_new_scene_event_function) {
				m_scene_event_function = p_new_scene_event_function;
			}
			co::Engine_Input* Engine_Input::Current_Input() {
				return m_current_input;
			}
			std::shared_ptr<PW_FUNCTION> Engine_Input::Access_Function(const std::wstring& p_function_name) {
				if (m_function_register->find(p_function_name) != m_function_register->end()) {
					return m_function_register->at(p_function_name);
				}
				else {
					return nullptr;
				}
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////  
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////