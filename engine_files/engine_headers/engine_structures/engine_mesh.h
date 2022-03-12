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
#ifndef H_ENGINE_MESH
#define H_ENGINE_MESH
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
#include <vector>
#pragma warning (pop)
//////////////////////////////////
// Project Headers 
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4201)
#include <GL\glew.h>
#include <glm\glm.hpp>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
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
		struct Vertex_Data {
		// Default Class Structures 
		public:
			Vertex_Data();
			Vertex_Data(const glm::vec3& p_vertex_position, const glm::vec2& p_texture_coord);
			
			 ~Vertex_Data();
		private:
		// Public Functions/Macros  
		public:
			 const glm::vec3& Vertex_Position() const;
			 void Set_Vertex_Position(const glm::vec3& p_vertex_position);
			
			 const glm::vec2& Texture_Coord() const;
			 void Set_Texture_Coord(const glm::vec2& p_texture_coord);
				 
			 const glm::vec4& Color_Data() const;
			 void Set_Color_Data(const glm::vec4& p_color_data);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			glm::vec3 m_vertex_position;
			glm::vec2 m_texture_coord;
			glm::vec4 m_color_data;
		};
		class Mesh {
		// Default Class Structures 
		public:
			Mesh();
			Mesh(Vertex_Data* p_vertices, const uint16_t& p_vertex_count, const uint32_t* p_indices, const uint16_t& p_indice_count, const glm::vec2& p_size, const glm::vec2& p_texture_size);

			~Mesh();
		private:
		// Public Functions/Macros 
		public:
			void Draw();

			Vertex_Data* Vertices();
			void Update_Vertices(Vertex_Data* p_new_vertices);

			void Change_Color_Data(const glm::vec4& p_new_color_data);
			void Change_Texture_Data(Vertex_Data* p_new_texture_data);

			const uint32_t& Vertex_Count() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			Vertex_Data* m_vertices;

			uint32_t m_indice_count;
			uint32_t m_vertex_count;

			uint32_t m_vertex_array_object;
			uint32_t m_vertex_buffer_object;
			uint32_t m_vertex_texture_object;
			uint32_t m_vertex_color_object;
			uint32_t m_vertex_element_object;
		}; 
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_MESH