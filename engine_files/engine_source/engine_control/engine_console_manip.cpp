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
			// Console_Color
			// Static Declarations
			// Class Members
				Console_Color::Console_Color() :
						color_creation{ 0 } {
				}
				Console_Color::Console_Color(Win_Text_Color text_color, Win_Backaround_Color backaround_color) :
						color_creation{ 0 } {
					color_creation = (WORD)text_color | (WORD)backaround_color;
				}
				Console_Color::~Console_Color() {
				}
				const uint16_t* Console_Color::Return_Color() {
					return &color_creation;
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
				uint16_t Console_Manip::msg_line{1};
				std::vector<size_t> Console_Manip::times;
				std::map<Console_Manip::Msg_Types, Console_Color> Console_Manip::msg_colors{
					std::make_pair(Console_Manip::Msg_Types::Clear, Console_Color{Win_Text_Color::BLACK, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::Default, Console_Color{Win_Text_Color::BRIGHT_WHITE, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::Engine, Console_Color{Win_Text_Color::GREEN, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::Game, Console_Color{Win_Text_Color::YELLOW, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::Info, Console_Color{Win_Text_Color::PINK, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::Error, Console_Color{ Win_Text_Color::RED, Win_Backaround_Color::DARK_RED}),
					std::make_pair(Console_Manip::Msg_Types::Success, Console_Color{ Win_Text_Color::BLUE, Win_Backaround_Color::BLACK}),
					std::make_pair(Console_Manip::Msg_Types::Console_Out, Console_Color{ Win_Text_Color::WHITE, Win_Backaround_Color::BLACK})
				};
			// Static Declarations
			// Class Members
				void Console_Manip::Set_Up_Console() {
					window_handle = GetConsoleWindow();

					ShowWindow(window_handle, SW_HIDE);

					// Make it so we can draw on our console
					screen_handle = CreateConsoleScreenBuffer(GENERIC_READ, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

					// Make the console un-resize-able
					SetWindowLongA(window_handle, GWL_STYLE, GetWindowLongA(window_handle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
					// Make the cursor go away
					console_output = GetStdHandle(STD_OUTPUT_HANDLE);

					setlocale(LC_ALL, "chinese");
					SetConsoleOutputCP(CP_UTF8);
					SetConsoleCP(CP_UTF8);

					CONSOLE_FONT_INFOEX fontInfo;
					fontInfo.cbSize = sizeof(fontInfo);
					fontInfo.FontFamily = 54;
					fontInfo.FontWeight = 400;
					fontInfo.nFont = 0;
					const wchar_t myFont[] = L"KaiTi";
					fontInfo.dwFontSize = { 120, 15 };
					std::copy(myFont, myFont + (sizeof(myFont) / sizeof(wchar_t)), fontInfo.FaceName);

					SetCurrentConsoleFontEx(console_output, false, &fontInfo);

					CONSOLE_CURSOR_INFO cursor_info{};

					GetConsoleCursorInfo(console_output, &cursor_info);
					cursor_info.bVisible = false;
					SetConsoleCursorInfo(console_output, &cursor_info);

					console_screen_buffer = new wchar_t[(size_t)console_width * (size_t)console_height];

					SetConsoleTitleW(L"Pistonworks Console");

					std::wstring temp_wstr{};

					// 0
					temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
					temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					// 10
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					// 20
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					// 30
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯                                                                            ▯▯                  ▯▯");
					temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
					temp_wstr.append(L"▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯▯");
					// 40

					for (size_t i = 0; i < console_height; i++) {
						for (size_t j = 0; j < console_width; j++) {
							console_screen_buffer[(i * console_width) + j] = temp_wstr[(i * (size_t)console_width) + j];
						}
					}
					SetConsoleActiveScreenBuffer(console_output);
				}
				void Console_Manip::Resize(uint32_t size_x, uint32_t size_y) {
					COORD size;
					size.X = size_x;
					size.Y = size_y;

					SMALL_RECT console_rect;
					console_rect.Left = 0;
					console_rect.Top = 0;
					console_rect.Right = size.X - 1;
					console_rect.Bottom = size.Y - 1;

					SetConsoleScreenBufferSize(console_output, size);

					SetConsoleWindowInfo(console_output, TRUE, &console_rect);

					SetConsoleActiveScreenBuffer(console_output);
				}
				void Console_Manip::Draw_Screen() {
					WORD color{ (WORD)Win_Text_Color::GREY | (WORD)Win_Backaround_Color::GREY };
					WORD color_default{ (WORD)Win_Text_Color::BLACK | (WORD)Win_Backaround_Color::BLACK };

					DWORD bytes_received = 0;

					Resize(100, 40);

					for (int i = 0; i < console_height; i++) {
						std::wstring line{};
						for (int j = 0; j < console_width; j++) {
							line.push_back(console_screen_buffer[(i * console_width) + j]);
							if (line.at(j) != L' ') {
								WriteConsoleOutputAttribute(console_output, &color, 1, { (int16_t)j, (int16_t)(i) }, &bytes_received);
							}
							else {
								WriteConsoleOutputAttribute(console_output, &color_default, 1, { (int16_t)j, (int16_t)(i) }, &bytes_received);
							}
						}
						WriteConsoleOutputCharacterW(console_output, line.c_str(), console_width, { 0, (int16_t)(i) }, &bytes_received);
					}
					ShowWindow(window_handle, SW_SHOW);

					SetFocus(window_handle);

					SetConsoleActiveScreenBuffer(console_output);
				}
				void Console_Manip::Print_Console(wchar_t* from, wchar_t* msg, Msg_Types msg_type, bool block_msg) {
					DWORD bytes_written = 0;
					std::wstring wstr{ L"|||" };

					size_t converted_chars = 0;

					wstr.insert(1, cm::Engine_Constant::To_WString(__TIME__));

					switch (msg_type) {
						case Msg_Types::Clear: {
							break;
						}
						case Msg_Types::Engine: {
							wstr.insert(10, L"ENGINE ");
							break;
						}
						case Msg_Types::Error: {
							wstr.insert(10, L"ERROR  ");
							break;
						}
						case Msg_Types::Game: {
							wstr.insert(10, L"GAME   ");
							break;
						}
						case Msg_Types::Info: {
							wstr.insert(10, L"INFO   ");
							break;
						}
						case Msg_Types::Success: {
							wstr.insert(10, L"SUCCESS");
							break;
						}
						case Msg_Types::Default:
						default: {
							wstr.insert(10, L"COUTMSG");
							break;
						}
					}
					if (block_msg == true) {
						wstr.insert(18, std::wstring(from));
						wstr.insert(std::wcslen(from) + 18, msg);
					}
					else {
						wstr.insert(18, std::wstring(std::wstring(from) + L"| "));
						wstr.insert(std::wcslen(from) + 20, msg);
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

					if (wstr.size() > 75) {
						for (size_t i = 0; i < 76; i++) {
							int16_t x_pos = x_off + (int16_t)i;
							Console_Manip::Draw_WChar(COORD{ x_pos, static_cast<int16_t>(msg_line) }, wstr.at(i), msg_colors.at(Console_Manip::Msg_Types::Default));
						}
						Console_Manip::Draw_WChar(COORD{ 77, static_cast<int16_t>(msg_line) }, L'|', msg_colors.at(Console_Manip::Msg_Types::Default));
					}
					else {
						for (size_t i = 0; i < wstr.size(); i++) {
							int16_t x_pos = x_off + (int16_t)i;
							Console_Manip::Draw_WChar(COORD{ x_pos, static_cast<int16_t>(msg_line) }, wstr.at(i), msg_colors.at(Console_Manip::Msg_Types::Default));
						}
						Console_Manip::Draw_WChar(COORD{ 77, static_cast<int16_t>(msg_line) }, L'|', msg_colors.at(Console_Manip::Msg_Types::Default));
					}

					for (size_t i = 0; i < 7; i++) {
						int16_t x_pos = x_off + (int16_t)i + 10;

						WriteConsoleOutputAttribute(console_output, msg_colors.at(msg_type).Return_Color(), 1, { x_pos, static_cast<int16_t>(msg_line) }, &bytes_written);
					}

					msg_line = msg_line + 1;
					if (msg_line > 37) {
						msg_line = 2;
						Clear_Console();
					}
				}
				void Console_Manip::Clear_Console() {
					int16_t x_off = 2;

					for (int16_t i = 0; i < 76; i++) {
						for (int16_t j = 0; j < 36; j++) {
							Console_Manip::Draw_WChar(COORD{ static_cast<int16_t>(i + x_off),  static_cast<int16_t>(j + 2) }, L' ', msg_colors.at(Console_Manip::Msg_Types::Clear));
						}
					}
				}
				void Console_Manip::Draw_WChar(COORD position, const wchar_t character, Console_Color color) {
					DWORD bytes_written = 0;
					WriteConsoleOutputCharacterW(console_output, &character, 1, position, &bytes_written);
					WriteConsoleOutputAttribute(console_output, color.Return_Color(), 1, position, &bytes_written);

					SetConsoleActiveScreenBuffer(console_output);
				}
				void Console_Manip::Draw_WChar(COORD position, const wchar_t* character, Console_Color* color) {
					DWORD bytes_written = 0;
					WriteConsoleOutputCharacterW(console_output, character, 1, position, &bytes_written);
					WriteConsoleOutputAttribute(console_output, color->Return_Color(), 1, position, &bytes_written);

					SetConsoleActiveScreenBuffer(console_output);
				}
				void Console_Manip::Draw_Line(COORD start, COORD end, const wchar_t character, Console_Color color) {
					if (abs(end.Y - start.Y) < abs(end.X - start.X)) {
						if (start.X > end.X) {
							Draw_Line_Low(end, start, &character, &color);
						}
						else {
							Draw_Line_Low(start, end, &character, &color);
						}
					}
					else {
						if (start.Y > end.Y) {
							Draw_Line_High(end, start, &character, &color);
						}
						else {
							Draw_Line_High(start, end, &character, &color);
						}
					}


				}
				void Console_Manip::Draw_Line_Low(COORD start, COORD end, const wchar_t* character, Console_Color* color) {
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
						Draw_WChar({ x,y }, character, color);
						if (d > 0) {
							y = y + yi;
							d = d + (2 * (dy - dx));
						}
						else {
							d = d + 2 * dy;
						}
					}
				}
				void Console_Manip::Draw_Line_High(COORD start, COORD end, const wchar_t* character, Console_Color* color) {
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
						Draw_WChar({ x,y }, character, color);
						if (d > 0) {
							x = x + xi;
							d = d + (2 * (dx - dy));
						}
						else {
							d = d + 2 * dx;
						}
					}
				}
				void Console_Manip::Draw_Rectangle_Vertical(COORD top_left, COORD size, const wchar_t character, Console_Color color) {
				   	/*
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
					auto v_thread_1 = std::async(std::launch::async, [](int16_t total_width, COORD* top_left, COORD* size, const wchar_t* character, Console_Color* color) {
						for (int16_t x = top_left->X; x < top_left->X + total_width; x++) {
							Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, *character, *color);
						}
					}, v_total_width, &top_left, &size, &character, &color);
					uint16_t v_last_width = v_total_width;
					v_total_width = v_total_width + v_t2_width;
					auto v_thread_2 = std::async(std::launch::async, [](int16_t total_width, int16_t last_width, COORD* top_left, COORD* size, const wchar_t* character, Console_Color* color) {
						for (int16_t x = top_left->X + last_width; x < top_left->X + total_width; x++) {
							Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, *character, *color);
						}
					}, v_total_width, v_last_width, & top_left, & size, & character, & color);
					// t3 and t4 can be 0
					if (v_t3_width != 0) {
						v_last_width = v_total_width;
						v_total_width = v_total_width + v_t3_width;
						auto v_thread_3 = std::async(std::launch::async, [](int16_t total_width, int16_t last_width, COORD* top_left, COORD* size, const wchar_t* character, Console_Color* color) {
							for (int16_t x = top_left->X + last_width; x < top_left->X + total_width; x++) {
								Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, *character, *color);
							}
						}, v_total_width, v_last_width, &top_left, &size, &character, &color);
					}
					if (v_t4_width != 0) {
						v_last_width = v_total_width;
						v_total_width = v_total_width + v_t4_width;
						auto v_thread_4 = std::async(std::launch::async, [](int16_t total_width, int16_t last_width, COORD* top_left, COORD* size, const wchar_t* character, Console_Color* color) {
							for (int16_t x = top_left->X + last_width; x < top_left->X + total_width; x++) {
								Draw_Line({ x, top_left->Y }, { x, (int16_t)(top_left->Y + size->Y) }, *character, *color);
							}
						}, v_total_width, v_last_width, &top_left, &size, &character, &color);
					}*/ 
					for (int16_t x = top_left.X; x < top_left.X + size.X; x++) {
						Draw_Line({ x, top_left.Y }, { x, (int16_t)(top_left.Y + size.Y) }, character, color);
					}
				}
				void Console_Manip::Draw_Rectangle_Horizontal(COORD top_left, COORD size, const wchar_t character, Console_Color color) {
					for (int16_t y = top_left.Y; y < top_left.Y + size.Y; y++) {
						Draw_Line({ top_left.X, y }, { (int16_t)(top_left.X + size.X), y }, character, color);
					}
				}
				std::map<Console_Manip::Msg_Types, Console_Color>* Console_Manip::Msg_Colors() {
					return &msg_colors;
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