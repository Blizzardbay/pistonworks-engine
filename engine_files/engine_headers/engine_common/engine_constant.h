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
#ifndef H_ENGINE_CONSTANT
#define H_ENGINE_CONSTANT
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
#include <typeinfo>
#include <any>
#include <chrono>
#include <filesystem>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4201)
#ifndef __glew_h__
#include <GL\glew.h>
#endif // !__glew_h__
#undef APIENTRY
#include <GLFW\glfw3.h>
#include <glm\trigonometric.hpp>
#include <glm\vec2.hpp>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_exception.h"
#include "engine_common\engine_memory.h"
#include "engine_common\engine_typedef.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////										
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	CM_NAMESPACE_SRT
	//////////////////////////////////
		struct Destroy_GLFW {
			// Default Class Structures
		public:
		private:
			// Public Functions/Macros 
		public:
			void operator()(GLFWwindow* p_window) {
				glfwDestroyWindow(p_window);
			}
			// Public Variables
		public:
			// Private Functions/Macros
		private:
			// Private Variables
		private:
		};
		class Engine_Constant {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			#define TO_WCHAR(c_str)				pw::cm::Engine_Constant::Evaluate_WStr(c_str)
			#define TO_CHAR(w_str)				pw::cm::Engine_Constant::Evaluate_Str(w_str)
			#define TO_WSTRING(c_str)			pw::cm::Engine_Constant::Evaluate_TWStr(c_str)
			#define TO_STRING(w_str)			pw::cm::Engine_Constant::Evaluate_TStr(w_str)

			static wchar_t* Evaluate_WStr(const std::any& p_str) {
				if (p_str.type() == typeid(const char*)) {
					return To_WChar(std::any_cast<const char*>(p_str));
				}
				if (p_str.type() == typeid(std::string)) {
					return To_WChar(std::any_cast<std::string>(p_str));
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					return To_WChar(std::any_cast<const wchar_t*>(p_str));
				}
				if (p_str.type() == typeid(std::wstring)) {
					return To_WChar(std::any_cast<std::wstring>(p_str).c_str());
				}
				if (p_str.type() == typeid(wchar_t*)) {
					return std::any_cast<wchar_t*>(p_str);
				}
				return nullptr;
			}
			static wchar_t* To_WChar(const char* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WChar");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							return v_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static wchar_t* To_WChar(const std::string& p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg.empty()) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WChar");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t v_msg_size = p_msg.size() + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&v_chars_converted, v_msg, v_msg_size, p_msg.c_str(), v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							return v_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static wchar_t* To_WChar(const wchar_t* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WChar");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WChar");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(v_msg_size);
						
						for (size_t i = 0; i < v_msg_size; i++) {
							v_msg[i] = p_msg[i];
						}
						return v_msg;
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static char* Evaluate_Str(const std::any& p_str) {
				if (p_str.type() == typeid(const char*)) {
					return (char*)(std::any_cast<const char*>(p_str));
				}
				if (p_str.type() == typeid(std::string)) {
					return To_Char(std::any_cast<std::string>(p_str).c_str());
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					return To_Char(std::any_cast<const wchar_t*>(p_str));
				}
				if (p_str.type() == typeid(std::wstring)) {
					return To_Char(std::any_cast<std::wstring>(p_str));
				}
				if (p_str.type() == typeid(char*)) {
					return std::any_cast<char*>(p_str);
				}
				return nullptr;
			}
			static char* To_Char(const wchar_t* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_Char");
				}
				else {
					try {
						// Get the msg size 
						TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_Char");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_Char");
						}
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							return v_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: wcstombs_s", EXCEPTION_LINE,
								__FILEW__, L"To_Char");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static char* To_Char(const std::wstring& p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg.empty()) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_Char");
				}
				else {
					try {
						// Get the msg size 
						TRY_LINE size_t v_msg_size = p_msg.size() + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_Char");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&v_chars_converted, v_msg, v_msg_size, p_msg.c_str(), v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_Char");
						}
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							return v_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: wcstombs_s", EXCEPTION_LINE,
								__FILEW__, L"To_Char");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static char* To_Char(const char* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_Char");
				}
				else {
					try {
						// Get the msg size 
						TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_Char");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(v_msg_size);
						
						for (size_t i = 0; i < v_msg_size; i++) {
							v_msg[i] = p_msg[i];
						}
						
						return v_msg;
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static std::wstring Evaluate_TWStr(const std::any& p_str) {
				if (p_str.type() == typeid(const char*)) {
					return To_WString(std::any_cast<const char*>(p_str));
				}
				if (p_str.type() == typeid(std::string)) {
					return To_WString(std::any_cast<std::string>(p_str));
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					return std::wstring(std::any_cast<const wchar_t*>(p_str));
				}
				if (p_str.type() == typeid(std::wstring)) {
					return std::any_cast<std::wstring>(p_str);
				}
				return std::wstring();
			}
			static std::wstring To_WString(const char* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WString");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WString");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_WString");
						}
						std::wstring v_formated_msg{};
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							v_formated_msg.append(v_msg);
							if (pw::Engine_Memory::Deallocate<wchar_t>(v_msg) == false) {
								if (v_msg != nullptr) {
									delete[] v_msg;
									v_msg = nullptr;
								}
							}

							return v_formated_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", EXCEPTION_LINE, __FILEW__, L"To_WString");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static std::wstring To_WString(const std::string& p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg.empty()) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WString");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t v_msg_size = p_msg.size() + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_WString");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&v_chars_converted, v_msg, v_msg_size, p_msg.c_str(), v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_WString");
						}
						std::wstring v_formated_msg{};
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							v_formated_msg.append(v_msg);
							if (pw::Engine_Memory::Deallocate<wchar_t>(v_msg) == false) {
								if (v_msg != nullptr) {
									delete[] v_msg;
									v_msg = nullptr;
								}
							}

							return v_formated_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", EXCEPTION_LINE, __FILEW__, L"To_WString");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static std::string Evaluate_TStr(const std::any& p_str) {
				if (p_str.type() == typeid(const char*)) {
					return std::string(std::any_cast<const char*>(p_str));
				}
				if (p_str.type() == typeid(std::string)) {
					return std::any_cast<std::string>(p_str);
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					return To_String(std::any_cast<const wchar_t*>(p_str));
				}
				if (p_str.type() == typeid(std::wstring)) {
					return To_String(std::any_cast<std::wstring>(p_str));
				}
				return std::string();
			}
			static std::string To_String(const wchar_t* p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_String");
				}
				else {
					try {
						// Get the msg size 
						TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_String");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_String");
						}
						std::string v_formated_msg{};
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							v_formated_msg.append(v_msg);
							if (pw::Engine_Memory::Deallocate<char>(v_msg) == false) {
								if (v_msg != nullptr) {
									delete[] v_msg;
									v_msg = nullptr;
								}
							}

							return v_formated_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: wcstombs_s", EXCEPTION_LINE, __FILEW__, L"To_String");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static std::string To_String(const std::wstring& p_msg) {
				// Check if the characters exist
				if (TRY_LINE p_msg.empty()) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_String");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t v_msg_size = p_msg.size() + 1;
						if (v_msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", EXCEPTION_LINE, __FILEW__, L"To_String");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(v_msg_size);
						size_t v_chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&v_chars_converted, v_msg, v_msg_size, p_msg.c_str(), v_msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", EXCEPTION_LINE, __FILEW__, L"To_String");
						}
						std::string v_formated_msg{};
						// If we converted all of the memory correctly then return the result
						if (v_chars_converted == v_msg_size) {
							v_formated_msg.append(v_msg);
							if (pw::Engine_Memory::Deallocate<char>(v_msg) == false) {
								if (v_msg != nullptr) {
									delete[] v_msg;
									v_msg = nullptr;
								}
							}

							return v_formated_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", EXCEPTION_LINE, __FILEW__, L"To_String");
						}
					}
					catch (const pw::er::Warning_Error& v_error) {
						throw v_error;
					}
					catch (const pw::er::Severe_Error& v_error) {
						throw v_error;
					}
				}
			}
			static void Calc_Elapsed_Time(GLFWwindow* p_main_window) {
				if (p_main_window == nullptr) {
					throw std::invalid_argument("p_main_window");
				}
				else {
					try {
						m_start_time = m_end_time;

						m_elapsed_time += m_delta_time;
						if (m_elapsed_time >= std::chrono::milliseconds(1000)) {
							if (m_fps_max < m_frames) {
								m_fps_max = m_frames;
							}
							if (m_fps_averager.size() != 60) {
								m_fps_averager.push_back(m_frames);

								size_t v_fps_average = 0;
								for (size_t i = 0; i < m_fps_averager.size(); i++) {
									v_fps_average = v_fps_average + m_fps_averager.at(i);
								}
								m_fps_average = (float)v_fps_average / (float)m_fps_averager.size();
							}
							else {
								m_fps_averager.erase(m_fps_averager.begin());
								m_fps_averager.push_back(m_frames);

								size_t v_fps_average = 0;
								for (size_t i = 0; i < m_fps_averager.size(); i++) {
									v_fps_average = v_fps_average + m_fps_averager.at(i);
								}
								m_fps_average = (float)v_fps_average / (float)m_fps_averager.size();
							}
							m_elapsed_time = std::chrono::system_clock::duration();

							#ifdef PW_DEBUG_MODE
								if (m_debug_info != nullptr) {
									m_debug_info();
								}
							#endif
							m_last_frames = m_frames;
							m_frames = 0;
						}
					}
					catch (const std::bad_alloc& error) {
						throw error;
					}
					catch (const std::length_error& error) {
						throw error;
					}
					catch (const std::invalid_argument& error) {
						throw error;
					}
					catch (const std::exception& error) {
						throw error;
					}
				}
			}
			static inline void Wait() {
				// Increment frame since frame is over
				m_frames = m_frames + 1;
				m_end_time = std::chrono::system_clock::now();
				m_delta_time = m_end_time - m_start_time;
				if (m_vsync != true) {
					while ((std::chrono::system_clock::now() - m_end_time) < (std::chrono::milliseconds((1000 / m_fps_cap) * 2) - m_delta_time));
				}
			}
			//////////////////////////////////
			// Window
			//////////////////////////////////
			static inline const int32_t& Window_Width() {
				return m_window_width;
			}
			static inline void Set_Window_Width(const uint32_t& p_window_width) {
				if (p_window_width == 0) {
					throw std::invalid_argument("p_window_width");
				}
				else {
					m_window_width = p_window_width;
				}
			}
			static inline const int32_t& Window_Height() {
				return m_window_height;
			}
			static inline void Set_Window_Height(const uint32_t& p_window_height) {
				if (p_window_height == 0) {
					throw std::invalid_argument("p_window_height");
				}
				else {
					m_window_height = p_window_height;
				}
			}
			static inline const int32_t& Hafe_Window_Width() {
				return m_hafe_window_width;
			}
			static inline void Set_Hafe_Window_Width(const uint32_t& p_hafe_window_width) {
				if (p_hafe_window_width == 0) {
					throw std::invalid_argument("p_hafe_window_width");
				}
				else {
					m_hafe_window_width = p_hafe_window_width;
				}
			}
			static inline const int32_t& Hafe_Window_Height() {
				return m_hafe_window_height;
			}
			static inline void Set_Hafe_Window_Height(const uint32_t& p_hafe_window_height) {
				if (p_hafe_window_height == 0) {
					throw std::invalid_argument("p_hafe_window_height");
				}
				else {
					m_hafe_window_height = p_hafe_window_height;
				}
			}
			static inline const std::wstring& Window_Name() {
				return m_window_name;
			}
			static inline void Set_Window_Name(const std::wstring& p_window_name) {
				if (p_window_name.size() == 0) {
					throw std::invalid_argument("p_window_name");
				}
				else {
					try {
						std::string v_window_name = To_String(p_window_name);

						if (m_current_window != nullptr) {
							glfwSetWindowTitle(&**m_current_window, v_window_name.c_str());
						}
						m_window_name = p_window_name;
					}
					catch (const std::bad_alloc& v_error) {
						throw v_error;
					}
					catch (const std::length_error& v_error) {
						throw v_error;
					}
					catch (const std::invalid_argument& v_error) {
						throw v_error;
					}
					catch (const std::exception& v_error) {
						throw v_error;
					}
				}
			}
			static inline std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>* Window() {
				return m_current_window;
			}
			static inline void Set_Window(std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>* p_window) {
				if (p_window == nullptr) {
					throw std::invalid_argument("p_window");
				}
				else {
					m_current_window = p_window;
				}
			}
			//////////////////////////////////
			// Fps / Monitor
			//////////////////////////////////
			static inline const int32_t& FPS() {
				return m_frames;
			}
			static inline const int32_t& Last_FPS() {
				return m_last_frames;
			}
			static inline const int32_t& FPS_Max() {
				return m_fps_max;
			}
			static inline const float& FPS_Average() {
				return m_fps_average;
			}
			static inline const int32_t& FPS_Cap() {
				return m_fps_cap;
			}
			static inline const bool& Vsync() {
				return m_vsync;
			}
			static inline const int32_t& Refresh_Rate() {
				return m_refresh_rate;
			}
			static inline void Set_Refresh_Rate(const int32_t& p_refresh_rate) {
				m_refresh_rate = p_refresh_rate;
			}
			static inline void Set_FPS_Info(const int32_t& p_fps_cap, const bool& p_has_vsync) {
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
			static inline const std::chrono::system_clock::duration& Delta_Time() {
				return m_delta_time;
			}
			static inline const std::chrono::system_clock::time_point& Current_Time() {
				return m_start_time;
			}
			//////////////////////////////////
			// Mouse
			//////////////////////////////////
			static inline const int32_t& Mouse_X_Coord() {
				return m_mouse_x_position;
			}
			static inline const int32_t& Mouse_Y_Coord() {
				return m_mouse_y_position;
			}
			static inline const double& Mouse_X_Coord_Raw() {
				return m_mouse_x_position_raw;
			}
			static inline const double& Mouse_Y_Coord_Raw() {
				return m_mouse_y_position_raw;
			}
			static inline const glm::vec2 Mouse_Coord() {
				return glm::vec2(TO_FLOAT(m_mouse_x_position), TO_FLOAT(m_mouse_y_position));
			}
			static inline const glm::vec2 Last_Mouse_Coord() {
				return glm::vec2(TO_FLOAT(m_last_mouse_x_position), TO_FLOAT(m_last_mouse_y_position));
			}
			static inline void Set_Mouse_Coord(const int32_t& p_x, const int32_t& p_y) {
				m_last_mouse_x_position = m_mouse_x_position;
				m_last_mouse_y_position = m_mouse_y_position;

				m_mouse_x_position = p_x;
				m_mouse_y_position = p_y;
			}
			static inline const glm::vec2 Mouse_Coord_Raw() {
				return glm::vec2(TO_FLOAT(m_mouse_x_position_raw), TO_FLOAT(m_mouse_y_position_raw));
			}
			static inline void Set_Mouse_Coord_Raw(const double& p_x, const double& p_y) {
				m_mouse_x_position_raw = p_x;
				m_mouse_y_position_raw = p_y;
			}
			//////////////////////////////////
			// Other
			//////////////////////////////////
			static inline const std::filesystem::path& Pistonworks_Path() {
				return m_pistonworks_path;
			}
			static inline const std::filesystem::path& Game_Path() {
				return m_game_path;
			}
			static inline const float& Inverse_Z_Tan() {
				return m_inverse_z_tan;
			}
			static inline const bool& Window_Lock() {
				return m_window_lock;
			}
			static inline void Set_Window_Lock(const bool& p_state) {
				m_window_lock = p_state;
			}
			static void Close_Engine() {
				glfwSetWindowShouldClose(&**cm::Engine_Constant::Window(), GLFW_TRUE);
			}
			#ifdef PW_DEBUG_MODE
				static inline void Set_Debug_Function(const PW_FUNCTION& p_new_function) {
					m_debug_info = p_new_function;
				}
			#endif // PW_DEBUG_MODE
			//////////////////////////////////
			// Release
			//////////////////////////////////
			static inline void Release_Constants() {
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
			static constexpr uint32_t PW_SCALE_FACTOR = 32;
			static constexpr uint32_t PW_FONT_RESOLUTION = 96;

			static constexpr uint32_t PW_SCROLL_WHEEL_FORWARD	= 0xa1;
			static constexpr uint32_t PW_SCROLL_WHEEL_BACKWARD	= 0xa2;
			static constexpr uint32_t PW_COLLISION_EVENT		= 0xa3;
			static constexpr uint32_t PW_CLICK_EVENT			= 0xa4;
			static constexpr uint32_t PW_HOVER_EVENT			= 0xa5;
			static constexpr uint32_t PW_ANIMATION_START_EVENT	= 0xa6;
			static constexpr uint32_t PW_ANIMATION_END_EVENT	= 0xa7;
			static constexpr uint32_t PW_SOUND_START_EVENT		= 0xa8;
			static constexpr uint32_t PW_SOUND_END_EVENT		= 0xa9;
			static constexpr uint32_t PW_MOUSE_EVENT			= 0xaa;
			static constexpr uint32_t PW_KEYBOARD_EVENT			= 0xab;
			static constexpr uint32_t PW_SCROLL_EVENT			= 0xac;
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			// Window's current width
			static int32_t m_window_width;
			// Window's current height
			static int32_t m_window_height;
			// Haft of the Window's current width
			static int32_t m_hafe_window_width;
			// Haft of the Window's current height
			static int32_t m_hafe_window_height;
			// Window's current name
			static std::wstring m_window_name;
			// The current window
			static std::unique_ptr<GLFWwindow, Destroy_GLFW>* m_current_window;

			static int32_t m_frames;
			static int32_t m_last_frames;
			static int32_t m_fps_max;
			static std::vector<int32_t> m_fps_averager;
			static float m_fps_average;
			static int32_t m_fps_cap;
			static bool m_vsync;
			static int32_t m_refresh_rate;

			static std::chrono::system_clock::time_point m_start_time;
			static std::chrono::system_clock::time_point m_end_time;
			// The current delta time in the engine represented by milliseconds
			static std::chrono::system_clock::duration m_delta_time;
			static std::chrono::system_clock::duration m_elapsed_time;

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
	//////////////////////////////////
	CM_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONSTANT