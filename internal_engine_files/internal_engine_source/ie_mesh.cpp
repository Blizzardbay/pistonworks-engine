#include "internal_engine_headers\ie_mesh.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// ID_Vertex_Data
		// Static Declarations   
		// Class Members
			ID_Vertex_Data::ID_Vertex_Data() :
					vertex_position(glm::vec3(0.0f, 0.0f, 0.0f)), texture_coord(glm::vec2(0.0f, 0.0f)),
					color_data(glm::vec3(0.0f, 0.0f, 0.0f)) {
			}
			ID_Vertex_Data::ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord) :
					vertex_position(vertex_position), texture_coord(texture_coord),
					color_data(glm::vec3(0.0f, 0.0f, 0.0f)) {
			}
			ID_Vertex_Data::~ID_Vertex_Data() {
			}
			PW_VOID ID_Vertex_Data::Set_Vertex_Position(glm::vec3 vertex_position) {
				this->vertex_position = vertex_position;
			}
			PW_VOID ID_Vertex_Data::Set_Texture_Coord(glm::vec2 texture_coord) {
				this->texture_coord = texture_coord;
			}
			PW_VOID ID_Vertex_Data::Set_Color_Data(glm::vec3 color_data) {
				this->color_data = color_data;
			}
			glm::vec3 ID_Vertex_Data::Vertex_Position() {
				return this->vertex_position;
			}
			glm::vec2 ID_Vertex_Data::Texture_Coord() {
				return this->texture_coord;
			}
			glm::vec3 ID_Vertex_Data::Color_Data() {
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
			Mesh::Mesh(ID_Vertex_Data* vertices, const PW_SUINT vertex_count, PW_UINT* indices, const PW_SUINT indice_count) :
					vertices(nullptr), draw_count(indice_count), vertex_count(vertex_count), vertex_array_object(0),
					vertex_buffer_object(0), vertex_texture_object(0), vertex_color_object(0), vertex_element_object(0) {

				this->vertices = std::make_shared<ID_Vertex_Data PW_SMART_ARRAY>(new ID_Vertex_Data[vertex_count]);

				for (size_t i = 0; i < vertex_count; i++) {
					(*this->vertices)[i] = vertices[i];
				}

				glGenVertexArrays(1, &vertex_array_object);
				glBindVertexArray(vertex_array_object);

				PW_SRD_PTR(glm::vec3 PW_SMART_ARRAY) vertex_position_arr =
					std::make_shared<glm::vec3 PW_SMART_ARRAY>(new glm::vec3[vertex_count]);
				PW_SRD_PTR(glm::vec2 PW_SMART_ARRAY) texture_data_arr =
					std::make_shared<glm::vec2 PW_SMART_ARRAY>(new glm::vec2[vertex_count]);
				PW_SRD_PTR(glm::vec3 PW_SMART_ARRAY) color_data =
					std::make_shared<glm::vec3 PW_SMART_ARRAY>(new glm::vec3[vertex_count]);

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
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				// Use vertex_element_buffer to handle index drawing
				glGenBuffers(1, &vertex_element_object);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_element_object);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_count * 
					sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glBindVertexArray(0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				vertex_position_arr.~shared_ptr();
				texture_data_arr.~shared_ptr();
				color_data.~shared_ptr();
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
			PW_BOOL Mesh::operator==(const Mesh& rhs) {
				if (this->draw_count == rhs.draw_count && this->vertices == rhs.vertices) {
					return true;
				}
				else {
					return false;
				}
			}
			PW_VOID Mesh::Draw() {
				glBindVertexArray(vertex_array_object);

				glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
			}
			PW_VOID Mesh::Delete() {
				glDeleteVertexArrays(1, &vertex_array_object);

				vertices.~shared_ptr();
			}
			ID_Vertex_Data* Mesh::Vertices() {
				return *vertices;
			}
			PW_UINT Mesh::Vertex_Count() {
				return vertex_count;
			}
			PW_VOID Mesh::Update_Vertices(ID_Vertex_Data* new_vertices) {
				for (PW_SIZE i = 0; i < vertex_count; i++) {
					(*vertices)[i] = new_vertices[i];
				}
			}
			PW_VOID Mesh::Change_Color_Data(
				glm::vec3 new_color_data) {

				std::shared_ptr<glm::vec3 PW_SMART_ARRAY> color_data = 
					std::make_shared<glm::vec3 PW_SMART_ARRAY>(new glm::vec3[vertex_count]);
				for (size_t i = 0; i < vertex_count; i++) {
					(*color_data)[i] = new_color_data;
				}
				glBindBuffer(GL_ARRAY_BUFFER, vertex_color_object);
				glBufferData(GL_ARRAY_BUFFER, vertex_count * 
					sizeof((*color_data)[0]), &(*color_data)[0], GL_STATIC_DRAW);

				color_data.~shared_ptr();

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			PW_VOID Mesh::Change_Texture_Data(
				ID_Vertex_Data* new_texture_data) {

				std::shared_ptr<glm::vec2 PW_SMART_ARRAY> texture_data_arr =
					std::make_shared<glm::vec2 PW_SMART_ARRAY>(new glm::vec2[vertex_count]);

				for (size_t i = 0; i < vertex_count; i++) {
					(*texture_data_arr)[i] = new_texture_data[i].Texture_Coord();
				}

				glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_object);
				glBufferData(GL_ARRAY_BUFFER, vertex_count * 
					sizeof((*texture_data_arr)[0]), &(*texture_data_arr)[0], GL_STATIC_DRAW);

				texture_data_arr.~shared_ptr();

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////