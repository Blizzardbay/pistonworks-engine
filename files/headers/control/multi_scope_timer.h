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
#ifndef H_MULTI_SCOPE_TIMER
#define H_MULTI_SCOPE_TIMER
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <map>
#include <chrono>
#include <optional>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "structures\timer.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Multi_Scope_Timer {
		// Default Class Structures
		public:
			/* Error List: NONE */
			Multi_Scope_Timer();
			/* Error List: NONE */
			Multi_Scope_Timer(const std::wstring& p_identifier);
			/* Error List: NONE */
			~Multi_Scope_Timer();
		private:
		// Protected Functions/Macros 
		protected:
			/* Error List: PW_FUNCTION_ERROR */
			static void Initialize();
			/* Error List: NONE */
			static void Release();
		// Protected Variables
		protected:
		// Public Functions/Macros
		public:
			/* Error List: NONE */
			template<class duration, class precision>
			const precision End(const std::wstring& p_identifier);
			/* Error List: PW_FUNCTION_ERROR, PW_WIN_FUNCTION_ERROR */
			template<class duration, class precision>
			const std::optional<precision> Print_End(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time = false);
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static std::map<std::wstring, std::chrono::steady_clock::time_point>* m_timer_pool;
		};
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_MULTI_SCOPE_TIMER