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
#ifndef H_ENGINE_MODEL
#define H_ENGINE_MODEL
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers  
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <cmath>
#pragma warning(pop)
//////////////////////////////////
// Project Headers 
#pragma warning(push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <glm\glm.hpp>
#include <box2d\b2_body.h>
#include <box2d\b2_fixture.h>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_mesh.h"
#include "engine_structures\engine_texture.h"
#include "engine_structures\engine_shader.h"      
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
		struct ID_Down_RS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			static Vertex_Data* Vertices();
			
			static const uint32_t* Indices();
			
			static const uint16_t& Vertices_Size();
			
			static const uint16_t& Indices_Size();
			
			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size);
			
			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			static const uint16_t m_vertices_size = 3;
			static Vertex_Data m_vertices[3];
			static const uint16_t m_indices_size = 3;
			static uint32_t m_indices[3];
		};
		struct ID_Down_LS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			static Vertex_Data* Vertices();

			static const uint32_t* Indices();

			static const uint16_t& Vertices_Size();

			static const uint16_t& Indices_Size();

			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size);

			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size);
		// Public Variables 
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t m_vertices_size = 3;
			static Vertex_Data m_vertices[3];
			static const uint16_t m_indices_size = 3;
			static uint32_t m_indices[3];
		};
		struct ID_Up_RS_Triangle {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			static Vertex_Data* Vertices();

			static const uint32_t* Indices();

			static const uint16_t& Vertices_Size();

			static const uint16_t& Indices_Size();

			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size);

			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t m_vertices_size = 3;
			static Vertex_Data m_vertices[3];
			static const uint16_t m_indices_size = 3;
			static uint32_t m_indices[3];
		};
		struct ID_Up_LS_Triangle {
			// Default Class Structures 
		public:
		private:
			// Public Functions/Macros 
		public:
			static Vertex_Data* Vertices();

			static const uint32_t* Indices();

			static const uint16_t& Vertices_Size();

			static const uint16_t& Indices_Size();

			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size);

			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size);
			// Public Variables       
		public:
			// Private Functions/Macros 
		private:
			// Private Variables     
		private:
			static const uint16_t m_vertices_size = 3;
			static Vertex_Data m_vertices[3];
			static const uint16_t m_indices_size = 3;
			static uint32_t m_indices[3];
		};
		struct ID_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			static Vertex_Data* Vertices();

			static const uint32_t* Indices();

			static const uint16_t& Vertices_Size();

			static const uint16_t& Indices_Size();

			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size);

			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size);
		// Public Variables  
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t m_vertices_size = 4;
			static Vertex_Data m_vertices[4];
			static const uint16_t m_indices_size = 6;
			static uint32_t m_indices[6];
		};
		enum class Geometry_Types {
			UNINIT,
			DOWN_RS_TRIANGLE,
			DOWN_LS_TRIANGLE,
			UP_RS_TRIANGLE,
			UP_LS_TRIANGLE,
			SQUARE,
			TYPE_COUNT
		};
		class Model {
		// Default Class Structures 
		public:
			Model();

			Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float& p_rotation, const glm::vec2& p_size, const bool& p_repeats = false, const bool& p_fixed_rotation = false);
			
			Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float& p_rotation, const glm::vec2& p_size, const glm::vec4& p_color, const bool& p_repeats = false, const bool& p_fixed_rotation = false);
			
			Model operator=(const Model& p_other);

			~Model();
		private:
		// Public Functions/Macros  
		public:
			void Render(const int32_t& p_is_text = 0);
			void Render(b2Body* p_body, const int32_t& p_is_text = 0);

			void Set_Texture(st::Texture* p_new_texture);
			void Set_Model_Color(const glm::vec4& p_new_color);

			void Update_Position(const glm::vec2& p_position);
			void Update_Position(const float& x_pos, const float& y_pos);

			void Set_Position(glm::vec2 p_new_position, bool p_attached = false);
			void Attach_To(glm::vec2* p_position);

			void Set_Size_X(const float& p_size_x);
			void Set_Size_Y(const float& p_size_y);
			void Set_Size(const glm::vec2& p_size_px);

			void Set_Offset(const glm::vec2& p_offset);

			void Set_Rotation(const float& p_new_rotation);
			void Set_Rotation(const float& p_new_rotation, b2Body* p_body);

			const Geometry_Types& Type() const;
			st::Mesh* Mesh() const;
			st::Texture* Texture() const;
			const glm::vec4& Color() const;
			const int32_t& Is_Colored() const;

			glm::vec2 Position();
			glm::vec2* Position_Reference();
			const glm::vec2& Last_Postition() const;
			const glm::vec2& Size() const;
			const glm::vec2& Offset() const;
			const float& Rotation() const;
			const float& Last_Rotation() const;
			
			const uint64_t& Id();

			glm::vec2 Tile_Center();
			glm::vec2 Calculate_Center();
		// Public Variables        
		public:
			static uint64_t m_model_counter;
			static uint64_t m_model_id_assigner;
		// Private Functions/Macros 
		private:
			void Update_Matrix();
			void Update_Matrix(b2Body*& p_body);
		// Private Variables      
		private:
			Geometry_Types m_type;
			st::Mesh* m_mesh;
			st::Texture* m_texture;
			glm::vec4 m_color;
			int32_t m_is_colored;

			glm::vec2* m_position;
			glm::vec2 m_last_position;
			glm::vec2 m_size;
			glm::vec2 m_offset;
			float m_rotation;
			float m_last_rotation;

			glm::mat4 m_matrix;

			bool m_attached;
			bool m_fixed_rotation;
			bool m_repeats;

			uint64_t m_id;

			static void(*model_functions_noc[(int32_t)Geometry_Types::TYPE_COUNT - 1])(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size);
			static void(*model_functions_c[(int32_t)Geometry_Types::TYPE_COUNT - 1])(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size);

			static const Vertex_Data* model_vertices[(int32_t)Geometry_Types::TYPE_COUNT - 1];
			static const uint16_t model_vertices_count[(int32_t)Geometry_Types::TYPE_COUNT - 1];
		};
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_MODEL