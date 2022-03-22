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
#ifndef H_ENGINE_SOUND
#define H_ENGINE_SOUND
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
#include <cassert>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning (push)
#pragma warning (disable:4201)
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <glm\glm.hpp>
#pragma warning (pop)
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"   
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers     
#include "engine_structures\engine_camera.h"
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
		class Listener {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Creates the context for the listener before hand
			static void Create_Listener(const glm::vec3& p_up_vector = st::Camera::Up_Vector(), glm::vec3& p_at_vector = st::Camera::At_Vector());
			static void Create_Listener(const std::function<glm::vec2()>& p_position_tie,
				const glm::vec3& p_up_vector = st::Camera::Up_Vector(), glm::vec3& p_at_vector = st::Camera::At_Vector());
			static void Change_Bound_Listener(const std::function<glm::vec2()>& p_new_position_tie);

			static void Update();
			// Once the listener is deleted it cannot be re-created
			static void Release_Listener();

			static void Set_Volume(const float& p_new_gain, const bool& p_windows_style);
			// Sets the current device for audio outputting
			static void Set_Device(const std::wstring& p_device_name);
			// Returns all of the current devices for audio output
			static std::vector<std::wstring> Get_Device_List();
			static std::wstring Device_Name();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			// You can only create one listener per engine instance
			static bool m_created_listener;
			// When you bind the listener to a object that must 
			// be directly tied to the host model's position 
			static std::function<glm::vec2()> m_position_calculator;
			static glm::vec2 m_position;
			static glm::vec3 m_up_vector;
			static glm::vec3& m_at_vector;
			static ALCdevice* m_current_device;
			static ALCcontext* m_context;
		};
		class Sound {
		// Default Class Structures 
		public:
			Sound();
			Sound(const uint32_t& p_source_id, const bool& p_loop);
			~Sound();
		private:
		// Public Functions/Macros  
		public:
			void Update();
			void Play(bool p_reset_play);
			void Pause();
			void Stop();
			void Reset();
			void Set_Volume(const float& p_new_gain, const bool& p_windows_style);

			void Attach(const std::function<glm::vec2()>& p_center_calculator);

			const bool& Start();
			const bool& End();
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
			Sound_Structure(st::Sound* p_sound);
			Sound_Structure(const std::vector<st::Sound*>& p_sounds, const std::vector<std::wstring>& p_sound_ids);
			~Sound_Structure();
		private:
		// Public Functions/Macros  
		public:
			st::Sound* Sound() const;
			st::Sound* Sound(const std::wstring& p_sound_id);
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
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_SOUND