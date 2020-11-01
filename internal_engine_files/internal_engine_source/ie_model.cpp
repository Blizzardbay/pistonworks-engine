#include "internal_engine_headers\ie_model.h"
namespace pw {
/* ID_DOWN_RS_Triangle      */
/* Static Declarations      */
	ID_Vertex_Data ID_DOWN_RS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	unsigned int ID_DOWN_RS_Triangle::indices[3] {
			0,2,1
	};
/* Class Members            */
	void ID_DOWN_RS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_DOWN_RS_Triangle::Get_Vertices(), ID_DOWN_RS_Triangle::Get_Vertices_Size(), ID_DOWN_RS_Triangle::Get_Indices(), ID_DOWN_RS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_DOWN_RS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_DOWN_RS_Triangle::Get_Vertices_Size(); ++i) {
			ID_DOWN_RS_Triangle::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_DOWN_RS_Triangle::Get_Vertices(), ID_DOWN_RS_Triangle::Get_Vertices_Size(), ID_DOWN_RS_Triangle::Get_Indices(), ID_DOWN_RS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_DOWN_LS_Triangle      */
/* Static Declarations      */
	ID_Vertex_Data ID_DOWN_LS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	unsigned int ID_DOWN_LS_Triangle::indices[3] {
		0,2,1
	};
/* Class Members            */
	void ID_DOWN_LS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_DOWN_LS_Triangle::Get_Vertices(), ID_DOWN_LS_Triangle::Get_Vertices_Size(), ID_DOWN_LS_Triangle::Get_Indices(), ID_DOWN_LS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_DOWN_LS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_DOWN_LS_Triangle::Get_Vertices_Size(); ++i) {
			ID_DOWN_LS_Triangle::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_DOWN_LS_Triangle::Get_Vertices(), ID_DOWN_LS_Triangle::Get_Vertices_Size(), ID_DOWN_LS_Triangle::Get_Indices(), ID_DOWN_LS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_UP_RS_Triangle        */
/* Static Declarations      */
	ID_Vertex_Data ID_UP_RS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	unsigned int ID_UP_RS_Triangle::indices[3] {
			0,2,1
	};
/* Class Members            */
	void ID_UP_RS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_UP_RS_Triangle::Get_Vertices(), ID_UP_RS_Triangle::Get_Vertices_Size(), ID_UP_RS_Triangle::Get_Indices(), ID_UP_RS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_UP_RS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_UP_RS_Triangle::Get_Vertices_Size(); ++i) {
			ID_UP_RS_Triangle::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_UP_RS_Triangle::Get_Vertices(), ID_UP_RS_Triangle::Get_Vertices_Size(), ID_UP_RS_Triangle::Get_Indices(), ID_UP_RS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_UP_LS_Triangle        */
/* Static Declarations      */
	ID_Vertex_Data ID_UP_LS_Triangle::vertices[3] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f, 0.0f,0.0f),glm::vec2(1.0f,0.0f))
	};
	unsigned int ID_UP_LS_Triangle::indices[3] {
		0,2,1
	};
/* Class Members            */
	void ID_UP_LS_Triangle::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_UP_LS_Triangle::Get_Vertices(), ID_UP_LS_Triangle::Get_Vertices_Size(), ID_UP_LS_Triangle::Get_Indices(), ID_UP_LS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_UP_LS_Triangle::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_UP_LS_Triangle::Get_Vertices_Size(); ++i) {
			ID_UP_LS_Triangle::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_UP_LS_Triangle::Get_Vertices(), ID_UP_LS_Triangle::Get_Vertices_Size(), ID_UP_LS_Triangle::Get_Indices(), ID_UP_LS_Triangle::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_Square                */
/* Static Declarations      */
	ID_Vertex_Data ID_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	unsigned int ID_Square::indices[6] {
		0,2,1,
		0,2,3
	};
/* Class Members            */
	void ID_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_Square::Get_Vertices(), ID_Square::Get_Vertices_Size(), ID_Square::Get_Indices(), ID_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_Square::Get_Vertices_Size(); ++i) {
			ID_Square::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_Square::Get_Vertices(), ID_Square::Get_Vertices_Size(), ID_Square::Get_Indices(), ID_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_HAFE_RS_Square        */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_RS_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.5f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.5f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	unsigned int ID_HAFE_RS_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	void ID_HAFE_RS_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_RS_Square::Get_Vertices(), ID_HAFE_RS_Square::Get_Vertices_Size(), ID_HAFE_RS_Square::Get_Indices(), ID_HAFE_RS_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_HAFE_RS_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_HAFE_RS_Square::Get_Vertices_Size(); ++i) {
			ID_HAFE_RS_Square::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_RS_Square::Get_Vertices(), ID_HAFE_RS_Square::Get_Vertices_Size(), ID_HAFE_RS_Square::Get_Indices(), ID_HAFE_RS_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_HAFE_LS_Square        */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_LS_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(0.5f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(0.5f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	unsigned int ID_HAFE_LS_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	void ID_HAFE_LS_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_LS_Square::Get_Vertices(), ID_HAFE_LS_Square::Get_Vertices_Size(), ID_HAFE_LS_Square::Get_Indices(), ID_HAFE_LS_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_HAFE_LS_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_HAFE_LS_Square::Get_Vertices_Size(); ++i) {
			ID_HAFE_LS_Square::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_LS_Square::Get_Vertices(), ID_HAFE_LS_Square::Get_Vertices_Size(), ID_HAFE_LS_Square::Get_Indices(), ID_HAFE_LS_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_HAFE_UP_Square        */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_UP_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-0.5f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-0.5f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
	};
	unsigned int ID_HAFE_UP_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	void ID_HAFE_UP_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_UP_Square::Get_Vertices(), ID_HAFE_UP_Square::Get_Vertices_Size(), ID_HAFE_UP_Square::Get_Indices(), ID_HAFE_UP_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_HAFE_UP_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_HAFE_UP_Square::Get_Vertices_Size(); ++i) {
			ID_HAFE_UP_Square::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_UP_Square::Get_Vertices(), ID_HAFE_UP_Square::Get_Vertices_Size(), ID_HAFE_UP_Square::Get_Indices(), ID_HAFE_UP_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* ID_HAFE_DOWN_Square      */
/* Static Declarations      */
	ID_Vertex_Data ID_HAFE_DOWN_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,-0.5f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-0.5f,0.0f),glm::vec2(1.0f,1.0f))
	};
	unsigned int ID_HAFE_DOWN_Square::indices[6] {
			0,2,1,
			0,2,3
	};
