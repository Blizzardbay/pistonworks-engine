#include "control\input.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Input
		// Static Declarations
			co::Input* Input::m_current_input{ nullptr };
			std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>* Input::m_function_register{ nullptr };
			COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) Input::m_scene_event_function{};
		// Class Members
			Input::Input() :
					m_current_key_events{}, m_key_events{}, m_current_mouse_events{},
					m_mouse_events{}, m_scroll_events{}, m_event_id_assigner{ 0 } {
			}
			Input::Input(
				std::vector<st::Event_Base*> p_current_key_events,
				std::map<PW_INPUT_TYPE, std::map<PW_KEY_CODE, std::map<PW_ID, st::Event_Base*>>> p_key_events,
				std::vector<st::Event_Base*> p_current_mouse_events,
				std::map<PW_INPUT_TYPE, std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>>> p_mouse_events,
				std::map<PW_SCROLL_ACTION, std::map<PW_ID, st::Event_Base*>> p_scroll_events) :
					m_current_key_events{ p_current_key_events }, m_key_events{ p_key_events }, m_current_mouse_events{ p_current_mouse_events },
					m_mouse_events{ p_mouse_events }, m_scroll_events{ p_scroll_events }, m_event_id_assigner{ 0 } {
			}
			Input::~Input() {
				for (auto i = m_current_key_events.begin(); i != m_current_key_events.end(); i++) {
					*i._Ptr = nullptr;
				}
				for (auto i = m_key_events.begin(); i != m_key_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							if (pw::co::Memory::Deallocate<pw::st::Event_Base>(k->second) == false) {
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
							if (pw::co::Memory::Deallocate<pw::st::Event_Base>(k->second) == false) {
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
						if (pw::co::Memory::Deallocate<pw::st::Event_Base>(j->second) == false) {
							if (j->second != nullptr) {
								delete j->second;
								j->second = nullptr;
							}
						}
					}
				}
				m_scroll_events.clear();
			}
			void Input::Initialize() {
				typedef std::map<std::wstring, std::shared_ptr<PW_FUNCTION>> FUNCTION_REGISTER;
				PW_CALL(m_function_register = pw::co::Memory::Allocate<FUNCTION_REGISTER>(), false);
			}
			void Input::Release() {
				if (pw::co::Memory::Deallocate<std::map<std::wstring, std::shared_ptr<PW_FUNCTION>>>(m_function_register) == false) {
					if (m_function_register != nullptr) {
						delete m_function_register;
						m_function_register = nullptr;
					}
				}

				m_scene_event_function.~function();
			}
			void Input::Poll_Active_Events() {
				cm::Constant::Set_Mouse_Coord((int32_t)cm::Constant::Mouse_X_Coord_Raw() + TO_INT64(st::Camera::Camera_Position().x),
					(int32_t)(TO_INT64(st::Camera::Camera_Position().y) - (int32_t)cm::Constant::Mouse_Y_Coord_Raw()));

				if (m_current_key_events.size() != 0) {
					for (auto i = m_current_key_events.begin(); i != m_current_key_events.end(); i++) {
						PW_CALL((*i._Ptr)->Trigger_Event(), true);
					}
				}
				if (m_current_mouse_events.size() != 0) {
					for (auto i = m_current_mouse_events.begin(); i != m_current_mouse_events.end(); i++) {
						PW_CALL((*i._Ptr)->Trigger_Event(), true);
					}
				}
			}
			void Input::Handle_Keyboard(GLFWwindow* p_window, int p_key, int p_code, int p_action, int p_mode) noexcept {
				// For gaining access to the current window using callbacks
				//co::Input* this_window = static_cast<co::Input*>(glfwGetWindowUserPointer(window));
				// For when a key is pressed by the user
				UNUSED(p_window)
				UNUSED(p_code)
				UNUSED(p_mode)
				if (m_current_input != nullptr) {
					if (m_current_input->m_key_events.count(p_action) == 1) {
						auto it = m_current_input->m_key_events.at(p_action).find(p_key);
						if (it != m_current_input->m_key_events.at(p_action).end()) {
							for (auto i = it->second.begin(); i != it->second.end(); i++) {
								PW_CALL(i->second->Trigger_Event(), true);
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
					PW_CALL(m_scene_event_function(cm::Constant::PW_KEYBOARD_EVENT, p_key, p_action), false);
				}
			}
			void Input::Handle_Mouse_Movement(GLFWwindow* p_window, double p_mouse_xpos, double p_mouse_ypos) noexcept {
				UNUSED(p_window)
				if (m_current_input != nullptr) {
					cm::Constant::Set_Mouse_Coord_Raw(p_mouse_xpos, p_mouse_ypos);
				}
			}
			void Input::Handle_Mouse_Button(GLFWwindow* p_window, int p_button, int p_action, int p_mods) noexcept {
				UNUSED(p_window)
				UNUSED(p_mods)
				if (m_current_input != nullptr) {
					if (m_current_input->m_mouse_events.count(p_action) >= 1) {
						auto it = m_current_input->m_mouse_events.at(p_action).find(p_button);
						if (it != m_current_input->m_mouse_events.at(p_action).end()) {
							for (auto i = it->second.begin(); i != it->second.end(); i++) {
								PW_CALL(i->second->Trigger_Event(), true);
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
							m_scene_event_function(cm::Constant::PW_MOUSE_EVENT, p_button, p_action);
							m_scene_event_function(cm::Constant::PW_CLICK_EVENT, p_button, p_action);
						}
					}
				}
			}
			void Input::Handle_Mouse_Scroll(GLFWwindow* p_window, double p_xoffset, double p_yoffset) noexcept {
				UNUSED(p_window)
				UNUSED(p_xoffset)
				if (m_current_input != nullptr) {
					PW_SCROLL_ACTION action = NULL;
					if (p_yoffset >= 1) {
						action = cm::Constant::PW_SCROLL_WHEEL_FORWARD;
					}
					else {
						action = cm::Constant::PW_SCROLL_WHEEL_BACKWARD;
					}
					if (m_current_input->m_scroll_events.count(action) >= 1) {
						for (auto i = m_current_input->m_scroll_events.at(action).begin(); i != m_current_input->m_scroll_events.at(action).end(); i++) {
							PW_CALL(i->second->Trigger_Event(), true);
						}
					}
				}
			}
			void Input::Handle_Resize(GLFWwindow* p_main_window, int p_window_width, int p_window_height) noexcept {
				PW_GL_VOID_CALL(glViewport(0, 0, p_window_width, p_window_height), false, true);

				PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false, true);
				PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false, true);
				int32_t buffer_width = 1;
				int32_t buffer_height = 1;
				if (p_window_width > 0) {
					buffer_width = p_window_width;
				}
				if (p_window_height > 0) {
					buffer_height = p_window_height;
				}

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(p_main_window, &buffer_width, &buffer_height), true);

				if (buffer_width != 0 && buffer_height != 0) {
					PW_CALL(cm::Constant::Set_Window_Width(TO_UINT32(buffer_width)), true);
					PW_CALL(cm::Constant::Set_Window_Height(TO_UINT32(buffer_height)), true);
					buffer_width = TO_INT32(ceilf((float)buffer_width / 2));
					PW_CALL(cm::Constant::Set_Hafe_Window_Width(TO_UINT32(buffer_width)), true);
					buffer_height = TO_INT32(ceilf((float)buffer_height / 2));
					PW_CALL(cm::Constant::Set_Hafe_Window_Height(TO_UINT32(buffer_height)), true);
				}

				PW_GLFW_VOID_CALL(glfwSwapBuffers(p_main_window), false);
			}
			void Input::Create_Event_Keyboard(const PW_INPUT_TYPE& p_action, const PW_KEY_CODE& p_key_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once) {
				if (p_function_ptr != nullptr) {
					if (m_key_events.count(p_action) < 1) {
						std::map<PW_ID, st::Event_Base*> v_id_event{};
						
						PW_CALL(v_id_event.insert(std::make_pair(m_event_id_assigner, pw::co::Memory::Allocate_Args<st::Event<void>>(p_key_code, p_action, p_function_ptr, p_only_play_once))), true);

						m_event_id_assigner = m_event_id_assigner + 1;

						std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>> button_event{ std::make_pair(p_key_code, v_id_event) };

						m_key_events.insert(std::make_pair(p_action, button_event));
					}
					else {
						auto v_button_found = m_key_events.at(p_action).find(p_key_code);
						if (v_button_found != m_key_events.at(p_action).end()) {
							PW_CALL(m_key_events.at(p_action).at(p_key_code).insert(std::make_pair(m_event_id_assigner,
								pw::co::Memory::Allocate_Args<st::Event<void>>(p_key_code, p_action, p_function_ptr, p_only_play_once))), true);

							m_event_id_assigner = m_event_id_assigner + 1;
						}
						else {
							std::map<PW_ID, st::Event_Base*> v_id_event{};

							PW_CALL(v_id_event.insert(std::make_pair(m_event_id_assigner,
								pw::co::Memory::Allocate_Args<st::Event<void>>(p_key_code, p_action, p_function_ptr, p_only_play_once))), true);

							m_event_id_assigner = m_event_id_assigner + 1;

							m_key_events.at(p_action).insert(std::make_pair(p_key_code, v_id_event));
						}
					}
				}
			}
			void Input::Create_Event_Mouse(const PW_INPUT_TYPE& p_action, const PW_BUTTON_CODE& p_code, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once) {
				if (p_function_ptr != nullptr) {
					if (m_mouse_events.count(p_action) < 1) {
						std::map<PW_ID, st::Event_Base*> v_id_event{};

						PW_CALL(v_id_event.insert(std::make_pair(m_event_id_assigner,
							pw::co::Memory::Allocate_Args<st::Event<void>>(p_code, p_action, p_function_ptr, p_only_play_once))), true);

						m_event_id_assigner = m_event_id_assigner + 1;

						std::map<PW_BUTTON_CODE, std::map<PW_ID, st::Event_Base*>> button_event{ std::make_pair(p_code, v_id_event) };

						m_mouse_events.insert(std::make_pair(p_action, button_event));
					}
					else {
						auto v_button_found = m_mouse_events.at(p_action).find(p_code);
						if (v_button_found != m_mouse_events.at(p_action).end()) {
							PW_CALL(m_mouse_events.at(p_action).at(p_code).insert(std::make_pair(m_event_id_assigner, 
								pw::co::Memory::Allocate_Args<st::Event<void>>(p_code, p_action, p_function_ptr, p_only_play_once))), true);

							m_event_id_assigner = m_event_id_assigner + 1;
						}
						else {
							std::map<PW_ID, st::Event_Base*> v_id_event{};

							PW_CALL(v_id_event.insert(std::make_pair(m_event_id_assigner,
								pw::co::Memory::Allocate_Args<st::Event<void>>(p_code, p_action, p_function_ptr, p_only_play_once))), true);

							m_event_id_assigner = m_event_id_assigner + 1;

							m_mouse_events.at(p_action).insert(std::make_pair(p_code, v_id_event));
						}
					}
				}
			}
			void Input::Create_Event_Scroll(const PW_SCROLL_ACTION& p_action, std::shared_ptr<PW_FUNCTION> p_function_ptr, const bool& p_only_play_once) {
				if (p_function_ptr != nullptr) {
					if (m_scroll_events.count(p_action) < 1) {															  
						std::map<PW_ID, st::Event_Base*> v_id_event{};
						
						PW_CALL(v_id_event.insert(std::make_pair(m_event_id_assigner,
							pw::co::Memory::Allocate_Args<st::Event<void>>(p_action, p_action, p_function_ptr, p_only_play_once))), true);

						m_event_id_assigner = m_event_id_assigner + 1;

						m_scroll_events.insert(std::make_pair(p_action, v_id_event));
					}
					else {
						PW_CALL(m_scroll_events.at(p_action).insert(std::make_pair(m_event_id_assigner, 
							pw::co::Memory::Allocate_Args<st::Event<void>>(p_action, p_action, p_function_ptr, p_only_play_once))), true);
						m_event_id_assigner = m_event_id_assigner + 1;
					}
				}
			}
			void Input::Register_Function(const std::wstring& p_function_name, std::shared_ptr<PW_FUNCTION> p_function) {
				if (p_function != nullptr) {
					m_function_register->insert(std::make_pair(p_function_name, p_function));
				}
			}
			void Input::Set_Current_Input(co::Input* p_new_input) {
				if (m_current_input != nullptr) {
					m_current_input->m_current_key_events.clear();
					m_current_input->m_current_mouse_events.clear();
				}
				m_current_input = p_new_input;
			}
			void Input::Set_Scene_Event_Function(const COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)& p_new_scene_event_function) {
				m_scene_event_function = p_new_scene_event_function;
			}
			co::Input* Input::Current_Input() {
				return m_current_input;
			}
			std::shared_ptr<PW_FUNCTION> Input::Access_Function(const std::wstring& p_function_name) {
				if (m_function_register->find(p_function_name) != m_function_register->end()) {
					return m_function_register->at(p_function_name);
				}
				else {
					return nullptr;
				}
			}
	CO_NAMESPACE_END
PW_NAMESPACE_END