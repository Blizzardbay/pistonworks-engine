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
#ifndef H_ENGINE_EXCEPTION
#define H_ENGINE_EXCEPTION
//////////////////////////////////
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <exception>
#include <stdexcept>
#include <string>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_macro.h"
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
	ER_NAMESPACE_SRT
	//////////////////////////////////
		class Engine_Exception {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			static const uint64_t& Exception_Line() {
				return m_exception_line;
			}
			static void Set_Exception_Line(const uint32_t& p_new_line) {
				m_exception_line = p_new_line;
			}
			// Try the line of code to see if it throws a exception or not
			#define TRY_LINE pw::er::Engine_Exception::Set_Exception_Line(__LINE__);
			// If there is an exception then get the latest line
			// Note if there was no exception the value stored will be the last exception if there was one
			#define EXCEPTION_LINE pw::er::Engine_Exception::Exception_Line()
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static uint64_t m_exception_line;
		};
		class Warning_Error : public std::exception {
		// Default Class Structures
		public:
			Warning_Error(const std::wstring& p_from, const std::wstring& p_msg, const uint64_t& p_line, const std::wstring& p_file,
							const std::wstring& p_function) :
					m_from{ p_from }, m_msg{ p_msg }, m_line{ p_line }, m_file{ p_file }, m_function{ p_function } {
			}
		private:
		// Public Functions/Macros
		public:
			const std::wstring& From() const {
				return m_from;
			}
			const std::wstring& Msg() const {
				return m_msg;
			}
			const uint64_t& Line() const {
				return m_line;
			}
			const std::wstring& File() const {
				return m_file;
			}
			const std::wstring& Function() const {
				return m_function;
			}
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			const std::wstring m_from;
			const std::wstring m_msg;
			const uint64_t m_line;
			const std::wstring m_file;
			const std::wstring m_function;
		};
		class Severe_Error : public std::exception {
		// Default Class Structures
		public:
			Severe_Error(const std::wstring& p_from, const std::wstring& p_msg, const uint64_t& p_line, const std::wstring& p_file,
							const std::wstring& p_function) :
					m_from{ p_from }, m_msg{ p_msg }, m_line{ p_line }, m_file{ p_file }, m_function{ p_function } {
			}
		private:
		// Public Functions/Macros
		public:
			const std::wstring& From() const {
				return m_from;
			}
			const std::wstring& Msg() const {
				return m_msg;
			}
			const uint64_t& Line() const {
				return m_line;
			}
			const std::wstring& File() const {
				return m_file;
			}
			const std::wstring& Function() const {
				return m_function;
			}
			// Public Variables
		public:
			// Private Functions/Macros
		private:
			// Private Variables
		private:
			const std::wstring m_from;
			const std::wstring m_msg;
			const uint64_t m_line;
			const std::wstring m_file;
			const std::wstring m_function;
		};
	//////////////////////////////////
	ER_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_EXCEPTION
