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
#ifndef H_ERROR_LOG
#define H_ERROR_LOG
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <filesystem>
#include <fstream>
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
	ER_NAMESPACE_SRT
		class Warning_Error {
		// Friends
		// Default Class Structures
		public:
			/* Error List: NONE */
			Warning_Error() noexcept :
				m_from{}, m_msg{}, m_line{}, m_file{}, m_function{} {
			}
			/* Error List: NONE */
			Warning_Error(const std::wstring& p_from, const std::wstring& p_msg, const uint64_t& p_line, const std::wstring& p_file,
				const std::wstring& p_function) noexcept :
				m_from{ p_from }, m_msg{ p_msg }, m_line{ p_line }, m_file{ p_file }, m_function{ p_function } {
			}
		private:
			// Public Functions/Macros
		public:
			/* Error List: NONE */
			const std::wstring& From() const noexcept {
				return m_from;
			}
			/* Error List: NONE */
			const std::wstring& Msg() const noexcept {
				return m_msg;
			}
			/* Error List: NONE */
			const uint64_t& Line() const noexcept {
				return m_line;
			}
			/* Error List: NONE */
			const std::wstring& File() const noexcept {
				return m_file;
			}
			/* Error List: NONE */
			const std::wstring& Function() const noexcept {
				return m_function;
			}
			// Public Variables
		public:
			// Private Functions/Macros
		private:
			// Private Variables
		private:
			std::wstring m_from;
			std::wstring m_msg;
			uint64_t m_line;
			std::wstring m_file;
			std::wstring m_function;
		};
		class Severe_Error {
		// Friends
		// Default Class Structures
		public:
			/* Error List: NONE */
			Severe_Error() noexcept :
				m_from{}, m_msg{}, m_line{}, m_file{}, m_function{} {
			}
			/* Error List: NONE */
			Severe_Error(const std::wstring& p_from, const std::wstring& p_msg, const uint64_t& p_line, const std::wstring& p_file,
				const std::wstring& p_function) noexcept :
				m_from{ p_from }, m_msg{ p_msg }, m_line{ p_line }, m_file{ p_file }, m_function{ p_function } {
			}
		private:
		// Public Functions/Macros
		public:
			/* Error List: NONE */
			const std::wstring& From() const noexcept {
				return m_from;
			}
			/* Error List: NONE */
			const std::wstring& Msg() const noexcept {
				return m_msg;
			}
			/* Error List: NONE */
			const uint64_t& Line() const noexcept {
				return m_line;
			}
			/* Error List: NONE */
			const std::wstring& File() const noexcept {
				return m_file;
			}
			/* Error List: NONE */
			const std::wstring& Function() const noexcept {
				return m_function;
			}
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			std::wstring m_from;
			std::wstring m_msg;
			uint64_t m_line;
			std::wstring m_file;
			std::wstring m_function;
		};
		class Error_Log {
		// Friends
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			static void Set_Error_State_Value_Callback(const std::function<std::wstring()>& p_callback) {
				m_error_state_value_callback = p_callback;
			}
			/* Error List: PW_RETURN_STATE_TF */
			static bool Dump_Log(const std::filesystem::path& p_pistonworks_path, const std::wstring& p_msg) noexcept {
				std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/files/resource/log/" };

				if (std::filesystem::exists(v_error_log_path) == true) {
					std::string v_file = m_console_log_name;
					v_file.insert(0, v_error_log_path.generic_string());

					std::wofstream v_dump{ v_file, std::ofstream::app };

					if (v_dump.is_open() == true) {

						v_dump << p_msg << std::endl;

						v_dump.close();

						return true;
					}
					else {
						return false;
					}
				}
				else {
					v_error_log_path = { p_pistonworks_path.generic_wstring() + L"/" };

					std::string v_file = m_console_log_name;
					v_file.insert(0, v_error_log_path.generic_string());

					std::wofstream v_dump{ v_file, std::ofstream::app };

					if (v_dump.is_open() == true) {

						v_dump << p_msg << std::endl;

						v_dump.close();

						return true;
					}
					else {
						return false;
					}
				}
			}
			/* Error List: PW_RETURN_STATE_TF */
			static bool Dump_Log(const std::filesystem::path& p_pistonworks_path, const er::Warning_Error& p_error) noexcept {
				std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/files/resource/log/" };

				if (std::filesystem::exists(v_error_log_path) == true) {
					std::string v_file = m_error_log_name;
					v_file.insert(0, v_error_log_path.generic_string());

					std::wofstream v_dump{ v_file, std::ofstream::app };

					if (v_dump.is_open() == true) {

						v_dump << L"Sender: " << p_error.From() << std::endl;
						v_dump << L"Msg: " << p_error.Msg() << std::endl;
						v_dump << L"Line: " << p_error.Line() << std::endl;
						v_dump << L"File: " << p_error.File() << std::endl;
						v_dump << L"Function: " << p_error.Function() << std::endl;
						v_dump << L"Error Value: " << m_error_state_value_callback() << std::endl;

						v_dump.close();

						return true;
					}
					else {
						return false;
					}
				}
				else {
					v_error_log_path = { p_pistonworks_path.generic_wstring() + L"/" };

					std::string v_file = m_error_log_name;
					v_file.insert(0, v_error_log_path.generic_string());

					std::wofstream v_dump{ v_file, std::ofstream::app };

					if (v_dump.is_open() == true) {

						v_dump << L"Sender: " << p_error.From() << std::endl;
						v_dump << L"Msg: " << p_error.Msg() << std::endl;
						v_dump << L"Line: " << p_error.Line() << std::endl;
						v_dump << L"File: " << p_error.File() << std::endl;
						v_dump << L"Function: " << p_error.Function() << std::endl;
						v_dump << L"Error Value: " << m_error_state_value_callback() << std::endl;

						v_dump.close();

						return true;
					}
					else {
						return false;
					}
				}
			}
			/* Error List: PW_RETURN_STATE_TF */
			static bool Dump_Log(const std::filesystem::path& p_pistonworks_path, const er::Severe_Error& p_error) noexcept {
				std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/files/resource/log/" };

				if (std::filesystem::exists(v_error_log_path) == true) {
					std::string v_file = m_error_log_name;
					v_file.insert(0, v_error_log_path.generic_string());

					std::wofstream v_dump{ v_file, std::ofstream::app };

					if (v_dump.is_open() == true) {

						v_dump << L"Sender: " << p_error.From() << std::endl;
						v_dump << L"Msg: " << p_error.Msg() << std::endl;
						v_dump << L"Line: " << p_error.Line() << std::endl;
						v_dump << L"File: " << p_error.File() << std::endl;
						v_dump << L"Function: " << p_error.Function() << std::endl;
						v_dump << L"Error Value: " << m_error_state_value_callback() << std::endl;

						v_dump.close();

						return true;
					}
					else {
						return false;
					}
				}
				else {
					v_error_log_path = { p_pistonworks_path.generic_wstring() + L"/" };

					std::string v_file = m_error_log_name;
					v_file.insert(0, v_error_log_path.generic_string());

					std::wofstream v_dump{ v_file, std::ofstream::app };

					if (v_dump.is_open() == true) {

						v_dump << L"Sender: " << p_error.From() << std::endl;
						v_dump << L"Msg: " << p_error.Msg() << std::endl;
						v_dump << L"Line: " << p_error.Line() << std::endl;
						v_dump << L"File: " << p_error.File() << std::endl;
						v_dump << L"Function: " << p_error.Function() << std::endl;
						v_dump << L"Error Value: " << m_error_state_value_callback() << std::endl;

						v_dump.close();

						return true;
					}
					else {
						return false;
					}
				}
			}
			/* Error List: NONE */
			static void Close_Log(const std::filesystem::path& p_pistonworks_path) noexcept {
				std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/files/resource/log/" };

				if (std::filesystem::exists(v_error_log_path) == true) {
					std::filesystem::path v_error_log{};
					std::filesystem::path v_console_log{};

					bool v_found_file = false;
					int16_t v_error_handle = 0;

					for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(v_error_log_path)) {
						// If the file is found break
						if (v_found_file == true) {
							break;
						}
						// If the file dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::string temp_file = v_file_finder.path().generic_string();
								temp_file.erase(0, temp_file.find_last_of("/") + 1);
								// If the file name is correct then we found the correct path
								if ((temp_file == m_error_log_name) == true) {
									v_found_file = true;
									// Save the correct path
									v_error_log = v_file_finder.path();
								}
							}
						}
					}
					if (v_found_file == true) {
						std::string v_closed{ "Closed_" };

						std::string v_file_error_new{ v_error_log_path.generic_string() };

						v_file_error_new.append(v_closed);

						v_file_error_new.append(m_error_log_name);

						v_error_handle = TO_INT16(std::rename(v_error_log.generic_string().c_str(), v_file_error_new.c_str()));
					}
					v_found_file = false;

					for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(v_error_log_path)) {
						// If the file is found break
						if (v_found_file == true) {
							break;
						}
						// If the file dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::string temp_file = v_file_finder.path().generic_string();
								temp_file.erase(0, temp_file.find_last_of("/") + 1);
								// If the file name is correct then we found the correct path
								if ((temp_file == m_console_log_name) == true) {
									v_found_file = true;
									// Save the correct path
									v_console_log = v_file_finder.path();
								}
							}
						}
					}
					if (v_found_file == true) {
						std::string v_closed{ "Closed_" };

						std::string v_file_console_new{ v_error_log_path.generic_string() };

						v_file_console_new.append(v_closed);

						v_file_console_new.append(m_console_log_name);

						v_error_handle = TO_INT16(std::rename(v_console_log.generic_string().c_str(), v_file_console_new.c_str()));
					}
				}
				else {
					v_error_log_path = { p_pistonworks_path.generic_wstring() + L"/" };

					std::filesystem::path v_error_log{};
					std::filesystem::path v_console_log{};

					bool v_found_file = false;
					int16_t v_error_handle = 0;

					for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(v_error_log_path)) {
						// If the file is found break
						if (v_found_file == true) {
							break;
						}
						// If the file dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::string temp_file = v_file_finder.path().generic_string();
								temp_file.erase(0, temp_file.find_last_of("/") + 1);
								// If the file name is correct then we found the correct path
								if ((temp_file == m_error_log_name) == true) {
									v_found_file = true;
									// Save the correct path
									v_error_log = v_file_finder.path();
								}
							}
						}
					}
					if (v_found_file == true) {
						std::string v_closed{ "Closed_" };

						std::string v_file_error_new{ v_error_log_path.generic_string() };

						v_file_error_new.append(v_closed);

						v_file_error_new.append(m_error_log_name);

						v_error_handle = TO_INT16(std::rename(v_error_log.generic_string().c_str(), v_file_error_new.c_str()));
					}
					v_found_file = false;

					for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(v_error_log_path)) {
						// If the file is found break
						if (v_found_file == true) {
							break;
						}
						// If the file dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::string temp_file = v_file_finder.path().generic_string();
								temp_file.erase(0, temp_file.find_last_of("/") + 1);
								// If the file name is correct then we found the correct path
								if ((temp_file == m_console_log_name) == true) {
									v_found_file = true;
									// Save the correct path
									v_console_log = v_file_finder.path();
								}
							}
						}
					}
					if (v_found_file == true) {
						std::string v_closed{ "Closed_" };

						std::string v_file_console_new{ v_error_log_path.generic_string() };

						v_file_console_new.append(v_closed);

						v_file_console_new.append(m_console_log_name);

						v_error_handle = TO_INT16(std::rename(v_console_log.generic_string().c_str(), v_file_console_new.c_str()));
					}
				}
				m_console_log_name.~basic_string();
				m_error_log_name.~basic_string();
			}
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static std::string m_console_log_name;
			static std::string m_error_log_name;
			static std::function<std::wstring()> m_error_state_value_callback;
		};
	ER_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_ERROR_LOG