/* Class Members            */
	void ID_HAFE_DOWN_Square::Handle_Model_Data_NOC(IE_Mesh*& model_mesh) {
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_DOWN_Square::Get_Vertices(), ID_HAFE_DOWN_Square::Get_Vertices_Size(), ID_HAFE_DOWN_Square::Get_Indices(), ID_HAFE_DOWN_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
	void ID_HAFE_DOWN_Square::Handle_Model_Data_C(IE_Mesh*& model_mesh, glm::vec3 model_color) {
		for (size_t i = 0; i < ID_HAFE_DOWN_Square::Get_Vertices_Size(); ++i) {
			ID_HAFE_DOWN_Square::Get_Vertices()[i].Set_Color_Data(model_color);
		}
		IE_Mesh* mesh = new IE_Mesh(ID_HAFE_DOWN_Square::Get_Vertices(), ID_HAFE_DOWN_Square::Get_Vertices_Size(), ID_HAFE_DOWN_Square::Get_Indices(), ID_HAFE_DOWN_Square::Get_Indices_Size());
		model_mesh = mesh;
		mesh = nullptr;
		delete mesh;
	}
/* IE_Model                 */
/* Static Declarations      */
	void(*IE_Model::model_functions_noc[(int)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh) {
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
	void(*IE_Model::model_functions_c[(int)Model_Types::TYPE_COUNT - 1])(IE_Mesh*& model_mesh, glm::vec3 model_color) {
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
	void(*IE_Model::model_collision_dectection[(int)Model_Types::TYPE_COUNT - 1])() {

	};
/* Class Members            */
	IE_Model::IE_Model() :
			model_texture(NULL), model_position(NULL), model_rotation(NULL), model_size(NULL),
			model_mesh(nullptr), model_type(IE_Model::Model_Types::UNINIT), model_is_colored(false), model_color(NULL) {
		model_mesh = new IE_Mesh;
	}
	IE_Model::IE_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size) :
			model_texture(texture), model_position(model_position), model_rotation(model_rotation), model_size(model_size),
			model_mesh(nullptr), model_type(type), model_is_colored(false), model_color(glm::vec3(0.0f,0.0f,0.0f)) {
		model_mesh = new IE_Mesh;
		model_functions_noc[(int)model_type](this->model_mesh);
	}
	IE_Model::IE_Model(Model_Types type, IE_Texture texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size, glm::vec3 model_color) :
			model_texture(texture), model_position(model_position), model_rotation(model_rotation), model_size(model_size),
			model_mesh(nullptr), model_type(type), model_is_colored(true), model_color(model_color) {
		model_mesh = new IE_Mesh;
		model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
	}
	void IE_Model::Render(IE_Shader shader) {
		shader.Use();

		shader.Update_Matrices(this->Handle_Calculations(), this->model_is_colored);

		this->model_texture.Bind(0);
		this->model_mesh->Draw();
	}
	void IE_Model::Delete() {
		delete model_mesh;
		model_mesh = nullptr;
		model_texture.Delete();
	}
	void IE_Model::Handle_Collisions(ID_Collision_Model_Data& m_model, ID_Collision_Model_Data& s_model) {
		ID_Collision_Model_Data* model_1 = &m_model;
		ID_Collision_Model_Data* model_2 = &s_model;

		for (size_t i = 0; i < 2; i++) {
			if (i == 1) {
				model_1 = &s_model;
				model_2 = &m_model;
			}
			for (size_t j = 0; j < m_model.Get_Vertices_Count(); j++) {

				Engine_2D_PVector model_line_1c = Engine_2D_PVector(glm::vec2(model_1->Get_Position().x, model_1->Get_Position().y));

				Engine_2D_PVector model_line_1e = Engine_2D_PVector(glm::vec2(
					model_1->Get_Vertices()[j].Get_Vertex_Position().x * Engine_Constant::Get_Buffer_Width() / 2.0f + Engine_Constant::Get_Hafe_Buffer_Width(),
					model_1->Get_Vertices()[j].Get_Vertex_Position().y * Engine_Constant::Get_Buffer_Height() / 2.0f + Engine_Constant::Get_Hafe_Buffer_Height()
				));

				glm::vec3 static_resolve = glm::vec3(0.0f);

				for (size_t k = 0; k < s_model.Get_Vertices_Count(); k++) {

					Engine_2D_PVector model_line_2c = Engine_2D_PVector(glm::vec2(
						model_2->Get_Vertices()[k].Get_Vertex_Position().x * Engine_Constant::Get_Buffer_Width() / 2.0f + Engine_Constant::Get_Hafe_Buffer_Width(),
						model_2->Get_Vertices()[k].Get_Vertex_Position().y * Engine_Constant::Get_Buffer_Height() / 2.0f + Engine_Constant::Get_Hafe_Buffer_Height()
					));

					Engine_2D_PVector model_line_2e = Engine_2D_PVector(glm::vec2(
						model_2->Get_Vertices()[(k + 1) % model_2->Get_Vertices_Count()].Get_Vertex_Position().x * Engine_Constant::Get_Buffer_Width() / 2.0f + Engine_Constant::Get_Hafe_Buffer_Width(),
						model_2->Get_Vertices()[(k + 1) % model_2->Get_Vertices_Count()].Get_Vertex_Position().y * Engine_Constant::Get_Buffer_Height() / 2.0f + Engine_Constant::Get_Hafe_Buffer_Height()
					));

					float h = 
						  (model_line_2e.Get_X_Position() - model_line_2c.Get_X_Position())
						* (model_line_1c.Get_Y_Position() - model_line_1e.Get_Y_Position())
						- (model_line_1c.Get_X_Position() - model_line_1e.Get_X_Position())
						* (model_line_2e.Get_Y_Position() - model_line_2c.Get_Y_Position());
					float t1 =
						 ((model_line_2c.Get_Y_Position() - model_line_2e.Get_Y_Position())
						* (model_line_1c.Get_X_Position() - model_line_2c.Get_X_Position())
						+ (model_line_2e.Get_X_Position() - model_line_2c.Get_X_Position())
						* (model_line_1c.Get_Y_Position() - model_line_2c.Get_Y_Position())) / h;
					float t2 =
						 ((model_line_1c.Get_Y_Position() - model_line_1e.Get_Y_Position())
						* (model_line_1c.Get_X_Position() - model_line_2c.Get_X_Position())
						+ (model_line_1e.Get_X_Position() - model_line_1c.Get_X_Position())
						* (model_line_1c.Get_Y_Position() - model_line_2c.Get_Y_Position())) / h;

					if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f) {
						static_resolve = glm::vec3(
							static_resolve.x + ((1.0f - t1) * (model_line_1e.Get_X_Position() - model_line_1c.Get_X_Position())),
							static_resolve.y + ((1.0f - t1) * (model_line_1e.Get_Y_Position() - model_line_1c.Get_Y_Position())),
							static_resolve.z
						);
					}
				}
				m_model.Set_X_Position(m_model.Get_X_Position() + static_resolve.x * (i == 0 ? -1 : +1));
				m_model.Set_Y_Position(m_model.Get_Y_Position() + static_resolve.y * (i == 0 ? -1 : +1));
			}
		}
	}
	glm::mat4 IE_Model::Handle_Calculations() {
		glm::mat4 model(1.0f);
		float pos_x = model_position.x;
		float pos_y = model_position.y;
		float size_x = model_size.x;
		float size_y = model_size.y;

		model_central_position.x = model_position.x / 2.0f;
		model_central_position.y = model_position.y / 2.0f;

		pos_x = ((model_position.x / Engine_Constant::Get_Buffer_Width()) * 2.0f) - 1.0f;
		pos_y = ((model_position.y / Engine_Constant::Get_Buffer_Height()) * 2.0f) - 1.0f;

		size_x = model_size.x / Engine_Constant::Get_Hafe_Buffer_Width();
		size_y = model_size.y / Engine_Constant::Get_Hafe_Buffer_Height();
		
		model = glm::translate(model, glm::vec3(pos_x, pos_y, -(1 / tan(glm::radians(45.0f / 2.0f)))));
		model = glm::rotate(model, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(size_x, size_y, 1.0f));

		return model;
	}
}