#include "control\console_manip.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		CN_NAMESPACE_SRT
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

					if (TRY_LINE FormatMessageW(
						FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, v_error_code, LANG_SYSTEM_DEFAULT, (LPWSTR)&v_error_string, NULL, NULL) == NULL) {

						LocalFree(v_error_string);

						SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Error", std::wstring(std::wstring(L"FormatMessageW Function Failure: Error Code: ") + std::to_wstring(v_error_code)), ERROR_LINE, __FILEW__, L"Windows_Last_Error"));

						return std::wstring(std::wstring(L"FormatMessageW Function Failure: Error Code: ") + std::to_wstring(v_error_code));
					}
					else {
						if (v_error_string != nullptr) {
							v_error.append(v_error_string);

							LocalFree(v_error_string);

							return v_error;
						}
						else {
							SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);
							SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Error", std::wstring(std::wstring(L"FormatMessageW Function Failure: Error Code: ") + std::to_wstring(v_error_code)), ERROR_LINE, __FILEW__, L"Windows_Last_Error"));

							return std::wstring(std::wstring(L"FormatMessageW Function Failure: Error Code: ") + std::to_wstring(v_error_code));
						}
					}
				}
			// Console_Color
			// Static Declarations
			// Class Members
				Console_Color::Console_Color() noexcept :
						m_color_attribute{ 0 } {
				}
				Console_Color::Console_Color(const Win_Text_Color& p_text_color, const Win_Backaround_Color& p_backaround_color) noexcept :
						m_color_attribute{ 0 } {
					m_color_attribute = TO_UINT16((WORD)p_text_color | (WORD)p_backaround_color);
				}
				const uint16_t& Console_Color::Return_Color() const noexcept {
					return m_color_attribute;
				}
			// Console_Msg
			// Static Declarations
			// Class Members
				Console_Msg::Console_Msg(const std::wstring_view& p_from, const std::wstring_view& p_msg, const pw::co::cn::Msg_Types& p_msg_type) : 
						m_from{ p_from }, m_msg{ p_msg }, m_msg_type{ p_msg_type } {
				}
				Console_Msg::~Console_Msg() {
				}
				const std::wstring_view& Console_Msg::From() const noexcept {
					return m_from;
				}
				const std::wstring_view& Console_Msg::Msg() const noexcept {
					return m_msg;
				}
				const pw::co::cn::Msg_Types& Console_Msg::Type() const noexcept {
					return m_msg_type;
				}
			// Console_Manip
				uint16_t Console_Manip::m_console_width{ 100 };
				uint16_t Console_Manip::m_console_height{ 40 };
				wchar_t* Console_Manip::m_console_screen_buffer{ nullptr };
				HWND Console_Manip::m_window_handle{ NULL };
				HANDLE Console_Manip::m_screen_handle{ NULL };
				HANDLE Console_Manip::m_console_output{ NULL };
				COORD Console_Manip::m_write_coord{ 0,0 };
				uint16_t Console_Manip::m_msg_line{ 0 };
				std::map<pw::co::cn::Msg_Types, Console_Color>* Console_Manip::m_msg_colors{ nullptr };
			// Static Declarations
			// Class Members
				void Console_Manip::Set_Up_Console() {
					TRY_LINE m_window_handle = GetConsoleWindow();

					if (m_window_handle == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();
						
						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function GetConsoleWindow: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function GetConsoleWindow: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					// The windows API does not standard error handling for this function
					ShowWindow(m_window_handle, SW_HIDE);

					// Make it so we can draw on our console
					TRY_LINE m_screen_handle = CreateConsoleScreenBuffer(GENERIC_READ, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

					if (m_screen_handle == INVALID_HANDLE_VALUE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function CreateConsoleScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function CreateConsoleScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					// Make the console un-resize-able
					if (TRY_LINE SetWindowLongA(m_window_handle, GWL_STYLE, GetWindowLongA(m_window_handle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX) == NULL) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetWindowLongA: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetWindowLongA: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					// Make the cursor go away
					TRY_LINE m_console_output = GetStdHandle(STD_OUTPUT_HANDLE);

					if (m_console_output == INVALID_HANDLE_VALUE || m_console_output == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function GetStdHandle: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function GetStdHandle: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}

					if (TRY_LINE setlocale(LC_ALL, "chinese") == nullptr) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function setlocale: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function setlocale: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					if (TRY_LINE SetConsoleOutputCP(CP_UTF8) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleOutputCP: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleOutputCP: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					if (TRY_LINE SetConsoleCP(CP_UTF8) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleCP: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleCP: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}

					CONSOLE_FONT_INFOEX v_font_info;
					v_font_info.cbSize = sizeof(v_font_info);
					v_font_info.FontFamily = 54;
					v_font_info.FontWeight = 700;
					v_font_info.nFont = 0;
					const wchar_t v_font[] = L"Consolas";
					v_font_info.dwFontSize = { 120, 15 };

					std::copy(v_font, v_font + (sizeof(v_font) / sizeof(wchar_t)), v_font_info.FaceName);

					if (TRY_LINE SetCurrentConsoleFontEx(m_console_output, false, &v_font_info) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetCurrentConsoleFontEx: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetCurrentConsoleFontEx: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					CONSOLE_CURSOR_INFO v_cursor_info{};

					if (TRY_LINE GetConsoleCursorInfo(m_console_output, &v_cursor_info) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function GetConsoleCursorInfo: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function GetConsoleCursorInfo: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					v_cursor_info.bVisible = false;
					if (TRY_LINE SetConsoleCursorInfo(m_console_output, &v_cursor_info) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleCursorInfo: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleCursorInfo: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					PW_CALL(m_console_screen_buffer = pw::co::Memory::Allocate<wchar_t>(TO_UINT64(m_console_width) * TO_UINT64(m_console_height)), true);

					if (TRY_LINE SetConsoleTitleW(L"Pistonworks Console") == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleTitleW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleTitleW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
					std::wstring v_temp_wstr{};

					v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
					for (char i = 0; i < 38; i++) {
						v_temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					}
					v_temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");

					for (size_t i = 0; i < m_console_height; i++) {
						for (size_t j = 0; j < m_console_width; j++) {
							m_console_screen_buffer[(i * m_console_width) + j] = v_temp_wstr[(i * TO_UINT64(m_console_width)) + j];
						}
					}

					if (TRY_LINE SetConsoleActiveScreenBuffer(m_console_output) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleActiveScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleActiveScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Set_Up_Console"));
								return;
							}
						}
					}
				}
				void Console_Manip::Initialize() {
					std::map<pw::co::cn::Msg_Types, Console_Color> v_temp{
						std::make_pair(pw::co::cn::Msg_Types::E_CLEAR, Console_Color{ Win_Text_Color::BLACK, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_DEFAULT, Console_Color{ Win_Text_Color::BRIGHT_WHITE, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_ENGINE, Console_Color{ Win_Text_Color::GREEN, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_GAME, Console_Color{ Win_Text_Color::YELLOW, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_INFO, Console_Color{ Win_Text_Color::PINK, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_ERROR, Console_Color{ Win_Text_Color::RED, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_SUCCESS, Console_Color{ Win_Text_Color::BLUE, Win_Backaround_Color::BLACK }),
						std::make_pair(pw::co::cn::Msg_Types::E_CONSOLE_OUT, Console_Color{ Win_Text_Color::WHITE, Win_Backaround_Color::BLACK })
					};
					// Template arguments do not work inside proper macros *PW_CALL*
					typedef std::map<pw::co::cn::Msg_Types, pw::co::cn::Console_Color> MSG_COLORS;
					PW_CALL(m_msg_colors = pw::co::Memory::Allocate_Args<MSG_COLORS>(v_temp), true);
				}
				void Console_Manip::Resize(const uint32_t& p_size_x, const uint32_t& p_size_y) {
					COORD v_size{};
					v_size.X = TO_INT16(p_size_x);
					v_size.Y = TO_INT16(p_size_y);

					SMALL_RECT v_console_rect{};
					v_console_rect.Left = 0;
					v_console_rect.Top = 0;
					v_console_rect.Right = v_size.X - 1;
					v_console_rect.Bottom = v_size.Y - 1;

					if (TRY_LINE SetConsoleWindowInfo(m_console_output, TRUE, &v_console_rect) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleWindowInfo: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Resize"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleWindowInfo: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Resize"));
								return;
							}
						}
					}
					if (TRY_LINE SetConsoleScreenBufferSize(m_console_output, v_size) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleScreenBufferSize: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Resize"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleScreenBufferSize: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Resize"));
								return;
							}
						}
					}
					if (TRY_LINE SetConsoleActiveScreenBuffer(m_console_output) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleActiveScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Resize"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleActiveScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Resize"));
								return;
							}
						}
					}
				}
				void Console_Manip::Draw_Screen() {
					WORD v_color{ (WORD)Win_Text_Color::DARK_BLUE | (WORD)Win_Backaround_Color::DARK_BLUE };
					WORD v_color_default{ (WORD)Win_Text_Color::BLACK | (WORD)Win_Backaround_Color::BLACK };

					DWORD v_bytes_received{ 0 };

					PW_CALL(Resize(100U, 40U), true);

					for (uint16_t i{ 0 }; i < m_console_height; i++) {
						std::wstring v_line{};
						for (uint16_t j{ 0 }; j < m_console_width; j++) {
							v_line.push_back(m_console_screen_buffer[ADD_UINT64(MUL_UINT64(i, m_console_width), j)]);
							if (v_line.at(j) != L' ') {
								if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &v_color, 1, { TO_INT16(j), TO_INT16(i) }, &v_bytes_received) == FALSE) {
									std::wstring v_win_error = Console_Error::Windows_Last_Error();

									if (v_win_error != std::wstring()) {
										if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
											SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

											std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

											SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
											return;
										}
										else {
											pw::er::Error_State::Handle_Error();

											SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

											std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

											SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
											return;
										}
									}
								}
							}
							else {
								if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &v_color_default, 1, { TO_INT16(j), TO_INT16(i) }, &v_bytes_received) == FALSE) {
									std::wstring v_win_error = Console_Error::Windows_Last_Error();

									if (v_win_error != std::wstring()) {
										if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
											SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

											std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

											SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
											return;
										}
										else {
											pw::er::Error_State::Handle_Error();

											SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

											std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

											SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
											return;
										}
									}
								}
							}
						}
						if (TRY_LINE WriteConsoleOutputCharacterW(m_console_output, v_line.c_str(), m_console_width, { 0, TO_INT16(i) }, &v_bytes_received) == FALSE) {
							std::wstring v_win_error = Console_Error::Windows_Last_Error();

							if (v_win_error != std::wstring()) {
								if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
									SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

									std::wstring v_total_error = { L"Function WriteConsoleOutputCharacterW: " + v_win_error };

									SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
									return;
								}
								else {
									pw::er::Error_State::Handle_Error();

									SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

									std::wstring v_total_error = { L"Function WriteConsoleOutputCharacterW: " + v_win_error };

									SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
									return;
								}
							}
						}
					}
					// The windows API does not standard error handling for this function
					TRY_LINE ShowWindow(m_window_handle, SW_SHOW);
					// Not guaranteed but we can try
					TRY_LINE SetFocus(m_window_handle);
					if (TRY_LINE SetConsoleActiveScreenBuffer(m_console_output) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleActiveScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleActiveScreenBuffer: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Screen"));
								return;
							}
						}
					}
				}
				void Console_Manip::Print_Info(const std::wstring& p_from, const std::wstring& p_msg, const uint16_t& p_line) {
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

					while (v_wstr.size() < 18) {
						v_wstr.push_back(L' ');
					}
					v_wstr.push_back(L'|');

					PW_CALL(Draw_Text_Line({ v_x_off , TO_INT16(p_line + 1) }, v_wstr, m_msg_colors->at(pw::co::cn::Msg_Types::E_DEFAULT)), true);
				}
				void Console_Manip::Print_Console(const std::wstring& p_from, const std::wstring& p_msg, const pw::co::cn::Msg_Types& p_msg_type, const bool& p_block_msg) {
					if (m_msg_line > 37) {
						m_msg_line = 0;
						Clear_Console();
					}

					DWORD v_bytes_written = 0;
					std::wstring v_wstr{ L"|||" };

					v_wstr.insert(1, TO_WSTRING(__TIME__));

					switch (p_msg_type) {
					case pw::co::cn::Msg_Types::E_CLEAR: {
						break;
					}
					case pw::co::cn::Msg_Types::E_ENGINE: {
						v_wstr.insert(10, L"ENGINE ");
						break;
					}
					case pw::co::cn::Msg_Types::E_ERROR: {
						v_wstr.insert(10, L"ERROR  ");
						break;
					}
					case pw::co::cn::Msg_Types::E_GAME: {
						v_wstr.insert(10, L"GAME   ");
						break;
					}
					case pw::co::cn::Msg_Types::E_INFO: {
						v_wstr.insert(10, L"INFO   ");
						break;
					}
					case pw::co::cn::Msg_Types::E_SUCCESS: {
						v_wstr.insert(10, L"SUCCESS");
						break;
					}
					case pw::co::cn::Msg_Types::E_DEFAULT:_FALLTHROUGH
					case pw::co::cn::Msg_Types::E_CONSOLE_OUT:
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

					er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), v_wstr.c_str());

					PW_CALL(Draw_Text_Line({ v_x_off , INC_INT16(m_msg_line) }, v_wstr.substr(0, v_wstr.size() > 75 ? 75 : v_wstr.size()), m_msg_colors->at(pw::co::cn::Msg_Types::E_DEFAULT)), true);

					PW_CALL(Draw_WChar({ TO_INT16(77), INC_INT16(m_msg_line) }, L'|', m_msg_colors->at(pw::co::cn::Msg_Types::E_DEFAULT)), true);

					for (size_t i = 0; i < 7; i++) {
						int16_t x_pos = v_x_off + (int16_t)i + 10;

						if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &m_msg_colors->at(p_msg_type).Return_Color(), 1, { x_pos, INC_INT16(m_msg_line) }, &v_bytes_written) == FALSE) {
							std::wstring v_win_error = Console_Error::Windows_Last_Error();

							if (v_win_error != std::wstring()) {
								if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
									SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

									std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

									SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Print_Console"));
									return;
								}
								else {
									pw::er::Error_State::Handle_Error();

									SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

									std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

									SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Print_Console"));
									return;
								}
							}
						}
					}

					m_msg_line = INC_UINT16(m_msg_line);
				}
				void Console_Manip::Print_Console(const Console_Msg& p_msg, const bool& p_block_msg) {
					if (m_msg_line > 37) {
						m_msg_line = 0;
						Clear_Console();
					}

					DWORD v_bytes_written = 0;
					std::wstring v_wstr{ L"|||" };

					v_wstr.insert(1, EXPRESSION_TO_WSTRING(__TIME__));

					switch (p_msg.Type()) {
					case pw::co::cn::Msg_Types::E_CLEAR: {
						break;
					}
					case pw::co::cn::Msg_Types::E_ENGINE: {
						v_wstr.insert(10, L"ENGINE ");
						break;
					}
					case pw::co::cn::Msg_Types::E_ERROR: {
						v_wstr.insert(10, L"ERROR  ");
						break;
					}
					case pw::co::cn::Msg_Types::E_GAME: {
						v_wstr.insert(10, L"GAME   ");
						break;
					}
					case pw::co::cn::Msg_Types::E_INFO: {
						v_wstr.insert(10, L"INFO   ");
						break;
					}
					case pw::co::cn::Msg_Types::E_SUCCESS: {
						v_wstr.insert(10, L"SUCCESS");
						break;
					}
					case pw::co::cn::Msg_Types::E_DEFAULT:
					default: {
						v_wstr.insert(10, L"COUTMSG");
						break;
					}
					}
					if (p_msg.From().empty() == true) {
						v_wstr.append(p_msg.Msg());
					}
					else {
						if (p_block_msg == true) {
							v_wstr.insert(18, p_msg.From());
							v_wstr.append(p_msg.Msg());
						}
						else {
							v_wstr.insert(18, std::wstring(p_msg.From()) + L"| ");
							v_wstr.append(p_msg.Msg());
						}
					}

					int16_t v_x_off{ 2 };
					// Fix weird Unicode character flaw
					std::wstring v_temp_wstr{ v_wstr };

					for (uint64_t i = 0; i < v_temp_wstr.size(); i++) {
						if (TO_UINT32(v_temp_wstr.at(i)) > TO_UINT32(127)) {
							if (i != 0) {
								i = INC_UINT64(i);
								v_temp_wstr.insert(i, 1, L' ');
							}
							else {
								v_temp_wstr.insert(0, 1, L' ');
							}
						}
					}
					v_wstr = v_temp_wstr;

					er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), v_wstr.c_str());

					PW_FINAL_CALL(Draw_Text_Line({ v_x_off , INC_INT16(m_msg_line) }, v_wstr.substr(0, v_wstr.size() > 75 ? 75 : v_wstr.size()), m_msg_colors->at(pw::co::cn::Msg_Types::E_DEFAULT)), pw::cm::Constant::Pistonworks_Path());

					PW_FINAL_CALL(Draw_WChar({ TO_INT16(77), INC_INT16(m_msg_line) }, L'|', m_msg_colors->at(pw::co::cn::Msg_Types::E_DEFAULT)), pw::cm::Constant::Pistonworks_Path());

					for (int16_t i{ 0 }; i < TO_INT16(7); i++) {
						int16_t x_pos = ADD_INT16(v_x_off + i, 10);

						if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &m_msg_colors->at(p_msg.Type()).Return_Color(), 1, { x_pos, TO_INT16(m_msg_line + 1) }, &v_bytes_written) == FALSE) {
							std::wstring v_win_error = Console_Error::Windows_Last_Error();

							if (v_win_error != std::wstring()) {
								if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
									SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

									std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

									er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), v_total_error);
									return;
								}
								else {
									SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

									std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

									er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), v_total_error);
									return;
								}
							}
						}
					}
					m_msg_line = INC_UINT16(m_msg_line);
				}
				void Console_Manip::Clear_Console() {
					int16_t v_x_off{ 2 };

					PW_CALL(Draw_WChar_Block(COORD{ TO_INT16(v_x_off), 1 }, COORD{ 78, 39 }, L' ', m_msg_colors->at(pw::co::cn::Msg_Types::E_CLEAR)), true);
				}
				void Console_Manip::Draw_WChar(const COORD& p_position, const wchar_t& p_character, const Console_Color& p_color) {
					DWORD v_bytes_written{ 0 };
					if (p_position.X < 0 || p_position.Y < 0) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_position was .X < 0 || .Y < 0", ERROR_LINE, __FILEW__, L"Draw_WChar"));
						return;
					}

					if (TRY_LINE WriteConsoleOutputCharacterW(m_console_output, &p_character, 1, p_position, &v_bytes_written) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleOutputCharacterW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_WChar"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleOutputCharacterW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_WChar"));
								return;
							}
						}
					}
					if (TRY_LINE WriteConsoleOutputAttribute(m_console_output, &p_color.Return_Color(), 1, p_position, &v_bytes_written) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_WChar"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleOutputAttribute: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_WChar"));
								return;
							}
						}
					}
				}
				void Console_Manip::Draw_WChar_Block(const COORD& p_position, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
					if (p_position.X < 0 || p_position.Y < 0) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_position was .X < 0 || .Y < 0", ERROR_LINE, __FILEW__, L"Draw_WChar_Block"));
						return;
					}
					SMALL_RECT v_write_area{};

					v_write_area.Left = p_position.X;
					v_write_area.Top = p_position.Y;
					v_write_area.Right = p_size.X;
					v_write_area.Bottom = p_size.Y;

					size_t v_block_size = TO_UINT64(p_size.X) * TO_UINT64(p_size.Y);

					CHAR_INFO* v_block{ nullptr };
					PW_CALL(v_block = pw::co::Memory::Allocate<CHAR_INFO>(v_block_size), true);

					for (size_t i = 0; i < v_block_size; i++) {
						v_block[i].Char.UnicodeChar = p_character;
						v_block[i].Attributes = p_color.Return_Color();
					}
					if (TRY_LINE WriteConsoleOutputW(m_console_output, v_block, p_size, p_position, &v_write_area) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleOutputW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_WChar_Block"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleOutputW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_WChar_Block"));
								return;
							}
						}
					}
					if (pw::co::Memory::Deallocate<CHAR_INFO>(v_block) == false) {
						if (v_block != nullptr) {
							delete[] v_block;
							v_block = nullptr;
						}
					}
				}
				void Console_Manip::Draw_Text_Line(const COORD& p_position, const std::wstring& p_block, const Console_Color& p_color) {
					if (p_position.X < 0 || p_position.Y < 0) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_position was .X < 0 || .Y < 0", ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
						return;
					}
					if (TRY_LINE SetConsoleCursorPosition(m_console_output, p_position) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleCursorPosition: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleCursorPosition: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
								return;
							}
						}
					}
					if (TRY_LINE SetConsoleTextAttribute(m_console_output, p_color.Return_Color()) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleTextAttribute: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function SetConsoleTextAttribute: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
								return;
							}
						}
					}

					DWORD v_characters_written{ 0 };

					if (TRY_LINE WriteConsoleW(m_console_output, p_block.c_str(), static_cast<DWORD>(p_block.size()), &v_characters_written, nullptr) == FALSE) {
						std::wstring v_win_error = Console_Error::Windows_Last_Error();

						if (v_win_error != std::wstring()) {
							if (v_win_error.find(L"FormatMessageW Function Failure: Error Code: ") == std::wstring::npos) {
								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
								return;
							}
							else {
								pw::er::Error_State::Handle_Error();

								SET_ERROR_STATE(PW_WIN_FUNCTION_ERROR);

								std::wstring v_total_error = { L"Function WriteConsoleW: " + v_win_error };

								SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::cn::Console_Manip", v_total_error, ERROR_LINE, __FILEW__, L"Draw_Text_Line"));
								return;
							}
						}
					}
				}
				void Console_Manip::Draw_Line(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color) {
					if (p_start.X < 0 || p_start.Y < 0) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_start was .X < 0 || .Y < 0", ERROR_LINE, __FILEW__, L"Draw_Line"));
						return;
					}
					if (p_end.X < 0 || p_end.Y < 0) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_end was .X < 0 || .Y < 0", ERROR_LINE, __FILEW__, L"Draw_Line"));
						return;
					}

					if (abs(p_end.Y - p_start.Y) < abs(p_end.X - p_start.X)) {
						if (p_start.X > p_end.X) {
							PW_CALL(Draw_Line_Low(p_end, p_start, p_character, p_color), true);
						}
						else {
							PW_CALL(Draw_Line_Low(p_start, p_end, p_character, p_color), true);
						}
					}
					else {
						if (p_start.Y > p_end.Y) {
							PW_CALL(Draw_Line_High(p_end, p_start, p_character, p_color), true);
						}
						else {
							PW_CALL(Draw_Line_High(p_start, p_end, p_character, p_color), true);
						}
					}
				}
				void Console_Manip::Draw_Rectangle_Vertical(const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
					// Note using std::async is fast but the console is throughput limited :(
					int16_t v_t1_width{ 0 };
					int16_t v_t2_width{ 0 };
					int16_t v_t3_width{ 0 };
					int16_t v_t4_width{ 0 };
					// 2 or greater
					if (p_size.X != 0 && p_size.X != 1) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_size.X != 0 && p_size.X != 1", ERROR_LINE, __FILEW__, L"Draw_Rectangle_Vertical"));
						return;
					}
					if (p_size.Y != 0 && p_size.Y != 1) {
						SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::cn::Console_Manip", L"Invalid Parameter: p_size.Y != 0 && p_size.Y != 1", ERROR_LINE, __FILEW__, L"Draw_Rectangle_Vertical"));
						return;
					}
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
					int16_t v_total_width = v_t1_width;
					auto v_thread_1 = std::async(std::launch::async, [](const int16_t& p_total_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
						for (int16_t x = p_top_left.X; x < p_top_left.X + p_total_width; x++) {
							PW_CALL(Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color), true);
						}
					}, v_total_width, p_top_left, p_size, p_character, p_color);
					int16_t v_last_width = v_total_width;
					v_total_width = v_total_width + v_t2_width;
					auto v_thread_2 = std::async(std::launch::async, [](const int16_t& p_total_width, const int16_t& last_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
						for (int16_t x = p_top_left.X + last_width; x < p_top_left.X + p_total_width; x++) {
							PW_CALL(Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color), true);
						}
					}, v_total_width, v_last_width, p_top_left, p_size, p_character, p_color);
					// t3 and t4 can be 0
					if (v_t3_width != 0) {
						v_last_width = v_total_width;
						v_total_width = v_total_width + v_t3_width;
						auto v_thread_3 = std::async(std::launch::async, [](const int16_t& p_total_width, const int16_t& last_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
							for (int16_t x = p_top_left.X + last_width; x < p_top_left.X + p_total_width; x++) {
								PW_CALL(Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color), true);
							}
						}, v_total_width, v_last_width, p_top_left, p_size, p_character, p_color);
					}
					if (v_t4_width != 0) {
						v_last_width = v_total_width;
						v_total_width = v_total_width + v_t4_width;
						auto v_thread_4 = std::async(std::launch::async, [](const int16_t& p_total_width, const int16_t& last_width, const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
							for (int16_t x = p_top_left.X + last_width; x < p_top_left.X + p_total_width; x++) {
								PW_CALL(Draw_Line({ x, p_top_left.Y }, { x, (int16_t)(p_top_left.Y + p_size.Y) }, p_character, p_color), true);
							}
						}, v_total_width, v_last_width, p_top_left, p_size, p_character, p_color);
					}
				}
				void Console_Manip::Draw_Rectangle_Horizontal(const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color) {
					for (int16_t y = p_top_left.Y; y < p_top_left.Y + p_size.Y; y++) {
						PW_CALL(Draw_Line({ p_top_left.X, y }, { (int16_t)(p_top_left.X + p_size.X), y }, p_character, p_color), true);
					}
				}
				void Console_Manip::Release() {
					if (pw::co::Memory::Deallocate<std::map<pw::co::cn::Msg_Types, Console_Color>>(m_msg_colors) == false) {
						if (m_msg_colors != nullptr) {
							delete m_msg_colors;
							m_msg_colors = nullptr;
						}
					}
					// No error handling in the release functions, if it does not get destroyed
					// by Pistonworks then its windows or other that destroyed it
					FreeConsole();
				}
				const std::map<pw::co::cn::Msg_Types, Console_Color>& Console_Manip::Msg_Colors() {
					return *m_msg_colors;
				}
				void Console_Manip::Draw_Line_Low(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color) {
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
						PW_CALL(Draw_WChar({ x,y }, p_character, p_color), true);
						if (d > 0) {
							y = y + v_yi;
							d = d + (2 * (v_dy - v_dx));
						}
						else {
							d = d + 2 * v_dy;
						}
					}
				}
				void Console_Manip::Draw_Line_High(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color) {
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
						PW_CALL(Draw_WChar({ x,y }, p_character, p_color), true);
						if (d > 0) {
							x = x + v_xi;
							d = d + (2 * (v_dx - v_dy));
						}
						else {
							d = d + 2 * v_dx;
						}
					}
				}
		CN_NAMESPACE_END
	CO_NAMESPACE_END
PW_NAMESPACE_END