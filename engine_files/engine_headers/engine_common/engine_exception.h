// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
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
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <exception>
#include <stdexcept>
#include <string>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Macros
#include "engine_common\engine_macro.h"
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ER_NAMESPACE_SRT
	//////////////////////////////////
		// //////////////////////////////////////////////////
		// PW_ERROR_API Class: pw::er::Engine_Exception
		// //////////////////////////////////////////////////
		// Purpose:
		//  Stores information for the current exception line
		//  since C++ does not have this as a built in
		//  function at runtime without a break point.
		// //////////////////////////////////////////////////
		class PW_ERROR_API Engine_Exception {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR uint64_t& Exception_Line() {
				return m_exception_line;
			}
			// Mutators
			USER_INTERACTION
			static MUTATOR void Set_Exception_Line(const uint32_t&& p_new_line) {
				m_exception_line = p_new_line;
			}
			// Try the line of code to see if it throws a excpetion or not
			#define TRY_LINE pw::er::Engine_Exception::Set_Exception_Line(__LINE__);
			// If there is an excpetion then get the latest line
			// Note if there was no exception the value stored will be the last excpetion if there was one
			#define EXCEPTION_LINE pw::er::Engine_Exception::Exception_Line()
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static uint64_t m_exception_line;
		};
		// //////////////////////////////////////////////////
		// PW_ERROR_API Class: pw::er::Warning_Error
		// //////////////////////////////////////////////////
		// Purpose:
		//  This is a non-fatal error that is a failure of a
		//  non-essential function or functionality.
		// //////////////////////////////////////////////////
		class PW_ERROR_API Warning_Error : public std::exception {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Warning_Error::Warning_Error
			// //////////////////////////////////////////////////
			// Purpose:
			//  Creates a console to be thrown.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) std::wstring p_from;
			// Purpose:
			//  Where is the error from.
			// (2) std::wstring p_msg;
			// Purpose:
			//  The msg or error purpose.
			// (3) uint32_t p_line;
			// Purpose:
			//  The line where the error occurred. 
			// (4) std::wstring p_file;
			// Purpose:
			//  The file in which the error occurred.
			// (5) std::wstring p_function;
			// Purpose:
			//  The function that threw the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Warning_Error(std::wstring&& p_from, std::wstring&& p_msg, uint64_t&& p_line, std::wstring&& p_file, 
				std::wstring&& p_function) :
					m_from{ p_from }, m_msg{ p_msg }, m_line{ p_line }, m_file{ p_file }, m_function{ p_function } {
			}
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Warning_Error::~Warning_Error
			// //////////////////////////////////////////////////
			// Purpose:
			//  Destroys the error.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Warning_Error() {
				LET_CPP_IMPLEMENT
			}
		private:
		// Public Functions/Macros
		public:
			// Accessors
			USER_INTERACTION
			const ACCESSOR std::wstring& From() const {
				return m_from;
			}
			USER_INTERACTION
			const ACCESSOR std::wstring& Msg() const {
				return m_msg;
			}
			USER_INTERACTION
			const ACCESSOR uint64_t& Line() const {
				return m_line;
			}
			USER_INTERACTION
			const ACCESSOR std::wstring& File() const {
				return m_file;
			}
			USER_INTERACTION
			const ACCESSOR std::wstring& Function() const {
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
		// //////////////////////////////////////////////////
		// PW_ERROR_API Class: pw::er::Severe_Error
		// //////////////////////////////////////////////////
		// Purpose:
		//  This is a fatal error that is a failure of a
		//  essential function or functionality. As soon as
		//  the engine gets the message it will exit. Will 
		//  also print out a log file.
		// //////////////////////////////////////////////////
		class PW_ERROR_API Severe_Error : public std::exception {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Severe_Error::Severe_Error
			// //////////////////////////////////////////////////
			// Purpose:
			//  Creates a console to be thrown.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) std::wstring p_from;
			// Purpose:
			//  Where is the error from.
			// (2) std::wstring p_msg;
			// Purpose:
			//  The msg or error purpose.
			// (3) uint32_t p_line;
			// Purpose:
			//  The line where the error occurred. 
			// (4) std::wstring p_file;
			// Purpose:
			//  The file in which the error occurred.
			// (5) std::wstring p_function;
			// Purpose:
			//  The function that threw the error.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Severe_Error(std::wstring&& p_from, std::wstring&& p_msg, uint64_t&& p_line, std::wstring&& p_file,
				std::wstring&& p_function) :
					m_from{ p_from }, m_msg{ p_msg }, m_line{ p_line }, m_file{ p_file }, m_function{ p_function } {
			}
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Severe_Error::~Severe_Error
			// //////////////////////////////////////////////////
			// Purpose:
			//  Destroys the error.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Severe_Error() {
				LET_CPP_IMPLEMENT
			}
		private:
			// Public Functions/Macros
		public:
			// Accessors
			USER_INTERACTION
			const ACCESSOR std::wstring& From() const {
				return m_from;
			}
			USER_INTERACTION
			const ACCESSOR std::wstring& Msg() const {
				return m_msg;
			}
			USER_INTERACTION
			const ACCESSOR uint64_t& Line() const {
				return m_line;
			}
			USER_INTERACTION
			const ACCESSOR std::wstring& File() const {
				return m_file;
			}
			USER_INTERACTION
			const ACCESSOR std::wstring& Function() const {
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
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	ER_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_EXCEPTION
