#include "structure_headers\player.h"

//////////////////////////////////
DU_NAMESPACE_SRT
//////////////////////////////////
	pw::st::Actor* du::Bush::m_bush{};
	// Player
	// Static Declarations
		pw::st::Actor* Player::m_player_actor{ nullptr };
		pw::st::Actor* Player::m_interaction_area{ nullptr };
		uint32_t Player::m_movement_keys{ 0 };
		bool Player::m_moving_left{ false };
		bool Player::m_moving_right{ false };
		bool Player::m_moving_up{ false };
		bool Player::m_moving_down{ false };
		bool Player::m_left_bearing{ false };
		bool Player::m_interacted{ false };
		std::unordered_set<char>* Player::m_current_directions{ nullptr };
		std::vector<char> Player::m_current_keys{};
		std::wstring Player::m_current_zone{};
		std::map<std::wstring, std::map<Player::Engine_Queue_State, std::function<void()>>>* Player::m_zone_specifier{ nullptr };
		std::map<std::wstring, du::Interaction_Group*>* Player::m_interactions{ nullptr };
	// Class Members
		void Player::Init_Player(pw::st::Game_Scene* p_zone_1) {
			std::map<std::wstring, std::map<Player::Engine_Queue_State, std::function<void()>>> v_temp{
				std::make_pair(L"Zone_1", []() ->std::map<Player::Engine_Queue_State, std::function<void()>> {
					std::map<Player::Engine_Queue_State, std::function<void()>> v_temp{
						std::make_pair(Player::Engine_Queue_State::BEFORE, Player::Zone_1_Before_Queue)
					};
					return v_temp;
				}())
			};

			m_zone_specifier = pw::Engine_Memory::Allocate<std::map<std::wstring, std::map<Player::Engine_Queue_State, std::function<void()>>>, bool>(v_temp);

			m_interactions = pw::Engine_Memory::Allocate<std::map<std::wstring, du::Interaction_Group*>, bool>();

			m_player_actor = p_zone_1->Access_Model(L"Player");

			m_interaction_area = pw::Engine_Memory::Allocate<pw::st::Actor, bool>(pw::Engine_Memory::Allocate<pw::st::Model, bool>(
				pw::st::Geometry_Types::SQUARE, pw::co::File_Loader::Load_Texture_File(L"White.png", true, false), glm::vec2(32.0f, 96.0f), 0.0f, glm::vec2(48.0f, 48.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
			m_interaction_area->Model()->Attach_To(m_player_actor->Model()->Position_Reference());

			m_interactions->insert(std::make_pair(L"Zone_1", pw::Engine_Memory::Allocate<Interaction_Group, bool>(m_interaction_area, L"Zone_1")));

			m_interactions->at(L"Zone_1")->Add_Interaction(pw::Engine_Memory::Allocate<Interaction, bool>(
				pw::Engine_Memory::Allocate<pw::st::Event<void>, bool>(NULL, NULL,
					std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
					std::bind(&du::Bush::Interact))), true),
				p_zone_1->Access_Model(L"Bush"),
				Interaction::Interaction_Type::INTERACT
				));
			m_interactions->at(L"Zone_1")->Add_Interaction(pw::Engine_Memory::Allocate<Interaction, bool>(
				pw::Engine_Memory::Allocate<pw::st::Event<void>, bool>(NULL, NULL,
					std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
						std::bind(&du::Bush::Attack))), true),
				p_zone_1->Access_Model(L"Bush"),
				Interaction::Interaction_Type::ATTACK
				));

			m_zone_specifier->at(L"Zone_1").insert(
				std::make_pair(Player::Engine_Queue_State::AFTER, Player::Zone_1_After_Queue)
			);

			m_current_directions = pw::Engine_Memory::Allocate<std::unordered_set<char>>();

			m_player_actor->Physics_Object()->Body()->SetLinearDamping(10.0f);

			p_zone_1->Scene_Physics()->Add_Object(m_interaction_area->Model(), b2BodyType::b2_dynamicBody, pw::st::Physics_Object::Object_Type::POLYGON, true, m_interaction_area->Model()->Id(), false);
			m_interaction_area->Set_Physics_Object(p_zone_1->Scene_Physics()->Access_Memeber(m_interaction_area->Model()->Id()));
		}
		void Player::Set_Zone(const std::wstring& p_zone) {
			if (p_zone != m_current_zone) {
				m_current_zone = p_zone;
			}
		}
		void Player::Delete_Player() {
			pw::Engine_Memory::Deallocate<pw::st::Actor>(m_interaction_area);

			pw::Engine_Memory::Deallocate<std::map<std::wstring, std::map<Player::Engine_Queue_State, std::function<void()>>>>(m_zone_specifier);

			for (auto i = m_interactions->begin(); i != m_interactions->end(); i++) {
				pw::Engine_Memory::Deallocate<Interaction_Group>(i->second);
			}

			pw::Engine_Memory::Deallocate<std::map<std::wstring, du::Interaction_Group*>>(m_interactions);

			pw::Engine_Memory::Deallocate<std::unordered_set<char>>(m_current_directions);

			m_current_keys.clear();
			m_current_keys.~vector();
		}
		void Player::Choose_Zone(const std::wstring& p_zone, const Player::Engine_Queue_State& p_queue_state) {
			auto v_found = m_zone_specifier->find(p_zone);

			if (v_found != m_zone_specifier->end()) {
				auto v_queue_state = v_found->second.find(p_queue_state);

				if (v_queue_state != v_found->second.end()) {
					v_queue_state->second();
				}
			}
		}
		void Player::Move_Left() {
			// When we first press the key
			auto v_found = m_current_directions->find('a');
			if (v_found == m_current_directions->end()) {
				m_current_keys.insert(m_current_keys.begin(), 'a');
				m_current_directions->insert('a');

				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(-PLAYER_SPEED, m_player_actor->Physics_Object()->Body()->GetLinearVelocity().y));

				//m_player_actor->Change_Animation(L"Moving_Left", true);

				m_movement_keys = m_movement_keys + 1;
			}
			else {
				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(-PLAYER_SPEED, m_player_actor->Physics_Object()->Body()->GetLinearVelocity().y));

				if (*m_current_keys.begin()._Ptr == 'a') {
					//m_player_actor->Change_Animation(L"Moving_Left", false);
				}
			}

			m_left_bearing = true;
		}
		void Player::Move_Right() {
			// When we first press the key
			auto v_found = m_current_directions->find('d');
			if (v_found == m_current_directions->end()) {
				m_current_keys.insert(m_current_keys.begin(), 'd');
				m_current_directions->insert('d');

				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(PLAYER_SPEED, m_player_actor->Physics_Object()->Body()->GetLinearVelocity().y));

				//m_player_actor->Change_Animation(L"Moving_Right", true);

				m_movement_keys = m_movement_keys + 1;
			}
			else {
				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(PLAYER_SPEED, m_player_actor->Physics_Object()->Body()->GetLinearVelocity().y));

				if (*m_current_keys.begin()._Ptr == 'd') {
					//m_player_actor->Change_Animation(L"Moving_Right", false);
				}
			}

			m_left_bearing = false;
		}
		void Player::Move_Up() {
			// When we first press the key
			auto v_found = m_current_directions->find('w');
			if (v_found == m_current_directions->end()) {
				m_current_keys.insert(m_current_keys.begin(), 'w');
				m_current_directions->insert('w');

				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(m_player_actor->Physics_Object()->Body()->GetLinearVelocity().x, PLAYER_SPEED));

				//m_player_actor->Change_Animation(L"Moving_Up", true);

				m_movement_keys = m_movement_keys + 1;
			}
			else {
				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(m_player_actor->Physics_Object()->Body()->GetLinearVelocity().x, PLAYER_SPEED));

				if (*m_current_keys.begin()._Ptr == 'w') {
					//m_player_actor->Change_Animation(L"Moving_Up", false);
				}
			}
		}
		void Player::Move_Down() {
			// When we first press the key
			auto v_found = m_current_directions->find('s');
			if (v_found == m_current_directions->end()) {
				m_current_keys.insert(m_current_keys.begin(), 's');
				m_current_directions->insert('s');

				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(m_player_actor->Physics_Object()->Body()->GetLinearVelocity().x, -PLAYER_SPEED));

				//m_player_actor->Change_Animation(L"Moving_Down", true);

				m_movement_keys = m_movement_keys + 1;
			}
			else {
				m_player_actor->Physics_Object()->Body()->SetLinearVelocity(b2Vec2(m_player_actor->Physics_Object()->Body()->GetLinearVelocity().x, -PLAYER_SPEED));

				if (*m_current_keys.begin()._Ptr == 's') {
					//m_player_actor->Change_Animation(L"Moving_Down", false);
				}
			}
		}
		void Player::End_Move_Left() {
			auto v_found = m_current_directions->find('a');
			if (v_found != m_current_directions->end()) {
				for (auto i = m_current_keys.begin(); i != m_current_keys.end(); i++) {
					if (*i._Ptr == 'a') {
						m_current_keys.erase(i);
						break;
					}
				}
				m_current_directions->erase('a');
			}
			m_movement_keys = m_movement_keys - 1;
		}
		void Player::End_Move_Right() {
			auto v_found = m_current_directions->find('d');
			if (v_found != m_current_directions->end()) {
				for (auto i = m_current_keys.begin(); i != m_current_keys.end(); i++) {
					if (*i._Ptr == 'd') {
						m_current_keys.erase(i);
						break;
					}
				}
				m_current_directions->erase('d');
			}
			m_movement_keys = m_movement_keys - 1;
		}
		void Player::End_Move_Up() {
			auto v_found = m_current_directions->find('w');
			if (v_found != m_current_directions->end()) {
				for (auto i = m_current_keys.begin(); i != m_current_keys.end(); i++) {
					if (*i._Ptr == 'w') {
						m_current_keys.erase(i);
						break;
					}
				}
				m_current_directions->erase('w');
			}
			m_movement_keys = m_movement_keys - 1;
		}
		void Player::End_Move_Down() {
			auto v_found = m_current_directions->find('s');
			if (v_found != m_current_directions->end()) {
				for (auto i = m_current_keys.begin(); i != m_current_keys.end(); i++) {
					if (*i._Ptr == 's') {
						m_current_keys.erase(i);
						break;
					}
				}
				m_current_directions->erase('s');
			}
			m_movement_keys = m_movement_keys - 1;
		}
		void Player::Interact() {
			PRINT_MSG(L"Game", L"Interact", GAME_MSG);
			auto v_found = m_interactions->find(m_current_zone);
			if (v_found != m_interactions->end()) {
				v_found->second->Test_Interaction(du::Interaction::Interaction_Type::INTERACT);
			}
		}
		void Player::Attack() {
			PRINT_MSG(L"Game", L"Attack", GAME_MSG);
			auto v_found = m_interactions->find(m_current_zone);
			if (v_found != m_interactions->end()) {
				v_found->second->Test_Interaction(du::Interaction::Interaction_Type::ATTACK);
			}
		}
		void Player::Set_Player_Actor(pw::st::Actor* p_new_actor) {
			m_player_actor = p_new_actor;
		}
		pw::st::Actor* Player::Player_Actor() {
			return m_player_actor;
		}
		void Player::Zone_1_Before_Queue() {
			pw::st::Camera::Center_Camera(m_player_actor->Model()->Calculate_Center());

			// Inventory Options



			if (m_movement_keys == 0) {
				if (m_left_bearing == false) {
					//m_player_actor->Change_Animation(L"Idle_R", true);
				}
				else {
					//m_player_actor->Change_Animation(L"Idle_L", true);
				}
			}
		}
		void Player::Zone_1_After_Queue() {
			m_interaction_area->Render();

			glm::vec2 v_player_center = m_player_actor->Model()->Calculate_Center();

			float v_mouse_angle = pw::cm::Engine_Math::Vector_Angle(v_player_center, pw::cm::Engine_Constant::Mouse_Coord());

			float v_cos_angle = glm::cos(glm::radians(v_mouse_angle));
			float v_sin_angle = glm::sin(glm::radians(v_mouse_angle));

			glm::vec2 v_center_offset{ 0.0f };
			glm::vec2 v_position_offset{ 0.0f };

			v_position_offset = m_player_actor->Model()->Calculate_Center() - m_player_actor->Model()->Position();

			v_center_offset.x = m_player_actor->Model()->Size().x * v_cos_angle;
			v_center_offset.y = -m_player_actor->Model()->Size().y * v_sin_angle;

			v_position_offset.x = v_position_offset.x * v_cos_angle;
			v_position_offset.y = v_position_offset.y * v_sin_angle;

			v_center_offset = v_center_offset - v_position_offset;

			v_center_offset.y = -v_center_offset.y;

			v_center_offset.x = v_center_offset.x + ((m_player_actor->Model()->Size().x - m_interaction_area->Model()->Size().x) / 2.0f);

			v_center_offset.y = v_center_offset.y + ((m_player_actor->Model()->Size().y - m_interaction_area->Model()->Size().y) / 2.0f);

			v_center_offset.x = v_center_offset.x + ((m_interaction_area->Model()->Size().x / 2.0f) * v_cos_angle);

			v_center_offset.y = v_center_offset.y + ((m_interaction_area->Model()->Size().y / 2.0f) * v_sin_angle);

			v_center_offset.y = v_center_offset.y - (m_player_actor->Model()->Size().y - m_interaction_area->Model()->Size().y);

			m_interaction_area->Model()->Set_Offset(v_center_offset);

			m_interaction_area->Model()->Set_Rotation(v_mouse_angle, m_interaction_area->Physics_Object()->Body());
		}
	// End of Class Members
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////