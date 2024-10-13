#include "utility\string.h"

PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		// String
		// Static Declarations
		// Class Members
			wchar_t* String::Evaluate_WStr(const std::any& p_str) noexcept {
				if (p_str.type() == typeid(char)) {
					char v_temp[2];
					v_temp[0] = std::any_cast<char>(p_str);
					v_temp[1] = '\0';

					PW_PTR_CALL(wchar_t* v_return = pw::util::String::To_WChar(v_temp), true);

					return v_return;
				}
				if (p_str.type() == typeid(const char*)) {
					PW_PTR_CALL(wchar_t* v_return = pw::util::String::To_WChar(std::any_cast<const char*>(p_str)), true);

					return v_return;
				}
				if (p_str.type() == typeid(std::string)) {
					PW_PTR_CALL(wchar_t* v_return = pw::util::String::To_WChar(std::any_cast<std::string>(p_str)), true);

					return v_return;
				}
				if (p_str.type() == typeid(wchar_t)) {
					wchar_t v_temp[2];
					v_temp[0] = std::any_cast<wchar_t>(p_str);
					v_temp[1] = L'\0';

					PW_PTR_CALL(wchar_t* v_return = pw::util::String::To_WChar(v_temp), true);

					return v_return;
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					PW_PTR_CALL(wchar_t* v_return = pw::util::String::To_WChar(std::any_cast<const wchar_t*>(p_str)), true);

					return v_return;
				}
				if (p_str.type() == typeid(std::wstring)) {
					TRY_LINE wchar_t* v_return = pw::util::String::To_WChar(std::any_cast<std::wstring>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"wchar_t* To_WChar(const wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_WStr");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(wchar_t*)) {
					return std::any_cast<wchar_t*>(p_str);
				}

				SET_ERROR_STATE(PW_UNKNOWN_STRING_TYPE);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Unknown String Type", ERROR_LINE, __FILEW__, L"Evaluate_WStr"));

				return nullptr;
			}
			wchar_t* String::To_WChar(const char* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_WChar"));
					return nullptr;
				}
				else {
					// Get the msg size
					TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_WChar"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					wchar_t* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<wchar_t>(v_msg_size), false);
					if (v_msg == nullptr) {
						return nullptr;
					}

					size_t v_chars_converted = 0;
					// Convert the memory
					if (TRY_LINE mbstowcs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
						SET_ERROR_STATE(PW_BUFFER_SIZE_MISMATCH);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Destination buffer is too small", ERROR_LINE, __FILEW__, L"To_WChar"));

						(void)pw::co::Memory::Deallocate<wchar_t>(v_msg);
						return nullptr;
					}
					// If we converted all of the memory correctly then return the result
					if (v_chars_converted == v_msg_size) {
						return v_msg;
					}
					else {
						SET_ERROR_STATE(PW_CRT_FUNCTION_FAILURE);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"CRT Function Failed: mbstowcs_s", ERROR_LINE, __FILEW__, L"To_WChar"));

						(void)pw::co::Memory::Deallocate<wchar_t>(v_msg);
						return nullptr;
					}
				}
			}
			wchar_t* String::To_WChar(const std::string& p_msg) noexcept {
				// This function inherits the other To_WChar errors
				return To_WChar(p_msg.c_str());
			}
			wchar_t* String::To_WChar(const wchar_t* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_WChar"));
					return nullptr;
				}
				else {
					// Get the msg size
					TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_WChar"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					wchar_t* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<wchar_t>(v_msg_size), false)
						if (v_msg == nullptr) {
							return nullptr;
						}
					for (size_t i = 0; i < v_msg_size; i++) {
						v_msg[i] = p_msg[i];
					}
					return v_msg;
				}
			}
			wchar_t* String::To_WChar(const std::wstring& p_msg) noexcept {
				// This function inherits the other To_WChar errors
				return To_WChar(p_msg.c_str());
			}
			char* String::Evaluate_Str(const std::any& p_str) noexcept {
				if (p_str.type() == typeid(char)) {
					char v_temp[2];
					v_temp[0] = std::any_cast<char>(p_str);
					v_temp[1] = '\0';

					TRY_LINE char* v_return = pw::util::String::To_Char(v_temp);

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"char* To_Char(const char* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(const char*)) {

					TRY_LINE char* v_return = pw::util::String::To_Char(std::any_cast<const char*>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"char* To_Char(const char* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(std::string)) {
					TRY_LINE char* v_return = pw::util::String::To_Char(std::any_cast<std::string>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"char* To_Char(const char* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(wchar_t)) {
					wchar_t v_temp[2];
					v_temp[0] = std::any_cast<wchar_t>(p_str);
					v_temp[1] = L'\0';

					TRY_LINE char* v_return = pw::util::String::To_Char(v_temp);

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"char* To_Char(const 'wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(const wchar_t*)) {
					TRY_LINE char* v_return = pw::util::String::To_Char(std::any_cast<const wchar_t*>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"char* To_Char(const 'wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(std::wstring)) {
					TRY_LINE char* v_return = pw::util::String::To_Char(std::any_cast<std::wstring>(p_str));

					if (v_return == nullptr) {
						pw::er::Error_State::Handle_Error();

						SET_ERROR_STATE(PW_FUNCTION_ERROR);
						MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"char* To_Char(const 'wchar_t* p_msg)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_Str");
						return nullptr;
					}
					return v_return;
				}
				if (p_str.type() == typeid(char*)) {
					return std::any_cast<char*>(p_str);
				}

				SET_ERROR_STATE(PW_UNKNOWN_STRING_TYPE);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Unknown String Type", ERROR_LINE, __FILEW__, L"Evaluate_Str"));

				return nullptr;
			}
			char* String::To_Char(const wchar_t* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_Char"));
					return nullptr;
				}
				else {
					// Get the msg size 
					TRY_LINE size_t v_msg_size = std::wcslen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_Char"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					char* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<char>(v_msg_size), false);
					if (v_msg == nullptr) {
						return nullptr;
					}
					size_t v_chars_converted = 0;
					// Convert the memory
					if (TRY_LINE wcstombs_s(&v_chars_converted, v_msg, v_msg_size, p_msg, v_msg_size - 1) != 0) {
						SET_ERROR_STATE(PW_BUFFER_SIZE_MISMATCH);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Destination buffer is too small", ERROR_LINE, __FILEW__, L"To_Char"));

						(void)pw::co::Memory::Deallocate<char>(v_msg);
						return nullptr;
					}
					// If we converted all of the memory correctly then return the result
					if (v_chars_converted == v_msg_size) {
						return v_msg;
					}
					else {
						SET_ERROR_STATE(PW_CRT_FUNCTION_FAILURE);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"CRT Function Failed: wcstombs_s", ERROR_LINE, __FILEW__, L"To_WChar"));

						(void)pw::co::Memory::Deallocate<char>(v_msg);
						return nullptr;
					}
				}
			}
			char* String::To_Char(const std::wstring& p_msg) noexcept {
				// This function inherits the other To_Char errors
				return To_Char(p_msg.c_str());
			}
			char* String::To_Char(const char* p_msg) noexcept {
				// Check if the characters exist
				if (TRY_LINE p_msg == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was nullptr", ERROR_LINE, __FILEW__, L"To_Char"));
					return nullptr;
				}
				else {
					// Get the msg size 
					TRY_LINE size_t v_msg_size = std::strlen(p_msg) + 1;
					if (v_msg_size == 1) {
						SET_ERROR_STATE(PW_EMPTY_PARAMETER_W);
						SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::util::String", L"Invalid Parameter: p_msg was empty", ERROR_LINE, __FILEW__, L"To_Char"));
						return nullptr;
					}
					// Allocate the memory for the new msg
					char* v_msg{ nullptr };
					PW_CALL(v_msg = pw::co::Memory::Allocate<char>(v_msg_size), false);
					if (v_msg == nullptr) {
						return nullptr;
					}

					for (size_t i = 0; i < v_msg_size; i++) {
						v_msg[i] = p_msg[i];
					}

					return v_msg;
				}
			}
			char* String::To_Char(const std::string& p_msg) noexcept {
				// This function inherits the other To_Char errors
				return To_Char(p_msg.c_str());
			}
			std::wstring String::Evaluate_TWStr(const std::any& p_str) noexcept {
				// Use other converting function to do the work
				TRY_LINE wchar_t* v_msg = TO_WCHAR(p_str);

				if (v_msg == nullptr) {
					pw::er::Error_State::Handle_Error();

					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"pw::util::String::Evaluate_WStr(c_str)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_TWStr");
					return std::wstring();
				}
				std::wstring v_formated_msg{};

				v_formated_msg.append(v_msg);

				if (pw::co::Memory::Deallocate<wchar_t>(v_msg) == false) {
					if (v_msg != nullptr) {
						delete[] v_msg;
						v_msg = nullptr;
					}
				}

				return v_formated_msg;
			}
			std::string String::Evaluate_TStr(const std::any& p_str) noexcept {
				// Use other converting function to do the work
				TRY_LINE char* v_msg = TO_CHAR(p_str);

				if (v_msg == nullptr) {
					pw::er::Error_State::Handle_Error();

					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::util::String", L"\"pw::util::String::Evaluate_Str(w_str)\" had an error.", ERROR_LINE, __FILEW__, L"Evaluate_TStr");
					return std::string();
				}
				std::string v_formated_msg{};

				v_formated_msg.append(v_msg);

				if (pw::co::Memory::Deallocate<char>(v_msg) == false) {
					if (v_msg != nullptr) {
						delete[] v_msg;
						v_msg = nullptr;
					}
				}

				return v_formated_msg;
			}
			std::vector<std::wstring> String::Parse(const std::wstring& p_input, const std::vector<std::wstring>& p_delimeters) {
				if (p_input != L"" && p_delimeters != std::vector<std::wstring>()) {
					std::vector<std::wstring> v_output{};
					std::vector<size_t> v_positions{};

					for (std::wstring v_delimeter : p_delimeters) {
						uint64_t v_index{ 0 };
						uint64_t v_found{ 0 };
						v_found = p_input.find(v_delimeter, v_index);
						while (v_found != std::wstring::npos) {
							v_positions.push_back(v_found);

							v_index = v_found;

							v_found = p_input.find(v_delimeter, v_index + 1);
						}
					}
					std::sort(v_positions.begin(), v_positions.end());

					uint64_t v_previous{ 0 };
					for (uint64_t v_indices : v_positions) {
						if (v_previous == v_indices + 1) {
							continue;
						}
						std::wstring v_phrase = p_input.substr(v_previous, v_indices - v_previous);

						if (v_phrase != L"") {
							v_output.push_back(v_phrase);
						}

						v_previous = v_indices + 1;
					}
					if (v_positions.size() > 0) {
						uint64_t v_last_position = v_positions.at(v_positions.size() - 1);

						if (v_last_position < p_input.size() - 1) {
							std::wstring v_phrase = p_input.substr(v_last_position + 1, p_input.size() - v_last_position);

							if (v_phrase != L"") {
								v_output.push_back(v_phrase);
							}
						}
					}
					else {
						v_output.push_back(p_input);
					}

					return v_output;
				}
				return std::vector<std::wstring>();
			}
			std::vector<std::wstring> String::Parse_English(const std::wstring& p_input, std::vector<std::wstring> p_custom_delimeters) {
				if (p_input != L"") {
					std::vector<std::wstring> v_delimeters{
						L"\"", L"'", L"[", L"]", L"(", L")", L"...", L",", L":", L";", L"!", L"?", L".", L"-", L" ", L"{", L"}",
						L">", L"<", L"\\", L"/", L"_", L"=", L"+", L"`", L"~"
					};

					v_delimeters.insert(v_delimeters.end(), p_custom_delimeters.begin(), p_custom_delimeters.end());

					return Parse(p_input, v_delimeters);
				}
				return std::vector<std::wstring>();
			}
			std::vector<uint64_t> String::Find_All_Delimiters(const std::wstring& p_input, const std::vector<std::wstring>& p_delimeters) {
				if (p_input != L"" && p_delimeters != std::vector<std::wstring>()) {
					std::vector<uint64_t> v_output{};

					for (std::wstring v_delimeter : p_delimeters) {
						uint64_t v_index{ 0 };
						uint64_t v_found{ 0 };
						v_found = p_input.find(v_delimeter, v_index);
						while (v_found != std::wstring::npos) {
							v_output.push_back(v_found);

							v_index = v_found;

							v_found = p_input.find(v_delimeter, v_index + 1);
						}
					}
					std::sort(v_output.begin(), v_output.end());

					return v_output;
				}
				return std::vector<uint64_t>();
			}
			std::vector<uint64_t> String::Find_All_Delimiters_English(const std::wstring& p_input, std::vector<std::wstring> p_custom_delimeters) {
				if (p_input != L"") {
					std::vector<std::wstring> v_delimeters{
						L"\"", L"'", L"[", L"]", L"(", L")", L"...", L",", L":", L";", L"!", L"?", L".", L"-", L" ", L"{", L"}",
						L">", L"<", L"\\", L"/", L"_", L"=", L"+", L"`", L"~"
					};

					v_delimeters.insert(v_delimeters.end(), p_custom_delimeters.begin(), p_custom_delimeters.end());

					return Find_All_Delimiters(p_input, v_delimeters);
				}
				return std::vector<uint64_t>();
			}
			std::vector<uint64_t> String::Find_All_Words(const std::wstring& p_input, const std::vector<std::wstring>& p_delimeters) {
				if (p_input != L"" && p_delimeters != std::vector<std::wstring>()) {
					std::vector<uint64_t> v_output{};
					std::vector<uint64_t> v_positions{};

					for (std::wstring v_delimeter : p_delimeters) {
						uint64_t v_index{ 0 };
						uint64_t v_found{ 0 };
						v_found = p_input.find(v_delimeter, v_index);
						while (v_found != std::wstring::npos) {
							v_positions.push_back(v_found);

							v_index = v_found;

							v_found = p_input.find(v_delimeter, v_index + 1);
						}
					}
					std::sort(v_positions.begin(), v_positions.end());

					uint64_t v_previous{ 0 };
					for (uint64_t v_indices : v_positions) {
						if (v_previous == v_indices) {
							v_previous = v_indices + 1;
							continue;
						}
						v_output.push_back(v_previous);

						v_previous = v_indices + 1;
					}
					if (v_output.empty() == true) {
						v_output.push_back(0);
					}
					else {
						uint64_t v_last_position = v_positions.at(v_positions.size() - 1);

						if (v_previous != v_last_position) {
							v_output.push_back(v_last_position);
						}
					}
					return v_output;
				}
				return std::vector<uint64_t>();
			}
			std::vector<uint64_t> String::Find_All_Words_English(const std::wstring& p_input, std::vector<std::wstring> p_custom_delimeters) {
				if (p_input != L"") {
					std::vector<std::wstring> v_delimeters{
						L"\"", L"'", L"[", L"]", L"(", L")", L"...", L",", L":", L";", L"!", L"?", L".", L"-", L" ", L"{", L"}",
						L">", L"<", L"\\", L"/", L"_", L"=", L"+", L"`", L"~"
					};

					v_delimeters.insert(v_delimeters.end(), p_custom_delimeters.begin(), p_custom_delimeters.end());

					return Find_All_Words(p_input, v_delimeters);
				}
				return std::vector<uint64_t>();
			}
			std::vector<uint64_t> String::Find_All_Unsorted(const std::wstring& p_input, const std::vector<std::wstring>& p_phrases) {
				if (p_input != L"" && p_phrases != std::vector<std::wstring>()) {
					std::vector<uint64_t> v_output{};

					for (std::wstring v_phrase : p_phrases) {
						uint64_t v_index{ 0 };
						uint64_t v_found{ 0 };
						v_found = p_input.find(v_phrase, v_index);
						while (v_found != std::wstring::npos) {
							v_output.push_back(v_found);

							v_index = v_found;

							v_found = p_input.find(v_phrase, v_index + 1);
						}
					}
					return v_output;
				}
				return std::vector<uint64_t>();
			}
			std::vector<uint64_t> String::Find_All_Sorted(const std::wstring& p_input, const std::vector<std::wstring>& p_phrases) {
				if (p_input != L"" && p_phrases != std::vector<std::wstring>()) {
					std::vector<uint64_t> v_output{};

					v_output = Find_All_Unsorted(p_input, p_phrases);

					std::sort(v_output.begin(), v_output.end());

					return v_output;
				}
				return std::vector<uint64_t>();
			}
	UTIL_NAMESPACE_END
PW_NAMESPACE_END