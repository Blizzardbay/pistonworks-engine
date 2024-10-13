#include "structures\model.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
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
			void ID_Down_RS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Down_RS_Triangle::Vertices(),
						ID_Down_RS_Triangle::Vertices_Size(),
						ID_Down_RS_Triangle::Indices(),
						ID_Down_RS_Triangle::Indices_Size()), false);
				}
			}
			void ID_Down_RS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Down_RS_Triangle::Vertices(),
						ID_Down_RS_Triangle::Vertices_Size(),
						ID_Down_RS_Triangle::Indices(),
						ID_Down_RS_Triangle::Indices_Size()), false);
				}
			}
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
			void ID_Down_LS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Down_LS_Triangle::Vertices(),
						ID_Down_LS_Triangle::Vertices_Size(),
						ID_Down_LS_Triangle::Indices(),
						ID_Down_LS_Triangle::Indices_Size()), false);
				}
			}
			void ID_Down_LS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Down_LS_Triangle::Vertices(),
						ID_Down_LS_Triangle::Vertices_Size(),
						ID_Down_LS_Triangle::Indices(),
						ID_Down_LS_Triangle::Indices_Size()), false);
				}
			}
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
			void ID_Up_RS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Up_RS_Triangle::Vertices(),
						ID_Up_RS_Triangle::Vertices_Size(),
						ID_Up_RS_Triangle::Indices(),
						ID_Up_RS_Triangle::Indices_Size()), false);
				}
			}
			void ID_Up_RS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Up_RS_Triangle::Vertices(),
						ID_Up_RS_Triangle::Vertices_Size(),
						ID_Up_RS_Triangle::Indices(),
						ID_Up_RS_Triangle::Indices_Size()), false);
				}
			}
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
			void ID_Up_LS_Triangle::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Up_LS_Triangle::Vertices(),
						ID_Up_LS_Triangle::Vertices_Size(),
						ID_Up_LS_Triangle::Indices(),
						ID_Up_LS_Triangle::Indices_Size()), false);
				}
			}
			void ID_Up_LS_Triangle::Handle_Model_Data_C(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Up_LS_Triangle::Vertices(),
						ID_Up_LS_Triangle::Vertices_Size(),
						ID_Up_LS_Triangle::Indices(),
						ID_Up_LS_Triangle::Indices_Size()), false);
				}
			}
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
			void ID_Square::Handle_Model_Data_NOC(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Square::Vertices(),
						ID_Square::Vertices_Size(),
						ID_Square::Indices(),
						ID_Square::Indices_Size()), false);
				}
			}
			void ID_Square::Handle_Model_Data_C(st::Mesh*& p_model_mesh) {
				if (p_model_mesh == nullptr) {
					PW_CALL(p_model_mesh = pw::co::Memory::Allocate_Args<Mesh>(
						ID_Square::Vertices(),
						ID_Square::Vertices_Size(),
						ID_Square::Indices(),
						ID_Square::Indices_Size()), false);
				}
			}
		// Model          
		// Static Declarations
			uint64_t st::Model::m_model_counter{ 0 };
			uint64_t st::Model::m_model_id_assigner{ 0 };

			std::map<pw::st::Geometry_Types, pw::st::Mesh*> st::Model::m_geometry_holder_c{};
			std::map<pw::st::Geometry_Types, pw::st::Mesh*> st::Model::m_geometry_holder_noc{};
		// Class Members            
			Model::Model() :
					m_texture{ NULL }, m_position{ NULL }, m_last_position{ std::numeric_limits<float>::quiet_NaN() }, m_rotation{ NULL },
					m_size{ NULL }, m_mesh{ nullptr }, m_type{ Geometry_Types::UNINIT }, m_is_colored{ false },
				m_is_text{ NULL }, m_color{ NULL }, m_matrix{}, m_id{ NULL }, m_render_index{ NULL }, m_model_matrix_index{ NULL }, m_offset{ NULL }, m_last_rotation{ 0.0f },
					m_repeats{ false }, m_attached{ false }, m_fixed_rotation{ false }, m_is_copy{ false }, m_changed{ true } {
			}
			Model::Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float p_rotation, const glm::vec2& p_size, const bool p_repeats, const bool p_fixed_rotation, int32_t p_is_text) :
					m_texture{ p_texture }, m_position{ nullptr },
					m_last_position{ std::numeric_limits<float>::quiet_NaN() }, m_rotation{ p_rotation }, m_size{ p_size }, m_mesh{ nullptr }, m_type{ p_type }, m_is_colored{ false },
					m_is_text{ p_is_text }, m_color{ glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) }, m_matrix{}, m_id{ ++Model::m_model_id_assigner }, m_render_index{ NULL }, m_model_matrix_index{ NULL },
					m_offset{ NULL }, m_last_rotation{ 0.0f },
					m_repeats{ p_repeats }, m_attached{ false }, m_fixed_rotation{ p_fixed_rotation }, m_is_copy{ false }, m_changed{ true } {
				if (p_texture == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Model", L"Invalid Parameter: p_texture was nullptr", ERROR_LINE, __FILEW__, L"Model"));
					return;
				}
				// Allocate after possible nullptr
				PW_CALL(m_position = pw::co::Memory::Allocate_Args<glm::vec2>(p_position), true);

				if (m_repeats == true) {
					st::Mesh::Non_Colored v_non_colored{};
					v_non_colored.m_size = m_size;
					v_non_colored.m_texture_size = m_texture->Size();
					v_non_colored.m_matrix = m_matrix;
					v_non_colored.m_is_text = m_is_text;
					v_non_colored.m_texture_handle = m_texture->Texture_Handle();

					auto v_found = m_geometry_holder_noc.find(m_type);

					if (v_found != m_geometry_holder_noc.end()) {
						m_mesh = v_found->second;

						std::pair<uint32_t, uint32_t> v_temp = m_mesh->Add(v_non_colored);
						m_render_index = v_temp.first;
						m_model_matrix_index = v_temp.second;
					}
				}
				else {
					st::Mesh::Non_Colored v_non_colored{};
					v_non_colored.m_size = glm::vec2(32.0f, 32.0f);
					v_non_colored.m_texture_size = glm::vec2(32.0f, 32.0f);
					v_non_colored.m_matrix = m_matrix;
					v_non_colored.m_is_text = m_is_text;
					v_non_colored.m_texture_handle = m_texture->Texture_Handle();

					auto v_found = m_geometry_holder_noc.find(m_type);

					if (v_found != m_geometry_holder_noc.end()) {
						m_mesh = v_found->second;

						std::pair<uint32_t, uint32_t> v_temp = m_mesh->Add(v_non_colored);
						m_render_index = v_temp.first;
						m_model_matrix_index = v_temp.second;
					}
				}
				
				Model::m_model_counter = Model::m_model_counter + 1;
			}
			Model::Model(const Geometry_Types& p_type, st::Texture* p_texture, const glm::vec2& p_position, const float p_rotation, const glm::vec2& p_size, const glm::vec4& p_color, const bool p_repeats, const bool p_fixed_rotation, int32_t p_is_text) :
					m_texture{ p_texture }, m_position{ nullptr },
					m_last_position{ std::numeric_limits<float>::quiet_NaN() }, m_rotation{ p_rotation }, m_size{ p_size }, m_mesh{ nullptr }, m_type{ p_type }, m_is_colored{ true },
					m_is_text{ p_is_text }, m_color{ p_color }, m_matrix{}, m_id{ ++Model::m_model_id_assigner }, m_render_index{ NULL }, m_model_matrix_index{ NULL }, m_offset{ NULL }, m_last_rotation{ 0.0f },
					m_repeats{ p_repeats }, m_attached{ false }, m_fixed_rotation{ p_fixed_rotation }, m_is_copy{ false }, m_changed{ true } {
				if (p_texture == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Model", L"Invalid Parameter: p_texture was nullptr", ERROR_LINE, __FILEW__, L"Model"));
					return;
				}
				// Allocate after possible nullptr
				PW_CALL(m_position = pw::co::Memory::Allocate_Args<glm::vec2>(p_position), true);

				if (m_repeats == true) {
					st::Mesh::Colored v_colored{};
					v_colored.m_size = m_size;
					v_colored.m_texture_size = m_texture->Size();
					v_colored.m_color = m_color;
					v_colored.m_matrix = m_matrix;
					v_colored.m_is_text = m_is_text;
					v_colored.m_texture_handle = m_texture->Texture_Handle();

					auto v_found = m_geometry_holder_c.find(m_type);

					if (v_found != m_geometry_holder_c.end()) {
						m_mesh = v_found->second;

						std::pair<uint32_t, uint32_t> v_temp = m_mesh->Add(v_colored);
						m_render_index = v_temp.first;
						m_model_matrix_index = v_temp.second;
					}
				}
				else {
					st::Mesh::Colored v_colored{};
					v_colored.m_size = glm::vec2(32.0f, 32.0f);
					v_colored.m_texture_size = glm::vec2(32.0f, 32.0f);
					v_colored.m_color = m_color;
					v_colored.m_matrix = m_matrix;
					v_colored.m_is_text = m_is_text;
					v_colored.m_texture_handle = m_texture->Texture_Handle();

					auto v_found = m_geometry_holder_c.find(m_type);

					if (v_found != m_geometry_holder_c.end()) {
						m_mesh = v_found->second;

						std::pair<uint32_t, uint32_t> v_temp = m_mesh->Add(v_colored);
						m_render_index = v_temp.first;
						m_model_matrix_index = v_temp.second;
					}
				}
				
				Model::m_model_counter = Model::m_model_counter + 1;
			}
			Model& Model::operator=(Model&& p_rhs) noexcept {
				m_texture = p_rhs.m_texture;
				m_position = p_rhs.m_position;
				m_last_position = p_rhs.m_last_position;
				m_size = p_rhs.m_size;
				m_mesh = p_rhs.m_mesh;
				m_type = p_rhs.m_type;
				m_is_colored = p_rhs.m_is_colored;
				m_color = p_rhs.m_color;
				m_matrix = p_rhs.m_matrix;
				m_id = p_rhs.m_id;
				m_offset = p_rhs.m_offset;
				m_last_rotation = p_rhs.m_last_rotation;
				m_repeats = p_rhs.m_repeats;
				m_attached = p_rhs.m_attached;
				m_fixed_rotation = p_rhs.m_fixed_rotation;

				m_is_copy = false;
				p_rhs.m_is_copy = true;

				return *this;
			}
			Model::~Model() {
				if (m_is_copy != true) {
					if (pw::co::Memory::Deallocate<st::Texture>(m_texture) == false) {
						if (m_texture != nullptr) {
							delete m_texture;
							m_texture = nullptr;
						}
					}
					if (m_attached != true) {
						if (pw::co::Memory::Deallocate<glm::vec2>(m_position) == false) {
							if (m_position != nullptr) {
								delete m_position;
								m_position = nullptr;
							}
						}
					}

					Model::m_model_counter = Model::m_model_counter - 1;
				}
				if (m_mesh != nullptr) {
					m_mesh->Remove(m_render_index, m_model_matrix_index);
				}
			}
			void Model::Render(const uint32_t p_layer) {
				if (TRY_LINE m_texture == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Model", L"Invalid Parameter: m_texture was nullptr", ERROR_LINE, __FILEW__, L"Render"));
					return;
				}
				if (TRY_LINE m_mesh == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Model", L"Invalid Parameter: m_mesh was nullptr", ERROR_LINE, __FILEW__, L"Render"));
					return;
				}
				PW_CALL(Update_Matrix(p_layer), true);

				PW_CALL(m_mesh->Render(m_render_index), false);
			}
			void Model::Render(const uint32_t p_layer, b2Body* p_model_body) {
				if (TRY_LINE m_texture == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Model", L"Invalid Parameter: m_texture was nullptr", ERROR_LINE, __FILEW__, L"Render"));
					return;
				}
				if (TRY_LINE m_mesh == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Model", L"Invalid Parameter: m_mesh was nullptr", ERROR_LINE, __FILEW__, L"Render"));
					return;
				}
				PW_CALL(Update_Matrix(p_layer, p_model_body), true);

				PW_CALL(m_mesh->Render(m_render_index), false);
			}
			void Model::Set_Texture(st::Texture* p_new_texture) {
				m_texture = p_new_texture;

				PW_CALL(m_mesh->Change_Texture_Handle(m_render_index, m_texture->Texture_Handle()), false);
			}
			void Model::Set_Model_Color(const glm::vec4& p_new_color) {
				if (m_color != p_new_color) {
					m_color = p_new_color;
					PW_CALL(m_mesh->Change_Color_Data(m_render_index, p_new_color), false);
				}
			}
			void Model::Update_Position(const glm::vec2& p_position) {
				m_changed = true;

				m_position->x = p_position.x;
				m_position->y = p_position.y;
			}
			void Model::Update_Position(const float x_pos, const float y_pos) {
				m_changed = true;

				m_position->x = x_pos;
				m_position->y = y_pos;
			}
			void Model::Set_Position(glm::vec2 p_new_position, bool p_attached) {
				m_changed = true;

				m_attached = p_attached;
				*m_position = p_new_position;
			}
			void Model::Attach_To(glm::vec2* p_position) {
				m_changed = true;
				m_attached = true;

				if (pw::co::Memory::Deallocate<glm::vec2>(m_position) == false) {
					if (m_position != nullptr) {
						delete m_position;
						m_position = nullptr;
					}
				}

				m_position = p_position;
			}
			void Model::Set_Size_X(const float p_size_x) {
				m_changed = true;

				m_size.x = p_size_x;
			}
			void Model::Set_Size_Y(const float p_size_y) {
				m_changed = true;

				m_size.y = p_size_y;
			}
			void Model::Set_Size(const glm::vec2& p_size_px) {
				m_changed = true;

				m_size = p_size_px;
			}
			void Model::Set_Offset(const glm::vec2& p_offset) {
				m_changed = true;

				m_offset = p_offset;
			}
			void Model::Set_Rotation(const float p_new_rotation) {
				m_changed = true;

				m_rotation = p_new_rotation;
			}
			void Model::Set_Rotation(const float p_new_rotation, b2Body* p_body) {
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
			const int32_t& Model::Is_Text() const {
				return m_is_text;
			}
			const bool& Model::Is_Attached() const {
				return m_attached;
			}
			glm::vec2 Model::Position() {
				if (m_position != nullptr) {
					glm::vec2 v_position = *m_position;

					v_position.x = v_position.x + m_offset.x;
					v_position.y = v_position.y + m_offset.y;

					return v_position;
				}
				else {
					return glm::vec2(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
				}
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
				if (m_position != nullptr) {
					return glm::vec2(m_position->x + (m_size.x / 2), m_position->y - (m_size.y / 2));
				}
				else {
					return glm::vec2(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
				}
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
			const uint32_t& Model::Render_Index() {
				return m_render_index;
			}
			void Model::Initialize() {
				// ID_Down_RS_Triangle
				pw::st::Mesh* v_down_rs_triangle_noc{ nullptr };
				pw::st::Mesh* v_down_rs_triangle_c{ nullptr };

				PW_CALL(ID_Down_RS_Triangle::Handle_Model_Data_NOC(v_down_rs_triangle_noc), true);
				PW_CALL(ID_Down_RS_Triangle::Handle_Model_Data_C(v_down_rs_triangle_c), true);

				m_geometry_holder_noc.insert(std::make_pair(Geometry_Types::DOWN_RS_TRIANGLE, v_down_rs_triangle_noc));
				m_geometry_holder_c.insert(std::make_pair(Geometry_Types::DOWN_RS_TRIANGLE, v_down_rs_triangle_c));

				// ID_Down_LS_Triangle
				pw::st::Mesh* v_down_ls_triangle_noc{ nullptr };
				pw::st::Mesh* v_down_ls_triangle_c{ nullptr };

				PW_CALL(ID_Down_LS_Triangle::Handle_Model_Data_NOC(v_down_ls_triangle_noc), true);
				PW_CALL(ID_Down_LS_Triangle::Handle_Model_Data_C(v_down_ls_triangle_c), true);

				m_geometry_holder_noc.insert(std::make_pair(Geometry_Types::DOWN_LS_TRIANGLE, v_down_ls_triangle_noc));
				m_geometry_holder_c.insert(std::make_pair(Geometry_Types::DOWN_LS_TRIANGLE, v_down_ls_triangle_c));

				// ID_Up_RS_Triangle
				pw::st::Mesh* v_up_rs_triangle_noc{ nullptr };
				pw::st::Mesh* v_up_rs_triangle_c{ nullptr };

				PW_CALL(ID_Up_RS_Triangle::Handle_Model_Data_NOC(v_up_rs_triangle_noc), true);
				PW_CALL(ID_Up_RS_Triangle::Handle_Model_Data_C(v_up_rs_triangle_c), true);

				m_geometry_holder_noc.insert(std::make_pair(Geometry_Types::UP_RS_TRIANGLE, v_up_rs_triangle_noc));
				m_geometry_holder_c.insert(std::make_pair(Geometry_Types::UP_RS_TRIANGLE, v_up_rs_triangle_c));

				// ID_Up_LS_Triangle
				pw::st::Mesh* v_up_ls_triangle_noc{ nullptr };
				pw::st::Mesh* v_up_ls_triangle_c{ nullptr };

				PW_CALL(ID_Up_LS_Triangle::Handle_Model_Data_NOC(v_up_ls_triangle_noc), true);
				PW_CALL(ID_Up_LS_Triangle::Handle_Model_Data_C(v_up_ls_triangle_c), true);

				m_geometry_holder_noc.insert(std::make_pair(Geometry_Types::UP_LS_TRIANGLE, v_up_ls_triangle_noc));
				m_geometry_holder_c.insert(std::make_pair(Geometry_Types::UP_LS_TRIANGLE, v_up_ls_triangle_c));

				// ID_Square
				pw::st::Mesh* v_square_noc{ nullptr };
				pw::st::Mesh* v_square_c{ nullptr };

				PW_CALL(ID_Square::Handle_Model_Data_NOC(v_square_noc), true);
				PW_CALL(ID_Square::Handle_Model_Data_C(v_square_c), true);

				m_geometry_holder_noc.insert(std::make_pair(Geometry_Types::SQUARE, v_square_noc));
				m_geometry_holder_c.insert(std::make_pair(Geometry_Types::SQUARE, v_square_c));
			}
			void Model::Release() {
				for (auto i = m_geometry_holder_noc.begin(); i != m_geometry_holder_noc.end(); i++) {
					if (pw::co::Memory::Deallocate<st::Mesh>(i->second) == false) {
						if (i->second != nullptr) {
							delete i->second;
							i->second = nullptr;
						}
					}
				}
				m_geometry_holder_noc.clear();
				for (auto i = m_geometry_holder_c.begin(); i != m_geometry_holder_c.end(); i++) {
					if (pw::co::Memory::Deallocate<st::Mesh>(i->second) == false) {
						if (i->second != nullptr) {
							delete i->second;
							i->second = nullptr;
						}
					}
				}
				m_geometry_holder_c.clear();
			}
			void Model::Draw() {
				for (auto i = m_geometry_holder_noc.begin(); i != m_geometry_holder_noc.end(); i++) {
					PW_CALL(i->second->Draw(), true);
				}
				for (auto i = m_geometry_holder_c.begin(); i != m_geometry_holder_c.end(); i++) {
					PW_CALL(i->second->Draw(), true);
				}
			}
			void Model::Draw_Transparent() {
				for (auto i = m_geometry_holder_noc.begin(); i != m_geometry_holder_noc.end(); i++) {
					PW_CALL(i->second->Draw_Transparent(), true);
				}
				for (auto i = m_geometry_holder_c.begin(); i != m_geometry_holder_c.end(); i++) {
					PW_CALL(i->second->Draw_Transparent(), true);
				}
			}
			void Model::Update_Matrix(const uint32_t p_layer) {
				if (m_changed == true || m_offset.y != 0.0f || m_offset.x != 0.0f) {
					m_matrix = glm::mat4(1.0f);

					m_last_position.x = m_position->x;
					m_last_position.y = m_position->y;

					m_last_rotation = m_rotation;

					glm::vec2 v_tile_center = glm::vec2(m_position->x + m_offset.x + (m_size.x / 2), m_position->y + m_offset.y - (m_size.y / 2));

					glm::vec2 v_model_difference = glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_tile_center;
					
					glm::vec2 v_result = glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_model_difference;
					// If the rotation is 0 then no need to glm::rotate
					if (m_rotation != 0.0f) {
						// Since we are not re-translating a translated matrix theres no need to multiply using glm::translate
						m_matrix[3].x = v_result.x;
						m_matrix[3].y = v_result.y;
						m_matrix[3].z = TO_FLOAT(p_layer);

						m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

						// Since we are not re-sizing a sized matrix theres no need to multiply using glm::scale
						m_matrix[0] = m_matrix[0] * m_size.x;
						m_matrix[1] = m_matrix[1] * m_size.y;
						m_matrix[2] = m_matrix[2] * 0.0f;
					}
					else {
						// Since we are not re-translating a translated matrix theres no need to multiply using glm::translate
						m_matrix[3].x = v_result.x;
						m_matrix[3].y = v_result.y;
						m_matrix[3].z = TO_FLOAT(p_layer);

						// Since we are not re-sizing a sized matrix theres no need to multiply using glm::scale
						// And since there is no rotation, theres no need to multiply vector-wise
						m_matrix[0].x = m_size.x;
						m_matrix[1].y = m_size.y;
						m_matrix[2].z = 0.0f;
					}

					PW_CALL(m_mesh->Change_Matrix_Data(m_render_index, m_model_matrix_index, &m_matrix), true);
					
					m_changed = false;
				}
			}
			void Model::Update_Matrix(const uint32_t p_layer, b2Body*& p_model_body) {
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

						m_matrix = glm::translate(m_matrix, glm::vec3(glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_model_difference, p_layer));

						if (m_rotation != 0.0f) {
							m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
						}

						m_matrix = glm::scale(m_matrix, glm::vec3(m_size.x, m_size.y, 0.0f));

						PW_CALL(m_mesh->Change_Matrix_Data(m_render_index, m_model_matrix_index, &m_matrix), true);
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

						m_matrix = glm::translate(m_matrix, glm::vec3(glm::vec2(m_position->x + m_offset.x, m_position->y + m_offset.y) - v_model_difference, p_layer));

						if (m_rotation != 0.0f) {
							m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
						}

						m_matrix = glm::scale(m_matrix, glm::vec3(m_size.x, m_size.y, 0.0f));

						PW_CALL(m_mesh->Change_Matrix_Data(m_render_index, m_model_matrix_index, &m_matrix), true);
					}
				}
			}
	ST_NAMESPACE_END
PW_NAMESPACE_END