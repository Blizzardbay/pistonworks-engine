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
#ifndef H_SOUND
#define H_SOUND
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
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <glm\glm.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"   
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers     
#include "structures\camera.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		class Sound {
		// Default Class Structures 
		public:
			/* Error List: NONE */
			Sound();
			/* Error List: PW_NO_AUDIO_SOURCE_ERROR, PW_AL_ERROR */
			Sound(const uint32_t& p_source_id, const bool& p_loop);
			/* Error List: PW_AL_ERROR */
			~Sound();
		private:
		// Public Functions/Macros  
		public:
			/* Error List: PW_AL_ERROR */
			void Update();
			/* Error List: PW_AL_ERROR, PW_FUNCTION_ERROR */
			void Play(bool p_reset_play);
			/* Error List: PW_AL_ERROR */
			void Pause();
			/* Error List: PW_AL_ERROR */
			void Stop();
			/* Error List: PW_AL_ERROR */
			void Reset();
			/* Error List: PW_AL_ERROR */
			void Set_Volume(const float& p_new_gain, const bool& p_windows_style);
			/* Error List: NONE */
			void Attach(const std::function<glm::vec2()>& p_center_calculator);
			/* Error List: NONE */
			const bool& Start();
			/* Error List: NONE */
			const bool& End();
			/* Error List: NONE */
			const int32_t& State() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			bool m_start;
			bool m_end;
			// When a sound stops without a event
			bool m_natural_stop;

			bool m_loop;

			uint32_t m_audio_source_id;
			glm::vec2 m_position;
			std::function<glm::vec2()> m_center_calculator;

			int32_t m_source_state;
		};
		struct Sound_Structure {
		// Default Class Structures 
		public:
			/* Error List: NONE */
			Sound_Structure(st::Sound* p_sound);
			/* Error List: PW_SOUND_ID_SIZE_MISMATCH */
			Sound_Structure(const std::vector<st::Sound*>& p_sounds, const std::vector<std::wstring>& p_sound_ids);
			/* Error List: NONE */
			~Sound_Structure();
		private:
		// Public Functions/Macros  
		public:
			/* Error List: NONE */
			st::Sound* Sound() const;
			/* Error List: NONE */
			st::Sound* Sound(const std::wstring& p_sound_id);
			/* Error List: NONE */
			std::map<std::wstring, st::Sound*>* All_Sounds();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			bool m_single_sound;
			std::map<std::wstring, st::Sound*> m_sounds;
			st::Sound* m_current_access;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_SOUND