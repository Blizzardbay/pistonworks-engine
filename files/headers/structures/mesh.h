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
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			glm::vec3 m_vertex_position;
			glm::vec2 m_texture_coord;
		};
		class Mesh {
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
			class Draw_Command {
			public:
				uint32_t m_count;
				uint32_t m_instance_count;
				uint32_t m_first_index;
				uint32_t m_base_vertex;
				uint32_t m_base_instance;
				/* Error List: NONE */
				bool operator==(const Draw_Command& p_rhs) {
					return this->m_count == p_rhs.m_count &&
						this->m_instance_count == p_rhs.m_instance_count &&
						this->m_first_index == p_rhs.m_first_index &&
						this->m_base_vertex == p_rhs.m_base_vertex &&
						this->m_base_instance == p_rhs.m_base_instance;
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
			uint32_t Add(const Non_Colored& p_data);
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			uint32_t Add(const Colored& p_data);
			/* Error List: NONE */
			void Remove(uint32_t p_index);
			/* Error List: PW_GL_ERROR */
			void Render(uint32_t p_index);
			/* Error List: PW_GL_ERROR */
			void Draw();
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
			void Change_Matrix_Data(uint32_t p_index, const glm::mat4& p_matrix);
			/* Error List: PW_FUNCTION_ERROR, PW_GL_ERROR */
			void Change_Texture_Handle(uint32_t p_index, const uint64_t& p_texture_handle);

			// The process of rendering will go as follows,
			// Change_, 
			// Queue_Render(instance_id)
			// Draw
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			template<class T> 
			void Add_To_Buffer(uint32_t& p_buffer_object, uint32_t& p_buffer_size, uint32_t& p_buffer_max_size, std::vector<uint32_t>& p_free_spaces, T* p_data) {
				constexpr uint32_t v_unit_size = sizeof(T);

				if (p_free_spaces.size() > 0) {
					p_buffer_size = p_buffer_size + 1;

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, p_buffer_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(p_free_spaces[0], MUL_UINT64(v_unit_size, m_vertex_count)), MUL_UINT64(m_vertex_count, v_unit_size), &p_data[0]),
						true, false
					);

					p_free_spaces.erase(p_free_spaces.begin());

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					return;
				}

				if (p_buffer_size < p_buffer_max_size) {
					p_buffer_size = p_buffer_size + 1;

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, p_buffer_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64((p_buffer_size - 1), v_unit_size)), MUL_UINT64(m_vertex_count, v_unit_size), &p_data[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
				else {
					PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);
					// m_size >= m_max_size
					// Allocate new buffer
					uint32_t v_new_buffer_size = p_buffer_max_size + TO_UINT32(p_buffer_max_size * glm::golden_ratio<double>());
					
					PW_GL_VOID_CALL(
						glBindBuffer(GL_ARRAY_BUFFER, p_buffer_object),
						true, false
					);

					PW_CALL(T* v_read_buffer = pw::co::Memory::Allocate<T>(MUL_UINT64(m_vertex_count, v_new_buffer_size)), true);

					PW_GL_VOID_CALL(
						T* v_temp_read_buffer = static_cast<T*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY)),
						true, false
					);

					for (uint32_t i = 0; i < MUL_UINT32(m_vertex_count, p_buffer_max_size); i++) {
						v_read_buffer[i] = v_temp_read_buffer[i];
					}
					for (uint32_t i = 0; i < m_vertex_count; i++) {
						v_read_buffer[(m_vertex_count * p_buffer_max_size) + i] = *p_data;
					}
					for (uint32_t i = MUL_UINT32(m_vertex_count, (p_buffer_max_size + 1)); i < MUL_UINT32(m_vertex_count, v_new_buffer_size); i++) {
						v_read_buffer[i] = T();
					}

					p_buffer_size = p_buffer_size + 1;

					PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER),
						true, false
					);
					PW_GL_VOID_CALL(
						glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_unit_size, v_new_buffer_size)), &v_read_buffer[0], GL_DYNAMIC_DRAW),
						true, false
					);
					
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					PW_GL_VOID_CALL(glBindVertexArray(0), true, false);

					if (pw::co::Memory::Deallocate<T>(v_read_buffer) == false) {
						if (v_read_buffer != nullptr) {
							delete[] v_read_buffer;
							v_read_buffer = nullptr;
						}
					}

					p_buffer_max_size = v_new_buffer_size;
				}
			}
			/* Error List: PW_GL_ERROR, PW_FUNCTION_ERROR */
			void Add_To_Matrix_Buffer(uint32_t& p_buffer_object, uint32_t& p_buffer_size, uint32_t& p_buffer_max_size, std::vector<uint32_t>& p_free_spaces, const glm::mat4& p_data) {
				constexpr uint32_t v_unit_size = sizeof(glm::mat4);

				if (p_free_spaces.size() > 0) {
					p_buffer_size = p_buffer_size + 1;

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, p_buffer_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(p_free_spaces[0], v_unit_size), v_unit_size, &p_data[0]),
						true, false
					);

					p_free_spaces.erase(p_free_spaces.begin());

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					return;
				}

				if (p_buffer_size < p_buffer_max_size) {
					p_buffer_size = p_buffer_size + 1;

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, p_buffer_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(p_buffer_size - 1, v_unit_size), v_unit_size, &p_data[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
				else {
					PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);
					// m_size >= m_max_size
					// Allocate new buffer
					uint32_t v_new_buffer_size = p_buffer_max_size + TO_UINT32(p_buffer_max_size * glm::golden_ratio<double>());

					PW_GL_VOID_CALL(
						glBindBuffer(GL_ARRAY_BUFFER, p_buffer_object),
						true, false
					);

					PW_CALL(glm::mat4* v_read_buffer = pw::co::Memory::Allocate<glm::mat4>(v_new_buffer_size), true);

					PW_GL_VOID_CALL(
						glm::mat4* v_temp_read_buffer = static_cast<glm::mat4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY)),
						true, false
					);

					for (uint32_t i = 0; i < p_buffer_max_size; i++) {
						v_read_buffer[i] = v_temp_read_buffer[i];
					}
					v_read_buffer[p_buffer_max_size] = p_data;
					for (uint32_t i = (p_buffer_max_size + 1); i < v_new_buffer_size; i++) {
						v_read_buffer[i] = glm::mat4();
					}

					p_buffer_size = p_buffer_size + 1;

					PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER),
						true, false
					);
					PW_GL_VOID_CALL(
						glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(v_unit_size, v_new_buffer_size), &v_read_buffer[0], GL_DYNAMIC_DRAW),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					PW_GL_VOID_CALL(glBindVertexArray(0), true, false);

					if (pw::co::Memory::Deallocate<glm::mat4>(v_read_buffer) == false) {
						if (v_read_buffer != nullptr) {
							delete[] v_read_buffer;
							v_read_buffer = nullptr;
						}
					}

					p_buffer_max_size = v_new_buffer_size;
				}
			}
		// Private Variables      
		private:
			Vertex_Data* m_vertices;

			uint32_t m_vertex_count;
			uint32_t m_indice_count;
			
			uint32_t m_array_object;

			uint32_t m_position_object;
			uint32_t m_element_object;

			uint32_t m_draw_command_object;
			uint32_t m_draw_command_size;
			uint32_t m_draw_command_max_size;

			uint32_t m_last_draw_size;
			bool m_frame_changed;

			std::vector<Draw_Command> m_draw_indices;
			std::vector<uint32_t> m_render_index_free_spaces;

			// Variable sized data stored within the arrays
			uint32_t m_texture_object;
			// Size of m_texture_object
			uint32_t m_to_size;
			// Max size of m_texture_object
			uint32_t m_to_max_size;
			// Open or free spaces in m_texture_object
			std::vector<uint32_t> m_to_free_spaces;

			uint32_t m_color_object;
			// Size of m_color_object
			uint32_t m_co_size;
			// Max size of m_color_object
			uint32_t m_co_max_size;
			// Open or free spaces in m_color_object
			std::vector<uint32_t> m_co_free_spaces;

			glm::vec4* m_color_array_storage;
			std::vector<glm::vec4> m_color_array_access;

			uint32_t m_model_object;
			// Size of m_model_object
			uint32_t m_mo_size;
			// Max size of m_model_object
			uint32_t m_mo_max_size;
			// Open or free spaces in m_model_object
			std::vector<uint32_t> m_mo_free_spaces;

			// The size of the buffer this frame
			uint32_t m_mo_size_tframe;
			// Max size of the vector, if the vector is cleared then the size will be set to 0
			// despite having the memory for the previous size
			uint32_t m_mo_marr_max_size;
			std::vector<std::pair<uint32_t, glm::mat4>> m_matrix_array_access;

			uint32_t m_is_colored_object;
			// Size of m_is_colored_object
			uint32_t m_ico_size;
			// Max size of m_is_colored_object
			uint32_t m_ico_max_size;
			// Open or free spaces in m_is_colored_object
			std::vector<uint32_t> m_ico_free_spaces;

			uint32_t m_is_text_object;
			// Size of m_is_text_object
			uint32_t m_ito_size;
			// Max size of m_is_text_object
			uint32_t m_ito_max_size;
			// Open or free spaces in m_is_text_object
			std::vector<uint32_t> m_ito_free_spaces;

			uint32_t m_texture_handle_object;
			// Size of m_texture_handle_object
			uint32_t m_tho_size;
			// Max size of m_texture_handle_object
			uint32_t m_tho_max_size;
			// Open or free spaces in m_texture_handle_object
			std::vector<uint32_t> m_tho_free_spaces;
		}; 
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_MESH