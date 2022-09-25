// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_GAME_SCENE
#define H_GAME_SCENE
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers 
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <unordered_set>
#include <algorithm>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <Quadtree\Quadtree.h>     
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
#include "engine_control\engine_input.h"
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_event.h"
#include "engine_structures\engine_model.h"
#include "engine_structures\engine_physics.h"
#include "engine_structures\engine_animation.h"
#include "engine_structures\engine_text.h"
#include "engine_structures\engine_sound.h"
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		class Actor {
		// Default Class Structures 
		public:
			Actor();
			
			Actor(st::Model* p_model, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, st::Text* p_text, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, st::Texture_Structure* p_multi_texture, const int32_t& p_layer = 0);

			// Sound Constructors
			Actor(st::Model* p_model, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, st::Text* p_text, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, st::Texture_Structure* p_multi_texture, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer = 0);

			Actor(st::Model* p_model, st::Animation* p_animation, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, st::Animation* p_animation, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer = 0);
			Actor(st::Model* p_model, const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids, st::Sound_Structure* p_sound_deposit, const int32_t& p_layer = 0);

			~Actor();
		private:
		// Public Functions/Macros  
		public:
			void Render();

			void Play_Sound(std::wstring p_sound_s_id, bool p_reset_play);
			void Pause_Sound(std::wstring p_sound_s_id);
			void Stop_Sound(std::wstring p_sound_s_id);
			void Reset_Sound(std::wstring p_sound_s_id);
			void Pause_All_Sounds();
			void Stop_All_Sounds();
			void Reset_All_Sounds();
			
			void Change_Volume(std::wstring p_sound_s_id, float p_new_volume, bool windows_style);

			void Run_Animation();
			void Advance_Animation();
			void Start_Animation();
			void Stop_Animation();
			void Change_Animation(std::wstring p_animation_id, bool p_reset = true);

			 // Tests for a non-b2Body collision between shapes
			 // so they don't just bounce off each other
			bool Test_Collision(st::Actor* p_other_model);
			
			void Set_Physics_Object(st::Physics_Object* p_body);

			void Set_S_ID(const std::wstring& p_s_id);

			void Set_Texture(std::wstring p_s_id);

			void Set_Render_State(const bool& p_state);

			void Set_Size_X(const float& p_size_x);
			void Set_Size_Y(const float& p_size_y);
			void Set_Size(const glm::vec2& p_size_px);
			
			void Set_Text(std::wstring p_new_text);

			void Set_Text_Color(glm::vec4 p_color);
			void Set_Color(glm::vec4 p_color);

			void Toggle_Render();
			void Set_Render_Toggle(const bool& p_state);

			st::Model* Model() const;
			st::Physics_Object* Physics_Object() const;
			st::Texture_Structure* Multi_Texture() const;

			st::Sound_Structure* Sound_Structure() const;
			
			const bool& Is_Rendered() const;
			const bool& Render_Toggle() const;

			const std::wstring& S_Id() const;

			st::Text* Text() const;

			st::Animation* Animation() const;
			st::Animation_Structure* Animation_Structure() const;
			
			const int32_t& Layer() const;

			static void Increment_ID_Index();

			static const PW_ID& Global_ID();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			st::Model* m_model;
			st::Physics_Object* m_body;
			st::Texture_Structure* m_multi_texture;
			// Sound structure
			st::Sound_Structure* m_sound_deposit;
			// Was the model rendered before the next frame runs
			bool m_is_rendered;
			// Should the model render or not
			bool m_render_toggle;
			// This is a special string id used for accessing a specific model
			std::wstring m_s_id;
			// A pointer to possible text the structure may be covering.
			st::Text* m_text;

			st::Animation* m_current_animation;
			st::Animation_Structure* m_animations;
			// The layer the model will be drawn on.
			int32_t m_layer;
			static PW_ID m_global_index;
		};
		class Scene_Event {
		// Default Class Structures 
		public:
			Scene_Event(st::Actor* p_model_pointer, st::Event_Base* p_model_event);
			
			~Scene_Event();
		private:
		// Public Functions/Macros 
		public:
			void Run_Event();
			
			st::Event_Base* Event() const;
			
			st::Actor* Model() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			st::Actor* m_model;
			pw::st::Event_Base* m_model_event;
		};
		struct Sub_Scene_Structure {
			// Default Class Structures
		public:
			Sub_Scene_Structure();
			Sub_Scene_Structure(const std::wstring& p_sub_scene_id, const std::vector<st::Actor*>& p_scene_repository, const bool& p_should_render);
			~Sub_Scene_Structure();
		private:
			// Public Functions/Macros 
		public:
			void Pre_Render(quadtree::Quadtree<st::Actor*, std::function<quadtree::Box<float>(st::Actor*)>>& p_quadtree_renderer);
			void De_Render(quadtree::Quadtree<st::Actor*, std::function<quadtree::Box<float>(st::Actor*)>>& p_quadtree_renderer);

			void Set_Render_State(const bool& p_is_rendering);
			void Set_Render_Toggle(bool p_render_structure);
			void Push_Screen_Models(std::vector<st::Actor*>& p_screen_models);

			const bool& Is_Rendered();
			const bool& Should_Render();
			std::vector<st::Actor*>& Scenes();
			const std::wstring& Sub_Scene_Id();
			// Public Variables     
		public:
			// Private Functions/Macros 
		private:
			// Private Variables       
		private:
			std::wstring m_sub_scene_id;

			std::vector<st::Actor*> m_scene_repository;
			// Is it currently rendered as of the last frame
			bool m_is_rendered;
			// Should the structure be rendered
			bool m_should_render;
		};
		class Game_Scene {
		// Default Class Structures
		public:
			Game_Scene();
			
			Game_Scene(const std::wstring& p_scene_name, const std::vector<st::Actor*>& p_scene_models, const std::vector<st::Actor*>& p_collision_models,
				 const std::map<std::wstring, co::Engine_Input*>& p_scene_input, st::Physics_Factory* p_scene_physics,
					const std::map<std::wstring, st::Sub_Scene_Structure*>& p_sub_scene_deposit, const std::wstring& p_listener_id);

			~Game_Scene();
		private:
		// Public Functions/Macros 
		public:
			void Pre_Render();
			
			void Render();

			void Pause_All_Sounds();
			void Stop_All_Sounds();
			void Reset_All_Sounds();
			
			template<class type, class ...args>
			void Create_Event(const std::wstring& p_event_holder_id, const PW_EVENT_ID& p_event_type, const PW_BUTTON_CODE& p_button, const PW_STATE& p_state, st::Actor* p_test_pointer,
						st::Actor* p_id_pointer, const std::shared_ptr<std::function<type(args...)>>& p_trigger_function, const bool& p_play_once, args... p_arguments) {
				if (p_trigger_function != nullptr) {
					switch (p_event_type) {
						case pw::cm::Engine_Constant::PW_ANIMATION_START_EVENT:
						case pw::cm::Engine_Constant::PW_ANIMATION_END_EVENT: {
							if (m_scene_alt_events.count(p_event_holder_id) < 1) {
								std::map<PW_ID, Scene_Event*> id_event{};
								Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
									pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

								id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

								std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>> model_id{};
								model_id.insert(std::make_pair(p_id_pointer->S_Id(), id_event));

								std::map<PW_EVENT_ID, std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>>> event_id{};

								event_id.insert(std::make_pair(p_event_type, model_id));

								m_scene_alt_events.insert(std::make_pair(p_event_holder_id, event_id));

								v_temp = nullptr;

								m_scene_id_counter = m_scene_id_counter + 1;
							}
							else {
								if (m_scene_alt_events.at(p_event_holder_id).count(p_event_type) < 1) {
									std::map<PW_ID, Scene_Event*> id_event{};
									Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
										pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

									id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

									std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>> model_id{};
									model_id.insert(std::make_pair(p_id_pointer->S_Id(), id_event));

									m_scene_alt_events.at(p_event_holder_id).insert(std::make_pair(p_event_type, model_id));

									v_temp = nullptr;

									m_scene_id_counter = m_scene_id_counter + 1;
								}
								else {
									if (m_scene_alt_events.at(p_event_holder_id).at(p_event_type).count(p_id_pointer->S_Id()) < 1) {
										std::map<PW_ID, Scene_Event*> id_event{};
										Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
											pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

										id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

										m_scene_alt_events.at(p_event_holder_id).at(p_event_type).insert(std::make_pair(p_id_pointer->S_Id(), id_event));

										v_temp = nullptr;

										m_scene_id_counter = m_scene_id_counter + 1;
									}
									else {
										Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
											pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

										m_scene_alt_events.at(p_event_holder_id).at(p_event_type).at(p_id_pointer->S_Id()).insert(std::make_pair(m_scene_id_counter, v_temp));

										v_temp = nullptr;

										m_scene_id_counter = m_scene_id_counter + 1;
									}
								}
							}
							break;
						}
						default: {
							if (m_scene_events.count(p_event_holder_id) < 1) {
								std::map<PW_ID, Scene_Event*> id_event{};
								Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
									pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

								id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

								std::map<st::Actor*, std::map<PW_ID, Scene_Event*>> actor_event{};
								actor_event.insert(std::make_pair(p_test_pointer, id_event));

								std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, Scene_Event*>>> state_event{};
								state_event.insert(std::make_pair(p_state, actor_event));

								std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, Scene_Event*>>>> button_event{};
								button_event.insert(std::make_pair(p_button, state_event));

								std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, Scene_Event*>>>>> event_id{};
								event_id.insert(std::make_pair(p_event_type, button_event));

								m_scene_events.insert(std::make_pair(p_event_holder_id, event_id));

								v_temp = nullptr;

								m_scene_id_counter = m_scene_id_counter + 1;
							}
							else {
								if (m_scene_events.at(p_event_holder_id).count(p_event_type) < 1) {
									std::map<PW_ID, Scene_Event*> id_event{};
									Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
										pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

									id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

									std::map<st::Actor*, std::map<PW_ID, Scene_Event*>> actor_event{};
									actor_event.insert(std::make_pair(p_test_pointer, id_event));

									std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, Scene_Event*>>> state_event{};
									state_event.insert(std::make_pair(p_state, actor_event));

									std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, Scene_Event*>>>> button_event{};
									button_event.insert(std::make_pair(p_button, state_event));

									m_scene_events.at(p_event_holder_id).insert(std::make_pair(p_event_type, button_event));

									v_temp = nullptr;

									m_scene_id_counter = m_scene_id_counter + 1;
								}
								else {
									if (m_scene_events.at(p_event_holder_id).at(p_event_type).count(p_button) < 1) {
										std::map<PW_ID, Scene_Event*> id_event{};
										Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
											pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

										id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

										std::map<st::Actor*, std::map<PW_ID, Scene_Event*>> actor_event{};
										actor_event.insert(std::make_pair(p_test_pointer, id_event));

										std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, Scene_Event*>>> state_event{};
										state_event.insert(std::make_pair(p_state, actor_event));

										m_scene_events.at(p_event_holder_id).at(p_event_type).insert(std::make_pair(p_button, state_event));

										v_temp = nullptr;

										m_scene_id_counter = m_scene_id_counter + 1;
									}
									else {
										if (m_scene_events.at(p_event_holder_id).at(p_event_type).at(p_button).count(p_state) < 1) {
											std::map<PW_ID, Scene_Event*> id_event{};
											Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
												pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

											id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

											std::map<st::Actor*, std::map<PW_ID, Scene_Event*>> actor_event{};
											actor_event.insert(std::make_pair(p_test_pointer, id_event));

											m_scene_events.at(p_event_holder_id).at(p_event_type).at(p_button).insert(std::make_pair(p_state, actor_event));

											v_temp = nullptr;

											m_scene_id_counter = m_scene_id_counter + 1;
										}
										else {
											if (m_scene_events.at(p_event_holder_id).at(p_event_type).at(p_button).at(p_state).count(p_test_pointer) < 1) {
												std::map<PW_ID, Scene_Event*> id_event{};
												Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
													pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

												id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

												m_scene_events.at(p_event_holder_id).at(p_event_type).at(p_button).at(p_state).insert(std::make_pair(p_test_pointer, id_event));

												v_temp = nullptr;

												m_scene_id_counter = m_scene_id_counter + 1;
											}
											else {
												std::map<PW_ID, Scene_Event*> id_event{};
												Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_id_pointer,
													pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(p_button, p_state, p_trigger_function, p_play_once, p_arguments...));

												m_scene_events.at(p_event_holder_id).at(p_event_type).at(p_button).at(p_state).at(p_test_pointer).insert(std::make_pair(m_scene_id_counter, v_temp));

												v_temp = nullptr;

												m_scene_id_counter = m_scene_id_counter + 1;
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
			template<class type, class ...args>
			void Create_Event(const std::wstring& p_event_holder_id, const std::wstring& p_sound_id, const PW_EVENT_ID& p_event_type, const PW_STATE& p_state, st::Actor* p_model_pointer,
				const std::shared_ptr<std::function<type(args...)>>& p_trigger_function, const bool& p_play_once, args... p_arguments) {
				if (p_trigger_function != nullptr) {
					if (m_scene_alt_events.count(p_event_holder_id) < 1) {
						std::map<PW_ID, Scene_Event*> id_event{};
						Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_model_pointer,
							pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, p_state, p_trigger_function, p_play_once, p_arguments...));

						id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

						std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>> model_id{};
						model_id.insert(std::make_pair(p_sound_id, id_event));

						std::map<PW_EVENT_ID, std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>>> event_id{};

						event_id.insert(std::make_pair(p_event_type, model_id));

						m_scene_alt_events.insert(std::make_pair(p_event_holder_id, event_id));

						v_temp = nullptr;

						m_scene_id_counter = m_scene_id_counter + 1;
					}
					else {
						if (m_scene_alt_events.at(p_event_holder_id).count(p_event_type) < 1) {
							std::map<PW_ID, Scene_Event*> id_event{};
							Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_model_pointer,
								pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, p_state, p_trigger_function, p_play_once, p_arguments...));

							id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

							std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>> model_id{};
							model_id.insert(std::make_pair(p_sound_id, id_event));

							m_scene_alt_events.at(p_event_holder_id).insert(std::make_pair(p_event_type, model_id));

							v_temp = nullptr;

							m_scene_id_counter = m_scene_id_counter + 1;
						}
						else {
							if (m_scene_alt_events.at(p_event_holder_id).at(p_event_type).count(p_sound_id) < 1) {
								std::map<PW_ID, Scene_Event*> id_event{};
								Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_model_pointer,
									pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, p_state, p_trigger_function, p_play_once, p_arguments...));

								id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

								m_scene_alt_events.at(p_event_holder_id).at(p_event_type).insert(std::make_pair(p_sound_id, id_event));

								v_temp = nullptr;

								m_scene_id_counter = m_scene_id_counter + 1;
							}
							else {
								Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(p_model_pointer,
									pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, p_state, p_trigger_function, p_play_once, p_arguments...));

								m_scene_alt_events.at(p_event_holder_id).at(p_event_type).at(p_sound_id).insert(std::make_pair(m_scene_id_counter, v_temp));

								v_temp = nullptr;

								m_scene_id_counter = m_scene_id_counter + 1;
							}
						}
					}
				}
			}
			template<class type, class ...args>
			void Create_Event(const std::wstring& p_event_holder_id, const std::wstring& p_collider_s_id, const std::wstring& p_object_s_id, 
					const std::shared_ptr<std::function<type(args...)>>& p_trigger_function, const bool& p_play_once, args... p_arguments) {
				 if (p_trigger_function != nullptr) {
					 if (m_scene_collision_events.count(p_event_holder_id) < 1) {
						 std::map<PW_ID, Scene_Event*> id_event{};
						 Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(nullptr,
							 pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, NULL, p_trigger_function, p_play_once, p_arguments...));

						 id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

						 std::map<std::wstring, std::map<PW_ID, Scene_Event*>> object_event{};
						 object_event.insert(std::make_pair(p_object_s_id, id_event));

						 std::map<std::wstring, std::map<std::wstring, std::map<PW_ID, Scene_Event*>>> host_event{};
						 host_event.insert(std::make_pair(p_collider_s_id, object_event));

						 m_scene_collision_events.insert(std::make_pair(p_event_holder_id, host_event));

						 v_temp = nullptr;

						 m_scene_id_counter = m_scene_id_counter + 1;
					 }
					 else {
						 if (m_scene_collision_events.at(p_event_holder_id).count(p_collider_s_id) < 1) {
							 std::map<PW_ID, Scene_Event*> id_event{};
							 Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(nullptr,
								 pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, NULL, p_trigger_function, p_play_once, p_arguments...));

							 id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

							 std::map<std::wstring, std::map<PW_ID, Scene_Event*>> object_event{};
							 object_event.insert(std::make_pair(p_object_s_id, id_event));

							 m_scene_collision_events.at(p_event_holder_id).insert(std::make_pair(p_collider_s_id, object_event));

							 v_temp = nullptr;

							 m_scene_id_counter = m_scene_id_counter + 1;
						 }
						 else {
							 if (m_scene_collision_events.at(p_event_holder_id).at(p_collider_s_id).count(p_object_s_id) < 1) {
								 std::map<PW_ID, Scene_Event*> id_event{};
								 Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(nullptr,
									 pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, NULL, p_trigger_function, p_play_once, p_arguments...));

								 id_event.insert(std::make_pair(m_scene_id_counter, v_temp));

								 m_scene_collision_events.at(p_event_holder_id).at(p_collider_s_id).insert(std::make_pair(p_object_s_id, id_event));

								 v_temp = nullptr;

								 m_scene_id_counter = m_scene_id_counter + 1;
							 }
							 else {
								 Scene_Event* v_temp = pw::Engine_Memory::Allocate<Scene_Event, bool>(nullptr,
									 pw::Engine_Memory::Allocate<st::Event<type, args...>, bool>(NULL, NULL, p_trigger_function, p_play_once, p_arguments...));

								 m_scene_collision_events.at(p_event_holder_id).at(p_collider_s_id).at(p_object_s_id).insert(std::make_pair(m_scene_id_counter, v_temp));

								 m_scene_id_counter = m_scene_id_counter + 1;

								 v_temp = nullptr;

								 m_scene_id_counter = m_scene_id_counter + 1;
							 }
						 }
					 }
				 }
			}
			void Activate_Event(const PW_EVENT_ID& p_event_type, const PW_BUTTON_CODE& p_button, const PW_STATE& p_state);

			void Activate_Event(const std::wstring& p_collider_s_id, const std::wstring& p_object_s_id);

			void Activate_Event(const PW_EVENT_ID& p_event_type, const std::wstring& p_model_s_id);
			
			void Register_S_ID(const std::wstring& p_s_id, st::Actor* p_model);

			// Adds the model to the current model list to be rendered
			void Add_Model(st::Actor* p_new_model);
			// Your model must have an id to be deleted
			void Toggle_Render(std::wstring p_s_id);
			void Toggle_Render(const std::wstring& p_s_id, const bool& p_state);
			void Remove_Model(const std::wstring& p_s_id);

			static quadtree::Box<float> Get_Box(st::Actor* p_model);
			
			void Re_Render();
			
			void Capture_Instance(const glm::vec2& p_camera_position);
			 
			void Set_Active_Input(std::wstring p_new_input_s_id);
			
			st::Actor* Access_Model(const std::wstring& p_s_id);

			void Set_Sub_Scene_State(const std::wstring& p_sub_scene, const bool& p_state);

			COMPLEX_FUNCTION_3(const PW_EVENT_ID&, const PW_BUTTON_CODE&, const PW_STATE&) Event_Callback();
		    
			const std::vector<st::Actor*>& Main_Scene_Models() const;
			
			const size_t& Last_Render_Count() const;
			
			st::Physics_Factory* Scene_Physics() const;
			
			co::Engine_Input* Input() const;

			static const int32_t& Actor_Count();

			const std::wstring& Scene_Name() const;
		// Public Variables     
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			// General Scene Information
			std::wstring m_scene_name;
			// Model Information
			std::vector<st::Actor*> m_main_scene_models;

			std::map<std::wstring, st::Sub_Scene_Structure*> m_sub_scene_deposit;

			std::vector<st::Actor*> m_render_queue;
			std::vector<st::Actor*> m_screen_models;
			size_t m_last_render_count;
			std::vector<st::Actor*> m_collision_models;
			std::map<st::Physics_Object*, st::Actor*> m_body_models;
			// Instant look up time is practical for the cost of doubled memory usage
			std::map<st::Animation*, st::Animation*> m_async_animations;
			// We need to keep track of the models that have special id's
			std::map<std::wstring, st::Actor*> s_id_models;
			// Input / Event Information
			std::map<std::wstring, co::Engine_Input*> m_scene_input;
			co::Engine_Input** m_current_scene_input;

			std::map<std::wstring, std::map<std::wstring, std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>>>> m_scene_collision_events;
			std::map<std::wstring, std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>>>* m_current_scene_collision_events;

			std::map<std::wstring, std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, st::Scene_Event*>>>>>> m_scene_events;
			std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<st::Actor*, std::map<PW_ID, st::Scene_Event*>>>>>* m_current_scene_events;
			std::vector<st::Scene_Event*> m_active_scene_events;
			uint32_t m_scene_id_counter;
			// Physics ( If the scene has it in the first place )
			st::Physics_Factory* m_scene_physics;
			// Alternate event holder for model specific sound / animation events
			std::map<std::wstring, std::map<PW_EVENT_ID, std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>>>> m_scene_alt_events;
			std::map<PW_EVENT_ID, std::map<std::wstring, std::map<PW_ID, st::Scene_Event*>>>* m_current_scene_alt_events;

			// Put all of the models into the quadtree for quick rendering and de-rendering
			quadtree::Quadtree<st::Actor*, std::function<quadtree::Box<float>(st::Actor*)>> m_quadtree_renderer;
			quadtree::Box<float> m_quadtree_render_box;

			// Layer Information
			// Bottom most is INT_32MIN, Top most is 3
			// Camera following is 4 >=
			
			// The scene can be changed from but when we return we need to do special coordinate
			// calculations for the layer 4 models
			// This will also be done for safety at the start of the scene's rendering anyways.
			bool m_re_render;
			bool m_new_input;

			glm::vec2 m_camera_position_instance;

			std::wstring m_listener_id;
			// How many models are currently loaded
			static int32_t m_global_actor_count;
		};
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_GAME_SCENE
