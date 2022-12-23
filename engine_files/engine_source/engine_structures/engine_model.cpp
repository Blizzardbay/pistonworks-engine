#include "engine_structures\engine_model.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// ID_Down_RS_Triangle   
		// Static Declarations
			Vertex_Data ID_Down_RS_Triangle::m_vertices[3] {
				Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
				Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
			};
			uint32_t ID_Down_RS_Triangle::m_indices[3] {
				0,2,1
			};
		// Class Members
			Vertex_Data* ID_Down_RS_Triangle::Vertices() {
				return m_vertices;
			}
			const uint32_t* ID_Down_RS_Triangle::Indices() {
				return m_indices;
			}
			const uint16_t& ID_Down_RS_Triangle::Vertices_Size() {
				return m_vertices_size;
			}
			const uint16_t& ID_Down_RS_Triangle::Indices_Size() {
				return m_indices_size;
			}
			void ID_Down_RS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Down_RS_Triangle::Vertices(),
							ID_Down_RS_Triangle::Vertices_Size(),
							ID_Down_RS_Triangle::Indices(),
							ID_Down_RS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void ID_Down_RS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Down_RS_Triangle::Vertices(),
							ID_Down_RS_Triangle::Vertices_Size(),
							ID_Down_RS_Triangle::Indices(),
							ID_Down_RS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
					p_model_mesh->Change_Color_Data(p_model_color);
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
		// End of Class Members
		// ID_Down_LS_Triangle 
		// Static Declarations      
			Vertex_Data ID_Down_LS_Triangle::m_vertices[3] {
				Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
			};
			uint32_t ID_Down_LS_Triangle::m_indices[3] {
				0,2,1
			};
		// Class Members
			Vertex_Data* ID_Down_LS_Triangle::Vertices() {
				return m_vertices;
			}
			const uint32_t* ID_Down_LS_Triangle::Indices() {
				return m_indices;
			}
			const uint16_t& ID_Down_LS_Triangle::Vertices_Size() {
				return m_vertices_size;
			}
			const uint16_t& ID_Down_LS_Triangle::Indices_Size() {
				return m_indices_size;
			}
			void ID_Down_LS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Down_LS_Triangle::Vertices(),
							ID_Down_LS_Triangle::Vertices_Size(),
							ID_Down_LS_Triangle::Indices(),
							ID_Down_LS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void ID_Down_LS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Down_LS_Triangle::Vertices(),
							ID_Down_LS_Triangle::Vertices_Size(),
							ID_Down_LS_Triangle::Indices(),
							ID_Down_LS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
					p_model_mesh->Change_Color_Data(p_model_color);
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
		// End of Class Members
		// ID_Up_RS_Triangle       
		// Static Declarations     
			Vertex_Data ID_Up_RS_Triangle::m_vertices[3] {
				Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f)),
				Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f))
			};
			uint32_t ID_Up_RS_Triangle::m_indices[3] {
				0,2,1
			};
		// Class Members
			Vertex_Data* ID_Up_RS_Triangle::Vertices() {
				return m_vertices;
			}
			const uint32_t* ID_Up_RS_Triangle::Indices() {
				return m_indices;
			}
			const uint16_t& ID_Up_RS_Triangle::Vertices_Size() {
				return m_vertices_size;
			}
			const uint16_t& ID_Up_RS_Triangle::Indices_Size() {
				return m_indices_size;
			}
			void ID_Up_RS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Up_RS_Triangle::Vertices(),
							ID_Up_RS_Triangle::Vertices_Size(),
							ID_Up_RS_Triangle::Indices(),
							ID_Up_RS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void ID_Up_RS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Up_RS_Triangle::Vertices(),
							ID_Up_RS_Triangle::Vertices_Size(),
							ID_Up_RS_Triangle::Indices(),
							ID_Up_RS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
					p_model_mesh->Change_Color_Data(p_model_color);
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
		// End of Class Members
		// ID_Up_LS_Triangle        
		// Static Declarations      
			Vertex_Data ID_Up_LS_Triangle::m_vertices[3] {
				Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
				Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
				Vertex_Data(glm::vec3(1.0f, 0.0f,0.0f),glm::vec2(1.0f,1.0f))
			};
			uint32_t ID_Up_LS_Triangle::m_indices[3] {
				0,2,1
			};
		// Class Members
			Vertex_Data* ID_Up_LS_Triangle::Vertices() {
				return m_vertices;
			}
			const uint32_t* ID_Up_LS_Triangle::Indices() {
				return m_indices;
			}
			const uint16_t& ID_Up_LS_Triangle::Vertices_Size() {
				return m_vertices_size;
			}
			const uint16_t& ID_Up_LS_Triangle::Indices_Size() {
				return m_indices_size;
			}
			void ID_Up_LS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Up_LS_Triangle::Vertices(),
							ID_Up_LS_Triangle::Vertices_Size(),
							ID_Up_LS_Triangle::Indices(),
							ID_Up_LS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void ID_Up_LS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Up_LS_Triangle::Vertices(),
							ID_Up_LS_Triangle::Vertices_Size(),
							ID_Up_LS_Triangle::Indices(),
							ID_Up_LS_Triangle::Indices_Size(), p_size, p_texture_size);
					}
					p_model_mesh->Change_Color_Data(p_model_color);
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
		// End of Class Members
		// ID_Square                
		// Static Declarations      
		Vertex_Data ID_Square::m_vertices[4] {
			Vertex_Data(glm::vec3(0.0f,0.0f,0.0f),glm::vec2(0.0f,1.0f)),
			Vertex_Data(glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.0f,0.0f)),
			Vertex_Data(glm::vec3(1.0f,-1.0f,0.0f),glm::vec2(1.0f,0.0f)),
			Vertex_Data(glm::vec3(1.0f,0.0f,0.0f),glm::vec2(1.0f,1.0f))
		};
		uint32_t ID_Square::m_indices[6] {
			0,2,1,
			0,2,3
		};
		// Class Members
			Vertex_Data* ID_Square::Vertices() {
				return m_vertices;
			}
			const uint32_t* ID_Square::Indices() {
				return m_indices;
			}
			const uint16_t& ID_Square::Vertices_Size() {
				return m_vertices_size;
			}
			const uint16_t& ID_Square::Indices_Size() {
				return m_indices_size;
			}
			void ID_Square::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Square::Vertices(),
							ID_Square::Vertices_Size(),
							ID_Square::Indices(),
							ID_Square::Indices_Size(), p_size, p_texture_size);
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			void ID_Square::Handle_Model_Data_C(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				try {
					if (p_model_mesh == nullptr) {
						p_model_mesh = pw::Engine_Memory::Allocate<Mesh, bool>(
							ID_Square::Vertices(),
							ID_Square::Vertices_Size(),
							ID_Square::Indices(),
							ID_Square::Indices_Size(), p_size, p_texture_size);
					}
					p_model_mesh->Change_Color_Data(p_model_color);
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
		// End of Class Members
		// Model          
		// Static Declarations
			uint64_t st::Model::m_model_counter{ 0 };
			uint64_t st::Model::m_model_id_assigner{ 0 };

			void(*st::Model::model_functions_noc[(int32_t)Geometry_Types::TYPE_COUNT - 1])(st::Mesh*& p_model_mesh, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				ID_Down_RS_Triangle::Handle_Model_Data_NOC,
					ID_Down_LS_Triangle::Handle_Model_Data_NOC,
					ID_Up_RS_Triangle::Handle_Model_Data_NOC,
					ID_Up_LS_Triangle::Handle_Model_Data_NOC,
					ID_Square::Handle_Model_Data_NOC
			};
			void(*st::Model::model_functions_c[(int32_t)Geometry_Types::TYPE_COUNT - 1])(st::Mesh*& p_model_mesh, const glm::vec4& p_model_color, const glm::vec2& p_size, const glm::vec2& p_texture_size) {
				ID_Down_RS_Triangle::Handle_Model_Data_C,
					ID_Down_LS_Triangle::Handle_Model_Data_C,
					ID_Up_RS_Triangle::Handle_Model_Data_C,
					ID_Up_LS_Triangle::Handle_Model_Data_C,
					ID_Square::Handle_Model_Data_C
			};
			const Vertex_Data* st::Model::model_vertices[(int32_t)Geometry_Types::TYPE_COUNT - 1]{
					ID_Down_RS_Triangle::Vertices(),
					ID_Down_LS_Triangle::Vertices(),
					ID_Up_RS_Triangle::Vertices(),
					ID_Up_LS_Triangle::Vertices(),
					ID_Square::Vertices()
			};
			const uint16_t st::Model::model_vertices_count[(int32_t)Geometry_Types::TYPE_COUNT - 1]{
					ID_Down_RS_Triangle::Vertices_Size(),
					ID_Down_LS_Triangle::Vertices_Size(),
					ID_Up_RS_Triangle::Vertices_Size(),
					ID_Up_LS_Triangle::Vertices_Size(),
					ID_Square::Vertices_Size()
			};
		// Class Members            
			Model::Model() :
					m_texture{ NULL }, m_position{ NULL }, m_last_position{ std::numeric_limits<float>::quiet_NaN() }, m_rotation{ NULL },
					m_size{ NULL }, m_mesh{ nullptr }, m_type{ Geometry_Types::UNINIT }, m_is_colored{ false },
					m_color{ NULL }, m_matrix{}, m_id{ 0 }, m_offset{ NULL }, m_last_rotation{ 0.0f },
					m_repeats{ false }, m_attached{ false }, m_fixed_rotation{ false } {
			}
			Model::Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float& p_rotation, const glm::vec2& p_size, const bool& p_repeats, const bool& p_fixed_rotation) :
					m_texture{ p_texture }, m_position{ pw::Engine_Memory::Allocate<glm::vec2, bool>(p_position) },
					m_last_position{ std::numeric_limits<float>::quiet_NaN() }, m_rotation{ p_rotation }, m_size{ p_size }, m_mesh{ nullptr }, m_type{ p_type }, m_is_colored{ false },
					m_color{ glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) }, m_matrix{}, m_id{ ++Model::m_model_id_assigner },
					m_offset{ NULL }, m_last_rotation{ 0.0f },
					m_repeats{ p_repeats }, m_attached{ false }, m_fixed_rotation{ p_fixed_rotation } {
				if (m_repeats == true) {
					model_functions_noc[(int)m_type - 1](m_mesh, m_size, m_texture->Size());
				}
				else {
					model_functions_noc[(int)m_type - 1](m_mesh, glm::vec2(32.0f, 32.0f), glm::vec2(32.0f, 32.0f));
				}
				
				Model::m_model_counter = Model::m_model_counter + 1;
			}
			Model::Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float& p_rotation, const glm::vec2& p_size, const glm::vec4& p_color, const bool& p_repeats, const bool& p_fixed_rotation) :
					m_texture{ p_texture }, m_position{ pw::Engine_Memory::Allocate<glm::vec2, bool>(p_position) },
					m_last_position{ std::numeric_limits<float>::quiet_NaN() }, m_rotation{ p_rotation }, m_size{ p_size }, m_mesh{ nullptr }, m_type{ p_type }, m_is_colored{ true },
					m_color{ p_color }, m_matrix{}, m_id{ ++Model::m_model_id_assigner }, m_offset{ NULL }, m_last_rotation{ 0.0f },
					m_repeats{ p_repeats }, m_attached{ false }, m_fixed_rotation{ p_fixed_rotation } {
				if (m_repeats == true) {
					model_functions_c[(int)m_type - 1](m_mesh, m_color, m_size, m_texture->Size());
				}
				else {
					model_functions_c[(int)m_type - 1](m_mesh, m_color, glm::vec2(32.0f, 32.0f), glm::vec2(32.0f, 32.0f));
				}
				
				Model::m_model_counter = Model::m_model_counter + 1;
			}
			Model Model::operator=(const Model& p_other) {
				Model v_copy;
				v_copy.m_texture = p_other.m_texture;
				v_copy.m_position = p_other.m_position;
				v_copy.m_last_position = p_other.m_last_position;
				v_copy.m_rotation = p_other.m_rotation;
				v_copy.m_size = p_other.m_size;
				v_copy.m_mesh = p_other.m_mesh;
				v_copy.m_type = p_other.m_type;
				v_copy.m_is_colored = p_other.m_is_colored;
				v_copy.m_color = p_other.m_color;
				v_copy.m_matrix = p_other.m_matrix;
				v_copy.m_id = p_other.m_id;
				v_copy.m_offset = p_other.m_offset;
				v_copy.m_last_rotation = p_other.m_last_rotation;
				v_copy.m_attached = p_other.m_attached;

				return v_copy;
			}
			Model::~Model() {
				if (pw::Engine_Memory::Deallocate<st::Texture>(m_texture) == false) {
					if (m_texture != nullptr) {
						delete m_texture;
						m_texture = nullptr;
					}
				}
				if (m_attached != true) {
					if (pw::Engine_Memory::Deallocate<glm::vec2>(m_position) == false) {
						if (m_position != nullptr) {
							delete m_position;
							m_position = nullptr;
						}
					}
				}
				if (pw::Engine_Memory::Deallocate<st::Mesh>(m_mesh) == false) {
					if (m_mesh != nullptr) {
						delete m_mesh;
						m_mesh = nullptr;
					}
				}

				Model::m_model_counter = Model::m_model_counter - 1;
			}
			void Model::Render(const int32_t& p_is_text) {
				try {
					if (TRY_LINE m_texture == nullptr) {
						throw pw::er::Warning_Error(L"Model", L"m_texture was nullptr", EXCEPTION_LINE, __FILEW__, L"Render");
					}
					if (TRY_LINE m_mesh == nullptr) {
						throw pw::er::Warning_Error(L"Model", L"m_mesh was nullptr", EXCEPTION_LINE, __FILEW__, L"Render");
					}
					Update_Matrix();

					st::Dynamic_Shader::Update_Matrices(m_matrix, m_is_colored, p_is_text);

					m_texture->Bind(0);
					m_mesh->Draw();
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Model::Render(b2Body* p_model_body, const int32_t& p_is_text) {
				try {
					if (TRY_LINE m_texture == nullptr) {
						throw pw::er::Warning_Error(L"Model", L"m_texture was nullptr", EXCEPTION_LINE, __FILEW__, L"Render");
					}
					if (TRY_LINE m_mesh == nullptr) {
						throw pw::er::Warning_Error(L"Model", L"m_mesh was nullptr", EXCEPTION_LINE, __FILEW__, L"Render");
					}
					Update_Matrix(p_model_body);

					st::Dynamic_Shader::Update_Matrices(m_matrix, m_is_colored, p_is_text);

					m_texture->Bind(0);
					m_mesh->Draw();
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Model::Set_Texture(st::Texture* p_new_texture) {
				m_texture = p_new_texture;
			}
			void Model::Set_Model_Color(const glm::vec4& p_new_color) {
				if (m_color != p_new_color) {
					m_color = p_new_color;
					if (m_repeats == true) {
						model_functions_c[(int)m_type - 1](m_mesh, m_color, m_size, m_texture->Size());
					}
					else {
						model_functions_c[(int)m_type - 1](m_mesh, m_color, glm::vec2(32.0f, 32.0f), glm::vec2(32.0f, 32.0f));
					}
				}
			}
			void Model::Update_Position(const glm::vec2& p_position) {
				m_position->x = p_position.x;
				m_position->y = p_position.y;
			}
			void Model::Update_Position(const float& x_pos, const float& y_pos) {
				m_position->x = x_pos;
				m_position->y = y_pos;
			}
			void Model::Set_Position(glm::vec2 p_new_position, bool p_attached) {
				m_attached = p_attached;
				*m_position = p_new_position;
			}
			void Model::Attach_To(glm::vec2* p_position) {
				m_attached = true;

				if (pw::Engine_Memory::Deallocate<glm::vec2>(m_position) == false) {
					if (m_position != nullptr) {
						delete m_position;
						m_position = nullptr;
					}
				}

				m_position = p_position;
			}
			void Model::Set_Size_X(const float& p_size_x) {
				m_size.x = p_size_x;
			}
			void Model::Set_Size_Y(const float& p_size_y) {
				m_size.x = p_size_y;
			}
			void Model::Set_Size(const glm::vec2& p_size_px) {
				m_size = p_size_px;
			}
			void Model::Set_Offset(const glm::vec2& p_offset) {
				m_offset = p_offset;
			}
			void Model::Set_Rotation(const float& p_new_rotation) {
				m_rotation = p_new_rotation;
			}
			void Model::Set_Rotation(const float& p_new_rotation, b2Body* p_body) {
				if (p_body != nullptr) {
					p_body->SetTransform(p_body->GetTransform().p, glm::radians(p_new_rotation));
				}
				m_rotation = p_new_rotation;
			}
			const Geometry_Types& Model::Type() const {
				return m_type;
			}
			st::Mesh* Model::Mesh() const {
				return m_mesh;
			}
			st::Texture* Model::Texture() const {
				return m_texture;
			}
			const glm::vec4& Model::Color() const {
				return m_color;
			}
			const int32_t& Model::Is_Colored() const {
				return m_is_colored;
			}
			glm::vec2 Model::Position() {
				glm::vec2 v_position = *m_position;

				v_position.x = v_position.x + m_offset.x;
				v_position.y = v_position.y + m_offset.y;

				return v_position;
			}
			glm::vec2* Model::Position_Reference() {
				return m_position;
			}
			const glm::vec2& Model::Last_Postition() const {
				return m_last_position;
			}
			const glm::vec2& Model::Size() const {
				return m_size;
			}
			const glm::vec2& Model::Offset() const {
				return m_offset;
			}
			const float& Model::Rotation() const {
				return m_rotation;
			}
			const float& Model::Last_Rotation() const {
				return m_last_rotation;
			}
			const uint64_t& Model::Id() {
				return m_id;
			}
			glm::vec2 Model::Tile_Center() {
				return glm::vec2(m_position->x + (m_size.x / 2), m_position->y - (m_size.y / 2));
			}
			glm::vec2 Model::Calculate_Center() {
				// The general formula for any of the engine shapes is
				// x , y = (X1 + X2... Xn) / n , (Y1 + Y2... Yn) / n
				float v_center_x_position = 0;
				float v_center_y_position = 0;
				for (uint16_t i = 0; i < m_mesh->Vertex_Count(); i++) {
					v_center_x_position = v_center_x_position +
						// Convert to pixel coords
						(m_position->x + m_offset.x + (m_mesh->Vertices()[i].Vertex_Position().x * m_size.x));
					v_center_y_position = v_center_y_position +
						// Convert to pixel coords
						(m_position->y + m_offset.y + (m_mesh->Vertices()[i].Vertex_Position().y * m_size.y));
				}
				// Divide by n
				v_center_x_position = (v_center_x_position / m_mesh->Vertex_Count());
				v_center_y_position = (v_center_y_position / m_mesh->Vertex_Count());

				return glm::vec2(v_center_x_position, v_center_y_position);
			}
			void Model::Update_Matrix() {
				if (*m_position != m_last_position || m_rotation != m_last_rotation || m_offset.y != 0.0f || m_offset.x != 0.0f) {
					m_matrix = glm::mat4(1.0f);

					m_last_position.x = m_position->x;
					m_last_position.y = m_position->y;

					m_last_rotation = m_rotation;

					glm::vec2 v_tile_center = glm::vec2(m_position->x + m_offset.x + (m_size.x / 2), m_position->y + m_offset.y - (m_size.y / 2));

					glm::vec2 v_model_difference = glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_tile_center;

					m_matrix = glm::translate(m_matrix, glm::vec3(glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_model_difference, cm::Engine_Constant::Inverse_Z_Tan()));

					m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

					m_matrix = glm::scale(m_matrix, glm::vec3(m_size.x, m_size.y, 0.0f));
				}
			}
			void Model::Update_Matrix(b2Body*& p_model_body) {
				if (p_model_body != nullptr) {
					if (m_attached != true) {
						glm::vec2 v_model_center_position = Calculate_Center();

						m_position->x = m_position->x + ((p_model_body->GetTransform().p.x * 32.0f) - v_model_center_position.x);
						m_position->y = m_position->y + ((p_model_body->GetTransform().p.y * 32.0f) - v_model_center_position.y);

						if (m_fixed_rotation != true) {
							m_rotation = glm::degrees(p_model_body->GetTransform().q.GetAngle());
						}

						m_matrix = glm::mat4(1.0f);

						m_last_position.x = m_position->x;
						m_last_position.y = m_position->y;

						m_last_rotation = m_rotation;

						glm::vec2 v_tile_center = glm::vec2(m_position->x + m_offset.x + (m_size.x / 2), m_position->y + m_offset.y - (m_size.y / 2));

						glm::vec2 v_model_difference = glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_tile_center;

						m_matrix = glm::translate(m_matrix, glm::vec3(glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_model_difference, cm::Engine_Constant::Inverse_Z_Tan()));

						m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

						m_matrix = glm::scale(m_matrix, glm::vec3(m_size.x, m_size.y, 0.0f));
					}
					else {
						glm::vec2 v_model_center_position = Calculate_Center();

						m_matrix = glm::mat4(1.0f);

						p_model_body->SetTransform(b2Vec2(v_model_center_position.x / 32.0f, v_model_center_position.y / 32.0f), glm::radians(m_rotation));

						m_last_position.x = m_position->x;
						m_last_position.y = m_position->y;

						m_last_rotation = m_rotation;

						glm::vec2 v_tile_center = glm::vec2(m_position->x + m_offset.x + (m_size.x / 2), m_position->y + m_offset.y - (m_size.y / 2));

						glm::vec2 v_model_difference = glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_tile_center;

						m_matrix = glm::translate(m_matrix, glm::vec3(glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_model_difference, cm::Engine_Constant::Inverse_Z_Tan()));

						m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

						m_matrix = glm::scale(m_matrix, glm::vec3(m_size.x, m_size.y, 0.0f));
					}
				}
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////