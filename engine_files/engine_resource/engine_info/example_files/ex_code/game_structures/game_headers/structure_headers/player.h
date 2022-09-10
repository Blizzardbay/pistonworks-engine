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
#ifndef H_PLAYER
#define H_PLAYER
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <map>
#include <functional>
//////////////////////////////////
// Project Headers
#include "engine_common\engine_math.h"
#include "engine_structures\engine_game_scene.h"
#include "engine_control\engine_file_loader.h"
//////////////////////////////////
// Game Common Headers
#include "common_headers\macro.h"
//////////////////////////////////
// Game Structures Headers
#include "structure_headers\interactions.h"
//////////////////////////////////
// Duralumin					//
// Created By : Darrian Corkadel//
//////////////////////////////////
DU_NAMESPACE_SRT
//////////////////////////////////
	class Bush {
	public:
		static void Init(pw::st::Game_Scene* p_zone_1) {
			m_bush = p_zone_1->Access_Model(L"Bush");
		}
		static void Interact() {
			m_bush->Set_Texture(L"FULL_BUSH");
		}
		static void Attack() {
			m_bush->Set_Texture(L"EMPTY_BUSH");
		}
		static pw::st::Actor* m_bush;
	};
	class Player {
	// Default Class Structures
	public:
		enum class Engine_Queue_State {
			BEFORE,
			AFTER
		};

		static void Init_Player(pw::st::Game_Scene* p_zone_1);
		static void Delete_Player();
	private:
	// Public Functions/Macros
	public:
		#define PLAYER_SPEED 4.5f

		static void Choose_Zone(const std::wstring& p_zone, const Player::Engine_Queue_State& p_queue_state);
		static void Set_Zone(const std::wstring& p_zone);

		// For moving around
		static void Move_Left();
		static void Move_Right();
		static void Move_Up();
		static void Move_Down();
		// For animation purposes
		static void End_Move_Left();
		static void End_Move_Right();
		static void End_Move_Up();
		static void End_Move_Down();

		static void Interact();
		static void Attack();

		static void Set_Player_Actor(pw::st::Actor* p_new_actor);
		static pw::st::Actor* Player_Actor();

		// Zone_1
		static void Zone_1_Before_Queue();
		static void Zone_1_After_Queue();
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		// The actor that contains the player information
		static pw::st::Actor* m_player_actor;
		// The actor that interacts with the world
		static pw::st::Actor* m_interaction_area;
		// How many keys are being pressed for character 
		// movement
		static uint32_t m_movement_keys;
		// Where are we moving and when
		static bool m_moving_left;
		static bool m_moving_right;
		static bool m_moving_up;
		static bool m_moving_down;
		static bool m_left_bearing;
		// Have we interacted with anything recently
		static bool m_interacted;

		static std::unordered_set<char>* m_current_directions;
		static std::vector<char> m_current_keys;
		static std::wstring m_current_zone;

		static std::map<std::wstring, std::map<Engine_Queue_State, std::function<void()>>>* m_zone_specifier;
		static std::map<std::wstring, du::Interaction_Group*>* m_interactions;
	};
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////
#endif // !H_PLAYER
