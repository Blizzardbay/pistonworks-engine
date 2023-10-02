// BSD 3 - Clause License
//
// Copyright(c) 2021-2023, Darrian Corkadel
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
#ifndef H_CONSTANT
#define H_CONSTANT
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <typeinfo>
#include <any>
#include <chrono>
#include <filesystem>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#ifndef __glew_h__
#include <GL\glew.h>
#endif // !__glew_h__
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <glm\trigonometric.hpp>
#include <glm\vec2.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error_state.h"
#include "common\typedef.h"
//////////////////////////////////
// Engine Control Headers
#include "control\memory.h"
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CM_NAMESPACE_SRT
		struct Destroy_GLFW {
			// Default Class Structures
		public:
		private:
			// Public Functions/Macros 
		public:
			/* Error List: PW_INVAILD_PARAMETER_S */
			void operator()(GLFWwindow* p_window) {
				if (p_window == nullptr) {
					SET_ERROR_STATE(PW_INVAILD_PARAMETER_S);
					return;
				}
				glfwDestroyWindow(p_window);
			}
			// Public Variables
		public:
			// Private Functions/Macros
		private:
			// Private Variables
		private:
		};
		class Constant {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			#define TO_WCHAR(c_str)				pw::cm::Constant::Evaluate_WStr(c_str)
			#define TO_CHAR(w_str)				pw::cm::Constant::Evaluate_Str(w_str)
			#define TO_WSTRING(c_str)			pw::cm::Constant::Evaluate_TWStr(c_str)
			#define TO_STRING(w_str)			pw::cm::Constant::Evaluate_TStr(w_str)

			/* Error List: PW_FUNCTION_ERROR, PW_UNKNOWN_STRING_TYPE */
			_NODISCARD static wchar_t* Evaluate_WStr(const std::any& p_str) noexcept {
				if (p_str.type() == typeid(char)) {
					char v_temp[2];
					v_temp[0] = std::any_cast<char>(p_str);
					v_temp[1] = '\0';

					PW_PTR_CALL(wchar_t* v_return = pw::cm::Constant::To_WChar(v_temp), true);

					return v_return;
				}
				if (p_str.type() == typeid(const char*)) {
					PW_PTR_CALL(wchar_t* v_return = pw::cm::Constant::To_WChar(std::any_cast<const char*>(p_str)), true);

					return v_return;
				}
				if (p_str.type() == typeid(std::string)) {
					PW_PTR_CALL(wchar_t* v_return = pw::cm::Constant::To_WChar(std::any_cast<std::string>(p_str)), true);

					return v_return;
				}
				if (p_str.type() == typeid(wchar_t)) {
					wchar_t v_temp[2];
					v_temp[0] = std::any_cast<wchar_t>(p_str);
					v_temp[1] = L'\0';

					PW_PTR_CALL(wchar_t* v_return = pw::cm::Constant::To_WChar(v_temp), true);

					return v_return;
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					PW_PTR_CALL(wchar_t* v_return = pw::cm::Constant::To_WChar(std::any_cast<const wchar_t*>(p_str)), true);

					return v_return;
				}
				if (p_str.type() == typeid(std::wstring)) {
					TRY_LINE wchar_t* v_return = pw::cm::Constant::To_WChar(std::any_cast<std::wstring>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"wchar_t* To_WChar(const wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_WStr");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(wchar_t*)) {
					return std::any_cast<wchar_t*>(p_str);
				}

				SET_ERROR_STATE(PW_UNKNOWN_STRING_TYPE);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Unknown String Type", ERROR_LINE, __FILEW__, L"Evaluate_WStr"));

				return nullptr;
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static wchar_t* To_WChar(const char* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_WChar"));
					return nullptr;
				}
				else {
					// Get the msg size
					TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_WChar"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					wchar_t* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<wchar_t>(v_msg_size), false);
					if (v_msg == nullptr) {
						return nullptr;
					}

					size_t v_chars_converted = 0;
					// Convert the memory
					if (TRY_LINE mbstowcs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
						SET_ERROR_STATE(PW_BUFFER_SIZE_MISMATCH);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Destination buffer is too small", ERROR_LINE, __FILEW__, L"To_WChar"));

						(void)pw::co::Memory::Deallocate<wchar_t>(v_msg);
						return nullptr;
					}
					// If we converted all of the memory correctly then return the result
					if (v_chars_converted == v_msg_size) {
						return v_msg;
					}
					else {
						SET_ERROR_STATE(PW_CRT_FUNCTION_FAILURE);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"CRT Function Failed: mbstowcs_s", ERROR_LINE, __FILEW__, L"To_WChar"));

						(void)pw::co::Memory::Deallocate<wchar_t>(v_msg);
						return nullptr;
					}
				}
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static wchar_t* To_WChar(const std::string& p_msg) noexcept {
				// This function inherits the other To_WChar errors
				return To_WChar(p_msg.c_str());
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static wchar_t* To_WChar(const wchar_t* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_WChar"));
					return nullptr;
				}
				else {
					// Get the msg size
					TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_WChar"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					wchar_t* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<wchar_t>(v_msg_size), false)
					if (v_msg == nullptr) {
						return nullptr;
					}
					for (size_t i = 0; i < v_msg_size; i++) {
						v_msg[i] = p_msg[i];
					}
					return v_msg;
				}
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static wchar_t* To_WChar(const std::wstring& p_msg) noexcept {
				// This function inherits the other To_WChar errors
				return To_WChar(p_msg.c_str());
			}
			/* Error List: PW_FUNCTION_ERROR, PW_UNKNOWN_STRING_TYPE */
			_NODISCARD static char* Evaluate_Str(const std::any& p_str) {
				if (p_str.type() == typeid(char)) {
					char v_temp[2];
					v_temp[0] = std::any_cast<char>(p_str);
					v_temp[1] = '\0';

					TRY_LINE char* v_return = pw::cm::Constant::To_Char(v_temp);

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"char* To_Char(const char* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(const char*)) {

					TRY_LINE char* v_return = pw::cm::Constant::To_Char(std::any_cast<const char*>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"char* To_Char(const char* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(std::string)) {
					TRY_LINE char* v_return = pw::cm::Constant::To_Char(std::any_cast<std::string>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"char* To_Char(const char* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(wchar_t)) {
					wchar_t v_temp[2];
					v_temp[0] = std::any_cast<wchar_t>(p_str);
					v_temp[1] = L'\0';

					TRY_LINE char* v_return = pw::cm::Constant::To_Char(v_temp);

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"char* To_Char(const 'wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					TRY_LINE char* v_return = pw::cm::Constant::To_Char(std::any_cast<const wchar_t*>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"char* To_Char(const 'wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(std::wstring)) {
					TRY_LINE char* v_return = pw::cm::Constant::To_Char(std::any_cast<std::wstring>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"char* To_Char(const 'wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(char*)) {
					return std::any_cast<char*>(p_str);
				}

				SET_ERROR_STATE(PW_UNKNOWN_STRING_TYPE);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Unknown String Type", ERROR_LINE, __FILEW__, L"Evaluate_Str"));

				return nullptr;
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static char* To_Char(const wchar_t* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_Char"));
					return nullptr;
				}
				else {
					// Get the msg size 
					TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_Char"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					char* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<char>(v_msg_size), false);
					if (v_msg == nullptr) {
						return nullptr;
					}
					size_t v_chars_converted = 0;
					// Convert the memory
					if (TRY_LINE wcstombs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
						SET_ERROR_STATE(PW_BUFFER_SIZE_MISMATCH);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Destination buffer is too small", ERROR_LINE, __FILEW__, L"To_Char"));

						(void)pw::co::Memory::Deallocate<char>(v_msg);
						return nullptr;
					}
					// If we converted all of the memory correctly then return the result
					if (v_chars_converted == v_msg_size) {
						return v_msg;
					}
					else {
						SET_ERROR_STATE(PW_CRT_FUNCTION_FAILURE);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"CRT Function Failed: wcstombs_s", ERROR_LINE, __FILEW__, L"To_WChar"));

						(void)pw::co::Memory::Deallocate<char>(v_msg);
						return nullptr;
					}
				}
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static char* To_Char(const std::wstring& p_msg) noexcept {
				// This function inherits the other To_Char errors
				return To_Char(p_msg.c_str());
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static char* To_Char(const char* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_Char"));
					return nullptr;
				}
				else {
					// Get the msg size 
					TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_Char"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					char* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<char>(v_msg_size), false);
					if (v_msg == nullptr) {
						return nullptr;
					}
						
					for (size_t i = 0; i < v_msg_size; i++) {
						v_msg[i] = p_msg[i];
					}
						
					return v_msg;
				}
			}
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static char* To_Char(const std::string& p_msg) noexcept {
				// This function inherits the other To_Char errors
				return To_Char(p_msg.c_str());
			}
			/* Error List: PW_FUNCTION_ERROR */
			_NODISCARD static std::wstring Evaluate_TWStr(const std::any& p_str) noexcept {
				// Use other converting function to do the work
				TRY_LINE wchar_t* v_msg = TO_WCHAR(p_str);

				if (v_msg == nullptr) {
					pw::er::Error_State::Handle_Error();

					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"pw::cm::Constant::Evaluate_WStr(c_str)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_TWStr");
					return std::wstring();
				}
				std::wstring v_formated_msg{};

				v_formated_msg.append(v_msg);

				if (pw::co::Memory::Deallocate<wchar_t>(v_msg) == false) {
					if (v_msg != nullptr) {
						delete[] v_msg;
						v_msg = nullptr;
					}
				}

				return v_formated_msg;
			}
			/* Error List: PW_FUNCTION_ERROR */
			_NODISCARD static std::string Evaluate_TStr(const std::any& p_str) noexcept {
				// Use other converting function to do the work
				TRY_LINE char* v_msg = TO_CHAR(p_str);

				if (v_msg == nullptr) {
					pw::er::Error_State::Handle_Error();

					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::cm::Constant", L"\"pw::cm::Constant::Evaluate_Str(w_str)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_TStr");
					return std::string();
				}
				std::string v_formated_msg{};

				v_formated_msg.append(v_msg);

				if (pw::co::Memory::Deallocate<char>(v_msg) == false) {
					if (v_msg != nullptr) {
						delete[] v_msg;
						v_msg = nullptr;
					}
				}

				return v_formated_msg;
			}
			/* Error List: PW_NULL_PARAMETER_W */
			static void Calc_Elapsed_Time(GLFWwindow* p_main_window) noexcept {
				if (TRY_LINE p_main_window == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_main_window was nullptr", ERROR_LINE, __FILEW__, L"Calc_Elapsed_Time"));
					return;
				}
				else {
					m_start_time = m_end_time;

					m_elapsed_time += m_delta_time;
					if (m_elapsed_time >= std::chrono::milliseconds(1000)) {
						if (m_fps_max < m_frames) {
							m_fps_max = m_frames;
						}
						if (m_fps_averager.size() != 60) {
							// Strong exception guarantee
							m_fps_averager.push_back(m_frames);

							size_t v_fps_average = 0;
							for (size_t i = 0; i < m_fps_averager.size(); i++) {
								v_fps_average = v_fps_average + m_fps_averager.at(i);
							}
							if (m_fps_averager.size() != 0) {
								m_fps_average = (int32_t)((float)v_fps_average / (float)m_fps_averager.size());
							}
						}
						else {
							// Size guaranteed to be == 60
							// Could cause debug assertion if m_fps_averager.size() == 0
							m_fps_averager.erase(m_fps_averager.begin());
							// Strong exception guarantee
							m_fps_averager.push_back(m_frames);

							size_t v_fps_average = 0;
							for (size_t i = 0; i < m_fps_averager.size(); i++) {
								v_fps_average = v_fps_average + m_fps_averager.at(i);
							}
							m_fps_average = (int32_t)((float)v_fps_average / (float)m_fps_averager.size());
						}
						m_elapsed_time = std::chrono::steady_clock::duration();

						#ifdef PW_DEBUG_MODE
							if (m_debug_info != nullptr) {
								m_debug_info();
							}
						#endif
						m_last_frames = m_frames;
						m_frames = 0;
					}
				}
			}
			/* Error List: NONE */
			static inline void Wait() noexcept {
				// Increment frame since frame is over
				m_frames = m_frames + 1;
				m_end_time = std::chrono::steady_clock::now();
				m_delta_time = m_end_time - m_start_time;
				if (m_vsync != true) {
					while ((std::chrono::steady_clock::now() - m_end_time) < (std::chrono::milliseconds((1000 / m_fps_cap) * 2) - m_delta_time));
				}
			}
			//////////////////////////////////
			// Window
			//////////////////////////////////
			/* Error List: NONE */
			_NODISCARD static F_INLINE const uint32_t& Window_Width() noexcept {
				return m_window_width;
			}
			/* Error List: PW_INVAILD_PARAMETER_W */
			static inline void Set_Window_Width(const uint32_t& p_window_width) {
				if (TRY_LINE p_window_width == 0x0000U) {
					SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_window_width was 0x0000U", ERROR_LINE, __FILEW__, L"Set_Window_Width"));
					return;
				}
				else {
					m_window_width = p_window_width;
				}
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const uint32_t& Window_Height() noexcept {
				return m_window_height;
			}
			/* Error List: PW_INVAILD_PARAMETER_W */
			static F_INLINE void Set_Window_Height(const uint32_t& p_window_height) {
				if (TRY_LINE p_window_height == 0x0000U) {
					SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_window_height was 0x0000U", ERROR_LINE, __FILEW__, L"Set_Window_Height"));
					return;
				}
				else {
					m_window_height = p_window_height;
				}
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const uint32_t& Hafe_Window_Width() noexcept {
				return m_hafe_window_width;
			}
			/* Error List: PW_INVAILD_PARAMETER_W */
			static inline void Set_Hafe_Window_Width(const uint32_t& p_hafe_window_width) {
				if (TRY_LINE p_hafe_window_width == 0x0000U) {
					SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_hafe_window_width was 0x0000U", ERROR_LINE, __FILEW__, L"Set_Hafe_Window_Width"));
					return;
				}
				else {
					m_hafe_window_width = p_hafe_window_width;
				}
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const uint32_t& Hafe_Window_Height() noexcept {
				return m_hafe_window_height;
			}
			/* Error List: PW_INVAILD_PARAMETER_W */
			static inline void Set_Hafe_Window_Height(const uint32_t& p_hafe_window_height) {
				if (TRY_LINE p_hafe_window_height == 0x0000U) {
					SET_ERROR_STATE(PW_INVAILD_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_hafe_window_height was 0x0000U", ERROR_LINE, __FILEW__, L"Set_Hafe_Window_Height"));
					return;
				}
				else {
					m_hafe_window_height = p_hafe_window_height;
				}
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const std::wstring& Window_Name() noexcept {
				return m_window_name;
			}
			/* Error List: PW_EMPTY_PARAMETER_W */
			static inline void Set_Window_Name(const std::wstring& p_window_name) {
				if (TRY_LINE p_window_name.empty() == true) {
					SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_window_name was empty", ERROR_LINE, __FILEW__, L"Set_Window_Name"));
					return;
				}
				else {
					std::string v_window_name = TO_STRING(p_window_name);

					if (m_current_window != nullptr) {
						glfwSetWindowTitle(&**m_current_window, v_window_name.c_str());
					}
					m_window_name = p_window_name;
				}
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>* Window() noexcept {
				return m_current_window;
			}
			/* Error List: PW_NULL_PARAMETER_W */
			static F_INLINE void Set_Window(std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>* p_window) {
				if (TRY_LINE p_window == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Invalid Parameter: p_window was nullptr", ERROR_LINE, __FILEW__, L"Set_Window"));
					return;
				}
				else {
					m_current_window = p_window;
				}
			}
			//////////////////////////////////
			// Fps / Monitor
			//////////////////////////////////
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& FPS() noexcept {
				return m_frames;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& Last_FPS() noexcept {
				return m_last_frames;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& FPS_Max() noexcept {
				return m_fps_max;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& FPS_Average() noexcept {
				return m_fps_average;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& FPS_Cap() noexcept {
				return m_fps_cap;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const bool& Vsync() noexcept {
				return m_vsync;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& Refresh_Rate() noexcept {
				return m_refresh_rate;
			}
			/* Error List: NONE */
			static F_INLINE void Set_Refresh_Rate(const int32_t& p_refresh_rate) noexcept {
				m_refresh_rate = p_refresh_rate;
			}
			/* Error List: NONE */
			static F_INLINE void Set_FPS_Info(const int32_t& p_fps_cap, const bool& p_has_vsync) noexcept {
				if (p_fps_cap <= 0) {
					m_fps_cap = INT32_MAX;
				}
				else {
					m_fps_cap = p_fps_cap;
				}
				m_vsync = p_has_vsync;
			}
			//////////////////////////////////
			// Time
			//////////////////////////////////
			/* Error List: NONE */
			_NODISCARD static F_INLINE const std::chrono::steady_clock::duration& Delta_Time() noexcept {
				return m_delta_time;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const std::chrono::steady_clock::time_point& Current_Time() noexcept {
				return m_start_time;
			}
			//////////////////////////////////
			// Mouse
			//////////////////////////////////
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& Mouse_X_Coord() noexcept {
				return m_mouse_x_position;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const int32_t& Mouse_Y_Coord() noexcept {
				return m_mouse_y_position;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const double& Mouse_X_Coord_Raw() noexcept {
				return m_mouse_x_position_raw;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const double& Mouse_Y_Coord_Raw() noexcept {
				return m_mouse_y_position_raw;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const glm::vec2 Mouse_Coord() noexcept {
				return glm::vec2(TO_FLOAT(m_mouse_x_position), TO_FLOAT(m_mouse_y_position));
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const glm::vec2 Last_Mouse_Coord() noexcept {
				return glm::vec2(TO_FLOAT(m_last_mouse_x_position), TO_FLOAT(m_last_mouse_y_position));
			}
			/* Error List: NONE */
			static F_INLINE void Set_Mouse_Coord(const int32_t& p_x, const int32_t& p_y) noexcept {
				m_last_mouse_x_position = m_mouse_x_position;
				m_last_mouse_y_position = m_mouse_y_position;

				m_mouse_x_position = p_x;
				m_mouse_y_position = p_y;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const glm::vec2 Mouse_Coord_Raw() noexcept {
				return glm::vec2(TO_FLOAT(m_mouse_x_position_raw), TO_FLOAT(m_mouse_y_position_raw));
			}
			/* Error List: NONE */
			static F_INLINE void Set_Mouse_Coord_Raw(const double& p_x, const double& p_y) noexcept {
				m_mouse_x_position_raw = p_x;
				m_mouse_y_position_raw = p_y;
			}
			//////////////////////////////////
			// Other
			//////////////////////////////////
			/* Error List: NONE */
			_NODISCARD static F_INLINE const std::filesystem::path& Pistonworks_Path() noexcept {
				return m_pistonworks_path;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const std::filesystem::path& Game_Path() noexcept {
				return m_game_path;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const float& Inverse_Z_Tan() noexcept {
				return m_inverse_z_tan;
			}
			/* Error List: NONE */
			_NODISCARD static F_INLINE const bool& Window_Lock() noexcept {
				return m_window_lock;
			}
			/* Error List: NONE */
			static F_INLINE void Set_Window_Lock(const bool& p_state) noexcept {
				m_window_lock = p_state;
			}
			/* Error List: NONE */
			static void Close_Engine() noexcept {
				glfwSetWindowShouldClose(&**cm::Constant::Window(), GLFW_TRUE);
			}
			#ifdef PW_DEBUG_MODE
				/* Error List: NONE */
				static inline void Set_Debug_Function(const PW_FUNCTION& p_new_function) noexcept {
					m_debug_info = p_new_function;
				}
			#endif // PW_DEBUG_MODE
			//////////////////////////////////
			// Release
			//////////////////////////////////
			/* Error List: NONE */
			static inline void Release() noexcept {
				m_window_name.~basic_string();

				m_fps_averager.~vector();

				m_pistonworks_path.~path();
				m_game_path.~path();

				#ifdef PW_DEBUG_MODE
					m_debug_info.~function();
				#endif // PW_DEBUG_MODE
			}
		// Public Variables
		public:
			static constexpr uint32_t PW_SCALE_FACTOR			= 32;
			static constexpr uint32_t PW_FONT_RESOLUTION		= 96;

			static constexpr uint32_t PW_SCROLL_WHEEL_FORWARD	= 0x00A1U;
			static constexpr uint32_t PW_SCROLL_WHEEL_BACKWARD	= 0x00A2U;
			static constexpr uint32_t PW_COLLISION_EVENT		= 0x00A3U;
			static constexpr uint32_t PW_CLICK_EVENT			= 0x00A4U;
			static constexpr uint32_t PW_HOVER_EVENT			= 0x00A5U;
			static constexpr uint32_t PW_ANIMATION_START_EVENT	= 0x00A6U;
			static constexpr uint32_t PW_ANIMATION_END_EVENT	= 0x00A7U;
			static constexpr uint32_t PW_SOUND_START_EVENT		= 0x00A8U;
			static constexpr uint32_t PW_SOUND_END_EVENT		= 0x00A9U;
			static constexpr uint32_t PW_MOUSE_EVENT			= 0x00AAU;
			static constexpr uint32_t PW_KEYBOARD_EVENT			= 0x00ABU;
			static constexpr uint32_t PW_SCROLL_EVENT			= 0x00ACU;
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			// Window's current width
			static uint32_t m_window_width;
			// Window's current height
			static uint32_t m_window_height;
			// Haft of the Window's current width
			static uint32_t m_hafe_window_width;
			// Haft of the Window's current height
			static uint32_t m_hafe_window_height;
			// Window's current name
			static std::wstring m_window_name;
			// The current window
			static std::unique_ptr<GLFWwindow, Destroy_GLFW>* m_current_window;

			static int32_t m_frames;
			static int32_t m_last_frames;
			static int32_t m_fps_max;
			static std::vector<int32_t> m_fps_averager;
			static int32_t m_fps_average;
			static int32_t m_fps_cap;
			static bool m_vsync;
			static int32_t m_refresh_rate;

			static std::chrono::steady_clock::time_point m_start_time;
			static std::chrono::steady_clock::time_point m_end_time;
			// The current delta time in the engine represented by nanoseconds
			static std::chrono::steady_clock::duration m_delta_time;
			static std::chrono::steady_clock::duration m_elapsed_time;

			static int32_t m_mouse_x_position;
			static int32_t m_mouse_y_position;
			static int32_t m_last_mouse_x_position;
			static int32_t m_last_mouse_y_position;
			static double m_mouse_x_position_raw;
			static double m_mouse_y_position_raw;

			static std::filesystem::path m_pistonworks_path;
			static std::filesystem::path m_game_path;

			static bool m_window_lock;
			static const float m_inverse_z_tan;

			#ifdef PW_DEBUG_MODE
				static PW_FUNCTION m_debug_info;
			#endif // PW_DEBUG_MODE
		};
	CM_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_CONSTANT