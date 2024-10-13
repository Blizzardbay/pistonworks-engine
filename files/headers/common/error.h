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
#ifndef H_ERROR
#define H_ERROR
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <codecvt>
#include <locale.h>
#include <corecrt.h>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
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
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\constant.h"
#include "common\error_values.h"
#include "common\error_log.h"
//////////////////////////////////
// Engine Control Headers
#include "control\console_manip.h"
// Exception to format to fix <Windows.h> bug
#ifndef PW_FI_H
#define PW_FI_H
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <freeimage\FreeImage.h>
#pragma warning(pop)
#endif // !PW_FI_H 
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ER_NAMESPACE_SRT
		class Error {
		// Friends
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			#define HANDLE_MSG_ERROR {																									\
				if (pw::er::Error_State::Get() > PW_NO_ERROR) {																			\
					if (pw::er::Error_State::Is_Warning_Error() == true) {																\
						(void)pw::er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), pw::er::Error_State::Warning_Error());	\
					}																													\
					else {																												\
						(void)pw::er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), pw::er::Error_State::Severe_Error());	\
					}																													\
					pw::er::Error_State::Clear_Error();																					\
				}																														\
			}
			#define HANDLE_STR_ERROR HANDLE_MSG_ERROR
			/* Error List: NONE */
			static void Print_Error(const pw::er::Warning_Error& p_error) {
				#ifndef PW_DEBUG_MODE
					pw::er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), p_error);
				#endif
				#ifdef PW_DEBUG_MODE
					if (pw::er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), p_error) == false) {
						PRINT_MSG(p_error.From(), L"Failed to dump error", ERROR_MSG);
					}
					std::wstring v_line{ std::to_wstring(p_error.Line()) };
					v_line.insert(0, L"Line: ");

					std::wstring v_file{ p_error.File() };
					size_t v_pos = v_file.find(L"common", 0);
					if (v_pos != std::wstring::npos) {
						v_file.erase(0, v_pos);
					}
					else {
						v_pos = v_file.find(L"control", 0);
						if (v_pos != std::wstring::npos) {
							v_file.erase(0, v_pos);
						}
						else {
							v_pos = v_file.find(L"structures", 0);
							if (v_pos != std::wstring::npos) {
								v_file.erase(0, v_pos);
							}
						}
					}
					// Clear to stop double reporting
					pw::er::Error_State::Clear_Error();
					// If the print function has an error then just dump and clear error state.
					PRINT_MSG(p_error.From(), p_error.Msg(), ERROR_MSG);
					HANDLE_MSG_ERROR;

					PRINT_MSG(p_error.From(), v_line, ERROR_MSG);
					HANDLE_MSG_ERROR;

					PRINT_MSG(p_error.From(), v_file, ERROR_MSG);
					HANDLE_MSG_ERROR;

					PRINT_MSG(p_error.From(), p_error.Function(), ERROR_MSG);
					HANDLE_MSG_ERROR;
				#endif // PW_DEBUG_MODE
			}
			/* Error List: NONE */
			static void Print_Error(const pw::er::Severe_Error& p_error) {
				#ifndef PW_DEBUG_MODE
					pw::er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), p_error);
				#endif
				#ifdef PW_DEBUG_MODE
					if (pw::er::Error_Log::Dump_Log(pw::cm::Constant::Pistonworks_Path(), p_error) == false) {
						PRINT_MSG(p_error.From(), L"Failed to dump error", ERROR_MSG);
					}
					std::wstring v_line{ std::to_wstring(p_error.Line()) };
					v_line.insert(0, L"Line: ");

					std::wstring v_file{ p_error.File() };
					size_t v_pos = v_file.find(L"common", 0);
					if (v_pos != std::wstring::npos) {
						v_file.erase(0, v_pos);
					}
					else {
						v_pos = v_file.find(L"control", 0);
						if (v_pos != std::wstring::npos) {
							v_file.erase(0, v_pos);
						}
						else {
							v_pos = v_file.find(L"structures", 0);
							if (v_pos != std::wstring::npos) {
								v_file.erase(0, v_pos);
							}
						}
					}
					// Clear to stop double reporting
					pw::er::Error_State::Clear_Error();
					// If the print function has an error then just dump and clear error state.
					PRINT_MSG(p_error.From(), p_error.Msg(), ERROR_MSG);
					HANDLE_MSG_ERROR;

					PRINT_MSG(p_error.From(), v_line, ERROR_MSG);
					HANDLE_MSG_ERROR;

					PRINT_MSG(p_error.From(), v_file, ERROR_MSG);
					HANDLE_MSG_ERROR;

					PRINT_MSG(p_error.From(), p_error.Function(), ERROR_MSG);
					HANDLE_MSG_ERROR;
				#endif // PW_DEBUG_MODE
			}
			/* Error List: NONE */
			static void GLFW_Callback_Handle(int32_t p_result, const char* p_description) noexcept {
				// Called by GLFW so cannot guarantee that it will be able to be error checked.
				// So it does not update Error_State and prints error
				if (p_result != 65537) {
					std::wstring v_werror_msg{ TO_WSTRING(p_description) };
					if (v_werror_msg == std::wstring()) {
						HANDLE_STR_ERROR;
					}

					Print_Error(er::Severe_Error(
						L"pw::er::Error", v_werror_msg, 0ULL, std::wstring(), L"GLFW_Callback_Handle"
					));
				}
			}
			/* Error List: PW_GLFW_ERROR */
			static void GLFW_Handle(const int32_t p_result, const uint64_t& p_line, const std::wstring& p_file) {
				if (p_result != GLFW_NO_ERROR && p_result != GLFW_TRUE) {
					const char* v_error_msg{ nullptr };
					// Returns pointer that will be handled by GLFW
					(void)glfwGetError(&v_error_msg);

					if (v_error_msg == nullptr) {
						SET_ERROR_STATE(PW_GLFW_ERROR);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::er::Error", L"glfwGetError had an error reporting the error. Error code: " + std::to_wstring(p_result), p_line, p_file, L"GLFW_Handle"));
						return;
					}
					std::wstring v_werror_msg{ TO_WSTRING(v_error_msg) };
					if (v_werror_msg == std::wstring()) {
						HANDLE_STR_ERROR;
					}
					SET_ERROR_STATE(PW_GLFW_ERROR);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::er::Error", v_werror_msg, p_line, p_file, L"GLFW_Handle"));
				}
				#ifdef PW_DEBUG_MODE
				else {
					PRINT_MSG(L"GLFW", L"Function Success ( Completed )", SUCCESS_MSG);
					HANDLE_MSG_ERROR;
				}
				#endif // PW_DEBUG_MODE
			}
			/* Error List: PW_GL_ERROR */
			static void GL_VOID_Handle(const GLenum& p_result, const uint64_t& p_line, const wchar_t* p_file, const bool p_handle_type) {
				if (p_result != 0 && p_result != 1282) {
					SET_ERROR_STATE(PW_GL_ERROR);
					SET_ERROR_TYPE(er::Severe_Error(
						L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(p_result)),
						p_line, p_file, L"GL_VOID_Handle"
					));
				}
				#ifdef PW_DEBUG_MODE
				else {
					if (p_handle_type == true) {
						PRINT_MSG(L"GL", L"Function Success ( Completed )", SUCCESS_MSG);
						HANDLE_MSG_ERROR;
					}
				}
				#endif // PW_DEBUG_MODE
			}		
			/* Error List: NONE */
			static void FI_Callback_Handle(FREE_IMAGE_FORMAT p_result, const char* p_description) noexcept {
				if (p_result != FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					std::string v_str{ p_description };
					v_str.insert(0, "Unknown Image Format ");

					std::wstring v_werror_msg{ TO_WSTRING(p_description) };
					if (v_werror_msg == std::wstring()) {
						HANDLE_STR_ERROR;
					}

					Print_Error(er::Warning_Error(
						L"FI", v_werror_msg, 0ULL, std::wstring(), L"FI_Callback_Handle"
					));
				}
				else {
					std::string v_str{ p_description };
					v_str.insert(0, "Known Image Format ");

					std::wstring v_werror_msg{ TO_WSTRING(p_description) };
					if (v_werror_msg == std::wstring()) {
						HANDLE_STR_ERROR;
					}

					Print_Error(er::Warning_Error(
						L"FI", v_werror_msg, 0ULL, std::wstring(), L"FI_Callback_Handle"
					));
				}
			}
			/* Error List: PW_GL_ERROR */
			static void GL_Handle(const GLenum& p_result, const uint64_t& p_line, const std::wstring& p_file) {
				if (p_result <= 0) {
					SET_ERROR_STATE(PW_GL_ERROR);
					SET_ERROR_TYPE(er::Severe_Error(
						L"GL", std::wstring(std::wstring(L"Function Error: ") + std::to_wstring(p_result)),
						p_line, p_file, L"GL_Handle"
					));
				}
				#ifdef PW_DEBUG_MODE
				else {
					//PRINT_MSG(L"GL", L"Function Success ( Completed )", SUCCESS_MSG);
					HANDLE_MSG_ERROR;
				}
				#endif // PW_DEBUG_MODE
			}
			/* Error List: PW_FT_ERROR */
			static void FT_Handle(const FT_Error& p_result, const uint64_t& p_line, const std::wstring& p_file, const std::wstring& p_function) {
				if (p_result != FT_Err_Ok) {
					std::wstring v_werror_msg{ TO_WSTRING(FT_Error_String(p_result)) };
					if (v_werror_msg == std::wstring()) {
						HANDLE_STR_ERROR;
					}

					SET_ERROR_STATE(PW_FT_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(
						L"FT", v_werror_msg, p_line, p_file, p_function
					));
				}
			}
			/* Error List: PW_AL_ERROR */
			static void AL_Handle(const ALenum& p_result, const uint64_t& p_line, const std::wstring& p_file, const std::wstring& p_function) {
				if (p_result != AL_NO_ERROR) {
					std::wstring v_werror_msg{ TO_WSTRING(alGetString(p_result)) };
					if (v_werror_msg == std::wstring()) {
						HANDLE_STR_ERROR;
					}

					SET_ERROR_STATE(PW_AL_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(
						L"AL", v_werror_msg, p_line, p_file, p_function
					));
				}
			}
			static void Release() noexcept {
				m_file.~basic_string();
			}
			#define PW_GLFW_VOID_CALL(p_funct, p_return)																			\
				TRY_LINE p_funct;																									\
				pw::er::Error::m_line = TO_UINT64(__LINE__);																		\
				pw::er::Error::m_file = __FILEW__;																					\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_GLFW_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_GLFW_CALL(p_funct, p_return)																					\
				TRY_LINE pw::er::Error::GLFW_Handle(p_funct, TO_UINT64(__LINE__), __FILEW__);										\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_GLFW_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_GL_VOID_CALL(p_funct, p_return, p_handle_type)																\
				TRY_LINE p_funct;																									\
				pw::er::Error::GL_VOID_Handle(glGetError(), pw::er::Error_State::Error_Line(), __FILEW__, TO_BOOL(p_handle_type));	\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_GL_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_GL_CUSTOM_CALL(p_funct, p_return, p_handle_type, p_type)														\
				TRY_LINE p_funct;																									\
				pw::er::Error::GL_VOID_Handle(glGetError(), pw::er::Error_State::Error_Line(), __FILEW__, TO_BOOL(p_handle_type));	\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_GL_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return p_type(0);														\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// In this special case where you return a template type or special return type value
			#define PW_GL_CUSTOM_CALL_T(p_funct, p_return, p_handle_type, ...)														\
				TRY_LINE p_funct;																									\
				pw::er::Error::GL_VOID_Handle(glGetError(), pw::er::Error_State::Error_Line(), __FILEW__, TO_BOOL(p_handle_type));	\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_GL_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return __VA_ARGS__;														\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_FI_VOID_CALL(p_funct, p_return)																				\
				TRY_LINE p_funct;																									\
				pw::er::Error::m_line = TO_UINT64(__LINE__);																		\
				pw::er::Error::m_file = __FILEW__;																					\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_FI_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_FI_PTR_CALL(p_funct, p_return)																				\
				TRY_LINE p_funct;																									\
				pw::er::Error::m_line = TO_UINT64(__LINE__);																		\
				pw::er::Error::m_file = __FILEW__;																					\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_FI_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return nullptr;															\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_FI_CUSTOM_CALL(p_funct, p_return, p_type)																	\
				TRY_LINE p_funct;																									\
				pw::er::Error::m_line = TO_UINT64(__LINE__);																		\
				pw::er::Error::m_file = __FILEW__;																					\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_FI_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return p_type();														\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_GL_CALL(p_funct, p_return)																					\
				TRY_LINE pw::er::Error::GL_Handle(p_funct, TO_UINT64(__LINE__), __FILEW__);											\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_GL_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_FT_CALL(p_funct, p_return)																					\
				TRY_LINE pw::er::Error::FT_Handle(p_funct, TO_UINT64(__LINE__), __FILEW__, L"No Function");							\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_FT_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_AL_VOID_CALL(p_funct, p_return)																				\
				TRY_LINE p_funct;																									\
				pw::er::Error::AL_Handle(alGetError(), TO_UINT64(__LINE__), __FILEW__, TO_WSTRING(VARIABLE_NAME(p_funct)));			\
				if (pw::er::Error_State::Get() > 0) {																				\
					pw::er::Error_State::Handle_Error();																			\
					std::wstring v_funct{ L"\"" };																					\
					std::wstring v_class{ __FUNCTIONW__ };																			\
					v_funct.append(EXPRESSION_WSTRING(p_funct));																	\
					v_funct.append(L"\" had an error.");																			\
					size_t v_last_colon{ 0 };																						\
					v_last_colon = v_class.find_last_of(L':');																		\
					if (v_last_colon != std::wstring::npos) {																		\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };								\
						v_class = v_class.substr(0, v_last_colon - 1);																\
						SET_ERROR_STATE(PW_AL_ERROR);																				\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);									\
					}																												\
					if constexpr(TO_BOOL(p_return) == true) return;																	\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Public Variables
		public:
			static uint64_t m_line;
			static std::wstring m_file;
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
		};
	ER_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_ERROR