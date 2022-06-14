#include "structure_headers\interactions.h"

//////////////////////////////////
DU_NAMESPACE_SRT
//////////////////////////////////
	// Interactions
	// Static Declarations
	uint64_t Interaction::m_interaction_id_counter{ 0 };
	// Class Members
	Interaction::Interaction(pw::st::Event_Base* p_event, pw::st::Actor* p_base_actor, const Interaction_Type& p_interaction_type) :
			m_event{ p_event }, m_base_actor{ p_base_actor }, m_interaction_id{ m_interaction_id_counter++ }, m_interaction_type{ p_interaction_type } {
	}
	Interaction::~Interaction() {
		pw::Engine_Memory::Deallocate<pw::st::Event_Base>(m_event);
	}
	void Interaction::Test_Interaction(pw::st::Actor* p_player, const Interaction_Type& p_interaction_type) {
		if (p_interaction_type == m_interaction_type) {
			if (p_player->Test_Collision(m_base_actor) == true) {
				m_event->Trigger_Event();
			}
		}
	}
	quadtree::Box<float> Interaction::Get_Box(Interaction* p_interaction) {
		return pw::st::Game_Scene::Get_Box(p_interaction->m_base_actor);
	}
	pw::st::Actor* Interaction::Actor() {
		return m_base_actor;
	}
	// End of Class Members
	// Interaction_Group
	// Static Declarations
	// Class Members
	Interaction_Group::Interaction_Group(pw::st::Actor* p_player, std::wstring p_scene) :
			m_interaction_holder{}, m_scene{ p_scene },
			m_quadtree_interaction_box{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, 2.0f * (float)INT32_MAX, 2.0f * (float)INT32_MAX} },
			m_quadtree_interacter{ quadtree::Box<float>{(float)INT32_MIN, (float)INT32_MIN, 2.0f * (float)INT32_MAX, 2.0f * (float)INT32_MAX},
			Interaction::Get_Box },
			m_player{ p_player } {
	}
	Interaction_Group::~Interaction_Group() {
		for (auto i = m_interaction_holder.begin(); i != m_interaction_holder.end(); i++) {
			pw::Engine_Memory::Deallocate<Interaction>(*i);
		}
		m_interaction_holder.clear();
	}
	void Interaction_Group::Add_Interaction(Interaction* p_interaction) {
		if (p_interaction != nullptr) {
			m_interaction_holder.push_back(p_interaction);
			
			m_quadtree_interacter.add(p_interaction);
		}
	}
	void Interaction_Group::Delete_Interaction(Interaction* p_interaction) {
		if (p_interaction != nullptr) {
			for (auto i = m_interaction_holder.begin(); i != m_interaction_holder.end(); i++) {
				if (*i == p_interaction) {
					m_interaction_holder.erase(i);
					break;
				}
			}
			m_quadtree_interacter.remove(p_interaction);

			pw::Engine_Memory::Deallocate<Interaction>(p_interaction);
		}
	}
	void Interaction_Group::Test_Interaction(const Interaction::Interaction_Type& p_interaction_type) {
		glm::vec2 v_camera_position = pw::st::Camera::Camera_Position();
		glm::vec2 v_camera_size = pw::st::Camera::Camera_Size();

		quadtree::Box<float> v_screen_box = quadtree::Box<float>(v_camera_position.x, v_camera_position.y - v_camera_size.y,
			v_camera_size.x, v_camera_size.y);

		std::vector<Interaction*> v_interactions{};

		if (m_quadtree_interaction_box.intersects(v_screen_box) == true) {
			v_interactions = m_quadtree_interacter.query(v_screen_box);
		}

		for (auto i = v_interactions.begin(); i != v_interactions.end(); i++) {
			(*i)->Test_Interaction(m_player, p_interaction_type);
		}
	}
	// End of Class Members
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////