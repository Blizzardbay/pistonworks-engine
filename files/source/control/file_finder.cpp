#include "control\file_finder.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// File_Finder  
		// Static Declarations
		// Class Members 
			std::filesystem::path File_Finder::Find_File(const std::wstring& p_directory, std::wstring p_file_name, const std::wstring& p_extension) {
				size_t v_slash = p_file_name.find_last_of(L"/");
				if (p_file_name.find_last_of(L"/") != std::wstring::npos) {
					p_file_name.erase(0, OFF_UINT64(v_slash));
				}
				p_file_name.append(p_extension);

				try {
					TRY_LINE for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
						// If the dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::wstring v_temp_file = v_file_finder.path().generic_wstring();
								v_temp_file.erase(0, v_temp_file.find_last_of(L"/") + 1);
								// If the file name is correct then we found the correct path
								if (v_temp_file == p_file_name) {
									// Save the correct path
									return v_file_finder.path();
								}
							}
						}
					}
				}
				// Catch all filesystem errors
				catch (const std::filesystem::filesystem_error& p_error) {
					SET_ERROR_STATE(PW_FILESYSTEM_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", L"std::filesystem error code: " + std::to_wstring(p_error.code().value()) + L" : Message: " + TO_WSTRING(p_error.code().message()), ERROR_LINE, __FILEW__, L"Find_File"));
					return std::filesystem::path();
				}
				SET_ERROR_STATE(PW_FILE_NOT_FOUND);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", p_file_name.insert(0, L"Could not find file "), ERROR_LINE, __FILEW__, L"Find_File"));
				return std::filesystem::path();
				
			}
			std::filesystem::path File_Finder::Find_File(const std::string& p_directory, std::string p_file_name, const std::string& p_extension) {
				size_t v_slash = p_file_name.find_last_of("/");
				if (p_file_name.find_last_of("/") != std::string::npos) {
					p_file_name.erase(0, OFF_UINT64(v_slash));
				}
				p_file_name.append(p_extension);

				try {
					TRY_LINE for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
						// If the dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::string v_temp_file = v_file_finder.path().generic_string();
								v_temp_file.erase(0, v_temp_file.find_last_of("/") + 1);
								// If the file name is correct then we found the correct path
								if (v_temp_file == p_file_name) {
									// Save the correct path
									return v_file_finder.path();
								}
							}
						}
					}
				}
				// Catch all filesystem errors
				catch (const std::filesystem::filesystem_error& p_error) {
					SET_ERROR_STATE(PW_FILESYSTEM_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", L"std::filesystem error code: " + std::to_wstring(p_error.code().value()) + L" : Message: " + TO_WSTRING(p_error.code().message()), ERROR_LINE, __FILEW__, L"Find_File"));
					return std::filesystem::path();
				}
				uint64_t v_temp_line_number{ pw::er::Error_State::Error_Line() };

				TRY_LINE std::wstring v_werror_msg{ TO_WSTRING(p_file_name.insert(0, "Could not find file ")) };

				if (v_werror_msg == std::wstring()) {
					pw::er::Error_State::Handle_Error();

					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::co::File_Finder", L"\"TO_WSTRING\" had an error.", ERROR_LINE, __FILEW__, L"Find_File");
					return std::filesystem::path();
				}
				SET_ERROR_STATE(PW_FILE_NOT_FOUND);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", v_werror_msg, v_temp_line_number, __FILEW__, L"Find_File"));
				return std::filesystem::path();
			}
			std::filesystem::path File_Finder::Find_File_From_Extension(const std::wstring& p_directory, std::wstring p_extension) {
				size_t v_period = p_extension.find_last_of(L".");
				if (p_extension.find_last_of(L".") != std::wstring::npos) {
					p_extension.erase(0, OFF_UINT64(v_period));
				}
				try {
					TRY_LINE for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
						// If the dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::wstring v_temp_file = v_file_finder.path().generic_wstring();
								v_temp_file.erase(0, v_temp_file.find_last_of(L".") + 1);
								// If the file name is correct then we found the correct path
								if (v_temp_file == p_extension) {
									// Save the correct path
									return v_file_finder.path();
								}
							}
						}
					}
				}
				// Catch all filesystem errors
				catch (const std::filesystem::filesystem_error& p_error) {
					SET_ERROR_STATE(PW_FILESYSTEM_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", L"std::filesystem error code: " + std::to_wstring(p_error.code().value()) + L" : Message: " + TO_WSTRING(p_error.code().message()), ERROR_LINE, __FILEW__, L"Find_File_From_Extension"));
					return std::filesystem::path();
				}
				SET_ERROR_STATE(PW_FILE_NOT_FOUND);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", p_extension.insert(0, L"Could not find file "), ERROR_LINE, __FILEW__, L"Find_File_From_Extension"));
				return std::filesystem::path();
			}
			std::filesystem::path File_Finder::Find_File_From_Extension(const std::string& p_directory, std::string p_extension) {
				size_t v_period = p_extension.find_last_of(".");
				if (p_extension.find_last_of(".") != std::string::npos) {
					p_extension.erase(0, OFF_UINT64(v_period));
				}
				try {
					TRY_LINE for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
						// If the dir exists then search for the file
						if (v_file_finder.exists() == true) {
							// If the path is empty 
							if (v_file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								std::string v_temp_file = v_file_finder.path().generic_string();
								v_temp_file.erase(0, v_temp_file.find_last_of(".") + 1);
								// If the file name is correct then we found the correct path
								if (v_temp_file == p_extension) {
									// Save the correct path
									return v_file_finder.path();
								}
							}
						}
					}
				}
				// Catch all filesystem errors
				catch (const std::filesystem::filesystem_error& p_error) {
					SET_ERROR_STATE(PW_FILESYSTEM_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", L"std::filesystem error code: " + std::to_wstring(p_error.code().value()) + L" : Message: " + TO_WSTRING(p_error.code().message()), ERROR_LINE, __FILEW__, L"Find_File_From_Extension"));
					return std::filesystem::path();
				}
				uint64_t v_temp_line_number{ pw::er::Error_State::Error_Line() };
				TRY_LINE std::wstring v_werror_msg{ TO_WSTRING(p_extension.insert(0, "Could not find extension ")) };

				if (v_werror_msg == std::wstring()) {
					pw::er::Error_State::Handle_Error();

					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::co::File_Finder", L"\"TO_WSTRING\" had an error.", ERROR_LINE, __FILEW__, L"Find_File_From_Extension");
					return std::filesystem::path();
				}
				SET_ERROR_STATE(PW_FILE_NOT_FOUND);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::File_Finder", v_werror_msg, v_temp_line_number, __FILEW__, L"Find_File_From_Extension"));
				return std::filesystem::path();
			}
		CO_NAMESPACE_END
PW_NAMESPACE_END