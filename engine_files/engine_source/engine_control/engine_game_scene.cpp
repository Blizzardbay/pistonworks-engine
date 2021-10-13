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
		// End of Class Members
		// Asset_Model         
		// Static Declarations    
		// Class Members         
			Asset_Model::Asset_Model() :
					model(nullptr) {
			}
			Asset_Model::Asset_Model(PW_SRD_PTR(Static_Model) model) :
					model(model) {
			}
			Asset_Model::~Asset_Model() {
			}
			void Asset_Model::Render() {
				model->Render();
			}
			void Asset_Model::Delete() {
				model->Delete();
			}
			void Asset_Model::Refresh() {
				model->Refresh_Model();
			}
			Static_Model& Asset_Model::Model() {
				return *model;
			}
		// End of Class Members
		// AAsset_Model           
		// Static Declarations     
		// Class Members         
			AAsset_Model::AAsset_Model(PW_SRD_PTR(Static_Model) model, PW_SRD_PTR(Animation) animation) :
					Asset_Model(model), animation(std::make_shared<Animation>(animation)) {
			}
			AAsset_Model::~AAsset_Model() {
			}
			void AAsset_Model::Render() {
				Run_Animation();
				this->Asset_Model::Render();
			}
			void AAsset_Model::Delete() {
				this->Asset_Model::Delete();
				animation->Delete();
			}
			void AAsset_Model::Refresh() {
				this->Asset_Model::Refresh();
			}
			void AAsset_Model::Run_Animation() {
				animation->Change_Frame();
				this->Asset_Model::Model().Model_Mesh()->Change_Texture_Data(animation->Vertices());
			}
		// End of Class Members
		// Actor_Model            
		// Static Declarations     
			PW_ID Actor_Model::global_index = 0;
		// Class Members       
			Actor_Model::Actor_Model() :
					model(nullptr),
					poly_body(nullptr), event_id(0), s_id{} {
			}
			Actor_Model::Actor_Model(PW_SRD_PTR(Dynamic_Model) model) :
					model(model), poly_body(nullptr), event_id(0) {
			}
			Actor_Model::~Actor_Model() {
			}
			void Actor_Model::Render() {
				model->Render(poly_body);
			}
			void Actor_Model::Delete() {
				model->Delete();
				poly_body = nullptr;
			}
			void Actor_Model::Refresh() {
				model->Refresh_Model();
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
		// End of Class Members
		// AActor_Model           
		// Static Declarations     
		// Class Members           
			AActor_Model::AActor_Model(PW_SRD_PTR(Dynamic_Model) model, PW_SRD_PTR(Animation) animation) :
					Actor_Model(model), animation(std::make_shared<Animation>(animation)) {
			}
			AActor_Model::~AActor_Model() {
			}
			void AActor_Model::Render() {
				Run_Animation();
				this->Actor_Model::Render();
			}
			void AActor_Model::Delete() {
				this->Actor_Model::Delete();
				animation->Delete();
			}
			void AActor_Model::Refresh() {
				this->Actor_Model::Refresh();
			}
			void AActor_Model::Run_Animation() {
				animation->Change_Frame();
				this->Actor_Model::Model().Model_Mesh()->Change_Texture_Data(animation->Vertices());
			}
		// End of Class Members
		// Scene_Event             
		// Static Declarations      
		// Class Members           
			Scene_Event::Scene_Event(PW_SRD_PTR(Actor_Model) model_pointer, st::Event model_event) :
					model(model_pointer), model_event(model_event) {
			}
			Scene_Event::~Scene_Event() {
			}
			void Scene_Event::Run_Event() {
				model_event.Trigger_Event();
			}
			st::Event Scene_Event::Event() const {
				return model_event;
			}
			std::shared_ptr<Actor_Model> Scene_Event::Model() const {
				return model;
			}
		// End of Class Members
		// Game_Scene   
		// Static Declarations     
			int32_t Game_Scene::global_asset_count = 0;
			int32_t Game_Scene::global_actor_count = 0;
		// Class Members  
			Game_Scene::Game_Scene(const wchar_t* scene_name, std::vector<PW_SRD_PTR(Scene_Model)> scene_models, std::vector<PW_SRD_PTR(Actor_Model)> collision_models,
				co::Engine_Input* scene_input, Pysics_Factory* scene_physics) :
					scene_name{ scene_name }, scene_models{ scene_models }, collision_models{ collision_models },
					scene_input{ scene_input }, scene_events{}, current_scene_events{}, scene_physics{ scene_physics }, s_id_models{}, s_ids{} {
			}
			Game_Scene::~Game_Scene() {
			}
			void Game_Scene::Render() {
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
				if (scene_models.size() > 0) {
					for (size_t i = 0; i < scene_models.size(); i++) {
						scene_models.at(i)->Render();
					}
				}
			}
			void Game_Scene::Delete() {
				for (size_t i = 0; i < scene_models.size(); i++) {
					(*scene_models.at(i)).Delete();
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
					delete scene_input;
				}
				
				for (auto i = scene_events.begin(); i != scene_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							k->second.~Scene_Event();
						}
						j->second.clear();
					}
					i->second.clear();
				}
				scene_events.clear();

				for (size_t i = 0; i < current_scene_events.size(); i++) {
					current_scene_events.at(i) = nullptr;
				}
				current_scene_events.erase(current_scene_events.begin(), current_scene_events.end());
				current_scene_events.~vector();
				if (scene_physics != nullptr) {
					scene_physics->Delete();
					delete scene_physics;
				}
			}
			void Game_Scene::Refresh_Scene() {
				for (size_t i = 0; i < scene_models.size(); i++) {
					scene_models.at(i)->Refresh();
				}
			}
			void Game_Scene::Create_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state, PW_SRD_PTR(Actor_Model) model_pointer, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once) {
				if (scene_events.count(event_type) < 1) {
					std::map<PW_STATE, Scene_Event> state_event = std::map<PW_STATE, Scene_Event>();
					state_event.insert(std::make_pair(state, Scene_Event(model_pointer, st::Event(state, trigger_function, play_once))));

					std::map<PW_BUTTON_CODE, std::map<PW_STATE, Scene_Event>> button_event = std::map<PW_BUTTON_CODE, std::map<PW_STATE, Scene_Event>>();
					button_event.insert(std::make_pair(button, state_event));

					scene_events.insert(std::make_pair(event_type, button_event));
				}
				else {
					if (scene_events.at(event_type).count(button) < 1) {
						std::map<PW_STATE, Scene_Event> state_event = std::map<PW_STATE, Scene_Event>();
						state_event.insert(std::make_pair(state, Scene_Event(model_pointer, st::Event(state, trigger_function, play_once))));

						scene_events.at(event_type).insert(std::make_pair(button, state_event));
					}
					else {
						scene_events.at(event_type).at(button).insert(std::make_pair(state, Scene_Event(model_pointer, st::Event(state, trigger_function, play_once))));
					}
				}	
			}
			std::vector<PW_SRD_PTR(Scene_Model)> Game_Scene::Scene() const {
				return scene_models;
			}
			Pysics_Factory* Game_Scene::Scene_Physics() {
				return scene_physics;
			}
			PW_SRD_PTR(Actor_Model) Game_Scene::Access_Model(std::wstring s_id) {
				if (s_ids.find(s_id) != s_ids.end()) {
					for (auto i = s_id_models.begin(); i != s_id_models.end(); i++) {
						if (*i->get()->S_ID() == s_id) {
							return *i;
						}
					}
					return nullptr;
				}
				else {
					return nullptr;
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
										// Use algorithm to find if the click was within the model range
										glm::ivec2 point = glm::ivec2(cm::Engine_Constant::Mouse_X_Coord(), cm::Engine_Constant::Mouse_Y_Coord());

										std::shared_ptr<st::Mesh> mesh = i->second.at(state).Model().get()->Model().Model_Mesh();
										glm::ivec2 model_position = glm::ivec2(i->second.at(state).Model().get()->Model().Position().x, i->second.at(state).Model().get()->Model().Position().y);
										glm::ivec2 model_size = glm::ivec2(i->second.at(state).Model().get()->Model().Model_Size());
										std::vector<glm::ivec2> points{};

										for (size_t j = 0; j < mesh.get()->Vertex_Count(); j++) {
											points.push_back(glm::ivec2(
												// x
												model_position.x + (model_size.x * mesh.get()->Vertices()[j].Vertex_Position().x),
												// y
												model_position.y + (model_size.y * mesh.get()->Vertices()[j].Vertex_Position().y)
											));
										}
										int32_t j = mesh.get()->Vertex_Count();
										int32_t nvert = mesh.get()->Vertex_Count();
										bool c = false;

										for (int32_t k = 0, j = nvert - 1; k < nvert; j = k++) {
											if (((points[k].y > point.y) != (points[j].y > point.y)) &&
												(point.x < (points[j].x - points[k].x) * (point.y - points[k].y) / (points[j].y - points[k].y) + points[k].x)) {
												c = !c;
											}
										}
										if (c == true) {
											if (i->second.at(state).Event().Play_State() == true) {
												i->second.at(state).Run_Event();
											}
										}
									}
								}
							}
							break;
						}
						case cm::Engine_Constant::PW_HOVER_EVENT: {
							for (auto i = scene_events.at(event_type).begin(); i != scene_events.at(event_type).end(); i++) {
								// Use algorithm to find if the click was within the model range
								glm::ivec2 point = glm::ivec2(cm::Engine_Constant::Mouse_X_Coord(), cm::Engine_Constant::Mouse_Y_Coord());

								std::shared_ptr<st::Mesh> mesh = i->second.at(state).Model().get()->Model().Model_Mesh();
								glm::ivec2 model_position = glm::ivec2(i->second.at(state).Model().get()->Model().Position().x, i->second.at(state).Model().get()->Model().Position().y);
								glm::ivec2 model_size = glm::ivec2(i->second.at(state).Model().get()->Model().Model_Size());
								std::vector<glm::ivec2> points{};

								for (size_t j = 0; j < mesh.get()->Vertex_Count(); j++) {
									points.push_back(glm::ivec2(
										// x
										model_position.x + (model_size.x * mesh.get()->Vertices()[j].Vertex_Position().x),
										// y
										model_position.y + (model_size.y * mesh.get()->Vertices()[j].Vertex_Position().y)
									));
								}
								int32_t j = mesh.get()->Vertex_Count();
								int32_t nvert = mesh.get()->Vertex_Count();
								bool c = false;

								for (int32_t k = 0, j = nvert - 1; k < nvert; j = k++) {
									if (((points[k].y > point.y) != (points[j].y > point.y)) &&
										(point.x < (points[j].x - points[k].x) * (point.y - points[k].y) / (points[j].y - points[k].y) + points[k].x)) {
										c = !c;
									}
								}
								if (c == true) {
									if (i->second.at(state).Event().Play_State() == true) {
										i->second.at(state).Run_Event();
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
			void Game_Scene::Register_S_ID(std::wstring s_id, PW_SRD_PTR(Actor_Model) model) {
				if (s_ids.insert(s_id).second == true) {
					model.get()->Set_S_ID(s_id);
					s_id_models.push_back(model);
				}
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
