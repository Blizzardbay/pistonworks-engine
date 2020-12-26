#include "internal_engine_headers\ie_model.h"
#include "internal_engine_headers\ie_player.h"
namespace pw {
/* ID_DOWN_RS_Triangle      */
/* Static Declarations      */
	ID_Vertex_Data ID_DOWN_RS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	PW_UINT ID_DOWN_RS_Triangle::indices[3] {
			0,2,1
	};
/* Class Members            */
	PW_VOID ID_DOWN_RS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_DOWN_RS_Triangle::Get_Vertices(), ID_DOWN_RS_Triangle::Get_Vertices_Size(), ID_DOWN_RS_Triangle::Get_Indices(), ID_DOWN_RS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_DOWN_RS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_DOWN_RS_Triangle::Get_Vertices(), ID_DOWN_RS_Triangle::Get_Vertices_Size(), ID_DOWN_RS_Triangle::Get_Indices(), ID_DOWN_RS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_DOWN_LS_Triangle      */
/* Static Declarations      */
	ID_Vertex_Data ID_DOWN_LS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	PW_UINT ID_DOWN_LS_Triangle::indices[3] {
		0,2,1
	};
/* Class Members            */
	PW_VOID ID_DOWN_LS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_DOWN_LS_Triangle::Get_Vertices(), ID_DOWN_LS_Triangle::Get_Vertices_Size(), ID_DOWN_LS_Triangle::Get_Indices(), ID_DOWN_LS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_DOWN_LS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_DOWN_LS_Triangle::Get_Vertices(), ID_DOWN_LS_Triangle::Get_Vertices_Size(), ID_DOWN_LS_Triangle::Get_Indices(), ID_DOWN_LS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_UP_RS_Triangle        */
/* Static Declarations      */
	ID_Vertex_Data ID_UP_RS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	PW_UINT ID_UP_RS_Triangle::indices[3] {
			0,2,1
	};
/* Class Members            */
	PW_VOID ID_UP_RS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_UP_RS_Triangle::Get_Vertices(), ID_UP_RS_Triangle::Get_Vertices_Size(), ID_UP_RS_Triangle::Get_Indices(), ID_UP_RS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_UP_RS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_UP_RS_Triangle::Get_Vertices(), ID_UP_RS_Triangle::Get_Vertices_Size(), ID_UP_RS_Triangle::Get_Indices(), ID_UP_RS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_UP_LS_Triangle        */
/* Static Declarations      */
	ID_Vertex_Data ID_UP_LS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f, 0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	PW_UINT ID_UP_LS_Triangle::indices[3] {
		0,2,1
	};
/* Class Members            */
	PW_VOID ID_UP_LS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_UP_LS_Triangle::Get_Vertices(), ID_UP_LS_Triangle::Get_Vertices_Size(), ID_UP_LS_Triangle::Get_Indices(), ID_UP_LS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_UP_LS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_UP_LS_Triangle::Get_Vertices(), ID_UP_LS_Triangle::Get_Vertices_Size(), ID_UP_LS_Triangle::Get_Indices(), ID_UP_LS_Triangle::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_Square                */
/* Static Declarations      */
	ID_Vertex_Data ID_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	PW_UINT ID_Square::indices[6] {
		0,2,1,
		0,2,3
	};
/* Class Members            */
	PW_VOID ID_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_Square::Get_Vertices(), ID_Square::Get_Vertices_Size(), ID_Square::Get_Indices(), ID_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_Square::Get_Vertices(), ID_Square::Get_Vertices_Size(), ID_Square::Get_Indices(), ID_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_HAFE_RS_Square        */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_RS_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.5f,0.0f,0.0f),glm::vec2(0.5f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.5f,-1.0f,0.0f),glm::vec2(0.5f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	PW_UINT ID_HAFE_RS_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	PW_VOID ID_HAFE_RS_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_RS_Square::Get_Vertices(), ID_HAFE_RS_Square::Get_Vertices_Size(), ID_HAFE_RS_Square::Get_Indices(), ID_HAFE_RS_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_HAFE_RS_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_RS_Square::Get_Vertices(), ID_HAFE_RS_Square::Get_Vertices_Size(), ID_HAFE_RS_Square::Get_Indices(), ID_HAFE_RS_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_HAFE_LS_Square        */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_LS_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(0.5f,-1.0f,0.0f),glm::vec2(0.5f,0.0f)),
			ID_Vertex_Data(glm::vec3(0.5f,0.0f,0.0f),glm::vec2(0.5f,1.0f))
	};
	PW_UINT ID_HAFE_LS_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	PW_VOID ID_HAFE_LS_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_LS_Square::Get_Vertices(), ID_HAFE_LS_Square::Get_Vertices_Size(), ID_HAFE_LS_Square::Get_Indices(), ID_HAFE_LS_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_HAFE_LS_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_LS_Square::Get_Vertices(), ID_HAFE_LS_Square::Get_Vertices_Size(), ID_HAFE_LS_Square::Get_Indices(), ID_HAFE_LS_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_HAFE_UP_Square        */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_UP_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-0.5f,0.0f),glm::vec2(0.0f,0.5f)),
			ID_Vertex_Data(glm::vec3(1.0f,-0.5f,0.0f),glm::vec2(1.0f,0.5f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	PW_UINT ID_HAFE_UP_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	PW_VOID ID_HAFE_UP_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_UP_Square::Get_Vertices(), ID_HAFE_UP_Square::Get_Vertices_Size(), ID_HAFE_UP_Square::Get_Indices(), ID_HAFE_UP_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_HAFE_UP_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_UP_Square::Get_Vertices(), ID_HAFE_UP_Square::Get_Vertices_Size(), ID_HAFE_UP_Square::Get_Indices(), ID_HAFE_UP_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* ID_HAFE_DOWN_Square      */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_DOWN_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,-0.5f,0.0f),glm::vec2(0.0f,0.5f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-0.5f,0.0f),glm::vec2(1.0f,0.5f))
	};
	PW_UINT ID_HAFE_DOWN_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	PW_VOID ID_HAFE_DOWN_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_DOWN_Square::Get_Vertices(), ID_HAFE_DOWN_Square::Get_Vertices_Size(), ID_HAFE_DOWN_Square::Get_Indices(), ID_HAFE_DOWN_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
	}
	PW_VOID ID_HAFE_DOWN_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		if (model_mesh == nullptr) {
			model_mesh = new IE_Mesh;
			IE_Mesh* mesh = new IE_Mesh(ID_HAFE_DOWN_Square::Get_Vertices(), ID_HAFE_DOWN_Square::Get_Vertices_Size(), ID_HAFE_DOWN_Square::Get_Indices(), ID_HAFE_DOWN_Square::Get_Indices_Size());
			model_mesh = mesh;
			mesh = nullptr;
			delete mesh;
		}
		model_mesh->Change_Color_Data(model_color);
	}
