#include "structures\mesh.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		// Vertex_Data
		// Static Declarations   
		// Class Members
			Vertex_Data::Vertex_Data() :
				m_vertex_position{ 0.0f }, m_texture_coord{ 0.0f },
				m_color{ 0.0f }, m_is_colored{ 0 }, m_is_text{ 0 },
				m_model_index{ 0 }, m_texture_handle{ 0 } {
			}
			Vertex_Data::Vertex_Data(const glm::vec3& p_vertex_position, const glm::vec2& p_texture_coord) :
				m_vertex_position{ p_vertex_position }, m_texture_coord{ p_texture_coord },
				m_color{ 0.0f }, m_is_colored{ 0 }, m_is_text{ 0 },
				m_model_index{ 0 }, m_texture_handle{ 0 } {
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
			const glm::vec4& Vertex_Data::Color() const {
				return m_color;
			}
			void Vertex_Data::Set_Color(const glm::vec4& p_color) {
				m_color = p_color;
			}
			const uint32_t& Vertex_Data::Is_Colored() const {
				return m_is_colored;
			}
			void Vertex_Data::Set_Is_Colored(const uint32_t& p_is_colored) {
				m_is_colored = p_is_colored;
			}
			const uint32_t& Vertex_Data::Is_Text() const {
				return m_is_text;
			}
			void Vertex_Data::Set_Is_Text(const uint32_t& p_is_text) {
				m_is_text = p_is_text;
			}
			const uint32_t& Vertex_Data::Model_Index() const {
				return m_model_index;
			}
			void Vertex_Data::Set_Model_Index(const uint32_t& p_model_index) {
				m_model_index = p_model_index;
			}
			const uint64_t& Vertex_Data::Texture_Handle() const {
				return m_texture_handle;
			}
			void Vertex_Data::Set_Texture_Handle(const uint64_t& p_texture_handle) {
				m_texture_handle = p_texture_handle;
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
		uint32_t Mesh::m_model_object{ 0 };
		uint32_t Mesh::m_mo_size{ 0 };
		uint32_t Mesh::m_mo_max_size{ 1 };
		uint32_t Mesh::m_mo_size_tframe{ 0 };
		uint32_t Mesh::m_mo_marr_max_size{ 0 };
		std::vector<uint32_t> Mesh::m_mo_free_spaces{};
		std::vector<std::pair<uint32_t, glm::mat4>> Mesh::m_matrix_array_access{};
		std::set<uint64_t> Mesh::m_transparent_textures{};
		std::set<uint32_t> Mesh::m_transparent_indices{};
		// Class Members    
			Mesh::Mesh() :
				m_vertices{ nullptr }, m_vertex_count{ 0 }, m_indice_count{ 0 }, m_array_object{ 0 },
				m_buffer_object{ 0 }, m_bo_size{ 0 }, m_bo_max_size{ 1 }, m_element_object{ 0 }, m_draw_command_object{ 0 }, m_transparent_draw_command_object{ 0 }, m_dc_size{ 0 }, m_last_dc_size{ 0 }, m_dcv_changed{ false },
				m_draw_indices{}, m_tdc_size{ 0 }, m_last_tdc_size{ 0 }, m_tdcv_changed{ false }, m_transparent_draw_indices{}, m_render_index_free_spaces{}, m_matrix_index_converter{} {
			}
			Mesh::Mesh(Vertex_Data* p_vertices, const uint16_t& p_vertex_count, const uint32_t* p_indices, const uint16_t& p_indice_count) :
				m_vertices{ nullptr }, m_vertex_count{ p_vertex_count }, m_indice_count{ p_indice_count }, m_array_object{ 0 },
				m_buffer_object{ 0 }, m_bo_size{ 0 }, m_bo_max_size{ 1 }, m_element_object{ 0 }, m_draw_command_object{ 0 }, m_transparent_draw_command_object{ 0 }, m_dc_size{ 0 }, m_last_dc_size{ 0 }, m_dcv_changed{ false },
				m_draw_indices{}, m_tdc_size{ 0 }, m_last_tdc_size{ 0 }, m_tdcv_changed{ false }, m_transparent_draw_indices{}, m_render_index_free_spaces{}, m_matrix_index_converter{} {
				m_vertices = p_vertices;

				for (size_t i = 0; i < p_vertex_count; i++) {
					m_vertices[i] = p_vertices[i];
				}

				PW_GL_VOID_CALL(glGenVertexArrays(1, &m_array_object), true, false);
				PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);

				Vertex_Data* v_vertex_data_arr{ nullptr };
				PW_CALL(v_vertex_data_arr = pw::co::Memory::Allocate<Vertex_Data>(m_vertex_count), false);

				if (v_vertex_data_arr == nullptr) {
					return;
				}

				for (size_t i = 0; i < m_vertex_count; i++) {
					v_vertex_data_arr[i].Set_Vertex_Position(glm::vec3(
						m_vertices[i].Vertex_Position().x - 0.5f,
						m_vertices[i].Vertex_Position().y + 0.5f,
						m_vertices[i].Vertex_Position().z));
				}

				// Per-Model vertex data
				PW_GL_VOID_CALL(glGenBuffers(1, &m_buffer_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

				// 4 bytes of padding get added on by the compiler, since OpenGL does not care about padding
				// tightly pack the array data on the GPU
				constexpr uint32_t v_buffer_object_size = sizeof(Vertex_Data);

				PW_GL_VOID_CALL(glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(MUL_UINT64(v_buffer_object_size, m_vertex_count), m_bo_max_size), &v_vertex_data_arr[0], GL_DYNAMIC_DRAW), true, false);

				// Everything is tightly packed so there is no offset to the data
				// Position
				PW_GL_VOID_CALL(glEnableVertexAttribArray(0), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, v_buffer_object_size, (void*)0), true, false);
				// Texture coords
				PW_GL_VOID_CALL(glEnableVertexAttribArray(1), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, v_buffer_object_size, (void*)(3 * sizeof(float))), true, false);
				// Color
				PW_GL_VOID_CALL(glEnableVertexAttribArray(2), true, false);
				PW_GL_VOID_CALL(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, v_buffer_object_size, (void*)(5 * sizeof(float))), true, false);
				// Is_Colored
				PW_GL_VOID_CALL(glEnableVertexAttribArray(3), true, false);
				PW_GL_VOID_CALL(glVertexAttribIPointer(3, 1, GL_INT, v_buffer_object_size, (void*)(9 * sizeof(float))), true, false);
				// Is_Text
				PW_GL_VOID_CALL(glEnableVertexAttribArray(4), true, false);
				PW_GL_VOID_CALL(glVertexAttribIPointer(4, 1, GL_INT, v_buffer_object_size, (void*)(sizeof(uint32_t) + (9 * sizeof(float)))), true, false);
				// Model_Index
				PW_GL_VOID_CALL(glEnableVertexAttribArray(5), true, false);
				PW_GL_VOID_CALL(glVertexAttribIPointer(5, 1, GL_INT, v_buffer_object_size, (void*)(sizeof(uint32_t) + sizeof(uint32_t) + (9 * sizeof(float)))), true, false);
				// Texture_Handle
				PW_GL_VOID_CALL(glEnableVertexAttribArray(6), true, false);
				PW_GL_VOID_CALL(glVertexAttribLPointer(6, 1, GL_UNSIGNED_INT64_ARB, v_buffer_object_size, (void*)(sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t) + (9 * sizeof(float)))), true, false);

				constexpr uint32_t v_draw_command_buffer_size = sizeof(Draw_Command);

				// Indirect index drawing
				PW_GL_VOID_CALL(glGenBuffers(1, &m_draw_command_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_draw_command_object), true, false);

				PW_GL_VOID_CALL(
					glBufferData(GL_DRAW_INDIRECT_BUFFER, v_draw_command_buffer_size, nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0), true, false);

				// Transparent Indirect index drawing
				PW_GL_VOID_CALL(glGenBuffers(1, &m_transparent_draw_command_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_transparent_draw_command_object), true, false);

				PW_GL_VOID_CALL(
					glBufferData(GL_DRAW_INDIRECT_BUFFER, v_draw_command_buffer_size, nullptr, GL_DYNAMIC_DRAW),
					true, false
				);

				PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0), true, false);

				// Element index drawing
				PW_GL_VOID_CALL(glGenBuffers(1, &m_element_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_object), true, false);
				PW_GL_VOID_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, TO_INT64(m_indice_count *
					sizeof(p_indices[0])), &p_indices[0], GL_STATIC_DRAW), true, false);

				PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), true, false);

				PW_GL_VOID_CALL(glBindVertexArray(0), true, false);

				if (pw::co::Memory::Deallocate<Vertex_Data>(v_vertex_data_arr) == false) {
					if (v_vertex_data_arr != nullptr) {
						delete[] v_vertex_data_arr;
						v_vertex_data_arr = nullptr;
					}
				}
			}
			Mesh::~Mesh() {
				PW_GL_VOID_CALL(glDeleteVertexArrays(1, &m_array_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_buffer_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_element_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_draw_command_object), true, false);
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_transparent_draw_command_object), true, false);
			}
			uint32_t Mesh::Add(const Non_Colored& p_data) {
				Vertex_Data* v_vertex_data_arr{ nullptr };
				PW_CALL(v_vertex_data_arr = pw::co::Memory::Allocate<Vertex_Data>(m_vertex_count), false);

				if (v_vertex_data_arr == nullptr) {
					return 0;
				}

				uint32_t v_model_index = Add_Matrix_To_SSBO(&p_data.m_matrix);

				for (size_t i = 0; i < m_vertex_count; i++) {
					v_vertex_data_arr[i].Set_Vertex_Position(glm::vec3(
						m_vertices[i].Vertex_Position().x - 0.5f,
						m_vertices[i].Vertex_Position().y + 0.5f,
						m_vertices[i].Vertex_Position().z
					));
					v_vertex_data_arr[i].Set_Texture_Coord(glm::vec2(
						m_vertices[i].Texture_Coord().x * (p_data.m_size.x / p_data.m_texture_size.x),
						m_vertices[i].Texture_Coord().y * (p_data.m_size.y / p_data.m_texture_size.y)
					));
					v_vertex_data_arr[i].Set_Color(glm::vec4(0.0f));
					v_vertex_data_arr[i].Set_Is_Colored(p_data.m_is_colored);
					v_vertex_data_arr[i].Set_Is_Text(p_data.m_is_text);
					v_vertex_data_arr[i].Set_Model_Index(v_model_index);
					v_vertex_data_arr[i].Set_Texture_Handle(p_data.m_texture_handle);
				}

				PW_GL_CUSTOM_CALL(glBindVertexArray(m_array_object), true, false, uint32_t);

				Add_To_Buffer(v_vertex_data_arr);

				PW_GL_CUSTOM_CALL(glBindVertexArray(0), true, false, uint32_t);

				if (pw::co::Memory::Deallocate<Vertex_Data>(v_vertex_data_arr) == false) {
					if (v_vertex_data_arr != nullptr) {
						delete[] v_vertex_data_arr;
						v_vertex_data_arr = nullptr;
					}
				}
				if (m_bo_size >= 1) {
					if (m_render_index_free_spaces.size() > 0) {
						uint32_t v_temp_return = m_render_index_free_spaces[0];

						m_render_index_free_spaces.erase(m_render_index_free_spaces.begin());

						m_matrix_index_converter.insert(std::make_pair(v_temp_return, v_model_index));

						auto v_found = m_transparent_textures.find(p_data.m_texture_handle);

						if (v_found != m_transparent_textures.end()) {
							m_transparent_indices.insert(v_temp_return);
						}
						return v_temp_return;
					}
					m_matrix_index_converter.insert(std::make_pair(m_bo_size - 1, v_model_index));

					auto v_found = m_transparent_textures.find(p_data.m_texture_handle);

					if (v_found != m_transparent_textures.end()) {
						m_transparent_indices.insert(m_bo_size - 1);
					}

					return m_bo_size - 1;
				}
				else {
					// Something went wrong if the size is not greater than 0
					return 0;
				}
			}
			uint32_t Mesh::Add(const Colored& p_data) {
				Vertex_Data* v_vertex_data_arr{ nullptr };
				PW_CALL(v_vertex_data_arr = pw::co::Memory::Allocate<Vertex_Data>(m_vertex_count), false);

				if (v_vertex_data_arr == nullptr) {
					return 0;
				}

				uint32_t v_model_index = Add_Matrix_To_SSBO(&p_data.m_matrix);

				for (size_t i = 0; i < m_vertex_count; i++) {
					v_vertex_data_arr[i].Set_Vertex_Position(glm::vec3(
						m_vertices[i].Vertex_Position().x - 0.5f,
						m_vertices[i].Vertex_Position().y + 0.5f,
						m_vertices[i].Vertex_Position().z
					));
					v_vertex_data_arr[i].Set_Texture_Coord(glm::vec2(
						m_vertices[i].Texture_Coord().x * (p_data.m_size.x / p_data.m_texture_size.x),
						m_vertices[i].Texture_Coord().y * (p_data.m_size.y / p_data.m_texture_size.y)
					));
					v_vertex_data_arr[i].Set_Color(p_data.m_color);
					v_vertex_data_arr[i].Set_Is_Colored(p_data.m_is_colored);
					v_vertex_data_arr[i].Set_Is_Text(p_data.m_is_text);
					v_vertex_data_arr[i].Set_Model_Index(v_model_index);
					v_vertex_data_arr[i].Set_Texture_Handle(p_data.m_texture_handle);
				}

				PW_GL_CUSTOM_CALL(glBindVertexArray(m_array_object), true, false, uint32_t);

				Add_To_Buffer(v_vertex_data_arr);

				PW_GL_CUSTOM_CALL(glBindVertexArray(0), true, false, uint32_t);

				if (pw::co::Memory::Deallocate<Vertex_Data>(v_vertex_data_arr) == false) {
					if (v_vertex_data_arr != nullptr) {
						delete[] v_vertex_data_arr;
						v_vertex_data_arr = nullptr;
					}
				}
				if (m_bo_size >= 1) {
					if (m_render_index_free_spaces.size() > 0) {
						uint32_t v_temp_return = m_render_index_free_spaces[0];

						m_render_index_free_spaces.erase(m_render_index_free_spaces.begin());

						m_matrix_index_converter.insert(std::make_pair(v_temp_return, v_model_index));

						auto v_found = m_transparent_textures.find(p_data.m_texture_handle);

						if (v_found != m_transparent_textures.end()) {
							m_transparent_indices.insert(v_temp_return);
						}
						return v_temp_return;
					}
					m_matrix_index_converter.insert(std::make_pair(m_bo_size - 1, v_model_index));

					auto v_found = m_transparent_textures.find(p_data.m_texture_handle);

					if (v_found != m_transparent_textures.end()) {
						m_transparent_indices.insert(m_bo_size - 1);
					}

					return m_bo_size - 1;
				}
				else {
					// Something went wrong if the size is not greater than 0
					return 0;
				}
			}
			void Mesh::Remove(uint32_t p_index) {
				constexpr uint32_t v_vertex_size = sizeof(Vertex_Data);
				// Removing the data from the OpenGL buffer would be
				// too resource intensive to overwrite the old info
				// so just label the space as open for new data.
				m_render_index_free_spaces.push_back(p_index);

				std::sort(m_render_index_free_spaces.begin(), m_render_index_free_spaces.end());

				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

				Vertex_Data v_temp{};

				PW_GL_VOID_CALL(glGetBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(MUL_UINT64(p_index, v_vertex_size), m_vertex_count), v_vertex_size, &v_temp), true, false);

				PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

				m_matrix_index_converter.erase(p_index);

				auto v_found = m_transparent_indices.find(p_index);

				if (v_found != m_transparent_indices.end()) {
					m_transparent_indices.erase(v_found);
				}

				m_mo_free_spaces.push_back(v_temp.Model_Index());
			}
			void Mesh::Render(uint32_t p_index) {
				constexpr uint32_t v_vertex_size = sizeof(Vertex_Data);
				constexpr uint32_t v_unit_size = sizeof(Draw_Command);
				// The add function guarantee's that 
				// p_index if correct is m_to_size - 1
				// so test for any range 0 < p_index < m_to_size
				if (p_index < m_bo_size) {
					Draw_Command v_temp{};

					v_temp.m_count = m_indice_count;
					v_temp.m_instance_count = 1;
					v_temp.m_first_index = p_index * m_indice_count;
					v_temp.m_base_vertex = 0;
					v_temp.m_base_instance = 0;

					auto v_found = m_transparent_indices.find(p_index);

					if (v_found == m_transparent_indices.end()) {
						if (m_draw_indices.size() > m_dc_size) {
							if (p_index * m_indice_count != m_draw_indices[m_dc_size].m_first_index) {
								m_dcv_changed = true;
								m_draw_indices[m_dc_size] = v_temp;
							}
						}
						else {
							m_dcv_changed = true;
							m_draw_indices.push_back(v_temp);
						}
						m_dc_size = m_dc_size + 1;
					}
					else {
						if (m_transparent_draw_indices.size() > m_tdc_size) {
							if (p_index * m_indice_count != m_transparent_draw_indices[m_tdc_size].m_first_index) {
								m_tdcv_changed = true;
								m_transparent_draw_indices[m_tdc_size] = v_temp;
							}
						}
						else {
							m_tdcv_changed = true;
							m_transparent_draw_indices.push_back(v_temp);
						}
						m_tdc_size = m_tdc_size + 1;
					}
				}
			}
			void Mesh::Draw() {
				constexpr uint32_t v_unit_size = sizeof(Draw_Command);

				if (m_mo_size_tframe > 0) {
					PW_GL_VOID_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_model_object), true, false);

					PW_GL_VOID_CALL(glm::mat4 * v_temp_mo_access = static_cast<glm::mat4*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY)), true, false);

					for (uint32_t i = 0; i < m_mo_size_tframe; i++) {
						v_temp_mo_access[m_matrix_array_access[i].first] = m_matrix_array_access[i].second;
					}

					PW_GL_VOID_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0), true, false);

					m_mo_marr_max_size = TO_UINT32(m_matrix_array_access.size());
					m_mo_size_tframe = 0;
				}
				if (m_dc_size > 0) {
					PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_object), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_draw_command_object), true, false);

					if (m_dcv_changed == true || m_last_dc_size != m_dc_size) {
						PW_GL_VOID_CALL(
							glBufferData(GL_DRAW_INDIRECT_BUFFER, MUL_UINT64(v_unit_size, m_dc_size), m_draw_indices.data(), GL_DYNAMIC_DRAW),
							true, false
						);
						m_dcv_changed = false;
					}
					m_last_dc_size = m_dc_size;

					PW_GL_VOID_CALL(glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, m_dc_size, 0), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0), true, false);
					PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), true, false);

					PW_GL_VOID_CALL(glBindVertexArray(0), true, false);

					m_dc_size = 0;
				}
			}
			void Mesh::Draw_Transparent() {
				constexpr uint32_t v_unit_size = sizeof(Draw_Command);

				if (m_tdc_size > 0) {
					PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_object), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_transparent_draw_command_object), true, false);

					if (m_tdcv_changed == true || m_last_tdc_size != m_tdc_size) {
						PW_GL_VOID_CALL(
							glBufferData(GL_DRAW_INDIRECT_BUFFER, MUL_UINT64(v_unit_size, m_tdc_size), m_transparent_draw_indices.data(), GL_DYNAMIC_DRAW),
							true, false
						);
						m_tdcv_changed = false;
					}
					m_last_tdc_size = m_tdc_size;

					PW_GL_VOID_CALL(glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, m_tdc_size, 0), true, false);

					PW_GL_VOID_CALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0), true, false);
					PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), true, false);

					PW_GL_VOID_CALL(glBindVertexArray(0), true, false);

					m_tdc_size = 0;
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
				if (p_index < m_bo_size) {
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

					PW_GL_VOID_CALL(
						Vertex_Data* v_temp_read_buffer = static_cast<Vertex_Data*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)),
						true, false
					);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_temp_read_buffer[MUL_UINT64(p_index, m_vertex_count) + i].Set_Color(p_new_color_data);
					}


					PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
			}
			void Mesh::Change_Texture_Data(uint32_t p_index, Vertex_Data* p_new_texture_data) {
				constexpr uint32_t v_unit_size = sizeof(glm::vec2);
				if (p_index < m_bo_size) {
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

					PW_GL_VOID_CALL(
						Vertex_Data* v_temp_read_buffer = static_cast<Vertex_Data*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)),
						true, false
					);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_temp_read_buffer[MUL_UINT64(p_index, m_vertex_count) + i].Set_Texture_Coord(p_new_texture_data[i].Texture_Coord());
					}


					PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
			}
			void Mesh::Change_Matrix_Data(uint32_t p_index, const glm::mat4& p_matrix) {
				constexpr uint32_t v_vertex_size = sizeof(Vertex_Data);
				constexpr uint32_t v_unit_size = sizeof(glm::mat4);
				if (p_index < m_bo_size) {
					if (m_matrix_array_access.size() > m_mo_size_tframe) {
						auto v_found = m_matrix_index_converter.find(p_index);

						if (v_found != m_matrix_index_converter.end()) {
							m_matrix_array_access[m_mo_size_tframe] = std::make_pair(v_found->second, p_matrix);
							m_mo_size_tframe = m_mo_size_tframe + 1;
						}
					}
					else {
						auto v_found = m_matrix_index_converter.find(p_index);

						if (v_found != m_matrix_index_converter.end()) {
							m_matrix_array_access.push_back(std::make_pair(v_found->second, p_matrix));
							m_mo_size_tframe = m_mo_size_tframe + 1;
						}

					}
				}
			}
			void Mesh::Change_Texture_Handle(uint32_t p_index, const uint64_t& p_texture_handle) {
				constexpr uint32_t v_unit_size = sizeof(uint64_t);
				if (p_index < m_bo_size) {
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

					PW_GL_VOID_CALL(
						Vertex_Data* v_temp_read_buffer = static_cast<Vertex_Data*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)),
						true, false
					);

					for (size_t i = 0; i < m_vertex_count; i++) {
						v_temp_read_buffer[MUL_UINT64(p_index, m_vertex_count) + i].Set_Texture_Handle(p_texture_handle);
					}


					PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
			}
			void Mesh::Label_Transparent_Texture_Handle(const uint64_t& p_texture_handle) {
				auto v_found = m_transparent_textures.find(p_texture_handle);

				if (v_found == m_transparent_textures.end()) {
					m_transparent_textures.insert(p_texture_handle);
				}
			}
			void Mesh::Validate_Multitex(uint32_t p_associated_index, const std::vector<uint64_t>& p_texture_handles) {
				for (auto i = p_texture_handles.begin(); i != p_texture_handles.end(); i++) {
					auto v_found = m_transparent_textures.find((*i));

					if (v_found != m_transparent_textures.end()) {
						m_transparent_indices.insert(p_associated_index);
					}
				}
			}
			void Mesh::Initialize() {
				// SSBO matrices
				PW_GL_VOID_CALL(glGenBuffers(1, &m_model_object), true, false);
				PW_GL_VOID_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_model_object), true, false);

				PW_GL_VOID_CALL(
					glBufferData(GL_SHADER_STORAGE_BUFFER, TO_INT64(sizeof(glm::mat4)) * m_mo_max_size, nullptr, GL_DYNAMIC_DRAW),
					true, false
				);
				PW_GL_VOID_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_model_object), true, false);

				PW_GL_VOID_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0), true, false);
			}
			void Mesh::Release() {
				PW_GL_VOID_CALL(glDeleteBuffers(1, &m_model_object), true, false);

				m_matrix_array_access.clear();
				m_mo_free_spaces.clear();
			}
			void Mesh::Add_To_Buffer(Vertex_Data* p_data) {
				constexpr uint32_t v_buffer_object_size = sizeof(Vertex_Data);

				if (m_render_index_free_spaces.size() > 0) {
					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(m_render_index_free_spaces[0], MUL_UINT64(v_buffer_object_size, m_vertex_count)), MUL_UINT64(m_vertex_count, v_buffer_object_size), &p_data[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

					return;
				}

				if (m_bo_size < m_bo_max_size) {
					m_bo_size = m_bo_size + 1;

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object), true, false);

					PW_GL_VOID_CALL(
						glBufferSubData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64((m_bo_size - 1), v_buffer_object_size)), MUL_UINT64(m_vertex_count, v_buffer_object_size), &p_data[0]),
						true, false
					);

					PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);
				}
				else {
					PW_GL_VOID_CALL(glBindVertexArray(m_array_object), true, false);
					// m_size >= m_max_size
					// Allocate new buffer
					uint32_t v_new_buffer_size = m_bo_max_size + TO_UINT32(m_bo_max_size * glm::golden_ratio<double>());
					// Vertex Data
					{
						PW_GL_VOID_CALL(
							glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object),
							true, false
						);

						PW_CALL(Vertex_Data* v_read_buffer = pw::co::Memory::Allocate<Vertex_Data>(MUL_UINT64(m_vertex_count, v_new_buffer_size)), true);

						PW_GL_VOID_CALL(
							Vertex_Data* v_temp_read_buffer = static_cast<Vertex_Data*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY)),
							true, false
						);

						for (uint32_t i = 0; i < MUL_UINT32(m_vertex_count, m_bo_max_size); i++) {
							v_read_buffer[i] = v_temp_read_buffer[i];
						}
						for (uint32_t i = 0; i < m_vertex_count; i++) {
							v_read_buffer[(m_vertex_count * m_bo_max_size) + i] = p_data[i];
						}
						for (uint32_t i = MUL_UINT32(m_vertex_count, (m_bo_max_size + 1)); i < MUL_UINT32(m_vertex_count, v_new_buffer_size); i++) {
							v_read_buffer[i] = Vertex_Data();
						}

						m_bo_size = m_bo_size + 1;

						PW_GL_VOID_CALL(glUnmapBuffer(GL_ARRAY_BUFFER),
							true, false
						);
						PW_GL_VOID_CALL(
							glBufferData(GL_ARRAY_BUFFER, MUL_UINT64(m_vertex_count, MUL_UINT64(v_buffer_object_size, v_new_buffer_size)), &v_read_buffer[0], GL_DYNAMIC_DRAW),
							true, false
						);

						PW_GL_VOID_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0), true, false);

						if (pw::co::Memory::Deallocate<Vertex_Data>(v_read_buffer) == false) {
							if (v_read_buffer != nullptr) {
								delete[] v_read_buffer;
								v_read_buffer = nullptr;
							}
						}
					}
					// Index Data
					{
						PW_GL_VOID_CALL(
							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_object),
							true, false
						);

						PW_CALL(uint32_t* v_read_buffer = pw::co::Memory::Allocate<uint32_t>(MUL_UINT64(m_indice_count, v_new_buffer_size)), true);

						PW_GL_VOID_CALL(
							uint32_t* v_temp_read_buffer = static_cast<uint32_t*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY)),
							true, false
						);

						for (uint32_t i = 0; i < MUL_UINT32(m_indice_count, m_bo_max_size); i++) {
							v_read_buffer[i] = v_temp_read_buffer[i];
						}
						for (uint32_t i = MUL_UINT32(m_indice_count, m_bo_max_size); i < MUL_UINT32(m_indice_count, v_new_buffer_size); i++) {
							v_read_buffer[i] = v_read_buffer[(i - 6)] + 4;
						}

						PW_GL_VOID_CALL(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER),
							true, false
						);
						PW_GL_VOID_CALL(
							glBufferData(GL_ELEMENT_ARRAY_BUFFER, MUL_UINT64(m_indice_count, MUL_UINT64(sizeof(uint32_t), v_new_buffer_size)), &v_read_buffer[0], GL_DYNAMIC_DRAW),
							true, false
						);

						PW_GL_VOID_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), true, false);

						if (pw::co::Memory::Deallocate<uint32_t>(v_read_buffer) == false) {
							if (v_read_buffer != nullptr) {
								delete[] v_read_buffer;
								v_read_buffer = nullptr;
							}
						}
					}
					m_bo_max_size = v_new_buffer_size;

					PW_GL_VOID_CALL(glBindVertexArray(0), true, false);
				}
			}
			uint32_t Mesh::Add_Matrix_To_SSBO(const glm::mat4* p_data) {
				constexpr uint32_t v_unit_size = sizeof(glm::mat4);

				if (m_mo_free_spaces.size() > 0) {
					PW_GL_CUSTOM_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_model_object), true, false, uint32_t);

					PW_GL_CUSTOM_CALL(
						glBufferSubData(GL_SHADER_STORAGE_BUFFER, MUL_UINT64(m_mo_free_spaces[0], v_unit_size), v_unit_size, &p_data[0]),
						true, false, uint32_t
					);

					uint32_t v_temp = m_mo_free_spaces[0];

					m_mo_free_spaces.erase(m_mo_free_spaces.begin());

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0), true, false, uint32_t);

					return v_temp;
				}

				if (m_mo_size < m_mo_max_size) {
					m_mo_size = m_mo_size + 1;

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_model_object), true, false, uint32_t);

					PW_GL_CUSTOM_CALL(
						glBufferSubData(GL_SHADER_STORAGE_BUFFER, MUL_UINT64(m_mo_size - 1, v_unit_size), v_unit_size, &p_data[0]),
						true, false, uint32_t
					);

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0), true, false, uint32_t);

					return m_mo_size - 1;
				}
				else {
					// m_size >= m_max_size
					// Allocate new buffer
					uint32_t v_new_buffer_size = m_mo_max_size + TO_UINT32(m_mo_max_size * glm::golden_ratio<double>());

					PW_GL_CUSTOM_CALL(
						glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_model_object),
						true, false, uint32_t
					);

					PW_CUSTOM_CALL(glm::mat4* v_read_buffer = pw::co::Memory::Allocate<glm::mat4>(v_new_buffer_size), true, uint32_t);

					PW_GL_CUSTOM_CALL(
						glm::mat4* v_temp_read_buffer = static_cast<glm::mat4*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY)),
						true, false, uint32_t
					);

					for (uint32_t i = 0; i < m_mo_max_size; i++) {
						v_read_buffer[i] = v_temp_read_buffer[i];
					}
					v_read_buffer[m_mo_max_size] = *p_data;
					for (uint32_t i = (m_mo_max_size + 1); i < v_new_buffer_size; i++) {
						v_read_buffer[i] = glm::mat4();
					}

					m_mo_size = m_mo_size + 1;

					PW_GL_CUSTOM_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER),
						true, false, uint32_t
					);
					PW_GL_CUSTOM_CALL(
						glBufferData(GL_SHADER_STORAGE_BUFFER, MUL_UINT64(v_unit_size, v_new_buffer_size), &v_read_buffer[0], GL_DYNAMIC_DRAW),
						true, false, uint32_t
					);

					PW_GL_CUSTOM_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0), true, false, uint32_t);

					if (pw::co::Memory::Deallocate<glm::mat4>(v_read_buffer) == false) {
						if (v_read_buffer != nullptr) {
							delete[] v_read_buffer;
							v_read_buffer = nullptr;
						}
					}

					m_mo_max_size = v_new_buffer_size;

					return m_mo_size - 1;
				}
			}
	ST_NAMESPACE_END
PW_NAMESPACE_END