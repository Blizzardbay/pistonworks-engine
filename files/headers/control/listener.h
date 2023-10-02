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
#ifndef H_LISTENER
#define H_LISTENER
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
	CO_NAMESPACE_SRT
		class Listener {
		// Default Class Structures 
		public:
		private:
		// Protected Functions/Macros  
		protected:
			// Creates the context for the listener before hand
			// Error List: PW_AUDIO_SOURCE_NOT_FOUND, PW_AL_ERROR
			static void Create_Listener(const glm::vec3& p_up_vector = st::Camera::Up_Vector(), glm::vec3& p_at_vector = st::Camera::At_Vector());
			/* Error List: PW_AUDIO_SOURCE_NOT_FOUND, PW_AL_ERROR */
			static void Create_Listener(const std::function<glm::vec2()>& p_position_tie,
				const glm::vec3& p_up_vector = st::Camera::Up_Vector(), glm::vec3& p_at_vector = st::Camera::At_Vector());

			/* Error List: PW_AL_ERROR */
			static void Update();
			// Once the listener is deleted it cannot be re-created
			// Error List: NONE
			static void Release();
		// Protected Variables         
		protected:
		// Public Functions/Macros  
		public:
			/* Error List: PW_AL_ERROR */
			static void Change_Bound_Listener(const std::function<glm::vec2()>& p_new_position_tie);

			/* Error List: PW_AL_ERROR */
			static void Set_Volume(const float& p_new_gain, const bool& p_windows_style);
			// Sets the current device for audio outputting
			// Error List: PW_AUDIO_SOURCE_NOT_FOUND
			static void Set_Device(const std::wstring& p_device_name);

			// Returns all of the current devices for audio output
			// Error List: NONE
			static std::vector<std::wstring> Get_Device_List();
			/* Error List: NONE */
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
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_LISTENER