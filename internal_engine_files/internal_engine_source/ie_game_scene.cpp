#include "internal_engine_headers\ie_game_scene.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// Scene_Model         
		// Static Declarations    
		// Class Members        
			PW_VOID Scene_Model::Render() {
			}
			PW_VOID Scene_Model::Delete() {
			}
			PW_VOID Scene_Model::Refresh() {
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
			PW_VOID Asset_Model::Render() {
				model->Render();
			}
			PW_VOID Asset_Model::Delete() {
				model->Delete();
			}
			PW_VOID Asset_Model::Refresh() {
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
			PW_VOID AAsset_Model::Render() {
				Run_Animation();
				this->Asset_Model::Render();
			}
			PW_VOID AAsset_Model::Delete() {
				this->Asset_Model::Delete();
				animation->Delete();
			}
			PW_VOID AAsset_Model::Refresh() {
				this->Asset_Model::Refresh();
			}
			PW_VOID AAsset_Model::Run_Animation() {
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
					poly_body(nullptr), event_id(0) {
			}
			Actor_Model::Actor_Model(PW_SRD_PTR(Dynamic_Model) model) :
					model(model), poly_body(nullptr), event_id(0) {
			}
			Actor_Model::~Actor_Model() {
			}
			PW_VOID Actor_Model::Render() {
				model->Render(poly_body);
			}
			PW_VOID Actor_Model::Delete() {
				model->Delete();
				poly_body = nullptr;
			}
			PW_VOID Actor_Model::Refresh() {
				model->Refresh_Model();
			}
			PW_VOID Actor_Model::Set_Poly_Body(b2Body* poly_body) {
				this->poly_body = poly_body;
			}
			PW_VOID Actor_Model::Set_Event_ID(PW_ID id) {
				event_id = id;
			}
			PW_VOID Actor_Model::Increment_ID_Index() {
				global_index = global_index + 1;
			}
			Dynamic_Model& Actor_Model::Model() {
				return *model;
			}
			PW_ID Actor_Model::Event_ID() const {
				return event_id;
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
			PW_VOID AActor_Model::Render() {
				Run_Animation();
				this->Actor_Model::Render();
			}
			PW_VOID AActor_Model::Delete() {
				this->Actor_Model::Delete();
				animation->Delete();
			}
			PW_VOID AActor_Model::Refresh() {
				this->Actor_Model::Refresh();
			}
			PW_VOID AActor_Model::Run_Animation() {
				animation->Change_Frame();
				this->Actor_Model::Model().Model_Mesh()->Change_Texture_Data(animation->Vertices());
			}
		// End of Class Members
		// Scene_Event             
		// Static Declarations      
		// Class Members           
			Scene_Event::Scene_Event(PW_SRD_PTR(Actor_Model) model_pointer, Model_Event model_event) :
					model(model_pointer), model_event(model_event) {
			}
			Scene_Event::~Scene_Event() {
			}
			PW_VOID Scene_Event::Run_Event() {
				model_event.Trigger_Event();
			}
			Model_Event Scene_Event::Event() const {
				return model_event;
			}
			std::shared_ptr<Actor_Model> Scene_Event::Model() const {
				return model;
			}
		// End of Class Members
		// Scene_Player         
		// Static Declarations    
			Actor_Model Scene_Player::model;
			b2Body* Scene_Player::player_body;
		// Class Members 
			PW_VOID Scene_Player::Init_Player(PW_SRD_PTR(Dynamic_Model) player_model, b2Body* poly_body) {
				model = Actor_Model(player_model);
				model.Set_Poly_Body(poly_body);

				player_body = poly_body;
			}
			PW_VOID Scene_Player::Render() {
				model.Render();
			}
			PW_VOID Scene_Player::Delete() {
				model.Delete();
			}
			Actor_Model& Scene_Player::Model() {
				return model;
			}
		// End of Class Members
		// Game_Scene   
		// Static Declarations     
			Scene_Player Game_Scene::player;
			PW_INT Game_Scene::global_asset_count = 0;
			PW_INT Game_Scene::global_actor_count = 0;
		// Class Members  
			Game_Scene::Game_Scene(PW_CSTRING level_location) :
					scene_models{}, collision_models{}, scene_events{},
					current_scene_events{}, scene_physics{b2Vec2(Engine_Constant::Gravity().x, Engine_Constant::Gravity().y), 6, 2, 1.0f / (Engine_Constant::FPS_Max() / 3.0f)},
					order_number{ NULL } {
				if (level_location != NULL) {
					scene_models = this->Load_Scene_From_String(this->Load_Scene_From_File(level_location));
				}
			}
			Game_Scene::~Game_Scene() {
			}
			void Game_Scene::Render() {
				scene_physics.Run();

				if (current_scene_events.size() > 0) {
					for (auto it = current_scene_events.begin(); it != current_scene_events.end(); it++) {
						if ((*it) != NULL) {
							(*it)->Run_Event();
						}
					}
				}
				if (scene_models.size() > 0) {
					for (PW_SIZE i = 0; i < scene_models.size(); i++) {
						scene_models.at(i)->Render();
					}
				}
				player.Render();
			}
			void Game_Scene::Delete() {
				for (PW_SIZE i = 0; i < scene_models.size(); i++) {
					scene_models.at(i).~shared_ptr();
				}
				scene_models.erase(scene_models.begin(), scene_models.end());
				scene_models.~vector();
				for (PW_SIZE i = 0; i < collision_models.size(); i++) {
					collision_models.at(i) = nullptr;
				}
				collision_models.erase(collision_models.begin(), collision_models.end());
				collision_models.~vector();
				player.Delete();

				scene_physics.Delete();
			}
			PW_VOID Game_Scene::Refresh_Scene() {
				for (PW_SIZE i = 0; i < scene_models.size(); i++) {
					scene_models.at(i)->Refresh();
				}
			}
			std::vector<PW_SRD_PTR(Scene_Model)> Game_Scene::Load_Scene_From_String(PW_STRING scene_str) {
				std::vector<PW_SRD_PTR(Scene_Model)> models;
				PW_SIZE index_front = 0;
				PW_SIZE index_back = 0;
				PW_SIZE index_prevf = 0;
				PW_SIZE index_prevb = 0;
				PW_STRING str = "";
				PW_STRING str2 = "";
				//Get order
				index_front = scene_str.find("*");
				index_back = scene_str.find("*", index_front + 1);
				str = scene_str.substr(index_front + 1, index_back - index_front - 1);
				if (str != "") {
					order_number = std::stoi(str);
				}
				else {
					std::cout << "ERROR";
				}

				while (scene_str.empty() != true) {
					index_front = 0;
					index_back = 0;
					index_prevf = 0;
					index_prevb = 0;
					str = "";
					str2 = "";
					if (scene_str.at(0) == '/') {
						index_back = scene_str.find(")", 0);
						scene_str.erase(0, index_back + 1);
						continue;
					}
					//Get the texture data
					index_front = scene_str.find("[");
					index_back = scene_str.find("-", index_front);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					index_front = index_back;
					index_back = scene_str.find("]");
					str2 = scene_str.substr(index_front + 1, index_back - index_front - 1);
					Texture texture;
					glm::vec3 model_color(1.0f);
					if (str == "D16" || str == "D32" || str == "D64") {
						str = Texture::Find_Color_Texture(str.c_str(), (Texture::Default_Texture)std::stoi(str2.c_str()), model_color);
						texture = Texture(str.c_str());
					}
					else {
						index_front = scene_str.find("[");
						index_back = scene_str.find("]", index_front);
						str = scene_str.substr(index_front + 1, index_back - index_front - 1);
						str2 = Texture::Find_Texture(str.c_str());
						texture = Texture(str2.c_str());
						model_color = glm::vec3(-1.0f);
					}
					str.clear();
					str2.clear();
					//Find out if it has animation data
					PW_INT boolean_expression = 0;
					PW_BOOL animated = false;
					PW_FLOAT animation_length = 0.0f;
					PW_UINT animation_frames = 0;
					PW_UINT animation_size_x = 0;

					index_prevb = index_back;

					index_front = scene_str.find("[", index_prevb);
					index_back = scene_str.find("=", index_front);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					boolean_expression = std::stoi(str);
					if (boolean_expression == 1) {
						animated = true;
					}
					str.clear();
					if (animated == true) {
						index_front = index_back;
						index_back = scene_str.find(",", index_front);
						str = scene_str.substr(index_front + 1, index_back - index_front - 1);
						animation_length = std::stof(str);
						index_front = index_back;
						index_back = scene_str.find(",", index_front + 1);
						str = scene_str.substr(index_front + 1, index_back - index_front - 1);
						animation_frames = std::stoi(str);
						index_front = index_back;
						index_back = scene_str.find("=", index_front + 1);
						str = scene_str.substr(index_front + 1, index_back - index_front - 1);
						animation_size_x = std::stoi(str);
						str.clear();
					}
					//Find out if it has collision data
					boolean_expression = 0;
					PW_BOOL collidable = false;

					index_prevb = index_back;

					index_front = scene_str.find("[", index_prevb);
					index_back = scene_str.find("]", index_front);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					boolean_expression = std::stoi(str);
					if (boolean_expression == 1) {
						collidable = true;
					}
					str.clear();
					//Get the model data
					PW_INT model_type = 0;
					glm::vec2 position(1.0f);
					PW_FLOAT rotation = 0.0f;
					glm::vec2 size(1.0f);
					//Model Type
					index_prevb = index_back;

					index_front = scene_str.find("(", index_prevb);
					index_back = scene_str.find(",", index_prevb);
					index_prevb = index_back;
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					model_type = std::stoi(str.c_str());
					str.clear();
					//Model Position
					index_front = scene_str.find("=", index_prevb + 1);
					index_prevf = index_front;
					index_back = scene_str.find(",", index_prevb + 1);
					index_prevb = index_back;
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					position.x = std::stof(str.c_str()) * 32.0f;
					str.clear();
					index_front = index_back;
					index_back = scene_str.find("=", index_prevf + 1);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					position.y = std::stof(str.c_str()) * 32.0f;
					str.clear();
					//Model Rotation
					index_front = scene_str.find(",", index_prevb + 1);
					index_prevf = index_front;
					index_back = scene_str.find(",", index_prevf + 1);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					rotation = std::stof(str.c_str());
					str.clear();
					//Model Size
					index_front = scene_str.find("=", index_prevf);
					index_prevf = index_front;
					index_back = scene_str.find(",", index_prevf + 1);
					index_prevb = index_back;
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					size.x = std::stof(str.c_str());
					str.clear();
					index_front = index_back;
					index_back = scene_str.find("=", index_prevf + 1);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					size.y = std::stof(str.c_str());
					str.clear();
					index_front = index_back;
					index_back = scene_str.find(")", index_prevf + 1);
					str = scene_str.substr(index_front + 1, index_back - index_front - 1);
					PW_CHAR type = str.at(0);
					str.clear();
					PW_SRD_PTR(Scene_Model) scene_model{ NULL };
					if (type == 'd') {
						global_actor_count = global_actor_count + 1;
						if (model_color.x != -1.0f) {
							PW_SRD_PTR(Dynamic_Model) model = std::make_shared<Dynamic_Model>(
								(Model_Types)model_type,
								texture, position, rotation, size, model_color);
							if (collidable == true) {
								if (animated == true) {
									PW_SRD_PTR(Animation) animation = std::make_shared<Animation>(
										animation_length, animation_frames, animation_size_x,
										model->Model_Mesh()->Vertices(),
										model->Model_Mesh()->Vertex_Count());
									PW_SRD_PTR(AActor_Model) aactor_model = std::make_shared<AActor_Model>(model, animation);

									collision_models.push_back(static_cast<PW_SRD_PTR(Actor_Model)>(aactor_model));

									scene_physics.Add_Object(model, b2_staticBody);
									if (scene_physics.Current_Rect() == true) {
										static_cast<PW_SRD_PTR(Actor_Model)>(aactor_model)->Set_Poly_Body(nullptr);
									}
									else {
										static_cast<PW_SRD_PTR(Actor_Model)>(aactor_model)->Set_Poly_Body(scene_physics.Last_Added_Body());
									}
									scene_model = aactor_model;
								}
								else {
									PW_SRD_PTR(Actor_Model) actor_model = std::make_shared<Actor_Model>(model);

									collision_models.push_back(actor_model);

									scene_physics.Add_Object(model, b2_staticBody);
									if (scene_physics.Current_Rect() == true) {
										actor_model->Set_Poly_Body(nullptr);
									}
									else {
										actor_model->Set_Poly_Body(scene_physics.Last_Added_Body());
									}
									scene_model = actor_model;
								}
							}
							else {
								if (animated == true) {
									PW_SRD_PTR(Animation) animation = std::make_shared<Animation>(
										animation_length, animation_frames, animation_size_x,
										model->Model_Mesh()->Vertices(),
										model->Model_Mesh()->Vertex_Count());
									PW_SRD_PTR(AActor_Model) aactor_model = std::make_shared<AActor_Model>(model, animation);
									scene_model = aactor_model;
								}
								else {
									PW_SRD_PTR(Actor_Model) actor_model = std::make_shared<Actor_Model>(model);
									scene_model = actor_model;
								}
							}
						}
						else {
							PW_SRD_PTR(Dynamic_Model) model =  std::make_shared<Dynamic_Model>(
								(Model_Types)model_type,
								texture, position, rotation, size);
							if (collidable == true) {
								if (animated == true) {
									PW_SRD_PTR(Animation) animation = std::make_shared<Animation>(
										animation_length, animation_frames, animation_size_x,
										model->Model_Mesh()->Vertices(),
										model->Model_Mesh()->Vertex_Count());
									PW_SRD_PTR(AActor_Model) aactor_model = std::make_shared<AActor_Model>(model, animation);

									collision_models.push_back(static_cast<PW_SRD_PTR(Actor_Model)>(aactor_model));

									scene_physics.Add_Object(model, b2_staticBody);
									if (scene_physics.Current_Rect() == true) {
										static_cast<PW_SRD_PTR(Actor_Model)>(aactor_model)->Set_Poly_Body(nullptr);
									}
									else {
										static_cast<PW_SRD_PTR(Actor_Model)>(aactor_model)->Set_Poly_Body(scene_physics.Last_Added_Body());
									}
									scene_model = aactor_model;
								}
								else {
									PW_SRD_PTR(Actor_Model) actor_model = std::make_shared<Actor_Model>(model);
								
									collision_models.push_back(actor_model);

									scene_physics.Add_Object(model, b2_staticBody);
									if (scene_physics.Current_Rect() == true) {
										actor_model->Set_Poly_Body(nullptr);
									}
									else {
										actor_model->Set_Poly_Body(scene_physics.Last_Added_Body());
									}
									scene_model = actor_model;
								}
							}
							else {
								if (animated == true) {
									PW_SRD_PTR(Animation) animation = std::make_shared<Animation>(
										animation_length, animation_frames, animation_size_x,
										model->Model_Mesh()->Vertices(),
										model->Model_Mesh()->Vertex_Count());
									PW_SRD_PTR(AActor_Model) aactor_model = std::make_shared<AActor_Model>(model, animation);

									scene_model = aactor_model;
								}
								else {
									PW_SRD_PTR(Actor_Model) actor_model = std::make_shared<Actor_Model>(model);

									scene_model = actor_model;
								}
							}
						}
					}
					else {
						global_asset_count = global_asset_count + 1;
						if (model_color.x != -1.0f) {
							PW_SRD_PTR(Static_Model) model = std::make_shared<Static_Model>(
								(Model_Types)model_type,
								texture, position, rotation, size, model_color);
							if (model == NULL) {
								continue;
							}
							if (animated == true) {
								PW_SRD_PTR(Animation) animation = std::make_shared<Animation>(
									animation_length, animation_frames, animation_size_x,
									model->Model_Mesh()->Vertices(),
									model->Model_Mesh()->Vertex_Count());
								PW_SRD_PTR(AAsset_Model) aasset_model = std::make_shared<AAsset_Model>(model, animation);
								scene_model = aasset_model;
							}
							else {
								PW_SRD_PTR(Asset_Model) asset_model = std::make_shared<Asset_Model>(model);
								scene_model = asset_model;
							}
						}
						else {
							PW_SRD_PTR(Static_Model) model = std::make_shared<Static_Model>(
								(Model_Types)model_type,
								texture, position, rotation, size);

							if (animated == true) {
								PW_SRD_PTR(Animation) animation = std::make_shared<Animation>(
									animation_length, animation_frames, animation_size_x,
									model->Model_Mesh()->Vertices(),
									model->Model_Mesh()->Vertex_Count());
								PW_SRD_PTR(AAsset_Model) aasset_model = std::make_shared<AAsset_Model>(model, animation);
								scene_model = aasset_model;
							}
							else {
								PW_SRD_PTR(Asset_Model) asset_model = std::make_shared<Asset_Model>(model);
								scene_model = asset_model;
							}
						}
					}
					models.push_back(scene_model);
					index_back = scene_str.find(")");
					scene_str.erase(0, index_back + 1);
				}
				scene_str.clear();
				printf("Actor Models: %d\n", global_actor_count);
				printf("Asset Models: %d\n", global_asset_count);
				printf("Global Total: %d\n", global_actor_count + global_asset_count);
				return models;
			}
			PW_STRING Game_Scene::Load_Scene_From_File(PW_CSTRING file_location) {
				PW_STRING content = "";
				std::ifstream fileStream(file_location, std::ios::in);

				if (!fileStream.is_open()) {
					printf("Scene File: %s did not open\n", file_location);
					return "";
				}

				PW_STRING line = "";
				while (!fileStream.eof()) {
					std::getline(fileStream, line);
					content.append(line);
				}
				fileStream.close();
				return content;
			}
			PW_VOID Game_Scene::Create_Event(PW_ID event_type, PW_SRD_PTR(Actor_Model) model_pointer, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once) {
				if (scene_events.count(event_type) < 1) {
					std::map<PW_ID, Scene_Event> map = std::map<PW_ID, Scene_Event>();
					if (model_pointer->Event_ID() == 0) {
						model_pointer->Set_Event_ID(model_pointer->Global_ID() + 1);
						Actor_Model::Increment_ID_Index();
					}
					switch (event_type) {
						case Engine_Constant::PW_COLLISION_EVENT: {
							map.insert(std::make_pair(model_pointer->Event_ID(), Scene_Event(model_pointer, Collision_Event(trigger_function, play_once))));
							scene_events.insert(std::make_pair(event_type, map));
							break;
						}
						default: {
							break;
						}
					}
				}
				else {
					if (model_pointer->Event_ID() == 0) {
						model_pointer->Set_Event_ID(model_pointer->Global_ID() + 1);
						Actor_Model::Increment_ID_Index();
					}
					switch (event_type) {
						case Engine_Constant::PW_COLLISION_EVENT: {
							scene_events.at(event_type).insert(std::make_pair(event_type, Scene_Event(model_pointer, Collision_Event(trigger_function, play_once))));
							break;
						}
						default: {
							break;
						}
					}
				}	
			}
			PW_VOID Game_Scene::Set_Order_Number(PW_UINT new_order_number) {

				order_number = new_order_number;
			}
			PW_UINT Game_Scene::Order_Number() const {
				return order_number;
			}
			std::vector<PW_SRD_PTR(Scene_Model)> Game_Scene::Scene() const {
				return scene_models;
			}
			Pysics_Factory* Game_Scene::Scene_Physics() {
				return &scene_physics;
			}
			Scene_Player Game_Scene::Player() {
				return player;
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
