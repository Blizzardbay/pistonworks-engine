#ifndef H_ENGINE_CONSTANT
#define H_ENGINE_CONSTANT
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
// +(Disabled Warnings)
#pragma warning(disable:4267)
#pragma warning(disable:4005)
#pragma warning(disable:6385)
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
// Engine Headers
//////////////////////////////////
// Engine Macro Includes
//////////////////////////////////
// Engine Macros

// Apart of the Engine Headers and Files
#define PW_ENGINE_API
// Apart of the Internal Headers and Files
#define PW_INTERNAL_API
// Apart of the Internal Data structs
#define PW_INTERNAL_DATA_API
// Standard pw namespace
#define PW_NAMESPACE_SRT namespace pw {
#define PW_NAMESPACE_END }
// Internal Engine namespace
#define IE_NAMESPACE_SRT namespace ie {
#define IE_NAMESPACE_END }
// Enable Debug Features
#ifdef _DEBUG
#define PW_DEBUG_MODE
#endif // _DEBUG
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Type Def	
#ifdef _WIN64
	typedef signed __int16				PW_SINT;
	typedef signed __int32				PW_INT;
	typedef signed __int32				PW_LINT;
	typedef signed __int64				PW_LLINT;
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
	typedef const char*					PW_CSTRING;
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

	typedef std::function<PW_VOID()>	PW_FUNCTION;
	//////////////////////////////////
	// Classes

	//////////////////////////////////
	// Class Name: pw::Engine_Constant
	//
	// Purpose: A static class for
	//    holding cross engine data
	//    values.
	//
	class PW_ENGINE_API Engine_Constant {
	// Default Class Structures
	public:
	private:
	// Public Functions/Macros 
	public:
		#define PW_SRD_PTR(type)							std::shared_ptr<type>
		#define PW_UNI_PTR(type)							std::unique_ptr<type>
		#define PW_DUNI_PTR(type, deleter)					std::unique_ptr<type, deleter>
		#define TO_LLINT(x)									static_cast<PW_LLINT>(x)
		#define TO_LLUINT(x)								static_cast<PW_LLUINT>(x)
		#define PW_SMART_ARRAY								*
		
		static constexpr PW_INT PW_SCALE_FACTOR			 =	32;

		static constexpr PW_INT PW_PLAYER_ID             =  0xff;

		static constexpr PW_INT PW_SCROLL_WHEEL_FROWARD  =	0xa1;
		static constexpr PW_INT PW_SCROLL_WHEEL_BACKWARD =	0xa2;

		static constexpr PW_INT PW_CONDIONAL_EVENT       =	0xb1;
		static constexpr PW_INT PW_ACONDIONAL_EVENT      =	0xb2;
		static constexpr PW_INT PW_COLLISION_EVENT       =	0xb3;

		// Getters and setters for core engine system variables.

		// Function: Engine_Constant::Window_Width
		//
		// Purpose: Returns the window's current width.
		//
		static PW_SUINT Window_Width() {
			return window_width;
		}
		// Function: Engine_Constant::Window_Height
		//
		// Purpose: Returns the window's current height.
		//
		static PW_SUINT Window_Height() {
			return window_height;
		}
		// Function: Engine_Constant::Hafe_Window_Width
		//
		// Purpose: Returns the window's current half weight.
		//
		static PW_SUINT Hafe_Window_Width() {
			return hafe_window_width;
		}
		// Function: Engine_Constant::Hafe_Window_Height
		//
		// Purpose: Returns the window's current half height.
		//
		static PW_SUINT Hafe_Window_Height() {
			return hafe_window_height;
		}
		// Function: Engine_Constant::Window_Name
		//
		// Purpose: Returns the current window name.
		//
		static PW_CSTRING Window_Name() {
			return window_name;
		}
		// Function: Engine_Constant::Mouse_X_Coord
		//
		// Purpose: Returns the current mouse_x_coord.
		//
		static PW_INT Mouse_X_Coord() {
			return mouse_x_position;
		}
		// Function: Engine_Constant::Mouse_Y_Coord
		//
		// Purpose: Returns the current mouse_y_coord.
		//
		static PW_INT Mouse_Y_Coord() {
			return mouse_y_position;
		}
		// Function: Engine_Constant::Inverse_Z_Tan
		//
		// Purpose: Returns an engine camera constant.
		//
		static const PW_FLOAT Inverse_Z_Tan() {
			return inverse_z_tan;
		}
		// Function: Engine_Constant::Gravity
		//
		// Purpose: Returns the current gravity constant.
		//
		static const glm::vec2 Gravity() {
			return physics_gravity;
		}
		// Function: Engine_Constant::Set_Window_Width
		//
		// Purpose: Sets the window's width to a new value. 
		//
		static PW_VOID Set_Window_Width(PW_SUINT new_window_width) { 
			window_width = new_window_width;
		}
		// Function: Engine_Constant::Set_Window_Height
		//
		// Purpose: Sets the window's height to a new value.
		//
		static PW_VOID Set_Window_Height(PW_SUINT new_window_height) {
			window_height = new_window_height; 
		}
		// Function: Engine_Constant::Set_Hafe_Window_Width
		//
		// Purpose: Sets the new half width value.
		//
		static PW_VOID Set_Hafe_Window_Width(PW_SUINT new_hafe_window_width) {
			hafe_window_width = new_hafe_window_width;
		}
		// Function: Engine_Constant::Set_Hafe_Window_Height
		//
		// Purpose: Set the new half height value.
		//
		static PW_VOID Set_Hafe_Window_Height(PW_SUINT new_hafe_window_height) {
			hafe_window_height = new_hafe_window_height;
		}
		// Function: Engine_Constant::Set_Window_Name
		//
		// Purpose: Sets the windows name.  
		//
		static PW_VOID Set_Window_Name(PW_CSTRING new_window_name) {
			window_name = new_window_name;
		}
		// Function: Engine_Constant::Set_Mouse_Coords
		//
		// Purpose: Sets the current mouse coords. Does not move the mouse.  
		//
		static PW_VOID Set_Mouse_Coords(PW_INT x, PW_INT y) {
			mouse_x_position = x;
			mouse_y_position = y;
		}
		// Function: Engine_Constant::Calc_Delta_Time
		//
		// Purpose: This function calculates the current
		//    delta time for the engine and makes sure key
		//    systems run at a set rate.
		//
		static PW_VOID Calc_Delta_Time() {
			delta_time = (static_cast<PW_FLOAT>(end_time - start_time) / 1000.0f);
			start_time = end_time;
			//std::cout << "Before Delta Time:" << delta_time << std::endl;
			if (delta_time < fps_constant) {
				delta_time = fps_constant - delta_time;
			}
			else {
				delta_time = fps_constant;
			}
			//std::cout << "After Delta Time:" << delta_time << std::endl;
		}
		// Function: Engine_Constant::Calc_Elapsed_Time
		//
		// Purpose: Sets the windows fps for the engine. 
		//
		static PW_VOID Calc_Elapsed_Time(GLFWwindow* main_window) {
			elapsed_time += delta_time;
			if (last_frames != frames) {
				if (elapsed_time >= 1.0f) {
					std::string str = (const char*)Engine_Constant::Window_Name();
					str.insert(str.size(), " Fps:");
					if (frames > static_cast<PW_INT>(fps_max) + 1) { // Extra frames may happen
						frames = static_cast<PW_INT>(fps_max);
					}
					str.insert(str.size(), std::to_string(frames));
					frames = 0;
					glfwSetWindowTitle(main_window, str.c_str());
					last_frames = frames;
					elapsed_time = 0;
				}
			}
		}
		// Function: Engine_Constant::Wait
		//
		// Purpose: The engine holds the fps back for consistent fps. 
		//
		static PW_VOID Wait() {
			frames = frames + 1; // Increment frame since frame is over
			/* Wait until next frame */
			std::this_thread::sleep_for(std::chrono::duration<PW_FLOAT, std::milli>(delta_time * 1000.0f));

			end_time = std::clock();
		}
		// Time structure getters

		// Function: Engine_Constant::Delta_Time
		//
		// Purpose: Returns the delta time. 
		//
		static PW_FLOAT Delta_Time() { return delta_time; }
		// Function: Engine_Constant::Current_Time
		//
		// Purpose: Returns the current start time of the frame.
		//
		static std::clock_t Current_Time() { return start_time; }
		// Function: Engine_Constant::FPS_Constant
		//
		// Purpose: Returns the fps constant of the engine.
		//
		static const PW_FLOAT FPS_Constant() { return fps_constant; }
		// Function: Engine_Constant::FPS_Max
		//
		// Purpose: Returns the max fps constant of the engine.
		//
		static const PW_FLOAT FPS_Max() { return fps_max; }
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		// Window's current width
		static PW_SUINT window_width;
		// Window's current height
		static PW_SUINT window_height;
		// Haft of the Window's current width
		static PW_SUINT hafe_window_width;
		// Haft of the Window's current height
		static PW_SUINT hafe_window_height;
		// Window's current name
		static PW_CSTRING window_name;

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
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CONSTANT