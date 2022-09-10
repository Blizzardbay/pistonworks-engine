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
//////////////////////////////////
// Project Headers
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
	class Item {
	// Default Class Structures
	public:
		Item(std::wstring p_item_name, pw::st::Actor* p_actor);
		~Item();
	private:
	// Public Functions/Macros
	public:
	// Public Variables
	public:
		void Set_Position(const glm::ivec2& p_new_position);
		void Set_Last_Position(const glm::ivec2& p_new_last_position);
		// Reverts back to the last position
		void Revert_Position();

		const glm::ivec2& Position();
		const glm::ivec2& Last_Position();
		pw::st::Actor* Actor();
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		std::wstring m_item_name;

		glm::ivec2 m_position;
		glm::ivec2 m_last_position;
		pw::st::Actor* m_actor;
	};
	class Inventory_Tile {
	// Default Class Structures
	public:
		Inventory_Tile(du::Item* p_item, glm::ivec2 p_position);
		~Inventory_Tile();
	private:
	// Public Functions/Macros
	public:
		bool Is_Open();

		void Set_Item(du::Item* p_new_item);

		const glm::ivec2& Position();
		Item* Item();
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		glm::ivec2 m_position;
		du::Item* m_item;
	};
	class Inventory {
	// Default Class Structures
	public:
	private:
	// Public Functions/Macros
	public:
		// True if the item is added correctly
		// False if not or if inventory is full
		bool Add_Item(du::Item* p_new_item);
		void Remove_Item(du::Item* p_item);

		void Open_Inventory();
		void Close_Inventory();

		void Move_Item();

		void Draw_Inventory();
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		// Holds all of the tile info
		std::array<std::array<Inventory_Tile*, 5>, 5> m_inventory;
		std::unordered_set<du::Item*> m_item_container;
		bool m_is_open;
	};
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////
#endif // !H_PLAYER