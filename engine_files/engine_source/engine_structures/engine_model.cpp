#include "internal_engine_headers\ie_model.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// ID_DOWN_RS_Triangle   
		// Static Declarations
			ID_Vertex_Data ID_DOWN_RS_Triangle::vertices[3] = {
				ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
			};
			PW_UINT ID_DOWN_RS_Triangle::indices[3]{
				0,2,1
			};
		// Class Members
			ID_Vertex_Data* ID_DOWN_RS_Triangle::Vertices() {
				return vertices;
			}
			PW_UINT* ID_DOWN_RS_Triangle::Indices() {
				return indices;
			}
			const PW_SUINT ID_DOWN_RS_Triangle::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_DOWN_RS_Triangle::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_DOWN_RS_Triangle::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_DOWN_RS_Triangle::Vertices(),
						ID_DOWN_RS_Triangle::Vertices_Size(),
						ID_DOWN_RS_Triangle::Indices(),
						ID_DOWN_RS_Triangle::Indices_Size()));
				}
			}
			PW_VOID ID_DOWN_RS_Triangle::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_DOWN_RS_Triangle::Vertices(),
						ID_DOWN_RS_Triangle::Vertices_Size(),
						ID_DOWN_RS_Triangle::Indices(),
						ID_DOWN_RS_Triangle::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_DOWN_LS_Triangle 
		// Static Declarations      
			ID_Vertex_Data ID_DOWN_LS_Triangle::vertices[3] = {
				ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
			};
			PW_UINT ID_DOWN_LS_Triangle::indices[3]{
				0,2,1
			};
		// Class Members
			ID_Vertex_Data* ID_DOWN_LS_Triangle::Vertices() {
				return vertices;
			}
			PW_UINT* ID_DOWN_LS_Triangle::Indices() {
				return indices;
			}
			const PW_SUINT ID_DOWN_LS_Triangle::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_DOWN_LS_Triangle::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_DOWN_LS_Triangle::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_DOWN_LS_Triangle::Vertices(),
						ID_DOWN_LS_Triangle::Vertices_Size(),
						ID_DOWN_LS_Triangle::Indices(),
						ID_DOWN_LS_Triangle::Indices_Size()));
				}
			}
			PW_VOID ID_DOWN_LS_Triangle::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_DOWN_LS_Triangle::Vertices(),
						ID_DOWN_LS_Triangle::Vertices_Size(),
						ID_DOWN_LS_Triangle::Indices(),
						ID_DOWN_LS_Triangle::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_UP_RS_Triangle       
		// Static Declarations     
			ID_Vertex_Data ID_UP_RS_Triangle::vertices[3] = {
				ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
			};
			PW_UINT ID_UP_RS_Triangle::indices[3]{
				0,2,1
			};
		// Class Members
			ID_Vertex_Data* ID_UP_RS_Triangle::Vertices() {
				return vertices;
			}
			PW_UINT* ID_UP_RS_Triangle::Indices() {
				return indices;
			}
			const PW_SUINT ID_UP_RS_Triangle::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_UP_RS_Triangle::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_UP_RS_Triangle::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_UP_RS_Triangle::Vertices(),
						ID_UP_RS_Triangle::Vertices_Size(),
						ID_UP_RS_Triangle::Indices(),
						ID_UP_RS_Triangle::Indices_Size()));
				}
			}
			PW_VOID ID_UP_RS_Triangle::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_UP_RS_Triangle::Vertices(),
						ID_UP_RS_Triangle::Vertices_Size(),
						ID_UP_RS_Triangle::Indices(),
						ID_UP_RS_Triangle::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_UP_LS_Triangle        
		// Static Declarations      
			ID_Vertex_Data ID_UP_LS_Triangle::vertices[3] = {
				ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(1.0f, 0.0f,0.0f),glm::vec2(1.0f,1.0f))
			};
			PW_UINT ID_UP_LS_Triangle::indices[3]{
				0,2,1
			};
		// Class Members
			ID_Vertex_Data* ID_UP_LS_Triangle::Vertices() {
				return vertices;
			}
			PW_UINT* ID_UP_LS_Triangle::Indices() {
				return indices;
			}
			const PW_SUINT ID_UP_LS_Triangle::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_UP_LS_Triangle::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_UP_LS_Triangle::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_UP_LS_Triangle::Vertices(),
						ID_UP_LS_Triangle::Vertices_Size(),
						ID_UP_LS_Triangle::Indices(),
						ID_UP_LS_Triangle::Indices_Size()));
				}
			}
			PW_VOID ID_UP_LS_Triangle::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_UP_LS_Triangle::Vertices(),
						ID_UP_LS_Triangle::Vertices_Size(),
						ID_UP_LS_Triangle::Indices(),
						ID_UP_LS_Triangle::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_Square                
		// Static Declarations      
		ID_Vertex_Data ID_Square::vertices[4] = {
			ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
		};
		PW_UINT ID_Square::indices[6]{
			0,2,1,
			0,2,3
		};
		// Class Members
			ID_Vertex_Data* ID_Square::Vertices() {
				return vertices;
			}
			PW_UINT* ID_Square::Indices() {
				return indices;
			}
			const PW_SUINT ID_Square::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_Square::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_Square::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_Square::Vertices(),
						ID_Square::Vertices_Size(),
						ID_Square::Indices(),
						ID_Square::Indices_Size()));
				}
			}
			PW_VOID ID_Square::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_Square::Vertices(),
						ID_Square::Vertices_Size(),
						ID_Square::Indices(),
						ID_Square::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_HAFE_RS_Square        
		// Static Declarations      
			ID_Vertex_Data ID_HAFE_RS_Square::vertices[4] = {
				ID_Vertex_Data(glm::vec3(0.5f,0.0f,0.0f),glm::vec2(0.5f,1.0f)),
				ID_Vertex_Data(glm::vec3(0.5f,-1.0f,0.0f),glm::vec2(0.5f,0.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
			};
			PW_UINT ID_HAFE_RS_Square::indices[6]{
				0,2,1,
				0,2,3
			};
		// Class Members
			ID_Vertex_Data* ID_HAFE_RS_Square::Vertices() {
				return vertices;
			}
			PW_UINT* ID_HAFE_RS_Square::Indices() {
				return indices;
			}
			const PW_SUINT ID_HAFE_RS_Square::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_HAFE_RS_Square::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_HAFE_RS_Square::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_RS_Square::Vertices(),
						ID_HAFE_RS_Square::Vertices_Size(),
						ID_HAFE_RS_Square::Indices(),
						ID_HAFE_RS_Square::Indices_Size()));
				}
			}
			PW_VOID ID_HAFE_RS_Square::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_RS_Square::Vertices(),
						ID_HAFE_RS_Square::Vertices_Size(),
						ID_HAFE_RS_Square::Indices(),
						ID_HAFE_RS_Square::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_HAFE_LS_Square        
		// Static Declarations      
			ID_Vertex_Data ID_HAFE_LS_Square::vertices[4] = {
				ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(0.5f,-1.0f,0.0f),glm::vec2(0.5f,0.0f)),
				ID_Vertex_Data(glm::vec3(0.5f,0.0f,0.0f),glm::vec2(0.5f,1.0f))
			};
			PW_UINT ID_HAFE_LS_Square::indices[6]{
				0,2,1,
				0,2,3
			};
		// Class Members
			ID_Vertex_Data* ID_HAFE_LS_Square::Vertices() {
				return vertices;
			}
			PW_UINT* ID_HAFE_LS_Square::Indices() {
				return indices;
			}
			const PW_SUINT ID_HAFE_LS_Square::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_HAFE_LS_Square::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_HAFE_LS_Square::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_LS_Square::Vertices(),
						ID_HAFE_LS_Square::Vertices_Size(),
						ID_HAFE_LS_Square::Indices(),
						ID_HAFE_LS_Square::Indices_Size()));
				}
			}
			PW_VOID ID_HAFE_LS_Square::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_LS_Square::Vertices(),
						ID_HAFE_LS_Square::Vertices_Size(),
						ID_HAFE_LS_Square::Indices(),
						ID_HAFE_LS_Square::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_HAFE_UP_Square        
		// Static Declarations      
			ID_Vertex_Data ID_HAFE_UP_Square::vertices[4] = {
				ID_Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				ID_Vertex_Data(glm::vec3(0.0f,-0.5f,0.0f),glm::vec2(0.0f,0.5f)),
				ID_Vertex_Data(glm::vec3(1.0f,-0.5f,0.0f),glm::vec2(1.0f,0.5f)),
				ID_Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
			};
			PW_UINT ID_HAFE_UP_Square::indices[6]{
				0,2,1,
				0,2,3
			};
		// Class Members
			ID_Vertex_Data* ID_HAFE_UP_Square::Vertices() {
				return vertices;
			}
			PW_UINT* ID_HAFE_UP_Square::Indices() {
				return indices;
			}
			const PW_SUINT ID_HAFE_UP_Square::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_HAFE_UP_Square::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_HAFE_UP_Square::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_UP_Square::Vertices(),
						ID_HAFE_UP_Square::Vertices_Size(),
						ID_HAFE_UP_Square::Indices(),
						ID_HAFE_UP_Square::Indices_Size()));
				}
			}
			PW_VOID ID_HAFE_UP_Square::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_UP_Square::Vertices(),
						ID_HAFE_UP_Square::Vertices_Size(),
						ID_HAFE_UP_Square::Indices(),
						ID_HAFE_UP_Square::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// ID_HAFE_DOWN_Square      
		// Static Declarations      
			ID_Vertex_Data ID_HAFE_DOWN_Square::vertices[4] = {
				ID_Vertex_Data(glm::vec3(0.0f,-0.5f,0.0f),glm::vec2(0.0f,0.5f)),
				ID_Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
				ID_Vertex_Data(glm::vec3(1.0f,-0.5f,0.0f),glm::vec2(1.0f,0.5f))
			};
			PW_UINT ID_HAFE_DOWN_Square::indices[6]{
				0,2,1,
				0,2,3
			};
		// Class Members
			ID_Vertex_Data* ID_HAFE_DOWN_Square::Vertices() {
				return vertices;
			}
			PW_UINT* ID_HAFE_DOWN_Square::Indices() {
				return indices;
			}
			const PW_SUINT ID_HAFE_DOWN_Square::Vertices_Size() {
				return vertices_size;
			}
			const PW_SUINT ID_HAFE_DOWN_Square::Indices_Size() {
				return indices_size;
			}
			PW_VOID ID_HAFE_DOWN_Square::Handle_Model_Data_NOC(std::shared_ptr<Mesh>& model_mesh) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_DOWN_Square::Vertices(),
						ID_HAFE_DOWN_Square::Vertices_Size(),
						ID_HAFE_DOWN_Square::Indices(),
						ID_HAFE_DOWN_Square::Indices_Size()));
				}
			}
			PW_VOID ID_HAFE_DOWN_Square::Handle_Model_Data_C(std::shared_ptr<Mesh>& model_mesh, glm::vec4 model_color) {
				if (model_mesh == nullptr) {
					model_mesh = PW_SRD_PTR(Mesh)( new Mesh(
						ID_HAFE_DOWN_Square::Vertices(),
						ID_HAFE_DOWN_Square::Vertices_Size(),
						ID_HAFE_DOWN_Square::Indices(),
						ID_HAFE_DOWN_Square::Indices_Size()));
				}
				model_mesh->Change_Color_Data(model_color);
			}
		// End of Class Members
		// IE_Static_Model          
		// Static Declarations      
			PW_VOID(*Static_Model::model_functions_noc[(PW_INT)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh) {
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
			PW_VOID(*Static_Model::model_functions_c[(PW_INT)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color) {
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
			ID_Vertex_Data* Static_Model::model_vertices[(PW_INT)Mesh_Types::TYPE_COUNT - 1]{
				ID_DOWN_RS_Triangle::Vertices(),
				ID_DOWN_LS_Triangle::Vertices(),
				ID_UP_RS_Triangle::Vertices(),
				ID_UP_LS_Triangle::Vertices(),
				ID_Square::Vertices(),
				ID_HAFE_RS_Square::Vertices(),
				ID_HAFE_LS_Square::Vertices(),
				ID_HAFE_UP_Square::Vertices(),
				ID_HAFE_DOWN_Square::Vertices()
			};
			const PW_SUINT Static_Model::model_vertices_count[(PW_INT)Mesh_Types::TYPE_COUNT - 1]{
				ID_DOWN_RS_Triangle::Vertices_Size(),
				ID_DOWN_LS_Triangle::Vertices_Size(),
				ID_UP_RS_Triangle::Vertices_Size(),
				ID_UP_LS_Triangle::Vertices_Size(),
				ID_Square::Vertices_Size(),
				ID_HAFE_RS_Square::Vertices_Size(),
				ID_HAFE_LS_Square::Vertices_Size(),
				ID_HAFE_UP_Square::Vertices_Size(),
				ID_HAFE_DOWN_Square::Vertices_Size()
			};
		// Class Members            
			Static_Model::Static_Model() :
					model_texture(NULL), model_position(NULL), model_rotation(NULL), model_size(NULL),
					model_mesh(nullptr), model_type(Mesh_Types::UNINIT), model_is_colored(false), model_color(NULL),
					model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Static_Model::Static_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size) :
					model_texture(texture), model_position(model_position, 0.0f), model_rotation(model_rotation), model_size(model_size),
					model_mesh(nullptr), model_type(type), model_is_colored(false), model_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
					model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				model_functions_noc[(int)model_type - 1](this->model_mesh);
				model_matrix = Handle_Calculations();
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Static_Model::Static_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec4 model_color) :
					model_texture(texture), model_position(model_position, 0.0f), model_rotation(model_rotation), model_size(model_size),
					model_mesh(nullptr), model_type(type), model_is_colored(true), model_color(model_color),
					model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
				model_matrix = Handle_Calculations();
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Static_Model::Static_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size) :
					model_texture(texture), model_position(model_position, 0.0f), model_rotation(model_rotation), model_size(model_size),
					model_mesh(nullptr), model_type(type), model_is_colored(false), model_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
					model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				model_functions_noc[(int)model_type - 1](this->model_mesh);
				model_mesh->Update_Vertices(mesh_info);
				model_matrix = Handle_Calculations();
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Static_Model::Static_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec4 model_color) :
					model_texture(texture), model_position(model_position, 0.0f), model_rotation(model_rotation), model_size(model_size),
					model_mesh(nullptr), model_type(type), model_is_colored(true), model_color(model_color),
					model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner ? id : ++Model::model_counter) {
				model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
				model_mesh->Update_Vertices(mesh_info);
				model_matrix = Handle_Calculations();
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			PW_VOID Static_Model::Render() {
				Shader::Get_Shader().Use();

				Shader::Get_Shader().Update_Matrices(this->model_matrix, this->model_is_colored);

				this->model_texture->Bind(0);
				this->model_mesh->Draw();
			}
			PW_VOID Static_Model::Delete() {
				if (deleted == false) {
					if (model_mesh != NULL) {
						model_mesh.~shared_ptr();
					}
					model_texture->Delete();
					delete model_texture;
					deleted = true;
					Model::model_counter = Model::model_counter - 1;
				}
			}
			glm::vec3 Static_Model::Position() {
				return model_position;
			}
			glm::vec3& Static_Model::Position_Reference() {
				return model_position;
			}
			Mesh_Types Static_Model::Model_Type() {
				return model_type;
			}
			PW_FLOAT Static_Model::Rotation() {
				return model_rotation;
			}
			glm::vec2 Static_Model::Model_Size() {
				return model_size;
			}
			PW_SRD_PTR(Mesh) Static_Model::Model_Mesh() {
				return model_mesh;
			}
			PW_SRD_PTR(Mesh)& Static_Model::Model_Mesh_Reference() {
				return model_mesh;
			}
			PW_VOID Static_Model::Refresh_Model() {
				this->model_matrix = Handle_Calculations();
			}
			glm::mat4 Static_Model::Handle_Calculations() {
				glm::mat4 model(1.0f);
				PW_FLOAT pos_x = model_position.x;
				PW_FLOAT pos_y = model_position.y;
				PW_FLOAT size_x = model_size.x;
				PW_FLOAT size_y = model_size.y;

				pos_x = ((pos_x / (PW_FLOAT)Engine_Constant::Window_Width()) * 2.0f) - 1.0f;
				pos_y = ((pos_y / (PW_FLOAT)Engine_Constant::Window_Height()) * 2.0f) - 1.0f;

				size_x = size_x / (PW_FLOAT)Engine_Constant::Hafe_Window_Width();
				size_y = size_y / (PW_FLOAT)Engine_Constant::Hafe_Window_Height();

				model = glm::translate(model, glm::vec3(pos_x, pos_y, Engine_Constant::Inverse_Z_Tan()));
				model = glm::rotate(model, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(size_x, size_y, 1.0f));

				return model;
			}
		// End of Class Members
		// IE_Dynamic_Model         
		// Static Declarations      
			PW_VOID(*Dynamic_Model::model_functions_noc[(PW_INT)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh) {
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
			PW_VOID(*Dynamic_Model::model_functions_c[(PW_INT)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color) {
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
			ID_Vertex_Data* Dynamic_Model::model_vertices[(PW_INT)Mesh_Types::TYPE_COUNT - 1]{
				ID_DOWN_RS_Triangle::Vertices(),
				ID_DOWN_LS_Triangle::Vertices(),
				ID_UP_RS_Triangle::Vertices(),
				ID_UP_LS_Triangle::Vertices(),
				ID_Square::Vertices(),
				ID_HAFE_RS_Square::Vertices(),
				ID_HAFE_LS_Square::Vertices(),
				ID_HAFE_UP_Square::Vertices(),
				ID_HAFE_DOWN_Square::Vertices()
			};
			const PW_SUINT Dynamic_Model::model_vertices_count[(PW_INT)Mesh_Types::TYPE_COUNT - 1]{
				ID_DOWN_RS_Triangle::Vertices_Size(),
				ID_DOWN_LS_Triangle::Vertices_Size(),
				ID_UP_RS_Triangle::Vertices_Size(),
				ID_UP_LS_Triangle::Vertices_Size(),
				ID_Square::Vertices_Size(),
				ID_HAFE_RS_Square::Vertices_Size(),
				ID_HAFE_LS_Square::Vertices_Size(),
				ID_HAFE_UP_Square::Vertices_Size(),
				ID_HAFE_DOWN_Square::Vertices_Size()
			};
		// Class Members            
			Dynamic_Model::Dynamic_Model() :
					model_texture(NULL), model_position(NULL), model_last_position(NULL), model_rotation(NULL),
					model_size(NULL), model_mesh(nullptr), model_type(Mesh_Types::UNINIT), model_is_colored(false),
					model_color(NULL), last_body_pos(0.0f), model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner ? id : ++Model::model_counter) {
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Dynamic_Model::Dynamic_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size) :
					model_texture(texture), model_position(model_position, 0.0f), model_last_position(NULL), model_rotation(model_rotation),
					model_size(model_size), model_mesh(nullptr), model_type(type), model_is_colored(false),
					model_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)), last_body_pos(0.0f), model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				if (model_type != Mesh_Types::UNINIT) {
					model_functions_noc[(int)model_type - 1](this->model_mesh);
				}
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Dynamic_Model::Dynamic_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec4 model_color) :
					model_texture(texture), model_position(model_position, 0.0f), model_last_position(NULL), model_rotation(model_rotation),
					model_size(model_size), model_mesh(nullptr), model_type(type), model_is_colored(true),
					model_color(model_color), last_body_pos(0.0f), model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Dynamic_Model::Dynamic_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size) :
					model_texture(texture), model_position(model_position, 0.0f), model_last_position(NULL), model_rotation(model_rotation),
					model_size(model_size), model_mesh(nullptr), model_type(type), model_is_colored(true),
					model_color(0.0f), last_body_pos(0.0f), model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
				model_mesh->Update_Vertices(mesh_info);
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			Dynamic_Model::Dynamic_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec4 model_color) :
					model_texture(texture), model_position(model_position, 0.0f), model_last_position(NULL), model_rotation(model_rotation),
					model_size(model_size), model_mesh(nullptr), model_type(type), model_is_colored(true),
					model_color(model_color), last_body_pos(0.0f), model_matrix(0.0f), deleted(false), id(id <= Model::model_id_assigner && id != 0 ? id : ++Model::model_counter) {
				model_functions_c[(int)model_type - 1](this->model_mesh, this->model_color);
				model_mesh->Update_Vertices(mesh_info);
				// Make sure the total number of models ever does not change for unique id
				if (Model::model_counter > Model::model_id_assigner) {
					Model::model_id_assigner = Model::model_counter;
				}
			}
			PW_VOID Dynamic_Model::Render() {
				Shader::Get_Shader().Use();

				Shader::Get_Shader().Update_Matrices(this->Handle_Calculations(), this->model_is_colored);

				this->model_texture->Bind(0);
				this->model_mesh->Draw();
			}
			PW_VOID Dynamic_Model::Render(
				b2Body* model_body) {

				Shader::Get_Shader().Use();

				Shader::Get_Shader().Update_Matrices(this->Handle_Calculations(model_body), this->model_is_colored);

				this->model_texture->Bind(0);
				this->model_mesh->Draw();
			}
			PW_VOID Dynamic_Model::Delete() {
				if (deleted == false) {
					if (model_mesh != NULL) {
						model_mesh.~shared_ptr();
					}
					model_texture->Delete();
					delete model_texture;
					deleted = true;
					Model::model_counter = Model::model_counter - 1;
				}
			}
			glm::vec3 Dynamic_Model::Position() {
				return model_position;
			}
			glm::vec3& Dynamic_Model::Position_Reference() {
				return model_position;
			}
			glm::vec3 Dynamic_Model::Last_Postition() {
				return model_last_position;
			}
			glm::vec3& Dynamic_Model::Last_Postition_Reference() {
				return model_last_position;
			}
			Mesh_Types Dynamic_Model::Model_Type() {
				return model_type;
			}
			PW_FLOAT Dynamic_Model::Rotation() {
				return model_rotation;
			}
			glm::vec2 Dynamic_Model::Model_Size() {
				return model_size;
			}
			PW_SRD_PTR(Mesh) Dynamic_Model::Model_Mesh() {
				return model_mesh;
			}
			PW_SRD_PTR(Mesh)& Dynamic_Model::Model_Mesh_Reference() {
				return model_mesh;
			}
			PW_VOID Dynamic_Model::Set_Model_Color(
				glm::vec4 new_model_color) {

				model_color = new_model_color;
				model_functions_c[(int)this->model_type - 1](this->model_mesh, this->model_color);
			}
			PW_VOID Dynamic_Model::Update_Position(
				glm::vec2 position) {

				this->model_position.x = position.x;
				this->model_position.y = position.y;
			}
			PW_VOID Dynamic_Model::Update_Position(
				PW_FLOAT x_pos,
				PW_FLOAT y_pos) {

				this->model_position.x = x_pos;
				this->model_position.y = y_pos;
			};
			PW_VOID Dynamic_Model::Set_Body_Pos(
				glm::vec2 body_pos) {

				last_body_pos = body_pos;
			}
			PW_VOID Dynamic_Model::Refresh_Model() {
				model_matrix = Handle_Calculations(true);
			}
			glm::mat4 Dynamic_Model::Handle_Calculations(PW_BOOL dynamic_override) {
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

				model = glm::translate(model, glm::vec3(pos_x, pos_y, Engine_Constant::Inverse_Z_Tan()));
				model = glm::rotate(model, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(size_x, size_y, 1.0f));

				return model;
			}
			glm::mat4 Dynamic_Model::Handle_Calculations(b2Body* model_body) {
				if (model_body != nullptr) {
					model_position.x = model_body->GetPosition().x * 32.0f;
					model_position.y = model_body->GetPosition().y * 32.0f;
				}
					model_matrix = glm::mat4(1.0f);


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

					model_matrix = glm::translate(model_matrix, glm::vec3(pos_x, pos_y, Engine_Constant::Inverse_Z_Tan()));
					model_matrix = glm::rotate(model_matrix, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
					model_matrix = glm::scale(model_matrix, glm::vec3(size_x, size_y, 1.0f));

					return model_matrix;
			}
			glm::mat4 Dynamic_Model::Handle_Calculations() {
				if (model_position != model_last_position) {
					model_matrix = glm::mat4(1.0f);

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

					model_matrix = glm::translate(model_matrix, glm::vec3(pos_x, pos_y, Engine_Constant::Inverse_Z_Tan()));
					model_matrix = glm::rotate(model_matrix, glm::radians(model_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
					model_matrix = glm::scale(model_matrix, glm::vec3(size_x, size_y, 1.0f));

					return model_matrix;
				}
				else {
					return model_matrix;
				}
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////





















/*PW_BOOL Dynamic_Model::Test_Collision(Dynamic_Model& m_model) {


					for (size_t j = 0; j < m_vertices_count; j++) {

						glm::vec2 line_r1s(
							0.0f, // X 
							0.0f  // Y
						);
						if (m_vertices_count == 3) {
							line_r1s = glm::vec2(
								((moveable_model->Position().x + (model_vertices[(int)moveable_model->Model_Type() - 1][0].Vertex_Position().x * moveable_model->Model_Size().x)) +
									(moveable_model->Position().x + (model_vertices[(int)moveable_model->Model_Type() - 1][1].Vertex_Position().x * moveable_model->Model_Size().x)) +
									(moveable_model->Position().x + (model_vertices[(int)moveable_model->Model_Type() - 1][2].Vertex_Position().x * moveable_model->Model_Size().x))) / 3, // X
								((moveable_model->Position().y + (model_vertices[(int)moveable_model->Model_Type() - 1][0].Vertex_Position().y * moveable_model->Model_Size().y)) +
									(moveable_model->Position().y + (model_vertices[(int)moveable_model->Model_Type() - 1][1].Vertex_Position().y * moveable_model->Model_Size().y)) +
									(moveable_model->Position().y +			if (abs(m_model.Position().x - this->Position().x) < 33 && abs(m_model.Position().y - this->Position().y) < 33) {
				Dynamic_Model* moveable_model = &m_model;
				Dynamic_Model* static_model = &*this;

				ID_Vertex_Data* m_vertices = model_vertices[(int)m_model.Model_Type() - 1];
				short unsigned int m_vertices_count = model_vertices_count[(int)m_model.Model_Type() - 1];

				ID_Vertex_Data* s_vertices = model_vertices[(int)this->Model_Type() - 1];
				short unsigned int s_vertices_count = model_vertices_count[(int)this->Model_Type() - 1];

				for (size_t i = 0; i < 2; i++) {
					if (i == 1) {
						moveable_model = &*this;
						static_model = &m_model;

						m_vertices = model_vertices[(int)this->Model_Type() - 1];
						m_vertices_count = model_vertices_count[(int)this->Model_Type() - 1];

						s_vertices = model_vertices[(int)m_model.Model_Type() - 1];
						s_vertices_count = model_vertices_count[(int)m_model.Model_Type() - 1];
					} (model_vertices[(int)moveable_model->Model_Type() - 1][2].Vertex_Position().y * moveable_model->Model_Size().y))) / 3  // Y
							);
						}
						else {
							line_r1s = glm::vec2(
								(moveable_model->Position().x + ((moveable_model->Model_Size().x * (m_vertices[0].Vertex_Position().x + m_vertices[2].Vertex_Position().x)) / 2.0f)), // X
								(moveable_model->Position().y + ((moveable_model->Model_Size().y * (m_vertices[0].Vertex_Position().y + m_vertices[2].Vertex_Position().y)) / 2.0f))  // Y
							);
						}
						glm::vec2 line_r1e(
							moveable_model->Position().x + (m_vertices[j].Vertex_Position().x * m_model.Model_Size().x), // X
							moveable_model->Position().y + (m_vertices[j].Vertex_Position().y * m_model.Model_Size().y)  // Y
						);
						glm::vec2 displacement(0.0f);

						for (size_t k = 0; k < s_vertices_count; k++) {
							glm::vec2 line_r2s(
								static_model->Position().x + (s_vertices[k].Vertex_Position().x * m_model.Model_Size().x), // X
								static_model->Position().y + (s_vertices[k].Vertex_Position().y * m_model.Model_Size().y)  // Y
							);
							glm::vec2 line_r2e(
								static_model->Position().x + (s_vertices[(k + 1) % s_vertices_count].Vertex_Position().x * m_model.Model_Size().x), // X
								static_model->Position().y + (s_vertices[(k + 1) % s_vertices_count].Vertex_Position().y * m_model.Model_Size().y)  // Y
							);

							float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
							float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
							float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

							if (t1 >= 0.0f && t1 < 1.00f && t2 >= 0.0f && t2 < 1.00f) {
								return true;
							}
						}
					}
				}
				return false;
			}
			return false;
		}*/