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
#ifndef H_ERROR_STATE
#define H_ERROR_STATE
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <string>
#include <any>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\macro.h"
#include "common\error_values.h"
#include "common\error_log.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ER_NAMESPACE_SRT
		class Error_State {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			/* Error List: NONE */
			static const uint32_t& Get() noexcept {
				return m_error_state;
			}
			/* Error List: NONE */
			static const bool& Is_Warning_Error() noexcept {
				return m_warning_error;
			}
			/* Error List: NONE */
			static const bool& Is_Severe_Error() noexcept {
				return m_severe_error;
			}
			/* Error List: NONE */
			static const pw::er::Warning_Error& Warning_Error() noexcept {
				return m_werror_info;
			}
			/* Error List: NONE */
			static const pw::er::Severe_Error& Severe_Error() noexcept {
				return m_serror_info;
			}
			/* Error List: NONE */
			static const uint64_t& Error_Line() noexcept {
				return m_error_line;
			}
			/* Error List: NONE */
			static void Set(const uint32_t& p_state) noexcept {
				m_error_state = p_state;
			}
			/* Error List: NONE */
			static void Set_Warning_Error(const pw::er::Warning_Error& p_error) noexcept {
				m_werror_info = p_error;
			}
			/* Error List: NONE */
			static void Set_Severe_Error(const pw::er::Severe_Error& p_error) noexcept {
				m_serror_info = p_error;
			}
			/* Error List: NONE */
			static void Set_Error_Line(const uint32_t& p_new_line) noexcept {
				m_error_line = p_new_line;
			}
			// Sets the execution line of the code in question
			#define TRY_LINE pw::er::Error_State::Set_Error_Line(TO_UINT32(__LINE__));
			// Get the line of the code that executed
			#define ERROR_LINE pw::er::Error_State::Error_Line()
			#define SET_ERROR_STATE(x) pw::er::Error_State::Set(TO_UINT32(x))
			#define SET_ERROR_TYPE(x) pw::er::Error_State::Set_Error_Type(x, TO_UINT64(__LINE__), __FILEW__)
			#define SET_ERROR_TYPE_W(p_msg)																			\
				std::wstring v_class{ __FUNCTIONW__ };																\
				size_t v_last_colon{ 0 };																			\
				v_last_colon = v_class.find_last_of(L':');															\
				if (v_last_colon != std::wstring::npos) {															\
					std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };					\
					v_class = v_class.substr(0, v_last_colon - 1);													\
					pw::er::Warning_Error v_error{v_class, std::wstring(p_msg), ERROR_LINE, __FILEW__, v_function}; \
					pw::er::Error_State::Set_Error_Type_Warning(v_error);											\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define SET_ERROR_TYPE_S(p_msg)																			\
				std::wstring v_class{ __FUNCTIONW__ };																\
				size_t v_last_colon{ 0 };																			\
				v_last_colon = v_class.find_last_of(L':');															\
				if (v_last_colon != std::wstring::npos) {															\
					std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };					\
					v_class = v_class.substr(0, v_last_colon - 1);													\
					pw::er::Severe_Error v_error{v_class, std::wstring(p_msg), ERROR_LINE, __FILEW__, v_function};	\
					pw::er::Error_State::Set_Error_Type_Severe(v_error)												\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			#define MAINTAIN_ERROR_TYPE(p_from, p_msg, p_line, p_file, p_function) {		\
				if (pw::er::Error_State::Is_Warning_Error() == true) {						\
					pw::er::Error_State::Set_Error_Type(									\
						pw::er::Warning_Error(p_from, p_msg, p_line, p_file, p_function)	\
						, TO_UINT64(__LINE__), __FILEW__);									\
				}																			\
				else {																		\
					pw::er::Error_State::Set_Error_Type(									\
						pw::er::Severe_Error(p_from, p_msg, p_line, p_file, p_function)		\
						, TO_UINT64(__LINE__), __FILEW__);									\
				}																			\
			}
			/* Error List: NONE */
			static void Set_Error_Type(const std::any& p_error, const uint64_t& p_line, const std::wstring& p_file) {
				if (p_error.type() == typeid(pw::er::Warning_Error)) {
					pw::er::Error_State::Set_Warning_Error(std::any_cast<pw::er::Warning_Error>(p_error));
					m_warning_error = true;
					m_severe_error = false;
					return;
				}
				if (p_error.type() == typeid(pw::er::Severe_Error)) {
					pw::er::Error_State::Set_Severe_Error(std::any_cast<pw::er::Severe_Error>(p_error));
					m_severe_error = true;
					m_warning_error = false;
					return;
				}
				SET_ERROR_STATE(PW_UNKNOWN_ERROR_TYPE);

				Set_Error_Type(pw::er::Severe_Error(
					L"Error_State", L"Unknown Error Passed To Function", p_line, p_file, L"Set_Error_Type"
				), p_line, p_file);
			}
			/* Error List: NONE */
			static void Set_Error_Type_Warning(const pw::er::Warning_Error& p_error) {
				pw::er::Error_State::Set_Warning_Error(p_error);
				m_warning_error = true;
				m_severe_error = false;
			}
			/* Error List: NONE */
			static void Set_Error_Type_Severe(const pw::er::Severe_Error& p_error) {
				pw::er::Error_State::Set_Severe_Error(p_error);
				m_severe_error = true;
				m_warning_error = false;
			}
			/* Error List: NONE */
			static void Handle_Error() {
				if (m_error_state > PW_NO_ERROR) {
					if (m_warning_error == true) {
						m_warning_handler(m_werror_info);
					}
					else {
						m_severe_handler(m_serror_info);
					}
				}
				// Does not clear the error type of the last error. That gets cleared by Set_Error_Type.
				Clear_Error();
			}
			/* Error List: NONE */
			static void Log_Error(const std::filesystem::path& p_pistonworks_path) {
				if (m_error_state > PW_NO_ERROR) {
					if (m_warning_error == true) {
						pw::er::Error_Log::Dump_Log(p_pistonworks_path, m_werror_info);
					}
					else {
						pw::er::Error_Log::Dump_Log(p_pistonworks_path, m_serror_info);
					}
				}
				// Does not clear the error type of the last error. That gets cleared by Set_Error_Type.
				Clear_Error();
			}
			/* Error List: NONE */
			static void Clear_Error() {
				m_error_state = PW_NO_ERROR;
				m_werror_info = {};
				m_serror_info = {};
			}
			/* Error List: NONE */
			static std::wstring Error_Value_String() {
				switch (m_error_state) {
					case PW_NO_ERROR: {
						return L"PW_NO_ERROR";
					}
					case PW_INVAILD_PARAMETER_W: {
						return L"PW_INVAILD_PARAMETER_W";
					}
					case PW_INVAILD_PARAMETER_S: {
						return L"PW_INVAILD_PARAMETER_S";
					}
					case PW_UNKNOWN_STRING_TYPE: {
						return L"PW_UNKNOWN_STRING_TYPE";
					}
					case PW_UNKNOWN_ERROR_TYPE: {
						return L"PW_UNKNOWN_ERROR_TYPE";
					}
					case PW_NULL_PARAMETER_W: {
						return L"PW_NULL_PARAMETER_W";
					}
					case PW_NULL_PARAMETER_S: {
						return L"PW_NULL_PARAMETER_S";
					}
					case PW_BUFFER_SIZE_MISMATCH: {
						return L"PW_BUFFER_SIZE_MISMATCH";
					}
					case PW_CRT_FUNCTION_FAILURE: {
						return L"PW_CRT_FUNCTION_FAILURE";
					}
					case PW_EMPTY_PARAMETER_W: {
						return L"PW_EMPTY_PARAMETER_W";
					}
					case PW_EMPTY_PARAMETER_S: {
						return L"PW_EMPTY_PARAMETER_S";
					}
					case PW_ALLOCATION_FAILURE: {
						return L"PW_ALLOCATION_FAILURE";
					}
					case PW_MEMORY_FAILURE: {
						return L"PW_MEMORY_FAILURE";
					}
					case PW_ZERO_ALLOCATION: {
						return L"PW_ZERO_ALLOCATION";
					}
					case PW_FUNCTION_ERROR: {
						return L"PW_FUNCTION_ERROR";
					}
					case PW_DIRECTORY_NOT_FOUND: {
						return L"PW_DIRECTORY_NOT_FOUND";
					}
					case PW_GAME_PATH_NOT_FOUND: {
						return L"PW_GAME_PATH_NOT_FOUND";
					}
					case PW_FILE_NOT_FOUND: {
						return L"PW_FILE_NOT_FOUND";
					}
					case PW_WIN_FUNCTION_ERROR: {
						return L"PW_WIN_FUNCTION_ERROR";
					}
					case PW_ANIMATION_ID_SIZE_MISMATCH: {
						return L"PW_ANIMATION_ID_SIZE_MISMATCH";
					}
					case PW_GLFW_ERROR: {
						return L"PW_GLFW_ERROR";
					}
					case PW_GL_ERROR: {
						return L"PW_GLFW_ERROR";
					}
					case PW_FI_ERROR: {
						return L"PW_GLFW_ERROR";
					}
					case PW_FT_ERROR: {
						return L"PW_GLFW_ERROR";
					}
					case PW_AL_ERROR: {
						return L"PW_GLFW_ERROR";
					}
					default: {
						return L"Unknown Error: Invalid error state.";
					}
				}
			}
			#define PW_CALL(p_funct, p_return)															\
				TRY_LINE p_funct;																		\
				if (pw::er::Error_State::Get() > 0) {													\
					pw::er::Error_State::Handle_Error();												\
					std::wstring v_funct{ L"\"" };														\
					std::wstring v_class{ __FUNCTIONW__ };												\
					v_funct.append(EXPRESSION_WSTRING(p_funct));										\
					v_funct.append(L"\" had an error.");												\
					size_t v_last_colon{ 0 };															\
					v_last_colon = v_class.find_last_of(L':');											\
					if (v_last_colon != std::wstring::npos) {											\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };	\
						v_class = v_class.substr(0, v_last_colon - 1);									\
						SET_ERROR_STATE(PW_FUNCTION_ERROR);												\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);		\
					}																					\
					if constexpr (TO_BOOL(p_return) == true) return;									\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_PTR_CALL(p_funct, p_return)														\
				TRY_LINE p_funct;																		\
				if (pw::er::Error_State::Get() > 0) {													\
					pw::er::Error_State::Handle_Error();												\
					std::wstring v_funct{ L"\"" };														\
					std::wstring v_class{ __FUNCTIONW__ };												\
					v_funct.append(EXPRESSION_WSTRING(p_funct));										\
					v_funct.append(L"\" had an error.");												\
					size_t v_last_colon{ 0 };															\
					v_last_colon = v_class.find_last_of(L':');											\
					if (v_last_colon != std::wstring::npos) {											\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };	\
						v_class = v_class.substr(0, v_last_colon - 1);									\
						SET_ERROR_STATE(PW_FUNCTION_ERROR);												\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);		\
					}																					\
					if constexpr(TO_BOOL(p_return) == true) return nullptr;								\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_CUSTOM_CALL(p_funct, p_return, p_type)											\
				TRY_LINE p_funct;																		\
				if (pw::er::Error_State::Get() > 0) {													\
					pw::er::Error_State::Handle_Error();												\
					std::wstring v_funct{ L"\"" };														\
					std::wstring v_class{ __FUNCTIONW__ };												\
					v_funct.append(EXPRESSION_WSTRING(p_funct));										\
					v_funct.append(L"\" had an error.");												\
					size_t v_last_colon{ 0 };															\
					v_last_colon = v_class.find_last_of(L':');											\
					if (v_last_colon != std::wstring::npos) {											\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };	\
						v_class = v_class.substr(0, v_last_colon - 1);									\
						SET_ERROR_STATE(PW_FUNCTION_ERROR);												\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);		\
					}																					\
					if constexpr(TO_BOOL(p_return) == true) return p_type();							\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////
			#define PW_AFTER_CALL(p_funct_name, p_return)												\
				if (pw::er::Error_State::Get() > 0) {													\
					pw::er::Error_State::Handle_Error();												\
					std::wstring v_funct{ L"\"" };														\
					std::wstring v_class{ __FUNCTIONW__ };												\
					v_funct.append(EXPRESSION_WSTRING(p_funct_name));									\
					v_funct.append(L"\" had an error.");												\
					size_t v_last_colon{ 0 };															\
					v_last_colon = v_class.find_last_of(L':');											\
					if (v_last_colon != std::wstring::npos) {											\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };	\
						v_class = v_class.substr(0, v_last_colon - 1);									\
						SET_ERROR_STATE(PW_FUNCTION_ERROR);												\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);		\
					}																					\
					if constexpr(TO_BOOL(p_return) == true) return;										\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////	
			#define PW_PTR_AFTER_CALL(p_funct_name, p_return)											\
				if (pw::er::Error_State::Get() > 0) {													\
					pw::er::Error_State::Handle_Error();												\
					std::wstring v_funct{ L"\"" };														\
					std::wstring v_class{ __FUNCTIONW__ };												\
					v_funct.append(EXPRESSION_WSTRING(p_funct_name));									\
					v_funct.append(L"\" had an error.");												\
					size_t v_last_colon{ 0 };															\
					v_last_colon = v_class.find_last_of(L':');											\
					if (v_last_colon != std::wstring::npos) {											\
						std::wstring v_function{ v_class.substr(v_last_colon + 1, v_class.size()) };	\
						v_class = v_class.substr(0, v_last_colon - 1);									\
						SET_ERROR_STATE(PW_FUNCTION_ERROR);												\
						MAINTAIN_ERROR_TYPE(v_class, v_funct, ERROR_LINE, __FILEW__, v_function);		\
					}																					\
					if constexpr(TO_BOOL(p_return) == true) return nullptr;								\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////		
			#define PW_SET_RET(p_no_error, p_return)													\
				if (pw::er::Error_State::Get() > 0) {													\
					p_no_error = false;																	\
					if constexpr(TO_BOOL(p_return) == true) return;										\
				}
			/////////////////////////////////////////////////////////////////////////////////////////////	
			#define PW_FINAL_CALL(p_funct, p_pistonworks_path)											\
				TRY_LINE p_funct;																		\
				if (pw::er::Error_State::Get() > 0) {													\
					pw::er::Error_State::Log_Error(p_pistonworks_path);									\
				}					
		// Public Variables
		public:
		// Protected Functions/Macros
		protected:
			/* Error List: NONE */
			static void Initialize(
					const std::function<void(const pw::er::Warning_Error&)>& p_warning_handler,
					std::function<void(const pw::er::Severe_Error&)> p_severe_handler) noexcept {
				m_warning_handler = p_warning_handler;
				m_severe_handler = p_severe_handler;

				pw::er::Error_Log::Set_Error_State_Value_Callback(Error_Value_String);
			}
		// Protected Variables
		protected:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static uint64_t m_error_line;
			static uint32_t m_error_state;
			static bool m_warning_error;
			static bool m_severe_error;
			static pw::er::Warning_Error m_werror_info;
			static pw::er::Severe_Error m_serror_info;
			static std::function<void(const pw::er::Warning_Error&)> m_warning_handler;
			static std::function<void(const pw::er::Severe_Error&)> m_severe_handler;
		};
	ER_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_ERROR_STATE
