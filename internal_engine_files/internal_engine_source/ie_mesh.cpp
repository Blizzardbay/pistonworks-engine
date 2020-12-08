#include "internal_engine_headers\ie_mesh.h"
namespace pw {
/* IE_Mesh                  */
/* Static Declarations      */
/* Class Members            */
	IE_Mesh::IE_Mesh() :
		vertices(0), draw_count(0),vertex_count(0), vertex_array_object(0),
		vertex_buffer_object(0), vertex_texture_object(0), vertex_color_object(0), vertex_element_object(0) {
	}
	IE_Mesh::IE_Mesh(ID_Vertex_Data* vertices, const PW_SUINT vertex_count, PW_UINT* indices, const PW_SUINT indice_count) :
			vertices(vertices), draw_count(indice_count), vertex_count(vertex_count), vertex_array_object(0),
			vertex_buffer_object(0), vertex_texture_object(0), vertex_color_object(0), vertex_element_object(0) {
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		glm::vec3* vertex_position_arr = new glm::vec3[vertex_count];
		glm::vec2* texture_data_arr = new glm::vec2[vertex_count];
		glm::vec3* color_data = new glm::vec3[vertex_count];

		for (size_t i = 0; i < vertex_count; i++) {
			vertex_position_arr[i] = vertices[i].Vertex_Position();
			texture_data_arr[i] = vertices[i].Texture_Coord();
			color_data[i] = vertices[i].Color_Data();
		}

		// Use the vertex_buffer_object for positions inside the vertex shader
		glGenBuffers(1, &vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(vertex_position_arr[0]), &vertex_position_arr[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		// Use vertex_texture_object to handle texture coordinates
		glGenBuffers(1, &vertex_texture_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_object);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(texture_data_arr[0]), &texture_data_arr[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		// Use vertex_color_data to handle color data
		glGenBuffers(1, &vertex_color_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_color_object);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(color_data[0]), &color_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// Use vertex_element_buffer to handle index drawing
		glGenBuffers(1, &vertex_element_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_element_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_count * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete []vertex_position_arr;
		vertex_position_arr = nullptr;
		delete []texture_data_arr;
		texture_data_arr = nullptr;
		delete []color_data;
		color_data = nullptr;

	}
	IE_Mesh::IE_Mesh(const IE_Mesh& other_ie_mesh) {

	}
	IE_Mesh IE_Mesh::operator=(const IE_Mesh& rhs) {
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
	bool IE_Mesh::operator==(const IE_Mesh& rhs) {
		if (this->draw_count == rhs.draw_count) {
			return true;
		}
		else {
			return false;
		}
	}
	void IE_Mesh::Draw() {
		glBindVertexArray(vertex_array_object);

		glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	void IE_Mesh::Delete() {
		glDeleteVertexArrays(1, &vertex_array_object);
	}
	void IE_Mesh::Change_Color_Data(glm::vec3 new_color_data) {
		glm::vec3* color_data = new glm::vec3[vertex_count];
		for (size_t i = 0; i < vertex_count; i++) {
			color_data[i] = new_color_data;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertex_color_object);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(color_data[0]), &color_data[0], GL_STATIC_DRAW);

		delete[] color_data;
		color_data = nullptr;
	}
	PW_VOID IE_Mesh::Change_Texture_Data(ID_Vertex_Data* new_texture_data) {
		glm::vec2* texture_data_arr = new glm::vec2[vertex_count];

		for (size_t i = 0; i < vertex_count; i++) {
			texture_data_arr[i] = new_texture_data[i].Texture_Coord();
		}

		glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_object);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(texture_data_arr[0]), &texture_data_arr[0], GL_STATIC_DRAW);

		delete[] texture_data_arr;
		texture_data_arr = nullptr;
	}
}