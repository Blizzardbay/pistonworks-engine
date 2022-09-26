#include "engine_structures\engine_game_scene.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Actor            
		// Static Declarations     
			PW_ID Actor::m_global_index = 0;
		// Class Members
			Actor::Actor() :
					m_model{ nullptr }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ nullptr }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ 0 } {
			}
			Actor::Actor(st::Model* p_model, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ nullptr }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ p_layer } {
			}
			Actor::Actor(st::Model* p_model, st::Text* p_text, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ nullptr }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ p_text }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ p_layer } {
			}
			Actor::Actor(st::Model* p_model, st::Texture_Structure* p_multi_texture, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ p_multi_texture }, m_sound_deposit{ nullptr }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ p_layer } {
			}
			Actor::Actor(st::Model* p_model, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ p_sound_deposit }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ p_layer } {
				if (m_sound_deposit->All_Sounds() != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Attach(std::bind(&st::Model::Calculate_Center, m_model));
					}
				}
			}
			Actor::Actor(st::Model* p_model, st::Text* p_text, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ p_sound_deposit }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ p_text }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ p_layer } {
				if (m_sound_deposit->All_Sounds() != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Attach(std::bind(&st::Model::Calculate_Center, m_model));
					}
				}
			}
			Actor::Actor(st::Model* p_model, st::Texture_Structure* p_multi_texture, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ p_multi_texture }, m_sound_deposit{ p_sound_deposit }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ nullptr }, m_animations{ nullptr }, m_layer{ p_layer } {
				if (m_sound_deposit->All_Sounds() != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Attach(std::bind(&st::Model::Calculate_Center, m_model));
					}
				}
			}
			Actor::Actor(st::Model* p_model, st::Animation* p_animation, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ nullptr }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ p_animation }, m_animations{ nullptr }, m_layer{ p_layer } {
			}
			Actor::Actor(st::Model* p_model, const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ nullptr }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ p_animations.front()._Myfirst._Val },
					m_animations{ pw::Engine_Memory::Allocate<st::Animation_Structure, bool>(p_animations, p_animation_ids) },
					m_layer{ p_layer } {
			}
			Actor::Actor(st::Model* p_model, st::Animation* p_animation, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ p_sound_deposit }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ p_animation }, m_animations{ nullptr }, m_layer{ p_layer } {
				if (m_sound_deposit->All_Sounds() != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Attach(std::bind(&st::Model::Calculate_Center, m_model));
					}
				}
			}
			Actor::Actor(st::Model* p_model, const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer) :
					m_model{ p_model }, m_body{ nullptr }, m_multi_texture{ nullptr }, m_sound_deposit{ p_sound_deposit }, m_is_rendered{ false }, m_render_toggle{ true }, m_s_id{},
					m_text{ nullptr }, m_current_animation{ p_animations.front()._Myfirst._Val },
					m_animations{ pw::Engine_Memory::Allocate<st::Animation_Structure, bool>(p_animations, p_animation_ids) },
					m_layer{ p_layer } {
				if (m_sound_deposit->All_Sounds() != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Attach(std::bind(&st::Model::Calculate_Center, m_model));
					}
				}
			}
			Actor::~Actor() {
				if (pw::Engine_Memory::Deallocate<st::Model>(m_model) == false) {
					if (m_model != nullptr) {
						delete m_model;
						m_model = nullptr;
					}
				}
				m_body = nullptr;
				if (pw::Engine_Memory::Deallocate<st::Texture_Structure>(m_multi_texture) == false) {
					if (m_multi_texture != nullptr) {
						delete m_multi_texture;
						m_multi_texture = nullptr;
					}
				}
				if (pw::Engine_Memory::Deallocate<st::Sound_Structure>(m_sound_deposit) == false) {
					if (m_sound_deposit != nullptr) {
						delete m_sound_deposit;
						m_sound_deposit = nullptr;
					}
				}
				if (pw::Engine_Memory::Deallocate<st::Text>(m_text) == false) {
					if (m_text != nullptr) {
						delete m_text;
						m_text = nullptr;
					}
				}
				if (pw::Engine_Memory::Deallocate<st::Animation_Structure>(m_animations) == false) {
					if (m_animations != nullptr) {
						delete m_animations;
						m_animations = nullptr;
					}
				}
				if (m_animations == nullptr) {
					if (pw::Engine_Memory::Deallocate<st::Animation>(m_current_animation) == false) {
						if (m_current_animation != nullptr) {
							delete m_current_animation;
							m_current_animation = nullptr;
						}
					}
				}
			}
			void Actor::Render() {
				if (m_current_animation != nullptr) {
					Run_Animation();
				}
				if (m_text != nullptr) {
					m_text->Render();
					if (m_model != nullptr) {
						if (m_body != nullptr) {
							m_model->Render(m_body->Body(), 1);
						}
						else {
							m_model->Render();
						}
					}
				}
				else {
					if (m_model != nullptr) {
						if (m_body != nullptr) {
							m_model->Render(m_body->Body(), 0);
						}
						else {
							m_model->Render();
						}
					}
				}
				if (m_sound_deposit != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Update();
					}
				}
			}
			void Actor::Play_Sound(std::wstring p_sound_s_id, bool p_reset_play) {
				if (m_sound_deposit != nullptr) {
					if (m_sound_deposit->Sound(std::move(p_sound_s_id)) != nullptr) {
						m_sound_deposit->Sound(std::move(p_sound_s_id))->Play(p_reset_play);
					}
				}
			}
			void Actor::Pause_Sound(std::wstring p_sound_s_id) {
				if (m_sound_deposit != nullptr) {
					if (m_sound_deposit->Sound(std::move(p_sound_s_id)) != nullptr) {
						m_sound_deposit->Sound(std::move(p_sound_s_id))->Pause();
					}
				}
			}
			void Actor::Stop_Sound(std::wstring p_sound_s_id) {
				if (m_sound_deposit != nullptr) {
					if (m_sound_deposit->Sound(std::move(p_sound_s_id)) != nullptr) {
						m_sound_deposit->Sound(std::move(p_sound_s_id))->Stop();
					}
				}
			}
			void Actor::Reset_Sound(std::wstring p_sound_s_id) {
				if (m_sound_deposit != nullptr) {
					if (m_sound_deposit->Sound(std::move(p_sound_s_id)) != nullptr) {
						m_sound_deposit->Sound(std::move(p_sound_s_id))->Reset();
					}
				}
			}
			void Actor::Pause_All_Sounds() {
				if (m_sound_deposit != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Pause();
					}
				}
			}
			void Actor::Stop_All_Sounds() {
				if (m_sound_deposit != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Stop();
					}
				}
			}
			void Actor::Reset_All_Sounds() {
				if (m_sound_deposit != nullptr) {
					for (auto i = m_sound_deposit->All_Sounds()->begin(); i != m_sound_deposit->All_Sounds()->end(); i++) {
						i->second->Reset();
					}
				}
			}
			void Actor::Change_Volume(std::wstring p_sound_s_id, float p_new_volume, bool windows_style) {
				if (m_sound_deposit != nullptr) {
					if (m_sound_deposit->Sound(p_sound_s_id) != nullptr) {
						m_sound_deposit->Sound(p_sound_s_id)->Set_Volume(p_new_volume, windows_style);
					}
				}
			}
			void Actor::Run_Animation() {
				if (m_current_animation != nullptr) {
					m_current_animation->Change_Frame();
					m_model->Mesh()->Change_Texture_Data(m_current_animation->Vertices());
				}
			}
			void Actor::Advance_Animation() {
				if (m_current_animation != nullptr) {
					m_current_animation->Advance_Frame();
					m_model->Mesh()->Change_Texture_Data(m_current_animation->Vertices());
				}
			}
			void Actor::Start_Animation() {
				if (m_current_animation != nullptr) {
					m_current_animation->Start_Animation();
				}
			}
			void Actor::Stop_Animation() {
				if (m_current_animation != nullptr) {
					m_current_animation->Stop_Animation();
				}
			}
			void Actor::Change_Animation(std::wstring p_animation_id, bool p_reset) {
				if (m_current_animation != nullptr) {
					if (p_animation_id != L"") {
						if (m_current_animation != m_animations->Animation(p_animation_id.c_str())._Myfirst._Val) {
							m_current_animation = m_animations->Animation(p_animation_id.c_str())._Myfirst._Val;
							m_model->Set_Texture(m_animations->Animation(p_animation_id.c_str())._Get_rest()._Myfirst._Val);
							if (p_reset == true) {
								m_current_animation->Reset_Animation();
							}
						}
					}
				}
			}
			bool Actor::Test_Collision(st::Actor* p_other_model) {
				if (m_body != nullptr) {
					if (m_body->Body() != nullptr) {
						if (p_other_model != nullptr) {
							if (p_other_model->Physics_Object() != nullptr) {
								if (p_other_model->Physics_Object()->Body() != nullptr) {
									return b2TestOverlap(m_body->Body()->GetFixtureList()->GetShape(), 0,
										p_other_model->Physics_Object()->Body()->GetFixtureList()->GetShape(), 0,
										m_body->Body()->GetTransform(), p_other_model->Physics_Object()->Body()->GetTransform());
								}
							}
						}
					}
				}
				return false;
			}
			void Actor::Set_Physics_Object(st::Physics_Object* p_body) {
				m_body = p_body;
			}
			void Actor::Set_S_ID(const std::wstring& p_s_id) {
				m_s_id = p_s_id;
			}
			void Actor::Set_Texture(std::wstring p_s_id) {
				if (m_multi_texture != nullptr) {
					st::Texture* v_temp_texture = m_multi_texture->Texture(std::move(p_s_id));
					if (m_model->Texture() != v_temp_texture) {
						m_model->Set_Texture(v_temp_texture);
					}
				}
			}
			void Actor::Set_Render_State(const bool& p_state) {
				m_is_rendered = p_state;
			}
			void Actor::Set_Size_X(const float& p_size_x) {
				m_model->Set_Size_X(p_size_x);

				if (m_body != nullptr) {
					m_body->Set_Size_Px(m_model->Size());
				}
			}
			void Actor::Set_Size_Y(const float& p_size_y) {
				m_model->Set_Size_Y(p_size_y);

				if (m_body != nullptr) {
					m_body->Set_Size_Px(m_model->Size());
				}
			}
			void Actor::Set_Size(const glm::vec2& p_size_px) {
				m_model->Set_Size(p_size_px);

				if (m_body != nullptr) {
					m_body->Set_Size_Px(m_model->Size());
				}
			}
			void Actor::Set_Text(std::wstring p_new_text) {
				if (m_text != nullptr) {
					m_text->Set_Text(p_new_text);
					m_model->Set_Size(m_text->Size());
				}
			}
			void Actor::Set_Text_Color(glm::vec4 p_color) {
				if (m_text != nullptr) {
					m_text->Set_Text_Color(p_color);
				}
			}
			void Actor::Set_Color(glm::vec4 p_color) {
				if (m_model != nullptr) {
					m_model->Set_Model_Color(p_color);
				}
			}
			void Actor::Toggle_Render() {
				m_render_toggle = !m_render_toggle;
			}
			void Actor::Set_Render_Toggle(const bool& p_state) {
				m_render_toggle = p_state;
			}
			st::Model* Actor::Model() const {
				return m_model;
			}
			st::Physics_Object* Actor::Physics_Object() const {
				return m_body;
			}
			st::Texture_Structure* Actor::Multi_Texture() const {
				return m_multi_texture;
			}
			st::Sound_Structure* Actor::Sound_Structure() const {
				return m_sound_deposit;
			}
			const bool& Actor::Is_Rendered() const {
				return m_is_rendered;
			}
			const bool& Actor::Render_Toggle() const {
				return m_render_toggle;
			}
			const std::wstring& Actor::S_Id() const {
				return m_s_id;
			}
			st::Text* Actor::Text() const {
				return m_text;
			}
			st::Animation* Actor::Animation() const {
				return m_current_animation;
			}
			st::Animation_Structure* Actor::Animation_Structure() const {
				return m_animations;
			}
			const int32_t& Actor::Layer() const {
				return m_layer;
			}
			void Actor::Increment_ID_Index() {
				m_global_index = m_global_index + 1;
			}
			const PW_ID& Actor::Global_ID() {
				return m_global_index;
			}
			bool Compare_Layer(st::Actor* lhs, st::Actor* rhs) {
				return lhs->Layer() < rhs->Layer();
			}
		// End of Class Members
		// Scene_Event
			Scene_Event::Scene_Event(st::Actor* p_model_pointer, st::Event_Base* p_model_event) :
					m_model{ p_model_pointer }, m_model_event{ p_model_event } {
			}
			Scene_Event::~Scene_Event() {
				m_model = nullptr;
				if (pw::Engine_Memory::Deallocate<st::Event_Base>(m_model_event) == false) {
					if (m_model_event != nullptr) {
						delete m_model_event;
						m_model_event = nullptr;
					}
				}
			}
			void Scene_Event::Run_Event() {
				m_model_event->Trigger_Event();
			}
			st::Event_Base* Scene_Event::Event() const {
				return m_model_event;
			}
			st::Actor* Scene_Event::Model() const {
				return m_model;
			}
		// Sub_Scene_Structure   
		// Static Declarations     
		// Class Members
			Sub_Scene_Structure::Sub_Scene_Structure() :
					m_sub_scene_id{}, m_scene_repository{}, m_should_render{ false }, m_is_rendered{ false } {
			}
			Sub_Scene_Structure::Sub_Scene_Structure(const std::wstring& p_sub_scene_id, const std::vector<st::Actor*>& p_scene_repository, const bool& p_should_render) :
					m_sub_scene_id{ p_sub_scene_id }, m_scene_repository { p_scene_repository }, m_should_render{ p_should_render }, m_is_rendered{ false } {
				// Attach any layer 4+ models to the camera relative to its position
				for (size_t i = 0; i < m_scene_repository.size(); i++) {
					st::Actor* v_temp = m_scene_repository.at(i);

					if (v_temp->Layer() >= 4) {
						glm::vec2 v_origin = v_temp->Model()->Position();

						v_temp->Model()->Set_Position(st::Camera::Camera_Position());

						v_temp->Model()->Set_Offset(glm::vec2(v_origin.x, v_origin.y - (float)pw::cm::Engine_Constant::Window_Height()));

						if (v_temp->Text() != nullptr) {
							v_temp->Text()->Set_Position(st::Camera::Camera_Position());

							v_temp->Text()->Set_Offset(glm::vec3(v_origin.x, v_origin.y - (float)pw::cm::Engine_Constant::Window_Height(), 0.0f));
						}
					}
				}
			}
			Sub_Scene_Structure::~Sub_Scene_Structure() {
				for (auto i = m_scene_repository.begin(); i != m_scene_repository.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Actor>(*i) == false) {
						if (*i != nullptr) {
							delete *i;
							*i = nullptr;
						}
					}
				}
			}
			void Sub_Scene_Structure::Pre_Render(quadtree::Quadtree<st::Actor*, std::function<quadtree::Box<float>(st::Actor*)>>& p_quadtree_renderer) {
				m_is_rendered = true;

				for (size_t i = 0; i < m_scene_repository.size(); i++) {
					st::Actor* v_temp = m_scene_repository.at(i);

					v_temp->Set_Render_State(false);
				}


				for (size_t i = 0; i < m_scene_repository.size(); i++) {
					p_quadtree_renderer.add(m_scene_repository.at(i));
				}
			}
			void Sub_Scene_Structure::De_Render(quadtree::Quadtree<st::Actor*, std::function<quadtree::Box<float>(st::Actor*)>>& p_quadtree_renderer) {
				m_is_rendered = false;

				for (size_t i = 0; i < m_scene_repository.size(); i++) {
					st::Actor* v_temp = m_scene_repository.at(i);

					v_temp->Set_Render_State(false);
				}

				for (size_t i = 0; i < m_scene_repository.size(); i++) {
					p_quadtree_renderer.remove(m_scene_repository.at(i));
				}
			}
			void Sub_Scene_Structure::Set_Render_State(const bool& p_is_rendering) {
				m_is_rendered = p_is_rendering;
			}
			void Sub_Scene_Structure::Set_Render_Toggle(bool p_render_structure) {
				m_should_render = p_render_structure;
			}
			void Sub_Scene_Structure::Push_Screen_Models(std::vector<st::Actor*>& p_screen_models) {
				for (size_t i = 0; i < m_scene_repository.size(); i++) {
					st::Actor* v_temp = m_scene_repository.at(i);

					if (v_temp->Layer() >= 4) {
						p_screen_models.push_back(v_temp);
					}
				}
			}
			const bool& Sub_Scene_Structure::Is_Rendered() {
				return m_is_rendered;
			}
			const bool& Sub_Scene_Structure::Should_Render() {
				return m_should_render;
			}
			std::vector<st::Actor*>& Sub_Scene_Structure::Scenes() {
				return m_scene_repository;
			}
			const std::wstring& Sub_Scene_Structure::Sub_Scene_Id() {
				return m_sub_scene_id;
			}
		// End of Class Members
		// Game_Scene   
		// Static Declarations     
			int32_t Game_Scene::m_global_actor_count = 0;
		// Class Members
			Game_Scene::Game_Scene() :
					m_scene_name{}, m_main_scene_models{}, m_collision_models{},
					m_scene_input{}, m_scene_events{}, m_scene_id_counter{ 0 }, m_active_scene_events{}, m_scene_physics{ nullptr }, s_id_models{}, m_render_queue{}, m_screen_models{}, m_last_render_count{ 0 }, m_re_render{ true },
					m_camera_position_instance{ st::Camera::Camera_Position() },
					m_body_models{}, m_async_animations{}, m_current_scene_collision_events{},
					m_quadtree_render_box{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, 2.0f * (float)INT32_MAX, 2.0f * (float)INT32_MAX} },
					m_quadtree_renderer{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, 2.0f * (float)INT32_MAX, 2.0f * (float)INT32_MAX},
					Game_Scene::Get_Box }, m_sub_scene_deposit{}, m_listener_id{}, m_current_scene_input{ nullptr }, m_current_scene_events{ nullptr }, m_scene_alt_events{}, m_current_scene_alt_events{nullptr},
					m_new_input{false} {
			}
			Game_Scene::Game_Scene(const std::wstring& p_scene_name, const std::vector<st::Actor*>& p_scene_models, const std::vector<st::Actor*>& p_collision_models,
				const std::map<std::wstring, co::Engine_Input*>& p_scene_input, st::Physics_Factory* p_scene_physics,
				const std::map<std::wstring, st::Sub_Scene_Structure*>& p_sub_scene_deposit, const std::wstring& p_listener_id) :
					m_scene_name{ p_scene_name }, m_main_scene_models{ p_scene_models }, m_collision_models{ p_collision_models },
					m_scene_input{ p_scene_input }, m_scene_events{}, m_scene_id_counter{ 0 }, m_active_scene_events{}, m_scene_physics{ p_scene_physics }, s_id_models{}, m_render_queue{}, m_screen_models{}, m_last_render_count{ 0 }, m_re_render{ true },
					m_camera_position_instance{ st::Camera::Camera_Position() },
					m_body_models{}, m_async_animations{},
					m_quadtree_render_box{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, 2.0f * (float)INT32_MAX, 2.0f * (float)INT32_MAX} },
					m_quadtree_renderer{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, 2.0f * (float)INT32_MAX, 2.0f * (float)INT32_MAX},
					Game_Scene::Get_Box }, m_sub_scene_deposit{ p_sub_scene_deposit }, m_listener_id{ p_listener_id }, m_current_scene_input{ nullptr }, m_current_scene_events{ nullptr }, m_scene_alt_events{},
					m_current_scene_alt_events{ nullptr }, m_current_scene_collision_events{},
					m_new_input{ false } {
				// Put models into the different quad-trees

				for (size_t i = 0; i < m_main_scene_models.size(); i++) {
					m_quadtree_renderer.add(m_main_scene_models.at(i));
				}
				// Attach any layer 4+ models to the camera relative to its position
				for (size_t i = 0; i < m_main_scene_models.size(); i++) {
					st::Actor* v_temp = m_main_scene_models.at(i);

					if (v_temp->Layer() >= 4) {
						glm::vec2 v_origin = v_temp->Model()->Position();

						v_temp->Model()->Set_Position(st::Camera::Camera_Position());

						v_temp->Model()->Set_Offset(glm::vec2(v_origin.x, v_origin.y - (float)pw::cm::Engine_Constant::Window_Height()));

						if (v_temp->Text() != nullptr) {
							v_temp->Text()->Set_Offset(st::Camera::Camera_Position());
						}
						m_screen_models.push_back(v_temp);
					}
				}

				// Stores unsorted models for callback
				for (auto i = m_collision_models.begin(); i != m_collision_models.end(); i++) {
					m_body_models.insert(std::make_pair((*i)->Physics_Object(), *i));
				}
				// Stores the sorted collision models
				std::vector<st::Actor*> v_collision_models{};
				// Find out which models have collision events
				for (auto i = m_collision_models.begin(); i != m_collision_models.end(); i++) {
					// Test for body
					if ((*i)->Physics_Object() != nullptr) {
						if ((*i)->Physics_Object()->Body() != nullptr) {
							// Test for id
							if ((*i)->S_Id().empty() != true) {
								v_collision_models.push_back(*i);
							}
						}
					}
				}
				m_collision_models.clear();
				m_collision_models.insert(m_collision_models.begin(), v_collision_models.begin(), v_collision_models.end());

				for (auto i = m_sub_scene_deposit.begin(); i != m_sub_scene_deposit.end(); i++) {
					i->second->Push_Screen_Models(m_screen_models);
				}

				// Fill the async animation vector for use
				for (size_t i = 0; i < m_main_scene_models.size(); i++) {
					if (m_main_scene_models.at(i)->Animation_Structure() != nullptr) {
						for (auto j = m_main_scene_models.at(i)->Animation_Structure()->Animations().begin(); j != m_main_scene_models.at(i)->Animation_Structure()->Animations().end(); j++) {
							if (std::get<0>(j->second)->Is_Async() == true) {
								auto k = m_async_animations.find(std::get<0>(j->second));
								if (k == m_async_animations.end()) {
									m_async_animations.insert(std::make_pair(std::get<0>(j->second), std::get<0>(j->second)));
								}
							}
						}
					}
					else {
						if (m_main_scene_models.at(i)->Animation() != nullptr) {
							if (m_main_scene_models.at(i)->Animation()->Is_Async() == true) {
								auto k = m_async_animations.find(m_main_scene_models.at(i)->Animation());
								if (k == m_async_animations.end()) {
									m_async_animations.insert(std::make_pair(m_main_scene_models.at(i)->Animation(), m_main_scene_models.at(i)->Animation()));
								}
							}
						}
					}
				}
			}
			Game_Scene::~Game_Scene() {
				for (auto i = m_scene_input.begin(); i != m_scene_input.end(); i++) {
					if (pw::Engine_Memory::Deallocate<pw::co::Engine_Input>(i->second) == false) {
						if (i->second != nullptr) {
							delete i->second;
							i->second = nullptr;
						}
					}
				}
				for (auto i = m_scene_collision_events.begin(); i != m_scene_collision_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							for (auto l = k->second.begin(); l != k->second.end(); l++) {
								if (pw::Engine_Memory::Deallocate<st::Scene_Event>(l->second) == false) {
									if (l->second != nullptr) {
										delete l->second;
										l->second = nullptr;
									}
								}
							}
						}
					}
				}
				for (auto i = m_scene_events.begin(); i != m_scene_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							for (auto l = k->second.begin(); l != k->second.end(); l++) {
								for (auto h = l->second.begin(); h != l->second.end(); h++) {
									for (auto g = h->second.begin(); g != h->second.end(); g++) {
										if (pw::Engine_Memory::Deallocate<st::Scene_Event>(g->second) == false) {
											if (g->second != nullptr) {
												delete g->second;
												g->second = nullptr;
											}
										}
									}
								}
							}
						}
					}
				}
				for (auto i = m_scene_alt_events.begin(); i != m_scene_alt_events.end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						for (auto k = j->second.begin(); k != j->second.end(); k++) {
							for (auto l = k->second.begin(); l != k->second.end(); l++) {
								if (pw::Engine_Memory::Deallocate<st::Scene_Event>(l->second) == false) {
									if (l->second != nullptr) {
										delete l->second;
										l->second = nullptr;
									}
								}
							}
						}
					}
				}
				for (auto i = m_main_scene_models.begin(); i != m_main_scene_models.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Actor>(*i) == false) {
						if (*i != nullptr) {
							delete *i;
							*i = nullptr;
						}
					}
				}
				for (auto i = m_sub_scene_deposit.begin(); i != m_sub_scene_deposit.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Sub_Scene_Structure>(i->second) == false) {
						if (i->second != nullptr) {
							delete i->second;
							i->second = nullptr;
						}
					}
				}

				if (pw::Engine_Memory::Deallocate<st::Physics_Factory>(m_scene_physics) == false) {
					if (m_scene_physics != nullptr) {
						delete m_scene_physics;
						m_scene_physics = nullptr;
					}
				}
			}
			void Game_Scene::Pre_Render() {
				m_new_input = false;

				for (auto i = m_collision_models.begin(); i != m_collision_models.end(); i++) {
					if ((*i)->Physics_Object() != nullptr) {
						if ((*i)->Physics_Object()->Body() != nullptr) {
							for (b2ContactEdge* j = (*i)->Physics_Object()->Body()->GetContactList(); j; j = j->next) {
								st::Actor* v_temp = nullptr;
								for (auto k = m_collision_models.begin(); k != m_collision_models.end(); k++) {
									if (j->contact->GetFixtureB()->GetBody() == (*k)->Physics_Object()->Body()) {
										v_temp = *k;
										break;
									}
								}
								if (v_temp != nullptr) {
									Activate_Event((*i)->S_Id(), v_temp->S_Id());
								}
								else {
									// We could just have a event were we collide with
									// anything.
									Activate_Event((*i)->S_Id(), L"NULL");
								}
							}
						}
					}
				}

				if (m_scene_physics != nullptr) {
					m_scene_physics->Run();
				}

				if (m_active_scene_events.size() > 0) {
					for (auto it = m_active_scene_events.begin(); it != m_active_scene_events.end(); it++) {
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

				std::vector<st::Actor*> v_models{};

				// Pre-Render any sub-scenes so they are added to the over all quadrants

				for (auto i = m_sub_scene_deposit.begin(); i != m_sub_scene_deposit.end(); i++) {
					if (i->second->Should_Render() == false && i->second->Is_Rendered() == true) {
						i->second->De_Render(m_quadtree_renderer);
					}
				}

				for (auto i = m_sub_scene_deposit.begin(); i != m_sub_scene_deposit.end(); i++) {
					if (i->second->Should_Render() == true && i->second->Is_Rendered() == false) {
						i->second->Pre_Render(m_quadtree_renderer);
					}
				}

				if (m_quadtree_render_box.intersects(v_screen_box) == true) {
					v_models = m_quadtree_renderer.query(v_screen_box);
					m_render_queue.insert(m_render_queue.end(), v_models.begin(), v_models.end());
					v_models.clear();
				}

				m_last_render_count = m_render_queue.size();

				if (m_render_queue.size() > 0) {
					std::sort(m_render_queue.begin(), m_render_queue.end(), Compare_Layer);

					for (uint32_t i = 0; i < m_render_queue.size(); i++) {
						st::Actor* v_temp = m_render_queue.at(i);

						if (v_temp->Render_Toggle() == false) {
							v_temp->Set_Render_State(false);
							m_render_queue.erase(m_render_queue.begin() + i);
							i = i - 1;
							continue;
						}
						else {
							v_temp->Set_Render_State(true);
						}

						if (v_temp->Text() != nullptr) {
							m_last_render_count = m_last_render_count + v_temp->Text()->Count();
						}
						if (v_temp->Animation() != nullptr) {
							if (v_temp->S_Id().empty() != true) {
								if (v_temp->Animation()->End() == true) {
									Activate_Event(pw::cm::Engine_Constant::PW_ANIMATION_END_EVENT, v_temp->S_Id());
								}
								if (v_temp->Animation()->Start() == true) {
									Activate_Event(pw::cm::Engine_Constant::PW_ANIMATION_START_EVENT, v_temp->S_Id());
								}
							}
						}
						if (v_temp->Sound_Structure() != nullptr) {
							if (v_temp->S_Id().empty() != true) {
								for (auto j = v_temp->Sound_Structure()->All_Sounds()->begin(); j != v_temp->Sound_Structure()->All_Sounds()->end(); j++) {
									if (j->second->End() == true) {
										// Sounds are different from animations in that they need to be called from the unique id's since
										// many from one model could be playing
										Activate_Event(pw::cm::Engine_Constant::PW_SOUND_END_EVENT, j->first);
									}
									if (j->second->Start() == true) {
										Activate_Event(pw::cm::Engine_Constant::PW_SOUND_START_EVENT, j->first);
									}
								}
							}
						}
					}
					for (auto i = m_screen_models.begin(); i != m_screen_models.end(); i++) {
						(*i)->Model()->Set_Position(st::Camera::Camera_Position());

						if ((*i)->Text() != nullptr) {
							(*i)->Text()->Set_Position(st::Camera::Camera_Position());
						}
					}


					Activate_Event(cm::Engine_Constant::PW_HOVER_EVENT, 0, 1);

					// Make sure after the fact we stop it from 
					// continuing to-do calculations
					if (m_re_render != false) {
						if (m_listener_id == L"NULL") {
							st::Listener::Change_Bound_Listener(nullptr);
						}
						else {
							st::Actor* v_listener = Access_Model(m_listener_id);
							if (v_listener != nullptr) {
								st::Listener::Create_Listener(std::bind(&st::Model::Calculate_Center, v_listener->Model()));
							}
						}

						m_re_render = false;
					}
					else {
						st::Listener::Update();
					}
				}
				// Update all of the async animations
				for (auto i = m_async_animations.begin(); i != m_async_animations.end(); i++) {
					i->first->Change_Frame(false);
				}
			}
			void Game_Scene::Render() {
				if (m_render_queue.size() > 0) {
					for (auto i = m_render_queue.begin(); i != m_render_queue.end(); i++) {
						(*i._Ptr)->Render();
					}
					m_render_queue.clear();
				}
			}
			void Game_Scene::Pause_All_Sounds() {
				for (auto i = m_main_scene_models.begin(); i != m_main_scene_models.end(); i++) {
					(*i)->Pause_All_Sounds();
				}
			}
			void Game_Scene::Stop_All_Sounds() {
				for (auto i = m_main_scene_models.begin(); i != m_main_scene_models.end(); i++) {
					(*i)->Stop_All_Sounds();
				}
			}
			void Game_Scene::Reset_All_Sounds() {
				for (auto i = m_main_scene_models.begin(); i != m_main_scene_models.end(); i++) {
					(*i)->Reset_All_Sounds();
				}
			}
			void Game_Scene::Activate_Event(const PW_EVENT_ID& p_event_type, const PW_BUTTON_CODE& p_button, const PW_STATE& p_state) {
				if (m_current_scene_events != nullptr) {
					if (m_current_scene_events->count(p_event_type) > 0) {
						switch (p_event_type) {
							case cm::Engine_Constant::PW_CLICK_EVENT: {
								for (auto i = m_current_scene_events->at(p_event_type).begin(); i != m_current_scene_events->at(p_event_type).end(); i++) {
									if (i->first == p_button) {
										if (i->second.count(p_state) > 0) {
											for (auto j = i->second.at(p_state).begin(); j != i->second.at(p_state).end(); j++) {
												for (auto h = j->second.begin(); h != j->second.end(); h++) {
													if (j->first->Is_Rendered() == true) {
														// Use algorithm to find if the click was within the model range
														glm::ivec2 v_point = glm::ivec2(cm::Engine_Constant::Mouse_X_Coord(), cm::Engine_Constant::Mouse_Y_Coord());

														st::Mesh* v_mesh = j->first->Model()->Mesh();
														glm::ivec2 v_position = glm::ivec2(j->first->Model()->Position().x, j->first->Model()->Position().y);
														glm::ivec2 v_size = glm::ivec2(j->first->Model()->Size());
														std::vector<glm::ivec2> v_points{};

														for (size_t k = 0; k < v_mesh->Vertex_Count(); k++) {
															v_points.push_back(glm::ivec2(
																// x
																v_position.x + (v_size.x * v_mesh->Vertices()[k].Vertex_Position().x),
																// y
																v_position.y + (v_size.y * v_mesh->Vertices()[k].Vertex_Position().y)
															));
														}
														int32_t l = v_mesh->Vertex_Count() - 1;
														int32_t v_nvert = v_mesh->Vertex_Count();
														bool c = false;

														for (int32_t p = 0; p < v_nvert; l = p++) {
															if (((v_points[p].y > v_point.y) != (v_points[l].y > v_point.y)) &&
																(v_point.x < (v_points[l].x - v_points[p].x) * (v_point.y - v_points[p].y) / (v_points[l].y - v_points[p].y) + v_points[p].x)) {
																c = !c;
															}
														}
														if (h->second->Event()->Trigger() == GLFW_RELEASE) {
															if (c != true) {
																if (h->second->Event()->Play_State() == true) {
																	h->second->Run_Event();
																	if (m_new_input != true) {
																		continue;
																	}
																	else {
																		return;
																	}
																}
															}
														}
														else {
															if (c == true) {
																if (h->second->Event()->Play_State() == true) {
																	h->second->Run_Event();
																	if (m_new_input != true) {
																		continue;
																	}
																	else {
																		return;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
								break;
							}
							case cm::Engine_Constant::PW_HOVER_EVENT: {
								for (auto i = m_current_scene_events->at(p_event_type).begin(); i != m_current_scene_events->at(p_event_type).end(); i++) {
									for (auto j = i->second.begin(); j != i->second.end(); j++) {
										for (auto t = j->second.begin(); t != j->second.end(); t++) {
											for (auto h = t->second.begin(); h != t->second.end(); h++) {
												if (t->first->Is_Rendered() == true) {
													// Use algorithm to find if the click was within the model range
													glm::ivec2 v_point = glm::ivec2(cm::Engine_Constant::Mouse_X_Coord(), cm::Engine_Constant::Mouse_Y_Coord());

													st::Mesh* v_mesh = t->first->Model()->Mesh();
													glm::ivec2 v_position = glm::ivec2(t->first->Model()->Position().x, t->first->Model()->Position().y);
													glm::ivec2 v_size = glm::ivec2(t->first->Model()->Size());
													std::vector<glm::ivec2> v_points{};

													for (size_t k = 0; k < v_mesh->Vertex_Count(); k++) {
														v_points.push_back(glm::ivec2(
															// x
															v_position.x + (v_size.x * v_mesh->Vertices()[k].Vertex_Position().x),
															// y
															v_position.y + (v_size.y * v_mesh->Vertices()[k].Vertex_Position().y)
														));
													}
													int32_t l = v_mesh->Vertex_Count() - 1;
													int32_t v_nvert = v_mesh->Vertex_Count();
													bool c = false;

													for (int32_t p = 0; p < v_nvert; l = p++) {
														if (((v_points[p].y > v_point.y) != (v_points[l].y > v_point.y)) &&
															(v_point.x < (v_points[l].x - v_points[p].x) * (v_point.y - v_points[p].y) / (v_points[l].y - v_points[p].y) + v_points[p].x)) {
															c = !c;
														}
													}
													if (h->second->Event()->Trigger() == GLFW_RELEASE) {
														if (c != true) {
															if (h->second->Event()->Play_State() == true) {
																h->second->Run_Event();
																if (m_new_input != true) {
																	continue;
																}
																else {
																	return;
																}
															}
														}
													}
													else {
														if (c == true) {
															if (h->second->Event()->Play_State() == true) {
																h->second->Run_Event();
																if (m_new_input != true) {
																	continue;
																}
																else {
																	return;
																}
															}
														}
													}
												}
											}
										}
									}
								}
								break;
							}
							default: {
								auto v_found_button = m_current_scene_events->at(p_event_type).find(p_button);
								if (v_found_button != m_current_scene_events->at(p_event_type).end()) {
									auto v_found_state = m_current_scene_events->at(p_event_type).at(p_button).find(p_state);
									if (v_found_state != m_current_scene_events->at(p_event_type).at(p_button).end()) {
										for (auto i = m_current_scene_events->at(p_event_type).at(p_button).at(p_state).rbegin(); i != m_current_scene_events->at(p_event_type).at(p_button).at(p_state).rend(); i++) {
											for (auto j = i->second.begin(); j != i->second.end(); j++) {
												if (i->first == nullptr) {
													j->second->Run_Event();
													if (m_new_input != true) {
														if (!(j->second->Event()->Play_State())) {
															m_active_scene_events.push_back(j->second);
														}
														continue;
													}
													else {
														return;
													}
												}
												else {
													if (i->first->Is_Rendered() == true) {
														j->second->Run_Event();
														if (m_new_input != true) {
															if (!(j->second->Event()->Play_State())) {
																m_active_scene_events.push_back(j->second);
															}
															continue;
														}
														else {
															return;
														}
													}
												}
											}
										}
									}
								}
								if (!m_active_scene_events.empty()) {
									for (auto i = m_active_scene_events.begin(); i != m_active_scene_events.end(); i++) {
										if ((*i._Ptr)->Event()->Resolution() == p_state) {
											if ((*i._Ptr)->Event()->Button() == p_button) {
												m_active_scene_events.erase(i);
												if (m_active_scene_events.size() > 1) {
													i = m_active_scene_events.begin();
												}
												else {
													break;
												}
											}
										}
									}
								}
								break;
							}
						}
					}
				}
			}
			void Game_Scene::Activate_Event(const std::wstring& p_collider_s_id, const std::wstring& p_object_s_id) {
				if (m_current_scene_collision_events != nullptr) {
					auto v_found_collider = m_current_scene_collision_events->find(p_collider_s_id);
					if (v_found_collider != m_current_scene_collision_events->end()) {
						auto v_found_object = m_current_scene_collision_events->at(p_collider_s_id).find(p_collider_s_id);
						if (v_found_object != m_current_scene_collision_events->at(p_collider_s_id).end()) {
							for (auto i = m_current_scene_collision_events->at(p_collider_s_id).at(p_object_s_id).begin(); i != m_current_scene_collision_events->at(p_collider_s_id).at(p_object_s_id).end(); i++) {
								i->second->Run_Event();
								if (m_new_input != true) {
									continue;
								}
								else {
									return;
								}
							}
						}
					}
				}
			}
			void Game_Scene::Activate_Event(const PW_EVENT_ID& p_event_type, const std::wstring& p_model_s_id) {
				if (m_current_scene_alt_events != nullptr) {
					auto v_found_event_type = m_current_scene_alt_events->find(p_event_type);
					if (v_found_event_type != m_current_scene_alt_events->end()) {
						auto v_found_s_id = m_current_scene_alt_events->at(p_event_type).find(p_model_s_id);
						if (v_found_s_id != m_current_scene_alt_events->at(p_event_type).end()) {
							for (auto i = m_current_scene_alt_events->at(p_event_type).at(p_model_s_id).begin(); i != m_current_scene_alt_events->at(p_event_type).at(p_model_s_id).end(); i++) {
								i->second->Run_Event();
								if (m_new_input != true) {
									continue;
								}
								else {
									return;
								}
							}
						}
					}
				}
			}
			void Game_Scene::Register_S_ID(const std::wstring& p_s_id, st::Actor* p_model) {
				auto v_found = s_id_models.find(p_s_id);
				if (v_found == s_id_models.end()) {
					s_id_models.insert(std::make_pair(p_s_id, p_model));
					p_model->Set_S_ID(p_s_id);
				}
			}
			void Game_Scene::Add_Model(st::Actor* p_new_model) {
				m_quadtree_renderer.add(p_new_model);

				m_main_scene_models.push_back(p_new_model);

				st::Actor* v_temp = static_cast<st::Actor*>(p_new_model);

				if (v_temp->Layer() >= 4) {
					glm::vec2 v_origin = v_temp->Model()->Position();

					v_temp->Model()->Set_Position(st::Camera::Camera_Position());

					v_temp->Model()->Set_Offset(glm::vec2(v_origin.x, v_origin.y - (float)pw::cm::Engine_Constant::Window_Height()));

					if (v_temp->Text() != nullptr) {
						v_temp->Text()->Set_Offset(st::Camera::Camera_Position());
					}

					m_screen_models.push_back(v_temp);
				}

				if (p_new_model->Animation_Structure() != nullptr) {
					for (auto j = p_new_model->Animation_Structure()->Animations().begin(); j != p_new_model->Animation_Structure()->Animations().end(); j++) {
						if (std::get<0>(j->second)->Is_Async() == true) {
							auto k = m_async_animations.find(std::get<0>(j->second));
							if (k == m_async_animations.end()) {
								m_async_animations.insert(std::make_pair(std::get<0>(j->second), std::get<0>(j->second)));
							}
						}
					}
				}
				else {
					if (p_new_model->Animation() != nullptr) {
						if (p_new_model->Animation()->Is_Async() == true) {
							auto k = m_async_animations.find(p_new_model->Animation());
							if (k == m_async_animations.end()) {
								m_async_animations.insert(std::make_pair(p_new_model->Animation(), p_new_model->Animation()));
							}
						}
					}
				}
			}
			void Game_Scene::Toggle_Render(std::wstring p_s_id) {
				auto v_found = s_id_models.find(p_s_id);
				if (v_found != s_id_models.end()) {
					v_found->second->Toggle_Render();
				}
			}
			void Game_Scene::Toggle_Render(const std::wstring& p_s_id, const bool& p_state) {
				auto v_found = s_id_models.find(p_s_id);
				if (v_found != s_id_models.end()) {
					v_found->second->Set_Render_State(p_state);
				}
			}
			void Game_Scene::Remove_Model(const std::wstring& p_s_id) {
				st::Actor* v_model = Access_Model(p_s_id);

				m_quadtree_renderer.remove(v_model);

				for (auto i = m_main_scene_models.begin(); i != m_main_scene_models.end(); i++) {
					if (*i == &*v_model) {
						m_main_scene_models.erase(i);
						break;
					}
				}
				for (auto i = m_screen_models.begin(); i != m_screen_models.end(); i++) {
					if (*i == &*v_model) {
						m_screen_models.erase(i);
						break;
					}
				}

				if (v_model->Animation_Structure() != nullptr) {
					for (auto j = v_model->Animation_Structure()->Animations().begin(); j != v_model->Animation_Structure()->Animations().end(); j++) {
						if (std::get<0>(j->second)->Is_Async() == true) {
							m_async_animations.erase(std::get<0>(j->second));
						}
					}
				}
				else {
					if (v_model->Animation() != nullptr) {
						if (v_model->Animation()->Is_Async() == true) {
							m_async_animations.erase(v_model->Animation());
						}
					}
				}
			}
			quadtree::Box<float> Game_Scene::Get_Box(st::Actor* p_model) {
				return quadtree::Box<float>{quadtree::Vector2<float>{(float)p_model->Model()->Position().x, (float)p_model->Model()->Position().y - (float)p_model->Model()->Size().y},
					quadtree::Vector2<float>{(float)p_model->Model()->Size().x, (float)p_model->Model()->Size().y}};
			}
			void Game_Scene::Re_Render() {
				m_re_render = true;
			}
			void Game_Scene::Capture_Instance(const glm::vec2& p_camera_position) {
				m_camera_position_instance = p_camera_position;
			}
			void Game_Scene::Set_Active_Input(std::wstring p_new_input_s_id) {
				m_new_input = true;
				auto v_found_input = m_scene_input.find(p_new_input_s_id);
				if (v_found_input != m_scene_input.end()) {
					m_current_scene_input = &v_found_input->second;
					co::Engine_Input::Set_Current_Input(*m_current_scene_input);
				}
				else {
					co::Engine_Input::Set_Current_Input(nullptr);
				}
				auto v_found_event = m_scene_events.find(p_new_input_s_id);
				if (v_found_event != m_scene_events.end()) {
					m_current_scene_events = &v_found_event->second;
				}
				else {
					m_current_scene_events = nullptr;
				}
				auto v_found_collisions = m_scene_collision_events.find(p_new_input_s_id);
				if (v_found_collisions != m_scene_collision_events.end()) {
					m_current_scene_collision_events = &v_found_collisions->second;
				}
				else {
					m_current_scene_collision_events = nullptr;
				}
				auto v_found_alt_event = m_scene_alt_events.find(p_new_input_s_id);
				if (v_found_alt_event != m_scene_alt_events.end()) {
					m_current_scene_alt_events = &v_found_alt_event->second;
				}
				else {
					m_current_scene_alt_events = nullptr;
				}
			}
			st::Actor* Game_Scene::Access_Model(const std::wstring& p_s_id) {
				auto v_found = s_id_models.find(p_s_id);
				if (v_found != s_id_models.end()) {
					return v_found->second;
				}
				else {
					return nullptr;
				}
			}
			void Game_Scene::Set_Sub_Scene_State(const std::wstring& p_sub_scene, const bool& p_state) {
				auto v_found = m_sub_scene_deposit.find(p_sub_scene);
				if (v_found != m_sub_scene_deposit.end()) {
					v_found->second->Set_Render_Toggle(p_state);
				}
			}
			COMPLEX_FUNCTION_3(const PW_EVENT_ID&, const PW_BUTTON_CODE&, const PW_STATE&) Game_Scene::Event_Callback() {
				return std::bind(static_cast<void(st::Game_Scene::*)(const PW_EVENT_ID&, const PW_BUTTON_CODE&, const PW_STATE&)>(&st::Game_Scene::Activate_Event), this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			}
			const std::vector<st::Actor*>& Game_Scene::Main_Scene_Models() const {
				return m_main_scene_models;
			}
			const size_t& Game_Scene::Last_Render_Count() const {
				return m_last_render_count;
			}
			st::Physics_Factory* Game_Scene::Scene_Physics() const {
				return m_scene_physics;
			}
			co::Engine_Input* Game_Scene::Input() const {
				return *m_current_scene_input;
			}
			const int32_t& Game_Scene::Actor_Count() {
				return m_global_actor_count;
			}
			const std::wstring& Game_Scene::Scene_Name() const {
				return m_scene_name;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
