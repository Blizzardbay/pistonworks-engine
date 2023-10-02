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
#ifndef H_ASYNC_TIMER
#define H_ASYNC_TIMER
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning (push)
#pragma warning (disable: PW_ALL_WARNINGS)
#include <map>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable: PW_ALL_WARNINGS)
#include <glm\common.hpp>
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "common\constant.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "structures\timer.h"
#include "structures\event.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Async_Timer {
		// Default Class Structures
		public:
		private:
		// Protected Functions/Macros 
		protected:
			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: NONE */
			static void Release();
		// Public Functions/Macros 
		public:
			// Polls all of the timers stored in m_timers
			// Error List: NONE 
			static void Poll();
			/* Error List: NONE */
			static void Add(const std::wstring& p_timer_id, pw::st::Manual_Timer<std::chrono::milliseconds>* p_timer, pw::st::Event_Base* p_callback);
			/* Error List: NONE */
			static void Remove(const std::wstring& p_timer_id);
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static std::map<std::wstring, std::pair<pw::st::Manual_Timer<std::chrono::milliseconds>*, pw::st::Event_Base*>>* m_timers;
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_ASYNC_TIMER
