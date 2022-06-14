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
#ifndef H_CONSOLE
#define H_CONSOLE
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
	class Console {
	// Default Class Structures
	public:
		enum class Msg_Type {
			INVENTORY,
			SETTINGS,
			GAME,
			COUT
		};
	private:
	// Public Functions/Macros
	public:
		//static void Initialize_Console();
		//static void Release_Console();

		//static void Print_Line(const std::wstring& p_msg, const Msg_Type& p_msg_type);

		//static void Clear_Console();
	// Public Variables
	public:
	// Private Functions/Macros
	private:
	// Private Variables
	private:
		//static pw::st::Actor* m_backaround;
		//static std::vector<pw::st::Text> m_text_log;
		//static uint64_t m_max_size;
	};
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////
#endif // !H_CONSOLE