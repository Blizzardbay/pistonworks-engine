// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
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
#ifndef H_ENGINE_SHADER
#define H_ENGINE_SHADER
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers 
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <fstream>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4201)
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
#include "engine_control\engine_file_finder.h"
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_camera.h"
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		class Shader_Loader {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			static std::wstring Load_Shader(const std::wstring& p_file_name);
			static uint32_t Compile_Shader(const std::wstring& p_shader_code, const GLenum& p_shader_type);
			static void Check_Error(const uint32_t& p_object_id, const GLenum& p_error, const bool& p_is_program, const std::wstring& p_custom_error_msg);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
		};
		class Dynamic_Shader {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			static void Create_Shader(const std::wstring& p_vertex_location, const std::wstring& p_fragment_location);
			
			static void Release_Shader();
			static void Use();
			
			static void Update_Matrices(const glm::mat4& p_model_matrix, const int32_t& p_model_is_colored, const int32_t& p_model_is_text);
			static void Update_Projection();
			
			static const uint32_t& Shader_Id();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			static uint32_t m_program_id;

			static uint32_t m_vertex_shader;
			static uint32_t m_fragment_shader;

			static uint32_t m_model_uniform;
			static uint32_t m_view_uniform;
			static uint32_t m_projection_uniform;

			static uint32_t m_color_uniform;
			static uint32_t m_text_uniform;
		};                 
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_SHADER