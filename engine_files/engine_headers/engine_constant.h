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
		static GLfloat Get_Window_Width() { return window_width; }
		static GLfloat Get_Window_Height() { return window_height; }
		static const char* Get_Window_Name() { return window_name; }
		static GLint Get_Buffer_Width() { return buffer_width; }
		static GLint Get_Buffer_Height() { return buffer_height; }
		static GLint Get_Hafe_Buffer_Width() { return hafe_buffer_width; }
		static GLint Get_Hafe_Buffer_Height() { return hafe_buffer_height; }

		static void Set_Window_Width(GLfloat new_window_width) { window_width = new_window_width; }
		static void Set_Window_Height(GLfloat new_window_height) { window_height = new_window_height; }
		static void Set_Window_Name(const char* new_window_name) { window_name = new_window_name; }
		static void Set_Buffer_Width(GLint new_buffer_width) { buffer_width = new_buffer_width; }
		static void Set_Buffer_Height(GLint new_buffer_height) { buffer_height = new_buffer_height; }
		static void Set_Hafe_Buffer_Width(GLint new_hafe_buffer_width) { hafe_buffer_width = new_hafe_buffer_width / 2; }
		static void Set_Hafe_Buffer_Height(GLint new_hafe_buffer_height) { hafe_buffer_height = new_hafe_buffer_height / 2; }

		static void Calc_Delta_Time() {
			previous_time = current_time;
			current_time = std::chrono::system_clock::now();
			delta_time = current_time - previous_time;
			if (delta_time.count() >= Engine_Constant::Get_FPS_Constant()) {
			}
		}
		static float Get_Delta_Time() { return delta_time.count(); }

		static const float Get_FPS_Constant() { return fps_constant; }

/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static GLfloat window_width;
		static GLfloat window_height;
		static GLint buffer_width;
		static GLint buffer_height;
		static GLint hafe_buffer_width;
		static GLint hafe_buffer_height;

		static const char* window_name;

		static std::chrono::system_clock::time_point  previous_time;
		static std::chrono::system_clock::time_point current_time;
		static std::chrono::system_clock::duration delta_time;
		static const float fps_constant;
	};
/* Functions                */
}
#endif // !H_ENGINE_CONSTANT