#include "structures\mesh.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		// Vertex_Data
		// Static Declarations   
		// Class Members
			Vertex_Data::Vertex_Data() :
					m_vertex_position{ glm::vec3(0.0f, 0.0f, 0.0f) }, m_texture_coord{ glm::vec2(0.0f, 0.0f) } {
			}
			Vertex_Data::Vertex_Data(const glm::vec3& p_vertex_position, const glm::vec2& p_texture_coord) :
					m_vertex_position{ p_vertex_position }, m_texture_coord{ p_texture_coord } {
			}
			Vertex_Data::~Vertex_Data() {
			}
			void Vertex_Data::Set_Vertex_Position(const glm::vec3& p_vertex_position) {
				m_vertex_position = p_vertex_position;
			}
			void Vertex_Data::Set_Texture_Coord(const glm::vec2& p_texture_coord) {
				m_texture_coord = p_texture_coord;
			}
			const glm::vec3& Vertex_Data::Vertex_Position() const {
				return m_vertex_position;
			}
			const glm::vec2& Vertex_Data::Texture_Coord() const {
				return m_texture_coord;
			}
		// Mesh
			// Non_Colored
			// Static Declarations 
				int32_t Mesh::Non_Colored::m_is_colored = 0;
			// Class Members  
			// Colored
			// Static Declarations 
				int32_t Mesh::Colored::m_is_colored = 1;
			// Class Members  
		// Static Declarations
		// Class Members    
			Mesh::Mesh() :
					m_vertices{ nullptr }, m_vertex_count{ 0 }, m_indice_count{ 0 }, m_array_object{ 0 },
					m_position_object{ 0 }, m_element_object{ 0 }, m_draw_command_object{ 0 }, m_draw_command_size{ 0 }, m_last_draw_size{ 0 }, m_draw_command_max_size{ 1 },
					m_frame_changed{ true }, m_draw_indices{}, m_render_index_free_spaces{}, m_mo_size_tframe{ 0 }, m_mo_marr_max_size{ 0 },
					m_texture_object{ 0 }, m_to_size{ 0 }, m_to_max_size{ 1 }, m_to_free_spaces{},
					m_color_object{ 0 }, m_co_size{ 0 }, m_co_max_size{ 1 }, m_co_free_spaces{},
					m_model_object{ 0 }, m_mo_size{ 0 }, m_mo_max_size{ 1 }, m_mo_free_spaces{},
					m_is_colored_object{ 0 }, m_ico_size{ 0 }, m_ico_max_size{ 1 }, m_ico_free_spaces{},
					m_is_text_object{ 0 }, m_ito_size{ 0 }, m_ito_max_size{ 1 }, m_ito_free_spaces{},
					m_texture_handle_object{ 0 }, m_tho_size{ 0 }, m_tho_max_size{ 1 }, m_tho_free_spaces{}, m_color_array_storage{ nullptr } {
			}
			Mesh::Mesh(Vertex_Data* p_vertices, const uint16_t& p_vertex_count, const uint32_t* p_indices, const uint16_t& p_indice_count) :
					m_vertices{ nullptr }, m_vertex_count{ p_vertex_count }, m_indice_count{ p_indice_count }, m_array_object{ 0 },
					m_position_object{ 0 }, m_element_object{ 0 }, m_draw_command_object{ 0 }, m_draw_command_size{ 0 }, m_last_draw_size{ 0 }, m_draw_command_max_size{ 1 },
					m_frame_changed{ true }, m_draw_indices{}, m_render_index_free_spaces{}, m_mo_size_tframe{ 0 }, m_mo_marr_max_size{ 0 },
					m_texture_object{ 0 }, m_to_size{ 0 }, m_to_max_size{ 1 }, m_to_free_spaces{},
					m_color_object{ 0 }, m_co_size{ 0 }, m_co_max_size{ 1 }, m_co_free_spaces{},
					m_model_object{ 0 }, m_mo_size{ 0 }, m_mo_max_size{ 1 }, m_mo_free_spaces{},
					m_is_colored_object{ 0 }, m_ico_size{ 0 }, m_ico_max_size{ 1 }, m_ico_free_spaces{},
					m_is_text_object{ 0 }, m_ito_size{ 0 }, m_ito_max_size{ 1 }, m_ito_free_spaces{},
					m_texture_handle_object{ 0 }, m_tho_size{ 0 }, m_tho_max_size{ 1 }, m_tho_free_spaces{}, m_color_array_storage{ nullptr }, m_color_array_access{}, m_matrix_array_access{} {
				m_vertices = p_vertices;

				for (size_t i = 0; i < p_vertex_count; i++) {
					m_vertices[i] = p_vertices[i];
				}

				PW_GL_VOID_CALL(glGenVertexArrays(1, &m_array_object), true, false);
				PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);

				glm::vec3* v_vertex_position_arr{ nullptr };
				PW_CALL(v_vertex_position_arr = pw::co::Memory::Allocate<glm::vec3>(m_vertex_count), false);

				if (v_vertex_position_arr == nullptr) {
					return;
				}

				for (size_t i = 0; i < m_vertex_count; i++) {
					v_vertex_position_arr[i] = glm::vec3(
						m_vertices[i].Vertex_Position().x - 0.5f,
						m_vertices[i].Vertex_Position().y + 0.5f,
						m_vertices[i].Vertex_Position().z);
				}

				PW_GL_VOID_CALL(glGenBuffers(1, &m_draw_command_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_draw_command_object), true, false);

				constexpr uint32_t v_draw_command_buffer_size = sizeof(Draw_Command);

				PW_GL_VOID_CALL(
					glBufferData(GL_DRAW_INDIRECT_BUFFER, MUL_UINT64(v_draw_command_buffer_size, m_draw_command_max_size), nullptr, GL_DYNAMIC_DRAW),
					true, false
				);
				
				PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0), true, false);

				// Use the vertex_buffer_object for positions inside the vertex shader
				PW_GL_VOID_CALL(glGenBuffers(1, &m_position_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_position_object), true, false);
				PW_GL_VOID_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(m_vertex_count *
					sizeof(v_vertex_position_arr[0])), &v_vertex_position_arr[0], GL_STATIC_DRAW), true, false);

				PW_GL_VOID_CALL(glEnableVertexAttribArray(0), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0), true, false);

				// Use vertex_texture_object to handle texture coordinates
				PW_GL_VOID_CALL(glGenBuffers(1, &m_texture_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_object), true, false);

				constexpr uint32_t v_texture_unit_size = 2 * sizeof(float);

				PW_GL_VOID_CALL(
					glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_texture_unit_size, m_to_max_size)), nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glEnableVertexAttribArray(1), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, v_texture_unit_size, (void*)0), true, false);

				//PW_GL_VOID_CALL(glVertexAttribDivisor(1, 1), true, false);

				// Use vertex_color_data to handle color data
				PW_GL_VOID_CALL(glGenBuffers(1, &m_color_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_color_object), true, false);

				constexpr uint32_t v_color_unit_size = 4 * sizeof(float);

				PW_GL_VOID_CALL(
					glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_color_unit_size, m_co_max_size)), nullptr, GL_DYNAMIC_DRAW),
					true, false
				);
				
				PW_GL_VOID_CALL(glEnableVertexAttribArray(2), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, MUL_UINT64(m_vertex_count, v_color_unit_size), (void*)0), true, false);
				PW_GL_VOID_CALL(glVertexAttribDivisor(2, 1), true, false);
				
				// Use vertex_element_buffer to handle index drawing
				PW_GL_VOID_CALL(glGenBuffers(1, &m_element_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_object), true, false);
				PW_GL_VOID_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, TO_INT64(m_indice_count *
					sizeof(p_indices[0])), &p_indices[0], GL_STATIC_DRAW), true, false);

				PW_GL_VOID_CALL(glGenBuffers(1, &m_model_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_model_object), true, false);

				PW_GL_VOID_CALL(
					glBufferData(GL_ARRAY_BUFFER, TO_INT64(sizeof(glm::mat4)) * m_mo_max_size, nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glEnableVertexAttribArray(3), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0), true, false);
				PW_GL_VOID_CALL(glEnableVertexAttribArray(4), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4))), true, false);
				PW_GL_VOID_CALL(glEnableVertexAttribArray(5), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4))), true, false);
				PW_GL_VOID_CALL(glEnableVertexAttribArray(6), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4))), true, false);
				
				PW_GL_VOID_CALL(glVertexAttribDivisor(3, 1), true, false);
				PW_GL_VOID_CALL(glVertexAttribDivisor(4, 1), true, false);
				PW_GL_VOID_CALL(glVertexAttribDivisor(5, 1), true, false);
				PW_GL_VOID_CALL(glVertexAttribDivisor(6, 1), true, false);

				PW_GL_VOID_CALL(glGenBuffers(1, &m_is_colored_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_is_colored_object), true, false);

				constexpr uint32_t v_is_colored_unit_size = 1 * sizeof(int32_t);

				PW_GL_VOID_CALL(
					glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_is_colored_unit_size, m_ico_max_size)), nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glEnableVertexAttribArray(7), true, false);
				PW_GL_VOID_CALL(glVertexAttribIPointer(7, 1, GL_INT, MUL_UINT64(m_vertex_count, v_is_colored_unit_size), (void*)0), true, false);

				PW_GL_VOID_CALL(glVertexAttribDivisor(7, 1), true, false);

				PW_GL_VOID_CALL(glGenBuffers(1, &m_is_text_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_is_text_object), true, false);

				constexpr uint32_t v_is_text_unit_size = 1 * sizeof(int32_t);

				PW_GL_VOID_CALL(
					glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_is_text_unit_size, m_ito_max_size)), nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glEnableVertexAttribArray(8), true, false);
				PW_GL_VOID_CALL(glVertexAttribIPointer(8, 1, GL_INT, MUL_UINT64(m_vertex_count, v_is_text_unit_size), (void*)0), true, false);

				PW_GL_VOID_CALL(glVertexAttribDivisor(8, 1), true, false);

				PW_GL_VOID_CALL(glGenBuffers(1, &m_texture_handle_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_handle_object), true, false);

				constexpr uint32_t v_texture_handle_unit_size = 1 * sizeof(uint64_t);
				
				PW_GL_VOID_CALL(
					glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_texture_handle_unit_size, m_tho_max_size)), nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glEnableVertexAttribArray(9), true, false);
				PW_GL_VOID_CALL(glVertexAttribLPointer(9, 1, GL_UNSIGNED_INT64_ARB, MUL_UINT64(m_vertex_count, v_texture_handle_unit_size), (void*)0), true, false);

				PW_GL_VOID_CALL(glVertexAttribDivisor(9, 1), true, false);

				PW_GL_VOID_CALL(glBindVertexArray(0), true, false);

				if (pw::co::Memory::Deallocate<glm::vec3>(v_vertex_position_arr) == false) {
					if (v_vertex_position_arr != nullptr) {
						delete[] v_vertex_position_arr;
						v_vertex_position_arr = nullptr;
					}
				}
			}
			Mesh::~Mesh() {
				PW_GL_VOID_CALL(glDeleteVertexArrays(1, &m_array_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_position_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_texture_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_color_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_element_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_model_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_is_colored_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_is_text_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_texture_handle_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_draw_command_object), true, false);
			}
			uint32_t Mesh::Add(const Non_Colored& p_data) {
				glm::vec2* v_texture_data_arr{ nullptr };
				PW_CALL(v_texture_data_arr = pw::co::Memory::Allocate<glm::vec2>(m_vertex_count), false);

				if (v_texture_data_arr == nullptr) {
					return 0;
				}

				glm::vec4* v_color_data{ nullptr };
				PW_CALL(v_color_data = pw::co::Memory::Allocate<glm::vec4>(m_vertex_count), false);

				if (v_color_data == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					return 0;
				}

				int32_t* v_is_colored{ nullptr };
				PW_CALL(v_is_colored = pw::co::Memory::Allocate<int32_t>(m_vertex_count), false);

				if (v_is_colored == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
					return 0;
				}

				int32_t* v_is_text{ nullptr };
				PW_CALL(v_is_text = pw::co::Memory::Allocate<int32_t>(m_vertex_count), false);

				if (v_is_text == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<int32_t>(v_is_colored) == false) {
						if (v_is_colored != nullptr) {
							delete[] v_is_colored;
							v_is_colored = nullptr;
						}
					}
					return 0;
				}

				uint64_t* v_texture_handle{ nullptr };
				PW_CALL(v_texture_handle = pw::co::Memory::Allocate<uint64_t>(m_vertex_count), false);

				if (v_texture_handle == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<int32_t>(v_is_colored) == false) {
						if (v_is_colored != nullptr) {
							delete[] v_is_colored;
							v_is_colored = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<int32_t>(v_is_text) == false) {
						if (v_is_text != nullptr) {
							delete[] v_is_text;
							v_is_text = nullptr;
						}
					}
					return 0;
				}
				for (size_t i = 0; i < m_vertex_count; i++) {
					v_texture_data_arr[i] = glm::vec2(
						m_vertices[i].Texture_Coord().x * (p_data.m_size.x / p_data.m_texture_size.x),
						m_vertices[i].Texture_Coord().y * (p_data.m_size.y / p_data.m_texture_size.y)
					);
					v_color_data[i] = glm::vec4(0.0f);
					v_is_colored[i] = Non_Colored::m_is_colored;
					v_is_text[i] = p_data.m_is_text;
					v_texture_handle[i] = p_data.m_texture_handle;
				}
				PW_GL_CUSTOM_CALL(glBindVertexArray(m_array_object), true, false, uint32_t);
				// Texture
				Add_To_Buffer<glm::vec2>(m_texture_object, m_to_size, m_to_max_size, m_to_free_spaces, v_texture_data_arr);
				// Color
				Add_To_Buffer<glm::vec4>(m_color_object, m_co_size, m_co_max_size, m_co_free_spaces, v_color_data);
				// Model Matrix
				Add_To_Matrix_Buffer(m_model_object, m_mo_size, m_mo_max_size, m_mo_free_spaces, p_data.m_matrix);
				// Is_Colored
				Add_To_Buffer<int32_t>(m_is_colored_object, m_ico_size, m_ico_max_size, m_ico_free_spaces, v_is_colored);
				// Is_Text
				Add_To_Buffer<int32_t>(m_is_text_object, m_ito_size, m_ito_max_size, m_ito_free_spaces, v_is_text);
				// Texture_Handle
				Add_To_Buffer<uint64_t>(m_texture_handle_object, m_tho_size, m_tho_max_size, m_tho_free_spaces, v_texture_handle);

				PW_GL_CUSTOM_CALL(glBindVertexArray(0), true, false, uint32_t);

				if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
					if (v_texture_data_arr != nullptr) {
						delete[] v_texture_data_arr;
						v_texture_data_arr = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
					if (v_color_data != nullptr) {
						delete[] v_color_data;
						v_color_data = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<int32_t>(v_is_colored) == false) {
					if (v_is_colored != nullptr) {
						delete[] v_is_colored;
						v_is_colored = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<int32_t>(v_is_text) == false) {
					if (v_is_text != nullptr) {
						delete[] v_is_text;
						v_is_text = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<uint64_t>(v_texture_handle) == false) {
					if (v_texture_handle != nullptr) {
						delete[] v_texture_handle;
						v_texture_handle = nullptr;
					}
				}
				// Make sure they are all the same size
				if ((m_to_size == m_co_size) &&
						(m_to_size == m_mo_size) &&
						(m_to_size == m_ico_size) &&
						(m_to_size == m_ito_size) &&
						(m_to_size == m_tho_size)) {
					if (m_to_size >= 1) {
						if (m_render_index_free_spaces.size() > 0) {
							uint32_t v_temp_return = m_render_index_free_spaces[0];

							m_render_index_free_spaces.erase(m_render_index_free_spaces.begin());

							return v_temp_return;
						}
						return m_to_size - 1;
					}
					else {
						// Something went wrong if the size is not greater than 0
						return 0;
					}
				}
				else {
					return 0;
				}
			}
			uint32_t Mesh::Add(const Colored& p_data) {
				glm::vec2* v_texture_data_arr{ nullptr };
				PW_CALL(v_texture_data_arr = pw::co::Memory::Allocate<glm::vec2>(m_vertex_count), false);

				if (v_texture_data_arr == nullptr) {
					return 0;
				}

				glm::vec4* v_color_data{ nullptr };
				PW_CALL(v_color_data = pw::co::Memory::Allocate<glm::vec4>(m_vertex_count), false);

				if (v_color_data == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					return 0;
				}

				int32_t* v_is_colored{ nullptr };
				PW_CALL(v_is_colored = pw::co::Memory::Allocate<int32_t>(m_vertex_count), false);

				if (v_is_colored == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
					return 0;
				}

				int32_t* v_is_text{ nullptr };
				PW_CALL(v_is_text = pw::co::Memory::Allocate<int32_t>(m_vertex_count), false);

				if (v_is_text == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<int32_t>(v_is_colored) == false) {
						if (v_is_colored != nullptr) {
							delete[] v_is_colored;
							v_is_colored = nullptr;
						}
					}
					return 0;
				}

				uint64_t* v_texture_handle{ nullptr };
				PW_CALL(v_texture_handle = pw::co::Memory::Allocate<uint64_t>(m_vertex_count), false);

				if (v_texture_handle == nullptr) {
					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<int32_t>(v_is_colored) == false) {
						if (v_is_colored != nullptr) {
							delete[] v_is_colored;
							v_is_colored = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<int32_t>(v_is_text) == false) {
						if (v_is_text != nullptr) {
							delete[] v_is_text;
							v_is_text = nullptr;
						}
					}
					return 0;
				}
				for (size_t i = 0; i < m_vertex_count; i++) {
					v_texture_data_arr[i] = glm::vec2(
						m_vertices[i].Texture_Coord().x * (p_data.m_size.x / p_data.m_texture_size.x),
						m_vertices[i].Texture_Coord().y * (p_data.m_size.y / p_data.m_texture_size.y)
					);
					v_color_data[i] = p_data.m_color;
					v_is_colored[i] = Colored::m_is_colored;
					v_is_text[i] = p_data.m_is_text;
					v_texture_handle[i] = p_data.m_texture_handle;
				}
				PW_GL_CUSTOM_CALL(glBindVertexArray(m_array_object), true, false, uint32_t);
				// Texture
				Add_To_Buffer<glm::vec2>(m_texture_object, m_to_size, m_to_max_size, m_to_free_spaces, v_texture_data_arr);
				// Color
				Add_To_Buffer<glm::vec4>(m_color_object, m_co_size, m_co_max_size, m_co_free_spaces, v_color_data);
				// Model Matrix
				Add_To_Matrix_Buffer(m_model_object, m_mo_size, m_mo_max_size, m_mo_free_spaces, p_data.m_matrix);
				// Is_Colored
				Add_To_Buffer<int32_t>(m_is_colored_object, m_ico_size, m_ico_max_size, m_ico_free_spaces, v_is_colored);
				// Is_Text
				Add_To_Buffer<int32_t>(m_is_text_object, m_ito_size, m_ito_max_size, m_ito_free_spaces, v_is_text);
				// Texture_Handle
				Add_To_Buffer<uint64_t>(m_texture_handle_object, m_tho_size, m_tho_max_size, m_tho_free_spaces, v_texture_handle);

				PW_GL_CUSTOM_CALL(glBindVertexArray(0), true, false, uint32_t);

				if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
					if (v_texture_data_arr != nullptr) {
						delete[] v_texture_data_arr;
						v_texture_data_arr = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<glm::vec4>(v_color_data) == false) {
					if (v_color_data != nullptr) {
						delete[] v_color_data;
						v_color_data = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<int32_t>(v_is_colored) == false) {
					if (v_is_colored != nullptr) {
						delete[] v_is_colored;
						v_is_colored = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<int32_t>(v_is_text) == false) {
					if (v_is_text != nullptr) {
						delete[] v_is_text;
						v_is_text = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<uint64_t>(v_texture_handle) == false) {
					if (v_texture_handle != nullptr) {
						delete[] v_texture_handle;
						v_texture_handle = nullptr;
					}
				}
				// Make sure they are all the same size
				if ((m_to_size == m_co_size) &&
					(m_to_size == m_mo_size) &&
					(m_to_size == m_ico_size) &&
					(m_to_size == m_ito_size) &&
					(m_to_size == m_tho_size)) {
					if (m_to_size >= 1) {
						if (m_render_index_free_spaces.size() > 0) {
							uint32_t v_temp_return = m_render_index_free_spaces[0];

							m_render_index_free_spaces.erase(m_render_index_free_spaces.begin());

							return v_temp_return;
						}
						return m_to_size - 1;
					}
					else {
						// Something went wrong if the size is not greater than 0
						return 0;
					}
				}
				else {
					return 0;
				}
			}
			void Mesh::Remove(uint32_t p_index) {
				// Removing the data from the OpenGL buffer would be
				// too resource intensive to overwrite the old info
				// so just label the space as open for new data.
				m_to_free_spaces.push_back(p_index);
				m_co_free_spaces.push_back(p_index);
				m_mo_free_spaces.push_back(p_index);
				m_ico_free_spaces.push_back(p_index);
				m_ito_free_spaces.push_back(p_index);
				m_tho_free_spaces.push_back(p_index);

				m_render_index_free_spaces.push_back(p_index);

				m_to_size = m_to_size - 1;
				m_co_size = m_co_size - 1;
				m_mo_size = m_mo_size - 1;
				m_ico_size = m_ico_size - 1;
				m_ito_size = m_ito_size - 1;
				m_tho_size = m_tho_size - 1;
			}
			void Mesh::Render(uint32_t p_index) {
				constexpr uint32_t OBJECT_SIZE = sizeof(glm::vec2) + sizeof(glm::vec4) + sizeof(glm::mat4) + sizeof(int32_t) + sizeof(int32_t) + sizeof(uint64_t);
				constexpr uint32_t v_unit_size = sizeof(Draw_Command);
				// The add function guarantee's that 
				// p_index if correct is m_to_size - 1
				// so test for any range 0 < p_index < m_to_size
				if (p_index < m_to_size) {
					Draw_Command v_temp{};

					v_temp.m_count = m_indice_count;
					v_temp.m_instance_count = 0;
					v_temp.m_first_index = 0;
					v_temp.m_base_vertex = 0;
					v_temp.m_base_instance = p_index;

					if (m_draw_indices.size() > p_index && m_draw_indices.size() > m_draw_command_size) {
						if (p_index != m_draw_indices[m_draw_command_size].m_base_instance) {
							m_frame_changed = true;
							m_draw_indices[m_draw_command_size] = v_temp;
						}
					}
					else {
						m_draw_indices.push_back(v_temp);
					}

					m_draw_command_size = m_draw_command_size + 1;
					if (m_draw_command_size >= m_draw_command_max_size) {
						uint32_t v_new_buffer_size = m_draw_command_max_size + TO_UINT32(m_draw_command_max_size * glm::golden_ratio<double>());

						PW_GL_VOID_CALL(
							glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_draw_command_object),
							true, false
						);

						PW_GL_VOID_CALL(
							glBufferData(GL_DRAW_INDIRECT_BUFFER, MUL_UINT64(v_unit_size, v_new_buffer_size), nullptr, GL_DYNAMIC_DRAW),
							true, false
						);

						PW_GL_VOID_CALL(
							glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0),
							true, false
						);
						m_draw_command_max_size = v_new_buffer_size;
					}
				}
			}
			void Mesh::Draw() {
				constexpr uint32_t v_unit_size = sizeof(Draw_Command);

				if (m_matrix_array_access.size() > 0) {
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_model_object), true, false);

					PW_GL_VOID_CALL(glm::mat4 * v_temp_mo_access = static_cast<glm::mat4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)), true, false);

					for (uint32_t i = 0; i < m_mo_size_tframe; i++) {
						v_temp_mo_access[m_matrix_array_access[i].first] = m_matrix_array_access[i].second;
					}

					PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER), true, false);

					if (m_matrix_array_access.size() > m_mo_marr_max_size) {
						m_mo_marr_max_size = TO_UINT32(m_matrix_array_access.size());
					}

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					m_mo_size_tframe = 0;
				}
				if (m_draw_command_size != 0) {
					PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_draw_command_object), true, false);

					if (m_last_draw_size != m_draw_command_size) {
						m_frame_changed = true;
					}

					if (m_frame_changed == true) {
						for (uint32_t i = 0; i < m_draw_indices.size(); i++) {
							m_draw_indices[i].m_instance_count = m_draw_command_size;
						}

						PW_GL_VOID_CALL(
							glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, MUL_UINT64(v_unit_size, m_draw_command_size), m_draw_indices.data()),
							true, false
						);
						m_last_draw_size = m_draw_command_size;
						m_frame_changed = false;
					}
					PW_GL_VOID_CALL(glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr), true, false);
					PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0), true, false);
					PW_GL_VOID_CALL(glBindVertexArray(0), true, false);
					m_draw_command_size = 0;
				}
			}
			Vertex_Data* Mesh::Vertices() {
				return m_vertices;
			}
			const uint32_t& Mesh::Vertex_Count() const {
				return m_vertex_count;
			}
			void Mesh::Update_Vertices(Vertex_Data* p_new_vertices) {
				for (size_t i = 0; i < m_vertex_count; i++) {
					m_vertices[i] = p_new_vertices[i];
				}
			}
			void Mesh::Change_Color_Data(uint32_t p_index, const glm::vec4& p_new_color_data) {
				constexpr uint32_t v_unit_size = sizeof(glm::vec4);
				if (p_index < m_to_size) {
					if (m_color_array_storage == nullptr) {
						PW_CALL(m_color_array_storage = pw::co::Memory::Allocate<glm::vec4>(m_vertex_count), true);
					}

					for (uint32_t i = 0; i < m_vertex_count; i++) {
						m_color_array_storage[i] = p_new_color_data;
					}
					
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_color_object), true, false);

					
					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(p_index, MUL_UINT64(v_unit_size, m_vertex_count)), MUL_UINT64(m_vertex_count, v_unit_size), &m_color_array_storage[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
			}
			void Mesh::Change_Texture_Data(uint32_t p_index, Vertex_Data* new_texture_data) {
				constexpr uint32_t v_unit_size = sizeof(glm::vec2);
				if (p_index < m_to_size) {
					glm::vec2* v_texture_data_arr{ nullptr };
					PW_CALL(v_texture_data_arr = pw::co::Memory::Allocate<glm::vec2>(m_vertex_count), true);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_texture_data_arr[i] = new_texture_data[i].Texture_Coord();
					}

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(p_index, MUL_UINT64(v_unit_size, m_vertex_count)), MUL_UINT64(m_vertex_count, v_unit_size), &v_texture_data_arr[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					if (pw::co::Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
			}
			void Mesh::Change_Matrix_Data(uint32_t p_index, const glm::mat4& p_matrix) {
				constexpr uint32_t v_unit_size = sizeof(glm::mat4);
				if (p_index < m_to_size) {
					if (ADD_UINT64(m_mo_marr_max_size, 1) > m_matrix_array_access.size() && m_matrix_array_access.size() != 0) {
						m_matrix_array_access[m_mo_size_tframe] = std::make_pair(p_index, p_matrix);
						m_mo_size_tframe = m_mo_size_tframe + 1;
						return;
					}
					m_matrix_array_access.push_back(std::make_pair(p_index, p_matrix));
					m_mo_size_tframe = m_mo_size_tframe + 1;
				}
			}
			void Mesh::Change_Texture_Handle(uint32_t p_index, const uint64_t& p_texture_handle) {
				constexpr uint32_t v_unit_size = sizeof(uint64_t);
				if (p_index < m_to_size) {
					uint64_t* v_texture_handle{ nullptr };
					PW_CALL(v_texture_handle = pw::co::Memory::Allocate<uint64_t>(m_vertex_count), true);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_texture_handle[i] = p_texture_handle;
					}
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_handle_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(p_index, MUL_UINT64(v_unit_size, m_vertex_count)), MUL_UINT64(m_vertex_count, v_unit_size), &v_texture_handle[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					if (pw::co::Memory::Deallocate<uint64_t>(v_texture_handle) == false) {
						if (v_texture_handle != nullptr) {
							delete[] v_texture_handle;
							v_texture_handle = nullptr;
						}
					}
				}
			}
	ST_NAMESPACE_END
PW_NAMESPACE_END
/*
* constexpr uint32_t v_texture_unit_size = 2 * sizeof(float);

				if (m_to_size < m_to_max_size) {
					m_to_size = m_to_size + 1;

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_object), true, false, uint32_t);

					PW_GL_CUSTOM_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, m_to_size * v_texture_unit_size * m_vertex_count, m_vertex_count * v_texture_unit_size, &v_texture_data_arr[0]),
						true, false, uint32_t
					);

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				}
				else {
					// m_to_size >= m_to_max_size
					// Prepare to read the old buffer data
					PW_GL_CUSTOM_CALL(
						glBindBuffer(GL_COPY_READ_BUFFER, m_texture_object),
						true, false, uint32_t
					);

					// Allocate new buffer
					uint32_t v_temp_buffer{ 0 };
					uint32_t v_new_buffer_size = TO_UINT32(m_to_max_size * glm::golden_ratio<double>());
					PW_GL_CUSTOM_CALL(
						glGenBuffers(1, &v_temp_buffer),
						true, false, uint32_t
					);
					PW_GL_CUSTOM_CALL(
						glBindBuffer(GL_COPY_WRITE_BUFFER, v_temp_buffer),
						true, false, uint32_t
					);
					PW_GL_CUSTOM_CALL(
						glBufferData(GL_COPY_WRITE_BUFFER, m_vertex_count * v_texture_unit_size * v_new_buffer_size, nullptr, GL_DYNAMIC_DRAW),
						true, false, uint32_t
					);

					// Write old buffer into new buffer
					PW_GL_CUSTOM_CALL(
						glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_to_max_size),
						true, false, uint32_t
					);
					// Set old buffer to new buffer
					// Might be memory leak
					m_texture_object = v_temp_buffer;
					m_to_max_size = v_new_buffer_size;
					// Insert element into new buffer
					m_to_size = m_to_size + 1;

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_object), true, false, uint32_t);

					PW_GL_CUSTOM_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, m_to_size * v_texture_unit_size * m_vertex_count, m_vertex_count * v_texture_unit_size, &v_texture_data_arr[0]),
						true, false, uint32_t
					);

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				}
				*/
		/*
		* // Texture
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_object), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(m_vertex_count *
					sizeof(v_texture_data_arr[0])), &v_texture_data_arr[0], GL_STATIC_DRAW), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				// Color
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_color_object), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(m_vertex_count *
					sizeof(v_color_data[0])), &v_color_data[0], GL_STATIC_DRAW), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				// Model Matrix
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_model_object), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(sizeof(glm::mat4)), glm::value_ptr(p_data.m_matrix), GL_DYNAMIC_DRAW), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				// Is_Colored
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_is_colored_object), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(sizeof(int32_t)* m_vertex_count), &v_is_colored[0], GL_STATIC_DRAW), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				// Is_Text
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_is_text_object), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(sizeof(int32_t)* m_vertex_count), &v_is_text[0], GL_STATIC_DRAW), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				// Texture_Handle
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_texture_handle_object), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBufferData(GL_ARRAY_BUFFER, TO_INT64(sizeof(uint64_t)* m_vertex_count), &v_texture_handle[0], GL_STATIC_DRAW), true, false, uint32_t);
				PW_GL_CUSTOM_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false, uint32_t);
				*/