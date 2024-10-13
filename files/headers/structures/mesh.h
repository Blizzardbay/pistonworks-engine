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
#ifndef H_MESH
#define H_MESH
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers 
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <vector>
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
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		struct Vertex_Data {
		// Friends
		// Default Class Structures 
		public:
			/* Error List: NONE */
			Vertex_Data();
			/* Error List: NONE */
			Vertex_Data(const glm::vec3& p_vertex_position, const glm::vec2& p_texture_coord);
			/* Error List: NONE */
			~Vertex_Data();
		private:
		// Public Functions/Macros  
		public:
			/* Error List: NONE */
			const glm::vec3& Vertex_Position() const;
			/* Error List: NONE */
			void Set_Vertex_Position(const glm::vec3& p_vertex_position);
			/* Error List: NONE */
			const glm::vec2& Texture_Coord() const;
			/* Error List: NONE */
			void Set_Texture_Coord(const glm::vec2& p_texture_coord);
			/* Error List: NONE */
			const glm::vec4& Color() const;
			/* Error List: NONE */
			void Set_Color(const glm::vec4& p_color);
			/* Error List: NONE */
			const uint32_t& Is_Colored() const;
			/* Error List: NONE */
			void Set_Is_Colored(uint32_t p_is_colored);
			/* Error List: NONE */
			const uint32_t& Is_Text() const;
			/* Error List: NONE */
			void Set_Is_Text(uint32_t p_is_text);
			/* Error List: NONE */
			const uint32_t& Model_Index() const;
			/* Error List: NONE */
			void Set_Model_Index(uint32_t p_model_index);
			/* Error List: NONE */
			const uint64_t& Texture_Handle() const;
			/* Error List: NONE */
			void Set_Texture_Handle(const uint64_t& p_texture_handle);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			glm::vec3 m_vertex_position;
			glm::vec2 m_texture_coord;
			glm::vec4 m_color;
			uint32_t m_is_colored;
			uint32_t m_is_text;
			uint32_t m_model_index;
			uint64_t m_texture_handle;
		};
		class Mesh {
		// Friends
			friend class pw::co::Control;
		// Default Class Structures 
		public:
			struct Non_Colored {
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				glm::vec2 m_size;
				glm::vec2 m_texture_size;
				glm::mat4 m_matrix;
				int32_t m_is_text;
				uint64_t m_texture_handle;
				static int32_t m_is_colored;
			// Private Functions/Macros 
			private:
			// Private Variables      
			private:
			};
			struct Colored {
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				glm::vec2 m_size;
				glm::vec2 m_texture_size;
				glm::vec4 m_color;
				glm::mat4 m_matrix;
				int32_t m_is_text;
				uint64_t m_texture_handle;
				static int32_t m_is_colored;
			// Private Functions/Macros 
			private:
			// Private Variables      
			private:
			};
			struct Matrix_Write {
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				uint32_t m_index;
				const glm::mat4* m_matrix;
			// Private Functions/Macros 
			private:
			// Private Variables      
			private:
			};
			class Draw_Command {
			public:
				uint32_t m_count;
				uint32_t m_instance_count;
				uint32_t m_first_index;
				uint32_t m_base_vertex;
				uint32_t m_base_instance;
				/* Error List: NONE */
				bool operator==(const Draw_Command& p_rhs) {
					return this->m_base_instance == p_rhs.m_base_instance;
				}
				bool operator>(const Draw_Command& p_rhs) {
					return this->m_base_instance > p_rhs.m_base_instance;
				}
				bool operator<(const Draw_Command& p_rhs) {
					return this->m_base_instance < p_rhs.m_base_instance;
				}
			};
			/* Error List: NONE */
			Mesh();
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			Mesh(Vertex_Data* p_vertices, const uint16_t& p_vertex_count, const uint32_t* p_indices, const uint16_t& p_indice_count);
			/* Error List: PW_GL_ERROR */
			~Mesh();
		private:
		// Public Functions/Macros 
		public:
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			std::pair<uint32_t, uint32_t> Add(const Non_Colored& p_data);
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			std::pair<uint32_t, uint32_t> Add(const Colored& p_data);
			/* Error List: PW_GL_ERROR */
			void Remove(uint32_t p_index, uint32_t p_model_matrix_index);
			/* Error List: PW_GL_ERROR */
			void Render(uint32_t p_index);
			/* Error List: PW_GL_ERROR */
			void Draw();
			/* Error List: PW_GL_ERROR */
			void Draw_Transparent();
			/* Error List: NONE */
			Vertex_Data* Vertices();
			/* Error List: NONE */
			const uint32_t& Vertex_Count() const;
			/* Error List: NONE */
			void Update_Vertices(Vertex_Data* p_new_vertices);
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			void Change_Color_Data(uint32_t p_index, const glm::vec4& p_new_color_data);
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			void Change_Texture_Data(uint32_t p_index, Vertex_Data* p_new_texture_data);
			/* Error List: PW_GL_ERROR */
			void Change_Matrix_Data(uint32_t p_index, uint32_t p_model_matrix_index, const glm::mat4* const p_matrix);
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			void Change_Texture_Handle(uint32_t p_index, const uint64_t& p_texture_handle);
			// Sets the texture handle as transparent internally so meshes know to render
			// them last
			// Error List: NONE
			static void Label_Transparent_Texture_Handle(const uint64_t& p_texture_handle);
			// The add function auto checks the texture_handle to see if its labeled as transparent but this
			// does not work for things that change texture but keep the render index, so add a function to
			// check a range of texture handle in relation to a index
			// Error List: NONE
			static void Validate_Multitex(uint32_t p_associated_index, const std::vector<uint64_t>& p_texture_handles);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			void Add_To_Buffer(Vertex_Data* p_data);
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			uint32_t Add_Matrix_To_SSBO(const glm::mat4* p_data);

			void Start_Sync_GPU();
			void End_Sync_GPU();

			/* Error List: PW_GL_ERROR */
			static void Initialize();
			/* Error List: PW_GL_ERROR */
			static void Release();
		// Private Variables      
		private:
			Vertex_Data* m_vertices;

			uint32_t m_vertex_count;
			uint32_t m_indice_count;

			uint32_t m_array_object;

			uint32_t m_buffer_object;
			// Size of m_buffer_object
			uint32_t m_bo_size;
			// Max size of m_buffer_object
			uint32_t m_bo_max_size;

			uint32_t m_element_object;

			uint32_t m_draw_command_object;
			uint32_t m_transparent_draw_command_object;

			uint32_t m_dc_size;
			uint32_t m_last_dc_size;
			bool m_dcv_changed;

			std::vector<Draw_Command> m_draw_indices;

			uint32_t m_tdc_size;
			uint32_t m_last_tdc_size;
			bool m_tdcv_changed;

			std::vector<Draw_Command> m_transparent_draw_indices;

			std::vector<uint32_t> m_render_index_free_spaces;

			static uint32_t m_model_object;
			// Size of m_model_object
			static uint32_t m_mo_size;
			// Max size of m_model_object
			static uint32_t m_mo_max_size;

			static glm::mat4* m_model_access;
			// The sync object for the model access
			static GLsync m_model_access_sync;

			// The size of the buffer this frame
			static uint32_t m_mo_size_tframe;
			// Max size of the vector, if the vector is cleared then the size will be set to 0
			// despite having the memory for the previous size
			static uint32_t m_mo_marr_max_size;
			static std::vector<uint32_t> m_mo_free_spaces;
			static std::vector<Matrix_Write> m_matrix_array_access;
			// Transparent textures must be rendered last or it leads to problems
			// Store texture_handles relating to such textures and then label indices that
			// render the textures
			static std::set<uint64_t> m_transparent_textures;
			static std::set<uint32_t> m_transparent_indices;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_MESH