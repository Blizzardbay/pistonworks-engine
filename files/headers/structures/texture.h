// BSD 3 - Clause License
//
// Copyright(c) 2021-2024, Darrian Corkadel
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
#ifndef H_TEXTURE
#define H_TEXTURE
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers 
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <cassert>
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
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		class Texture {
		// Friends
		// Default Class Structures 
		public:
			/* Error List: NONE */
			Texture();
			/* Error List: PW_NULL_PARAMETER_W, PW_FUNCTION_ERROR */
			Texture(BYTE* p_tex_data, const uint32_t p_texture_width, const uint32_t p_texture_height, const int32_t p_internal_format, const int32_t p_format, const bool p_repeat = false, const bool p_linear = true);
			/* Error List: PW_NULL_PARAMETER_W, PW_FUNCTION_ERROR */
			Texture(BYTE* p_tex_data, const uint32_t p_target, const uint32_t p_texture_width, const uint32_t p_texture_height, const int32_t p_internal_format, const int32_t p_format, const bool p_repeat = false, const bool p_linear = true);
			/* Error List: NONE */
			Texture(const Texture& p_other);
			/* Error List: PW_NULL_PARAMETER_W, PW_FUNCTION_ERROR */
			~Texture();
		private:
		// Public Functions/Macros  
		public:
			/* Error List: NONE */
			glm::vec2 Size();
			/* Error List: NONE */
			const uint64_t& Texture_Handle() const;
			/* Error List: NONE */
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			bool m_copy;

			uint32_t m_texture_id;

			uint64_t m_texture_handle;

			uint32_t m_texture_width;
			uint32_t m_texture_height;
		};
		struct Texture_Structure {
		// Friends
		// Default Class Structures 
		public:
			/* Error List: NONE */
			Texture_Structure(st::Texture* p_texture);
			/* Error List: PW_ANIMATION_ID_SIZE_MISMATCH */
			Texture_Structure(const std::vector<st::Texture*>& p_textures, const std::vector<std::wstring>& p_texture_ids);
			/* Error List: NONE */
			~Texture_Structure();
		private:
		// Public Functions/Macros 
		public:
			// If the structure only has one texture it will return a ptr to the texture else a nullptr
			// Error List: NONE
			st::Texture* Texture() const;
			/* Error List: NONE */
			st::Texture* Texture(const std::wstring& p_texture_id);
			/* Error List: NONE */
			std::map<std::wstring, st::Texture*>& Textures();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			bool m_single_texture;
			std::map<std::wstring, st::Texture*> m_textures;
			st::Texture* m_current_access;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_TEXTURE