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
#ifndef H_ENGINE_ERROR
#define H_ENGINE_ERROR
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <codecvt>
#include <locale.h>
//////////////////////////////////
// Project Headers
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // PW_GLEW_H 
#include <GLFW\glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype\fterrors.h>
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
#include "engine_common\engine_constant.h"
#include "engine_control\engine_console_manip.h"
// Exception to format to fix <Windows.h> bug
#ifndef PW_FI_H
#define PW_FI_H
#include "freeimage\FreeImage.h"
#endif // PW_FI_H 
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
	ER_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// Class Name: pw::er::Engine_Error
		// //////////////////////////////////////////////////
		// Purpose:
		//  For handling error
		//  within parts of the engine.
		// //////////////////////////////////////////////////
		class PW_COMMON_API Engine_Error {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_Print_Error
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints a custom error msg.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) const wchar_t* sender;
			// Purpose: 
			//  The function or thing giving the error.
			// (2) const wchar_t* msg;
			// Purpose: 
			//  The warning or description sent by the function.
			// (3) const int32_t line;
			// Purpose: 
			//  The line the msg came from.
			// (4) const wchar_t* file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_Print_Error(const wchar_t* sender, const wchar_t* msg, const int32_t line, const char* file) {
				#ifdef PW_DEBUG_MODE
					PW_Print_Error(sender, msg, line, cm::Engine_Constant::To_WString(file).c_str());
				#endif // PW_DEBUG_MODE
			}
			static ERROR_HANDLE void PW_Print_Error(const wchar_t* sender, const wchar_t* msg, const int32_t line, const wchar_t* file) {
				#ifdef PW_DEBUG_MODE
					std::wstring v_line{ std::to_wstring(line) };
				
					PRINT_MSG(sender, msg, ERROR_MSG);
					PRINT_MSG(sender, v_line.c_str(), ERROR_MSG);
					PRINT_MSG(sender, file, ERROR_MSG);

				#endif // PW_DEBUG_MODE
			}
			static ERROR_HANDLE void PW_Print_Error(const wchar_t* sender, const wchar_t* msg, const int32_t line, const char* file, bool print_success) {
				#ifdef PW_DEBUG_MODE
					PW_Print_Error(sender, msg, line, cm::Engine_Constant::To_WString(file).c_str(), print_success);
				#endif // PW_DEBUG_MODE
			}
			static ERROR_HANDLE void PW_Print_Error(const wchar_t* sender, const wchar_t* msg, const int32_t line, const wchar_t* file, bool print_success) {
				#ifdef PW_DEBUG_MODE
					if (print_success == true) {
						PRINT_MSG(sender, msg, SUCCESS_MSG);
					}
					else {
						std::wstring v_line{ std::to_wstring(line) };

						PRINT_MSG(sender, msg, ERROR_MSG);
						PRINT_MSG(sender, v_line.c_str(), ERROR_MSG);
						PRINT_MSG(sender, file, ERROR_MSG);
					}
				#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GLFW_Callback_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints error msg's sent to the function from
			//  glfw.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) int32_t result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const wchar_t* description;
			// Purpose: 
			//  The description of the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GLFW_Callback_Handle(int32_t result, const char* description) {
				if (result != 65537) {
					PW_Print_Error(L"GLFW", pw::cm::Engine_Constant::To_WString(description).c_str(), PW_LINE_, PW_FILE_);
				}
				return;
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GLFW_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Takes a result and finds if it is an error or not
			//  .
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const int32_t result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t line;
			// Purpose: 
			//  The line the error was on.
			// (3) const wchar_t* file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GLFW_Handle(const int32_t result, const int32_t line, const char* file) {
				if (result != GLFW_NO_ERROR && result != GLFW_TRUE) {
					PW_Print_Error(L"GLFW", L"Function Error", line, file);
					return;
				}
			#ifdef PW_DEBUG_MODE
				else {
					PW_Print_Error(L"GLFW", L"Function Success ( Completed )", line, file, true);
					return;
				}
			#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GL_VOID_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Finds an error from a opengl function with a void
			//  return.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) const GLenum result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t line;
			// Purpose: 
			//  The line the error was on.
			// (3) const wchar_t* file;
			// Purpose: 
			//  The file the error happened in.
			// (4) bool handle_type;
			// Purpose:
			//  Should the error be printed or not.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GL_VOID_Handle(const GLenum result, const int32_t line, const char* file, bool handle_type) {
				if (result != 0 && result != 1282) {
					PW_Print_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(result)).c_str(), line, file);
					return;
				}
			#ifdef PW_DEBUG_MODE
				else {
					if (handle_type == true) {
						PW_Print_Error(L"GL", L"Function Success ( Completed )", line, file, true);
						return;
					}
				}
			#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_FI_Callback_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints error msg's sent to the function from FI.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) FREE_IMAGE_FORMAT result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const wchar_t* description;
			// Purpose: 
			//  The description of the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_FI_Callback_Handle(FREE_IMAGE_FORMAT result, const char* description) {
				if (result != FIF_UNKNOWN) {
					std::string str = std::string(description);
					str.insert(0, "Unknown Image Format ");

					PW_Print_Error(L"FI", cm::Engine_Constant::To_WString(str.c_str()).c_str(), PW_LINE_, PW_FILE_);
					return;
				}
				else {
					std::string str = std::string(description);
					str.insert(0, "Known Image Format ");

					PW_Print_Error(L"FI", cm::Engine_Constant::To_WString(str.c_str()).c_str(), PW_LINE_, PW_FILE_);
					return;
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GL_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Interprets a result form a opengl function.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// 
			// (1) const GLenum result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t line;
			// Purpose: 
			//  The line the error was on.
			// (3) const wchar_t* file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GL_Handle(const GLenum result, const int32_t line, const char* file) {
				if (result <= 0) {
					PW_Print_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(result)).c_str(), line, file);
					return;
				}
			#ifdef PW_DEBUG_MODE
				else {
					PW_Print_Error(L"GL", L"Function Success ( Completed )", line, file, true);
					return;

				}
			#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_FT_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Handles possible font loading issues.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const FT_Error result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t line;
			// Purpose: 
			//  The line the error was on.
			// (3) const wchar_t* file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_FT_Handle(const FT_Error result, const int32_t line, const char* file) {
				if (result != FT_Err_Ok) {
					PW_Print_Error(L"FT", cm::Engine_Constant::To_WString(FT_Error_String(result)).c_str(), line, file);
					return;
				}
			}
			#define PW_GLFW_VOID_CALL(funct)			{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__; const char* v_char_str = __FILE__; delete[] pw::er::Engine_Error::PW_FILE_; int32_t v_char_size = OFF(std::strlen(v_char_str)); size_t converted_chars = 0; wchar_t* file_string = new wchar_t[v_char_size]; mbstowcs_s(&converted_chars, file_string, v_char_size, v_char_str, _TRUNCATE); pw::er::Engine_Error::PW_FILE_ = file_string; }
			#define PW_GLFW_CALL(funct)					{ pw::er::Engine_Error::PW_GLFW_Handle(funct, __LINE__, __FILE__); }
			#define PW_GL_VOID_CALL(funct, handle_type) { funct; pw::er::Engine_Error::PW_GL_VOID_Handle(glGetError(), __LINE__, __FILE__,handle_type); }
			#define PW_FI_VOID_CALL(funct)				{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__;	const char* v_char_str = __FILE__; delete[] pw::er::Engine_Error::PW_FILE_; int32_t v_char_size = OFF(std::strlen(v_char_str)); size_t converted_chars = 0; wchar_t* file_string = new wchar_t[v_char_size]; mbstowcs_s(&converted_chars, file_string, v_char_size, v_char_str, _TRUNCATE); pw::er::Engine_Error::PW_FILE_ = file_string; }
			#define PW_FI_VOID_CALL_C(funct)			{ pw::er::Engine_Error::PW_LINE_ = __LINE__; const char* v_char_str = __FILE__; delete[] pw::er::Engine_Error::PW_FILE_; int32_t v_char_size = OFF(std::strlen(v_char_str)); size_t converted_chars = 0; wchar_t* file_string = new wchar_t[v_char_size]; mbstowcs_s(&converted_chars, file_string, v_char_size, v_char_str, _TRUNCATE); pw::er::Engine_Error::PW_FILE_ = file_string; funct }
			#define PW_GL_CALL(funct)					{ pw::er::Engine_Error::PW_GL_Handle(funct, __LINE__, __FILE__); }
			#define PW_FT_CALL(funct)					{ pw::er::Engine_Error::PW_FT_Handle(funct, __LINE__, __FILE__);}
			#define PW_PRINT_ERROR(sender, msg)			{ pw::er::Engine_Error::PW_Print_Error(sender, msg, __LINE__, __FILE__); }
		// Public Variables
		public:
			static int32_t PW_LINE_;
			static const wchar_t* PW_FILE_;
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	ER_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_ERROR