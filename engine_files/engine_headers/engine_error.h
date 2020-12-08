#ifndef H_ENGINE_ERROR
#define H_ENGINE_ERROR

//(HEADER_ONLY)

/* C++ Headers           */
#include <stdio.h>
#include <string>
/* Project Headers       */
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // PW_GLEW_H
#include <GLFW\glfw3.h>
#include <stb_image.h>
/* Engine Headers        */
#include "engine_constant.h"
/* Engine Macro Includes */
/* Engine Macros         */
#ifdef _DEBUG
#define PW_DEBUG_MODE
#endif // _DEBUG
/*************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (Engine_Error)                              ]
	 For handling error within parts of the engine.
	*/
	class Engine_Error {
		/* Default Class Structures */
	public:
	private:
		/* Public Functions/Macros  */
	public:
		// Acceptation to format
		static int PW_LINE_;
		// Acceptation to format
		static const char* PW_FILE_;

		static void PW_GLFW_Callback_Handle(int result, const char* description) {
			printf("|GLFW Function Error: %s\n|Error Code: %d\n|The Error Is On Line: %d\n|In File: %s\n", description, result, PW_LINE_, PW_FILE_);
			return;
		}
		static void PW_GLFW_Handle(const int result, const int line, const char* file) {
			if (result == GLFW_FALSE) {
				printf("|GLFW Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", "Function Error", line, file);
				return;
			}
#ifdef PW_DEBUG_MODE
			else {
				printf("|GLFW Function Succeed: %s\n", "No Error");
				return;
			}
#endif // PW_DEBUG_MODE
		}
		static void PW_GL_VOID_Handle(const GLenum result, const int line, const char* file) {
			if (result != 0) {
				printf("|GL Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", glewGetErrorString(result), line, file);
				return;
			}
#ifdef PW_DEBUG_MODE
			else {
				printf("|GL Function Succeed: %s\n", glewGetErrorString(result));
				return;
			}
#endif // PW_DEBUG_MODE
		}
		static void PW_GL_Handle(const GLenum result, const int line, const char* file) {
			if (result <= 0) {
				printf("|GL Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", glewGetErrorString(result), line, file);
				return;
			}
#ifdef PW_DEBUG_MODE
			else {
				printf("|GL Function Succeed: No Error\n");
				return;
			}
#endif // PW_DEBUG_MODE
		}
		static void PW_STBI_Handle(unsigned char* result, const int line, const char* file) {
			if (result == NULL) {
				printf("|STBI Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", stbi_failure_reason(), line, file);
				return;
			}
		}
		#define PW_GLFW_VOID_CALL(x) { x; pw::Engine_Error::PW_LINE_ = __LINE__; pw::Engine_Error::PW_FILE_ = __FILE__; }
		#define PW_GLFW_CALL(x) { pw::Engine_Error::PW_GLFW_Handle(x, __LINE__, __FILE__); }
		#define PW_GL_VOID_CALL(x) { pw::Engine_Error::PW_GL_VOID_Handle(glGetError(), __LINE__, __FILE__); }
		#define PW_GL_CALL(x) { pw::Engine_Error::PW_GL_Handle(x, __LINE__, __FILE__); }
		#define PW_STBI_CALL(x) { pw::Engine_Error::PW_STBI_Handle(x, __LINE__, __FILE__); }
		/* Public Variables         */
	public:
		/* Private Functions/Macros */
	private:
		/* Private Variables        */
	private:
	};
	/* Functions                */
}
#endif // !H_ENGINE_ERROR