// BSD 3 - Clause License
//
// Copyright(c) 2021-2023, Darrian Corkadel
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
#ifndef H_TEXT_RENDERER
#define H_TEXT_RENDERER
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <map>
#include <algorithm>
#include <cstring>
#include <cmath>
#pragma warning(pop)
//////////////////////////////////
// Project Headers 
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <glm\glm.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
#include "control\file_finder.h"
//////////////////////////////////
// Engine Structures Headers
#include "structures\model.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Text_Renderer {
		// Default Class Structures
		public:
			class Character {
				// Default Class Structures
			public:
				/* Error List: PW_FUNCTION_ERROR */
				Character(const wchar_t& p_type, BYTE* p_character_data, const glm::ivec2& p_character_size, const glm::ivec2& p_baseline_offset, const uint32_t& p_spacing);
				/* Error List: NONE */
				~Character();
			private:
				// Public Functions/Macros
			public:
				// Public Variables   
			public:
				/* Error List: NONE */
				const wchar_t& Type() const;
				/* Error List: PW_FUNCTION_ERROR, PW_NULL_PARAMETER_S */
				st::Texture* Character_Data();
				/* Error List: NONE */
				const glm::ivec2& Character_Size() const;
				/* Error List: NONE */
				const glm::ivec2& Baseline_Offset() const;
				/* Error List: NONE */
				const uint32_t& Spacing() const;
				/* Error List: NONE */
				void Set_Type(const wchar_t& p_type);
				/* Error List: NONE */
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
		private:
		// Protected Functions/Macros
		protected:
			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: PW_FT_ERROR, PW_FUNCTION_ERROR */
			static void Load_Engine_Fonts_Default();
			/* Error List: PW_FT_ERROR, PW_FUNCTION_ERROR */
			static void Load_Engine_Fonts(const std::wstring& p_font_location, const std::vector<std::wstring>& p_font_ids, const std::vector<std::wstring>& p_font_names);
			/* Error List: NONE */
			static void Release();
			/* Error List: NONE */
			static Character* Create_Character(const wchar_t& p_letter_type, const std::wstring& p_font_type);
		// Protected Variables   
		protected:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			// Default fonts are loaded from engine font directory
			static std::vector<std::wstring> m_default_font_ids;
			static std::vector<std::wstring> m_default_font_names;
			static std::map<std::wstring, std::map<wchar_t, Character*>>* m_font_library;
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_TEXT_RENDERER
