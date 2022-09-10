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
#ifndef H_INTERACTIONS
#define H_INTERACTIONS
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#include "engine_structures\engine_game_scene.h"
//////////////////////////////////
// Game Common Headers
#include "common_headers\macro.h"
//////////////////////////////////
// Game Structures Headers
//////////////////////////////////
// Duralumin					//
// Created By : Darrian Corkadel//
//////////////////////////////////
DU_NAMESPACE_SRT
//////////////////////////////////
	class Interaction {
	// Default Class Structures
	public:
		enum class Interaction_Type {
			INTERACT,
			ATTACK
		};

		Interaction(pw::st::Event_Base* p_event, pw::st::Actor* p_base_actor, const Interaction_Type& p_interaction_type);
		~Interaction();
	private:
	// Public Functions/Macros
	public:
		// If the interaction is the same as the interaction type
		// then it will trigger the event function callback
		void Test_Interaction(pw::st::Actor* p_player, const Interaction_Type& p_interaction_type);

		static quadtree::Box<float> Get_Box(Interaction* p_interaction);

		pw::st::Actor* Actor();
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		pw::st::Event_Base* m_event;
		pw::st::Actor* m_base_actor;
		uint64_t m_interaction_id;
		Interaction_Type m_interaction_type;

		static uint64_t m_interaction_id_counter;
	};
	class Interaction_Group {
	// Default Class Structures
	public:
		Interaction_Group(pw::st::Actor* p_player, std::wstring p_scene);
		~Interaction_Group();
	private:
	// Public Functions/Macros
	public:
		void Add_Interaction(Interaction* p_interaction);
		void Delete_Interaction(Interaction* p_interaction);

		void Test_Interaction(const Interaction::Interaction_Type& p_interaction_type);
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		std::vector<Interaction*> m_interaction_holder;
		std::wstring m_scene;

		quadtree::Quadtree<Interaction*, std::function<quadtree::Box<float>(Interaction*)>> m_quadtree_interacter;
		quadtree::Box<float> m_quadtree_interaction_box;

		pw::st::Actor* m_player;
	};
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////
#endif // !H_INTERACTIONS