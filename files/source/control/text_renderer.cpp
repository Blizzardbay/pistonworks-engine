#include "control\text_renderer.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Text_Renderer  
		// Static Declarations
		std::vector<std::wstring> Text_Renderer::m_default_font_ids{};
		std::vector<std::wstring> Text_Renderer::m_default_font_names{};
		std::map<std::wstring, std::map<wchar_t, Text_Renderer::Character*>>* Text_Renderer::m_font_library{ nullptr };
		// Class Members  
			// Character 
			// Static Declarations
			// Class Members
				Text_Renderer::Character::Character(const wchar_t& p_type, BYTE* p_character_data, const glm::ivec2& p_character_size, const glm::ivec2& p_baseline_offset,
					const uint32_t p_spacing) :
						m_type{ p_type }, m_character_data{ nullptr },
						m_character_size{ p_character_size.x, p_character_size.y },
						m_baseline_offset{ p_baseline_offset.x, p_baseline_offset.y },
						m_spacing{ p_spacing / 64 } {
					if (p_character_data == NULL) {
						PW_CALL(m_character_data = pw::co::Memory::Allocate<st::Texture>(), false);
					}
					else {
						PW_CALL(
							m_character_data = pw::co::Memory::Allocate_Args<st::Texture>(
								p_character_data, p_character_size.x, p_character_size.y,
								GL_RED, GL_RED
							), false
						);
					}
				}
				Text_Renderer::Character::~Character() {
					if (pw::co::Memory::Deallocate<st::Texture>(m_character_data) == false) {
						if (m_character_data != nullptr) {
							delete m_character_data;
							m_character_data = nullptr;
						}
					}
				}
				const wchar_t& Text_Renderer::Character::Type() const {
					return m_type;
				}
				st::Texture* Text_Renderer::Character::Character_Data() {
					if (TRY_LINE m_character_data != nullptr) {
						PW_PTR_CALL(st::Texture * v_temp = pw::co::Memory::Allocate_Args<st::Texture>(*m_character_data), true);
						return v_temp;
					}
					else {
						SET_ERROR_STATE(PW_NULL_PARAMETER_S);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Text_Renderer", L"Invalid Parameter: m_character_data was nullptr", ERROR_LINE, __FILEW__, L"Character_Data"));
						return nullptr;
					}
					
				}
				const glm::ivec2& Text_Renderer::Character::Character_Size() const {
					return m_character_size;
				}
				const glm::ivec2& Text_Renderer::Character::Baseline_Offset() const {
					return m_baseline_offset;
				}
				const uint32_t& Text_Renderer::Character::Spacing() const {
					return m_spacing;
				}
				void Text_Renderer::Character::Set_Type(const wchar_t& p_type) {
					m_type = p_type;
				}
				void Text_Renderer::Character::Set_Texture(st::Texture* p_new_texture) {
					m_character_data = p_new_texture;
				}
		void Text_Renderer::Initialize() {
			typedef std::map<std::wstring, std::map<wchar_t, Character*>> FONT_LIBRARY;
			PW_CALL(m_font_library = pw::co::Memory::Allocate<FONT_LIBRARY>(), false);

			m_default_font_ids.push_back(L"arial");
			m_default_font_names.push_back(L"arial 1.ttf");
			m_default_font_ids.push_back(L"consolas");
			m_default_font_names.push_back(L"consola.ttf");
		}
		void Text_Renderer::Load_Engine_Fonts_Default() {
			std::wstring v_font_location = pw::cm::Constant::Pistonworks_Path().generic_wstring() + L"/files/resource/essential/font";

			FT_Library v_ft_library;
			PW_FT_CALL(FT_Init_FreeType(&v_ft_library), true);

			for (size_t i = 0; i < m_default_font_ids.size(); i++) {
				FT_Face v_face;

				std::filesystem::path v_file_location = co::File_Finder::Find_File(v_font_location, TO_WSTRING(m_default_font_names.at(i)));

				PW_FT_CALL(FT_New_Face(v_ft_library, v_file_location.generic_string().c_str(), 0, &v_face), true);

				PW_FT_CALL(FT_Set_Pixel_Sizes(v_face, 0, cm::Constant::PW_FONT_RESOLUTION), true);

				for (BYTE j = 0; j < 128; j++) {
					PW_FT_CALL(FT_Load_Char(v_face, j, FT_LOAD_RENDER), true);

					// Images are not flipped when loaded, so they need to be formated.
					// Flip across the horizontal axis
					if (v_face->glyph->bitmap.rows % 2 == 0) {
						for (size_t k = 0; k < (v_face->glyph->bitmap.rows) / 2; k++) {
							for (size_t o = 0; o < v_face->glyph->bitmap.width; o++) {
								BYTE ch = v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o] =
									v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o] = ch;
							}
						}
					}
					else {
						for (size_t k = 0; k < (v_face->glyph->bitmap.rows - 1) / 2; k++) {
							for (size_t o = 0; o < v_face->glyph->bitmap.width; o++) {
								BYTE ch = v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o] =
									v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o] = ch;
							}
						}
					}

					PW_CALL(
						Character * v_symbol = pw::co::Memory::Allocate_Args<Character>(
							(wchar_t)j, v_face->glyph->bitmap.buffer,
							glm::vec2(v_face->glyph->bitmap.width, v_face->glyph->bitmap.rows),
							glm::vec2(v_face->glyph->bitmap_left, v_face->glyph->bitmap_top), v_face->glyph->advance.x
							), true
					);

					if (m_font_library->count(m_default_font_ids.at(i)) < 1) {
						std::map<wchar_t, Character*> v_map = std::map<wchar_t, Character*>();
						v_map.insert(std::make_pair((wchar_t)j, v_symbol));
						m_font_library->insert(std::make_pair(m_default_font_ids.at(i), v_map));
					}
					else {
						auto v_found_character = m_font_library->at(m_default_font_ids.at(i)).find((wchar_t)j);
						if (v_found_character == m_font_library->at(m_default_font_ids.at(i)).end()) {
							m_font_library->at(m_default_font_ids.at(i)).insert(std::make_pair((wchar_t)j, v_symbol));
						}
					}
					v_symbol = nullptr;
				}
				PW_FT_CALL(FT_Done_Face(v_face), true);
			}
			PW_FT_CALL(FT_Done_FreeType(v_ft_library), false);
		}
		void Text_Renderer::Load_Engine_Fonts(const std::wstring& p_font_location, const std::vector<std::wstring>& p_font_ids, const std::vector<std::wstring>& p_font_names) {
			FT_Library v_ft_library;
			PW_FT_CALL(FT_Init_FreeType(&v_ft_library), true);

			for (size_t i = 0; i < p_font_ids.size(); i++) {
				FT_Face v_face;

				std::filesystem::path v_file_location = co::File_Finder::Find_File(p_font_location, TO_WSTRING(p_font_names.at(i)));

				PW_FT_CALL(FT_New_Face(v_ft_library, v_file_location.generic_string().c_str(), 0, &v_face), true);

				PW_FT_CALL(FT_Set_Pixel_Sizes(v_face, 0, cm::Constant::PW_FONT_RESOLUTION), true);

				for (BYTE j = 0; j < 128; j++) {
					PW_FT_CALL(FT_Load_Char(v_face, j, FT_LOAD_RENDER), true);

					// Images are not flipped when loaded, so they need to be formated.
					// Flip across the horizontal axis{
					if (v_face->glyph->bitmap.rows % 2 == 0) {
						for (size_t k = 0; k < (v_face->glyph->bitmap.rows) / 2; k++) {
							for (size_t o = 0; o < v_face->glyph->bitmap.width; o++) {
								BYTE ch = v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o] =
									v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o] = ch;
							}
						}
					}
					else {
						for (size_t k = 0; k < (v_face->glyph->bitmap.rows - 1) / 2; k++) {
							for (size_t o = 0; o < v_face->glyph->bitmap.width; o++) {
								BYTE ch = v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[(k * v_face->glyph->bitmap.width) + o] =
									v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o];
								v_face->glyph->bitmap.buffer[((v_face->glyph->bitmap.rows - 1 - k) * v_face->glyph->bitmap.width) + o] = ch;
							}
						}
					}

					PW_CALL(
						Character* v_symbol = pw::co::Memory::Allocate_Args<Character>(
							(wchar_t)j, v_face->glyph->bitmap.buffer,
							glm::vec2(v_face->glyph->bitmap.width, v_face->glyph->bitmap.rows),
							glm::vec2(v_face->glyph->bitmap_left, v_face->glyph->bitmap_top), v_face->glyph->advance.x
						), true
					);

					if (m_font_library->count(p_font_ids.at(i)) < 1) {
						std::map<wchar_t, Character*> v_map = std::map<wchar_t, Character*>();
						v_map.insert(std::make_pair((wchar_t)j, v_symbol));
						m_font_library->insert(std::make_pair(p_font_ids.at(i), v_map));
					}
					else {
						auto v_found_character = m_font_library->at(p_font_ids.at(i)).find((wchar_t)j);
						if (v_found_character == m_font_library->at(p_font_ids.at(i)).end()) {
							m_font_library->at(p_font_ids.at(i)).insert(std::make_pair((wchar_t)j, v_symbol));
						}
					}
					v_symbol = nullptr;
				}
				PW_FT_CALL(FT_Done_Face(v_face), true);
			}
			PW_FT_CALL(FT_Done_FreeType(v_ft_library), false);
		}
		void Text_Renderer::Release() {
			for (auto i = m_font_library->begin(); i != m_font_library->end(); i++) {
				for (auto j = i->second.begin(); j != i->second.end(); j++) {
					if (pw::co::Memory::Deallocate<Character>(j->second) == false) {
						if (j->second != nullptr) {
							delete j->second;
							j->second = nullptr;
						}
					}
					j->second = nullptr;
				}
			}
			if (pw::co::Memory::Deallocate<std::map<std::wstring, std::map<wchar_t, Character*>>>(m_font_library) == false) {
				if (m_font_library != nullptr) {
					delete m_font_library;
					m_font_library = nullptr;
				}
			}
			m_default_font_ids = std::vector<std::wstring>();
			m_default_font_names = std::vector<std::wstring>();
		}
		Text_Renderer::Character* Text_Renderer::Create_Character(const wchar_t& p_letter_type, const std::wstring& p_font_type) {
			auto v_found = m_font_library->find(p_font_type);
			if (v_found != m_font_library->end()) {
				auto v_found_character = v_found->second.find(p_letter_type);
				if (v_found_character != v_found->second.end()) {
					return v_found_character->second;
				}
			}
			return nullptr;
		}
	CO_NAMESPACE_END
PW_NAMESPACE_END