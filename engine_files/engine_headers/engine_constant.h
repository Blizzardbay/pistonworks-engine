#ifndef H_ENGINE_CONSTANT
#define H_ENGINE_CONSTANT

//(HEADER_ONLY)

/* C++ Headers           */
#include <chrono>
/* Project Headers       */
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // !PW_GLEW_H
/* Engine Headers        */
/* Engine Macro Includes */
#include "engine_error.h"
/* Engine Macros         */
/*************************/
/*Type Def               */
#ifdef _WIN32
	typedef signed short int PW_SINT;
	typedef signed int PW_INT;
	typedef signed long int PW_LINT;
	typedef signed long long int PW_LLINT;
	typedef unsigned short int PW_SUINT;
	typedef unsigned int PW_UINT;
	typedef unsigned long int PW_LUINT;
	typedef unsigned long long int PW_LLUINT;
#else 
	typedef signed __int8 PW_SINT;
	typedef signed __int16 PW_INT;
	typedef signed __int32 PW_LINT;
	typedef signed __int64 PW_LLINT;
	typedef unsigned __int8 PW_SUINT;
	typedef unsigned __int16 PW_UINT;
	typedef unsigned __int32 PW_LUINT;
	typedef unsigned __int64 PW_LLUINT;
#endif

typedef std::string PW_STRING;

#if _UNICODE  
	typedef char  PW_CHAR;
	typedef const char* PW_CSTRING;
#else
	#if _MBCS
	typedef wchar_t PW_CHAR;
	typedef const wchar_t* PW_CSTRING;
#endif
#endif

typedef float PW_FLOAT;
typedef double PW_DOUBLE;
typedef long double PW_LDOUBLE;

typedef void PW_VOID;
typedef void* PW_TYPE;

typedef bool PW_BOOL;
typedef unsigned char PW_BYTE;
/*************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (Engine_Constant)                           ]
	 A static class for holding cross engine data
	 values.
	*/
	class Engine_Constant {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static PW_SUINT Window_Width() { return window_width; }
		static PW_SUINT Window_Height() { return window_height; }
		static PW_SUINT Hafe_Window_Width() { return hafe_window_width; }
		static PW_SUINT Hafe_Window_Height() { return hafe_window_height; }
		static PW_CSTRING Window_Name() { return window_name; }

		static PW_VOID Set_Window_Width(PW_SUINT new_window_width) { window_width = new_window_width; }
		static PW_VOID Set_Window_Height(PW_SUINT new_window_height) { window_height = new_window_height; }
		static PW_VOID Set_Hafe_Window_Width(PW_SUINT new_hafe_window_width) { hafe_window_width = new_hafe_window_width; }
		static PW_VOID Set_Hafe_Window_Height(PW_SUINT new_hafe_window_height) { hafe_window_height = new_hafe_window_height; }
		static PW_VOID Set_Window_Name(PW_CSTRING new_window_name) { window_name = new_window_name; }

		static PW_VOID Calc_Delta_Time() {
			previous_time = current_time;
			current_time = std::chrono::system_clock::now();
			delta_time = current_time - previous_time;
			if (delta_time >= Engine_Constant::FPS_Constant()) {
				delta_time = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(Engine_Constant::FPS_Constant());
			}
		}
		static std::chrono::duration<PW_FLOAT, std::milli> Delta_Time() { return delta_time; }
		static std::chrono::system_clock::time_point Current_Time() { return current_time; }
		static const std::chrono::duration<PW_FLOAT, std::milli> FPS_Constant() { return fps_constant; }

/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static PW_SUINT window_width;
		static PW_SUINT window_height;
		static PW_SUINT hafe_window_width;
		static PW_SUINT hafe_window_height;

		static PW_CSTRING window_name;

		static std::chrono::system_clock::time_point previous_time;
		static std::chrono::system_clock::time_point current_time;
		static std::chrono::duration<PW_FLOAT, std::milli> delta_time;
		static const std::chrono::duration<PW_FLOAT, std::milli> fps_constant;
	};
/* Functions                */
}
#endif // !H_ENGINE_CONSTANT