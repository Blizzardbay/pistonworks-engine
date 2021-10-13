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
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Macros

// Apart of the Engine Common Files
#define PW_COMMON_API
// Apart of the Engine Control Files
#define PW_CONTROL_API
// Apart of the Engine Structure Files
#define PW_STRUCTURES_API
// Apart of the Error.h header file
#define PW_ERROR_API
// Apart of the Internal Data structs
#define INTERNAL_DATA_API
// Standard PW Namespace
#define PW_NAMESPACE_SRT namespace pw {
#define PW_NAMESPACE_END }
// Standard Common Namespace
#define CM_NAMESPACE_SRT namespace cm {
#define CM_NAMESPACE_END }
// Standard Control Namespace
#define CO_NAMESPACE_SRT namespace co {
#define CO_NAMESPACE_END }
// Standard Structure Namespace
#define ST_NAMESPACE_SRT namespace st {
#define ST_NAMESPACE_END }
// Error namespace
#define ER_NAMESPACE_SRT namespace er {
#define ER_NAMESPACE_END }
// Enable Debug Features
#ifdef _DEBUG
#define PW_DEBUG_MODE
#endif // _DEBUG
// For different function types
// An ACCESSOR function returns the function's name as a variable to the user.
// EX. int c = 0;
// int C(); <- is a ACCESSOR
// int C(); returns the c variable 
#define ACCESSOR
// An MUTATOR function changes the function's name to a variable.
// EX. int c = 0;
// void C(int new_val); <- is a MUTATOR
// void C(int new_val); changes the c variable to new_val
#define MUTATOR
// A LOADER function loads something that is the function's name.
// EX. byte_data;
// byte_data Load_Byte_Data(string location); <- is a LOADER
// byte_data Load_Byte_Data(string location); loads byte_data from a certain file location
#define LOADER
// A CORE function is a function that is within the core functionality of the engine.
// This function usually has a description of what it does and what arguments passed to it do.
#define CORE
// A ERROR_HANDLE function is purely for error reporting to the user. They handle and send important
// error related information.
#define ERROR_HANDLE
// A UTILITY function is one that preforms a certain operation that is not necessarily a necessity inside the engine.
#define UTILITY
// A CLASS_FUCNTION is a operator , deconstructor or a constructor that the class has.
#define CLASS_FUNCTION
// The user is required to overload this function
#define OVERLOAD
// A function labeled with USER_INTERACTION can be used
#define USER_INTERACTION 
// A function labeled with NO_USER_INTERACTION should not be used.
#define NO_USER_INTERACTION
// A section of code that consists of only accessors
#define ACCESSORS
// A section of code that consists of only mutators
#define MUTATORS
// Lets C++ implement the function
#define LET_CPP_IMPLEMENT
// A root file is a file that does not include any other Pistonworks Engine headers
#define ROOT_FILE
// A root structure is a structure that does not include any other Pistonworks Engine structures
#define ROOT_STRUCTURE
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
		std::wstring, std::wstring>		PW_PROJECT_FILE;

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
			// INTERNAL_DATA_API Struct: pw::co::Destroy_GLFW
			// //////////////////////////////////////////////////
			// Purpose:
			//  Destroys GLFW though a function operator call.
			// //////////////////////////////////////////////////
			struct INTERNAL_DATA_API Destroy_GLFW {
				public:
					void operator()(GLFWwindow* p_window) {
						glfwDestroyWindow(p_window);
					}
			};
		private:
		// Public Functions/Macros 
		public:
			#define PW_SRD_PTR(type)									std::shared_ptr<type>
			#define PW_UNI_PTR(type)									std::unique_ptr<type>
			#define PW_DUNI_PTR(type, deleter)							std::unique_ptr<type, deleter>
			#define TO_32INT(x)											static_cast<int32_t>(x)
			#define TO_32UINT(x)										static_cast<uint32_t>(x)
			#define TO_64INT(x)											static_cast<int64_t>(x)
			#define TO_64UINT(x)										static_cast<uint64_t>(x)
			#define VARIABLE_NAME(x)									static_cast<const wchar_t*>(#x)
			#define OFF(x)												(x + 1)
			#define COMPLEX_FUNCTION_1(x_args)							std::function<void(x_args)>
			#define COMPLEX_FUNCTION_2(x_args, y_args)					std::function<void(x_args, y_args)>
			#define COMPLEX_FUNCTION_3(x_args, y_args, z_args)			std::function<void(x_args, y_args, z_args)>
			#define COMPLEX_FUNCTION_4(x_args, y_args, z_args, a_args)	std::function<void(x_args, y_args, z_args, a_args)>

			static wchar_t* To_WChar(const char* msg) {
				size_t msg_size = std::strlen(msg) + 1;
				wchar_t* v_msg = new wchar_t[msg_size];
				size_t chars_converted = 0;
				mbstowcs_s(&chars_converted, v_msg, msg_size, msg, SIZE_MAX);
				if (chars_converted == msg_size) {
					return v_msg;
				}
				else {
					return nullptr;
				}
			}
			static char* To_Char(const wchar_t* msg) {
				size_t msg_size = std::wcslen(msg) + 1;
				char* v_msg = new char[msg_size];
				size_t chars_converted = 0;
				wcstombs_s(&chars_converted, v_msg, msg_size, msg, SIZE_MAX);
				if (chars_converted == msg_size) {
					return v_msg;
				}
				else {
					return nullptr;
				}
			}
		// Accessors
			USER_INTERACTION
			static ACCESSOR const int32_t Window_Width() {
				return m_window_width;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t Window_Height() {
				return m_window_height;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t Hafe_Window_Width() {
				return m_hafe_window_width;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t Hafe_Window_Height() {
				return m_hafe_window_height;
			}
			USER_INTERACTION
			static ACCESSOR const wchar_t* Window_Name() {
				return m_window_name;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t Mouse_X_Coord() {
				return m_mouse_x_position;
			}
			USER_INTERACTION
			static ACCESSOR const int32_t Mouse_Y_Coord() {
				return m_mouse_y_position;
			}
			USER_INTERACTION
			static ACCESSOR const float Inverse_Z_Tan() {
				return m_inverse_z_tan;
			}
			USER_INTERACTION
			static ACCESSOR const glm::vec2 Gravity() {
				return m_physics_gravity;
			}
			USER_INTERACTION
			static ACCESSOR const PW_DUNI_PTR(GLFWwindow, Destroy_GLFW)* Window() {
				return &m_current_window;
			}
			USER_INTERACTION
			static ACCESSOR const float Delta_Time() {
				return m_delta_time;
			}
			USER_INTERACTION
			static ACCESSOR const std::clock_t Current_Time() {
				return m_start_time;
			}
			USER_INTERACTION
			static ACCESSOR const float FPS_Constant() {
				return m_fps_constant;
			}
			USER_INTERACTION
			static ACCESSOR const float FPS_Max() {
				return m_fps_max;
			}
		// Mutators
			USER_INTERACTION
			static MUTATOR void Set_Window_Width(const uint32_t* p_window_width) {
				m_window_width = *p_window_width;
			}
			USER_INTERACTION
			static MUTATOR void Set_Window_Height(const uint32_t* p_window_height) {
				m_window_height = *p_window_height;
			}
			USER_INTERACTION
			static MUTATOR void Set_Hafe_Window_Width(const uint32_t* p_hafe_window_width) {
				m_hafe_window_width = *p_hafe_window_width;
			}
			USER_INTERACTION
			static MUTATOR void Set_Hafe_Window_Height(const uint32_t* p_hafe_window_height) {
				m_hafe_window_height = *p_hafe_window_height;
			}
			USER_INTERACTION
			static MUTATOR void Set_Window_Name(const wchar_t* p_window_name) {
				char* v_window_name = To_Char(p_window_name);

				glfwSetWindowTitle(m_current_window.get(), v_window_name);
				m_window_name = p_window_name;

				delete[] v_window_name;
			}
			USER_INTERACTION
			static MUTATOR void Set_Window(GLFWwindow* p_window) {
				m_current_window = std::unique_ptr<GLFWwindow, Destroy_GLFW>(p_window);
			}
			USER_INTERACTION
			static MUTATOR void Set_Mouse_Coords(const int32_t p_x, const int32_t p_y) {
				m_mouse_x_position = p_x;
				m_mouse_y_position = p_y;
			}
		// Public Variables
		public:
			static constexpr uint32_t PW_SCALE_FACTOR = 32;
			static constexpr uint32_t PW_FONT_RESOLUTION = 256;

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
				m_delta_time = static_cast<float>(m_end_time - m_start_time) / 1000.0f;
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
				m_elapsed_time += m_delta_time;
				if (m_last_frames != m_frames) {
					if (m_elapsed_time >= 1.0f) {
						#ifdef PW_DEBUG_MODE
							std::wstring v_str = Engine_Constant::Window_Name();
							v_str.insert(v_str.size(), L" Fps:");
							v_str.insert(v_str.size(), std::to_wstring(m_frames));
							m_frames = 0;
							char* v_char_name = To_Char(v_str.c_str());
							glfwSetWindowTitle(p_main_window, v_char_name);
							delete[] v_char_name;
						#endif // PW_DEBUG
						m_last_frames = m_frames;
						m_elapsed_time = 0;
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
				/* Wait until next frame */
				//std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(m_delta_time * 1000.0f));

				m_end_time = std::clock();
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

			static const float m_fps_max;
			// A constant bar for which the fps must abide to
			static const float m_fps_constant;

			static int32_t m_mouse_x_position;
			static int32_t m_mouse_y_position;

			static const float m_inverse_z_tan;
			static const glm::vec2 m_physics_gravity;
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