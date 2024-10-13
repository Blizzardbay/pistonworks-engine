// BSD 3 - Clause License
//
// Copyright(c) 2021-2024, Darrian Corkadel
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
#ifndef H_CONSOLE_MANIP
#define H_CONSOLE_MANIP
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#undef APIENTRY
#include <Windows.h>
#include <map>
#include <future>
#include <new>
#pragma comment(lib,"user32.lib") 
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\constant.h"
#include "common\error_log.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		CN_NAMESPACE_SRT
			class Console_Error {
			// Friends
			// Default Class Structures
			public:
			private:
			// Public Functions/Macros
			public:
				/* Error List: PW_WIN_FUNCTION_ERROR */
				_NODISCARD static std::wstring Windows_Last_Error() noexcept;
				/* Error List: PW_WIN_FUNCTION_ERROR */
				static void Handle_Windows_Error(const std::wstring& p_function, const std::wstring& p_caller) noexcept;
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
			};
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
			enum class Msg_Types {
				E_CLEAR,
				E_DEFAULT,
				E_ENGINE,
				E_GAME,
				E_INFO,
				E_ERROR,
				E_SUCCESS,
				E_CONSOLE_OUT
			};
			class Console_Color {
			// Friends
			// Default Class Structures
			public:
				/* Error List: NONE */
				_NODISCARD Console_Color() noexcept;
				/* Error List: NONE */
				_NODISCARD Console_Color(const Win_Text_Color& p_text_color, const Win_Backaround_Color& p_backaround_color) noexcept;
			private:
			// Public Functions/Macros
			public:
				/* Error List: NONE */
				_NODISCARD const uint16_t& Return_Color() const noexcept;
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
				uint16_t m_color_attribute;
			};
			class Console_Msg {
			// Friends
			// Default Class Structures
			public:
				Console_Msg() = delete;
				Console_Msg(const Console_Msg&) = delete;
				Console_Msg& operator= (const Console_Msg&) = delete;
				/* Error List: NONE */
				Console_Msg(const std::wstring_view& p_from, const std::wstring_view& p_msg, const pw::co::cn::Msg_Types& p_msg_type);
				/* Error List: NONE */
				~Console_Msg();
			private:
			// Public Functions/Macros
			public:
				/* Error List: NONE */
				const std::wstring_view& From() const noexcept;
				/* Error List: NONE */
				const std::wstring_view& Msg() const noexcept;
				/* Error List: NONE */
				const pw::co::cn::Msg_Types& Type() const noexcept;
			// Public Variables
			public:
				const pw::co::cn::Msg_Types m_msg_type;
				const std::wstring_view m_from;
				const std::wstring_view m_msg;
			// Private Functions/Macros
			private:
			// Private Variables
			private:
			};
			class Console_Manip {
			// Friends
				friend class pw::co::Control;
			// Default Class Structures
			public:
			private:
				// Public Functions/Macros
			public:
				/* Error List: PW_WIN_FUNCTION_ERROR */
				static void Resize(const uint32_t p_size_x, const uint32_t p_size_y);
				/* Error List: PW_FUNCTION_ERROR */
				static void Print_Info(const std::wstring& p_from, const std::wstring& p_msg, const uint16_t& p_line);
				/* Error List: PW_FUNCTION_ERROR, PW_WIN_FUNCTION_ERROR */
				static void Print_Console(const std::wstring& p_from, const std::wstring& p_msg, const pw::co::cn::Msg_Types& p_msg_type, const bool p_block_msg);
				/* Error List: PW_FUNCTION_ERROR, PW_WIN_FUNCTION_ERROR */
				static void Print_Console(const Console_Msg& p_msg, const bool p_block_msg);
				/* Error List: PW_FUNCTION_ERROR */
				static void Clear_Console();
				/* Error List: PW_INVAILD_PARAMETER_W, PW_WIN_FUNCTION_ERROR */
				static void Draw_WChar(const COORD& p_position, const wchar_t& character, const Console_Color& color);
				/* Error List: PW_INVAILD_PARAMETER_W, PW_FUNCTION_ERROR, PW_WIN_FUNCTION_ERROR */
				static void Draw_WChar_Block(const COORD& p_position, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color);
				/* Error List: PW_INVAILD_PARAMETER_W, PW_WIN_FUNCTION_ERROR */
				static void Draw_Text_Line(const COORD& p_position, const std::wstring& p_block, const Console_Color& p_color);
				/* Error List: PW_INVAILD_PARAMETER_W, PW_FUNCTION_ERROR */
				static void Draw_Line(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color);
				/* Error List: PW_INVAILD_PARAMETER_W, PW_FUNCTION_ERROR */
				static void Draw_Rectangle_Vertical(const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color);
				/* Error List: PW_FUNCTION_ERROR */
				static void Draw_Rectangle_Horizontal(const COORD& p_top_left, const COORD& p_size, const wchar_t& p_character, const Console_Color& p_color);

				#define CLEAR_MSG pw::co::cn::Msg_Types::E_CLEAR
				#define DEFAULT_MSG pw::co::cn::Msg_Types::E_DEFAULT
				#define ENGINE_MSG pw::co::cn::Msg_Types::E_ENGINE
				#define ERROR_MSG pw::co::cn::Msg_Types::E_ERROR
				#define GAME_MSG pw::co::cn::Msg_Types::E_GAME
				#define INFO_MSG pw::co::cn::Msg_Types::E_INFO
				#define SUCCESS_MSG pw::co::cn::Msg_Types::E_SUCCESS
				#define COUT_MSG pw::co::cn::Msg_Types::E_CONSOLE_OUT


				#ifdef PW_DEBUG_MODE
					#define PRINT_MSG(p_from, p_msg, p_msg_type) {										\
						pw::co::cn::Console_Manip::Print_Console({p_from, p_msg, p_msg_type}, false);	\
					}
					#define PRINT_BLOCK(p_from, p_msg, p_msg_type) {																					\
						pw::co::cn::Console_Manip::Print_Console(L"", L"---------------------------------------------------------", COUT_MSG, true);	\
						pw::co::cn::Console_Manip::Print_Console(std::wstring(p_from), std::wstring(p_msg), p_msg_type, false);							\
						pw::co::cn::Console_Manip::Print_Console(L"", L"---------------------------------------------------------", COUT_MSG, true);	\
					}																							
					#define PRINT_INFO(p_from, p_msg, p_line) {														\
						assert(p_line >= 0 && p_line < 36);															\
						pw::co::cn::Console_Manip::Print_Info(std::wstring(p_from), std::wstring(p_msg), p_line);	\
					}
				#else
					#define PRINT_MSG(p_from, p_msg, p_msg_type) 
					#define PRINT_BLOCK(p_from, p_msg, p_msg_type)
					#define PRINT_INFO(p_from, p_msg, p_line)
				#endif // PW_DEBUG_MODE
				/* Error List: NONE */
				static const std::map<pw::co::cn::Msg_Types, Console_Color>& Msg_Colors();
				// Public Variables
			public:
				// Private Functions/Macros
			private:
				/* Error List: PW_WIN_FUNCTION_ERROR, PW_FUNCTION_ERROR */
				static void Set_Up_Console();
				/* Error List: PW_FUNCTION_ERROR */
				static void Initialize();
				/* Error List: PW_FUNCTION_ERROR, PW_WIN_FUNCTION_ERROR */
				static void Draw_Screen();
				/* Error List: NONE */
				static void Release();

				/* Error List: PW_FUNCTION_ERROR */
				static void Draw_Line_Low(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color);
				/* Error List: PW_FUNCTION_ERROR */
				static void Draw_Line_High(const COORD& p_start, const COORD& p_end, const wchar_t& p_character, const Console_Color& p_color);
				// Private Variables
			private:
				static uint16_t m_console_width;
				static uint16_t m_console_height;

				static wchar_t* m_console_screen_buffer;
				static HWND m_window_handle;
				static HANDLE m_screen_handle;
				static HANDLE m_console_output;

				static COORD m_write_coord;
				static uint16_t m_msg_line;

				static std::map<pw::co::cn::Msg_Types, Console_Color>* m_msg_colors;
			};
		CN_NAMESPACE_END
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_CONSOLE_MANIP