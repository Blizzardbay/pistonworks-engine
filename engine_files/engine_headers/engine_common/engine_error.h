// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
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
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <codecvt>
#include <locale.h>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H 
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype\fterrors.h>
#include <AL\alut.h>
#pragma warning (pop)
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
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <freeimage\FreeImage.h>
#pragma warning (pop)
#endif // !PW_FI_H 
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ER_NAMESPACE_SRT
	//////////////////////////////////
		class Engine_Error {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			static void PW_Print_Error(const pw::er::Warning_Error& p_error) {
				#ifdef PW_DEBUG_MODE
					if (pw::er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), p_error) == false) {
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
			static void PW_Print_Error(const pw::er::Severe_Error& p_error) {
				#ifdef PW_DEBUG_MODE
					if (pw::er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), p_error) == false) {
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
			static void Evaluate_Error(const std::any& p_error) {
				if (p_error.type() == typeid(pw::er::Warning_Error)) {
					PW_Print_Error(std::any_cast<pw::er::Warning_Error>(p_error));
				}
				if (p_error.type() == typeid(pw::er::Severe_Error)) {
					PW_Print_Error(std::any_cast<pw::er::Severe_Error>(p_error));
				}
			}
			static void PW_GLFW_Callback_Handle(int32_t p_result, const char* p_description) {
				if (p_result != 65537) {
					try {
						PW_Print_Error(er::Severe_Error(L"GLFW", TO_WSTRING(p_description).c_str(), std::move(PW_LINE_), PW_FILE_.c_str(), L"PW_GLFW_Callback_Handle"));
						throw er::Severe_Error(L"GLFW", TO_WSTRING(p_description).c_str(), std::move(PW_LINE_), PW_FILE_.c_str(), L"PW_GLFW_Callback_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static void PW_GLFW_Handle(const int32_t& p_result, const int32_t& p_line, const std::wstring& p_file) {
				if (p_result != GLFW_NO_ERROR && p_result != GLFW_TRUE) {
					try {
						PW_Print_Error(er::Severe_Error(L"GLFW", L"Function Error", p_line, p_file, L"PW_GLFW_Handle"));
						throw er::Severe_Error(L"GLFW", L"Function Error", p_line, p_file, L"PW_GLFW_Handle");
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
			static void PW_GL_VOID_Handle(const GLenum& p_result, const int32_t& p_line, const wchar_t* p_file, const bool& p_handle_type) {
				if (p_result != 0 && p_result != 1282) {
					try {
						PW_Print_Error(er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(p_result)),
							p_line, p_file, L"PW_GL_VOID_Handle"));
						throw er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(p_result)),
							p_line, p_file, L"PW_GL_VOID_Handle");
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
					if (p_handle_type == true) {
						PRINT_MSG(L"GL", L"Function Success ( Completed )", SUCCESS_MSG);
					}
				}
			#endif // PW_DEBUG_MODE
			}			
			static void PW_FI_Callback_Handle(FREE_IMAGE_FORMAT p_result, const char* p_description) {
				if (p_result != FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					std::string v_str = std::string(p_description);
					v_str.insert(0, "Unknown Image Format ");
					try {
						PW_Print_Error(er::Warning_Error(L"FI", TO_WSTRING(v_str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle"));
						throw er::Warning_Error(L"FI", TO_WSTRING(v_str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
				else {
					std::string v_str = std::string(p_description);
					v_str.insert(0, "Known Image Format ");
					try {
						PW_Print_Error(er::Warning_Error(L"FI", TO_WSTRING(v_str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle"));
						throw er::Warning_Error(L"FI", TO_WSTRING(v_str.c_str()).c_str(), std::move(PW_LINE_), std::move(PW_FILE_), L"PW_FI_Callback_Handle");
					}
					catch (const er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static void PW_GL_Handle(const GLenum& p_result, const int32_t& p_line, const std::wstring& p_file) {
				try {
					if (p_result <= 0) {
						PW_Print_Error(er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(p_result)).c_str(), p_line, p_file, L"PW_GL_Handle"));
						throw er::Severe_Error(L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(p_result)).c_str(), p_line, p_file, L"PW_GL_Handle");
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
			static void PW_FT_Handle(const FT_Error& p_result, const int32_t& p_line, const std::wstring& p_file, const std::wstring& p_function) {
				if (p_result != FT_Err_Ok) {
					PW_Print_Error(pw::er::Warning_Error(L"FT",
						std::move(TO_WSTRING(FT_Error_String(p_result))), p_line, p_file, p_function));
					throw pw::er::Warning_Error(L"FT",
						std::move(TO_WSTRING(FT_Error_String(p_result))), p_line, p_file, p_function);
				}
			}
			static void PW_AL_Handle(const ALenum& p_result, const int32_t& p_line, const std::wstring& p_file, const std::wstring& p_function) {
				if (p_result != AL_NO_ERROR) {
					PW_Print_Error(pw::er::Warning_Error(L"AL",
						std::move(TO_WSTRING(alGetString(p_result))), p_line, p_file, p_function));
					throw pw::er::Warning_Error(L"AL",
						std::move(TO_WSTRING(alGetString(p_result))), p_line, p_file, p_function);
				}
			}
			static void Release_Error() {
				PW_FILE_.~basic_string();
			}
			#define PW_GLFW_VOID_CALL(p_funct) {			\
				p_funct;									\
				pw::er::Engine_Error::PW_LINE_ = __LINE__;	\
				pw::er::Engine_Error::PW_FILE_ = __FILEW__;	\
			}
			#define PW_GLFW_CALL(p_funct) {											\
				pw::er::Engine_Error::PW_GLFW_Handle(p_funct, __LINE__, __FILEW__);	\
			}
			#define PW_GL_VOID_CALL(p_funct, p_handle_type) {												\
				p_funct;																					\
				pw::er::Engine_Error::PW_GL_VOID_Handle(glGetError(), __LINE__, __FILEW__, p_handle_type);	\
			}
			#define PW_FI_VOID_CALL(p_funct) {				\
				p_funct;									\
				pw::er::Engine_Error::PW_LINE_ = __LINE__;	\
				pw::er::Engine_Error::PW_FILE_ = __FILEW__;	\
			}
			#define PW_GL_CALL(p_funct)	{											\
				pw::er::Engine_Error::PW_GL_Handle(p_funct, __LINE__, __FILEW__);	\
			}
			#define PW_FT_CALL(p_funct) {															\
				pw::er::Engine_Error::PW_FT_Handle(p_funct, __LINE__, __FILEW__, L"No Function");	\
			}
			#define PW_AL_VOID_CALL(p_funct) {																				\
				p_funct;																									\
				pw::er::Engine_Error::PW_AL_Handle(alGetError(), __LINE__, __FILEW__, TO_WSTRING(VARIABLE_NAME(p_funct)));	\
			}  
			#define PW_PRINT_ERROR(p_error) {					\
				pw::er::Engine_Error::Evaluate_Error(p_error);	\
			}
		// Public Variables
		public:
			static int32_t PW_LINE_;
			static std::wstring PW_FILE_;
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
		};
	//////////////////////////////////
	ER_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_ERROR