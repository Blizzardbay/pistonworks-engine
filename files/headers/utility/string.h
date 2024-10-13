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
#include "common\error_state.h"
//////////////////////////////////
// Engine Control Headers
#include "control\memory.h"
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		class String {
		// Friends
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			#define TO_WCHAR(c_str)				pw::util::String::Evaluate_WStr(c_str)
			#define TO_CHAR(w_str)				pw::util::String::Evaluate_Str(w_str)
			#define TO_WSTRING(c_str)			pw::util::String::Evaluate_TWStr(c_str)
			#define TO_STRING(w_str)			pw::util::String::Evaluate_TStr(w_str)

			/* Error List: PW_FUNCTION_ERROR, PW_UNKNOWN_STRING_TYPE */
			_NODISCARD static wchar_t* Evaluate_WStr(const std::any& p_str) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static wchar_t* To_WChar(const char* p_msg) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static wchar_t* To_WChar(const std::string& p_msg) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static wchar_t* To_WChar(const wchar_t* p_msg) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static wchar_t* To_WChar(const std::wstring& p_msg) noexcept;
			/* Error List: PW_FUNCTION_ERROR, PW_UNKNOWN_STRING_TYPE */
			_NODISCARD static char* Evaluate_Str(const std::any& p_str) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static char* To_Char(const wchar_t* p_msg) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR, PW_BUFFER_SIZE_MISMATCH, PW_CRT_FUNCTION_FAILURE */
			_NODISCARD static char* To_Char(const std::wstring& p_msg) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static char* To_Char(const char* p_msg) noexcept;
			/* Error List: PW_NULL_PARAMETER_W, PW_EMPTY_PARAMETER_W, PW_FUNCTION_ERROR */
			_NODISCARD static char* To_Char(const std::string& p_msg) noexcept;
			/* Error List: PW_FUNCTION_ERROR */
			_NODISCARD static std::wstring Evaluate_TWStr(const std::any& p_str) noexcept;
			/* Error List: PW_FUNCTION_ERROR */
			_NODISCARD static std::string Evaluate_TStr(const std::any& p_str) noexcept;

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