/* IE_Static_Model          */
/* Static Declarations      */
	PW_VOID(*IE_Static_Model::model_functions_noc[(PW_INT)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh) {
		ID_DOWN_RS_Triangle::Handle_Model_Data_NOC,
		ID_DOWN_LS_Triangle::Handle_Model_Data_NOC,
		ID_UP_RS_Triangle::Handle_Model_Data_NOC,
		ID_UP_LS_Triangle::Handle_Model_Data_NOC,
		ID_Square::Handle_Model_Data_NOC,
		ID_HAFE_RS_Square::Handle_Model_Data_NOC,
		ID_HAFE_LS_Square::Handle_Model_Data_NOC,
		ID_HAFE_UP_Square::Handle_Model_Data_NOC,
		ID_HAFE_DOWN_Square::Handle_Model_Data_NOC
	};
	PW_VOID(*IE_Static_Model::model_functions_c[(PW_INT)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		ID_DOWN_RS_Triangle::Handle_Model_Data_C,
		ID_DOWN_LS_Triangle::Handle_Model_Data_C,
		ID_UP_RS_Triangle::Handle_Model_Data_C,
		ID_UP_LS_Triangle::Handle_Model_Data_C,
		ID_Square::Handle_Model_Data_C,
		ID_HAFE_RS_Square::Handle_Model_Data_C,
		ID_HAFE_LS_Square::Handle_Model_Data_C,
		ID_HAFE_UP_Square::Handle_Model_Data_C,
		ID_HAFE_DOWN_Square::Handle_Model_Data_C
	};
	ID_Vertex_Data* IE_Static_Model::model_vertices[(PW_INT)Model_Types::TYPE_COUNT - 1] {
		ID_DOWN_RS_Triangle::Get_Vertices(),
		ID_DOWN_LS_Triangle::Get_Vertices(),
		ID_UP_RS_Triangle::Get_Vertices(),
		ID_UP_LS_Triangle::Get_Vertices(),
		ID_Square::Get_Vertices(),
		ID_HAFE_RS_Square::Get_Vertices(),
		ID_HAFE_LS_Square::Get_Vertices(),
		ID_HAFE_UP_Square::Get_Vertices(),
		ID_HAFE_DOWN_Square::Get_Vertices()
	};
	const PW_SUINT IE_Static_Model::model_vertices_count[(PW_INT)Model_Types::TYPE_COUNT - 1] {
		ID_DOWN_RS_Triangle::Get_Vertices_Size(),
		ID_DOWN_LS_Triangle::Get_Vertices_Size(),
		ID_UP_RS_Triangle::Get_Vertices_Size(),
		ID_UP_LS_Triangle::Get_Vertices_Size(),
		ID_Square::Get_Vertices_Size(),
		ID_HAFE_RS_Square::Get_Vertices_Size(),
		ID_HAFE_LS_Square::Get_Vertices_Size(),
		ID_HAFE_UP_Square::Get_Vertices_Size(),
		ID_HAFE_DOWN_Square::Get_Vertices_Size()
	};
/* Class Members            */
	IE_Static_Model::IE_Static_Model() :
			model_texture(NULL), model_position(NULL), model_rotation(NULL), model_size(NULL),
			model_mesh(nullptr), model_type(IE_Static_Model::Model_Types::UNINIT), model_is_colored(false), model_color(NULL),
			model_matrix(0.0f) {
	}
	IE_Static_Model::IE_Static_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size) :
			model_texture(texture), model_position(model_position, 0.0f), model_rotation(model_rotation), model_size(model_size),
			model_mesh(nullptr), model_type(type), model_is_colored(false), model_color(glm::vec3(0.0f,0.0f,0.0f)),
			model_matrix(0.0f) {
		model_functions_noc[(int)model_type - 1](this->model_mesh);
		model_matrix = Handle_Calculations();
	}
	IE_Static_Model::IE_Static_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec3 model_color) :
			model_texture(texture), model_position(model_position, 0.0f), model_rotation(model_rotation), model_size(model_size),
			model_mesh(nullptr), model_type(type), model_is_colored(true), model_color(model_color),
			model_matrix(0.0f) {
		model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
		model_matrix = Handle_Calculations();
	}
	PW_VOID IE_Static_Model::Render() {
		IE_Shader::Get_Shader().Use();

		IE_Shader::Get_Shader().Update_Matrices(this->model_matrix, this->model_is_colored);

		this->model_texture.Bind(0);
		this->model_mesh->Draw();
	}
	PW_VOID IE_Static_Model::Delete() {
		delete model_mesh;
		model_mesh = nullptr;
		model_texture.Delete();
	}
	glm::mat4 IE_Static_Model::Handle_Calculations() {
		glm::mat4 model(1.0f);
		PW_FLOAT pos_x = model_position.x;
		PW_FLOAT pos_y = model_position.y;
		PW_FLOAT size_x = model_size.x;
		PW_FLOAT size_y = model_size.y;

		pos_x = ((pos_x / (PW_FLOAT)Engine_Constant::Window_Width()) * 2.0f) - 1.0f;
		pos_y = ((pos_y / (PW_FLOAT)Engine_Constant::Window_Height()) * 2.0f) - 1.0f;

		size_x = size_x / (PW_FLOAT)Engine_Constant::Hafe_Window_Width();
		size_y = size_y / (PW_FLOAT)Engine_Constant::Hafe_Window_Height();
		
		model = glm::translate(model, glm::vec3(pos_x, pos_y, -(1.0f / tan(glm::radians(45.0f / 2.0f)))));
		model = glm::rotate(model, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(size_x, size_y, 1.0f));

		return model;
	}
