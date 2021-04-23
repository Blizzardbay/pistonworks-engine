#ifndef H_ENGINE_ERROR
#define H_ENGINE_ERROR
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <stdio.h>
#include <string>
//////////////////////////////////
// Project Headers
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // PW_GLEW_H
#include <GLFW\glfw3.h>
#include <stb_image.h>
//////////////////////////////////
// Engine Headers
#include "engine_constant.h"
//////////////////////////////////
// Engine Macro Includes
//////////////////////////////////
// Engine Macros
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Classes

	//////////////////////////////////
	// Class Name: pw::Engine_Error
	//
	// Purpose: For handling error
	//    within parts of the engine.
	//
	class PW_ENGINE_API Engine_Error {
	// Default Class Structures
	public:
	private:
	// Public Functions/Macros
	public:
		// Function: Engine_Error::PW_GLFW_Callback_Handle
		//
		// Purpose: Prints error msg's sent to the function from glfw. 
		//
		static PW_VOID PW_GLFW_Callback_Handle(PW_INT result, PW_CSTRING description) {
			if (result != 65537) {
				printf("|%s|GLFW Function Error: %s\n|Error Code: %d\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, description, result, PW_LINE_, PW_FILE_);
			}
			return;
		}
		// Function: Engine_Error::PW_GLFW_Handle
		//
		// Purpose: Takes a result and finds if it is an error or not.
		//
		static PW_VOID PW_GLFW_Handle(const PW_INT result, const PW_INT line, PW_CSTRING file) {
			if (result != GLFW_NO_ERROR && result != GLFW_TRUE) {
				printf("|%s|GLFW Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, "Function Error", line, file);
				return;
			}
		#ifdef PW_DEBUG_MODE
			else {
				printf("|%s|GLFW Function Succeed: %s\n", __TIME__, "No Error");
				return;
			}
		#endif // PW_DEBUG_MODE
		}
		// Function: Engine_Error::PW_GL_VOID_Handle
		//
		// Purpose: Finds an error from a opengl function with a void return.
		//
		static PW_VOID PW_GL_VOID_Handle(const GLenum result, const PW_INT line, PW_CSTRING file, bool handle_type) {
			if (result != 0 && result != 1282) {
				printf("|%s|GL Function Error: %d\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, result, line, file);
				return;
			}
		#ifdef PW_DEBUG_MODE
			else {
				if (handle_type == true) {
					printf("|%s|GL Function Succeed: %s\n", __TIME__, "  No Error");
					return;
				}
			}
		#endif // PW_DEBUG_MODE
		}
		// Function: Engine_Error::PW_GL_Handle
		//
		// Purpose: Interprets a result form a opengl function.
		//
		static PW_VOID PW_GL_Handle(const GLenum result, const PW_INT line, PW_CSTRING file) {
			if (result <= 0) {
				printf("|%s|GL Function Error: %d\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, result, line, file);
				return;
			}
		#ifdef PW_DEBUG_MODE
			else {
				printf("|%s|GL Function Succeed: %s\n", __TIME__, "  No Error");
				return;

			}
		#endif // PW_DEBUG_MODE
		}
		// Function: Engine_Error::PW_STBI_Handle
		//
		// Purpose: Tests if the result is an error, if so then print out the error msg.
		//
		static PW_VOID PW_STBI_Handle(PW_BYTE* result, const PW_INT line, PW_CSTRING file) {
			if (result == NULL) {
				printf("|%s|STBI Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, stbi_failure_reason(), line, file);
				return;
			}
		}
		#define PW_GLFW_VOID_CALL(funct) { funct; pw::Engine_Error::PW_LINE_ = __LINE__; pw::Engine_Error::PW_FILE_ = __FILE__; }
		#define PW_GLFW_CALL(funct) { pw::Engine_Error::PW_GLFW_Handle(funct, __LINE__, __FILE__); }
		#define PW_GL_VOID_CALL(funct, handle_type) { funct; pw::Engine_Error::PW_GL_VOID_Handle(glGetError(), __LINE__, __FILE__,handle_type); }
		#define PW_GL_CALL(funct) { pw::Engine_Error::PW_GL_Handle(funct, __LINE__, __FILE__); }
		#define PW_STBI_CALL(funct) { pw::Engine_Error::PW_STBI_Handle(funct, __LINE__, __FILE__); }
	// Public Variables
	public:
		static PW_INT PW_LINE_;
		static PW_CSTRING PW_FILE_;
	// Private Functions/Macros 
	private:
	// Private Variables
	private:
	};
	// Functions
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_ERROR