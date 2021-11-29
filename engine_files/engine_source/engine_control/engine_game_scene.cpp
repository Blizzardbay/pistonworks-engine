#include "engine_structures\engine_game_scene.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Scene_Model         
		// Static Declarations    
		// Class Members        
			void Scene_Model::Render() {
			}
			void Scene_Model::Delete() {
			}
			void Scene_Model::Refresh() {
			}
			Scene_Model::Type_Identifier Scene_Model::Model_Identifier() {
				return Scene_Model::Type_Identifier::NO_TYPE;
			}
		// End of Class Members
		// Asset_Model         
		// Static Declarations    
		// Class Members         
			Asset_Model::Asset_Model() :
					model(nullptr), m_text(nullptr), layer(0) {
			}
			Asset_Model::Asset_Model(PW_SRD_PTR(Static_Model) model, int32_t layer) :
					model(model), m_text(nullptr), layer(layer) {
			}
			Asset_Model::Asset_Model(PW_SRD_PTR(Static_Model) model, st::Text* text, int32_t layer) :
					model(model), m_text(text), layer(layer) {
			}
			Asset_Model::~Asset_Model() {
			}
			void Asset_Model::Render() {
				if (m_text != nullptr) {
					m_text->Render();
				}
				if (model != nullptr) {
					model->Render();
				}
			}
			void Asset_Model::Delete() {
				if (m_text != nullptr) {
					m_text->Delete();
					pw::Engine_Memory::Deallocate<st::Text>(m_text, false);
				}
				if (model != nullptr) {
					model->Delete();
					pw::Engine_Memory::Deallocate<st::Static_Model>(model.get(), true);
				}
			}
			void Asset_Model::Refresh() {
				if (m_text != nullptr) {
					m_text->Refresh();
				}
				if (model != nullptr) {
					model->Refresh_Model();
				}
			}
			Scene_Model::Type_Identifier Asset_Model::Model_Identifier() {
				return Scene_Model::Type_Identifier::ASSET_MODEL;
			}
			Static_Model& Asset_Model::Model() {
				return *model;
			}
			st::Text* Asset_Model::Text() {
				return m_text;
			}
			int32_t Asset_Model::Layer() {
				return layer;
			}
		// End of Class Members
		// AAsset_Model           
		// Static Declarations     
		// Class Members
			AAsset_Model::AAsset_Model() :
				Asset_Model(), m_animations(std::make_shared<Animation>(Animation())), m_current_animation{nullptr} {
			}
			AAsset_Model::AAsset_Model(PW_SRD_PTR(Static_Model) model, PW_SRD_PTR(Animation) animation, int32_t layer) :
					Asset_Model(model, layer), m_animations(animation), m_current_animation{ animation.get() } {
			}
			AAsset_Model::AAsset_Model(PW_SRD_PTR(Static_Model) model, std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> p_animations, std::vector<std::wstring> p_animation_ids, int32_t layer) :
				Asset_Model(model, layer), m_animations(p_animations, p_animation_ids), m_current_animation{ p_animations.front()._Myfirst._Val.get() } {
			}
			AAsset_Model::~AAsset_Model() {
			}
			void AAsset_Model::Render() {
				Run_Animation();
				this->Asset_Model::Render();
			}
			void AAsset_Model::Delete() {
				this->Asset_Model::Delete();
				m_animations.Delete();
				m_current_animation = nullptr;
			}
			void AAsset_Model::Refresh() {
				this->Asset_Model::Refresh();
			}
			void AAsset_Model::Run_Animation() {
				m_current_animation->Change_Frame();
				this->Asset_Model::Model().Model_Mesh()->Change_Texture_Data(m_current_animation->Vertices());
			}
			void AAsset_Model::Advance_Animation() {
				m_current_animation->Advance_Frame();
				this->Asset_Model::Model().Model_Mesh()->Change_Texture_Data(m_current_animation->Vertices());
			}
			void AAsset_Model::Start_Animation() {
				m_current_animation->Start_Animation();
			}
			void AAsset_Model::Stop_Animation() {
				m_current_animation->Stop_Animation();
			}
			Scene_Model::Type_Identifier AAsset_Model::Model_Identifier() {
				return Scene_Model::Type_Identifier::AASSET_MODEL;
			}
			st::Animation* AAsset_Model::Model_Animation() {
				return m_current_animation;
			}
		// End of Class Members
		// Actor_Model            
		// Static Declarations     
			PW_ID Actor_Model::global_index = 0;
		// Class Members       
			Actor_Model::Actor_Model() :
					model(nullptr), poly_body(nullptr), event_id(0), s_id{}, m_text(nullptr), layer(0) {
			}
			Actor_Model::Actor_Model(PW_SRD_PTR(Dynamic_Model) model, int32_t layer) :
					model(model), poly_body(nullptr), event_id(0), s_id{}, m_text(nullptr), layer(layer) {
			}
			Actor_Model::Actor_Model(PW_SRD_PTR(Dynamic_Model) model, st::Text* text, int32_t layer) :
					model(model), poly_body(nullptr), event_id(0), s_id{}, m_text(text), layer(layer) {
			}
			Actor_Model::~Actor_Model() {
			}
			void Actor_Model::Render() {
				if (m_text != nullptr) {
					m_text->Render();
				}
				if (model != nullptr) {
					if (poly_body != nullptr) {
						model->Render(poly_body);
					}
					else {
						model->Render();
					}
				}
			}
			void Actor_Model::Delete() {
				if (m_text != nullptr) {
					m_text->Delete();
					pw::Engine_Memory::Deallocate<st::Text>(m_text, false);
				}
				if (model != nullptr) {
					model->Delete();
					pw::Engine_Memory::Deallocate<st::Dynamic_Model>(model.get(), true);
				}
				poly_body = nullptr;
			}
			void Actor_Model::Refresh() {
				if (m_text != nullptr) {
					m_text->Refresh();
				}
				if (model != nullptr) {
					model->Refresh_Model();
				}
			}
			Scene_Model::Type_Identifier Actor_Model::Model_Identifier() {
				return Scene_Model::Type_Identifier::ACTOR_MODEL;
			}
			void Actor_Model::Set_Poly_Body(b2Body* poly_body) {
				this->poly_body = poly_body;
			}
			void Actor_Model::Set_Event_ID(PW_ID id) {
				event_id = id;
			}
			void Actor_Model::Set_S_ID(std::wstring s_id) {
				this->s_id = s_id;
			}
			void Actor_Model::Increment_ID_Index() {
				global_index = global_index + 1;
			}
			Dynamic_Model& Actor_Model::Model() {
				return *model;
			}
			PW_ID Actor_Model::Event_ID() const {
				return event_id;
			}
			std::wstring* Actor_Model::S_ID() {
				return &s_id;
			}
			const PW_ID Actor_Model::Global_ID() {
				return global_index;
			}
			st::Text* Actor_Model::Text() {
				return m_text;
			}
			int32_t Actor_Model::Layer() {
				return layer;
			}
		// End of Class Members
		// AActor_Model           
		// Static Declarations     
		// Class Members 
			AActor_Model::AActor_Model() :
				Actor_Model(), m_animations(std::make_shared<Animation>(Animation())), m_current_animation{ nullptr } {
			}
			AActor_Model::AActor_Model(PW_SRD_PTR(Dynamic_Model) model, PW_SRD_PTR(Animation) animation, int32_t layer) :
				Actor_Model(model, layer), m_animations(animation), m_current_animation{ animation.get() } {
			}
			AActor_Model::AActor_Model(PW_SRD_PTR(Dynamic_Model) model, std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> p_animations, std::vector<std::wstring> p_animation_ids, int32_t layer) :
				Actor_Model(model, layer), m_animations(p_animations, p_animation_ids), m_current_animation{ p_animations.front()._Myfirst._Val.get() } {
			}
			AActor_Model::~AActor_Model() {
			}
			void AActor_Model::Render() {
				Run_Animation();
				this->Actor_Model::Render();
			}
			void AActor_Model::Delete() {
				this->Actor_Model::Delete();
				m_animations.Delete();
				m_current_animation = nullptr;
			}
			void AActor_Model::Refresh() {
				this->Actor_Model::Refresh();
			}
			void AActor_Model::Run_Animation() {
				m_current_animation->Change_Frame();
				this->Actor_Model::Model().Model_Mesh()->Change_Texture_Data(m_current_animation->Vertices());
			}
			void AActor_Model::Advance_Animation() {
				m_current_animation->Advance_Frame();
				this->Actor_Model::Model().Model_Mesh()->Change_Texture_Data(m_current_animation->Vertices());
			}
			void AActor_Model::Start_Animation() {
				m_current_animation->Start_Animation();
			}
			void AActor_Model::Stop_Animation() {
				m_current_animation->Stop_Animation();
			}
			void AActor_Model::Change_Animation(std::wstring p_animation_id, bool reset) {
				if (p_animation_id != L"") {
					m_current_animation = m_animations.Animation(p_animation_id.c_str())._Myfirst._Val.get();
					this->Model().Set_Texture(m_animations.Animation(p_animation_id.c_str())._Get_rest()._Myfirst._Val);
					if (reset == true) {
						m_current_animation->Reset_Animation();
					}
				}
			}
			Scene_Model::Type_Identifier AActor_Model::Model_Identifier() {
				return Scene_Model::Type_Identifier::AACTOR_MODEL;
			}
			st::Animation* AActor_Model::Model_Animation() {
				return m_current_animation;
			}
		// End of Class Members
		// Scene_Event
			Scene_Event::Scene_Event(Actor_Model* model_pointer, st::Event_Base* model_event) :
					m_model{ model_pointer }, m_model_event{ model_event } {
			}
			Scene_Event::~Scene_Event() {
				LET_CPP_IMPLEMENT
			}
			void Scene_Event::Run_Event() {
				m_model_event->Trigger_Event();
			}
			st::Event_Base* Scene_Event::Event() const {
				return m_model_event;
			}
			Actor_Model* Scene_Event::Model() const {
				return m_model;
			}
		// Game_Scene   
		// Static Declarations     
			int32_t Game_Scene::global_asset_count = 0;
			int32_t Game_Scene::global_actor_count = 0;
		// Class Members
			Game_Scene::Game_Scene() :
				scene_name{nullptr}, scene_models{}, collision_models{},
				scene_input{ nullptr }, scene_events{}, scene_id_counter{ 0 }, current_scene_events{}, scene_physics{ nullptr }, s_id_models{}, render_queue{}, m_last_render_count{ 0 }, re_render{ true }, camera_position_instance{ st::Camera::Camera_Position() },
					quadrant_1_box{ quadtree::Box<float>{(float)0, (float)0, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_1{ quadtree::Box<float>{(float)0, (float)0, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box },
					quadrant_2_box{ quadtree::Box<float>{(float)INT32_MIN, (float)0, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_2{ quadtree::Box<float>{(float)INT32_MIN, (float)0, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box },
					quadrant_3_box{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_3{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box },
					quadrant_4_box{ quadtree::Box<float>{(float)0, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_4{ quadtree::Box<float>{(float)0, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box } {
			}
			Game_Scene::Game_Scene(const wchar_t* scene_name, std::vector<PW_SRD_PTR(Scene_Model)> scene_models, std::vector<PW_SRD_PTR(Actor_Model)> collision_models,
				co::Engine_Input* scene_input, Pysics_Factory* scene_physics) :
					scene_name{ scene_name }, scene_models{ scene_models }, collision_models{ collision_models },
				scene_input{ scene_input }, scene_events{}, scene_id_counter{ 0 }, current_scene_events{}, scene_physics{ scene_physics }, s_id_models{}, render_queue{}, m_last_render_count{ 0 }, re_render{ true }, camera_position_instance{ st::Camera::Camera_Position() },
					quadrant_1_box{ quadtree::Box<float>{(float)0, (float)0, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_1{ quadtree::Box<float>{(float)0, (float)0, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box },
					quadrant_2_box{ quadtree::Box<float>{(float)INT32_MIN, (float)0, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_2{ quadtree::Box<float>{(float)INT32_MIN, (float)0, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box },
					quadrant_3_box{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_3{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box },
					quadrant_4_box{ quadtree::Box<float>{(float)0, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX} },
					quadrant_4{ quadtree::Box<float>{(float)0, (float)INT32_MIN, (float)INT32_MAX, (float)INT32_MAX},
						Game_Scene::Get_Box } {
				// Put models into the different quadtrees
				
				for (size_t i = 0; i < scene_models.size(); i++) {
					bool v_x_bit = false;
					bool v_y_bit = false;
					switch (scene_models.at(i).get()->Model_Identifier()) {
						case Scene_Model::Type_Identifier::ASSET_MODEL: {
							Asset_Model* v_model = static_cast<Asset_Model*>(scene_models.at(i).get());

							// True = positive , False = negative
							v_x_bit = !std::signbit(v_model->Model().Position().x);
							v_y_bit = !std::signbit(v_model->Model().Position().y);

							break;
						}
						case Scene_Model::Type_Identifier::AASSET_MODEL: {
							AAsset_Model* v_model = static_cast<AAsset_Model*>(scene_models.at(i).get());

							// True = positive , False = negative
							v_x_bit = !std::signbit(v_model->Model().Position().x);
							v_y_bit = !std::signbit(v_model->Model().Position().y);

							break;
						}
						case Scene_Model::Type_Identifier::ACTOR_MODEL: {
							Actor_Model* v_model = static_cast<Actor_Model*>(scene_models.at(i).get());

							// True = positive , False = negative
							v_x_bit = !std::signbit(v_model->Model().Position().x);
							v_y_bit = !std::signbit(v_model->Model().Position().y);

							break;
						}
						case Scene_Model::Type_Identifier::AACTOR_MODEL: {
							AActor_Model* v_model = static_cast<AActor_Model*>(scene_models.at(i).get());

							// True = positive , False = negative
							v_x_bit = !std::signbit(v_model->Model().Position().x);
							v_y_bit = !std::signbit(v_model->Model().Position().y);

							break;
						}
						default: {
							break;
						}
					}
					// Quadrant_1 +,+
					// Quadrant_4 +,-
					if (v_x_bit == true) {
						// Quadrant_1 +,+
						if (v_y_bit == true) {
							quadrant_1.add(scene_models.at(i).get());
						}
						// Quadrant_4 +,-
						else {
							quadrant_4.add(scene_models.at(i).get());
						}
					}
					// Quadrant_2 -,+
					// Quadrant_3 -,-
					else {
						// Quadrant_2 -,+
						if (v_y_bit == true) {
							quadrant_2.add(scene_models.at(i).get());
						}
						// Quadrant_3 -,-
						else {
							quadrant_3.add(scene_models.at(i).get());
						}
					}


				}
			}
			Game_Scene::~Game_Scene() {
			}
			void Game_Scene::Pre_Render() {
				if (scene_physics != nullptr) {
					scene_physics->Run();
				}

				if (current_scene_events.size() > 0) {
					for (auto it = current_scene_events.begin(); it != current_scene_events.end(); it++) {
						if ((*it) != NULL) {
							(*it)->Run_Event();
						}
					}
				}
				// Test for intersections
				glm::vec2 v_camera_position = st::Camera::Camera_Position();
				glm::vec2 v_camera_size = st::Camera::Camera_Size();
				quadtree::Box<float> v_screen_box = quadtree::Box<float>(v_camera_position.x, v_camera_position.y - v_camera_size.y,
					v_camera_size.x, v_camera_size.y);

				std::vector<Scene_Model*> v_models{};
				if (quadrant_1_box.intersects(v_screen_box) == true) {
					v_models = quadrant_1.query(v_screen_box);
					render_queue.insert(render_queue.end(), v_models.begin(), v_models.end());
					v_models.clear();
				}
				if (quadrant_2_box.intersects(v_screen_box) == true) {
					v_models = quadrant_2.query(v_screen_box);
					render_queue.insert(render_queue.end(), v_models.begin(), v_models.end());
					v_models.clear();
				}
				if (quadrant_3_box.intersects(v_screen_box) == true) {
					v_models = quadrant_3.query(v_screen_box);
					render_queue.insert(render_queue.end(), v_models.begin(), v_models.end());
					v_models.clear();
				}
				if (quadrant_4_box.intersects(v_screen_box) == true) {
					v_models = quadrant_4.query(v_screen_box);
					render_queue.insert(render_queue.end(), v_models.begin(), v_models.end());
					v_models.clear();
				}

				m_last_render_count = render_queue.size();

				if (render_queue.size() > 0) {
					std::multimap<int, st::Scene_Model*> render_order{};
					std::vector<Scene_Model*> screen_render{};

					glm::vec2 camera_change{ st::Camera::Camera_Position() - st::Camera::Camera_Position_Last() };

					for (size_t i = 0; i < render_queue.size(); i++) {
						switch (render_queue.at(i)->Model_Identifier()) {
							case st::Scene_Model::Type_Identifier::ASSET_MODEL: {
								Asset_Model* v_temp = static_cast<Asset_Model*>(render_queue.at(i));
								if (v_temp->Text() != nullptr) {
									m_last_render_count = m_last_render_count + v_temp->Text()->Count();
								}
								render_order.insert(std::make_pair(v_temp->Layer(), render_queue.at(i)));
								break;
							}
							case st::Scene_Model::Type_Identifier::AASSET_MODEL: {
								Asset_Model* v_temp = static_cast<Asset_Model*>(render_queue.at(i));
								if (v_temp->Text() != nullptr) {
									m_last_render_count = m_last_render_count + v_temp->Text()->Count();
								}
								render_order.insert(std::make_pair(v_temp->Layer(), render_queue.at(i)));
								break;
							}
							case st::Scene_Model::Type_Identifier::ACTOR_MODEL: {
								Actor_Model* v_temp = static_cast<Actor_Model*>(render_queue.at(i));
								if (v_temp->Text() != nullptr) {
									m_last_render_count = m_last_render_count + v_temp->Text()->Count();
								}
								if (v_temp->Layer() == 4) {
									if (re_render == true) {
										v_temp->Model().Position_Reference().x = v_temp->Model().Position_Reference().x + (st::Camera::Camera_Position().x - camera_position_instance.x);
										v_temp->Model().Position_Reference().y = v_temp->Model().Position_Reference().y + (st::Camera::Camera_Position().y - camera_position_instance.y);
									}
									else {
										v_temp->Model().Position_Reference().x = v_temp->Model().Position_Reference().x + camera_change.x;
										v_temp->Model().Position_Reference().y = v_temp->Model().Position_Reference().y + camera_change.y;
									}
									screen_render.push_back(render_queue.at(i));
								}
								else {
									render_order.insert(std::make_pair(v_temp->Layer(), render_queue.at(i)));
								}
								break;
							}
							case st::Scene_Model::Type_Identifier::AACTOR_MODEL: {
								Actor_Model* v_temp = static_cast<Actor_Model*>(render_queue.at(i));
								if (v_temp->Text() != nullptr) {
									m_last_render_count = m_last_render_count + v_temp->Text()->Count();
								}
								if (v_temp->Layer() == 4) {
									if (re_render == true) {
										v_temp->Model().Position_Reference().x = v_temp->Model().Position_Reference().x + (st::Camera::Camera_Position().x - camera_position_instance.x);
										v_temp->Model().Position_Reference().y = v_temp->Model().Position_Reference().y + (st::Camera::Camera_Position().y - camera_position_instance.y);
									}
									else {
										v_temp->Model().Position_Reference().x = v_temp->Model().Position_Reference().x + camera_change.x;
										v_temp->Model().Position_Reference().y = v_temp->Model().Position_Reference().y + camera_change.y;
									}
									screen_render.push_back(render_queue.at(i));
								}
								else {
									render_order.insert(std::make_pair(v_temp->Layer(), render_queue.at(i)));
								}
								break;
							}
							default: {
								break;
							}
						}
					}
					// Make sure after the fact we stop it from 
					// continuing todo calculations
					if (re_render != false) {
						re_render = false;
					}

					render_queue.clear();
					for (auto i = render_order.begin(); i != render_order.end(); i++) {
						render_queue.push_back(i->second);
					}
					for (auto i = screen_render.begin(); i != screen_render.end(); i++) {
						render_queue.push_back((*i._Ptr));
					}
				}
			}
			void Game_Scene::Render() {
				if (render_queue.size() > 0) {
					for (auto i = render_queue.begin(); i != render_queue.end(); i++) {
						(*i._Ptr)->Render();
					}
					render_queue.clear();
				}
			}
			void Game_Scene::Delete() {
				for (size_t i = 0; i < scene_models.size(); i++) {
					(*scene_models.at(i)).Delete();
					pw::Engine_Memory::Deallocate<st::Scene_Model>(scene_models.at(i).get(), true);
					scene_models.at(i).~shared_ptr();
				}
				scene_models.erase(scene_models.begin(), scene_models.end());
				scene_models.~vector();
				for (size_t i = 0; i < collision_models.size(); i++) {
					collision_models.at(i) = nullptr;
				}
				collision_models.erase(collision_models.begin(), collision_models.end());
				collision_models.~vector();

				if (scene_input != nullptr) {
					pw::Engine_Memory::Deallocate<co::Engine_Input>(scene_input);
				}
				for (auto i = scene_events.begin(); i != scene_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							for (auto l = k->second.begin(); l != k->second.end(); l++) {
								pw::Engine_Memory::Deallocate<st::Event_Base>(l->second.Event());
							}
						}
					}
				}
				scene_events.clear();

				for (size_t i = 0; i < current_scene_events.size(); i++) {
					current_scene_events.at(i) = nullptr;
				}
				current_scene_events.erase(current_scene_events.begin(), current_scene_events.end());
				current_scene_events.~vector();
				if (scene_physics != nullptr) {
					scene_physics->Delete();
					pw::Engine_Memory::Deallocate<st::Pysics_Factory>(scene_physics);
				}
			}
			void Game_Scene::Refresh_Scene() {
				for (size_t i = 0; i < scene_models.size(); i++) {
					scene_models.at(i)->Refresh();
				}
			}
			void Game_Scene::Re_Render() {
				re_render = true;
			}
			void Game_Scene::Capture_Instance(glm::vec2 camera_position) {
				camera_position_instance = camera_position;
			}
			std::vector<PW_SRD_PTR(Scene_Model)> Game_Scene::Scene() const {
				return scene_models;
			}
			const size_t& Game_Scene::Last_Render_Count() const {
				return m_last_render_count;
			}
			Pysics_Factory* Game_Scene::Scene_Physics() {
				return scene_physics;
			}
			Actor_Model& Game_Scene::Access_Model(std::wstring s_id) {
				auto v_found = s_id_models.find(s_id);
				if (v_found != s_id_models.end()) {
					return *v_found->second;
				}
			}
			COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) Game_Scene::Event_Callback() {
				return std::bind(&st::Game_Scene::Activate_Event, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			}
			PW_FUNCTION Game_Scene::Refresh_Scene_Callback() {
				return std::bind(&st::Game_Scene::Refresh_Scene, this);
			}
			int32_t Game_Scene::Asset_Count() {
				return global_asset_count;
			}
			int32_t Game_Scene::Actor_Count() {
				return global_actor_count;
			}
			void Game_Scene::Activate_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state) {
				if (scene_events.count(event_type) > 0) {
					switch (event_type) {
						case cm::Engine_Constant::PW_CLICK_EVENT: {
							for (auto i = scene_events.at(event_type).begin(); i != scene_events.at(event_type).end(); i++) {
								if (i->first == button) {
									if (i->second.count(state) > 0) {
										for (auto j = i->second.at(state).begin(); j != i->second.at(state).end(); j++) {
											// Use algorithm to find if the click was within the model range
											glm::ivec2 point = glm::ivec2(cm::Engine_Constant::Mouse_X_Coord(), cm::Engine_Constant::Mouse_Y_Coord());

											std::shared_ptr<st::Mesh> mesh = j->second.Model()->Model().Model_Mesh();
											glm::ivec2 model_position = glm::ivec2(j->second.Model()->Model().Position().x, j->second.Model()->Model().Position().y);
											glm::ivec2 model_size = glm::ivec2(j->second.Model()->Model().Model_Size());
											std::vector<glm::ivec2> points{};

											for (size_t k = 0; k < mesh.get()->Vertex_Count(); k++) {
												points.push_back(glm::ivec2(
													// x
													model_position.x + (model_size.x * mesh.get()->Vertices()[k].Vertex_Position().x),
													// y
													model_position.y + (model_size.y * mesh.get()->Vertices()[k].Vertex_Position().y)
												));
											}
											int32_t l = mesh.get()->Vertex_Count();
											int32_t nvert = mesh.get()->Vertex_Count();
											bool c = false;

											for (int32_t p = 0, j = nvert - 1; p < nvert; l = p++) {
												if (((points[p].y > point.y) != (points[l].y > point.y)) &&
													(point.x < (points[l].x - points[p].x) * (point.y - points[p].y) / (points[l].y - points[p].y) + points[p].x)) {
													c = !c;
												}
											}
											if (c == true) {
												if (j->second.Event()->Play_State() == true) {
													j->second.Run_Event();
												}
											}
										}
									}
								}
							}
							break;
						}
						case cm::Engine_Constant::PW_HOVER_EVENT: {
							for (auto i = scene_events.at(event_type).begin(); i != scene_events.at(event_type).end(); i++) {
								for (auto j = i->second.begin(); j != i->second.end(); j++) {
									for (auto t = j->second.begin(); t != j->second.end(); t++) {
										// Use algorithm to find if the click was within the model range
										glm::ivec2 point = glm::ivec2(cm::Engine_Constant::Mouse_X_Coord(), cm::Engine_Constant::Mouse_Y_Coord());

										std::shared_ptr<st::Mesh> mesh = t->second.Model()->Model().Model_Mesh();
										glm::ivec2 model_position = glm::ivec2(t->second.Model()->Model().Position().x, t->second.Model()->Model().Position().y);
										glm::ivec2 model_size = glm::ivec2(t->second.Model()->Model().Model_Size());
										std::vector<glm::ivec2> points{};

										for (size_t k = 0; k < mesh.get()->Vertex_Count(); k++) {
											points.push_back(glm::ivec2(
												// x
												model_position.x + (model_size.x * mesh.get()->Vertices()[k].Vertex_Position().x),
												// y
												model_position.y + (model_size.y * mesh.get()->Vertices()[k].Vertex_Position().y)
											));
										}
										int32_t l = mesh.get()->Vertex_Count() - 1;
										int32_t nvert = mesh.get()->Vertex_Count();
										bool c = false;

										for (int32_t p = 0, j = nvert - 1; p < nvert; l = p++) {
											if (((points[p].y > point.y) != (points[l].y > point.y)) &&
												(point.x < (points[l].x - points[p].x) * (point.y - points[p].y) / (points[l].y - points[p].y) + points[p].x)) {
												c = !c;
											}
										}
										if (c == true) {
											if (t->second.Event()->Play_State() == true) {
												t->second.Run_Event();
											}
										}
									}
								}
							}
							break;
						}
						case cm::Engine_Constant::PW_KEYBOARD_EVENT: {
							auto v_found_button = scene_events.at(event_type).find(button);
							if (v_found_button != scene_events.at(event_type).end()) {
								auto v_found_state = scene_events.at(event_type).at(button).find(state);
								if (v_found_state != scene_events.at(event_type).at(button).end()) {
									for (auto i = scene_events.at(event_type).at(button).at(state).begin(); i != scene_events.at(event_type).at(button).at(state).end(); i++) {
										i->second.Run_Event();
										if (!(i->second.Event()->Play_State())) {
											current_scene_events.push_back(std::make_shared<Scene_Event>(i->second));
										}
									}
								}
							}
							break;
						}
						default: {
							break;
						}
					}
				}
			}
			void Game_Scene::Register_S_ID(std::wstring s_id, Actor_Model* model) {
				auto v_found = s_id_models.find(s_id);
				if (v_found == s_id_models.end()) {
					s_id_models.insert(std::make_pair(s_id, model));
				}
			}
			quadtree::Box<float> Game_Scene::Get_Box(Scene_Model* p_model) {
				switch (p_model->Model_Identifier()) {
					case Scene_Model::Type_Identifier::ASSET_MODEL: {
						Asset_Model* v_model = static_cast<Asset_Model*>(p_model);

						return quadtree::Box<float>{quadtree::Vector2<float>{(float)v_model->Model().Position().x, (float)v_model->Model().Position().y - (float)v_model->Model().Model_Size().y},
							quadtree::Vector2<float>{(float)v_model->Model().Model_Size().x, (float)v_model->Model().Model_Size().y}};
						break;
					}
					case Scene_Model::Type_Identifier::AASSET_MODEL: {
						AAsset_Model* v_model = static_cast<AAsset_Model*>(p_model);

						return quadtree::Box<float>{quadtree::Vector2<float>{(float)v_model->Model().Position().x, (float)v_model->Model().Position().y - (float)v_model->Model().Model_Size().y},
							quadtree::Vector2<float>{(float)v_model->Model().Model_Size().x, (float)v_model->Model().Model_Size().y}};
						break;
					}
					case Scene_Model::Type_Identifier::ACTOR_MODEL: {
						Actor_Model* v_model = static_cast<Actor_Model*>(p_model);

						return quadtree::Box<float>{quadtree::Vector2<float>{(float)v_model->Model().Position().x, (float)v_model->Model().Position().y - (float)v_model->Model().Model_Size().y},
							quadtree::Vector2<float>{(float)v_model->Model().Model_Size().x, (float)v_model->Model().Model_Size().y}};
						break;
					}
					case Scene_Model::Type_Identifier::AACTOR_MODEL: {
						AActor_Model* v_model = static_cast<AActor_Model*>(p_model);

						return quadtree::Box<float>{quadtree::Vector2<float>{(float)v_model->Model().Position().x, (float)v_model->Model().Position().y - (float)v_model->Model().Model_Size().y},
							quadtree::Vector2<float>{(float)v_model->Model().Model_Size().x, (float)v_model->Model().Model_Size().y}};
						break;
					}
					default: {
						break;
					}
				}
				return quadtree::Box<float>();
			}
			co::Engine_Input* Game_Scene::Input() {
				return scene_input;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
