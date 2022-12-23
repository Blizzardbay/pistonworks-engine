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
#ifndef H_ENGINE_TIMER
#define H_ENGINE_TIMER
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <glm\common.hpp>
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_constant.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
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
	CM_NAMESPACE_SRT
	//////////////////////////////////
		class Engine_Timer {
		// Default Class Structures
		public:
			Engine_Timer(const float& p_timer_length, const bool& p_start_ready, const bool& p_reset) :
					m_activation_time{},
					m_timer_length{ p_timer_length }, m_start_ready{ p_start_ready }, m_should_reset{ p_reset }, m_reseted{ false } {
			}
		private:
		// Public Functions/Macros 
		public:
			// On each call of use the timer will check if the
			// time has been reached, if it has then return true and
			// reset.
			bool Use() {
				if (m_start_ready == true) {
					m_start_ready = false;
					return true;
				}
				if (m_activation_time >= cm::Engine_Constant::Current_Time() && m_reseted == true) {
					return false;
				}
				if (m_should_reset == false) {
					m_reseted = false;
					return true;
				}
				m_reseted = true;
				m_activation_time = cm::Engine_Constant::Current_Time() + std::chrono::milliseconds(TO_INT32(m_timer_length));
				return true;
			}
			// If the time is not reseting automatically
			// turn it on and
			void Reset() {
				m_reseted = true;
				m_activation_time = cm::Engine_Constant::Current_Time() + std::chrono::milliseconds(TO_INT32(m_timer_length));
			}
			// This will return how much time left out of x / 1
			// we are at
			float Time_Left() {
				return glm::clamp(TO_FLOAT(cm::Engine_Constant::Current_Time().time_since_epoch() / m_activation_time.time_since_epoch()), 0.0f, 1.0f);
			}
			const float& Timer_Length() {
				return m_timer_length;
			}
			const bool& Start_Ready() {
				return m_start_ready;
			}
			const bool& Should_Reset() {
				return m_should_reset;
			}
			const bool& Reseted() {
				return m_reseted;
			}
			const std::chrono::system_clock::time_point& Activation_Time() {
				return m_activation_time;
			}
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			// The timer length in seconds
			float m_timer_length;

			bool m_start_ready;
			bool m_should_reset;
			bool m_reseted;

			std::chrono::system_clock::time_point m_activation_time;
		};
	//////////////////////////////////
	CM_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_TIMER