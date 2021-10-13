#include "engine_structures\engine_physics.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Pysics_Object          
		// Static Declarations     
		// Class Members           
			Pysics_Object::Pysics_Object(std::shared_ptr<Dynamic_Model> model, b2BodyType type, b2World* world,bool is_fixed) :
					body{},
					shape_vertices{ new b2Vec2[model->Model_Mesh()->Vertex_Count()] },
					model_size{} {
				b2BodyDef body_def{};
				// Create body def
				body_def.fixedRotation = is_fixed;
				body_def.type = type;
				body_def.position.Set(model->Position().x / 32.0f, model->Position().y / 32.0f);

				vertex_count = model->Model_Mesh()->Vertex_Count();
				model_size.Set(model->Model_Size().x, model->Model_Size().y);
				// Add body def to world
				body = world->CreateBody(&body_def);

				b2PolygonShape shape{};

				// Fill in the shape's vertices
				for (size_t i = 0; i < model->Model_Mesh()->Vertex_Count(); i++) {
					shape_vertices.get()[i].Set(model->Model_Mesh()->Vertices()[i].Vertex_Position().x,
						model->Model_Mesh()->Vertices()[i].Vertex_Position().y);
				}
				// Create shape
				shape.Set(shape_vertices.get(), model->Model_Mesh()->Vertex_Count());

				if (!shape.Validate()) {
					printf("Error\n");
				}

				b2FixtureDef fixture{};
				// Check for static type
				if (type == b2_staticBody) {
					// Create the fixture for the body
					fixture.shape = &shape;
					body->CreateFixture(&fixture);
				}
				else {
					// Create the fixture for the body
					// Dynamic / Kinematic
					fixture.friction = 1.0f;
					fixture.restitution = 0.95f;
					fixture.density = 1.0f;
					fixture.shape = &shape;
					body->CreateFixture(&fixture);
				}
			}
			Pysics_Object::~Pysics_Object() {
			}
			void Pysics_Object::Delete() {
				shape_vertices.~shared_ptr();
			}
			int32_t Pysics_Object::X_Pixels_Position(int32_t scale_factor) {
				return static_cast<int32_t>(body->GetPosition().x * scale_factor);
			}
			int32_t Pysics_Object::Y_Pixels_Position(int32_t scale_factor) {
				return static_cast<int32_t>(body->GetPosition().y * scale_factor);
			}
			b2Body* Pysics_Object::Body() {
				return body;
			}
			b2Vec2 Pysics_Object::Size() {
				return model_size;
			}
			void Pysics_Object::Set_Body(b2Body* body) {
				this->body = body;
			}
		// End of Class Members
		// Pysics_Factory          
		// Static Declarations      
		// Class Members            
			Pysics_Factory::Pysics_Factory(b2Vec2 gravity, int32_t velocity_it, int32_t position_it, float time_step) :
					world{ gravity }, velocity_it{ velocity_it }, position_it{ position_it },
					time_step{ time_step }, last_added_body{ NULL }, multiplier{ 1 }, current_rect{ false },
					factory_static{}, factory_dynamic{} {
			}
			Pysics_Factory::~Pysics_Factory() {
			}
			void Pysics_Factory::Run() {
				world.Step(time_step, velocity_it, position_it);
			}
			void Pysics_Factory::Delete() {
				for (size_t i = 0; i < factory_static.size(); i++) {
					factory_static.at(i)->Delete();
					factory_static.at(i)->~Pysics_Object();
					delete factory_static.at(i);
					factory_static.at(i) = nullptr;
				}

				factory_static.erase(factory_static.begin(), factory_static.end());

				for (auto i = factory_dynamic.begin(); i != factory_dynamic.end(); i++) {
					factory_dynamic.at(i->first)->Delete();
					factory_dynamic.at(i->first)->~Pysics_Object();
					delete factory_dynamic.at(i->first);
					factory_dynamic.at(i->first) = nullptr;
				}

				factory_dynamic.erase(factory_dynamic.begin(), factory_dynamic.end());
			}
			void Pysics_Factory::Add_Object(std::shared_ptr<Dynamic_Model> model, b2BodyType type, PW_ID object_id, bool is_fixed) {
				if (type == b2_staticBody) {
					/* Expensive Algorithm to link similar squares into rectangles*/

					// Test if there was a square last time
					if (factory_static.size() > 0) {
						// If vertices
						if (static_cast<b2PolygonShape*>(factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList()->GetShape())->m_count == 4) {
							// If size1 = size2 && if it is really a square
							if ((int32_t)factory_static.at(factory_static.size() - 1)->Size().x % (int32_t)model->Model_Size().x == 0 &&
								(int32_t)factory_static.at(factory_static.size() - 1)->Size().y % (int32_t)model->Model_Size().y == 0 &&
								(int32_t)model->Model_Size().x == 32 && (int32_t)model->Model_Size().y == 32)
							{
								// If x's line up
								if (model->Position().x / 32.0f == factory_static.at(factory_static.size() - 1)->X_Pixels_Position(1) + 1 * multiplier) {
									// If y is on the same axis of y
									if (model->Position().y / 32.0f == factory_static.at(factory_static.size() - 1)->Y_Pixels_Position(1)) {
										b2FixtureDef fixture{};
									
										size_t vertices_size = static_cast<b2PolygonShape*>(factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList()->GetShape())->m_count;
										b2Vec2* vertices = static_cast<b2PolygonShape*>(factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList()->GetShape())->m_vertices;

										for (size_t i = 0; i < vertices_size; i++) {
											if (vertices[i].x != 0.0f) {
												vertices[i].Set(vertices[i].x + 1.0f, vertices[i].y);
											}
										}
										b2PolygonShape shape{};

										shape.Set(vertices, static_cast<int32>(vertices_size));

										if (!shape.Validate()) {
											printf("Error\n");
										}

										fixture.shape = &shape;
										factory_static.at(
											factory_static.size() - 1)->Body()->DestroyFixture(
												factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList());
										factory_static.at(factory_static.size() - 1)->Body()->CreateFixture(&fixture);

										multiplier = multiplier + 1;
										current_rect = true;
									}
									else {
										Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
										last_added_body = object->Body();
										factory_static.push_back(object);
										current_rect = false;
										multiplier = 1;
									}
								}
								else {
									// If x's line up
									if (model->Position().x / 32.0f == factory_static.at(factory_static.size() - 1)->X_Pixels_Position(1) - 1 * multiplier) {
										// If y is on the same axis of y
										if (model->Position().y / 32.0f == factory_static.at(factory_static.size() - 1)->Y_Pixels_Position(1)) {
											b2FixtureDef fixture{};

											// This is a bit big
											size_t vertices_size = static_cast<b2PolygonShape*>(factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList()->GetShape())->m_count;
											b2Vec2* vertices = static_cast<b2PolygonShape*>(factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList()->GetShape())->m_vertices;

											for (size_t i = 0; i < vertices_size; i++) {
												//if (vertices[i].x != 0.0f) {
													vertices[i].Set(vertices[i].x + 1.0f, vertices[i].y);
												//}
											}
											b2PolygonShape shape{};

											shape.Set(vertices, static_cast<int32>(vertices_size));

											if (!shape.Validate()) {
												printf("Error\n");
											}

											fixture.shape = &shape;

											factory_static.at(
												factory_static.size() - 1)->Body()->DestroyFixture(
													factory_static.at(factory_static.size() - 1)->Body()->GetFixtureList());
											world.DestroyBody(factory_static.at(
												factory_static.size() - 1)->Body());
											b2BodyDef body_def{};

											body_def.fixedRotation = is_fixed;
											body_def.type = type;
											body_def.position.Set(model->Position().x / 32.0f, model->Position().y / 32.0f);

											b2Body* body = world.CreateBody(&body_def);

											body->CreateFixture(&fixture);

											factory_static.at(
												factory_static.size() - 1)->Set_Body(body);
											multiplier = multiplier + 1;
											current_rect = true;
										}
										else {
											Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
											last_added_body = object->Body();
											factory_static.push_back(object);
											current_rect = false;
											multiplier = 1;
										}
									}
									else {
										Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
										last_added_body = object->Body();
										factory_static.push_back(object);
										current_rect = false;
										multiplier = 1;
									}
								}
							}
							else {
								Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
								last_added_body = object->Body();
								factory_static.push_back(object);
								current_rect = false;
								multiplier = 1;
							}
						}
						else {
							Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
							last_added_body = object->Body();
							factory_static.push_back(object);
							current_rect = false;
							multiplier = 1;
						}
					}
					else {
						Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
						last_added_body = object->Body();
						factory_static.push_back(object);
						current_rect = false;
						multiplier = 1;
					}
				}
				else {
					Pysics_Object* object = new Pysics_Object{ model, type, &world, is_fixed };
					last_added_body = object->Body();
					factory_dynamic.insert(std::make_pair(object_id, object));
					current_rect = false;
					multiplier = 1;
				}
			}
			Pysics_Object* Pysics_Factory::Access_Memeber(PW_ID id) {
				if (factory_dynamic.count(id) > 0) {
					return factory_dynamic.at(id);
				}
				else {
					return nullptr;
				}
			}
			b2Body* Pysics_Factory::Last_Added_Body() {
				return last_added_body;
			}
			bool Pysics_Factory::Current_Rect() {
				return current_rect;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////