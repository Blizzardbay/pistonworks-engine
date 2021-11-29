// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_ENGINE_CONSOLE_MANIP
#define H_ENGINE_CONSOLE_MANIP
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <Windows.h>
#include <map>
#include <future>
#include <exception>
#include <new>
//////////////////////////////////
// Project Headers
#include "engine_common\engine_constant.h"
#include "engine_common\engine_error_log.h"
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Macros
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		CN_NAMESPACE_SRT
		//////////////////////////////////
			// //////////////////////////////////////////////////
			// PW_CONSOLE_API Class: pw::co::cn::Console_Error
			// //////////////////////////////////////////////////
			// Purpose:
			//  To hold a windows get error function.
			// //////////////////////////////////////////////////
			class PW_CONSOLE_API Console_Error : std::exception {
			// Default Class Structures
			public:
			private:
			// Public Functions/Macros
			public:
				// //////////////////////////////////////////////////
				// CORE Function: Console_Error:Windows_Last_Error 
				// //////////////////////////////////////////////////
				// Purpose:
				//  Returns the last windows error detected by the 
				//  system. If it does not get an error it returns an
				//  empty std::wstring(). If it gets a function error
				//  it will print so.  If the format function gets an
				//  error, then the function will return a error msg
				//  for the format msg and give any other possible
				//  error information about the original error.
				// //////////////////////////////////////////////////
				// Parameters: NONE
				// //////////////////////////////////////////////////
				static CORE std::wstring Windows_Last_Error() noexcept;
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
			};
			// //////////////////////////////////////////////////
			// PW_CONSOLE_API Enum: pw::co::cn::Win_Text_Color
			// //////////////////////////////////////////////////
			// Purpose:
			//  Windows consoles need very specific color number
			//  inputs. Using a enum structure makes this very
			//	easy to navigate.
			// //////////////////////////////////////////////////
			enum class Win_Text_Color {
				BLACK = 0,
				DARK_BLUE = FOREGROUND_BLUE,
				DARK_GREEN = FOREGROUND_GREEN,
				DARK_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
				DARK_RED = FOREGROUND_RED,
				DARK_PINK = FOREGROUND_RED | FOREGROUND_BLUE,
				DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
				WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
				GREY = 0 | FOREGROUND_INTENSITY,
				BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
				GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
				CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
				RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
				PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
				YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
				BRIGHT_WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
			};
			// //////////////////////////////////////////////////
			// PW_CONSOLE_API Enum: pw::co::cn::Win_Backaround_Color
			// //////////////////////////////////////////////////
			// Purpose:
			//  Like the console text color, the background text
			//  color also needs a specific color enum value in
			//  order for the text to be colored correctly.
			// //////////////////////////////////////////////////
			enum class Win_Backaround_Color {
				BLACK = 0,
				DARK_BLUE = BACKGROUND_BLUE,
				DARK_GREEN = BACKGROUND_GREEN,
				DARK_CYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
				DARK_RED = BACKGROUND_RED,
				DARK_PINK = BACKGROUND_RED | BACKGROUND_BLUE,
				DARK_YELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
				LIGHT_GREY = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN,
				GREY = 0 | BACKGROUND_INTENSITY,
				BLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
				GREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
				CYAN = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
				RED = BACKGROUND_RED | BACKGROUND_INTENSITY,
				PINK = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
				YELLOW = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
				BRIGHT_WHITE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY
			};
			// //////////////////////////////////////////////////
			// PW_CONSOLE_API Class: pw::co::cn::Console_Color
			// //////////////////////////////////////////////////
			// Purpose:
			//  A simple windows API color wrapper.
			// //////////////////////////////////////////////////
			struct PW_CONSOLE_API Console_Color {
			// Default Class Structures
			public:
				// //////////////////////////////////////////////////
				// CLASS_FUNCTION Function: pw::co::cn::Console_Color
				// //////////////////////////////////////////////////
				// Purpose:
				//  Initializes an empty console_color structure.
				// //////////////////////////////////////////////////
				// Parameters: NONE
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				CLASS_FUNCTION Console_Color();
				// //////////////////////////////////////////////////
				// CLASS_FUNCTION Function: pw::co::cn::Console_Color
				// //////////////////////////////////////////////////
				// Purpose:
				//  Initializes an empty console color structure.
				// //////////////////////////////////////////////////
				// Parameters: 2
				// (1) Win_Text_Color text_color;
				// Purpose:
				//  The color of the text.
				// (2)
				// Purpose:
				//  The color of the background.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				CLASS_FUNCTION Console_Color(Win_Text_Color text_color, Win_Backaround_Color backaround_color);
				// //////////////////////////////////////////////////
				// CLASS_FUNCTION Function: pw::co::cn::~Console_Color
				// //////////////////////////////////////////////////
				// Purpose:
				//  Deallocates memory of the color structure.
				// //////////////////////////////////////////////////
				// Parameters: NONE
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				CLASS_FUNCTION ~Console_Color();
			private:
			// Public Functions/Macros
			public:
				// Accessors
				USER_INTERACTION
				const ACCESSOR uint16_t& Return_Color() const;
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
				uint16_t m_color_creation;
			};
			// //////////////////////////////////////////////////
			// PW_CONSOLE_API Class: pw::co::cn::Console_Manip
			// //////////////////////////////////////////////////
			// Purpose:
			//  The control structure for the debug console.
			// //////////////////////////////////////////////////
			class PW_CONSOLE_API Console_Manip {
			// Default Class Structures
			public:
				// //////////////////////////////////////////////////
				// PW_CONSOLE_API Enum: pw::co::cn::Console_Manip::Msg_Types
				// //////////////////////////////////////////////////
				// Purpose:
				//  The different types of msg's that the console can
				//  be sent.
				// //////////////////////////////////////////////////
				enum class PW_CONSOLE_API Msg_Types {
					E_CLEAR,
					E_DEFAULT,
					E_ENGINE,
					E_GAME,
					E_INFO,
					E_ERROR,
					E_SUCCESS,
					E_CONSOLE_OUT
				};
			private:
				// Public Functions/Macros
			public:
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Set_Up_Console
				// //////////////////////////////////////////////////
				// Purpose:
				//  Initializes the console window for use. Note that
				//  in release mode the console will not appear.
				// //////////////////////////////////////////////////
				// Parameters: NONE
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Set_Up_Console();
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Resize
				// //////////////////////////////////////////////////
				// Purpose:
				//  Resizes the console window on a character size
				//  basis.
				// //////////////////////////////////////////////////
				// Parameters: 2
				// (1) uint32_t&& size_x;
				// Purpose:
				//  The size in characters the x-axis will extend.
				//  Direction: Right
				// (2) uint32_t&& size_y;
				// Purpose:
				//  The size in characters the y-axis will extend.
				//  Direction: Down
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Resize(uint32_t&& size_x, uint32_t&& size_y);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_Screen
				// //////////////////////////////////////////////////
				// Purpose:
				//  Draws a default built in screen template for the
				//  console window to give information from.
				// //////////////////////////////////////////////////
				// Parameters: NONE
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Draw_Screen();
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Print_Console
				// //////////////////////////////////////////////////
				// Purpose:
				//  Prints the msg to the console along with time,
				//  sender and msg type information. 
				// //////////////////////////////////////////////////
				// Parameters: 3
				// (1) wchar_t* from;
				// Purpose:
				//  The function or class sending the msg to the
				//  console.
				// (2) wchar_t* msg;
				// Purpose:
				//  The msg being printed to the console.
				// (3) uint16_t&& line;
				// Purpose:
				//  The line to print the data on.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Print_Info(std::wstring&& from, std::wstring&& msg, uint16_t&& line);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Print_Console
				// //////////////////////////////////////////////////
				// Purpose:
				//  Prints the msg to the console along with time,
				//  sender and msg type information. 
				// //////////////////////////////////////////////////
				// Parameters: 4
				// (1) wchar_t* from;
				// Purpose:
				//  The function or class sending the msg to the
				//  console.
				// (2) wchar_t* msg;
				// Purpose:
				//  The msg being printed to the console.
				// (3) Msg_Types&& msg_type;
				// Purpose:
				//  The type of msg that is being printed.
				// (4) bool&& block_msg;
				// Purpose:
				//  Is this msg a block or not.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Print_Console(std::wstring&& from, std::wstring&& msg, Msg_Types&& msg_type, bool&& block_msg);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Clear_Console
				// //////////////////////////////////////////////////
				// Purpose:
				//  Clears the text portion of the console to black.
				// //////////////////////////////////////////////////
				// Parameters: NONE
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Clear_Console();
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_WChar
				// //////////////////////////////////////////////////
				// Purpose:
				//  Prints the character to the console screen. 
				// //////////////////////////////////////////////////
				// Parameters: 3
				// (1) COORD&& position;
				// Purpose:
				//  The position of the character to be printed to.
				// (2) const wchar_t&& character;
				// Purpose:
				//  The character being printed. Only one will be
				//  printed.
				// (3) Console_Color&& color;
				// Purpose:
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Draw_WChar(COORD&& position, const wchar_t&& character, Console_Color&& color);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_Line
				// //////////////////////////////////////////////////
				// Purpose:
				//  Draws a line of colored characters between two 
				//  points. 
				// //////////////////////////////////////////////////
				// Parameters: 4
				// (1) COORD&& start;
				// Purpose:
				//  The position of the first point.
				// (2) COORD&& end;
				// Purpose:
				//  The position of the end point.
				// (3) const wchar_t&& character;
				// Purpose:
				//  The character being printed. 
				// (4) Console_Color&& color;
				// Purpose:
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Draw_Line(COORD&& start, COORD&& end, wchar_t&& character, Console_Color&& color);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_Rectangle_Vertical
				// //////////////////////////////////////////////////
				// Purpose:
				//  Draws a rectangle from its top left position. It
				//  draws the rectangle in vertical lines.
				// //////////////////////////////////////////////////
				// Parameters: 4
				// (1) COORD&& top_left;
				// Purpose:
				//  The position of the top left of the rectangle.
				// (2) COORD&& size;
				// Purpose:
				//  The size of the rectangle.
				// (3) const wchar_t&& character;
				// Purpose:
				//  The character being printed. 
				// (4) Console_Color&& color;
				// Purpose:
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Draw_Rectangle_Vertical(COORD&& top_left, COORD&& size, wchar_t&& character, Console_Color&& color);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_Rectangle_Horizontal
				// //////////////////////////////////////////////////
				// Purpose:
				//  Draws a rectangle from its top left position. It
				//  draws the rectangle in horizontal lines.
				// //////////////////////////////////////////////////
				// Parameters: 4
				// (1) COORD&& top_left;
				// Purpose:
				//  The position of the top left of the rectangle.
				// (2) COORD&& size;
				// Purpose:
				//  The size of the rectangle.
				// (3) const wchar_t&& character;
				// Purpose:
				//  The character being printed. 
				// (4) Console_Color&& color;
				// Purpose:
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Draw_Rectangle_Horizontal(COORD&& top_left, COORD&& size, wchar_t&& character, Console_Color&& color);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Delete_Console
				// //////////////////////////////////////////////////
				// Purpose:
				//  When the main program is done, delete the console
				//  .
				// //////////////////////////////////////////////////
				// Parameters: NONE
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE void Delete_Console();

				#define CLEAR_MSG pw::co::cn::Console_Manip::Msg_Types::E_CLEAR
				#define DEFAULT_MSG pw::co::cn::Console_Manip::Msg_Types::E_DEFAULT
				#define ENGINE_MSG pw::co::cn::Console_Manip::Msg_Types::E_ENGINE
				#define ERROR_MSG pw::co::cn::Console_Manip::Msg_Types::E_ERROR
				#define GAME_MSG pw::co::cn::Console_Manip::Msg_Types::E_GAME
				#define INFO_MSG pw::co::cn::Console_Manip::Msg_Types::E_INFO
				#define SUCCESS_MSG pw::co::cn::Console_Manip::Msg_Types::E_SUCCESS
				#define COUT_MSG pw::co::cn::Console_Manip::Msg_Types::E_CONSOLE_OUT


				#define PRINT_MSG(from, msg, msg_type) { pw::co::cn::Console_Manip::Print_Console(std::move(std::wstring(from)), std::move(std::wstring(msg)), std::move(msg_type), false); }
				#define PRINT_BLOCK(from, msg, msg_type) {  pw::co::cn::Console_Manip::Print_Console(L"", L"---------------------------------------------------------", COUT_MSG, true);  pw::co::cn::Console_Manip::Print_Console(std::move(std::wstring(from)), std::move(std::wstring(msg)), std::move(msg_type), false);  pw::co::cn::Console_Manip::Print_Console(L"", L"---------------------------------------------------------", COUT_MSG, true); }

				#define PRINT_INFO(from, msg, line) { pw::co::cn::Console_Manip::Print_Info(std::move(std::wstring(from)), std::move(std::wstring(msg)), std::move(line)); }
				// Accessors																																																																			 
				USER_INTERACTION
				static const ACCESSOR std::map<Msg_Types, Console_Color>& Msg_Colors();
				// Public Variables
			public:
				// Private Functions/Macros
			private:
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_Line_Low
				// //////////////////////////////////////////////////
				// Purpose:
				//  Draws a line of colored characters between two 
				//  points. Draws it for "low" values.
				// //////////////////////////////////////////////////
				// Parameters: 4
				// (1) COORD&& start;
				// Purpose:
				//  The position of the first point.
				// (2) COORD&& end;
				// Purpose:
				//  The position of the end point.
				// (3) const wchar_t&& character;
				// Purpose:
				//  The character being printed. Draws only the first
				//  character. 
				// (4) Console_Color&& color;
				// Purpose:
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE ALGORITHM void Draw_Line_Low(COORD&& start, COORD&& end, wchar_t&& character, Console_Color&& color);
				// //////////////////////////////////////////////////
				// CONSOLE Function: Console_Manip::Draw_Line_High
				// //////////////////////////////////////////////////
				// Purpose:
				//  Draws a line of colored characters between two 
				//  points. Draws it for "high" values.
				// //////////////////////////////////////////////////
				// Parameters: 4
				// (1) COORD&& start;
				// Purpose:
				//  The position of the first point.
				// (2) COORD&& end;
				// Purpose:
				//  The position of the end point.
				// (3) const wchar_t&& character;
				// Purpose:
				//  The character being printed. Draws only the first
				//  character. 
				// (4) Console_Color&& color;
				// Purpose:
				//  The color of the character being printed.
				// //////////////////////////////////////////////////
				NO_USER_INTERACTION
				static CONSOLE ALGORITHM void Draw_Line_High(COORD&& start, COORD&& end, wchar_t&& character, Console_Color&& color);
				// Private Variables
			private:
				static uint16_t console_width;
				static uint16_t console_height;

				static wchar_t* console_screen_buffer;
				static HWND window_handle;
				static HANDLE screen_handle;
				static HANDLE console_output;

				static COORD write_coord;
				static uint16_t msg_line;

				static std::map<Msg_Types, Console_Color> msg_colors;
			};
			// Functions
			// Macros / Definitions
		//////////////////////////////////
		CN_NAMESPACE_END
		//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONSOLE_MANIP