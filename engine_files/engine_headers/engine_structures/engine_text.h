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
#ifndef H_ENGINE_TEXT
#define H_ENGINE_TEXT
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
#include <map>
#include <algorithm>
#include <cstring>
#include <cmath>
#pragma warning (pop)
//////////////////////////////////
// Project Headers 
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4201)
#include <glm\glm.hpp>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
#include "engine_control\engine_file_finder.h"
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_model.h"
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
		class Text_Renderer;
		
		class Character {
		// Default Class Structures
		public:
			Character(const wchar_t& p_type, BYTE* p_character_data, const glm::ivec2& p_character_size, const glm::ivec2& p_baseline_offset, const uint32_t& p_spacing);
			
			~Character();
		private:
		// Public Functions/Macros
		public:
		// Public Variables   
		public:
			const wchar_t& Type() const;
			
			st::Texture* Character_Data();
			
			const glm::ivec2& Character_Size() const;
			
			const glm::ivec2& Baseline_Offset() const;
			
			const uint32_t& Spacing() const;
			
			void Set_Type(const wchar_t& p_type);
			
			void Set_Texture(st::Texture* p_new_texture);
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			wchar_t m_type;
			st::Texture* m_character_data;
			glm::ivec2 m_character_size;
			glm::ivec2 m_baseline_offset;
			uint32_t m_spacing;
		};
		
		class Text {
		// Default Class Structures
		public:
			Text();

			Text(const std::wstring& p_text, const glm::ivec2& p_position, const glm::ivec2& p_size, const glm::vec4& p_color, const std::wstring& p_font_type);
			
			~Text();
		private:
		// Public Functions/Macros
		public:
		// Public Variables   
		public:
			void Render();

			void Set_Position(const glm::vec2& p_new_position);
			
			void Set_Offset(const glm::vec3& p_from);

			void Set_Text(const std::wstring& p_new_text);

			void Set_Size(const glm::vec2& p_size);

			void Set_Text_Color(const glm::vec4& p_new_color);
			
			glm::vec2& Position_Reference();
			
			const glm::vec2& Position() const;
			
			const glm::vec2& Size() const;
			
			const uint64_t Count() const;
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			std::wstring m_text;
			std::vector<st::Model*> m_text_string;
			glm::vec2 m_text_position;
			glm::vec2 m_text_size;
			glm::vec4 m_text_color;
			// When the structure is first created
			// what are the initial text placement values
			glm::vec2 m_raw_text_position;
			glm::vec2 m_raw_text_size;

			std::wstring m_text_font;
		};
		class Text_Renderer {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			static void Initialize_Text_Renderer();

			static void Load_Engine_Fonts(const std::wstring& p_font_location, const std::vector<std::wstring>& p_font_ids, const std::vector<std::wstring>& p_font_names);
			
			static void Release_Engine_Fonts();
			
			static Character* Create_Character(const wchar_t& p_letter_type, const std::wstring& p_font_type);
		// Public Variables   
		public:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			static std::map<std::wstring, std::map<wchar_t, Character*>>* m_font_library;
		};
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_TEXT