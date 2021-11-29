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
#include "engine_common\engine_error_log.h"
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
		class PW_ERROR_API Engine_Error {
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
			// Parameters: 1
			// (1) const pw::er::Warning_Error& p_error;
			// Purpose: 
			//  The error to be printed.
			// //////////////////////////////////////////////////
			static ERROR_HANDLE void PW_Print_Error(const pw::er::Warning_Error& p_error) {
				#ifdef PW_DEBUG_MODE
					if (pw::er::Error_Log::Dump_Log(p_error) == false) {
						PRINT_MSG(p_error.From(), L"Failed to dump error", ERROR_MSG);
					}
					std::wstring v_line{ std::to_wstring(p_error.Line()) };
					v_line.insert(0, L"Line: ");

					std::wstring v_file{ p_error.File() };
					size_t v_pos = v_file.find(L"engine_common", 0);
					if (v_pos != std::wstring::npos) {
						v_file.erase(0, v_pos);
					}
					else {
						v_pos = v_file.find(L"engine_control", 0);
						if (v_pos != std::wstring::npos) {
							v_file.erase(0, v_pos);
						}
						else {
							v_pos = v_file.find(L"engine_structures", 0);
							if (v_pos != std::wstring::npos) {
								v_file.erase(0, v_pos);
							}
						}
					}

					PRINT_MSG(p_error.From(), p_error.Msg(), ERROR_MSG);
					PRINT_MSG(p_error.From(), v_line, ERROR_MSG);
					PRINT_MSG(p_error.From(), v_file, ERROR_MSG);
					PRINT_MSG(p_error.From(), p_error.Function(), ERROR_MSG);
				#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_Print_Error
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints a custom error msg.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const pw::er::Severe_Error& p_error;
			// Purpose: 
			//  The error to be printed.
			// //////////////////////////////////////////////////
			static ERROR_HANDLE void PW_Print_Error(const pw::er::Severe_Error& p_error) {
				#ifdef PW_DEBUG_MODE
					if (pw::er::Error_Log::Dump_Log(p_error) == false) {
						PRINT_MSG(p_error.From(), L"Failed to dump error", ERROR_MSG);
					}
					std::wstring v_line{ std::to_wstring(p_error.Line()) };
					v_line.insert(0, L"Line: ");

					std::wstring v_file{ p_error.File() };
					size_t v_pos = v_file.find(L"engine_common", 0);
					if (v_pos != std::wstring::npos) {
						v_file.erase(0, v_pos);
					}
					else {
						v_pos = v_file.find(L"engine_control", 0);
						if (v_pos != std::wstring::npos) {
							v_file.erase(0, v_pos);
						}
						else {
							v_pos = v_file.find(L"engine_structures", 0);
							if (v_pos != std::wstring::npos) {
								v_file.erase(0, v_pos);
							}
						}
					}

					PRINT_MSG(p_error.From(), p_error.Msg(), ERROR_MSG);
					PRINT_MSG(p_error.From(), v_line, ERROR_MSG);
					PRINT_MSG(p_error.From(), v_file, ERROR_MSG);
					PRINT_MSG(p_error.From(), p_error.Function(), ERROR_MSG);
				#endif // PW_DEBUG_MODE
			}
			static ERROR_HANDLE void Evaluate_Error(std::any p_error) {
				if (p_error.type() == typeid(pw::er::Warning_Error)) {
					PW_Print_Error(std::any_cast<pw::er::Warning_Error>(p_error));
				}
				if (p_error.type() == typeid(pw::er::Severe_Error)) {
					PW_Print_Error(std::any_cast<pw::er::Severe_Error>(p_error));
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GLFW_Callback_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints error msg's sent to the function from
			//  glfw.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) int32_t&& result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) std::wstring description;
			// Purpose: 
			//  The description of the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GLFW_Callback_Handle(int32_t result, const char* description) {
				if (result != 65537) {
					try {
						PW_Print_Error(er::Severe_Error(L"GLFW", TO_WSTRING(description).c_str(), std::move(PW_LINE_), PW_FILE_.c_str(), L"PW_GLFW_Callback_Handle"));
						throw er::Severe_Error(L"GLFW", TO_WSTRING(description).c_str(), std::move(PW_LINE_), PW_FILE_.c_str(), L"PW_GLFW_Callback_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GLFW_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Takes a result and finds if it is an error or not
			//  .
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const int32_t&& result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t&& line;
			// Purpose: 
			//  The line the error was on.
			// (3) std::wstring file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GLFW_Handle(const int32_t&& result, int32_t&& line, std::wstring&& file) {
				if (result != GLFW_NO_ERROR && result != GLFW_TRUE) {
					try {
						PW_Print_Error(er::Severe_Error(L"GLFW", L"Function Error", std::move(line), std::move(file), L"PW_GLFW_Handle"));
						throw er::Severe_Error(L"GLFW", L"Function Error", std::move(line), std::move(file), L"PW_GLFW_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			#ifdef PW_DEBUG_MODE
				else {
					PRINT_MSG(L"GLFW", L"Function Success ( Completed )", SUCCESS_MSG);
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
			// (1) const GLenum&& result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) int32_t&& line;
			// Purpose: 
			//  The line the error was on.
			// (3) std::wstring file;
			// Purpose: 
			//  The file the error happened in.
			// (4) bool&& handle_type;
			// Purpose:
			//  Should the error be printed or not.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GL_VOID_Handle(const GLenum&& result, int32_t&& line, std::wstring&& file, bool&& handle_type) {
				if (result != 0 && result != 1282) {
					try {
						PW_Print_Error(er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(result)), std::move(line), std::move(file), L"PW_GL_VOID_Handle"));
						throw er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(result)), std::move(line), std::move(file), L"PW_GL_VOID_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			#ifdef PW_DEBUG_MODE
				else {
					if (handle_type == true) {
						PRINT_MSG(L"GL", L"Function Success ( Completed )", SUCCESS_MSG);
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
			// (1) FREE_IMAGE_FORMAT&& result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) std::wstring description;
			// Purpose: 
			//  The description of the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_FI_Callback_Handle(FREE_IMAGE_FORMAT result, const char* description) {
				if (result != FIF_UNKNOWN) {
					std::string str = std::string(description);
					str.insert(0, "Unknown Image Format ");
					try {
						PW_Print_Error(er::Warning_Error(L"FI", TO_WSTRING(str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle"));
						throw er::Warning_Error(L"FI", TO_WSTRING(str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				else {
					std::string str = std::string(description);
					str.insert(0, "Known Image Format ");
					try {
						PW_Print_Error(er::Warning_Error(L"FI", TO_WSTRING(str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle"));
						throw er::Warning_Error(L"FI", TO_WSTRING(str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GL_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Interprets a result form a opengl function.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const GLenum&& result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t&& line;
			// Purpose: 
			//  The line the error was on.
			// (3) std::wstring file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_GL_Handle(const GLenum&& result, int32_t&& line, std::wstring&& file) {
				try {
					if (result <= 0) {
						PW_Print_Error(er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(result)).c_str(), std::move(line), std::move(file), L"PW_GL_Handle"));
						throw er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(result)).c_str(), std::move(line), std::move(file), L"PW_GL_Handle");
					}
					#ifdef PW_DEBUG_MODE
						else {
							PRINT_MSG(L"GL", L"Function Success ( Completed )", SUCCESS_MSG);
						}
					#endif // PW_DEBUG_MODE
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_FT_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Handles possible font loading issues.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const FT_Error&& result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const int32_t&& line;
			// Purpose: 
			//  The line the error was on.
			// (3) std::wstring file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE void PW_FT_Handle(const FT_Error&& result, int32_t&& line, std::wstring&& file, std::wstring&& function) {
				if (result != FT_Err_Ok) {
					PW_Print_Error(pw::er::Warning_Error(L"FT",
						std::move(TO_WSTRING(FT_Error_String(result))), std::move(line), std::move(file), std::move(function)));
					throw pw::er::Warning_Error(L"FT",
						std::move(TO_WSTRING(FT_Error_String(result))), std::move(line), std::move(file), std::move(function));
				}
			}
			#define PW_GLFW_VOID_CALL(funct)				{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__; pw::er::Engine_Error::PW_FILE_ = __FILEW__; }
			#define PW_GLFW_CALL(funct)						{ pw::er::Engine_Error::PW_GLFW_Handle(funct, __LINE__, __FILEW__); }
			#define PW_GL_VOID_CALL(funct, handle_type)		{ funct; pw::er::Engine_Error::PW_GL_VOID_Handle(glGetError(), __LINE__, __FILEW__,handle_type); }
			#define PW_FI_VOID_CALL(funct)					{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__; pw::er::Engine_Error::PW_FILE_ = __FILEW__; }
			#define PW_FI_VOID_CALL_C(funct)				{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__; pw::er::Engine_Error::PW_FILE_ = __FILEW__; funct }
			#define PW_GL_CALL(funct)						{ pw::er::Engine_Error::PW_GL_Handle(funct, __LINE__, __FILEW__); }
			#define PW_FT_CALL(funct)						{ pw::er::Engine_Error::PW_FT_Handle(funct, __LINE__, __FILEW__, L"No Function");}
			
			#define PW_PRINT_ERROR(p_error) { pw::er::Engine_Error::Evaluate_Error(p_error); }

		// Public Variables
		public:
			static int32_t PW_LINE_;
			static std::wstring PW_FILE_;
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