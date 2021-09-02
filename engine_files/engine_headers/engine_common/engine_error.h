#ifndef H_ENGINE_ERROR
#define H_ENGINE_ERROR
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
//////////////////////////////////
// Project Headers
#ifndef PW_GLEW_H
#define PW_GLEW_H
#include <GL\glew.h>
#endif // PW_GLEW_H
#include <GLFW\glfw3.h>
#include <freeimage\FreeImage.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype\fterrors.h>
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_constant.h"
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
	//////////////////////////////////
	ER_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// Class Name: pw::er::Engine_Error
		// //////////////////////////////////////////////////
		// Purpose:
		//  For handling error
		//  within parts of the engine.
		// //////////////////////////////////////////////////
		class PW_COMMON_API Engine_Error {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			static ERROR_HANDLE PW_VOID PW_Print_Error(const PW_CSTRING sender, const PW_CSTRING msg, const PW_INT line, PW_CSTRING file);
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GLFW_Callback_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints error msg's sent to the function from
			//  glfw.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_INT result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) PW_CSTRING description;
			// Purpose: 
			//  The description of the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_GLFW_Callback_Handle(PW_INT result, PW_CSTRING description) {
				if (result != 65537) {
					PW_Print_Error("GLFW", description, PW_LINE_, PW_FILE_);
				}
				return;
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GLFW_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Takes a result and finds if it is an error or not
			//  .
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const PW_INT result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const PW_INT line;
			// Purpose: 
			//  The line the error was on.
			// (3) PW_CSTRING file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_GLFW_Handle(const PW_INT result, const PW_INT line, PW_CSTRING file) {
				if (result != GLFW_NO_ERROR && result != GLFW_TRUE) {
					PW_Print_Error("GLFW", "Function Error", line, file);
					return;
				}
			#ifdef PW_DEBUG_MODE
				else {
					PW_Print_Error("GLFW", "Function Succeed", line, file);
					return;
				}
			#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GL_VOID_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Finds an error from a opengl function with a void
			//  return.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) const GLenum result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const PW_INT line;
			// Purpose: 
			//  The line the error was on.
			// (3) PW_CSTRING file;
			// Purpose: 
			//  The file the error happened in.
			// (4) PW_FLAG handle_type;
			// Purpose:
			//  Should the error be printed or not.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_GL_VOID_Handle(const GLenum result, const PW_INT line, PW_CSTRING file, PW_FLAG handle_type) {
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
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_FI_Callback_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints error msg's sent to the function from FI.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) FREE_IMAGE_FORMAT result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) PW_CSTRING description;
			// Purpose: 
			//  The description of the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_FI_Callback_Handle(FREE_IMAGE_FORMAT result, PW_CSTRING description) {
				if (result != FIF_UNKNOWN) {
					printf("|%s|FI Function Error: %s\n|Unknown Image Format: %d\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, description, result, PW_LINE_, PW_FILE_);
					return;
				}
				else {
					printf("|%s|FI Function Error: %s\n|Known Image Format: %d\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, description, result, PW_LINE_, PW_FILE_);
					return;
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_GL_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Interprets a result form a opengl function.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// 
			// (1) const GLenum result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const PW_INT line;
			// Purpose: 
			//  The line the error was on.
			// (3) PW_CSTRING file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_GL_Handle(const GLenum result, const PW_INT line, PW_CSTRING file) {
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
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_FT_Handle
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Handles possible font loading issues.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) const FT_Error result;
			// Purpose: 
			//  The result of the function to be evaluated.
			// (2) const PW_INT line;
			// Purpose: 
			//  The line the error was on.
			// (3) PW_CSTRING file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_FT_Handle(const FT_Error result, const PW_INT line, PW_CSTRING file) {
				if (result != FT_Err_Ok) {
					printf("|%s|FT Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, FT_Error_String(result), line, file);
					return;
				}
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_Print_Error
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints a custom error msg.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) const PW_CSTRING sender;
			// Purpose: 
			//  The function or thing giving the error.
			// (2) const PW_CSTRING msg;
			// Purpose: 
			//  The warning or description sent by the function.
			// (3) const PW_INT line;
			// Purpose: 
			//  The line the msg came from.
			// (4) PW_CSTRING file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_Print_Error(const PW_CSTRING sender, const PW_CSTRING msg, const PW_INT line, PW_CSTRING file) {
			#ifdef PW_DEBUG_MODE
				std::cerr << "|" << __TIME__ << "|" << sender << " Function Error: " << msg << "\n" << "|The error is on line: " << line << "\n"
					<< "|In file: " << file << "\n";
			#endif // PW_DEBUG_MODE
			}
			// //////////////////////////////////////////////////
			// ERROR_HANDLE Function: Engine_Error::PW_Print_Error
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints a custom error msg.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) const PW_CSTRING sender;
			// Purpose: 
			//  The function or thing giving the error.
			// (2) const PW_CSTRING msg;
			// Purpose: 
			//  The warning or description sent by the function.
			// (3) const PW_INT line;
			// Purpose: 
			//  The line the msg came from.
			// (4) PW_CSTRING file;
			// Purpose: 
			//  The file the error happened in.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static ERROR_HANDLE PW_VOID PW_Print_Error(const PW_CSTRING sender, const PW_CSTRING msg, const PW_INT line, PW_CSTRING file) {
			#ifdef PW_DEBUG_MODE
				std::cerr << "|" << __TIME__ << "|" << sender << " Function Error: " << msg << "\n" << "|The error is on line: " << line << "\n"
					<< "|In file: " << file << "\n";
			#endif // PW_DEBUG_MODE
			}
			#define PW_GLFW_VOID_CALL(funct)			{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__; pw::er::Engine_Error::PW_FILE_ = __FILE__; }
			#define PW_GLFW_CALL(funct)					{ pw::er::Engine_Error::PW_GLFW_Handle(funct, __LINE__, __FILE__); }
			#define PW_GL_VOID_CALL(funct, handle_type) { funct; pw::er::Engine_Error::PW_GL_VOID_Handle(glGetError(), __LINE__, __FILE__,handle_type); }
			#define PW_FI_VOID_CALL(funct)				{ funct; pw::er::Engine_Error::PW_LINE_ = __LINE__; pw::er::Engine_Error::PW_FILE_ = __FILE__; }
			#define PW_FI_VOID_CALL_C(funct)			{ pw::er::Engine_Error::PW_LINE_ = __LINE__; pw::er::Engine_Error::PW_FILE_ = __FILE__; funct }
			#define PW_GL_CALL(funct)					{ pw::er::Engine_Error::PW_GL_Handle(funct, __LINE__, __FILE__); }
			#define PW_FT_CALL(funct)					{ pw::er::Engine_Error::PW_FT_Handle(funct, __LINE__, __FILE__);}
			#define PW_PRINT_ERROR(sender, msg)			{ pw::er::Engine_Error::PW_Print_Error(sender, msg, __LINE__, __FILE__); }
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
		// Macros / Definitions
	//////////////////////////////////
	ER_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_ERROR