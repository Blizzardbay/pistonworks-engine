#include "engine_structures\engine_mesh.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// ID_Vertex_Data
		// Static Declarations   
		// Class Members
			ID_Vertex_Data::ID_Vertex_Data() :
					vertex_position(glm::vec3(0.0f, 0.0f, 0.0f)), texture_coord(glm::vec2(0.0f, 0.0f)),
					color_data(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) {
			}
			ID_Vertex_Data::ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord) :
					vertex_position(vertex_position), texture_coord(texture_coord),
					color_data(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) {
			}
			ID_Vertex_Data::~ID_Vertex_Data() {
			}
			void ID_Vertex_Data::Set_Vertex_Position(glm::vec3 vertex_position) {
				this->vertex_position = vertex_position;
			}
			void ID_Vertex_Data::Set_Texture_Coord(glm::vec2 texture_coord) {
				this->texture_coord = texture_coord;
			}
			void ID_Vertex_Data::Set_Color_Data(glm::vec4 color_data) {
				this->color_data = color_data;
			}
			const glm::vec3& ID_Vertex_Data::Vertex_Position() {
				return this->vertex_position;
			}
			const glm::vec2& ID_Vertex_Data::Texture_Coord() {
				return this->texture_coord;
			}
			const glm::vec4& ID_Vertex_Data::Color_Data() {
				return this->color_data;
			}
		// End of Class Members
		// Mesh              
		// Static Declarations   
		// Class Members           
			Mesh::Mesh() :
					vertices(nullptr), draw_count(0), vertex_count(0), vertex_array_object(0),
					vertex_buffer_object(0), vertex_texture_object(0), vertex_color_object(0), vertex_element_object(0) {
			}
			Mesh::Mesh(ID_Vertex_Data* vertices, const uint16_t vertex_count, uint32_t* indices, const uint16_t indice_count) :
					vertices(nullptr), draw_count(indice_count), vertex_count(vertex_count), vertex_array_object(0),
					vertex_buffer_object(0), vertex_texture_object(0), vertex_color_object(0), vertex_element_object(0) {
				try {
					this->vertices = std::make_shared<ID_Vertex_Data*>(pw::Engine_Memory::Allocate<ID_Vertex_Data>(vertex_count));

					for (size_t i = 0; i < vertex_count; i++) {
						(*this->vertices)[i] = vertices[i];
					}
					PW_GL_VOID_CALL(glGenVertexArrays(1, &vertex_array_object), false);
					PW_GL_VOID_CALL(glBindVertexArray(vertex_array_object), false);

					PW_SRD_PTR(glm::vec3*) vertex_position_arr =
						std::make_shared<glm::vec3*>(pw::Engine_Memory::Allocate<glm::vec3>(vertex_count));
					PW_SRD_PTR(glm::vec2*) texture_data_arr =
						std::make_shared<glm::vec2*>(pw::Engine_Memory::Allocate<glm::vec2>(vertex_count));
					PW_SRD_PTR(glm::vec4*) color_data =
						std::make_shared<glm::vec4*>(pw::Engine_Memory::Allocate<glm::vec4>(vertex_count));

					for (size_t i = 0; i < vertex_count; i++) {
						(*vertex_position_arr)[i] = vertices[i].Vertex_Position();
						(*texture_data_arr)[i] = vertices[i].Texture_Coord();
						(*color_data)[i] = vertices[i].Color_Data();
					}

					// Use the vertex_buffer_object for positions inside the vertex shader
					glGenBuffers(1, &vertex_buffer_object);
					glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
					glBufferData(GL_ARRAY_BUFFER, vertex_count *
						sizeof((*vertex_position_arr)[0]), &(*vertex_position_arr)[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

					// Use vertex_texture_object to handle texture coordinates
					glGenBuffers(1, &vertex_texture_object);
					glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_object);
					glBufferData(GL_ARRAY_BUFFER, vertex_count *
						sizeof((*texture_data_arr)[0]), &(*texture_data_arr)[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

					// Use vertex_color_data to handle color data
					glGenBuffers(1, &vertex_color_object);
					glBindBuffer(GL_ARRAY_BUFFER, vertex_color_object);
					glBufferData(GL_ARRAY_BUFFER, vertex_count *
						sizeof((*color_data)[0]), &(*color_data)[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
					// Use vertex_element_buffer to handle index drawing
					glGenBuffers(1, &vertex_element_object);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_element_object);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_count *
						sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

					glBindBuffer(GL_ARRAY_BUFFER, 0);

					glBindVertexArray(0);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

					pw::Engine_Memory::Deallocate<glm::vec3>(*vertex_position_arr.get());
					pw::Engine_Memory::Deallocate<glm::vec2>(*texture_data_arr.get());
					pw::Engine_Memory::Deallocate<glm::vec4>(*color_data.get());

					vertex_position_arr.~shared_ptr();
					texture_data_arr.~shared_ptr();
					color_data.~shared_ptr();
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			Mesh::Mesh(const ID_Vertex_Data* vertices, const uint16_t vertex_count, const uint32_t* indices, const uint16_t indice_count) :
				Mesh((ID_Vertex_Data*)vertices, vertex_count, (uint32_t*)indices, indice_count) {
			}
			Mesh::~Mesh() {
			}
			Mesh Mesh::operator=(const Mesh& rhs) {

				this->draw_count = 0;
				this->vertex_array_object = 0;
				this->vertex_buffer_object = 0;
				this->vertex_texture_object = 0;
				this->vertex_color_object = 0;
				this->vertex_element_object = 0;

				this->draw_count = rhs.draw_count;
				this->vertex_array_object = rhs.vertex_array_object;
				this->vertex_buffer_object = rhs.vertex_buffer_object;
				this->vertex_texture_object = rhs.vertex_texture_object;
				this->vertex_color_object = rhs.vertex_color_object;
				this->vertex_element_object = rhs.vertex_element_object;

				return *this;
			}
			bool Mesh::operator==(const Mesh& rhs) {
				if (this->draw_count == rhs.draw_count && this->vertices == rhs.vertices) {
					return true;
				}
				else {
					return false;
				}
			}
			void Mesh::Draw() {
				try {
					glBindVertexArray(vertex_array_object);

					if (TRY_LINE draw_count == 0) {
						throw pw::er::Warning_Error(L"Mesh", L"draw_count == 0", std::move(EXCEPTION_LINE), __FILEW__, L"Draw");
					}
					glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);

					glBindVertexArray(0);
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void Mesh::Delete() {
				glDeleteVertexArrays(1, &vertex_array_object);

				pw::Engine_Memory::Deallocate<st::ID_Vertex_Data>(*vertices.get(), true);

				vertices.~shared_ptr();
			}
			ID_Vertex_Data* Mesh::Vertices() {
				return *vertices;
			}
			const uint32_t& Mesh::Vertex_Count() {
				return vertex_count;
			}
			void Mesh::Update_Vertices(ID_Vertex_Data* new_vertices) {
				for (size_t i = 0; i < vertex_count; i++) {
					(*vertices)[i] = new_vertices[i];
				}
			}
			void Mesh::Change_Color_Data(
				glm::vec4 new_color_data) {
				try {
					std::shared_ptr<glm::vec4*> color_data =
						std::make_shared<glm::vec4*>(pw::Engine_Memory::Allocate<glm::vec4>(vertex_count));
					for (size_t i = 0; i < vertex_count; i++) {
						(*color_data)[i] = new_color_data;
					}
					glBindBuffer(GL_ARRAY_BUFFER, vertex_color_object);
					glBufferData(GL_ARRAY_BUFFER, vertex_count *
						sizeof((*color_data)[0]), &(*color_data)[0], GL_STATIC_DRAW);
					pw::Engine_Memory::Deallocate<glm::vec4>(*color_data.get());
					color_data.~shared_ptr();

					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void Mesh::Change_Texture_Data(
				ID_Vertex_Data* new_texture_data) {
				try {
					std::shared_ptr<glm::vec2*> texture_data_arr =
						std::make_shared<glm::vec2*>(pw::Engine_Memory::Allocate<glm::vec2>(vertex_count));

					for (size_t i = 0; i < vertex_count; i++) {
						(*texture_data_arr)[i] = new_texture_data[i].Texture_Coord();
					}

					glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_object);
					glBufferData(GL_ARRAY_BUFFER, vertex_count * 
						sizeof((*texture_data_arr)[0]), &(*texture_data_arr)[0], GL_STATIC_DRAW);
					pw::Engine_Memory::Deallocate<glm::vec2>(*texture_data_arr.get());
					texture_data_arr.~shared_ptr();

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