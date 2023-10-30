#include "utility\string.h"

PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		// String
		// Static Declarations
		// Class Members
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
						L"\"", L"'", L"–", L"[", L"]", L"(", L")", L"—", L"...", L",", L":", L";", L"!", L"?", L".", L"-", L" ", L"{", L"}",
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
						L"\"", L"'", L"–", L"[", L"]", L"(", L")", L"—", L"...", L",", L":", L";", L"!", L"?", L".", L"-", L" ", L"{", L"}",
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
						L"\"", L"'", L"–", L"[", L"]", L"(", L")", L"—", L"...", L",", L":", L";", L"!", L"?", L".", L"-", L" ", L"{", L"}",
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