#include "extensions\user_interface.h"

PW_NAMESPACE_SRT
	EX_NAMESPACE_SRT
		UI_NAMESPACE_SRT
			// User_Interface
			// Static Declarations
				st::Texture* User_Interface::m_default_empty{ nullptr };
				st::Texture* User_Interface::m_default_filled{ nullptr };
			// Class Members
				st::Texture* const User_Interface::Default_Empty_Texture() {
					return m_default_empty;
				}
				st::Texture* const User_Interface::Default_Filled_Texture() {
					return m_default_filled;
				}
				void User_Interface::Initialize(st::Texture* p_default_empty, st::Texture* p_default_filled) {
					m_default_empty = p_default_empty;
					m_default_filled = p_default_filled;
				}
			// Button_Events
			// Static Declarations
			// Class Members
				Button_Events::Button_Events() :
						m_on_lclick_mouse{ nullptr }, m_on_lrelease_mouse{ nullptr },
						m_on_rclick_mouse{ nullptr }, m_on_rrelease_mouse{ nullptr },
						m_on_scroll_up{ nullptr }, m_on_scroll_down{ nullptr },
						m_on_click_button{ nullptr }, m_on_release_button{ nullptr },
						m_on_hover_button_area{ nullptr }, m_no_hover_button_area{ nullptr },
						m_on_hover_background{ nullptr }, m_no_hover_background{ nullptr },
						m_on_hover_border{ nullptr }, m_no_hover_border{ nullptr },
						m_keyboard_events{} {
				}
			// Button_Structure
			// Static Declarations
			// Class Members
			// Button
			// Static Declarations
				uint64_t Button::m_button_id_assigner{ 0 };
			// Class Members
				Button::Button(const Button_Structure& p_button) :
						m_layer{ p_button.m_layer }, m_position{ p_button.m_position },
						m_size{ p_button.m_size }, m_rotation{ p_button.m_rotation },
						m_button_area{ nullptr }, m_backaround{ nullptr }, m_border{ nullptr }, m_border_size{ p_button.m_border_size },
						m_events{ p_button.m_events },
						m_orientation{ p_button.m_orientation }, m_display_style{ p_button.m_display_style }, m_border_style{ p_button.m_border_style },
						m_id{ ++m_button_id_assigner } {
					// Invalid layering				
					if (m_layer >= INT16_MAX / 4 && m_layer - 1 <= INT16_MAX / 2) {
						SET_ERROR_STATE(PW_INVALID_LAYER);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::ex::ui::Button", L"Invalid layer value: m_layer >= INT16_MAX / 4 && m_layer - 1 <= INT16_MAX / 2", ERROR_LINE, __FILEW__, L"Button"));
						return;
					}

					pw::st::Model* v_temp{ nullptr };
					// Button Area
					if (m_display_style != Button_Structure::Display_Style::DISABLE_BUTTON) {
						if (p_button.m_button_area_color.a == 0.0f) {
							if (p_button.m_button_area_texture == nullptr) {
								PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
									pw::st::Geometry_Types::SQUARE, User_Interface::Default_Filled_Texture(),
									glm::vec2(0.0f, 0.0f), p_button.m_rotation,
									p_button.m_button_area_size
									), true
								);
							}
							else {
								PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
									pw::st::Geometry_Types::SQUARE, p_button.m_button_area_texture,
									glm::vec2(0.0f, 0.0f), p_button.m_rotation,
									p_button.m_button_area_size
									), true
								);
							}
						}
						else {
							if (p_button.m_button_area_texture == nullptr) {
								PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
									pw::st::Geometry_Types::SQUARE, User_Interface::Default_Filled_Texture(),
									glm::vec2(0.0f, 0.0f), p_button.m_rotation,
									p_button.m_button_area_size, p_button.m_button_area_color
									), true
								);
							}
							else {
								PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
									pw::st::Geometry_Types::SQUARE, p_button.m_button_area_texture,
									glm::vec2(0.0f, 0.0f), p_button.m_rotation,
									p_button.m_button_area_size, p_button.m_button_area_color
									), true
								);
							}
						}
						v_temp->Attach_To(&m_position);
						switch (m_orientation) {
							case Button_Structure::Button_Orientation::FREE: {
								v_temp->Set_Offset(p_button.m_button_area_offset);
								break;
							}
							case Button_Structure::Button_Orientation::CENTERED: {
								glm::vec2 v_center = glm::vec2(m_position.x + (m_size.x / 2.0f), m_position.y - (m_size.y / 2.0f));
								glm::vec2 v_button_area_center = v_temp->Calculate_Center();

								v_temp->Set_Offset(v_center - v_button_area_center);
								break;
							}
							default: {
								// Error
								return;
							}
						}

						PW_CALL(m_button_area = pw::co::Memory::Allocate_Args<st::Actor>(v_temp, m_layer + 1), true);
					}
					// Background
					switch (m_display_style) {
						case Button_Structure::Display_Style::BUTTON_AREA_BACKGROUND_ONLY: _FALLTHROUGH
						case Button_Structure::Display_Style::DISABLE_BUTTON: _FALLTHROUGH
						case Button_Structure::Display_Style::DISPLAY_ALL: {
							if (p_button.m_background_color.a == 0.0f) {
								if (p_button.m_background_texture == nullptr) {
									PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
										pw::st::Geometry_Types::SQUARE, User_Interface::Default_Filled_Texture(),
										glm::vec2(0.0f, 0.0f), p_button.m_rotation,
										m_size
										), true
									);
								}
								else {
									PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
										pw::st::Geometry_Types::SQUARE, p_button.m_background_texture,
										glm::vec2(0.0f, 0.0f), p_button.m_rotation,
										m_size
										), true
									);
								}
							}
							else {
								if (p_button.m_button_area_texture == nullptr) {
									PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
										pw::st::Geometry_Types::SQUARE, User_Interface::Default_Filled_Texture(),
										glm::vec2(0.0f, 0.0f), p_button.m_rotation,
										m_size, p_button.m_background_color
										), true
									);
								}
								else {
									PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
										pw::st::Geometry_Types::SQUARE, p_button.m_background_texture,
										glm::vec2(0.0f, 0.0f), p_button.m_rotation,
										m_size, p_button.m_background_color
										), true
									);
								}
							}

							v_temp->Attach_To(&m_position);

							PW_CALL(m_backaround = pw::co::Memory::Allocate_Args<st::Actor>(v_temp, m_layer), true);
							break;
						}
						default: {
							break;
						}
					}
					// Border
					switch (m_display_style) {
						case Button_Structure::Display_Style::DISABLE_BUTTON: _FALLTHROUGH
						case Button_Structure::Display_Style::DISPLAY_ALL: {
							for (size_t i = 0; i < 4; i++) {
								glm::vec2 v_offset{ 0.0f };
								glm::vec2 v_size{ 0.0f };
								switch (m_border_style) {
									case Button_Structure::Border_Style::INNER: {
										switch (i) {
											case 0: {
												v_offset = glm::vec2(0.0f, 0.0f);
												v_size = glm::vec2(p_button.m_border_size, m_size.y);
												break;
											}
											case 1: {
												v_offset = glm::vec2(p_button.m_border_size, 0.0f);
												v_size = glm::vec2(m_size.x - (p_button.m_border_size * 2.0f), p_button.m_border_size);
												break;
											}
											case 2: {
												v_offset = glm::vec2(m_size.x - p_button.m_border_size, 0.0f);
												v_size = glm::vec2(p_button.m_border_size, m_size.y);
												break;
											}
											case 3: {
												v_offset = glm::vec2(0.0f, -(m_size.y - p_button.m_border_size));
												v_size = glm::vec2(m_size.x, p_button.m_border_size);
												break;
											}
										}
										break;
									}
									case Button_Structure::Border_Style::SPLIT: {
										switch (i) {
											case 0: {
												v_offset = glm::vec2(-p_button.m_border_size / 2.0f, 0.0f);
												v_size = glm::vec2(p_button.m_border_size, m_size.y);
												break;
											}
											case 1: {
												v_offset = glm::vec2(-p_button.m_border_size / 2.0f, p_button.m_border_size / 2.0f);
												v_size = glm::vec2(m_size.x + p_button.m_border_size + 1, p_button.m_border_size);
												break;
											}
											case 2: {
												v_offset = glm::vec2(m_size.x - (p_button.m_border_size / 2.0f), 0.0f);
												v_size = glm::vec2(p_button.m_border_size + 1, m_size.y);
												break;
											}
											case 3: {
												v_offset = glm::vec2(-p_button.m_border_size / 2.0f, -(m_size.y - (p_button.m_border_size / 2.0f)));
												v_size = glm::vec2(m_size.x + p_button.m_border_size + 1, p_button.m_border_size);
												break;
											}
										}
										break;
									}
									case Button_Structure::Border_Style::OUTER: {
										switch (i) {
											case 0: {
												v_offset = glm::vec2(-p_button.m_border_size, 0.0f);
												v_size = glm::vec2(p_button.m_border_size, m_size.y);
												break;
											}
											case 1: {
												v_offset = glm::vec2(-p_button.m_border_size, p_button.m_border_size);
												v_size = glm::vec2(m_size.x + (p_button.m_border_size * 2.0f), p_button.m_border_size);
												break;
											}
											case 2: {
												v_offset = glm::vec2(m_size.x, 0.0f);
												v_size = glm::vec2(p_button.m_border_size, m_size.y);
												break;
											}
											case 3: {
												v_offset = glm::vec2(-p_button.m_border_size, -(m_size.y - p_button.m_border_size) - p_button.m_border_size);
												v_size = glm::vec2(m_size.x + (p_button.m_border_size * 2.0f), p_button.m_border_size);
												break;
											}
										}
										break;
									}
								}

								if (p_button.m_border_color.a == 0.0f) {
									if (p_button.m_border_texture == nullptr) {
										PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
											pw::st::Geometry_Types::SQUARE, User_Interface::Default_Filled_Texture(),
											glm::vec2(0.0f, 0.0f), p_button.m_rotation,
											v_size
											), true
										);
									}
									else {
										PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
											pw::st::Geometry_Types::SQUARE, p_button.m_border_texture,
											glm::vec2(0.0f, 0.0f), p_button.m_rotation,
											v_size
											), true
										);
									}
								}
								else {
									if (p_button.m_border_texture == nullptr) {
										PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
											pw::st::Geometry_Types::SQUARE, User_Interface::Default_Filled_Texture(),
											glm::vec2(0.0f, 0.0f), p_button.m_rotation,
											v_size, p_button.m_border_color
											), true
										);
									}
									else {
										PW_CALL(v_temp = pw::co::Memory::Allocate_Args<st::Model>(
											pw::st::Geometry_Types::SQUARE, p_button.m_border_texture,
											glm::vec2(0.0f, 0.0f), p_button.m_rotation,
											v_size, p_button.m_border_color
											), true
										);
									}
								}
								v_temp->Attach_To(&m_position);
								v_temp->Set_Offset(v_offset);
								PW_CALL(m_border[i] = pw::co::Memory::Allocate_Args<st::Actor>(v_temp, m_layer + 1), true);
							}
							break;
						}
						default: {
							break;
						}
					}

					pw::co::Custom_Input::Add(
						std::to_wstring(m_id),
						std::bind(static_cast<void(Button::*)(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE)>(&Button::Process_Events), this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
					);
				}
				Button::~Button() {
					pw::co::Custom_Input::Remove(std::to_wstring(m_id));
					if (pw::co::Memory::Deallocate<st::Actor>(m_button_area) == false) {
						if (m_button_area != nullptr) {
							delete m_button_area;
							m_button_area = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<st::Actor>(m_backaround) == false) {
						if (m_backaround != nullptr) {
							delete m_backaround;
							m_backaround = nullptr;
						}
					}
					for (size_t i = 0; i < 4; i++) {
						if (pw::co::Memory::Deallocate<st::Actor>(m_border[i]) == false) {
							if (m_border[i] != nullptr) {
								delete m_border[i];
								m_border[i] = nullptr;
							}
						}
					}
				}
				void Button::Render() {
					switch (m_display_style) {
						case Button_Structure::Display_Style::BUTTON_AREA_ONLY: {
							if (m_button_area != nullptr) {
								PW_CALL(m_button_area->Render(), true);
							}
							break;
						}
						case Button_Structure::Display_Style::BUTTON_AREA_BACKGROUND_ONLY: {
							if (m_button_area != nullptr) {
								PW_CALL(m_button_area->Render(), true);
							}
							if (m_backaround != nullptr) {
								PW_CALL(m_backaround->Render(), true);
							}
							break;
						}
						case Button_Structure::Display_Style::DISPLAY_ALL: {
							if (m_button_area != nullptr) {
								PW_CALL(m_button_area->Render(), true);
							}
							if (m_backaround != nullptr) {
								PW_CALL(m_backaround->Render(), true);
							}

							for (size_t i = 0; i < 4; i++) {
								if (m_border[i] != nullptr) {
									PW_CALL(m_border[i]->Render(), true);
								}
							}
							break;
						}
						case Button_Structure::Display_Style::DISABLE_BUTTON: {
							if (m_backaround != nullptr) {
								PW_CALL(m_backaround->Render(), true);
							}

							for (size_t i = 0; i < 4; i++) {
								if (m_border[i] != nullptr) {
									PW_CALL(m_border[i]->Render(), true);
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
				void Button::Process_Events(PW_EVENT_ID p_event_id, PW_BUTTON_CODE p_button_code, PW_STATE p_state) {
					UNUSED(p_button_code);
					switch (p_event_id) {
						case cm::Constant::PW_KEYBOARD_EVENT: {
							for (auto i = m_events.m_keyboard_events.begin(); i != m_events.m_keyboard_events.end(); i++) {
								if ((*i)->Button() == p_button_code && (*i)->Trigger() == p_state) {
									(*i)->Trigger_Event();
								}
							}
							break;
						}
						case cm::Constant::PW_SCROLL_WHEEL_FORWARD: {
							if (m_events.m_on_scroll_up != nullptr) {
								m_events.m_on_scroll_up->Trigger_Event();
							}
							break;
						}
						case cm::Constant::PW_SCROLL_WHEEL_BACKWARD: {
							if (m_events.m_on_scroll_down != nullptr) {
								m_events.m_on_scroll_down->Trigger_Event();
							}
							break;
						}
						case cm::Constant::PW_MOUSE_EVENT: {
							switch (p_state) {
								case GLFW_PRESS: {
									if (p_button_code == GLFW_MOUSE_BUTTON_LEFT) {
										if (m_events.m_on_lclick_mouse != nullptr) {
											m_events.m_on_lclick_mouse->Trigger_Event();
										}
									}
									else {
										if (p_button_code == GLFW_MOUSE_BUTTON_RIGHT) {
											if (m_events.m_on_rclick_mouse != nullptr) {
												m_events.m_on_rclick_mouse->Trigger_Event();
											}
										}
									}
									break;
								}
								case GLFW_RELEASE: {
									if (p_button_code == GLFW_MOUSE_BUTTON_LEFT) {
										if (m_events.m_on_lrelease_mouse != nullptr) {
											m_events.m_on_lrelease_mouse->Trigger_Event();
										}
									}
									else {
										if (p_button_code == GLFW_MOUSE_BUTTON_RIGHT) {
											if (m_events.m_on_rrelease_mouse != nullptr) {
												m_events.m_on_rrelease_mouse->Trigger_Event();
											}
										}
									}
									break;
								}
								default: {
									break;
								}
							}
							if (m_button_area != nullptr) {
								if (pw::util::alg::Point_In_Shape(cm::Constant::Mouse_Coord(), m_button_area->Model()) == true) {
									switch (p_state) {
										case GLFW_PRESS: {
											if (m_events.m_on_click_button != nullptr) {
												m_events.m_on_click_button->Trigger_Event();
											}
											break;
										}
										case GLFW_RELEASE: {
											if (m_events.m_on_release_button != nullptr) {
												m_events.m_on_release_button->Trigger_Event();
											}
											break;
										}
										default: {
											break;
										}
									}
								}
							}
							break;
						}
						case cm::Constant::PW_HOVER_EVENT: {
							if (m_button_area != nullptr) {
								if (pw::util::alg::Point_In_Shape(cm::Constant::Mouse_Coord(), m_button_area->Model()) == true) {
									if (m_events.m_on_hover_button_area != nullptr) {
										m_events.m_on_hover_button_area->Trigger_Event();
									}
								}
								else {
									if (m_events.m_no_hover_button_area != nullptr) {
										m_events.m_no_hover_button_area->Trigger_Event();
									}
								}
							}
							if (m_events.m_on_hover_border != nullptr) {
								for (size_t i = 0; i < 4; i++) {
									if (m_border[i] == nullptr) {
										return;
									}
								}
								bool v_overall_success{ false };
								for (size_t i = 0; i < 4; i++) {
									if (pw::util::alg::Point_In_Shape(cm::Constant::Mouse_Coord(), m_border[i]->Model()) == true) {
										v_overall_success = true;
										break;
									}
								}
								if (v_overall_success == true) {
									m_events.m_on_hover_border->Trigger_Event();
								}
								else {
									if (m_events.m_no_hover_border != nullptr) {
										m_events.m_no_hover_border->Trigger_Event();
									}
								}
							}
							if (m_events.m_on_hover_background != nullptr && m_backaround != nullptr) {
								if (pw::util::alg::Point_In_Shape(cm::Constant::Mouse_Coord(), m_backaround->Model()) == true) {
									m_events.m_on_hover_background->Trigger_Event();
								}
								else {
									if (m_events.m_no_hover_background != nullptr) {
										m_events.m_no_hover_background->Trigger_Event();
									}
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
				void Button::Set_Layer(uint32_t p_layer) {
					// Invalid layering				
					if (p_layer >= INT16_MAX / 4 && p_layer - 1 <= INT16_MAX / 2) {
						SET_ERROR_STATE(PW_INVALID_LAYER);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::ex::ui::Button", L"Invalid layer value: p_layer >= INT16_MAX / 4 && p_layer - 1 <= INT16_MAX / 2", ERROR_LINE, __FILEW__, L"Set_Layer"));
						return;
					}

					if (m_button_area != nullptr) {
						m_button_area->Set_Layer(p_layer + 1);
					}
					if (m_backaround != nullptr) {
						m_backaround->Set_Layer(p_layer);
					}

					for (size_t i = 0; i < 4; i++) {
						if (m_border[i] != nullptr) {
							m_border[i]->Set_Layer(p_layer + 1);
						}
					}
				}
				void Button::Set_Position(const glm::vec2& p_position) {
					m_position = p_position;
				}
				void Button::Set_Size(const glm::vec2& p_size) {
					m_size = p_size;

					if (m_backaround != nullptr) {
						PW_CALL(m_backaround->Set_Size(m_size), true);
					}

					if (m_button_area != nullptr) {
						switch (m_orientation) {
							case Button_Structure::Button_Orientation::CENTERED: {
								glm::vec2 v_center = glm::vec2(m_position.x + (m_size.x / 2.0f), m_position.y - (m_size.y / 2.0f));
								glm::vec2 v_button_area_center = m_button_area->Model()->Calculate_Center();

								m_button_area->Model()->Set_Offset(v_center - v_button_area_center);
								break;
							}
							default: {
								break;
							}
						}
					}

					switch (m_display_style) {
						case Button_Structure::Display_Style::DISPLAY_ALL: {
							for (size_t i = 0; i < 4; i++) {
								glm::vec2 v_offset{ 0.0f };
								glm::vec2 v_size{ 0.0f };
								switch (m_border_style) {
									case Button_Structure::Border_Style::INNER: {
										switch (i) {
											case 0: {
												v_offset = glm::vec2(0.0f, 0.0f);
												v_size = glm::vec2(m_border_size, m_size.y);
												break;
											}
											case 1: {
												v_offset = glm::vec2(m_border_size, 0.0f);
												v_size = glm::vec2(m_size.x - (m_border_size * 2.0f), m_border_size);
												break;
											}
											case 2: {
												v_offset = glm::vec2(m_size.x - m_border_size, 0.0f);
												v_size = glm::vec2(m_border_size, m_size.y);
												break;
											}
											case 3: {
												v_offset = glm::vec2(0.0f, -(m_size.y - m_border_size));
												v_size = glm::vec2(m_size.x, m_border_size);
												break;
											}
										}
										break;
									}
									case Button_Structure::Border_Style::SPLIT: {
										switch (i) {
											case 0: {
												v_offset = glm::vec2(-m_border_size / 2.0f, 0.0f);
												v_size = glm::vec2(m_border_size, m_size.y);
												break;
											}
											case 1: {
												v_offset = glm::vec2(-m_border_size / 2.0f, m_border_size / 2.0f);
												v_size = glm::vec2(m_size.x + m_border_size + 1, m_border_size);
												break;
											}
											case 2: {
												v_offset = glm::vec2(m_size.x - (m_border_size / 2.0f), 0.0f);
												v_size = glm::vec2(m_border_size + 1, m_size.y);
												break;
											}
											case 3: {
												v_offset = glm::vec2(-m_border_size / 2.0f, -(m_size.y - (m_border_size / 2.0f)));
												v_size = glm::vec2(m_size.x + m_border_size + 1, m_border_size);
												break;
											}
										}
										break;
									}
									case Button_Structure::Border_Style::OUTER: {
										switch (i) {
											case 0: {
												v_offset = glm::vec2(-m_border_size, 0.0f);
												v_size = glm::vec2(m_border_size, m_size.y);
												break;
											}
											case 1: {
												v_offset = glm::vec2(-m_border_size, m_border_size);
												v_size = glm::vec2(m_size.x + (m_border_size * 2.0f), m_border_size);
												break;
											}
											case 2: {
												v_offset = glm::vec2(m_size.x, 0.0f);
												v_size = glm::vec2(m_border_size, m_size.y);
												break;
											}
											case 3: {
												v_offset = glm::vec2(-m_border_size, -(m_size.y - m_border_size) - m_border_size);
												v_size = glm::vec2(m_size.x + (m_border_size * 2.0f), m_border_size);
												break;
											}
										}
										break;
									}
								}
								if (m_border[i] != nullptr) {
									PW_CALL(m_border[i]->Set_Size(v_size), true);
									m_border[i]->Model()->Set_Offset(v_offset);
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
				void Button::Set_Rotation(const float p_rotation) {
					if (m_button_area != nullptr) {
						m_button_area->Model()->Set_Rotation(p_rotation);
					}
					if (m_backaround != nullptr) {
						m_backaround->Model()->Set_Rotation(p_rotation);
					}

					for (size_t i = 0; i < 4; i++) {
						if (m_border[i] != nullptr) {
							m_border[i]->Model()->Set_Rotation(p_rotation);
						}
					}
				}
				void Button::Attach_To(glm::vec2* p_position) {
					if (m_button_area != nullptr) {
						m_button_area->Model()->Attach_To(p_position);
					}
					if (m_backaround != nullptr) {
						m_backaround->Model()->Attach_To(p_position);
					}

					for (size_t i = 0; i < 4; i++) {
						if (m_border[i] != nullptr) {
							m_border[i]->Model()->Attach_To(p_position);
						}
					}
				}
				void Button::Set_Offset(const glm::vec2& p_offset) {
					if (m_button_area != nullptr) {
						m_button_area->Model()->Set_Offset(p_offset);
					}
					if (m_backaround != nullptr) {
						m_backaround->Model()->Set_Offset(p_offset);
					}

					for (size_t i = 0; i < 4; i++) {
						if (m_border[i] != nullptr) {
							m_border[i]->Model()->Set_Offset(p_offset);
						}
					}
				}
				void Button::Set_On_LClick(st::Event_Base* p_event) {
					m_events.m_on_lclick_mouse = p_event;
				}
				void Button::Set_On_LRelease(st::Event_Base* p_event) {
					m_events.m_on_lrelease_mouse = p_event;
				}
				void Button::Set_On_RClick(st::Event_Base* p_event) {
					m_events.m_on_rclick_mouse = p_event;
				}
				void Button::Set_On_RRelease(st::Event_Base* p_event) {
					m_events.m_on_rrelease_mouse = p_event;
				}
				void Button::Set_On_Scroll_Up(st::Event_Base* p_event) {
					m_events.m_on_scroll_up = p_event;
				}
				void Button::Set_On_Scroll_Down(st::Event_Base* p_event) {
					m_events.m_on_scroll_down = p_event;
				}
				void Button::Set_On_Click_Button(st::Event_Base* p_event) {
					m_events.m_on_click_button = p_event;
				}
				void Button::Set_On_Release_Button(st::Event_Base* p_event) {
					m_events.m_on_release_button = p_event;
				}
				void Button::Set_On_Hover_Button_Area(st::Event_Base* p_event) {
					m_events.m_on_hover_button_area = p_event;
				}
				void Button::Set_No_Hover_Button_Area(st::Event_Base* p_event) {
					m_events.m_no_hover_button_area = p_event;
				}
				void Button::Set_On_Hover_Background(st::Event_Base* p_event) {
					m_events.m_on_hover_background = p_event;
				}
				void Button::Set_No_Hover_Background(st::Event_Base* p_event) {
					m_events.m_no_hover_background = p_event;
				}
				void Button::Set_On_Hover_Border(st::Event_Base* p_event) {
					m_events.m_on_hover_border = p_event;
				}
				void Button::Set_No_Hover_Border(st::Event_Base* p_event) {
					m_events.m_no_hover_border = p_event;
				}
				void Button::Set_Button_Area_Offset(const glm::vec2& p_position) {
					if (m_button_area != nullptr) {
						m_button_area->Model()->Set_Offset(p_position);
					}
				}
				void Button::Set_Button_Area_Size(const glm::vec2& p_size) {
					if (m_button_area != nullptr) {
						m_button_area->Set_Size(p_size);
					}
				}
				void Button::Set_Button_Area_Color(const glm::vec4& p_color) {
					if (m_button_area != nullptr) {
						PW_CALL(m_button_area->Set_Color(p_color), true);
					}
				}
				void Button::Set_Button_Area_Texture(st::Texture* p_texture) {
					if (m_button_area != nullptr) {
						PW_CALL(m_button_area->Model()->Set_Texture(p_texture), true);
					}
				}
				void Button::Set_Backaround_Color(const glm::vec4& p_color) {
					if (m_backaround != nullptr) {
						PW_CALL(m_backaround->Set_Color(p_color), true);
					}
				}
				void Button::Set_Backaround_Texture(st::Texture* p_texture) {
					if (m_backaround != nullptr) {
						PW_CALL(m_backaround->Model()->Set_Texture(p_texture), true);
					}
				}
				void Button::Set_Border_Size(const float& p_size) {
					m_border_size = p_size;
					switch (m_display_style) {
						case Button_Structure::Display_Style::DISPLAY_ALL: {
							for (size_t i = 0; i < 4; i++) {
								glm::vec2 v_offset{ 0.0f };
								glm::vec2 v_size{ 0.0f };
								if (m_border[i] != nullptr) {
									switch (m_border_style) {
										case Button_Structure::Border_Style::INNER: {
											switch (i) {
												case 0: {
													v_offset = glm::vec2(0.0f, 0.0f);
													v_size = glm::vec2(m_border_size, m_size.y);
													break;
												}
												case 1: {
													v_offset = glm::vec2(m_border_size, 0.0f);
													v_size = glm::vec2(m_size.x - (m_border_size * 2.0f), m_border_size);
													break;
												}
												case 2: {
													v_offset = glm::vec2(m_size.x - m_border_size, 0.0f);
													v_size = glm::vec2(m_border_size, m_size.y);
													break;
												}
												case 3: {
													v_offset = glm::vec2(0.0f, -(m_size.y - m_border_size));
													v_size = glm::vec2(m_size.x, m_border_size);
													break;
												}
											}
											break;
										}
										case Button_Structure::Border_Style::SPLIT: {
											switch (i) {
												case 0: {
													v_offset = glm::vec2(-m_border_size / 2.0f, 0.0f);
													v_size = glm::vec2(m_border_size, m_size.y);
													break;
												}
												case 1: {
													v_offset = glm::vec2(-m_border_size / 2.0f, m_border_size / 2.0f);
													v_size = glm::vec2(m_size.x + m_border_size + 1, m_border_size);
													break;
												}
												case 2: {
													v_offset = glm::vec2(m_size.x - (m_border_size / 2.0f), 0.0f);
													v_size = glm::vec2(m_border_size + 1, m_size.y);
													break;
												}
												case 3: {
													v_offset = glm::vec2(-m_border_size / 2.0f, -(m_size.y - (m_border_size / 2.0f)));
													v_size = glm::vec2(m_size.x + m_border_size + 1, m_border_size);
													break;
												}
											}
											break;
										}
										case Button_Structure::Border_Style::OUTER: {
											switch (i) {
												case 0: {
													v_offset = glm::vec2(-m_border_size, 0.0f);
													v_size = glm::vec2(m_border_size, m_size.y);
													break;
												}
												case 1: {
													v_offset = glm::vec2(-m_border_size, m_border_size);
													v_size = glm::vec2(m_size.x + (m_border_size * 2.0f), m_border_size);
													break;
												}
												case 2: {
													v_offset = glm::vec2(m_size.x, 0.0f);
													v_size = glm::vec2(m_border_size, m_size.y);
													break;
												}
												case 3: {
													v_offset = glm::vec2(-m_border_size, -(m_size.y - m_border_size) - m_border_size);
													v_size = glm::vec2(m_size.x + (m_border_size * 2.0f), m_border_size);
													break;
												}
											}
											break;
										}
									}
									PW_CALL(m_border[i]->Set_Size(v_size), true);
									m_border[i]->Model()->Set_Offset(v_offset);
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
				void Button::Set_Border_Color(const glm::vec4& p_color) {
					for (size_t i = 0; i < 4; i++) {
						if (m_border[i] != nullptr) {
							PW_CALL(m_border[i]->Set_Color(p_color), true);
						}
					}
				}
				void Button::Set_Border_Texture(st::Texture* p_texture) {
					for (size_t i = 0; i < 4; i++) {
						if (m_border[i] != nullptr) {
							PW_CALL(m_border[i]->Model()->Set_Texture(p_texture), true);
						}
					}
				}
				const uint32_t& Button::Layer() const {
					return m_layer;
				}
				const glm::vec2& Button::Position() const {
					return m_position;
				}
				const glm::vec2& Button::Size() const {
					return m_size;
				}
				const float& Button::Rotation() const {
					return m_rotation;
				}
				st::Actor* const Button::Button_Area() const {
					return m_button_area;
				}
				st::Actor* const Button::Backaround() const {
					return m_backaround;
				}
				st::Actor* const Button::Border(uint32_t p_part) const {
					if (p_part >= 1 && p_part <= 4) {
						return m_border[p_part - 1];
					}
					return nullptr;
				}
				const st::Event_Base* const Button::On_LClick() const {
					return m_events.m_on_lclick_mouse;
				}
				const st::Event_Base* const Button::On_LRelease() const {
					return m_events.m_on_lrelease_mouse;
				}
				const st::Event_Base* const Button::On_RClick() const {
					return m_events.m_on_rclick_mouse;
				}
				const st::Event_Base* const Button::On_RRelease() const {
					return m_events.m_on_rrelease_mouse;
				}
				const st::Event_Base* const Button::On_Scroll_Up() const {
					return m_events.m_on_scroll_up;
				}
				const st::Event_Base* const Button::On_Scroll_Down() const {
					return m_events.m_on_scroll_down;
				}
				const st::Event_Base* const Button::On_Click_Button() const {
					return m_events.m_on_click_button;
				}
				const st::Event_Base* const Button::On_Release_Button() const {
					return m_events.m_on_release_button;
				}
				const st::Event_Base* const Button::On_Hover_Button_Area() const {
					return m_events.m_on_hover_button_area;
				}
				const st::Event_Base* const Button::No_Hover_Button_Area() const {
					return m_events.m_no_hover_button_area;
				}
				const st::Event_Base* const Button::On_Hover_Background() const {
					return m_events.m_on_hover_background;
				}
				const st::Event_Base* const Button::No_Hover_Background() const {
					return m_events.m_no_hover_background;
				}
				const st::Event_Base* const Button::On_Hover_Border() const {
					return m_events.m_on_hover_border;
				}
				const st::Event_Base* const Button::No_Hover_Border() const {
					return m_events.m_no_hover_border;
				}
				std::vector<st::Event_Base*>& Button::On_Keyboard() {
					return m_events.m_keyboard_events;
				}
			// Slider
			// Static Declarations
			// Class Members
				Slider::Slider(const Slider_Structure& p_slider) :
						m_slider{ nullptr }, m_value{ p_slider.m_starting_value }, m_pressed{ false },
						m_user_defined_events{ p_slider.m_user_defined_events },
						m_type{ p_slider.m_type }, m_trigger{ p_slider.m_trigger },
						m_movement{ p_slider.m_movement } {
					// Invalid size		
					switch (m_movement) {
						case Slider_Structure::Movement::HORIZONTAL: {
							if (p_slider.m_size.x <= p_slider.m_slider_size.x && p_slider.m_size.y >= p_slider.m_slider_size.y) {
								SET_ERROR_STATE(PW_INVALID_SIZE);
								SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::ex::ui::Slider", L"Cannot have: p_slider.m_size.x <= p_slider.m_slider_size.x && p_slider.m_size.y >= p_slider.m_slider_size.y", ERROR_LINE, __FILEW__, L"Slider"));
								return;
							}
							break;
						}
						case Slider_Structure::Movement::VERTICAL: {
							if (p_slider.m_size.x >= p_slider.m_slider_size.x && p_slider.m_size.y <= p_slider.m_slider_size.y) {
								SET_ERROR_STATE(PW_INVALID_SIZE);
								SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::ex::ui::Slider", L"Cannot have: p_slider.m_size.x >= p_slider.m_slider_size.x && p_slider.m_size.y <= p_slider.m_slider_size.y", ERROR_LINE, __FILEW__, L"Slider"));
								return;
							}
							break;
						}
						default: {
							break;
						}
					}
					Button_Structure v_temp{};

					v_temp.m_layer = p_slider.m_layer;
					v_temp.m_position = p_slider.m_position;
					v_temp.m_size = p_slider.m_size;
					v_temp.m_rotation = 0.0f;
					v_temp.m_button_area_offset = glm::vec2(0.0f);
					v_temp.m_button_area_size = p_slider.m_slider_size;
					v_temp.m_button_area_texture = p_slider.m_slider_texture;
					v_temp.m_button_area_color = p_slider.m_slider_color;
					v_temp.m_background_texture = p_slider.m_bar_texture;
					v_temp.m_background_color = p_slider.m_bar_color;
					v_temp.m_border_size = p_slider.m_border_size;
					v_temp.m_border_texture = p_slider.m_border_texture;
					v_temp.m_border_color = p_slider.m_border_color;
					v_temp.m_events.m_on_lclick_mouse = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_LClick), this)
						)),
						true
					);
					v_temp.m_events.m_on_lrelease_mouse = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_LRelease), this)
						)),
						true
					);
					v_temp.m_events.m_on_rclick_mouse = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_RClick), this)
						)),
						true
					);
					v_temp.m_events.m_on_rrelease_mouse = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_RRelease), this)
						)),
						true
					);
					v_temp.m_events.m_on_scroll_up = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Scroll_Up), this)
						)),
						true
					);
					v_temp.m_events.m_on_scroll_down = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Scroll_Down), this)
						)),
						true
					);
					v_temp.m_events.m_on_click_button = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Click_Button), this)
						)),
						true
					);
					v_temp.m_events.m_on_release_button = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Release_Button), this)
						)),
						true
					);
					v_temp.m_events.m_on_hover_button_area = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Hover_Button_Area), this)
						)),
						true
					);
					v_temp.m_events.m_no_hover_button_area = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_No_Hover_Button_Area), this)
						)),
						true
					);
					v_temp.m_events.m_on_hover_background = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Hover_Background), this)
						)),
						true
					);
					v_temp.m_events.m_no_hover_background = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_No_Hover_Background), this)
						)),
						true
					);
					v_temp.m_events.m_on_hover_border = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Hover_Border), this)
						)),
						true
					);
					v_temp.m_events.m_no_hover_border = pw::co::Memory::Allocate_Args<st::Event<void>>(
						0, 0,
						std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
							std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_No_Hover_Border), this)
						)),
						true
					);
					v_temp.m_events.m_keyboard_events.push_back(pw::co::Memory::Allocate_Args<st::Event<void>>(
							0, 0,
							std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
								std::bind(static_cast<void(Slider::*)()>(&Slider::Handle_Keyboard), this)
							)),
							true
						)
					);

					v_temp.m_orientation = pw::ex::ui::Button_Structure::Button_Orientation::CENTERED;
					v_temp.m_display_style = pw::ex::ui::Button_Structure::Display_Style::DISPLAY_ALL;
					v_temp.m_border_style = pw::ex::ui::Button_Structure::Border_Style::OUTER;

					m_slider = pw::co::Memory::Allocate_Args<pw::ex::ui::Button>(v_temp);

					switch (m_type) {
						case ui::Slider_Structure::Type::LEFT_TOP_FILL:
						case ui::Slider_Structure::Type::RIGHT_BOTTOM_FILL:
						case ui::Slider_Structure::Type::CENTER_FILL: {
							switch (m_movement) {
								case Slider_Structure::Movement::HORIZONTAL: {
									m_slider->Button_Area()->Set_Size_X(0.0f);
									m_slider->Button_Area()->Model()->Set_Offset(glm::vec2(0.0f));
									break;
								}
								case Slider_Structure::Movement::VERTICAL: {
									m_slider->Button_Area()->Set_Size_Y(0.0f);
									m_slider->Button_Area()->Model()->Set_Offset(glm::vec2(0.0f));
									break;
								}
								default: {
									break;
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
				Slider::~Slider() {
					if (pw::co::Memory::Deallocate<Button>(m_slider) == false) {
						if (m_slider != nullptr) {
							delete m_slider;
							m_slider = nullptr;
						}
					}
				}
				void Slider::Render() {
					m_slider->Render();
				}
				void Slider::Set_Layer(uint32_t p_layer) {
					m_slider->Set_Layer(p_layer);
				}
				void Slider::Set_Position(const glm::vec2& p_position) {
					m_slider->Set_Position(p_position);
				}
				void Slider::Set_Size(const glm::vec2& p_size) {
					m_slider->Set_Size(p_size);
				}
				void Slider::Attach_To(glm::vec2* p_position) {
					m_slider->Attach_To(p_position);
				}
				void Slider::Set_Offset(const glm::vec2& p_offset) {
					m_slider->Set_Offset(p_offset);
				}
				const uint32_t& Slider::Layer() const {
					return m_slider->Layer();
				}
				const glm::vec2& Slider::Position() const {
					return m_slider->Position();
				}
				const glm::vec2& Slider::Size() const {
					return m_slider->Size();
				}
				const float& Slider::Value() const {
					return m_value;
				}
				Button* const Slider::Base() const {
					return m_slider;
				}
				Button_Events& Slider::User_Events() {
					return m_user_defined_events;
				}
				void Slider::Handle_LClick() {
					m_pressed = true;

					if (m_user_defined_events.m_on_lclick_mouse != nullptr) {
						m_user_defined_events.m_on_lclick_mouse->Trigger_Event();
					}
				}
				void Slider::Handle_LRelease() {
					m_pressed = false;

					if (m_user_defined_events.m_on_lrelease_mouse != nullptr) {
						m_user_defined_events.m_on_lrelease_mouse->Trigger_Event();
					}
				}
				void Slider::Handle_RClick() {
					m_pressed = true;

					if (m_user_defined_events.m_on_rclick_mouse != nullptr) {
						m_user_defined_events.m_on_rclick_mouse->Trigger_Event();
					}
				}
				void Slider::Handle_RRelease() {
					m_pressed = false;

					if (m_user_defined_events.m_on_rrelease_mouse != nullptr) {
						m_user_defined_events.m_on_rrelease_mouse->Trigger_Event();
					}
				}
				void Slider::Handle_Scroll_Up() {
					if (m_user_defined_events.m_on_scroll_up != nullptr) {
						m_user_defined_events.m_on_scroll_up->Trigger_Event();
					}
				}
				void Slider::Handle_Scroll_Down() {
					if (m_user_defined_events.m_on_scroll_down != nullptr) {
						m_user_defined_events.m_on_scroll_down->Trigger_Event();
					}
				}
				void Slider::Handle_Click_Button() {
					if (m_user_defined_events.m_on_click_button != nullptr) {
						m_user_defined_events.m_on_click_button->Trigger_Event();
					}
				}
				void Slider::Handle_Release_Button() {
					if (m_user_defined_events.m_on_release_button != nullptr) {
						m_user_defined_events.m_on_release_button->Trigger_Event();
					}
				}
				void Slider::Handle_Hover_Button_Area() {
					switch (m_trigger) {
						case Slider_Structure::Trigger::PRESS_HOLD: {
							if (m_pressed == true) {
								Move_Slider();
							}
							break;
						}
						case Slider_Structure::Trigger::RELEASE_JUMP: {
							if (m_pressed == false) {
								Move_Slider();
							}
							break;
						}
						case Slider_Structure::Trigger::HOVER: {
							Move_Slider();
							break;
						}
						default: {
							break;
						}
					}
					if (m_user_defined_events.m_on_hover_button_area != nullptr) {
						m_user_defined_events.m_on_hover_button_area->Trigger_Event();
					}
				}
				void Slider::Handle_No_Hover_Button_Area() {
					if (m_user_defined_events.m_no_hover_button_area != nullptr) {
						m_user_defined_events.m_no_hover_button_area->Trigger_Event();
					}
				}
				void Slider::Handle_Hover_Background() {
					switch (m_trigger) {
						case Slider_Structure::Trigger::PRESS_HOLD: {
							if (m_pressed == true) {
								Move_Slider();
							}
							break;
						}
						case Slider_Structure::Trigger::RELEASE_JUMP: {
							if (m_pressed == false) {
								Move_Slider();
							}
							break;
						}
						case Slider_Structure::Trigger::HOVER: {
							Move_Slider();
							break;
						}
						default: {
							break;
						}
					}
					if (m_user_defined_events.m_on_hover_background != nullptr) {
						m_user_defined_events.m_on_hover_background->Trigger_Event();
					}
				}
				void Slider::Handle_No_Hover_Background() {
					if (m_user_defined_events.m_no_hover_background != nullptr) {
						m_user_defined_events.m_no_hover_background->Trigger_Event();
					}
				}
				void Slider::Handle_Hover_Border() {
					if (m_user_defined_events.m_on_hover_border != nullptr) {
						m_user_defined_events.m_on_hover_border->Trigger_Event();
					}
				}
				void Slider::Handle_No_Hover_Border() {
					if (m_user_defined_events.m_no_hover_border != nullptr) {
						m_user_defined_events.m_no_hover_border->Trigger_Event();
					}
				}
				void Slider::Handle_Keyboard() {
					if (m_user_defined_events.m_keyboard_events.empty() != true) {
						for (auto i = m_user_defined_events.m_keyboard_events.begin(); i != m_user_defined_events.m_keyboard_events.end(); i++) {
							if ((*i) != nullptr) {
								(*i)->Trigger_Event();
							}
						}
					}
				}
				void Slider::Move_Slider() {
					float v_mouse_x_coord = TO_FLOAT(pw::cm::Constant::Mouse_X_Coord());
					float v_mouse_y_coord = TO_FLOAT(pw::cm::Constant::Mouse_Y_Coord());

					st::Model* v_slider = m_slider->Button_Area()->Model();
					switch (m_type) {
						case ui::Slider_Structure::Type::LEFT_TOP_FILL:
						case ui::Slider_Structure::Type::RIGHT_BOTTOM_FILL:
						case ui::Slider_Structure::Type::CENTER_FILL: {
							if (!(v_mouse_x_coord <= m_slider->Position().x + m_slider->Size().x)) {
								return;
							}
							if (!(v_mouse_x_coord >= m_slider->Position().x)) {
								return;
							}
							if (!(v_mouse_y_coord >= m_slider->Position().y - m_slider->Size().y)) {
								return;
							}
							if (!(v_mouse_y_coord <= m_slider->Position().y)) {
								return;
							}
							break;
						}
						case ui::Slider_Structure::Type::LEFT_TOP_SLIDER: 
						case ui::Slider_Structure::Type::RIGHT_BOTTOM_SLIDER:
						case ui::Slider_Structure::Type::CENTER_SLIDER: {
							switch (m_movement) {
								case Slider_Structure::Movement::HORIZONTAL: {
									if (!(v_mouse_x_coord <= m_slider->Position().x + m_slider->Size().x - (v_slider->Size().x / 2.0f))) {
										return;
									}
									if (!(v_mouse_x_coord >= m_slider->Position().x + (v_slider->Size().x / 2.0f))) {
										return;
									}
									if (!(v_mouse_y_coord >= m_slider->Position().y - m_slider->Size().y)) {
										return;
									}
									if (!(v_mouse_y_coord <= m_slider->Position().y)) {
										return;
									}
									break;
								}
								case Slider_Structure::Movement::VERTICAL: {
									if (!(v_mouse_x_coord <= m_slider->Position().x + m_slider->Size().x)) {
										return;
									}
									if (!(v_mouse_x_coord >= m_slider->Position().x)) {
										return;
									}
									if (!(v_mouse_y_coord >= m_slider->Position().y - m_slider->Size().y + (v_slider->Size().y / 2.0f))) {
										return;
									}
									if (!(v_mouse_y_coord <= m_slider->Position().y - (v_slider->Size().y / 2.0f))) {
										return;
									}
									break;
								}
								default: {
									break;
								}
							}
							break;
						}
						default: {
							break;
						}
					}
					switch (m_movement) {
						case Slider_Structure::Movement::HORIZONTAL: {
							switch (m_type) {
								case ui::Slider_Structure::Type::LEFT_TOP_FILL: {
									m_value = (glm::abs(m_slider->Position().x - v_mouse_x_coord) / m_slider->Size().x);

									m_slider->Button_Area()->Set_Size_X(m_value * m_slider->Size().x);
									break;
								}
								case ui::Slider_Structure::Type::RIGHT_BOTTOM_FILL: {
									m_value = (glm::abs(m_slider->Position().x + m_slider->Size().x - v_mouse_x_coord) / m_slider->Size().x);

									m_slider->Button_Area()->Set_Size_X(m_value * m_slider->Size().x);

									m_slider->Set_Button_Area_Offset(glm::vec2(m_slider->Size().x - m_slider->Button_Area()->Model()->Size().x, v_slider->Offset().y));
									break;
								}

								case ui::Slider_Structure::Type::CENTER_FILL: {
									m_value = (glm::abs(m_slider->Position().x + (m_slider->Size().x / 2.0f) - v_mouse_x_coord) / (m_slider->Size().x / 2.0f));

									m_slider->Button_Area()->Set_Size_X(m_value * m_slider->Size().x);

									m_slider->Set_Button_Area_Offset(glm::vec2((m_slider->Size().x / 2.0f) - (m_slider->Button_Area()->Model()->Size().x / 2.0f), v_slider->Offset().y));
									break;
								}
								case ui::Slider_Structure::Type::LEFT_TOP_SLIDER: {
									const float v_slider_x = v_slider->Offset().x - (v_slider->Position().x - v_mouse_x_coord + (v_slider->Size().x / 2.0f));

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider_x, v_slider->Offset().y));

									m_value = (glm::abs(m_slider->Position().x - v_slider->Position().x) / (m_slider->Size().x - v_slider->Size().x));
									break;
								}
								case ui::Slider_Structure::Type::RIGHT_BOTTOM_SLIDER: {
									const float v_slider_x = v_slider->Offset().x - (v_slider->Position().x - v_mouse_x_coord + (v_slider->Size().x / 2.0f));

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider_x, v_slider->Offset().y));

									m_value = (glm::abs(m_slider->Position().x + m_slider->Size().x - v_slider->Size().x - v_slider->Position().x) / (m_slider->Size().x - v_slider->Size().x));
									break;
								}
								case ui::Slider_Structure::Type::CENTER_SLIDER: {
									const float v_slider_x = v_slider->Offset().x - (v_slider->Position().x - v_mouse_x_coord + (v_slider->Size().x / 2.0f));

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider_x, v_slider->Offset().y));

									m_value = (glm::abs(m_slider->Position().x + (m_slider->Size().x / 2.0f) - (v_slider->Size().x / 2.0f) - v_slider->Position().x) / ((m_slider->Size().x / 2.0f) - (v_slider->Size().x / 2.0f)));
									break;
								}
								default: {
									break;
								}
							}
							break;
						}
						case Slider_Structure::Movement::VERTICAL: {
							switch (m_type) {
								case ui::Slider_Structure::Type::LEFT_TOP_FILL: {
									m_value = (glm::abs(m_slider->Position().y - v_mouse_y_coord) / m_slider->Size().y);

									m_slider->Button_Area()->Set_Size_Y(m_value * m_slider->Size().y);
									break;
								}
								case ui::Slider_Structure::Type::RIGHT_BOTTOM_FILL: {
									m_value = (glm::abs(m_slider->Position().y - m_slider->Size().y - v_mouse_y_coord) / m_slider->Size().y);

									m_slider->Button_Area()->Set_Size_Y(m_value * m_slider->Size().y);

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider->Offset().x, m_slider->Button_Area()->Model()->Size().y - m_slider->Size().y));
									break;
								}
								case ui::Slider_Structure::Type::CENTER_FILL: {
									m_value = (glm::abs(m_slider->Position().y - (m_slider->Size().y / 2.0f) - v_mouse_y_coord) / (m_slider->Size().y / 2.0f));

									m_slider->Button_Area()->Set_Size_Y(m_value * m_slider->Size().y);

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider->Offset().x, (m_slider->Button_Area()->Model()->Size().y / 2.0f) - (m_slider->Size().y / 2.0f)));
									break;
								}
								case ui::Slider_Structure::Type::LEFT_TOP_SLIDER: {
									const float v_slider_y = v_slider->Offset().y - (v_slider->Position().y - v_mouse_y_coord - (v_slider->Size().y / 2.0f));

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider->Offset().x, v_slider_y));

									m_value = (glm::abs(m_slider->Position().y - v_mouse_y_coord - (v_slider->Size().y / 2.0f)) / (m_slider->Size().y - v_slider->Size().y));
									break;
								}
								case ui::Slider_Structure::Type::RIGHT_BOTTOM_SLIDER: {
									const float v_slider_y = v_slider->Offset().y - (v_slider->Position().y - v_mouse_y_coord - (v_slider->Size().y / 2.0f));

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider->Offset().x, v_slider_y));

									m_value = (glm::abs(glm::abs(m_slider->Position().y - m_slider->Size().y) - v_mouse_y_coord + (v_slider->Size().y / 2.0f)) / (m_slider->Size().y - v_slider->Size().y));
									break;
								}
								case ui::Slider_Structure::Type::CENTER_SLIDER: {
									const float v_slider_y = v_slider->Offset().y - (v_slider->Position().y - v_mouse_y_coord - (v_slider->Size().y / 2.0f));

									m_slider->Set_Button_Area_Offset(glm::vec2(v_slider->Offset().x, v_slider_y));

									m_value = (glm::abs(glm::abs(m_slider->Position().y - (m_slider->Size().y / 2.0f)) - v_mouse_y_coord) / ((m_slider->Size().y / 2.0f) - (v_slider->Size().y / 2.0f)));
									break;
								}
								default: {
									break;
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
			// Text_Box_Structure
			// Static Declarations
			// Class Members
			// Text_Box
				Text_Box::Text_Box(const Text_Box_Structure& p_text_box, const glm::vec4& p_color) :
						m_layer{ p_text_box.m_layer }, m_backaround{ nullptr }, m_text_string{ p_text_box.m_text }, m_lines{}, m_text_size{}, m_default_color{ p_color },
						m_box_type{ p_text_box.m_box_type }, m_wrapping_type{ p_text_box.m_wrapping_type } {
					Button_Structure v_temp{};

					v_temp.m_layer = p_text_box.m_layer - 1;
					v_temp.m_position = p_text_box.m_position;
					v_temp.m_size = p_text_box.m_size;
					v_temp.m_rotation = 0.0f;
					v_temp.m_background_texture = p_text_box.m_backaround_texture;
					v_temp.m_background_color = p_text_box.m_backaround_color;
					v_temp.m_border_size = p_text_box.m_border_size;
					v_temp.m_border_texture = p_text_box.m_border_texture;
					v_temp.m_border_color = p_text_box.m_border_color;
					v_temp.m_events.m_on_lclick_mouse = nullptr;
					v_temp.m_events.m_on_lrelease_mouse = nullptr;
					v_temp.m_events.m_on_rclick_mouse = nullptr;
					v_temp.m_events.m_on_rrelease_mouse = nullptr;
					v_temp.m_events.m_on_scroll_up = nullptr;
					v_temp.m_events.m_on_scroll_down = nullptr;
					v_temp.m_events.m_on_click_button = nullptr;
					v_temp.m_events.m_on_release_button = nullptr;
					v_temp.m_events.m_on_hover_button_area = nullptr;
					v_temp.m_events.m_no_hover_button_area = nullptr;
					v_temp.m_events.m_on_hover_background = nullptr;
					v_temp.m_events.m_no_hover_background = nullptr;
					v_temp.m_events.m_on_hover_border = nullptr;
					v_temp.m_events.m_no_hover_border = nullptr;

					v_temp.m_orientation = pw::ex::ui::Button_Structure::Button_Orientation::CENTERED;
					v_temp.m_display_style = pw::ex::ui::Button_Structure::Display_Style::DISABLE_BUTTON;
					v_temp.m_border_style = pw::ex::ui::Button_Structure::Border_Style::OUTER;

					m_backaround = pw::co::Memory::Allocate_Args<pw::ex::ui::Button>(v_temp);

					std::vector<std::tuple<glm::vec2, std::wstring, float>> v_text_sizes{};
					// The amount of space leftover after putting the text in
					float v_y_difference = 0.0f;
					{
						wchar_t v_wrapping_char{};

						switch (m_wrapping_type) {
							case pw::ex::ui::Text_Box_Structure::Wrapping_Style::HYPHEN: {
								v_wrapping_char = L'-';
								break;
							}
							case pw::ex::ui::Text_Box_Structure::Wrapping_Style::NONE:
							default: {
								v_wrapping_char = L'\000';
								break;
							}
						}

						std::wstring v_temp_line_str{ v_wrapping_char };

						float v_y_offset{ 0.0f };
						size_t v_index{ 0 };

						for (int64_t i = 0; TO_UINT64(i) < m_text_string.size(); i++) {
							glm::vec2 v_current_size{};
							if (m_text_string[i] != L'\n') {
								v_temp_line_str.insert(v_temp_line_str.begin() + v_index, m_text_string[i]);
							}
							else {
								if (i == 0) {
									v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, L" ", false);
									v_y_offset = v_y_offset + v_current_size.y;
									continue;
								}
								if (p_text_box.m_horizontal_bias == Text_Box_Structure::Horizontal_Bias::RIGHT && m_text_string.size() - 1 == TO_UINT64(i)) {
									v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, v_temp_line_str, true);
								}
								else {
									v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, v_temp_line_str, false);
								}
								v_text_sizes.push_back(std::make_tuple(v_current_size, v_temp_line_str, v_y_offset));
								v_temp_line_str = v_wrapping_char;
								v_y_offset = v_y_offset + v_current_size.y;
								v_index = 0;
								m_text_string.erase(m_text_string.begin(), m_text_string.begin() + i);
								i = -1;
								continue;
							}
							v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, v_temp_line_str, false);
							

							if (p_text_box.m_position.y - v_y_offset - p_text_box.m_font_size.y < p_text_box.m_position.y - p_text_box.m_size.y) {
								v_y_difference = -1.0f; // This means that there is no difference
								break;
							}

							if (v_current_size.x > p_text_box.m_size.x) {
								if (v_temp_line_str.size() > 1) {
									v_temp_line_str.erase(v_temp_line_str.end() - 2);
								}
								v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, v_temp_line_str, false);
								v_text_sizes.push_back(std::make_tuple(v_current_size, v_temp_line_str, v_y_offset));
								v_temp_line_str = v_wrapping_char;
								v_y_offset = v_y_offset + v_current_size.y;
								v_index = 0;
								m_text_string.erase(m_text_string.begin(), m_text_string.begin() + i);
								i = -1;
								continue;
							}
							v_index = v_index + 1;
							if (m_text_string.size() - 1 == TO_UINT64(i)) {
								if (v_temp_line_str.size() > 1) {
									v_temp_line_str.erase(v_temp_line_str.end() - 1);
								}
								if (p_text_box.m_horizontal_bias == Text_Box_Structure::Horizontal_Bias::RIGHT) {
									v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, v_temp_line_str, true);
								}
								else {
									v_current_size = st::Text::Predict_Size_Bottom_Y(p_text_box.m_font_type.data(), p_text_box.m_font_size, v_temp_line_str, false);
								}
								v_text_sizes.push_back(std::make_tuple(v_current_size, v_temp_line_str, v_y_offset));
								v_y_offset = v_y_offset + v_current_size.y;
							}
						}
						if (v_y_difference != -1.0f) {
							v_y_difference = p_text_box.m_size.y - v_y_offset - p_text_box.m_font_size.y;
						}
					}
					for (auto i = v_text_sizes.begin(); i != v_text_sizes.end(); i++) {
						float v_x_pos = 0.0f;
						float v_y_pos = 0.0f;

						switch (p_text_box.m_vertical_bias) {
							case Text_Box_Structure::Vertical_Bias::CENTER: {
								if (v_y_difference != -1.0f) {
									v_y_pos = p_text_box.m_position.y - (v_y_difference / 2.0f) - std::get<2>(*i);
								}
								else {
									v_y_pos = p_text_box.m_position.y - std::get<2>(*i);
								}
								break;
							}
							case Text_Box_Structure::Vertical_Bias::BOTTOM: {
								if (v_y_difference != -1.0f) {
									v_y_pos = p_text_box.m_position.y - v_y_difference - std::get<2>(*i);
								}
								else {
									v_y_pos = p_text_box.m_position.y - std::get<2>(*i);
								}
								break;
							}
							case Text_Box_Structure::Vertical_Bias::TOP: _FALLTHROUGH
							default: {
								v_y_pos = p_text_box.m_position.y - std::get<2>(*i);
								break;
							}
						}
						switch (p_text_box.m_horizontal_bias) {
							case Text_Box_Structure::Horizontal_Bias::CENTER: {
								v_x_pos = ((p_text_box.m_size.x - std::get<0>(*i).x) / 2.0f) + p_text_box.m_position.x;
								break;
							}
							case Text_Box_Structure::Horizontal_Bias::RIGHT: {
								v_x_pos = (p_text_box.m_size.x - std::get<0>(*i).x) + p_text_box.m_position.x;
								break;
							}
							case Text_Box_Structure::Horizontal_Bias::LEFT: _FALLTHROUGH
							default: {
								v_x_pos = p_text_box.m_position.x;
								break;
							}
						}

						st::Text* v_line_of_text = pw::co::Memory::Allocate_Args<st::Text>(std::get<1>(*i), glm::vec2(v_x_pos, v_y_pos), p_text_box.m_font_size, p_color, p_text_box.m_font_type.data());
						m_lines.push_back(v_line_of_text);
					}
					//st::Text* v_line_of_text_1 = pw::co::Memory::Allocate_Args<st::Text>(v_temp_line_str, glm::vec2(p_text_box.m_position.x, p_text_box.m_position.y - v_y_offset), p_text_box.m_font_size, p_color, p_text_box.m_font_type.data());
					// m_lines.push_back(v_line_of_text_1);
					//st::Text* v_line_of_text_2 = pw::co::Memory::Allocate_Args<st::Text>(v_temp_line_str, glm::vec2(p_text_box.m_position.x, p_text_box.m_position.y - v_y_offset), p_text_box.m_font_size, p_color, p_text_box.m_font_type.data());
					// m_lines.push_back(v_line_of_text_2);
				}
				//Text_Box::Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_1& p_settings);
				//Text_Box::Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_2& p_settings);
				//Text_Box::Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_3& p_settings);
				//Text_Box::Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_4& p_settings);
				Text_Box::Text_Box::~Text_Box() {
					if (pw::co::Memory::Deallocate<Button>(m_backaround) == false) {
						if (m_backaround != nullptr) {
							delete m_backaround;
							m_backaround = nullptr;
						}
					}
				}
				void Text_Box::Render() {
					m_backaround->Render();

					for (auto i = m_lines.begin(); i != m_lines.end(); i++) {
						(*i)->Render(m_layer);
					}
				}
				void Text_Box::Set_Layer(uint32_t p_layer) {
					m_backaround->Set_Layer(p_layer);

					m_layer = p_layer;
				}
				void Text_Box::Set_Position(const glm::vec2& p_position) {
					// TODO!
				}
				void Text_Box::Set_Size(const glm::vec2& p_size) {
					// TODO!
				}
				void Text_Box::Set_Color(const glm::vec4& p_color) {
					for (auto i = m_lines.begin(); i != m_lines.end(); i++) {
						(*i)->Set_Text_Color(p_color);
					}
				}
				void Text_Box::Attach_To(glm::vec2* p_position) {
					m_backaround->Attach_To(p_position);

					for (auto i = m_lines.begin(); i != m_lines.end(); i++) {
						(*i)->Attach_To(p_position);
					}
				}
				void Text_Box::Set_Offset(const glm::vec2& p_offset) {
					m_backaround->Set_Offset(p_offset);

					for (auto i = m_lines.begin(); i != m_lines.end(); i++) {
						(*i)->Set_Offset(p_offset);
					}
				}
				const uint32_t& Text_Box::Layer() const {
					return m_layer;
				}
				const glm::vec2& Text_Box::Position() const {
					return m_backaround->Position();
				}
				const glm::vec2& Text_Box::Size() const {
					return m_backaround->Size();
				}
				Button* Text_Box::Backaround() const {
					return m_backaround;
				}
				const std::wstring_view& Text_Box::Text() const {
					return m_text_string;
				}
				const std::vector<st::Text*>& Text_Box::Lines() const {
					return m_lines;
				}
				const glm::vec2 Text_Box::Text_Size() const {
					return m_text_size;
				}
				const Text_Box_Structure::Type Text_Box::Fitting_Type() const {
					return m_box_type;
				}
				const Text_Box_Structure::Wrapping_Style Text_Box::Wrapping_Style() const {
					return m_wrapping_type;
				}
			// Static Declarations
			// Class Members
		UI_NAMESPACE_END
	EX_NAMESPACE_END
PW_NAMESPACE_END