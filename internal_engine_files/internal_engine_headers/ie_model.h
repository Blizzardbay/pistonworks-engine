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
#include "engine_headers\engine_math.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
	struct ID_MODEL_Data {
		/* Default Class Structures */
	public:
	private:
		/* Public Functions/Macros  */
	public:
		/* Public Variables         */
	public:
		/* Private Functions/Macros */
	private:
		/* Private Variables        */
	private:
	};
	/*                                             */
	/*[ (ID_DOWN_RS_Triangle)                       ]
	 Holds the data for a ID_DOWN_RS_Triangle.
	 XXo
	 Xoo
	 ooo
	 Picture of triangle (X = blank) (o = triangle)
	*/
	struct ID_DOWN_RS_Triangle : public ID_MODEL_Data {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static ID_Vertex_Data* Get_Vertices()  { return vertices; }
		static unsigned int* Get_Indices()  { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
		//static ID_Collision_Model_Data Create_Collisions_Profile();
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 3;
		static ID_Vertex_Data vertices[3];
		static const short unsigned int indices_size = 3;
		static unsigned int indices[3];
	};
	/*                                             */
	/*[ (ID_DOWN_LS_Triangle)                       ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 3;
		static ID_Vertex_Data vertices[3];
		static const short unsigned int indices_size = 3;
		static unsigned int indices[3];
	};
	/*                                             */
	/*[ (ID_UP_RS_Triangle)                         ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 3;
		static ID_Vertex_Data vertices[3];
		static const short unsigned int indices_size = 3;
		static unsigned int indices[3];
	};
	/*                                             */
	/*[ (ID_UP_LS_Triangle)                         ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 3;
		static ID_Vertex_Data vertices[3];
		static const short unsigned int indices_size = 3;
		static unsigned int indices[3];
	};
	/*                                             */
	/*[ (ID_Square)                                 ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 4;
		static ID_Vertex_Data vertices[4];
		static const short unsigned int indices_size = 6;
		static unsigned int indices[6];
	};
	/*                                             */
	/*[ (ID_HAFE_RS_Square)                         ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 4;
		static ID_Vertex_Data vertices[4];
		static const short unsigned int indices_size = 6;
		static unsigned int indices[6];
	};
	/*                                             */
	/*[ (ID_HAFE_LS_Square)                         ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 4;
		static ID_Vertex_Data vertices[4];
		static const short unsigned int indices_size = 6;
		static unsigned int indices[6];
	};
	/*                                             */
	/*[ (ID_HAFE_UP_Square)                         ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 4;
		static ID_Vertex_Data vertices[4];
		static const short unsigned int indices_size = 6;
		static unsigned int indices[6];
	};
	/*                                             */
	/*[ (ID_HAFE_DOWN_Square)                       ]
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
		static unsigned int* Get_Indices() { return indices; }
		static const short unsigned int Get_Vertices_Size() { return vertices_size; }
		static const short unsigned int Get_Indices_Size() { return indices_size; }

		static void Handle_Model_Data_NOC(IE_Mesh*& model_mesh);
		static void Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static const short unsigned int vertices_size = 4;
		static ID_Vertex_Data vertices[4];
		static const short unsigned int indices_size = 6;
		static unsigned int indices[6];
	};
	class ID_Collision_Model_Data;
	/*                                             */
	/*[ (IE_Model)                                  ]
	 A structure that holds all data for a
	 model.
	*/
	class IE_Model {
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
		IE_Model();
		IE_Model(Model_Types type,IE_Texture texture,glm::vec2 model_position, float model_rotation, glm::vec2 model_size);
		IE_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size,glm::vec3 model_color);
		~IE_Model() {};
	private:
/* Public Functions/Macros  */
	public:
		void Render(IE_Shader shader);
		void Delete();
		void Update_Position(glm::vec2 position) { this->model_position = position; }
		void Update_Position(float x_pos, float y_pos) { this->model_position.x = x_pos; this->model_position.y = y_pos; };

		int Get_IPosition_X() { return (int)model_position.x; }
		int Get_IPosition_Y() { return (int)model_position.y; }

		Model_Types Get_Model_Type() { return model_type; }
		// Credits to: https://www.youtube.com/watch?v=7Ik2vowGcU0&t=1734s
		static void Handle_Collisions(ID_Collision_Model_Data& m_model, ID_Collision_Model_Data& s_model);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		glm::mat4 Handle_Calculations();
/* Private Variables        */
	private:
		Model_Types model_type;
		IE_Mesh* model_mesh;
		IE_Texture model_texture;
		glm::vec3 model_color;
		bool model_is_colored;

		glm::vec2 model_central_position;
		glm::vec2 model_position;
		glm::vec2 model_size;

		float model_rotation;

		static void(*model_functions_noc[(int)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh);
		static void(*model_functions_c[(int)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh, glm::vec3 model_color);
		static void(*model_collision_dectection[(int)Model_Types::TYPE_COUNT - 1])();
	};
	/*                                             */
	/*[ (ID_Collision_Model_Data)                   ]
	 A structure that holds all data for a
	 model.
	*/
	class ID_Collision_Model_Data {
		/* Default Class Structures */
	public:
		ID_Collision_Model_Data(IE_Model::Model_Types model_type, ID_Vertex_Data vertices[], unsigned int vertices_count, glm::vec3& model_position, float model_angle) :
			model_type(model_type), vertices(vertices), vertices_count(vertices_count), model_position(model_position), model_angle(model_angle) {
		}
		~ID_Collision_Model_Data() {}
	private:
		/* Public Functions/Macros  */
	public:
		IE_Model::Model_Types Get_Model_Type() { return model_type; }
		ID_Vertex_Data* Get_Vertices() { return vertices; }
		unsigned int Get_Vertices_Count() { return vertices_count; }

		glm::vec3& Get_Position() { return model_position; }
		float Get_X_Position() { return model_position.x; }
		float Get_Y_Position() { return model_position.y; }
		float Get_Z_Position() { return model_position.z; }

		float Get_Rotation() { return model_angle; }

		void Set_Model_Type(IE_Model::Model_Types new_model_type) { model_type = new_model_type; }
		void Set_Vertices(ID_Vertex_Data new_vertices[]) { vertices = new_vertices; }
		void Set_Vertices_Count(unsigned int new_vertices_count) { vertices_count = new_vertices_count; }

		void Set_Position(glm::vec3& new_model_position) { model_position = new_model_position; }
		void Set_X_Position(float x_position) { model_position.x = x_position; }
		void Set_Y_Position(float y_position) { model_position.y = y_position; }
		void Set_Z_Position(float z_position) { model_position.z = z_position; }

		void Set_Rotation(float new_model_angle) { model_angle = new_model_angle; }
		/* Public Variables         */
	public:
		/* Private Functions/Macros */
	private:
		/* Private Variables        */
	private:
		IE_Model::Model_Types model_type;
		ID_Vertex_Data* vertices;
		unsigned int vertices_count;

		glm::vec3& model_position;
		float model_angle;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_MODEL