#include "engine_control\engine_file_finder.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// File_Finder  
		// Static Declarations
		// Class Members 
			std::filesystem::path File_Finder::Find_File(const std::wstring& p_directory, std::wstring p_file_name, const std::wstring& p_extension) {
				size_t v_slash = p_file_name.find_last_of(L"/");
				if (p_file_name.find_last_of(L"/") != std::wstring::npos) {
					p_file_name.erase(0, OFFU64(v_slash));
				}
				p_file_name.append(p_extension);

				bool v_found_file = false;
				for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
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
				if (TRY_LINE v_found_file == false) {
					throw er::Warning_Error(L"File Loader", p_file_name.insert(0, L"Could not find file "), EXCEPTION_LINE, __FILEW__, L"recursive_directory_iterator");
				}
				return std::filesystem::path();
			}
			std::filesystem::path File_Finder::Find_File(const std::string& p_directory, std::string p_file_name, const std::string& p_extension) {
				size_t v_slash = p_file_name.find_last_of("/");
				if (p_file_name.find_last_of("/") != std::string::npos) {
					p_file_name.erase(0, OFFU64(v_slash));
				}
				p_file_name.append(p_extension);

				bool v_found_file = false;
				for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
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
				if (TRY_LINE v_found_file == false) {
					throw er::Warning_Error(L"File Loader", TO_WSTRING(p_file_name.insert(0, "Could not find file ")), EXCEPTION_LINE, __FILEW__, L"recursive_directory_iterator");
				}
				return std::filesystem::path();
			}
			std::filesystem::path File_Finder::Find_File_From_Extension(const std::wstring& p_directory, std::wstring p_extension) {
				size_t v_period = p_extension.find_last_of(L".");
				if (p_extension.find_last_of(L".") != std::wstring::npos) {
					p_extension.erase(0, OFFU64(v_period));
				}

				bool v_found_file = false;
				for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
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
				if (TRY_LINE v_found_file == false) {
					throw er::Warning_Error(L"File Loader", std::move(p_extension.insert(0, L"Could not find file ")), EXCEPTION_LINE, __FILEW__, L"recursive_directory_iterator");
				}
				return std::filesystem::path();
			}
			std::filesystem::path File_Finder::Find_File_From_Extension(const std::string& p_directory, std::string p_extension) {
				size_t v_period = p_extension.find_last_of(".");
				if (p_extension.find_last_of(".") != std::string::npos) {
					p_extension.erase(0, OFFU64(v_period));
				}

				bool v_found_file = false;
				for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_directory)) {
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
				if (TRY_LINE v_found_file == false) {
					throw er::Warning_Error(L"File Loader", std::move(TO_WSTRING(p_extension.insert(0, "Could not find file "))), EXCEPTION_LINE, __FILEW__, L"recursive_directory_iterator");
				}
				return std::filesystem::path();
			}
			// End of Class Members
		//////////////////////////////////
		CO_NAMESPACE_END
		//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////