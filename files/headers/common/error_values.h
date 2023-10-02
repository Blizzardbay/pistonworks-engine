// BSD 3 - Clause License
//
// Copyright(c) 2021-2023, Darrian Corkadel
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
#ifndef H_ERROR_VALUES
#define H_ERROR_VALUES
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <stdint.h>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////

// There is no current error affecting the engine.
#define PW_NO_ERROR								0x0000U
// This function returns the state of if it properly worked
// represented by a true / false value.
#define PW_RETURN_STATE_TF						0x0000U
// The function was called with a invalid parameter.
// The value of the variable is wrong or cannot be used.
// Find the function call and check passed parameters.
// This is treated as a non-fatal warning.
#define PW_INVAILD_PARAMETER_W					0x0001U
// The function was called with a invalid parameter.
// The value of the variable is wrong or cannot be used.
// Find the function call and check passed parameters.
// This is treated as a fatal severe error.
#define PW_INVAILD_PARAMETER_S					0x0002U
// The type to be evaluated by the string converter function is
// not of a standard string type.
// The following functions give this error,
// 1. pw::cm::Constant::Evaluate_WStr
// 2. pw::cm::Constant::Evaluate_Str
// 3. pw::cm::Constant::Evaluate_TWStr
// 4. pw::cm::Constant::Evaluate_TStr
// Usually wrapped by macros,
// 1. TO_WCHAR
// 2. TO_CHAR
// 3. TO_WSTRING
// 4. TO_STRING
// In order.
// Supported string types,
// char
// const char*
// std::string
// wchar_t
// const wchar_t*
// std::wstring
// Unsupported string types,
// char*
// wchar_t*
// These are unsupported due to raw pointers causing c-like buffer problems.
#define PW_UNKNOWN_STRING_TYPE					0x0003U
// The function was called with a invalid parameter.
// The value of the error is wrong or cannot be used.
// Find the function call and check passed parameters.
// This is treated as a fatal severe error. 
#define PW_UNKNOWN_ERROR_TYPE					0x0004U
// The function was called with a nullptr or NULL parameter.
// Find the function call and check passed parameters.
// This is treated as a non-fatal warning.
#define PW_NULL_PARAMETER_W						0x0005U
// The function was called with a nullptr or NULL parameter.
// Find the function call and check passed parameters.
// This is treated as a fatal severe error.
#define PW_NULL_PARAMETER_S						0x0006U
// The buffers are not equal in size.
#define PW_BUFFER_SIZE_MISMATCH					0x0007U
// A C runtime library (CRT) function has failed.
// This is most likely a wrong implementation of the function.
#define PW_CRT_FUNCTION_FAILURE					0x0008U
// The function was called with a empty container parameter.
// Find the function call and check passed parameters.
// This is treated as a non-fatal warning.
#define PW_EMPTY_PARAMETER_W					0x0009U
// The function was called with a empty container parameter.
// Find the function call and check passed parameters.
// This is treated as a fatal severe error.
#define PW_EMPTY_PARAMETER_S					0x000AU
// The memory function could not properly allocate memory.
#define PW_ALLOCATION_FAILURE					0x000BU
// The first initialization function could not allocate memory.
#define PW_MEMORY_FAILURE						0x000CU
// Cannot allocate 0 types.
// "template<class type> static type* Allocate" must have a non-zero 
// p_count value.
#define PW_ZERO_ALLOCATION						0x000DU
// A Pistonworks function had an error.
// Check error logs for more information.
#define PW_FUNCTION_ERROR						0x000EU
// A Pistonworks function could not find a specified directory.
// It either does not exist in the searched location and or the 
// executable is being run in the wrong place.
#define PW_DIRECTORY_NOT_FOUND					0x000FU
// The game path directory was not found.
// It either does not exist in the searched location and or the 
// executable is being run in the wrong place.
#define PW_GAME_PATH_NOT_FOUND					0x0010U
// The file trying to be found could not be found.
// It either does not exist in the searched location and or the 
// executable is being run in the wrong place.
#define PW_FILE_NOT_FOUND						0x0011U
// A Windows function had an error.
// This is most likely a wrong implementation of the function.
// It could be a fatal error, treated as severe.
#define PW_WIN_FUNCTION_ERROR					0x0012U
// The number of animations in pw::st::Animation_Structure::Animation_Structure
// does not equal the number of id's given.
// Every animation must have an associated id.
#define PW_ANIMATION_ID_SIZE_MISMATCH			0x0013U
// There was an error with GLFW.
// Most likely miss use or engine defect.
#define PW_GLFW_ERROR							0x0014U
// There was an error with OpenGL.
// Most likely miss use or engine defect.
#define PW_GL_ERROR								0x0015U
// There was an error with FreeImage.
// Most likely miss use or engine defect.
#define PW_FI_ERROR								0x0016U
// There was an error with FreeType.
// Most likely miss use or engine defect.
#define PW_FT_ERROR								0x0017U
// There was an error with OpenAL.
// Most likely miss use or engine defect.
#define PW_AL_ERROR								0x0018U
// No audio source for this computer was found by
// OpenAL. Please connect a audio source and
// restart the program.
#define PW_NO_AUDIO_SOURCE_ERROR				0x0019U
// The number of sounds in pw::st::Sound_Structure::Sound_Structure
// does not equal the number of id's given.
// Every sound must have an associated id.
#define PW_SOUND_ID_SIZE_MISMATCH				0x001AU
// The pw::st::Physics_Object b2PolygonShape is not complete
// or is invalid. Check engine code for details and or problem.
#define PW_B2SHAPE_INVALID						0x001BU
// No audio source was found on this computer according
// to OpenAL.
#define PW_AUDIO_SOURCE_NOT_FOUND				0x001CU
// The file type of the given file is unloadable by
// FreeImage.
#define PW_FI_UNKNOWN_FILE_TYPE					0x001DU
// The file type of the given file is unsupported by
// FreeImage.
#define PW_FI_UNSUPPORTED_FILE_TYPE				0x001EU
// The file was unable to load. Was trying to be
// loaded by FreeImage.
#define PW_FI_FILE_LOAD_FAILURE					0x001FU
// The file that was loaded has no pixel data.
#define PW_FI_NO_PIXELS							0x0020U
// The file that was loaded has no pixel data.
#define PW_UNSUPPORTED_ANIMATION_EXTENSION		0x0021U
// There is a chance that the function may give an error,
// or not. It is user implementation defined.
#define PW_POSSIBLE_ERROR						0x0022U
#endif // !H_ERROR_VALUES
