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
#ifndef H_TEXT
#define H_TEXT
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers 
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
#include "control\text_renderer.h"
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
#include "utility\string.h"
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		class Text : public pw::co::Text_Renderer {
		// Default Class Structures
		public:
			enum class Color_Settings {
				// All text is one color
				SOLID_ALL,
				// Color[i], For i + increment
				SINGLE_REPEAT,
				// Color[i], Word[i]
				WORD_REPEAT,
				// Color[i] applied based on cypher
				TARGET_CYPHER
			};
			/* Error List: NONE */
			Text();
			/* Error List: PW_FUNCTION_ERROR */
			Text(const std::wstring& p_text, const glm::vec2& p_position, const glm::vec2& p_size, const glm::vec4& p_color, const std::wstring& p_font_type);
			// Error List: PW_FUNCTION_ERROR 
			Text(const std::wstring& p_text, const glm::vec2& p_position, const glm::vec2& p_size, const glm::vec4& p_default_color, const std::vector<glm::vec4>& p_colors, const std::wstring& p_font_type, const Color_Settings& p_settings);
			// Error List: PW_FUNCTION_ERROR 
			Text(const std::wstring& p_text, const glm::vec2& p_position, const glm::vec2& p_size, const glm::vec4& p_default_color, const std::vector<std::pair<glm::vec4, std::vector<std::wstring>>>& p_colors, const std::wstring& p_font_type);

			Text& operator=(Text&& p_rhs) noexcept;
			/* Error List: NONE */
			~Text();
		private:
		// Public Functions/Macros
		public:
		// Public Variables   
		public:
			/* Error List: PW_FUNCTION_ERROR */
			void Render();
			/* Error List: NONE */
			void Set_Position(const glm::vec2& p_new_position);
			/* Error List: NONE */
			void Set_Offset(const glm::vec3& p_from);
			/* Error List: PW_FUNCTION_ERROR */
			void Set_Text(const std::wstring& p_new_text);
			/* Error List: NONE */
			void Set_Size(const glm::vec2& p_size);
			/* Error List: PW_FUNCTION_ERROR */
			void Set_Text_Color(const glm::vec4& p_new_color);
			/* Error List: NONE */
			glm::vec2& Position_Reference();
			/* Error List: NONE */
			const glm::vec2& Position() const;
			/* Error List: NONE */
			const glm::vec2& Size() const;
			/* Error List: NONE */
			const uint64_t Count() const;
			/* Error List: NONE */
			const std::wstring& String() const;
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			std::wstring m_text;
			std::vector<st::Model*> m_text_string;
			glm::vec2 m_text_position;
			glm::vec2 m_text_size;

			Color_Settings m_current_settings;

			glm::vec4 m_default_color;
			// The second std::pair member will be zero if non-cypher pattern
			std::vector<std::pair<glm::vec4, std::vector<std::wstring>>> m_stored_cypher_colors;
			std::vector<glm::vec4> m_stored_colors;

			// When the structure is first created
			// what are the initial text placement values
			glm::vec2 m_raw_text_position;
			glm::vec2 m_raw_text_size;

			std::wstring m_text_font;

			bool m_is_copy;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_TEXT