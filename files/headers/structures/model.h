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
#ifndef H_MODEL
#define H_MODEL
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers  
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <cmath>
#pragma warning(pop)
//////////////////////////////////
// Project Headers 
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <glm\glm.hpp>
#include <box2d\b2_body.h>
#include <box2d\b2_fixture.h>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "structures\mesh.h"
#include "structures\texture.h"
#include "control\shader.h"      
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Engine_Queue;
	CO_NAMESPACE_END
PW_NAMESPACE_END

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		struct ID_Down_RS_Triangle {
		// Friends
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			/* Error List: NONE */
			static Vertex_Data* Vertices();
			/* Error List: NONE */
			static const uint32_t* Indices();
			/* Error List: NONE */
			static const uint16_t& Vertices_Size();
			/* Error List: NONE */
			static const uint16_t& Indices_Size();
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh);
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh);
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
		// Friends
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			/* Error List: NONE */
			static Vertex_Data* Vertices();
			/* Error List: NONE */
			static const uint32_t* Indices();
			/* Error List: NONE */
			static const uint16_t& Vertices_Size();
			/* Error List: NONE */
			static const uint16_t& Indices_Size();
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh);
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh);
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
		// Friends
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			/* Error List: NONE */
			static Vertex_Data* Vertices();
			/* Error List: NONE */
			static const uint32_t* Indices();
			/* Error List: NONE */
			static const uint16_t& Vertices_Size();
			/* Error List: NONE */
			static const uint16_t& Indices_Size();
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh);
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh);
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
		// Friends
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			/* Error List: NONE */
			static Vertex_Data* Vertices();
			/* Error List: NONE */
			static const uint32_t* Indices();
			/* Error List: NONE */
			static const uint16_t& Vertices_Size();
			/* Error List: NONE */
			static const uint16_t& Indices_Size();
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh);
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh);
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
		// Friends
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			/* Error List: NONE */
			static Vertex_Data* Vertices();
			/* Error List: NONE */
			static const uint32_t* Indices();
			/* Error List: NONE */
			static const uint16_t& Vertices_Size();
			/* Error List: NONE */
			static const uint16_t& Indices_Size();
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_NOC(st::Mesh*& p_model_mesh);
			/* Error List: PW_FUNCTION_ERROR */
			static void Handle_Model_Data_C(st::Mesh*& p_model_mesh);
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
		// Friends
			friend class pw::co::Control;
			friend class pw::co::Engine_Queue;
		// Default Class Structures 
		public:
			/* Error List: NONE */
			Model();
			/* Error List: PW_FUNCTION_ERROR */
			Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float p_rotation, const glm::vec2& p_size, const bool p_repeats = false, const bool p_fixed_rotation = false, int32_t p_is_text = 0);
			/* Error List: PW_FUNCTION_ERROR */
			Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float p_rotation, const glm::vec2& p_size, const glm::vec4& p_color, const bool p_repeats = false, const bool p_fixed_rotation = false, int32_t p_is_text = 0);
			/* Error List: NONE */
			Model& operator=(Model&& p_rhs) noexcept;
			/* Error List: NONE */
			~Model();
		private:
		// Public Functions/Macros  
		public:
			/* Error List: PW_NULL_PARAMETER_W, PW_FUNCTION_ERROR */
			void Render(uint32_t p_layer);
			/* Error List: PW_NULL_PARAMETER_W, PW_FUNCTION_ERROR */
			void Render(uint32_t p_layer, b2Body* p_body);

			/* Error List: PW_FUNCTION_ERROR */
			void Set_Texture(st::Texture* p_new_texture);
			/* Error List: PW_FUNCTION_ERROR */
			void Set_Model_Color(const glm::vec4& p_new_color);

			/* Error List: NONE */
			void Update_Position(const glm::vec2& p_position);
			/* Error List: NONE */
			void Update_Position(const float x_pos, const float y_pos);

			/* Error List: NONE */
			void Set_Position(glm::vec2 p_new_position, bool p_attached = false);
			/* Error List: NONE */
			void Attach_To(glm::vec2* p_position);

			/* Error List: NONE */
			void Set_Size_X(const float p_size_x);
			/* Error List: NONE */
			void Set_Size_Y(const float p_size_y);
			/* Error List: NONE */
			void Set_Size(const glm::vec2& p_size_px);

			/* Error List: NONE */
			void Set_Offset(const glm::vec2& p_offset);

			/* Error List: NONE */
			void Set_Rotation(const float p_new_rotation);
			/* Error List: NONE */
			void Set_Rotation(const float p_new_rotation, b2Body* p_body);

			/* Error List: NONE */
			const Geometry_Types& Type() const;
			/* Error List: NONE */
			st::Mesh* Mesh() const;
			/* Error List: NONE */
			st::Texture* Texture() const;
			/* Error List: NONE */
			const glm::vec4& Color() const;
			/* Error List: NONE */
			const int32_t& Is_Colored() const;
			/* Error List: NONE */
			const int32_t& Is_Text() const;
			/* Error List: NONE */
			const bool& Is_Attached() const;

			/* Error List: NONE */
			glm::vec2 Position();
			/* Error List: NONE */
			glm::vec2* Position_Reference();
			/* Error List: NONE */
			const glm::vec2& Last_Postition() const;
			/* Error List: NONE */
			const glm::vec2& Size() const;
			/* Error List: NONE */
			const glm::vec2& Offset() const;
			/* Error List: NONE */
			const float& Rotation() const;
			/* Error List: NONE */
			const float& Last_Rotation() const;

			/* Error List: NONE */
			const uint64_t& Id();
			/* Error List: NONE */
			glm::vec2 Tile_Center();
			/* Error List: NONE */
			glm::vec2 Calculate_Center();
			/* Error List: NONE */
			const uint32_t& Render_Index();
		// Public Variables        
		public:
			static uint64_t m_model_counter;
			static uint64_t m_model_id_assigner;
		// Private Functions/Macros 
		private:
			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: NONE */
			static void Release();

			/* Error List: PW_FUNCTION_ERROR */
			static void Draw();
			/* Error List: PW_FUNCTION_ERROR */
			static void Draw_Transparent();

			/* Error List: PW_FUNCTION_ERROR */
			void Update_Matrix(uint32_t p_layer);
			/* Error List: PW_FUNCTION_ERROR */
			void Update_Matrix(uint32_t p_layer, b2Body*& p_body);
		// Private Variables      
		private:
			Geometry_Types m_type;
			st::Mesh* m_mesh;
			st::Texture* m_texture;
			glm::vec4 m_color;
			int32_t m_is_colored;
			int32_t m_is_text;

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
			bool m_is_copy;
			bool m_changed;

			uint64_t m_id;
			uint32_t m_render_index;
			uint32_t m_model_matrix_index;

			static std::map<pw::st::Geometry_Types, pw::st::Mesh*> m_geometry_holder_c;
			static std::map<pw::st::Geometry_Types, pw::st::Mesh*> m_geometry_holder_noc;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_MODEL