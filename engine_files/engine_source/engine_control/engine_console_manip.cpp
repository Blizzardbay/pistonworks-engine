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
						m_color_creation{ 0 } {
				}
				Console_Color::Console_Color(Win_Text_Color text_color, Win_Backaround_Color backaround_color) :
						m_color_creation{ 0 } {
					m_color_creation = (WORD)text_color | (WORD)backaround_color;
				}
				Console_Color::~Console_Color() {
				}
				const uint16_t& Console_Color::Return_Color() const {
					return m_color_creation;
				}
			// End of Class Members
			// Console_Manip
				uint16_t Console_Manip::console_width{ 100 };
				uint16_t Console_Manip::console_height{ 40 };
				wchar_t* Console_Manip::console_screen_buffer{ nullptr };
				HWND Console_Manip::window_handle{ NULL };
				HANDLE Console_Manip::screen_handle{ NULL };
				HANDLE Console_Manip::console_output{ NULL };
				COORD Console_Manip::write_coord{ 0,0 };
				uint16_t Console_Manip::msg_line{0};
				std::map<Console_Manip::Msg_Types, Console_Color> Console_Manip::msg_colors{
					std::make_pair(Console_Manip::Msg_Types::E_CLEAR, Console_Color{Win_Text_Color::BLACK, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::E_DEFAULT, Console_Color{Win_Text_Color::BRIGHT_WHITE, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::E_ENGINE, Console_Color{Win_Text_Color::GREEN, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::E_GAME, Console_Color{Win_Text_Color::YELLOW, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::E_INFO, Console_Color{Win_Text_Color::PINK, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::E_ERROR, Console_Color{ Win_Text_Color::RED, Win_Backaround_Color::DARK_RED}),
					std::make_pair(Console_Manip::Msg_Types::E_SUCCESS, Console_Color{ Win_Text_Color::BLUE, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::E_CONSOLE_OUT, Console_Color{ Win_Text_Color::WHITE, Win_Backaround_Color::BLACK})
				};
			// Static Declarations
			// Class Members
				void Console_Manip::Set_Up_Console() {
					try {
						TRY_LINE window_handle = GetConsoleWindow();
						// In the event the GetConsoleWindow cannot find the console throw a 
						// Console_Error
						if (window_handle == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"GetConsoleWindow");
						}
						// The windows API does not standard error handling for this function
						TRY_LINE ShowWindow(window_handle, SW_HIDE);

						// Make it so we can draw on our console
						TRY_LINE screen_handle = CreateConsoleScreenBuffer(GENERIC_READ, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

						if (screen_handle == INVALID_HANDLE_VALUE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"CreateConsoleScreenBuffer");
						}
						// Make the console un-resize-able
						if (TRY_LINE SetWindowLongA(window_handle, GWL_STYLE, GetWindowLongA(window_handle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX) == NULL) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetWindowLongA");
						}
						// Make the cursor go away
						TRY_LINE console_output = GetStdHandle(STD_OUTPUT_HANDLE);

						if (TRY_LINE console_output == INVALID_HANDLE_VALUE || console_output == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"GetStdHandle");
						}

						if (TRY_LINE setlocale(LC_ALL, "chinese") == nullptr) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"setlocale");
						}
						if (TRY_LINE SetConsoleOutputCP(CP_UTF8) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleOutputCP");
						}
						if (TRY_LINE SetConsoleCP(CP_UTF8) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleCP");
						}

						try {
							TRY_LINE CONSOLE_FONT_INFOEX v_font_info;
							v_font_info.cbSize = sizeof(v_font_info);
							v_font_info.FontFamily = 54;
							v_font_info.FontWeight = 400;
							v_font_info.nFont = 0;
							TRY_LINE const wchar_t v_font[] = L"KaiTi";
							v_font_info.dwFontSize = { 120, 15 };

							std::copy(v_font, v_font + (sizeof(v_font) / sizeof(wchar_t)), v_font_info.FaceName);

							if (TRY_LINE SetCurrentConsoleFontEx(console_output, false, &v_font_info) == FALSE) {
								throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetCurrentConsoleFontEx");
							}
						}
						catch (const std::bad_alloc& v_error) {
							throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"CONSOLE_FONT_INFOEX / Font");
						}
						try {
							TRY_LINE CONSOLE_CURSOR_INFO cursor_info{};

							if (TRY_LINE GetConsoleCursorInfo(console_output, &cursor_info) == FALSE) {
								throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"GetConsoleCursorInfo");
							}
							cursor_info.bVisible = false;
							if (TRY_LINE SetConsoleCursorInfo(console_output, &cursor_info) == FALSE) {
								throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleCursorInfo");
							}
						}
						catch (const std::bad_alloc& v_error) {
							throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"CONSOLE_FONT_INFOEX / Font");
						}
						catch (const er::Severe_Error& v_error) {
							throw v_error;
						}
						try {
							TRY_LINE console_screen_buffer = pw::Engine_Memory::Allocate<wchar_t>((size_t)console_width * (size_t)console_height);
						}
						catch (const std::bad_alloc& v_error) {
							throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"console_screen_buffer");
						}

						if (TRY_LINE SetConsoleTitleW(L"Pistonworks Console") == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleTitleW");
						}
						std::wstring v_temp_wstr{};

						v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
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
						v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
						v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");

						for (size_t i = 0; i < console_height; i++) {
							for (size_t j = 0; j < console_width; j++) {
								console_screen_buffer[(i * console_width) + j] = v_temp_wstr[(i * TO_UINT64(console_width)) + j];
							}
						}

						if (TRY_LINE SetConsoleActiveScreenBuffer(console_output) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleActiveScreenBuffer");
						}
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Resize(uint32_t&& p_size_x, uint32_t&& p_size_y) {
					try {
						TRY_LINE COORD v_size;
						v_size.X = p_size_x;
						v_size.Y = p_size_y;

						TRY_LINE SMALL_RECT v_console_rect;
						v_console_rect.Left = 0;
						v_console_rect.Top = 0;
						v_console_rect.Right = v_size.X - 1;
						v_console_rect.Bottom = v_size.Y - 1;

						if (TRY_LINE SetConsoleWindowInfo(console_output, TRUE, &v_console_rect) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleWindowInfo");
						}
						if (TRY_LINE SetConsoleScreenBufferSize(console_output, v_size) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleScreenBufferSize");
						}
						if (TRY_LINE SetConsoleActiveScreenBuffer(console_output) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleActiveScreenBuffer");
						}
					}
					catch (const std::bad_alloc& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"COORD / SMALL_RECT");
					}
					catch (const std::out_of_range& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"v_console_rect");
					}
					catch (const std::length_error& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"v_size");
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"COORD / SMALL_RECT");
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Draw_Screen() {
					try {
						WORD color{ (WORD)Win_Text_Color::GREY | (WORD)Win_Backaround_Color::GREY };
						WORD color_default{ (WORD)Win_Text_Color::BLACK | (WORD)Win_Backaround_Color::BLACK };

						DWORD bytes_received = 0;

						TRY_LINE Resize(100, 40);

						for (int i = 0; i < console_height; i++) {
							std::wstring line{};
							for (int j = 0; j < console_width; j++) {
								line.push_back(console_screen_buffer[(i * console_width) + j]);
								if (line.at(j) != L' ') {
									if (TRY_LINE WriteConsoleOutputAttribute(console_output, &color, 1, { TO_INT16(j), TO_INT16(i) }, &bytes_received) == FALSE) {
										throw er::Warning_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"WriteConsoleOutputAttribute");
									}
								}
								else {
									if (TRY_LINE WriteConsoleOutputAttribute(console_output, &color_default, 1, { TO_INT16(j), TO_INT16(i) }, &bytes_received) == FALSE) {
										throw er::Warning_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"WriteConsoleOutputAttribute");
									}
								}
							}
							if (TRY_LINE WriteConsoleOutputCharacterW(console_output, line.c_str(), console_width, { 0, TO_INT16(i) }, &bytes_received) == FALSE) {
								throw er::Warning_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"WriteConsoleOutputCharacterW");
							}
						}
						// The windows API does not standard error handling for this function
						TRY_LINE ShowWindow(window_handle, SW_SHOW);
						// Not guaranteed but we can try
						TRY_LINE SetFocus(window_handle);
						if (TRY_LINE SetConsoleActiveScreenBuffer(console_output) == FALSE) {
							throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"SetConsoleActiveScreenBuffer");
						}
					}
					catch (const std::bad_alloc& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"WORD / DWORD");
					}
					catch (const std::length_error& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"console_screen_buffer");
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"console_screen_buffer");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Print_Info(std::wstring&& from, std::wstring&& msg, uint16_t&& line) {
					// Line 1 Reserved: 
					// Line 1 Reserved:
					// Line 1 Reserved:
					// Line 1 Reserved:
					// Line 1 Reserved:
					// Line 1 Reserved:
					// Line 1 Reserved:
					// Line 1 Reserved:
					try {
						DWORD bytes_written = 0;
						std::wstring wstr{ L"||" };

						size_t converted_chars = 0;

						wstr.insert(1, from);

						wstr.insert(from.size() + 2, msg);

						int16_t x_off = 80;
						// Fix weird Unicode character flaw
						std::wstring temp_wstr{ wstr };

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
						wstr = temp_wstr;

						if (wstr.size() > 18) {
							for (size_t i = 0; i < 18; i++) {
								int16_t x_pos = x_off + (int16_t)i;
								Console_Manip::Draw_WChar(COORD{ x_pos, TO_INT16(line + 2) }, std::move(wstr.at(i)), std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
							}
							Console_Manip::Draw_WChar(COORD{ TO_INT16(x_off + 17), TO_INT16(line + 2) }, L'|', std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
						}
						else {
							for (size_t i = 0; i < wstr.size(); i++) {
								int16_t x_pos = x_off + (int16_t)i;
								Console_Manip::Draw_WChar(COORD{ x_pos, TO_INT16(line + 2) }, std::move(wstr.at(i)), std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
							}
							for (size_t i = 0; i < (18 - wstr.size()); i++) {
								int16_t x_pos = x_off + (int16_t)i + wstr.size();
								Console_Manip::Draw_WChar(COORD{ x_pos, TO_INT16(line + 2) }, L' ', std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
							}
							Console_Manip::Draw_WChar(COORD{ TO_INT16(x_off + 17), TO_INT16(line + 2) }, L'|', std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"Draw_WChar");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				void Console_Manip::Print_Console(std::wstring&& from, std::wstring&& msg, Msg_Types&& msg_type, bool&& block_msg) {
					try {
						DWORD bytes_written = 0;
						std::wstring wstr{ L"|||" };

						size_t converted_chars = 0;

						wstr.insert(1, TO_WSTRING(__TIME__));

						switch (msg_type) {
							case Msg_Types::E_CLEAR: {
								break;
							}
							case Msg_Types::E_ENGINE: {
								wstr.insert(10, L"ENGINE ");
								break;
							}
							case Msg_Types::E_ERROR: {
								wstr.insert(10, L"ERROR  ");
								break;
							}
							case Msg_Types::E_GAME: {
								wstr.insert(10, L"GAME   ");
								break;
							}
							case Msg_Types::E_INFO: {
								wstr.insert(10, L"INFO   ");
								break;
							}
							case Msg_Types::E_SUCCESS: {
								wstr.insert(10, L"SUCCESS");
								break;
							}
							case Msg_Types::E_DEFAULT:
							default: {
								wstr.insert(10, L"COUTMSG");
								break;
							}
						}
						if (block_msg == true) {
							wstr.insert(18, from);
							wstr.insert(from.size() + 18, msg);
						}
						else {
							wstr.insert(18, std::wstring(from + L"| "));
							wstr.insert(from.size() + 20, msg);
						}

						int16_t x_off = 2;
						// Fix weird Unicode character flaw
						std::wstring temp_wstr{ wstr };

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
						wstr = temp_wstr;

						er::Error_Log::Dump_Log(wstr.c_str());

						if (wstr.size() > 75) {
							for (size_t i = 0; i < 76; i++) {
								int16_t x_pos = x_off + (int16_t)i;
								Console_Manip::Draw_WChar(COORD{ x_pos, TO_INT16(msg_line + 2) }, std::move(wstr.at(i)), std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
							}
							Console_Manip::Draw_WChar(COORD{ 77, TO_INT16(msg_line + 2) }, L'|', std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
						}
						else {
							for (size_t i = 0; i < wstr.size(); i++) {
								int16_t x_pos = x_off + (int16_t)i;
								Console_Manip::Draw_WChar(COORD{ x_pos, TO_INT16(msg_line + 2) }, std::move(wstr.at(i)), std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
							}
							Console_Manip::Draw_WChar(COORD{ 77, TO_INT16(msg_line + 2) }, L'|', std::move(msg_colors.at(Console_Manip::Msg_Types::E_DEFAULT)));
						}

						for (size_t i = 0; i < 7; i++) {
							int16_t x_pos = x_off + (int16_t)i + 10;

							if (TRY_LINE WriteConsoleOutputAttribute(console_output, &msg_colors.at(msg_type).Return_Color(), 1, { x_pos, TO_INT16(msg_line + 2) }, &bytes_written) == FALSE) {
								throw er::Warning_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"WriteConsoleOutputAttribute");
							}
						}

						msg_line = msg_line + 1;
						if (msg_line > 35) {
							msg_line = 0;
							Clear_Console();
						}
					}
					catch (const std::invalid_argument& v_error) {
						throw er::Severe_Error(L"Console", TO_WSTRING(v_error.what()), std::move(EXCEPTION_LINE), __FILEW__, L"Draw_WChar");
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
						int16_t x_off = 2;

						for (int16_t i = 0; i < 76; i++) {
							for (int16_t j = 0; j < 36; j++) {
								Console_Manip::Draw_WChar(COORD{ TO_INT16(i + x_off),  TO_INT16(j + 2) }, L' ', std::move(msg_colors.at(Console_Manip::Msg_Types::E_CLEAR)));
							}
						}
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
				}
				void Console_Manip::Draw_WChar(COORD&& position, const wchar_t&& character, Console_Color&& color) {
					DWORD bytes_written = 0;
					if (position.X < 0 || position.Y < 0) {
						throw std::invalid_argument("position");
					}

					if (TRY_LINE WriteConsoleOutputCharacterW(console_output, &character, 1, position, &bytes_written) == FALSE) {
						throw er::Warning_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"WriteConsoleOutputCharacterW");
					}
					if (TRY_LINE WriteConsoleOutputAttribute(console_output, &color.Return_Color(), 1, position, &bytes_written) == FALSE) {
						throw er::Warning_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"WriteConsoleOutputAttribute");
					}
				}
				void Console_Manip::Draw_Line(COORD&& start, COORD&& end, wchar_t&& character, Console_Color&& color) {
					try {
						if (start.X < 0 || start.Y < 0) {
							throw std::invalid_argument("start");
						}
						if (end.X < 0 || end.Y < 0) {
							throw std::invalid_argument("end");
						}

						if (abs(end.Y - start.Y) < abs(end.X - start.X)) {
							if (start.X > end.X) {
								Draw_Line_Low(std::move(end), std::move(start), std::move(character), std::move(color));
							}
							else {
								Draw_Line_Low(std::move(start), std::move(end), std::move(character), std::move(color));
							}
						}
						else {
							if (start.Y > end.Y) {
								Draw_Line_High(std::move(end), std::move(start), std::move(character), std::move(color));
							}
							else {
								Draw_Line_High(std::move(start), std::move(end), std::move(character), std::move(color));
							}
						}
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
				}
				void Console_Manip::Draw_Line_Low(COORD&& start, COORD&& end, wchar_t&& character, Console_Color&& color) {
					try {
						// Does not need to check if start and end values are correct the previous function Draw_Line does that automatically
						int16_t dx = end.X - start.X;
						int16_t dy = end.Y - start.Y;

						int16_t yi = 1;
						if (dy < 0) {
							yi = -1;
							dy = -(dy);
						}
						int16_t d = (dy * 2) - dx;
						int16_t y = start.Y;

						for (int16_t x = start.X; x < end.X; x++) {
							Draw_WChar({ x,y }, std::move(character), std::move(color));
							if (d > 0) {
								y = y + yi;
								d = d + (2 * (dy - dx));
							}
							else {
								d = d + 2 * dy;
							}
						}
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
				}
				void Console_Manip::Draw_Line_High(COORD&& start, COORD&& end, wchar_t&& character, Console_Color&& color) {
					try {
						// Does not need to check if start and end values are correct the previous function Draw_Line does that automatically
						int16_t dx = end.X - start.X;
						int16_t dy = end.Y - start.Y;

						int16_t xi = 1;
						if (dy < 0) {
							xi = -1;
							dx = -(dx);
						}
						int16_t d = (dx * 2) - dy;
						int16_t x = start.X;

						for (int16_t y = start.Y; y < end.Y; y++) {
							Draw_WChar({ x,y }, std::move(character), std::move(color));
							if (d > 0) {
								x = x + xi;
								d = d + (2 * (dx - dy));
							}
							else {
								d = d + 2 * dx;
							}
						}
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
				}
				void Console_Manip::Draw_Rectangle_Vertical(COORD&& top_left, COORD&& size, wchar_t&& character, Console_Color&& color) { 
					try {
						int16_t v_t1_width = 0;
						int16_t v_t2_width = 0;
						int16_t v_t3_width = 0;
						int16_t v_t4_width = 0;
						// 2 or greater
						assert(size.X != 0 && size.X != 1);
						assert(size.Y != 0 && size.Y != 1);
						// Even
						if (size.X % 2 == 0) {
							switch (size.X % 4) {
								case 2: {
									int16_t full_quartets = size.X / 4;
									v_t1_width = v_t1_width + 1;
									v_t2_width = v_t2_width + 1;
									for (int16_t i = 0; i < full_quartets; i++) {
										v_t1_width = v_t1_width + 1;
										v_t2_width = v_t2_width + 1;
										v_t3_width = v_t3_width + 1;
										v_t4_width = v_t4_width + 1;
									}
									break;
								}
								case 0: {
									int16_t full_quartets = size.X / 4;
									for (int16_t i = 0; i < full_quartets; i++) {
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
							if (size.X - v_t1_width != 0) {
								switch ((size.X - v_t1_width) % 4) {
									case 2: {
										int16_t full_quartets = (size.X - v_t1_width) / 4;
										v_t1_width = v_t1_width + 1;
										v_t2_width = v_t2_width + 1;
										for (int16_t i = 0; i < full_quartets; i++) {
											v_t1_width = v_t1_width + 1;
											v_t2_width = v_t2_width + 1;
											v_t3_width = v_t3_width + 1;
											v_t4_width = v_t4_width + 1;
										}
										break;
									}
									case 0: {
										int16_t full_quartets = size.X / 4;
										for (int16_t i = 0; i < full_quartets; i++) {
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
						auto v_thread_1 = std::async(std::launch::async, [](int16_t total_width, COORD* top_left, COORD* size, wchar_t&& character, Console_Color&& color) {
							for (int16_t x = top_left->X; x < top_left->X + total_width; x++) {
								Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, std::move(character), std::move(color));
							}
						}, v_total_width, &top_left, &size, std::move(character), std::move(color));
						uint16_t v_last_width = v_total_width;
						v_total_width = v_total_width + v_t2_width;
						auto v_thread_2 = std::async(std::launch::async, [](int16_t total_width, int16_t last_width, COORD* top_left, COORD* size, wchar_t&& character, Console_Color&& color) {
							for (int16_t x = top_left->X + last_width; x < top_left->X + total_width; x++) {
								Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, std::move(character), std::move(color));
							}
						}, v_total_width, v_last_width, & top_left, & size, std::move(character), std::move(color));
						// t3 and t4 can be 0
						if (v_t3_width != 0) {
							v_last_width = v_total_width;
							v_total_width = v_total_width + v_t3_width;
							auto v_thread_3 = std::async(std::launch::async, [](int16_t total_width, int16_t last_width, COORD* top_left, COORD* size, wchar_t&& character, Console_Color&& color) {
								for (int16_t x = top_left->X + last_width; x < top_left->X + total_width; x++) {
									Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, std::move(character), std::move(color));
								}
							}, v_total_width, v_last_width, &top_left, &size, std::move(character), std::move(color));
						}
						if (v_t4_width != 0) {
							v_last_width = v_total_width;
							v_total_width = v_total_width + v_t4_width;
							auto v_thread_4 = std::async(std::launch::async, [](int16_t total_width, int16_t last_width, COORD* top_left, COORD* size, wchar_t&& character, Console_Color&& color) {
								for (int16_t x = top_left->X + last_width; x < top_left->X + total_width; x++) {
									Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, std::move(character), std::move(color));
								}
							}, v_total_width, v_last_width, &top_left, &size, std::move(character), std::move(color));
						}
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
				}
				void Console_Manip::Draw_Rectangle_Horizontal(COORD&& top_left, COORD&& size, wchar_t&& character, Console_Color&& color) {
					try {
						for (int16_t y = top_left.Y; y < top_left.Y + size.Y; y++) {
							Draw_Line({ top_left.X, y }, { (int16_t)(top_left.X + size.X), y }, std::move(character), std::move(color));
						}
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
				}
				const std::map<Console_Manip::Msg_Types, Console_Color>& Console_Manip::Msg_Colors() {
					return msg_colors;
				}
				void Console_Manip::Delete_Console() {
					if (TRY_LINE PostMessageW(window_handle, WM_CLOSE, 0, 0) == FALSE) {
						throw er::Severe_Error(L"Console", std::move(Console_Error::Windows_Last_Error()), std::move(EXCEPTION_LINE), __FILEW__, L"PostMessageW");
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