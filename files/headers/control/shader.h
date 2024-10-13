// BSD 3 - Clause License
//
// Copyright(c) 2021-2024, Darrian Corkadel
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
#ifndef H_SHADER
#define H_SHADER
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers 
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <fstream>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
#include "control\file_finder.h"
//////////////////////////////////
// Engine Structures Headers
#include "structures\camera.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		class Model;
	ST_NAMESPACE_END
PW_NAMESPACE_END

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Engine_Queue;
	CO_NAMESPACE_END
PW_NAMESPACE_END

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Shader;
		class Shader_Loader {
		// Friends
			friend class pw::co::Shader;
		// Default Class Structures 
		public:
		private:
		// Private Functions/Macros  
		private:
			/* Error List: PW_FILE_NOT_FOUND */
			static std::wstring Load_Shader(const std::wstring& p_file_name);
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR, PW_GL_ERROR */
			static uint32_t Compile_Shader(const std::wstring& p_shader_code, const uint32_t p_shader_type);
			/* Error List: PW_GL_ERROR */
			static void Check_Error(const uint32_t p_object_id, const uint32_t p_error, const bool p_is_program, const std::wstring& p_custom_error_msg);
		// Private Variables         
		private:
		};
		class Shader {
		// Friends
			friend class pw::co::Control;
			friend class pw::st::Model;
			friend class pw::co::Engine_Queue;
		// Default Class Structures 
		public:
		private:
		// Private Functions/Macros 
		private:
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			static void Create_Shader(const std::wstring& p_vertex_location, const std::wstring& p_fragment_location);
			/* Error List: PW_GL_ERROR */
			static void Release();
			/* Error List: PW_GL_ERROR */
			static void Use();
			/* Error List: PW_GL_ERROR */
			static void Update_Projection();
			/* Error List: NONE */
			static const uint32_t& Shader_Id();
		// Private Variables        
		private:
			static uint32_t m_program_id;

			static uint32_t m_vertex_shader;
			static uint32_t m_fragment_shader;

			static int32_t m_view_uniform;
			static int32_t m_projection_uniform;
		};                 
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_SHADER