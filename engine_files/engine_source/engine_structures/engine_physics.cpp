#include "engine_structures\engine_physics.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Physics_Object          
		// Static Declarations     
		// Class Members
			Physics_Object::Physics_Object(st::Model* p_model, const b2BodyType& p_type, b2World* p_world, const bool& p_is_fixed, const float& p_friction, const float& p_restitution, const float& p_density, const Object_Type& p_polygon, const bool& p_is_sensor) :
					m_body{},
					m_shape_vertices{ pw::Engine_Memory::Allocate<b2Vec2>(b2Vec2(), p_model->Mesh()->Vertex_Count()) },
					m_model_size{}, m_current_fixture{ nullptr },
					m_friction{ p_friction }, m_restitution{ p_restitution }, m_density{ p_density },
					m_vertex_count{ p_model->Mesh()->Vertex_Count() }, m_body_type{ p_polygon } {
				b2BodyDef v_body_def{};
				// Create m_body def
				v_body_def.fixedRotation = p_is_fixed;
				v_body_def.type = p_type;
				glm::vec2 v_model_position = p_model->Calculate_Center();
				v_body_def.position.Set(v_model_position.x / 32.0f, v_model_position.y / 32.0f);
				v_body_def.angle = glm::radians(p_model->Rotation());

				m_model_size.Set(p_model->Size().x, p_model->Size().y);
				// Add m_body def to m_world
				m_body = p_world->CreateBody(&v_body_def);

				switch (p_polygon) {
					case Object_Type::POLYGON: {
						b2PolygonShape v_shape{};

						// Fill in the shape's vertices
						for (size_t i = 0; i < p_model->Mesh()->Vertex_Count(); i++) {
							m_shape_vertices[i].Set((p_model->Mesh()->Vertices()[i].Vertex_Position().x - 0.5f) * m_model_size.x / 32.0f,
								(p_model->Mesh()->Vertices()[i].Vertex_Position().y + 0.5f) * m_model_size.y / 32.0f);
						}
						// Create shape
						v_shape.Set(m_shape_vertices, p_model->Mesh()->Vertex_Count());

						if (TRY_LINE !v_shape.Validate()) {
							throw pw::er::Warning_Error(L"Physics_Object", L"shape is not valid", EXCEPTION_LINE, __FILEW__, L"Physics_Object");
						}

						b2FixtureDef v_fixture{};

						v_fixture.isSensor = p_is_sensor;
						// Check for static type
						if (p_type == b2BodyType::b2_staticBody) {
							if (p_friction != -1.0f) {
								v_fixture.friction = p_friction;
							}
							if (p_friction != -1.0f) {
								v_fixture.restitution = p_restitution;
							}
							if (p_friction != -1.0f) {
								v_fixture.density = p_density;
							}
							// Create the fixture for the m_body
							v_fixture.shape = &v_shape;
							m_current_fixture = m_body->CreateFixture(&v_fixture);
						}
						else {
							// Create the fixture for the m_body
							// Dynamic / Kinematic
							v_fixture.friction = p_friction;
							v_fixture.restitution = p_restitution;
							v_fixture.density = p_density;
							v_fixture.shape = &v_shape;
							m_current_fixture = m_body->CreateFixture(&v_fixture);
						}
						break;
					}
					case Object_Type::CIRCLE: {
						b2CircleShape v_shape{};

						v_shape.m_radius = ((m_model_size.x + m_model_size.y) / 4) / 32.0f;

						b2FixtureDef v_fixture{};

						v_fixture.isSensor = p_is_sensor;
						// Check for static type
						if (p_type == b2BodyType::b2_staticBody) {
							if (p_friction != -1.0f) {
								v_fixture.friction = p_friction;
							}
							if (p_friction != -1.0f) {
								v_fixture.restitution = p_restitution;
							}
							if (p_friction != -1.0f) {
								v_fixture.density = p_density;
							}
							// Create the fixture for the m_body
							v_fixture.shape = &v_shape;
							m_current_fixture = m_body->CreateFixture(&v_fixture);
						}
						else {
							// Create the fixture for the m_body
							// Dynamic / Kinematic
							v_fixture.friction = p_friction;
							v_fixture.restitution = p_restitution;
							v_fixture.density = p_density;
							v_fixture.shape = &v_shape;
							m_current_fixture = m_body->CreateFixture(&v_fixture);
						}
						break;
					}
					default: {
						break;
					}
				}
			}
			Physics_Object::~Physics_Object() {
				if (pw::Engine_Memory::Deallocate<b2Vec2>(m_shape_vertices) == false) {
					if (m_shape_vertices != nullptr) {
						delete m_shape_vertices;
						m_shape_vertices = nullptr;
					}
				}
			}
			int32_t Physics_Object::X_Pixels_Position(const int32_t& p_scale_factor) {
				return static_cast<int32_t>(m_body->GetPosition().x * p_scale_factor);
			}
			int32_t Physics_Object::Y_Pixels_Position(const int32_t& p_scale_factor) {
				return static_cast<int32_t>(m_body->GetPosition().y * p_scale_factor);
			}
			b2Body* Physics_Object::Body() {
				return m_body;
			}
			const b2Vec2& Physics_Object::Size() {
				return m_model_size;
			}
			void Physics_Object::Set_Size_Px(const b2Vec2& p_size_px) {
				m_model_size = p_size_px;

				switch (m_body_type) {
					case Object_Type::POLYGON: {
						b2PolygonShape v_shape{};

						// Fill in the shape's vertices
						for (size_t i = 0; i < m_vertex_count; i++) {
							m_shape_vertices[i].Set((m_shape_vertices[i].x - 0.5f) * m_model_size.x / 32.0f,
								(m_shape_vertices[i].y + 0.5f) * m_model_size.y / 32.0f);
						}
						// Create shape
						v_shape.Set(m_shape_vertices, m_vertex_count);

						if (TRY_LINE !v_shape.Validate()) {
							throw pw::er::Warning_Error(L"Physics_Object", L"shape is not valid", EXCEPTION_LINE, __FILEW__, L"Physics_Object");
						}
						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					case Object_Type::CIRCLE: {
						b2CircleShape v_shape{};

						v_shape.m_radius = ((m_model_size.x + m_model_size.y) / 4) / 32.0f;
						
						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					default: {
						break;
					}
				}
			}
			void Physics_Object::Set_Size_M(const b2Vec2& p_size_m) {
				m_model_size = p_size_m;

				m_model_size.x = m_model_size.x * 32.0f;
				m_model_size.y = m_model_size.y * 32.0f;

				switch (m_body_type) {
					case Object_Type::POLYGON: {
						b2PolygonShape v_shape{};

						// Fill in the shape's vertices
						for (size_t i = 0; i < m_vertex_count; i++) {
							m_shape_vertices[i].Set((m_shape_vertices[i].x - 0.5f) * m_model_size.x / 32.0f,
								(m_shape_vertices[i].y + 0.5f) * m_model_size.y / 32.0f);
						}
						// Create shape
						v_shape.Set(m_shape_vertices, m_vertex_count);

						if (TRY_LINE !v_shape.Validate()) {
							throw pw::er::Warning_Error(L"Physics_Object", L"shape is not valid", EXCEPTION_LINE, __FILEW__, L"Physics_Object");
						}
						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					case Object_Type::CIRCLE: {
						b2CircleShape v_shape{};

						v_shape.m_radius = ((m_model_size.x + m_model_size.y) / 4) / 32.0f;

						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					default: {
						break;
					}
				}
			}
			void Physics_Object::Set_Size_Px(const glm::vec2& p_size_px) {
				m_model_size.Set(p_size_px.x, p_size_px.y);

				switch (m_body_type) {
					case Object_Type::POLYGON: {
						b2PolygonShape v_shape{};

						// Fill in the shape's vertices
						for (size_t i = 0; i < m_vertex_count; i++) {
							m_shape_vertices[i].Set((m_shape_vertices[i].x - 0.5f) * m_model_size.x / 32.0f,
								(m_shape_vertices[i].y + 0.5f) * m_model_size.y / 32.0f);
						}
						// Create shape
						v_shape.Set(m_shape_vertices, m_vertex_count);

						if (TRY_LINE !v_shape.Validate()) {
							throw pw::er::Warning_Error(L"Physics_Object", L"shape is not valid", EXCEPTION_LINE, __FILEW__, L"Physics_Object");
						}
						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					case Object_Type::CIRCLE: {
						b2CircleShape v_shape{};

						v_shape.m_radius = ((m_model_size.x + m_model_size.y) / 4) / 32.0f;

						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					default: {
						break;
					}
				}
			}
			void Physics_Object::Set_Size_M(const glm::vec2& p_size_m) {
				m_model_size.Set(p_size_m.x * 32.0f, p_size_m.y * 32.0f);

				switch (m_body_type) {
					case Object_Type::POLYGON: {
						b2PolygonShape v_shape{};

						// Fill in the shape's vertices
						for (size_t i = 0; i < m_vertex_count; i++) {
							m_shape_vertices[i].Set((m_shape_vertices[i].x - 0.5f) * m_model_size.x / 32.0f,
								(m_shape_vertices[i].y + 0.5f) * m_model_size.y / 32.0f);
						}
						// Create shape
						v_shape.Set(m_shape_vertices, m_vertex_count);

						if (TRY_LINE !v_shape.Validate()) {
							throw pw::er::Warning_Error(L"Physics_Object", L"shape is not valid", EXCEPTION_LINE, __FILEW__, L"Physics_Object");
						}
						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					case Object_Type::CIRCLE: {
						b2CircleShape v_shape{};

						v_shape.m_radius = ((m_model_size.x + m_model_size.y) / 4) / 32.0f;

						b2FixtureDef v_fixture{};

						v_fixture.friction = m_current_fixture->GetFriction();
						v_fixture.restitution = m_current_fixture->GetRestitution();
						v_fixture.density = m_current_fixture->GetDensity();
						v_fixture.isSensor = m_current_fixture->IsSensor();
						v_fixture.shape = &v_shape;

						m_body->DestroyFixture(m_current_fixture);

						m_current_fixture = m_body->CreateFixture(&v_fixture);
						break;
					}
					default: {
						break;
					}
				}
			}
			void Physics_Object::Set_Body(b2Body* p_body) {
				m_body = p_body;
			}
		// End of Class Members
		// Physics_Factory          
		// Static Declarations      
		// Class Members
			Physics_Factory::Physics_Factory() : m_world{ nullptr }, m_velocity_it{ 0 }, m_position_it{ 0 },
					m_last_added_body{ NULL },
					m_factory_static{}, m_factory_dynamic{} {
			}
			Physics_Factory::Physics_Factory(const b2Vec2& p_gravity, const int32_t& p_velocity_it, const int32_t& p_position_it) :
					m_world{ pw::Engine_Memory::Allocate<b2World, bool>(p_gravity) }, m_velocity_it{ p_velocity_it }, m_position_it{ p_position_it },
					m_last_added_body{ NULL },
					m_factory_static{}, m_factory_dynamic{} {
			}
			Physics_Factory::~Physics_Factory() {
				for (auto i = m_factory_static.begin(); i != m_factory_static.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Physics_Object>(*i) == false) {
						if (*i != nullptr) {
							delete *i;
							*i = nullptr;
						}
					}
				}
				for (auto i = m_factory_dynamic.begin(); i != m_factory_dynamic.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Physics_Object>(i->second) == false) {
						if (i->second != nullptr) {
							delete i->second;
							i->second = nullptr;
						}
					}
				}
				if (pw::Engine_Memory::Deallocate<b2World>(m_world) == false) {
					if (m_world != nullptr) {
						delete m_world;
						m_world = nullptr;
					}
				}
			}
			void Physics_Factory::Run() {
				m_world->Step(std::chrono::duration<float, std::deci>(pw::cm::Engine_Constant::Delta_Time()).count() / 10.0f, m_velocity_it, m_position_it);
			}
			void Physics_Factory::Add_Object(st::Model* p_model, const b2BodyType& p_type, const st::Physics_Object::Object_Type& p_polygon, const bool& p_is_sensor, const PW_ID& p_object_id, const bool& p_is_fixed, const float& p_friction, const float& p_restitution, const float& p_density) {
				try {
					st::Physics_Object* v_object = pw::Engine_Memory::Allocate<Physics_Object, bool>(p_model, p_type, m_world, p_is_fixed, p_friction, p_restitution, p_density, p_polygon, p_is_sensor);
					m_last_added_body = v_object->Body();
					m_factory_dynamic.insert(std::make_pair(p_object_id, v_object));
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			st::Physics_Object* Physics_Factory::Access_Memeber(const PW_ID& p_id) {
				if (m_factory_dynamic.count(p_id) > 0) {
					return m_factory_dynamic.at(p_id);
				}
				else {
					return nullptr;
				}
			}
			b2Body* Physics_Factory::Last_Added_Body() {
				return m_last_added_body;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////