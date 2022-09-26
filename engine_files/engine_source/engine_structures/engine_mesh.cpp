#include "engine_structures\engine_mesh.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Vertex_Data
		// Static Declarations   
		// Class Members
			Vertex_Data::Vertex_Data() :
					m_vertex_position{ glm::vec3(0.0f, 0.0f, 0.0f) }, m_texture_coord{ glm::vec2(0.0f, 0.0f) },
					m_color_data{ glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) } {
			}
			Vertex_Data::Vertex_Data(const glm::vec3& p_vertex_position, const glm::vec2& p_texture_coord) :
					m_vertex_position{ p_vertex_position }, m_texture_coord{ p_texture_coord },
					m_color_data{ glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) } {
			}
			Vertex_Data::~Vertex_Data() {
			}
			void Vertex_Data::Set_Vertex_Position(const glm::vec3& p_vertex_position) {
				m_vertex_position = p_vertex_position;
			}
			void Vertex_Data::Set_Texture_Coord(const glm::vec2& p_texture_coord) {
				m_texture_coord = p_texture_coord;
			}
			void Vertex_Data::Set_Color_Data(const glm::vec4& p_color_data) {
				m_color_data = p_color_data;
			}
			const glm::vec3& Vertex_Data::Vertex_Position() const {
				return m_vertex_position;
			}
			const glm::vec2& Vertex_Data::Texture_Coord() const {
				return m_texture_coord;
			}
			const glm::vec4& Vertex_Data::Color_Data() const {
				return m_color_data;
			}
		// End of Class Members
		// Mesh              
		// Static Declarations 
		// Class Members           
			Mesh::Mesh() :
					m_vertices{ nullptr }, m_indice_count{ 0 }, m_vertex_count{ 0 }, m_vertex_array_object{ 0 },
					m_vertex_buffer_object{ 0 }, m_vertex_texture_object{ 0 }, m_vertex_color_object{ 0 }, m_vertex_element_object{ 0 } {
			}
			Mesh::Mesh(Vertex_Data* p_vertices, const uint16_t& p_vertex_count, const uint32_t* p_indices, const uint16_t& p_indice_count, const glm::vec2& p_size, const glm::vec2& p_texture_size) :
					m_vertices{ nullptr }, m_indice_count{ p_indice_count }, m_vertex_count{ p_vertex_count }, m_vertex_array_object{ 0 },
					m_vertex_buffer_object{ 0 }, m_vertex_texture_object{ 0 }, m_vertex_color_object{ 0 }, m_vertex_element_object{ 0 } {
				try {
					m_vertices = p_vertices;

					for (size_t i = 0; i < p_vertex_count; i++) {
						m_vertices[i] = p_vertices[i];
					}

					PW_GL_VOID_CALL(glGenVertexArrays(1, &m_vertex_array_object), false);
					PW_GL_VOID_CALL(glBindVertexArray(m_vertex_array_object), false);

					glm::vec3* v_vertex_position_arr = pw::Engine_Memory::Allocate<glm::vec3>(m_vertex_count);
					glm::vec2* v_texture_data_arr = pw::Engine_Memory::Allocate<glm::vec2>(m_vertex_count);
					glm::vec4* v_color_data = pw::Engine_Memory::Allocate<glm::vec4>(m_vertex_count);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_vertex_position_arr[i] = glm::vec3(
							m_vertices[i].Vertex_Position().x - 0.5f,
							m_vertices[i].Vertex_Position().y + 0.5f,
							m_vertices[i].Vertex_Position().z);
						v_texture_data_arr[i] = glm::vec2(
							m_vertices[i].Texture_Coord().x * (p_size.x / p_texture_size.x),
							m_vertices[i].Texture_Coord().y * (p_size.y / p_texture_size.y)
						);
						v_color_data[i] = m_vertices[i].Color_Data();
					}

					// Use the vertex_buffer_object for positions inside the vertex shader
					glGenBuffers(1, &m_vertex_buffer_object);
					glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
					glBufferData(GL_ARRAY_BUFFER, m_vertex_count *
						sizeof(v_vertex_position_arr[0]), &v_vertex_position_arr[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

					// Use vertex_texture_object to handle texture coordinates
					glGenBuffers(1, &m_vertex_texture_object);
					glBindBuffer(GL_ARRAY_BUFFER, m_vertex_texture_object);
					glBufferData(GL_ARRAY_BUFFER, m_vertex_count *
						sizeof(v_texture_data_arr[0]), &v_texture_data_arr[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

					// Use vertex_color_data to handle color data
					glGenBuffers(1, &m_vertex_color_object);
					glBindBuffer(GL_ARRAY_BUFFER, m_vertex_color_object);
					glBufferData(GL_ARRAY_BUFFER, m_vertex_count *
						sizeof(v_color_data[0]), &v_color_data[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

					// Use vertex_element_buffer to handle index drawing
					glGenBuffers(1, &m_vertex_element_object);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertex_element_object);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indice_count *
						sizeof(p_indices[0]), &p_indices[0], GL_STATIC_DRAW);

					glBindBuffer(GL_ARRAY_BUFFER, 0);

					glEnableVertexAttribArray(3);
					glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
					glEnableVertexAttribArray(4);
					glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
					glEnableVertexAttribArray(5);
					glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
					glEnableVertexAttribArray(6);
					glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

					glVertexAttribDivisor(3, 1);
					glVertexAttribDivisor(4, 1);
					glVertexAttribDivisor(5, 1);
					glVertexAttribDivisor(6, 1);

					glBindVertexArray(0);

					if (pw::Engine_Memory::Deallocate<glm::vec3>(v_vertex_position_arr) == false) {
						if (v_vertex_position_arr != nullptr) {
							delete[] v_vertex_position_arr;
							v_vertex_position_arr = nullptr;
						}
					}
					if(pw::Engine_Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}
					if (pw::Engine_Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			Mesh::~Mesh() {
				glDeleteVertexArrays(1, &m_vertex_array_object);
				glDeleteBuffers(1, &m_vertex_buffer_object);
				glDeleteBuffers(1, &m_vertex_texture_object);
				glDeleteBuffers(1, &m_vertex_color_object);
				glDeleteBuffers(1, &m_vertex_element_object);
			}
			void Mesh::Draw() {
				try {
					glBindVertexArray(m_vertex_array_object);

					if (TRY_LINE m_indice_count == 0) {
						throw pw::er::Warning_Error(L"Mesh", L"draw_count == 0", EXCEPTION_LINE, __FILEW__, L"Draw");
					}
					glDrawElements(GL_TRIANGLES, m_indice_count, GL_UNSIGNED_INT, 0);

					glBindVertexArray(0);
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
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
			void Mesh::Change_Color_Data(const glm::vec4& p_new_color_data) {
				try {
					glm::vec4* v_color_data = pw::Engine_Memory::Allocate<glm::vec4>(m_vertex_count);
					for (size_t i = 0; i < m_vertex_count; i++) {
						v_color_data[i] = p_new_color_data;
					}
					glBindBuffer(GL_ARRAY_BUFFER, m_vertex_color_object);
					glBufferData(GL_ARRAY_BUFFER, m_vertex_count *
						sizeof(v_color_data[0]), &v_color_data[0], GL_STATIC_DRAW);
					if (pw::Engine_Memory::Deallocate<glm::vec4>(v_color_data) == false) {
						if (v_color_data != nullptr) {
							delete[] v_color_data;
							v_color_data = nullptr;
						}
					}

					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void Mesh::Change_Texture_Data(Vertex_Data* new_texture_data) {
				try {
					glm::vec2* v_texture_data_arr = pw::Engine_Memory::Allocate<glm::vec2>(m_vertex_count);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_texture_data_arr[i] = new_texture_data[i].Texture_Coord();
					}

					glBindBuffer(GL_ARRAY_BUFFER, m_vertex_texture_object);
					glBufferData(GL_ARRAY_BUFFER, m_vertex_count *
						sizeof(v_texture_data_arr[0]), &v_texture_data_arr[0], GL_STATIC_DRAW);
					if (pw::Engine_Memory::Deallocate<glm::vec2>(v_texture_data_arr) == false) {
						if (v_texture_data_arr != nullptr) {
							delete[] v_texture_data_arr;
							v_texture_data_arr = nullptr;
						}
					}

					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////