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
#ifndef H_ENGINE_CONSTANT
#define H_ENGINE_CONSTANT
//////////////////////////////////
// // TEMP https://github.com/jbeder/yaml-cpp
// https://github.com/ben-strasser/fast-cpp-csv-parser
// #FILE_INFO#
// +(HEADER_ONLY)
// +(Disabled Warnings)
#pragma warning(push)
#pragma warning(disable:4267)
#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(push)
#pragma warning(disable:6385)
#pragma warning(push)
#pragma warning(disable:6386)
#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(push)
#pragma warning(disable:26451)
#pragma warning(push)
#pragma warning(disable:4003)
//////////////////////////////////
// C++ Headers
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <memory>
#include <utility>
#include <functional>
#include <stdint.h>
#include <any>
#include <tuple>
#include <functional>
//////////////////////////////////
// Project Headers
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H
#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_exception.h"
#include "engine_common\engine_memory.h"
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
	// Type Def	

	typedef uint64_t					PW_ID;
	typedef int32_t						PW_INPUT_TYPE;
	typedef int32_t						PW_KEY_CODE;
	typedef int32_t						PW_BUTTON_CODE;
	typedef int32_t						PW_SCROLL_ACTION;
	typedef int32_t						PW_COMPLEX_EVENT;
	typedef int32_t						PW_COMPLEX_EVENT;
	typedef int32_t						PW_EVENT_ID;
	typedef int32_t						PW_FONT_ID;
	typedef int32_t						PW_TRIGGER;
	typedef int32_t						PW_STATE;
	typedef const wchar_t*				PW_NAME_ID;
	typedef std::tuple<bool,
		std::wstring, std::vector<std::tuple<std::wstring, bool>>>	
										PW_PROJECT_FILE;

	typedef std::function<void()>		PW_FUNCTION;
												
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	CM_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// PW_COMMON_API Class: pw::co::Engine_Constant
		// //////////////////////////////////////////////////
		// Purpose:
		//  A static class for
		//  holding cross engine data
		//  values.
		// //////////////////////////////////////////////////
		class PW_COMMON_API Engine_Constant {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// PW_COMMON_API Struct: pw::co::Destroy_GLFW
			// //////////////////////////////////////////////////
			// Purpose:
			//  Destroys GLFW though a function operator call.
			// //////////////////////////////////////////////////
			struct PW_COMMON_API Destroy_GLFW {
				public:
					void operator()(GLFWwindow* p_window) {
						glfwDestroyWindow(p_window);
					}
			};
		private:
		// Public Functions/Macros 
		public:
			#define TO_WCHAR(str)			pw::cm::Engine_Constant::To_WChar(str)
			#define TO_CHAR(str)			pw::cm::Engine_Constant::To_Char(str)
			#define TO_WSTRING(str)			pw::cm::Engine_Constant::Evaluate_TWStr(str)
			#define TO_STRING(str)			pw::cm::Engine_Constant::Evaluate_TStr(str)

			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::To_WChar
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a const char* to a wchar_t*, must be
			//  deallocated.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const char* msg;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE wchar_t* To_WChar(const char* msg) {
				// Check if the characters exist
				if (TRY_LINE msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_WChar");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t msg_size = std::strlen(msg) + 1;
						if (msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_WChar");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(wchar_t(), msg_size);
						size_t chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&chars_converted, v_msg, msg_size, msg, msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", std::move(EXCEPTION_LINE), __FILEW__, L"To_WChar");
						}
						// If we converted all of the memory correctly then return the result
						if (chars_converted == msg_size) {
							return v_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", std::move(EXCEPTION_LINE), __FILEW__, L"To_WChar");
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
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::To_Char
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a const wchar_t* to a char*, must be
			//  deallocated.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* msg;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE char* To_Char(const wchar_t* msg) {
				// Check if the characters exist
				if (TRY_LINE msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_Char");
				}
				else {
					try {
						// Get the msg size 
						TRY_LINE size_t msg_size = std::wcslen(msg) + 1;
						if (msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_Char");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(char(), msg_size);
						size_t chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&chars_converted, v_msg, msg_size, msg, msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", std::move(EXCEPTION_LINE), __FILEW__, L"To_Char");
						}
						// If we converted all of the memory correctly then return the result
						if (chars_converted == msg_size) {
							return v_msg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: wcstombs_s", std::move(EXCEPTION_LINE),
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
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::Evaluate_TWStr
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a char string to a wchar_t string.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) std::any str;
			// Purpose:
			//  The message to be converted. Must be a string
			//  type. 
			// //////////////////////////////////////////////////
			static CORE std::wstring Evaluate_TWStr(std::any str) {
				if (str.type() == typeid(const char*)) {
					return To_WString(std::any_cast<const char*>(str));
				}
				if (str.type() == typeid(std::string)) {
					return To_WString(std::any_cast<std::string>(str));
				}
				if (str.type() == typeid(const wchar_t*)) {
					return std::wstring(std::any_cast<const wchar_t*>(str));
				}
				if (str.type() == typeid(std::wstring)) {
					return std::any_cast<std::wstring>(str);
				}
				return std::wstring();
			}
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::To_WString
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a const char* to a std::wstring.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const char* msg;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE std::wstring To_WString(const char* msg) {
				// Check if the characters exist
				if (TRY_LINE msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t msg_size = std::strlen(msg) + 1;
						if (msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(wchar_t(), msg_size);
						size_t chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&chars_converted, v_msg, msg_size, msg, msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
						}
						std::wstring v_smsg{};
						// If we converted all of the memory correctly then return the result
						if (chars_converted == msg_size) {
							v_smsg.append(v_msg);
							pw::Engine_Memory::Deallocate<wchar_t>(v_msg);

							return v_smsg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
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
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::To_WString
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a std::string to a std::wstring.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) std::string msg;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE std::wstring To_WString(std::string msg) {
				// Check if the characters exist
				if (TRY_LINE msg.empty()) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t msg_size = msg.size() + 1;
						if (msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
						}
						// Allocate the memory for the new msg
						wchar_t* v_msg = pw::Engine_Memory::Allocate<wchar_t>(wchar_t(), msg_size);
						size_t chars_converted = 0;
						// Convert the memory
						if (TRY_LINE mbstowcs_s(&chars_converted, v_msg, msg_size, msg.c_str(), msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
						}
						std::wstring v_smsg{};
						// If we converted all of the memory correctly then return the result
						if (chars_converted == msg_size) {
							v_smsg.append(v_msg);
							pw::Engine_Memory::Deallocate<wchar_t>(v_msg);

							return v_smsg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", std::move(EXCEPTION_LINE), __FILEW__, L"To_WString");
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
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::Evaluate_TStr
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a wchar_t string to a char string.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) std::any str;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE std::string Evaluate_TStr(std::any str) {
				if (str.type() == typeid(const char*)) {
					return std::string(std::any_cast<const char*>(str));
				}
				if (str.type() == typeid(std::string)) {
					return std::any_cast<std::string>(str);
				}
				if (str.type() == typeid(const wchar_t*)) {
					return To_String(std::any_cast<const wchar_t*>(str));
				}
				if (str.type() == typeid(std::wstring)) {
					return To_String(std::any_cast<std::wstring>(str));
				}
				return std::string();
			}
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::To_String
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a const wchar_t* to a std::string.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const char* msg;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE std::string To_String(const wchar_t* msg) {
				// Check if the characters exist
				if (TRY_LINE msg == nullptr) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
				}
				else {
					try {
						// Get the msg size 
						TRY_LINE size_t msg_size = std::wcslen(msg) + 1;
						if (msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(char(), msg_size);
						size_t chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&chars_converted, v_msg, msg_size, msg, msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
						}
						std::string v_smsg{};
						// If we converted all of the memory correctly then return the result
						if (chars_converted == msg_size) {
							v_smsg.append(v_msg);
							pw::Engine_Memory::Deallocate<char>(v_msg);

							return v_smsg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: wcstombs_s", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
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
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::To_String
			// //////////////////////////////////////////////////
			// Purpose:
			//  Converts a std::wstring to a std::string.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) std::wstring msg;
			// Purpose:
			//  The message to be converted. 
			// //////////////////////////////////////////////////
			static CORE std::string To_String(std::wstring msg) {
				// Check if the characters exist
				if (TRY_LINE msg.empty()) {
					throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
				}
				else {
					try {
						// Get the msg size
						TRY_LINE size_t msg_size = msg.size() + 1;
						if (msg_size == 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Invalid Argument", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
						}
						// Allocate the memory for the new msg
						char* v_msg = pw::Engine_Memory::Allocate<char>(char(), msg_size);
						size_t chars_converted = 0;
						// Convert the memory
						if (TRY_LINE wcstombs_s(&chars_converted, v_msg, msg_size, msg.c_str(), msg_size - 1) != 0) {
							throw pw::er::Warning_Error(L"Engine Constant", L"Destination buffer is too small", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
						}
						std::string v_smsg{};
						// If we converted all of the memory correctly then return the result
						if (chars_converted == msg_size) {
							v_smsg.append(v_msg);
							pw::Engine_Memory::Deallocate<char>(v_msg);

							return v_smsg;
						}
						else {
							throw pw::er::Warning_Error(L"Engine Constant", L"Function Failed: mbstowcs_s", std::move(EXCEPTION_LINE), __FILEW__, L"To_String");
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
		// Accessors
			USER_INTERACTION
			static ACCESSOR const int32_t& Window_Width() {
				return m_window_width;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& Window_Height() {
				return m_window_height;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& Hafe_Window_Width() {
				return m_hafe_window_width;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& Hafe_Window_Height() {
				return m_hafe_window_height;
			}
			USER_INTERACTION
			static ACCESSOR const wchar_t*& Window_Name() {
				return m_window_name;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& Mouse_X_Coord() {
				return m_mouse_x_position;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& Mouse_Y_Coord() {
				return m_mouse_y_position;
			}
			USER_INTERACTION
			static ACCESSOR const float& Inverse_Z_Tan() {
				return m_inverse_z_tan;
			}
			USER_INTERACTION
			static ACCESSOR const glm::vec2& Gravity() {
				return m_physics_gravity;
			}
			USER_INTERACTION
			static ACCESSOR PW_DUNI_PTR(GLFWwindow, Destroy_GLFW)* Window() {
				return &m_current_window;
			}
			USER_INTERACTION
			static ACCESSOR const float& Delta_Time() {
				return m_delta_time;
			}
			USER_INTERACTION
			static ACCESSOR const std::clock_t& Current_Time() {
				return m_start_time;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& FPS_Max() {
				return m_fps_max;
			}
			USER_INTERACTION
			static ACCESSOR const float& FPS_Average() {
				return m_fps_average;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& FPS() {
				return m_frames;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t& Last_FPS() {
				return m_last_frames;
			}
		// Mutators
			USER_INTERACTION
			static MUTATOR void Set_Window_Width(const uint32_t&& p_window_width) {
				if (p_window_width == 0) {
					throw std::invalid_argument("p_window_width");
				}
				else {
					m_window_width = p_window_width;
				}
			}
			USER_INTERACTION
			static MUTATOR void Set_Window_Height(const uint32_t&& p_window_height) {
				if (p_window_height == 0) {
					throw std::invalid_argument("p_window_height");
				}
				else {
					m_window_height = p_window_height;
				}	
			}
			USER_INTERACTION
			static MUTATOR void Set_Hafe_Window_Width(const uint32_t&& p_hafe_window_width) {
				if (p_hafe_window_width == 0) {
					throw std::invalid_argument("p_hafe_window_width");
				}
				else {
					m_hafe_window_width = p_hafe_window_width;
				}
			}
			USER_INTERACTION
			static MUTATOR void Set_Hafe_Window_Height(const uint32_t&& p_hafe_window_height) {
				if (p_hafe_window_height == 0) {
					throw std::invalid_argument("p_hafe_window_height");
				}
				else {
					m_hafe_window_height = p_hafe_window_height;
				}
			}
			USER_INTERACTION
			static MUTATOR void Set_Window_Name(const wchar_t* p_window_name) {
				if (p_window_name == nullptr || std::wcslen(p_window_name) == 0) {
					throw std::invalid_argument("p_hafe_window_height");
				}
				else {
					try {
						std::string v_window_name = To_String(p_window_name);

						glfwSetWindowTitle(m_current_window.get(), v_window_name.c_str());
						m_window_name = p_window_name;
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
			USER_INTERACTION
			static MUTATOR void Set_Window(GLFWwindow* p_window) {
				if (p_window == nullptr) {
					throw std::invalid_argument("p_window");
				}
				else {
					m_current_window = std::unique_ptr<GLFWwindow, Destroy_GLFW>(p_window);
				}
			}
			USER_INTERACTION
			static MUTATOR void Set_Mouse_Coords(const int32_t&& p_x, const int32_t&& p_y) {
				m_mouse_x_position = p_x;
				m_mouse_y_position = p_y;
			}
			USER_INTERACTION
			static MUTATOR void Set_Debug_Function(const PW_FUNCTION&& p_new_function) {
				m_debug_info = p_new_function;
			}
		// Public Variables
		public:
			static constexpr uint32_t PW_SCALE_FACTOR = 32;
			static constexpr uint32_t PW_FONT_RESOLUTION = 48;

			static constexpr uint32_t PW_PLAYER_ID = 0xff;

			static constexpr uint32_t PW_SCROLL_WHEEL_FORWARD = 0xa1;
			static constexpr uint32_t PW_SCROLL_WHEEL_BACKWARD = 0xa2;

			static constexpr uint32_t PW_CONDIONAL_EVENT = 0xb1;
			static constexpr uint32_t PW_ACONDIONAL_EVENT = 0xb2;
			// When the model collides with a specified actor, or any actor
			static constexpr uint32_t PW_COLLISION_EVENT = 0xb3;
			// When the mouse is clicked over the area that contains the actor's model
			static constexpr uint32_t PW_CLICK_EVENT = 0xb4;
			// When the mouse is over the area that contains the actor's model
			static constexpr uint32_t PW_HOVER_EVENT = 0xb5;
			// For the reading of the different types of events
			static constexpr uint32_t PW_MOUSE_EVENT = 0xf0;
			static constexpr uint32_t PW_KEYBOARD_EVENT = 0xf1;
			static constexpr uint32_t PW_SCROLL_EVENT = 0xf2;
		// Protected Functions/Macros
		protected:
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::Calc_Delta_Time
			// //////////////////////////////////////////////////
			// Purpose: 
			//  This function calculates the current
			//	delta time for the engine and makes sure 
			//	key systems run at a set rate.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Calc_Delta_Time() {
				m_delta_time = static_cast<float>(std::abs(m_end_time - m_start_time)) / 1000.0f;
				m_start_time = m_end_time;
			}
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::Calc_Elapsed_Time
			// //////////////////////////////////////////////////
			// Purpose: Sets the windows fps for the engine.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) GLFWwindow* main_window;
			// Purpose: 
			//  It is the main window of the application
			//  that is used to set the window's title
			//  fps.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Calc_Elapsed_Time(GLFWwindow* p_main_window) {
				if (p_main_window == nullptr) {
					throw std::invalid_argument("p_main_window");
				}
				else {
					try {
						m_elapsed_time += m_delta_time;
						if (m_elapsed_time >= 1.0f) {
							if (m_fps_max < m_frames) {
								m_fps_max = m_frames;
							}
							if (m_fps_averager.size() != 60) {
								m_fps_averager.push_back(m_frames);
							}
							else {
								size_t v_fps_average = 0;
								for (size_t i = 0; i < m_fps_averager.size(); i++) {
									v_fps_average = v_fps_average + m_fps_averager.at(i);
								}
								m_fps_average = (float)v_fps_average / (float)m_fps_averager.size();
								m_fps_averager.clear();
							}
							m_elapsed_time = 0;

							m_debug_info();
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
			// //////////////////////////////////////////////////
			// CORE Function: Engine_Constant::Wait
			// //////////////////////////////////////////////////
			// Purpose:
			//  The engine holds the fps back for
			//  consistent fps.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Wait() {
				m_frames = m_frames + 1; // Increment frame since frame is over

				m_end_time = std::clock();
				if (m_end_time == -1) {
					throw std::exception("Function Failed: std::clock");
				}
			}
		// Protected Variables
		public:
			// Window's current width
			static int32_t m_window_width;
			// Window's current height
			static int32_t m_window_height;
			// Haft of the Window's current width
			static int32_t m_hafe_window_width;
			// Haft of the Window's current height
			static int32_t m_hafe_window_height;
			// Window's current name
			static const wchar_t* m_window_name;
			// The current window
			static PW_DUNI_PTR(GLFWwindow, Destroy_GLFW) m_current_window;

			static int32_t m_frames;
			static int32_t m_last_frames;
			static bool m_engine_start;

			static std::clock_t m_start_time;
			static std::clock_t m_end_time;
			// The current delta time in the engine represented by milliseconds
			static float m_delta_time;
			static float m_elapsed_time;

			static int32_t m_fps_max;
			static std::vector<int16_t> m_fps_averager;
			static float m_fps_average;

			static int32_t m_mouse_x_position;
			static int32_t m_mouse_y_position;

			static const float m_inverse_z_tan;
			static const glm::vec2 m_physics_gravity;

			#ifdef PW_DEBUG_MODE
				static PW_FUNCTION m_debug_info;
			#endif
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	CM_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONSTANT