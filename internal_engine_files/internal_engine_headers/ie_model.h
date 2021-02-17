#ifndef H_IE_MODEL
#define H_IE_MODEL

//(DUAL_FILE)

/* C++ Headers              */
#include <cmath>
/* Project Headers          */
#include <glm\glm.hpp>
/* Engine Headers           */
#include "ie_mesh.h"
#include "ie_texture.h"
#include "ie_shader.h"
#include "engine_headers\engine_constant.h"
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
		/* -ID_DOWN_RS_Triangle
		 Holds the data for a ID_DOWN_RS_Triangle.
		 XXo
		 Xoo
		 ooo
		 Picture of triangle (X = blank) (o = triangle)
		*/
		struct ID_DOWN_RS_Triangle {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		/* -ID_DOWN_LS_Triangle
		 Holds the data for a ID_DOWN_LS_Triangle.
		 oXX
		 ooX
		 ooo
		 Picture of triangle (X = blank) (o = triangle)
		*/
		struct ID_DOWN_LS_Triangle {
			/* Default Class Structures */
		public:
		private:
			/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		/* -ID_UP_RS_Triangle
		 Holds the data for a ID_UP_RS_Triangle.
		 XXo
		 Xoo
		 ooo
		 Picture of triangle (X = blank) (o = triangle)
		*/
		struct ID_UP_RS_Triangle {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		/* -ID_UP_LS_Triangle
		 Holds the data for a ID_UP_LS_Triangle.
		 ooo
		 ooX
		 oXX
		 Picture of triangle (X = blank) (o = triangle)
		*/
		struct ID_UP_LS_Triangle {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		/* -ID_Square
		 Holds the data for a ID_Square.
		 ooo
		 ooo
		 ooo
		 Picture of square (x = blank) (o = square)
		*/
		struct ID_Square {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		/* -ID_HAFE_RS_Square
		 Holds the data for a ID_HAFE_RS_Square.
		 ooo
		 ooo
		 ooo
		 Picture of square (x = blank) (o = square)
		*/
		struct ID_HAFE_RS_Square {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		/* -ID_HAFE_LS_Square
		 Holds the data for a ID_HAFE_LS_Square.
		 ooo
		 ooo
		 ooo
		 Picture of square (x = blank) (o = square)
		*/
		struct ID_HAFE_LS_Square {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		/* -ID_HAFE_UP_Square
		 Holds the data for a ID_HAFE_UP_Square.
		 ooo
		 ooo----(cut in two)
		 XXX
		 Picture of square (x = blank) (o = square)
		*/
		struct ID_HAFE_UP_Square {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		/* -ID_HAFE_DOWN_Square
		 Holds the data for a ID_HAFE_DOWN_Square.
		 XXX
		 ooo----(cut in two)
		 ooo
		 Picture of square (x = blank) (o = square)
		*/
		struct ID_HAFE_DOWN_Square {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static ID_Vertex_Data* Get_Vertices() { return vertices; }
			static PW_UINT* Get_Indices() { return indices; }
			static const PW_SUINT Get_Vertices_Size() { return vertices_size; }
			static const PW_SUINT Get_Indices_Size() { return indices_size; }

			static PW_VOID Handle_Model_Data_NOC(Mesh*& model_mesh);
			static PW_VOID Handle_Model_Data_C(Mesh*& model_mesh, glm::vec3 model_color);
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		class Dynamic_Model;
		/* -Static_Model
		 A structure that holds all data for a
		 model. Does not update.
		*/
		class Static_Model {
	/* Default Class Structures */
		public:
			enum class Model_Types {
				UNINIT,
				DOWN_RS_TRIANGLE,
				DOWN_LS_TRIANGLE,
				UP_RS_TRIANGLE,
				UP_LS_TRIANGLE,
				SQUARE,
				HAFE_RS_SQUARE,
				HAFE_LS_SQUARE,
				HAFE_UP_SQUARE,
				HAFE_DOWN_SQUARE,
				TYPE_COUNT
			};
			Static_Model();
			Static_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size);
			Static_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec3 model_color);
			~Static_Model() {};
		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Render();
			PW_VOID Delete();

			glm::vec3 Position() { return model_position; }
			glm::vec3& Position_Reference() { return model_position; }
			Model_Types Model_Type() { return model_type; }

			PW_FLOAT Rotation() { return model_rotation; }
			glm::vec2 Model_Size() { return model_size; }
			Mesh* Model_Mesh() { return model_mesh; }
			Mesh*& Model_Mesh_Reference() { return model_mesh; }
	/* Public Variables         */
		public:
			static PW_VOID(*model_functions_noc[(PW_INT)Model_Types::TYPE_COUNT - 1])(Mesh*& model_mesh);
			static PW_VOID(*model_functions_c[(PW_INT)Model_Types::TYPE_COUNT - 1])(Mesh*& model_mesh, glm::vec3 model_color);

			static ID_Vertex_Data* model_vertices[(PW_INT)Model_Types::TYPE_COUNT - 1];
			static const PW_SUINT model_vertices_count[(PW_INT)Model_Types::TYPE_COUNT - 1];

			PW_VOID Refresh_Model();
	/* Private Functions/Macros */
		private:
			glm::mat4 Handle_Calculations();
	/* Private Variables        */
		private:
			Model_Types model_type;
			Mesh* model_mesh;
			Texture model_texture;
			glm::vec3 model_color;
			PW_BOOL model_is_colored;

			glm::vec3 model_position;
			glm::vec2 model_size;
			PW_FLOAT model_rotation;

			glm::mat4 model_matrix;
		};
		/* -Dynamic_Model
		 A structure that holds all data for a
		 model. Updates frequently.
		*/
		class Dynamic_Model {
	/* Default Class Structures */
		public:
			enum class Model_Types {
				UNINIT,
				DOWN_RS_TRIANGLE,
				DOWN_LS_TRIANGLE,
				UP_RS_TRIANGLE,
				UP_LS_TRIANGLE,
				SQUARE,
				HAFE_RS_SQUARE,
				HAFE_LS_SQUARE,
				HAFE_UP_SQUARE,
				HAFE_DOWN_SQUARE,
				TYPE_COUNT
			};
			Dynamic_Model();
			Dynamic_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size);
			Dynamic_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec3 model_color);
			~Dynamic_Model() {};
		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Render();
			PW_VOID Delete();

			glm::vec3 Position() { return model_position; }
			glm::vec3& Position_Reference() { return model_position; }

			glm::vec3 Last_Postition() { return model_last_position; }
			glm::vec3& Last_Postition_Reference() { return model_last_position; }

			Model_Types Model_Type() { return model_type; }

			PW_FLOAT Rotation() { return model_rotation; }
			glm::vec2 Model_Size() { return model_size; }
			Mesh* Model_Mesh() { return model_mesh; }
			Mesh*& Model_Mesh_Reference() { return model_mesh; }
			PW_BOOL Collided() { return collided; }

			PW_VOID Set_Model_Color(glm::vec3 new_model_color) { model_color = new_model_color; model_functions_c[(int)this->model_type - 1](this->model_mesh, this->model_color); }
			PW_VOID Update_Position(glm::vec2 position) { this->model_position.x = position.x; this->model_position.y = position.y; }
			PW_VOID Update_Position(PW_FLOAT x_pos, PW_FLOAT y_pos) { this->model_position.x = x_pos; this->model_position.y = y_pos; };
			PW_VOID Set_Collided(PW_BOOL new_state) { collided = new_state; }

			PW_BOOL Handle_Collisions(Dynamic_Model& m_model);

			PW_VOID Refresh_Model();
	/* Public Variables         */
		public:
			static PW_VOID(*model_functions_noc[(PW_INT)Model_Types::TYPE_COUNT - 1])(Mesh*& model_mesh);
			static PW_VOID(*model_functions_c[(PW_INT)Model_Types::TYPE_COUNT - 1])(Mesh*& model_mesh, glm::vec3 model_color);

			static ID_Vertex_Data* model_vertices[(PW_INT)Model_Types::TYPE_COUNT - 1];
			static const PW_SUINT model_vertices_count[(PW_INT)Model_Types::TYPE_COUNT - 1];
	/* Private Functions/Macros */
		private:
			glm::mat4 Handle_Calculations(PW_BOOL dynamic_override);
			glm::mat4 Handle_Calculations();
	/* Private Variables        */
		private:
			Model_Types model_type;
			Mesh* model_mesh;
			Texture model_texture;
			glm::vec3 model_color;
			PW_BOOL model_is_colored;

			glm::vec3 model_position;
			glm::vec3 model_last_position;
			glm::vec2 model_size;
			PW_FLOAT model_rotation;

			PW_BOOL collided;

			glm::mat4 model_matrix;
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_MODEL