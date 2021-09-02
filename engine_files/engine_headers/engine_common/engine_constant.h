#ifndef H_ENGINE_CONSTANT
#define H_ENGINE_CONSTANT
//////////////////////////////////
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
#define PW_INTERNAL_DATA_API
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
// Re def for different window name, or change in file system
#define PW_APP_NANE (pw::PW_CSTRING)"Pistonworks Window"
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	// Type Def	
	#ifdef _WIN64
		typedef signed	 __int16			PW_SINT;
		typedef signed	 __int32			PW_INT;
		typedef signed	 __int32			PW_LINT;
		typedef signed	 __int64			PW_LLINT;
		typedef unsigned __int16 			PW_SUINT;
		typedef unsigned __int32			PW_UINT;
		typedef unsigned __int32			PW_LUINT;
		typedef unsigned __int64 			PW_LLUINT;

		typedef unsigned __int64			PW_SIZE;
	#else 
		#ifdef _WIN32
			typedef signed short int		PW_SINT;
			typedef signed int				PW_INT;
			typedef signed long int			PW_LINT;
			typedef signed long long int	PW_LLINT;
			typedef unsigned short int		PW_SUINT;
			typedef unsigned int			PW_UINT;
			typedef unsigned long int		PW_LUINT;
			typedef unsigned long long int	PW_LLUINT;

			typedef size_t					PW_SIZE;
		#endif
	#endif
		typedef std::string					PW_STRING;
	#if _UNICODE  
		typedef char						PW_CHAR;
		typedef const char* PW_CSTRING;
		typedef char* PW_CHAR_PTR;
	#else
		#if _MBCS
			typedef wchar_t					PW_CHAR;
			typedef const wchar_t*			PW_CSTRING;
		#endif
	#endif
	typedef float						PW_FLOAT;
	typedef double						PW_DOUBLE;
	typedef long double					PW_LDOUBLE;

	typedef void						PW_VOID;
	typedef void*						PW_TYPE;

	typedef bool						PW_BOOL;
	typedef bool						PW_FLAG;
	typedef unsigned char				PW_BYTE;

	typedef PW_INT						PW_ID;
	typedef PW_INT						PW_INPUT_TYPE;
	typedef PW_INT						PW_KEY_CODE;
	typedef PW_INT						PW_BUTTON_CODE;
	typedef PW_INT						PW_SCROLL_ACTION;
	typedef PW_INT						PW_COMPLEX_EVENT;
	typedef PW_INT						PW_COMPLEX_EVENT;
	typedef PW_INT						PW_EVENT_ID;
	typedef PW_INT						PW_FONT_ID;
	typedef PW_INT						PW_TRIGGER;
	typedef PW_INT						PW_STATE;
	typedef PW_CSTRING					PW_NAME_ID;

	typedef std::function<PW_VOID()>	PW_FUNCTION;
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
			// PW_INTERNAL_DATA_API Struct: pw::co::Destroy_GLFW
			// //////////////////////////////////////////////////
			// Purpose:
			//  Destroys GLFW though a function operator call.
			// //////////////////////////////////////////////////
			struct PW_INTERNAL_DATA_API Destroy_GLFW {
				public:
					PW_VOID operator()(GLFWwindow* window) {
						glfwDestroyWindow(window);
					}
			};
		private:
		// Public Functions/Macros 
		public:
			#define PW_SRD_PTR(type)									std::shared_ptr<type>
			#define PW_UNI_PTR(type)									std::unique_ptr<type>
			#define PW_DUNI_PTR(type, deleter)							std::unique_ptr<type, deleter>
			#define TO_INT(x)											static_cast<PW_INT>(x)
			#define TO_UINT(x)											static_cast<PW_UINT>(x)
			#define TO_LLINT(x)											static_cast<PW_LLINT>(x)
			#define TO_LLUINT(x)										static_cast<PW_LLUINT>(x)
			#define VARIABLE_NAME(x)									static_cast<PW_CSTRING>(#x)
			#define OFF(x)												(x + 1)
			#define COMPLEX_FUNCTION_1(x_args)							std::function<PW_VOID(x_args)>
			#define COMPLEX_FUNCTION_2(x_args, y_args)					std::function<PW_VOID(x_args, y_args)>
			#define COMPLEX_FUNCTION_3(x_args, y_args, z_args)			std::function<PW_VOID(x_args, y_args, z_args)>
			#define COMPLEX_FUNCTION_4(x_args, y_args, z_args, a_args)	std::function<PW_VOID(x_args, y_args, z_args, a_args)>
		// Accessors
			USER_INTERACTION
			static ACCESSOR const PW_INT Window_Width() {
				return window_width;
			}
			USER_INTERACTION
			static ACCESSOR const PW_INT Window_Height() {
				return window_height;
			}
			USER_INTERACTION
			static ACCESSOR const PW_INT Hafe_Window_Width() {
				return hafe_window_width;
			}
			USER_INTERACTION
			static ACCESSOR const PW_INT Hafe_Window_Height() {
				return hafe_window_height;
			}
			USER_INTERACTION
			static ACCESSOR const PW_CSTRING Window_Name() {
				return window_name;
			}
			USER_INTERACTION
			static ACCESSOR const PW_INT Mouse_X_Coord() {
				return mouse_x_position;
			}
			USER_INTERACTION
			static ACCESSOR const PW_INT Mouse_Y_Coord() {
				return mouse_y_position;
			}
			USER_INTERACTION
			static ACCESSOR const PW_FLOAT Inverse_Z_Tan() {
				return inverse_z_tan;
			}
			USER_INTERACTION
			static ACCESSOR const glm::vec2 Gravity() {
				return physics_gravity;
			}
			USER_INTERACTION
			static ACCESSOR const PW_DUNI_PTR(GLFWwindow, Destroy_GLFW)* Window() {
				return current_window;
			}
			USER_INTERACTION
			static ACCESSOR const PW_FLOAT Delta_Time() {
				return delta_time;
			}
			USER_INTERACTION
			static ACCESSOR const std::clock_t Current_Time() {
				return start_time;
			}
			USER_INTERACTION
			static ACCESSOR const PW_FLOAT FPS_Constant() {
				return fps_constant;
			}
			USER_INTERACTION
			static ACCESSOR const PW_FLOAT FPS_Max() {
				return fps_max;
			}
		// Mutators
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Window_Width(const PW_INT* n_window_width) {
				window_width = *n_window_width;
			}
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Window_Height(const PW_INT* n_window_height) {
				window_height = *n_window_height;
			}
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Hafe_Window_Width(const PW_INT* n_hafe_window_width) {
				hafe_window_width = *n_hafe_window_width;
			}
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Hafe_Window_Height(const PW_INT* n_hafe_window_height) {
				hafe_window_height = *n_hafe_window_height;
			}
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Window_Name(const PW_CSTRING* n_window_name) {
				glfwSetWindowTitle((*current_window).get(), *n_window_name);
				window_name = *n_window_name;
			}
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Window(const GLFWwindow* window) {
				current_window = &PW_DUNI_PTR(GLFWwindow, Engine_Constant::Destroy_GLFW)((GLFWwindow*)window);
			}
			USER_INTERACTION
			static MUTATOR PW_VOID Set_Mouse_Coords(const PW_INT x, const PW_INT y) {
				mouse_x_position = x;
				mouse_y_position = y;
			}
		// Public Variables
		public:
			static constexpr PW_INT PW_SCALE_FACTOR = 32;
			static constexpr PW_INT PW_FONT_RESOLUTION = 256;

			static constexpr PW_INT PW_PLAYER_ID = 0xff;

			static constexpr PW_INT PW_SCROLL_WHEEL_FROWARD = 0xa1;
			static constexpr PW_INT PW_SCROLL_WHEEL_BACKWARD = 0xa2;

			static constexpr PW_INT PW_CONDIONAL_EVENT = 0xb1;
			static constexpr PW_INT PW_ACONDIONAL_EVENT = 0xb2;
			// When the model collides with a specified actor, or any actor
			static constexpr PW_INT PW_COLLISION_EVENT = 0xb3;
			// When the mouse is clicked over the area that contains the actor's model
			static constexpr PW_INT PW_CLICK_EVENT = 0xb4;
			// When the mouse is over the area that contains the actor's model
			static constexpr PW_INT PW_HOVER_EVENT = 0xb5;
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
			static CORE PW_VOID Calc_Delta_Time() {
				delta_time = static_cast<PW_FLOAT>(end_time - start_time) / 1000.0f;
				start_time = end_time;
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
			static CORE PW_VOID Calc_Elapsed_Time(GLFWwindow* main_window) {
				elapsed_time += delta_time;
				if (last_frames != frames) {
					if (elapsed_time >= 1.0f) {
						#ifdef PW_DEBUG_MODE
							std::string str = (const char*)Engine_Constant::Window_Name();
							str.insert(str.size(), " Fps:");
							str.insert(str.size(), std::to_string(frames));
							frames = 0;
							glfwSetWindowTitle(main_window, str.c_str());
						#endif // PW_DEBUG
						last_frames = frames;
						elapsed_time = 0;
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
			static CORE PW_VOID Wait() {
				frames = frames + 1; // Increment frame since frame is over
				/* Wait until next frame */
				std::this_thread::sleep_for(std::chrono::duration<PW_FLOAT, std::milli>(delta_time * 1000.0f));

				end_time = std::clock();
			}
		// Private Variables
		private:
			// Window's current width
			static PW_INT window_width;
			// Window's current height
			static PW_INT window_height;
			// Haft of the Window's current width
			static PW_INT hafe_window_width;
			// Haft of the Window's current height
			static PW_INT hafe_window_height;
			// Window's current name
			static PW_CSTRING window_name;
			// The current window
			static PW_DUNI_PTR(GLFWwindow, Destroy_GLFW)* current_window;

			static PW_INT frames;
			static PW_INT last_frames;
			static PW_BOOL engine_start;

			static std::clock_t start_time;
			static std::clock_t end_time;
			// The current delta time in the engine represented by milliseconds
			static PW_FLOAT delta_time;
			static PW_FLOAT elapsed_time;

			static const PW_FLOAT fps_max;
			// A constant bar for which the fps must abide to
			static const PW_FLOAT fps_constant;

			static PW_INT mouse_x_position;
			static PW_INT mouse_y_position;

			static const PW_FLOAT inverse_z_tan;
			static const glm::vec2 physics_gravity;
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