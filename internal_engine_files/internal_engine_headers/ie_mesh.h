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
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (ID_Vertex_Data)                            ]
	 Holds the data for each vertex in the model.
	*/
	struct ID_Vertex_Data {
/* Default Class Structures */
	public:
		ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord) :
				vertex_position( vertex_position ), texture_coord( texture_coord ),
				color_data( glm::vec3( 0.0f,0.0f,0.0f )) {
		}
		~ID_Vertex_Data() {};
	private:
/* Public Functions/Macros  */
	public:
		void Set_Vertex_Position(glm::vec3 vertex_position) { this->vertex_position = vertex_position; }
		void Set_Texture_Coord(glm::vec2 texture_coord) { this->texture_coord = texture_coord; }
		void Set_Color_Data(glm::vec3 color_data) { this->color_data = color_data; }

		glm::vec3 Get_Vertex_Position() { return this->vertex_position; }
		glm::vec2 Get_Texture_Coord() { return this->texture_coord; }
		glm::vec3 Get_Color_Data() { return this->color_data; }
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
	/*[ (IE_Mesh)                             ]
	 Creates and send the vertex data to the
	 shader.
	*/
	class IE_Mesh {
/* Default Class Structures */
	public:
		IE_Mesh();
		IE_Mesh(ID_Vertex_Data* vertices, const short unsigned int vertex_count, unsigned int* indices,const short unsigned int indice_count);
		~IE_Mesh() {};

		IE_Mesh(const IE_Mesh& other_ie_mesh);
		IE_Mesh operator=(const IE_Mesh& rhs);
	private:
/* Public Functions/Macros  */
	public:
		void Draw();
		void Delete();
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		unsigned int draw_count;

		GLuint vertex_array_object;
		GLuint vertex_buffer_object;
		GLuint vertex_texture_object;
		GLuint vertex_color_object;
		GLuint vertex_element_object;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_MESH