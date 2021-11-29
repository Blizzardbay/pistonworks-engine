// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
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
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers              
#include <fstream>
#include <stdio.h>
//////////////////////////////////
// Project Headers          
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
//////////////////////////////////
// Engine Headers           
#include "engine_structures\engine_camera.h"
//////////////////////////////////
// Engine Macro Includes    
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Macros            
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
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Shader
		// //////////////////////////////////////////////////																				 
		// Purpose: 
		//  A class for handling the shaders in opengl.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Shader {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Shader::Shader
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a uninitialized shader.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Shader();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Shader::~Shader
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates all data used for the shader.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Shader();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Shader::Create_Shader
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a new shader after one has been loaded
			//  from file.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) const std::wstring& vertex_location;
			// Purpose: 
			//  The location of the vertex shader.
			// (2) const std::wstring& fragment_location;
			// Purpose: 
			//  The location of the fragment shader.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			void CORE Create_Shader(const std::wstring& vertex_location, const std::wstring& fragment_location);
			// //////////////////////////////////////////////////
			// CORE Function: Shader::Use
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Gets the shader ready for use.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			void CORE Use();
			// //////////////////////////////////////////////////
			// CORE Function: Shader::Update_Matrices
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Updates the matrices of the model.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) glm::mat4 model;
			// Purpose: 
			//  The model to be updated by the shader. 
			// (2) int32_t& model_is_colored;
			// Purpose: 
			//  Is the model colored or not.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			void CORE Update_Matrices(glm::mat4* model, int32_t& model_is_colored);
			// //////////////////////////////////////////////////
			// CORE Function: Shader::Update_Projection
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Updates the camera projection.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			void CORE Update_Projection();
			// Accessors
			USER_INTERACTION
			ACCESSOR uint32_t Shader_Id();
			USER_INTERACTION
			static ACCESSOR Shader Get_Shader();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			// //////////////////////////////////////////////////
			// LOADER Function: Shader::Load_Shader
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a shader from file.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const std::wstring& file_name;
			// Purpose: 
			//  The file name of the shader. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static LOADER std::wstring Load_Shader(const std::wstring& file_name);
			// //////////////////////////////////////////////////
			// CORE Function: Shader::Compile_Shader
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Complies the shader for use.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) const std::wstring shader_code;
			// Purpose: 
			//  The shader id.
			// (2) GLenum shader_type;
			// Purpose: 
			//  The type of shader, i.e. vertex or fragment. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE uint32_t Compile_Shader(const std::wstring shader_code, GLenum shader_type);
			// //////////////////////////////////////////////////
			// CORE Function: Shader::Check_Error
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Checks if the shader is not correctly made.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) uint32_t object_id;
			// Purpose: 
			//  The shader id.
			// (2) GLenum error;
			// Purpose: 
			//  The type of shader, i.e. vertex or fragment.
			// (3) bool is_program;
			// Purpose: 
			//  The type of shader, i.e. vertex or fragment.
			// (4) const wchar_t* custom_error_msg;
			// Purpose: 
			//  The type of shader, i.e. vertex or fragment. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Check_Error(uint32_t object_id, GLenum error, bool is_program, std::wstring custom_error_msg);
		// Private Variables        
		private:
			static Shader this_shader;

			uint32_t program_id;

			uint32_t vertex_shader;
			uint32_t fragment_shader;

			uint32_t model_uniform;
			uint32_t texture_uniform;
			uint32_t view_uniform;
			uint32_t projection_uniform;
		};
		// Functions                
		// Macros / Definitions                  
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_SHADER