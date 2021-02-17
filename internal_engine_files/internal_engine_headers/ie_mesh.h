#ifndef H_IE_MESH
#define H_IE_MESH

//(DUAL_FILE)

/* C++ Headers              */
#include <vector>
/* Project Headers          */
#include <GL\glew.h>
#include <glm/glm.hpp>
/* Engine Headers           */
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
	/* Classes                  */
	//
		/* -ID_Vertex_Data
		 Holds the data for each vertex in the model.
		*/
		struct ID_Vertex_Data {
	/* Default Class Structures */
		public:
			ID_Vertex_Data() :
				vertex_position(glm::vec3(0.0f, 0.0f, 0.0f)), texture_coord(glm::vec2(0.0f, 0.0f)),
				color_data(glm::vec3(0.0f, 0.0f, 0.0f)) {
			}
			ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord) :
				vertex_position(vertex_position), texture_coord(texture_coord),
				color_data(glm::vec3(0.0f, 0.0f, 0.0f)) {
			}
			~ID_Vertex_Data() {};
		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Set_Vertex_Position(glm::vec3 vertex_position) { this->vertex_position = vertex_position; }
			PW_VOID Set_Texture_Coord(glm::vec2 texture_coord) { this->texture_coord = texture_coord; }
			PW_VOID Set_Color_Data(glm::vec3 color_data) { this->color_data = color_data; }

			glm::vec3 Vertex_Position() { return this->vertex_position; }
			glm::vec2 Texture_Coord() { return this->texture_coord; }
			glm::vec3 Color_Data() { return this->color_data; }
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			glm::vec3 vertex_position;
			glm::vec2 texture_coord;
			glm::vec3 color_data;
		};
		/* -Mesh
		 Creates and send the vertex data to the
		 shader.
		*/
		class Mesh {
	/* Default Class Structures */
		public:
			Mesh();
			Mesh(ID_Vertex_Data* vertices, const PW_SUINT vertex_count, PW_UINT* indices, const PW_SUINT indice_count);
			~Mesh() {};

			Mesh operator=(const Mesh& rhs);
			PW_BOOL operator==(const Mesh& rhs);
		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Draw();
			PW_VOID Delete();

			ID_Vertex_Data* Vertices() { return vertices; }
			ID_Vertex_Data*& Vertices_Ref() { return vertices; }
			PW_UINT Vertex_Count() { return vertex_count; }

			PW_VOID Update_Vertices(ID_Vertex_Data* new_vertices) { delete vertices; vertices = new_vertices; }

			PW_VOID Change_Color_Data(glm::vec3 new_color_data);

			PW_VOID Change_Texture_Data(ID_Vertex_Data* new_texture_data);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			ID_Vertex_Data* vertices;

			PW_UINT draw_count;
			PW_UINT vertex_count;

			PW_UINT vertex_array_object;
			PW_UINT vertex_buffer_object;
			PW_UINT vertex_texture_object;
			PW_UINT vertex_color_object;
			PW_UINT vertex_element_object;
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_MESH