/* IE_Dynamic_Model         */
/* Static Declarations      */
	PW_VOID(*IE_Dynamic_Model::model_functions_noc[(PW_INT)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh) {
		ID_DOWN_RS_Triangle::Handle_Model_Data_NOC,
		ID_DOWN_LS_Triangle::Handle_Model_Data_NOC,
		ID_UP_RS_Triangle::Handle_Model_Data_NOC,
		ID_UP_LS_Triangle::Handle_Model_Data_NOC,
		ID_Square::Handle_Model_Data_NOC,
		ID_HAFE_RS_Square::Handle_Model_Data_NOC,
		ID_HAFE_LS_Square::Handle_Model_Data_NOC,
		ID_HAFE_UP_Square::Handle_Model_Data_NOC,
		ID_HAFE_DOWN_Square::Handle_Model_Data_NOC
	};
	PW_VOID(*IE_Dynamic_Model::model_functions_c[(PW_INT)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		ID_DOWN_RS_Triangle::Handle_Model_Data_C,
		ID_DOWN_LS_Triangle::Handle_Model_Data_C,
		ID_UP_RS_Triangle::Handle_Model_Data_C,
		ID_UP_LS_Triangle::Handle_Model_Data_C,
		ID_Square::Handle_Model_Data_C,
		ID_HAFE_RS_Square::Handle_Model_Data_C,
		ID_HAFE_LS_Square::Handle_Model_Data_C,
		ID_HAFE_UP_Square::Handle_Model_Data_C,
		ID_HAFE_DOWN_Square::Handle_Model_Data_C
	};
	ID_Vertex_Data* IE_Dynamic_Model::model_vertices[(PW_INT)Model_Types::TYPE_COUNT - 1] {
		ID_DOWN_RS_Triangle::Get_Vertices(),
		ID_DOWN_LS_Triangle::Get_Vertices(),
		ID_UP_RS_Triangle::Get_Vertices(),
		ID_UP_LS_Triangle::Get_Vertices(),
		ID_Square::Get_Vertices(),
		ID_HAFE_RS_Square::Get_Vertices(),
		ID_HAFE_LS_Square::Get_Vertices(),
		ID_HAFE_UP_Square::Get_Vertices(),
		ID_HAFE_DOWN_Square::Get_Vertices()
	};
	const PW_SUINT IE_Dynamic_Model::model_vertices_count[(PW_INT)Model_Types::TYPE_COUNT - 1] {
		ID_DOWN_RS_Triangle::Get_Vertices_Size(),
		ID_DOWN_LS_Triangle::Get_Vertices_Size(),
		ID_UP_RS_Triangle::Get_Vertices_Size(),
		ID_UP_LS_Triangle::Get_Vertices_Size(),
		ID_Square::Get_Vertices_Size(),
		ID_HAFE_RS_Square::Get_Vertices_Size(),
		ID_HAFE_LS_Square::Get_Vertices_Size(),
		ID_HAFE_UP_Square::Get_Vertices_Size(),
		ID_HAFE_DOWN_Square::Get_Vertices_Size()
	};
/* Class Members            */
	IE_Dynamic_Model::IE_Dynamic_Model() :
			model_texture(NULL), model_position(NULL), model_last_position(NULL), model_rotation(NULL),
			model_size(NULL), model_mesh(NULL), model_type(IE_Dynamic_Model::Model_Types::UNINIT), model_is_colored(false),
			model_color(NULL), model_matrix(0.0f), collided(false) {
	}
	IE_Dynamic_Model::IE_Dynamic_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size) :
			model_texture(texture), model_position(model_position, 0.0f), model_last_position(NULL), model_rotation(model_rotation),
			model_size(model_size), model_mesh(NULL), model_type(type), model_is_colored(false),
			model_color(glm::vec3(0.0f, 0.0f, 0.0f)), model_matrix(0.0f), collided(false) {
		model_functions_noc[(int)model_type - 1](this->model_mesh);
	}
	IE_Dynamic_Model::IE_Dynamic_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec3 model_color) :
			model_texture(texture), model_position(model_position, 0.0f), model_last_position(NULL), model_rotation(model_rotation),
			model_size(model_size), model_mesh(NULL), model_type(type), model_is_colored(true),
			model_color(model_color), model_matrix(0.0f), collided(false) {
		model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
	}
	PW_VOID IE_Dynamic_Model::Render() {
		IE_Shader::Get_Shader().Use();

		IE_Shader::Get_Shader().Update_Matrices(this->Handle_Calculations(), this->model_is_colored);

		this->model_texture.Bind(0);
		this->model_mesh->Draw();
	}
	PW_VOID IE_Dynamic_Model::Delete() {
		delete model_mesh;
		model_mesh = nullptr;
		model_texture.Delete();
	}
	PW_BOOL IE_Dynamic_Model::Handle_Collisions(IE_Dynamic_Model& m_model) {
		if (abs(m_model.Position().x - this->Position().x) < 33 && abs(m_model.Position().y - this->Position().y) < 33) {
			IE_Dynamic_Model moveable_model = m_model;
			IE_Dynamic_Model static_model = *this;

			ID_Vertex_Data* m_vertices = model_vertices[(int)m_model.Model_Type() - 1];
			short unsigned int m_vertices_count = model_vertices_count[(int)m_model.Model_Type() - 1];

			ID_Vertex_Data* s_vertices = model_vertices[(int)this->Model_Type() - 1];
			short unsigned int s_vertices_count = model_vertices_count[(int)this->Model_Type() - 1];

			for (size_t i = 0; i < 2; i++) {
				if (i == 1) {
					ID_Vertex_Data* temp_data = m_vertices;
					m_vertices = s_vertices;
					s_vertices = temp_data;
					temp_data = nullptr;
					short unsigned int temp_int = m_vertices_count;
					m_vertices_count = s_vertices_count;
					s_vertices_count = temp_int;

					IE_Dynamic_Model temp_model = moveable_model;
					moveable_model = static_model;
					static_model = temp_model;
				}

				for (size_t j = 0; j < m_vertices_count; j++) {

					glm::vec2 line_r1s(
						0.0f, // X 
						0.0f  // Y
					);
					if (m_vertices_count == 3) {
						line_r1s = glm::vec2(
							((moveable_model.Position().x + (model_vertices[(int)moveable_model.Model_Type() - 1][0].Vertex_Position().x * moveable_model.Model_Size().x)) +
								(moveable_model.Position().x + (model_vertices[(int)moveable_model.Model_Type() - 1][1].Vertex_Position().x * moveable_model.Model_Size().x)) +
								(moveable_model.Position().x + (model_vertices[(int)moveable_model.Model_Type() - 1][2].Vertex_Position().x * moveable_model.Model_Size().x))) / 3, // X
							((moveable_model.Position().y + (model_vertices[(int)moveable_model.Model_Type() - 1][0].Vertex_Position().y * moveable_model.Model_Size().y)) +
								(moveable_model.Position().y + (model_vertices[(int)moveable_model.Model_Type() - 1][1].Vertex_Position().y * moveable_model.Model_Size().y)) +
								(moveable_model.Position().y + (model_vertices[(int)moveable_model.Model_Type() - 1][2].Vertex_Position().y * moveable_model.Model_Size().y))) / 3  // Y
						);
					}
					else {
						line_r1s = glm::vec2(
							(moveable_model.Position().x + ((moveable_model.Model_Size().x * (m_vertices[0].Vertex_Position().x + m_vertices[2].Vertex_Position().x)) / 2.0f)), // X
							(moveable_model.Position().y + ((moveable_model.Model_Size().y * (m_vertices[0].Vertex_Position().y + m_vertices[2].Vertex_Position().y)) / 2.0f))  // Y
						);
					}
					glm::vec2 line_r1e(
						moveable_model.Position().x + (m_vertices[j].Vertex_Position().x * m_model.Model_Size().x), // X
						moveable_model.Position().y + (m_vertices[j].Vertex_Position().y * m_model.Model_Size().y)  // Y
					);

					glm::vec2 overlap = glm::vec2(0.0f);

					for (size_t k = 0; k < s_vertices_count; k++) {
						glm::vec2 line_r2s(
							static_model.Position().x + (s_vertices[k].Vertex_Position().x * m_model.Model_Size().x), // X
							static_model.Position().y + (s_vertices[k].Vertex_Position().y * m_model.Model_Size().y)  // Y
						);
						glm::vec2 line_r2e(
							static_model.Position().x + (s_vertices[(k + 1) % s_vertices_count].Vertex_Position().x * m_model.Model_Size().x), // X
							static_model.Position().y + (s_vertices[(k + 1) % s_vertices_count].Vertex_Position().y * m_model.Model_Size().y)  // Y
						);
						
						float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
						float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
						float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

						if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f) {
							glm::vec2 line_center(
								((0.5f * (line_r2e.x - line_r2s.x)) + line_r2e.x),
								((0.5f * (line_r2e.y - line_r2s.y)) + line_r2e.y)
							);
							if (line_r2e.x - line_r2s.x == 0 || line_r2e.y - line_r2s.y == 0) {
								
							}
							else {
								overlap.x = (1.0f - t1) * (line_r1e.x - line_r1s.x);
								overlap.y = (1.0f - t1) * (line_r1e.y - line_r1s.y);
							}
							break;
						}
					}
					if (overlap != glm::vec2(0.0f, 0.0f)) {
						m_model.Position_Reference().x += overlap.x * (i == 0 ? -1 : +1);
						m_model.Position_Reference().y += overlap.y * (i == 0 ? -1 : +1);
					}
				}
			}
			return true;
		}
		return false;
	}
	glm::mat4 IE_Dynamic_Model::Handle_Calculations() {
		if (model_position != model_last_position) {
			glm::mat4 model(1.0f);
			PW_FLOAT pos_x = model_position.x;
			PW_FLOAT pos_y = model_position.y;
			PW_FLOAT size_x = model_size.x;
			PW_FLOAT size_y = model_size.y;

			model_last_position.x = model_position.x;
			model_last_position.y = model_position.y;

			pos_x = ((pos_x / (PW_FLOAT)Engine_Constant::Window_Width()) * 2.0f) - 1.0f;
			pos_y = ((pos_y / (PW_FLOAT)Engine_Constant::Window_Height()) * 2.0f) - 1.0f;

			size_x = size_x / (PW_FLOAT)Engine_Constant::Hafe_Window_Width();
			size_y = size_y / (PW_FLOAT)Engine_Constant::Hafe_Window_Height();

			model = glm::translate(model, glm::vec3(pos_x, pos_y, -(1.0f / tanf(glm::radians(45.0f / 2.0f)))));
			model = glm::rotate(model, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(size_x, size_y, 1.0f));

			model_matrix = model;

			return model;
		}
		else {
			collided = false;
			return model_matrix;
		}
	}
}
//glm::vec2 line_center(
//	((0.5f * (line_r2s.x - line_r2e.x)) + line_r2e.x),
//	((0.5f * (line_r2s.y - line_r2e.y)) + line_r2e.y)
//);
//
//bool x_move = (m_model.Position().x != m_model.Last_Postition().x);
//bool y_move = (m_model.Position().y != m_model.Last_Postition().y);
//
//if (line_r1e.y >= line_center.y) {
//	if (s_vertices_count == 3 || m_vertices_count == 3) {
//		if (y_move) {
//			overlap.y += ((1.0f - t1) * (line_r1s.y - line_r1e.y));
//		}
//		else {
//			overlap.x += ((1.0f - t1) * (line_r1s.x - line_r1e.x));
//		}
//	}
//	else {
//		if (y_move) {
//			overlap.y += ((1.0f - t1) * (line_r1s.y - line_r1e.y));
//		}
//		else {
//			overlap.x += ((1.0f - t1) * (line_r1s.x - line_r1e.x));
//		}
//	}
//}
//else {
//	if (s_vertices_count == 3) {
//		overlap.x += ((1.0f - t1) * (line_r1s.x - line_r1e.x));
//		if (static_model.Model_Type() == IE_Dynamic_Model::Model_Types::DOWN_RS_TRIANGLE
//			|| static_model.Model_Type() == IE_Dynamic_Model::Model_Types::DOWN_LS_TRIANGLE) {
//			overlap.y += ((1.0f - t1) * (line_r1s.y - line_r1e.y)) + 1.0f;
//		}
//	}
//	else {
//		if (m_vertices_count == 3) {
//			overlap.x += ((1.0f - t1) * (line_r1s.x - line_r1e.x));
//			if (static_model.Model_Type() == IE_Dynamic_Model::Model_Types::DOWN_RS_TRIANGLE
//				|| static_model.Model_Type() == IE_Dynamic_Model::Model_Types::DOWN_LS_TRIANGLE) {
//				overlap.y += ((1.0f - t1) * (line_r1s.y - line_r1e.y)) + 1.0f;
//			}
//		}
//	}
//}
//						}
//					}