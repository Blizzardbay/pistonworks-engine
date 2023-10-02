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
#ifndef H_STRING
#define H_STRING
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <string>
#include <vector>
#include <algorithm>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\macro.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		class String {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			/* Error List: NONE */
			static std::vector<std::wstring> Parse(const std::wstring& p_input, const std::vector<std::wstring>& p_delimeters);
			/* Error List: NONE */
			static std::vector<std::wstring> Parse_English(const std::wstring& p_input, std::vector<std::wstring> p_custom_delimeters = std::vector<std::wstring>());
			/* Error List: NONE */
			static std::vector<uint64_t> Find_All_Delimiters(const std::wstring& p_input, const std::vector<std::wstring>& p_delimeters);
			/* Error List: NONE */
			static std::vector<uint64_t> Find_All_Delimiters_English(const std::wstring& p_input, std::vector<std::wstring> p_custom_delimeters = std::vector<std::wstring>());
			/* Error List: NONE */
			static std::vector<uint64_t> Find_All_Words(const std::wstring& p_input, const std::vector<std::wstring>& p_delimeters);
			/* Error List: NONE */
			static std::vector<uint64_t> Find_All_Words_English(const std::wstring& p_input, std::vector<std::wstring> p_custom_delimeters = std::vector<std::wstring>());
			/* Error List: NONE */
			static std::vector<uint64_t> Find_All_Unsorted(const std::wstring& p_input, const std::vector<std::wstring>& p_phrases);
			/* Error List: NONE */
			static std::vector<uint64_t> Find_All_Sorted(const std::wstring& p_input, const std::vector<std::wstring>& p_phrases);
		// Public Variables        
		public:
		};
	UTIL_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_STRING