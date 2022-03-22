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
#ifndef H_ENGINE_ERROR_LOG
#define H_ENGINE_ERROR_LOG
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
#include <filesystem>
#include <fstream>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
#include "engine_common\engine_macro.h"
#include "engine_common\engine_exception.h"
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
		class Error_Log {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			static bool Dump_Log(const std::filesystem::path& p_pistonworks_path, const std::wstring& p_msg) {
				#ifdef PW_DEBUG_MODE
					std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/engine_files/engine_resource/engine_log/" };

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
						return false;
					}
				#else
					return true;
				#endif // PW_DEBUG_MODE
			}
			static bool Dump_Log(const std::filesystem::path& p_pistonworks_path, const er::Warning_Error& p_error) {
				#ifdef PW_DEBUG_MODE
					std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/engine_files/engine_resource/engine_log/" };

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

							v_dump.close();

							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				#else
					return true;
				#endif // PW_DEBUG_MODE
			}
			static bool Dump_Log(const std::filesystem::path& p_pistonworks_path, const er::Severe_Error& p_error) {
				#ifdef PW_DEBUG_MODE
					std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/engine_files/engine_resource/engine_log/" };

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

							v_dump.close();

							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				#else
					return true;
				#endif // PW_DEBUG_MODE
			}
			static void Close_Log(const std::filesystem::path& p_pistonworks_path) {
				#ifdef PW_DEBUG_MODE
					std::filesystem::path v_error_log_path{ p_pistonworks_path.generic_wstring() + L"/engine_files/engine_resource/engine_log/" };

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
					m_console_log_name.~basic_string();
					m_error_log_name.~basic_string();
				#endif // PW_DEBUG_MODE
			}
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
			static std::string m_console_log_name;
			static std::string m_error_log_name;
		};
	//////////////////////////////////
	ER_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_ERROR_LOG