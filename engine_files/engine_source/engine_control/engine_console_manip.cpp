#include "engine_control\engine_console_manip.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		CN_NAMESPACE_SRT
		//////////////////////////////////
			// Console_Error
			// Static Declarations
			// Class Members
				std::wstring Console_Error::Windows_Last_Error() noexcept {
					// This function does not use exceptions
					std::wstring v_error{};
					LPWSTR v_error_string = nullptr;
					
					uint32_t v_error_code = GetLastError();

					if (v_error_code == 0) {
						return std::wstring();
					}

					if (FormatMessageW(
						FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, v_error_code, LANG_SYSTEM_DEFAULT, (LPWSTR)&v_error_string, NULL, NULL) == NULL) {

						LocalFree(v_error_string);

						return std::wstring(std::wstring(L"FormatMessageW Function Failure: Error Code: ") + std::to_wstring(v_error_code));
					}
					else {
						if (v_error_string != nullptr) {
							v_error.append(v_error_string);

							LocalFree(v_error_string);

							return v_error;
						}
						else {
							return std::wstring(std::wstring(L"FormatMessageW Function Failure: Error Code: ") + std::to_wstring(v_error_code));
						}
					}
				}
			// End of Class Members
			// Console_Color
			// Static Declarations
			// Class Members
				Console_Color::Console_Color() :
						m_color_attribute{ 0 } {
				}
				Console_Color::Console_Color(const Win_Text_Color& p_text_color, const Win_Backaround_Color& p_backaround_color) :
						m_color_attribute{ 0 } {
					m_color_attribute = (WORD)p_text_color | (WORD)p_backaround_color;
				}
				const uint16_t& Console_Color::Return_Color() const {
					return m_color_attribute;
				}
			// End of Class Members
			// Console_Manip
				uint16_t Console_Manip::m_console_width{ 100 };
				uint16_t Console_Manip::m_console_height{ 40 };
				wchar_t* Console_Manip::m_console_screen_buffer{ nullptr };
				HWND Console_Manip::m_window_handle{ NULL };
				HANDLE Console_Manip::m_screen_handle{ NULL };
				HANDLE Console_Manip::m_console_output{ NULL };
				COORD Console_Manip::m_write_coord{ 0,0 };
				uint16_t Console_Manip::m_msg_line{ 0 };
				std::map<Console_Manip::Msg_Types, Console_Color>* Console_Manip::m_msg_colors{ nullptr };
			// Static Declarations
			// Class Members
				void Console_Manip::Set_Up_Console() {
					try {
						TRY_LINE m_window_handle = GetConsoleWindow();
						// In the event the GetConsoleWindow cannot find the console throw a 
						// Console_Error
						if (m_window_handle == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"GetConsoleWindow");
						}
						// The windows API does not standard error handling for this function
						TRY_LINE ShowWindow(m_window_handle, SW_HIDE);

						// Make it so we can draw on our console
						TRY_LINE m_screen_handle = CreateConsoleScreenBuffer(GENERIC_READ, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

						if (m_screen_handle == INVALID_HANDLE_VALUE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"CreateConsoleScreenBuffer");
						}
						// Make the console un-resize-able
						if (TRY_LINE SetWindowLongA(m_window_handle, GWL_STYLE, GetWindowLongA(m_window_handle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX) == NULL) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetWindowLongA");
						}
						// Make the cursor go away
						TRY_LINE m_console_output = GetStdHandle(STD_OUTPUT_HANDLE);

						if (TRY_LINE m_console_output == INVALID_HANDLE_VALUE || m_console_output == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"GetStdHandle");
						}

						if (TRY_LINE setlocale(LC_ALL, "chinese") == nullptr) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"setlocale");
						}
						if (TRY_LINE SetConsoleOutputCP(CP_UTF8) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleOutputCP");
						}
						if (TRY_LINE SetConsoleCP(CP_UTF8) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleCP");
						}

						try {
							TRY_LINE CONSOLE_FONT_INFOEX v_font_info;
							v_font_info.cbSize = sizeof(v_font_info);
							v_font_info.FontFamily = 54;
							v_font_info.FontWeight = 700;
							v_font_info.nFont = 0;
							TRY_LINE const wchar_t v_font[] = L"Consolas";
							v_font_info.dwFontSize = { 120, 15 };

							std::copy(v_font, v_font + (sizeof(v_font) / sizeof(wchar_t)), v_font_info.FaceName);

							if (TRY_LINE SetCurrentConsoleFontEx(m_console_output, false, &v_font_info) == FALSE) {
								throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetCurrentConsoleFontEx");
							}
						}
						catch (const std::bad_alloc& v_error) {
							throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"CONSOLE_FONT_INFOEX / Font");
						}
						try {
							TRY_LINE CONSOLE_CURSOR_INFO v_cursor_info{};

							if (TRY_LINE GetConsoleCursorInfo(m_console_output, &v_cursor_info) == FALSE) {
								throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"GetConsoleCursorInfo");
							}
							v_cursor_info.bVisible = false;
							if (TRY_LINE SetConsoleCursorInfo(m_console_output, &v_cursor_info) == FALSE) {
								throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleCursorInfo");
							}
						}
						catch (const std::bad_alloc& v_error) {
							throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"CONSOLE_FONT_INFOEX / Font");
						}
						catch (const er::Severe_Error& v_error) {
							throw v_error;
						}
						try {
							TRY_LINE m_console_screen_buffer = pw::Engine_Memory::Allocate<wchar_t>(TO_UINT64(m_console_width) * TO_UINT64(m_console_height));
						}
						catch (const std::bad_alloc& v_error) {
							throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"console_screen_buffer");
						}

						if (TRY_LINE SetConsoleTitleW(L"Pistonworks Console") == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleTitleW");
						}
						std::wstring v_temp_wstr{};

						v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
						v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");

						for (size_t i = 0; i < m_console_height; i++) {
							for (size_t j = 0; j < m_console_width; j++) {
								m_console_screen_buffer[(i * m_console_width) + j] = v_temp_wstr[(i * TO_UINT64(m_console_width)) + j];
							}
						}

						if (TRY_LINE SetConsoleActiveScreenBuffer(m_console_output) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleActiveScreenBuffer");
						}
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Initialize_Console() {
					std::map<Console_Manip::Msg_Types, Console_Color> v_temp{
						std::make_pair(Console_Manip::Msg_Types::E_CLEAR, Console_Color{ Win_Text_Color::BLACK, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_DEFAULT, Console_Color{ Win_Text_Color::BRIGHT_WHITE, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_ENGINE, Console_Color{ Win_Text_Color::GREEN, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_GAME, Console_Color{ Win_Text_Color::YELLOW, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_INFO, Console_Color{ Win_Text_Color::PINK, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_ERROR, Console_Color{ Win_Text_Color::RED, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_SUCCESS, Console_Color{ Win_Text_Color::BLUE, Win_Backaround_Color::BLACK }),
						std::make_pair(Console_Manip::Msg_Types::E_CONSOLE_OUT, Console_Color{ Win_Text_Color::WHITE, Win_Backaround_Color::BLACK })
					};

					m_msg_colors = pw::Engine_Memory::Allocate<std::map<Console_Manip::Msg_Types, Console_Color>, bool>(v_temp);
				}
				void Console_Manip::Resize(const uint32_t& p_size_x, const uint32_t& p_size_y) {
					try {
						TRY_LINE COORD v_size;
						v_size.X = TO_INT16(p_size_x);
						v_size.Y = TO_INT16(p_size_y);

						TRY_LINE SMALL_RECT v_console_rect;
						v_console_rect.Left = 0;
						v_console_rect.Top = 0;
						v_console_rect.Right = v_size.X - 1;
						v_console_rect.Bottom = v_size.Y - 1;

						if (TRY_LINE SetConsoleWindowInfo(m_console_output, TRUE, &v_console_rect) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleWindowInfo");
						}
						if (TRY_LINE SetConsoleScreenBufferSize(m_console_output, v_size) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleScreenBufferSize");
						}
						if (TRY_LINE SetConsoleActiveScreenBuffer(m_console_output) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleActiveScreenBuffer");
						}
					}
					catch (const std::bad_alloc& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"COORD / SMALL_RECT");
					}
					catch (const std::out_of_range& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"v_console_rect");
					}
					catch (const std::length_error& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"v_size");
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"COORD / SMALL_RECT");
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_Screen() {
					try {
						WORD v_color{ (WORD)Win_Text_Color::DARK_BLUE | (WORD)Win_Backaround_Color::DARK_BLUE };
						WORD v_color_default{ (WORD)Win_Text_Color::BLACK | (WORD)Win_Backaround_Color::BLACK };

						DWORD v_bytes_received = 0;

						TRY_LINE Resize(100, 40);

						for (int i = 0; i < m_console_height; i++) {
							std::wstring v_line{};
							for (int j = 0; j < m_console_width; j++) {
								v_line.push_back(m_console_screen_buffer[(i * m_console_width) + j]);
								if (v_line.at(j) != L' ') {
									if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &v_color, 1, { TO_INT16(j), TO_INT16(i) }, &v_bytes_received) == FALSE) {
										throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputAttribute");
									}
								}
								else {
									if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &v_color_default, 1, { TO_INT16(j), TO_INT16(i) }, &v_bytes_received) == FALSE) {
										throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputAttribute");
									}
								}
							}
							if (TRY_LINE WriteConsoleOutputCharacterW(m_console_output, v_line.c_str(), m_console_width, { 0, TO_INT16(i) }, &v_bytes_received) == FALSE) {
								throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputCharacterW");
							}
						}
						// The windows API does not standard error handling for this function
						TRY_LINE ShowWindow(m_window_handle, SW_SHOW);
						// Not guaranteed but we can try
						TRY_LINE SetFocus(m_window_handle);
						if (TRY_LINE SetConsoleActiveScreenBuffer(m_console_output) == FALSE) {
							throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleActiveScreenBuffer");
						}
					}
					catch (const std::bad_alloc& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"WORD / DWORD");
					}
					catch (const std::length_error& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"console_screen_buffer");
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"console_screen_buffer");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Print_Info(const std::wstring& p_from, const std::wstring& p_msg, const uint16_t& p_line) {
					try {
						std::wstring v_wstr{ L"||" };

						v_wstr.insert(1, p_from);

						v_wstr.insert(p_from.size() + 2, p_msg);

						int16_t v_x_off = 80;
						// Fix weird Unicode character flaw
						std::wstring temp_wstr{ v_wstr };

						for (size_t i = 0; i < temp_wstr.size(); i++) {
							if ((DWORD)temp_wstr.at(i) > 127) {
								if (i != 0) {
									temp_wstr.insert(i + 1, 1, L' ');
									i = i + 1;

								}
								else {
									temp_wstr.insert(0, 1, L' ');
								}
							}
						}
						v_wstr = temp_wstr;

						while (v_wstr.size() != 18) {
							v_wstr.push_back(L' ');
						}
						v_wstr.push_back(L'|');

						Draw_Text_Line({ v_x_off , TO_INT16(p_line + 1) }, v_wstr, m_msg_colors->at(Console_Manip::Msg_Types::E_DEFAULT));
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"Draw_WChar");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Print_Console(const std::wstring& p_from, const std::wstring& p_msg, const Msg_Types& p_msg_type, const bool& p_block_msg) {
					try {
						if (m_msg_line > 37) {
							m_msg_line = 0;
							Clear_Console();
						}

						DWORD v_bytes_written = 0;
						std::wstring v_wstr{ L"|||" };

						v_wstr.insert(1, TO_WSTRING(__TIME__));

						switch (p_msg_type) {
						case Msg_Types::E_CLEAR: {
							break;
						}
						case Msg_Types::E_ENGINE: {
							v_wstr.insert(10, L"ENGINE ");
							break;
						}
						case Msg_Types::E_ERROR: {
							v_wstr.insert(10, L"ERROR  ");
							break;
						}
						case Msg_Types::E_GAME: {
							v_wstr.insert(10, L"GAME   ");
							break;
						}
						case Msg_Types::E_INFO: {
							v_wstr.insert(10, L"INFO   ");
							break;
						}
						case Msg_Types::E_SUCCESS: {
							v_wstr.insert(10, L"SUCCESS");
							break;
						}
						case Msg_Types::E_DEFAULT:
						default: {
							v_wstr.insert(10, L"COUTMSG");
							break;
						}
						}
						if (p_from.empty() == true) {
							v_wstr.append(p_msg);
						}
						else {
							if (p_block_msg == true) {
								v_wstr.insert(18, p_from);
								v_wstr.append(p_msg);
							}
							else {
								v_wstr.insert(18, std::wstring(p_from + L"| "));
								v_wstr.append(p_msg);
							}
						}

						int16_t v_x_off = 2;
						// Fix weird Unicode character flaw
						std::wstring v_temp_wstr{ v_wstr };

						for (size_t i = 0; i < v_temp_wstr.size(); i++) {
							if ((DWORD)v_temp_wstr.at(i) > 127) {
								if (i != 0) {
									v_temp_wstr.insert(i + 1, 1, L' ');
									i = i + 1;

								}
								else {
									v_temp_wstr.insert(0, 1, L' ');
								}
							}
						}
						v_wstr = v_temp_wstr;

						er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_wstr.c_str());

						Draw_Text_Line({ v_x_off , TO_INT16(m_msg_line + 1) }, v_wstr.substr(0, v_wstr.size() > 75 ? 75 : v_wstr.size()), m_msg_colors->at(Console_Manip::Msg_Types::E_DEFAULT));
						Draw_WChar({ TO_INT16(77), TO_INT16(m_msg_line + 1) }, L'|', m_msg_colors->at(Console_Manip::Msg_Types::E_DEFAULT));

						for (size_t i = 0; i < 7; i++) {
							int16_t x_pos = v_x_off + (int16_t)i + 10;

							if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &m_msg_colors->at(p_msg_type).Return_Color(), 1, { x_pos, TO_INT16(m_msg_line + 1) }, &v_bytes_written) == FALSE) {
								throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputAttribute");
							}
						}

						m_msg_line = m_msg_line + 1;
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), EXCEPTION_LINE, __FILEW__, L"Draw_WChar");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Clear_Console() {
					try {
						int16_t v_x_off = 2;

						Draw_WChar_Block(COORD{ TO_INT16(v_x_off), 1 }, COORD{ 78, 39 }, L' ', m_msg_colors->at(Console_Manip::Msg_Types::E_CLEAR));
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_WChar(const COORD& p_position, const wchar_t& p_character, const Console_Color& p_color) {
					DWORD v_bytes_written = 0;
					if (p_position.X < 0 || p_position.Y < 0) {
						throw std::invalid_argument("position");
					}

					if (TRY_LINE WriteConsoleOutputCharacterW(m_console_output, &p_character, 1, p_position, &v_bytes_written) == FALSE) {
						throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputCharacterW");
					}
					if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &p_color.Return_Color(), 1, p_position, &v_bytes_written) == FALSE) {
						throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputAttribute");
					}
				}
				void Console_Manip::Draw_WChar_Block(const COORD& p_position, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
					if (p_position.X < 0 || p_position.Y < 0) {
						throw std::invalid_argument("position");
					}
					SMALL_RECT v_write_area{};

					v_write_area.Left = p_position.X;
					v_write_area.Top = p_position.Y;
					v_write_area.Right = p_size.X;
					v_write_area.Bottom = p_size.Y;

					size_t v_block_size = TO_UINT64(p_size.X) * TO_UINT64(p_size.Y);

					CHAR_INFO* v_block = pw::Engine_Memory::Allocate<CHAR_INFO>(v_block_size);
					for (size_t i = 0; i < v_block_size; i++) {
						v_block[i].Char.UnicodeChar = p_character;
						v_block[i].Attributes = p_color.Return_Color();
					}
					if (TRY_LINE WriteConsoleOutputW(m_console_output, v_block, p_size, p_position, &v_write_area) == FALSE) {
						throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleOutputW");
					}
					pw::Engine_Memory::Deallocate<CHAR_INFO>(v_block);
				}
				void Console_Manip::Draw_Text_Line(const COORD& p_position, const std::wstring& p_block, const Console_Color& p_color) {
					if (p_position.X < 0 || p_position.Y < 0) {
						throw std::invalid_argument("position");
					}
					if (TRY_LINE SetConsoleCursorPosition(m_console_output, p_position) == FALSE) {
						throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleCursorPosition");
					}
					if (TRY_LINE SetConsoleTextAttribute(m_console_output, p_color.Return_Color()) == FALSE) {
						throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"SetConsoleTextAttribute");
					}

					DWORD v_characters_written{ 0 };

					if (TRY_LINE WriteConsoleW(m_console_output, p_block.c_str(), static_cast<DWORD>(p_block.size()), &v_characters_written, nullptr) == FALSE) {
						throw er::Warning_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"WriteConsoleW");
					}
				}
				void Console_Manip::Draw_Line(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color) {
					try {
						if (p_start.X < 0 || p_start.Y < 0) {
							throw std::invalid_argument("start");
						}
						if (p_end.X < 0 || p_end.Y < 0) {
							throw std::invalid_argument("end");
						}

						if (abs(p_end.Y - p_start.Y) < abs(p_end.X - p_start.X)) {
							if (p_start.X > p_end.X) {
								Draw_Line_Low(p_end, p_start, p_character, p_color);
							}
							else {
								Draw_Line_Low(p_start, p_end, p_character, p_color);
							}
						}
						else {
							if (p_start.Y > p_end.Y) {
								Draw_Line_High(p_end, p_start, p_character, p_color);
							}
							else {
								Draw_Line_High(p_start, p_end, p_character, p_color);
							}
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_Line_Low(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color) {
					try {
						// Does not need to check if start and end values are correct the previous function Draw_Line does that automatically
						int16_t v_dx = p_end.X - p_start.X;
						int16_t v_dy = p_end.Y - p_start.Y;

						int16_t v_yi = 1;
						if (v_dy < 0) {
							v_yi = -1;
							v_dy = -(v_dy);
						}
						int16_t d = (v_dy * 2) - v_dx;
						int16_t y = p_start.Y;

						for (int16_t x = p_start.X; x < p_end.X; x++) {
							Draw_WChar({ x,y }, p_character, p_color);
							if (d > 0) {
								y = y + v_yi;
								d = d + (2 * (v_dy - v_dx));
							}
							else {
								d = d + 2 * v_dy;
							}
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_Line_High(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color) {
					try {
						// Does not need to check if start and end values are correct the previous function Draw_Line does that automatically
						int16_t v_dx = p_end.X - p_start.X;
						int16_t v_dy = p_end.Y - p_start.Y;

						int16_t v_xi = 1;
						if (v_dy < 0) {
							v_xi = -1;
							v_dx = -(v_dx);
						}
						int16_t d = (v_dx * 2) - v_dy;
						int16_t x = p_start.X;

						for (int16_t y = p_start.Y; y < p_end.Y; y++) {
							Draw_WChar({ x,y }, p_character, p_color);
							if (d > 0) {
								x = x + v_xi;
								d = d + (2 * (v_dx - v_dy));
							}
							else {
								d = d + 2 * v_dx;
							}
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_Rectangle_Vertical(const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
					try {
						int16_t v_t1_width = 0;
						int16_t v_t2_width = 0;
						int16_t v_t3_width = 0;
						int16_t v_t4_width = 0;
						// 2 or greater
						assert(p_size.X != 0 && p_size.X != 1);
						assert(p_size.Y != 0 && p_size.Y != 1);
						// Even
						if (p_size.X % 2 == 0) {
							switch (p_size.X % 4) {
								case 2: {
									int16_t v_full_quartets = p_size.X / 4;
									v_t1_width = v_t1_width + 1;
									v_t2_width = v_t2_width + 1;
									for (int16_t i = 0; i < v_full_quartets; i++) {
										v_t1_width = v_t1_width + 1;
										v_t2_width = v_t2_width + 1;
										v_t3_width = v_t3_width + 1;
										v_t4_width = v_t4_width + 1;
									}
									break;
								}
								case 0: {
									int16_t v_full_quartets = p_size.X / 4;
									for (int16_t i = 0; i < v_full_quartets; i++) {
										v_t1_width = v_t1_width + 1;
										v_t2_width = v_t2_width + 1;
										v_t3_width = v_t3_width + 1;
										v_t4_width = v_t4_width + 1;
									}
									break;
								}
								default: {
									break;
								}
							}
						}
						else {
							// Odd, still works
							v_t1_width = 1;
							// Any odd number accept 1
							if (p_size.X - v_t1_width != 0) {
								switch ((p_size.X - v_t1_width) % 4) {
									case 2: {
										int16_t v_full_quartets = (p_size.X - v_t1_width) / 4;
										v_t1_width = v_t1_width + 1;
										v_t2_width = v_t2_width + 1;
										for (int16_t i = 0; i < v_full_quartets; i++) {
											v_t1_width = v_t1_width + 1;
											v_t2_width = v_t2_width + 1;
											v_t3_width = v_t3_width + 1;
											v_t4_width = v_t4_width + 1;
										}
										break;
									}
									case 0: {
										int16_t v_full_quartets = p_size.X / 4;
										for (int16_t i = 0; i < v_full_quartets; i++) {
											v_t1_width = v_t1_width + 1;
											v_t2_width = v_t2_width + 1;
											v_t3_width = v_t3_width + 1;
											v_t4_width = v_t4_width + 1;
										}
										break;
									}
									default: {
										break;
									}
								}
							}
						}
						// Now that we know the width of every thread we run them in order to draw the shape
						// t1 and t2 always are 1 or more
						uint16_t v_total_width = v_t1_width;
						auto v_thread_1 = std::async(std::launch::async, [](const int16_t& p_total_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
							for (int16_t x = p_top_left.X; x < p_top_left.X + p_total_width; x++) {
								Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color);
							}
						}, v_total_width, p_top_left, p_size, p_character, p_color);
						uint16_t v_last_width = v_total_width;
						v_total_width = v_total_width + v_t2_width;
						auto v_thread_2 = std::async(std::launch::async, [](const int16_t& p_total_width, const int16_t& last_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
							for (int16_t x = p_top_left.X + last_width; x < p_top_left.X + p_total_width; x++) {
								Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color);
							}
						}, v_total_width, v_last_width, p_top_left, p_size, p_character, p_color);
						// t3 and t4 can be 0
						if (v_t3_width != 0) {
							v_last_width = v_total_width;
							v_total_width = v_total_width + v_t3_width;
							auto v_thread_3 = std::async(std::launch::async, [](const int16_t& p_total_width, const int16_t& last_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
								for (int16_t x = p_top_left.X + last_width; x < p_top_left.X + p_total_width; x++) {
									Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color);
								}
							}, v_total_width, v_last_width, p_top_left, p_size, p_character, p_color);
						}
						if (v_t4_width != 0) {
							v_last_width = v_total_width;
							v_total_width = v_total_width + v_t4_width;
							auto v_thread_4 = std::async(std::launch::async, [](const int16_t& p_total_width, const int16_t& last_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
								for (int16_t x = p_top_left.X + last_width; x < p_top_left.X + p_total_width; x++) {
									Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color);
								}
							}, v_total_width, v_last_width, p_top_left, p_size, p_character, p_color);
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_Rectangle_Horizontal(const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
					try {
						for (int16_t y = p_top_left.Y; y < p_top_left.Y + p_size.Y; y++) {
							Draw_Line({ p_top_left.X, y }, { (int16_t)(p_top_left.X + p_size.X), y }, p_character, p_color);
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
				}
				const std::map<Console_Manip::Msg_Types, Console_Color>& Console_Manip::Msg_Colors() {
					return *m_msg_colors;
				}
				void Console_Manip::Release_Console() {
					if (pw::Engine_Memory::Deallocate<std::map<Console_Manip::Msg_Types, Console_Color>>(m_msg_colors) == false) {
						if (m_msg_colors != nullptr) {
							delete m_msg_colors;
							m_msg_colors = nullptr;
						}
					}
					if (TRY_LINE FreeConsole() == FALSE) {
						throw er::Severe_Error(L"Console", Console_Error::Windows_Last_Error(), EXCEPTION_LINE, __FILEW__, L"FreeConsole");
					}
				}
			// End of Class Members
		//////////////////////////////////
		CN_NAMESPACE_END
		//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////