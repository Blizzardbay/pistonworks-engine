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
#ifndef H_TIMER
#define H_TIMER
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <glm\common.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\constant.h"
//////////////////////////////////
// Engine Control Headers
#include "control\console_manip.h"
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		template<class duration>
		class Time;
		class Time_Constant {
		// Friends
			friend class pw::co::Control;
			template<class duration>
			friend class Time;
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
		// Public Variables
		public:
		// Private Functions/Macros
		private:
			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: NONE */
			static void Release();
		// Private Variables
		private:
			static std::map<std::string, std::wstring>* m_time_total;
			static std::map<std::string, std::wstring>* m_time_postfix;
		};
		template<class duration>
		class Time {
			static_assert(std::is_same_v<duration, std::chrono::nanoseconds> ||
				std::is_same_v<duration, std::chrono::microseconds> ||
				std::is_same_v<duration, std::chrono::milliseconds> ||
				std::is_same_v<duration, std::chrono::seconds> ||
				std::is_same_v<duration, std::chrono::minutes> ||
				std::is_same_v<duration, std::chrono::hours> ||
				std::is_same_v<duration, std::chrono::days> ||
				std::is_same_v<duration, std::chrono::months> ||
				std::is_same_v<duration, std::chrono::years>);
		// Friends
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			/* Error List: NONE */
			std::wstring Total();
			/* Error List: NONE */
			std::wstring Postfix();
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
		};
		template<class duration>
		class Manual_Timer : public Time<duration> {
		// Friends
		// Default Class Structures
		public:
			/* Error List: NONE */
			_NODISCARD Manual_Timer(const uint64_t& p_timer_length, const bool p_start_ready, const bool p_reset) noexcept;
		private:
		// Public Functions/Macros 
		public:
			// On each call of use the timer will check if the
			// time has been reached, if it has then return true and
			// reset.
			// Error List: NONE
			_NODISCARD bool Use() noexcept;
			// If the time is not reseting automatically, manually set it.
			// Error List: NONE 
			void Reset() noexcept;
			// This will return how much time left out of x / 1 we are at.
			// Error List: NONE 
			_NODISCARD const float Time_Left() const noexcept;
			/* Error List: NONE */
			template<class precision>
			_NODISCARD const precision& Timer_Length() noexcept;
			/* Error List: NONE */
			_NODISCARD const bool Start_Ready() noexcept;
			/* Error List: NONE */
			_NODISCARD const bool Should_Reset() noexcept;
			/* Error List: NONE */
			_NODISCARD const bool Reseted() noexcept;
			/* Error List: NONE */
			_NODISCARD const std::chrono::steady_clock::time_point& Activation_Time() noexcept;
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			// The timer length in seconds
			uint64_t m_timer_length;

			bool m_start_ready;
			bool m_started;
			bool m_should_reset;
			bool m_reseted;

			std::chrono::steady_clock::time_point m_activation_time;
		};
		template<class duration, class precision>
		class Scope_Timer : public Time<duration> {
			static_assert(std::is_same_v<precision, int64_t> ||
				std::is_same_v<precision, float> ||
				std::is_same_v<precision, double>);
		// Friends
		// Default Class Structures
		public:
			/* Error List: NONE */
			Scope_Timer(const pw::co::cn::Msg_Types& p_msg_type) noexcept;
			/* Error List: PW_FUNCTION_ERROR, PW_WIN_FUNCTION_ERROR */
			~Scope_Timer() noexcept;
		private:
		// Public Functions/Macros 
		public:
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			pw::co::cn::Msg_Types m_msg_type;
			std::chrono::steady_clock::time_point m_start_time;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_TIMER