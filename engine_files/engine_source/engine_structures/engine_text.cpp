#include "engine_structures\engine_text.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Character 
		// Static Declarations
		// Class Members
			Character::Character(const wchar_t& p_type, BYTE* p_character_data, const glm::ivec2& p_character_size, const glm::ivec2& p_baseline_offset, const uint32_t& p_spacing) :
					m_type{ p_type }, m_character_data{ nullptr },
					m_character_size{ TO_INT32((float)(p_character_size.x) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
							TO_INT32((float)(p_character_size.y) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR) },
					m_baseline_offset{TO_INT32((float)(p_baseline_offset.x) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
							TO_INT32((float)(p_baseline_offset.y) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)},
					m_spacing{ TO_UINT32((float)(p_spacing / 64) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR) } {
				try {
					if (p_character_data == NULL) {
						m_character_data = pw::Engine_Memory::Allocate<st::Texture>();
					}
					else {
						m_character_data = pw::Engine_Memory::Allocate<st::Texture, bool>(p_character_data, p_character_size.x, p_character_size.y, GL_RED, GL_RED);
					}
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			Character::~Character() {
				if (pw::Engine_Memory::Deallocate<st::Texture>(m_character_data) == false) {
					if (m_character_data != nullptr) {
						delete m_character_data;
						m_character_data = nullptr;
					}
				}
			}
			const wchar_t& Character::Type() const {
				return m_type;
			}
			st::Texture* Character::Character_Data() {
				try {
					return pw::Engine_Memory::Allocate<st::Texture, bool>(*m_character_data);
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
			}
			const glm::ivec2& Character::Character_Size() const {
				return m_character_size;
			}
			const glm::ivec2& Character::Baseline_Offset() const {
				return m_baseline_offset;
			}
			const uint32_t& Character::Spacing() const {
				return m_spacing;
			}
			void Character::Set_Type(const wchar_t& p_type) {
				m_type = p_type;
			}
			void Character::Set_Texture(st::Texture* p_new_texture) {
				m_character_data = p_new_texture;
			}
		// End of Class Members
		// Text
		// Static Declarations
		// Class Members
			Text::Text() :
					m_text{}, m_text_string{}, m_text_position{ glm::vec2(0.0f, 0.0f) }, m_text_size{ glm::vec2(0.0f, 0.0f) }, m_text_color{},
					m_raw_text_position{}, m_raw_text_size{} {
			}
			Text::Text(const std::wstring& p_text, const glm::ivec2& p_position, const glm::ivec2& p_size, const glm::vec4& p_color, const std::wstring& p_font_type) :
					m_text{ p_text }, m_text_string{}, m_text_position{ p_position }, m_text_size{ glm::vec2(0.0f, p_size.y) }, m_text_font{ p_font_type }, m_text_color{ p_color },
					m_raw_text_position{ p_position }, m_raw_text_size{ p_size } {
				try {
					float v_max_height = 0.0f;

					float v_y_scale = p_size.y / (float)pw::cm::Engine_Constant::PW_SCALE_FACTOR;
					float v_x_scale = p_size.x / (float)pw::cm::Engine_Constant::PW_SCALE_FACTOR;


					for (size_t i = 0; i < p_text.size(); i++) {
						Character* v_current_char = Text_Renderer::Create_Character(p_text[i], p_font_type);

						float v_character_height = (float)v_current_char->Character_Size().y * v_y_scale;

						st::Model* v_char_model{ nullptr };

						// Getting characters for most fonts ideally positioned does not really work
						// for the way positions are calculated, so we will have to segregate the lower
						// baseline characters
						if (p_text[i] == L'g' || p_text[i] == L'p' || p_text[i] == L'y') {
							v_char_model = pw::Engine_Memory::Allocate<Model, bool>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
								glm::vec2(m_text_position.x + ((float)v_current_char->Baseline_Offset().x * v_x_scale),
									m_text_position.y - (p_size.y - ((float)v_current_char->Baseline_Offset().y * v_y_scale))),
								0.0f, glm::vec2(((float)v_current_char->Character_Size().x * v_x_scale),
									(v_character_height)),
								p_color);
						}
						else {
							v_char_model = pw::Engine_Memory::Allocate<Model, bool>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
								glm::vec2(m_text_position.x + ((float)v_current_char->Baseline_Offset().x * v_x_scale),
									m_text_position.y - (p_size.y - (((float)v_current_char->Baseline_Offset().y + ((float)v_current_char->Character_Size().y - (float)v_current_char->Baseline_Offset().y)) * v_y_scale))),
								0.0f, glm::vec2(((float)v_current_char->Character_Size().x * v_x_scale),
									(v_character_height)),
								p_color);
						}

						if (v_character_height > v_max_height) {
							v_max_height = v_character_height;
						}

						m_text_string.push_back(v_char_model);
						m_text_position.x = m_text_position.x + TO_INT32((float)v_current_char->Spacing() * v_x_scale);
						m_text_size.x = m_text_size.x + TO_INT32((float)v_current_char->Spacing() * v_x_scale);
					}
					m_text_position.y = m_text_position.y - (m_text_size.y - v_max_height);
					m_text_size.y = v_max_height;
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			Text::~Text() {
				for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Model>(*i) == false) {
						if (*i != nullptr) {
							delete *i;
							*i = nullptr;
						}
					}
				}
			}
			void Text::Render() {
				for (size_t i = 0; i < m_text_string.size(); i++) {
					m_text_string.at(i)->Render(1);
				}
			}
			void Text::Set_Position(const glm::vec2& p_new_position) {
				if (m_raw_text_position != p_new_position) {
					float v_difference_x_overall = p_new_position.x - m_raw_text_position.x;
					float v_difference_y_overall = p_new_position.y - m_raw_text_position.y;
					for (size_t i = 0; i < m_text_string.size(); i++) {
						float v_difference_x = p_new_position.x - m_text_string.at(i)->Position().x;
						float v_difference_y = p_new_position.y - m_text_string.at(i)->Position().y;

						m_text_string.at(i)->Set_Position(glm::vec2(m_text_string.at(i)->Position().x + v_difference_x,
							m_text_string.at(i)->Position().y + v_difference_y));
					}
					m_text_position.x = m_text_position.x + v_difference_x_overall;
					m_text_position.y = m_text_position.y + v_difference_y_overall;

					m_raw_text_position = p_new_position;
				}
			}
			void Text::Set_Offset(const glm::vec3& p_from) {
				for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {

					glm::vec2 v_origin = (*i)->Position();

					(*i)->Set_Position(p_from);

					(*i)->Set_Offset(glm::vec2(v_origin.x, v_origin.y - (float)pw::cm::Engine_Constant::Window_Height()));
				}
			}
			void Text::Set_Text(const std::wstring& p_new_text) {
				try {
					if (m_text != p_new_text) {
						for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {
							if (pw::Engine_Memory::Deallocate<st::Model>(*i) == false) {
								if (*i != nullptr) {
									delete *i;
									*i = nullptr;
								}
							}
						}
						m_text_string.clear();

						float v_max_height = 0.0f;

						float v_y_scale = m_raw_text_size.y / pw::cm::Engine_Constant::PW_SCALE_FACTOR;
						float v_x_scale = m_raw_text_size.x / pw::cm::Engine_Constant::PW_SCALE_FACTOR;

						float v_position_x = m_raw_text_position.x;

						for (size_t i = 0; i < p_new_text.size(); i++) {
							Character* v_current_char = Text_Renderer::Create_Character(p_new_text[i], m_text_font);

							float v_character_height = (float)v_current_char->Character_Size().y * v_y_scale;

							st::Model* v_char_model{ nullptr };

							// Getting characters for most fonts ideally positioned does not really work
							// for the way positions are calculated, so we will have to segregate the lower
							// baseline characters
							if (m_text[i] == L'g' || m_text[i] == L'p' || m_text[i] == L'y') {
								v_char_model = pw::Engine_Memory::Allocate<Model, bool>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
									glm::vec2(v_position_x + ((float)v_current_char->Baseline_Offset().x * v_x_scale),
										m_raw_text_position.y - (m_raw_text_size.y - ((float)v_current_char->Baseline_Offset().y * v_y_scale))),
									0.0f, glm::vec2(((float)v_current_char->Character_Size().x * v_x_scale),
										(v_character_height)),
									m_text_color);
							}
							else {
								v_char_model = pw::Engine_Memory::Allocate<Model, bool>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
									glm::vec2(v_position_x + ((float)v_current_char->Baseline_Offset().x * v_x_scale),
										m_raw_text_position.y - (m_raw_text_size.y - (((float)v_current_char->Baseline_Offset().y + ((float)v_current_char->Character_Size().y - (float)v_current_char->Baseline_Offset().y)) * v_y_scale))),
									0.0f, glm::vec2(((float)v_current_char->Character_Size().x * v_x_scale),
										(v_character_height)),
									m_text_color);
							}

							if (v_character_height > v_max_height) {
								v_max_height = v_character_height;
							}

							m_text_string.push_back(v_char_model);
							v_position_x = v_position_x + TO_INT32((float)v_current_char->Spacing() * v_x_scale);
							m_text_size.x = m_text_size.x + TO_INT32((float)v_current_char->Spacing() * v_x_scale);
						}
						m_text_position.y = m_text_position.y - (m_raw_text_size.y - v_max_height);
						m_text_size.y = v_max_height;

						m_text = p_new_text;
					}
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Text::Set_Size(const glm::vec2& p_size) {
				try {
					double v_x_ratio = p_size.x / m_text_size.x;
					double v_y_ratio = p_size.y / m_text_size.y;

					size_t v_spacing = 0;
					for (size_t i = 0; i < m_text_string.size(); i++) {
						Model* v_current_model = m_text_string.at(i);

						if (OFFU64(i) < m_text_string.size()) {
							v_spacing = TO_UINT64((TO_UINT64(v_current_model->Position().x) + TO_UINT64(v_current_model->Size().x)) - TO_UINT64(m_text_string.at(OFFU64(i))->Position().x));
						}

						v_spacing = TO_UINT64(TO_FLOAT(v_spacing) * v_x_ratio);

						if (i != 0) {
							v_current_model->Set_Position(glm::vec2(v_current_model->Position().x + v_spacing, v_current_model->Position().y));
						}
						v_current_model->Set_Size(glm::vec2(v_current_model->Size().x * v_x_ratio, v_current_model->Size().y * v_y_ratio));
					}
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Text::Set_Text_Color(const glm::vec4& p_new_color) {
				try {
					for (size_t i = 0; i < m_text_string.size(); i++) {
						Model* v_current_model = m_text_string.at(i);

						v_current_model->Set_Model_Color(p_new_color);
					}
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			glm::vec2& Text::Position_Reference() {
				return m_text_position;
			}
			const glm::vec2& Text::Position() const {
				return m_text_position;
			}
			const glm::vec2& Text::Size() const {
				return m_text_size;
			}
			const uint64_t Text::Count() const {
				return m_text_string.size();
			}
		// End of Class Members
		// Text_Renderer  
		// Static Declarations
			std::map<std::wstring, std::map<wchar_t, Character*>>* Text_Renderer::m_font_library{ nullptr };
		// Class Members  
			void Text_Renderer::Initialize_Text_Renderer() {
				m_font_library = pw::Engine_Memory::Allocate<std::map<std::wstring, std::map<wchar_t, Character*>>>();
			}
			void Text_Renderer::Load_Engine_Fonts(const std::wstring& p_font_location, const std::vector<std::wstring>& p_font_ids, const std::vector<std::wstring>& p_font_names) {
				try {
					FT_Library v_ft_library;
					PW_FT_CALL(FT_Init_FreeType(&v_ft_library));

					for (size_t i = 0; i < p_font_ids.size(); i++) {
						FT_Face v_face;

						std::filesystem::path v_file_location = co::File_Finder::Find_File(p_font_location, TO_WSTRING(p_font_names.at(i)));

						PW_FT_CALL(FT_New_Face(v_ft_library, v_file_location.generic_string().c_str(), 0, &v_face));

						PW_FT_CALL(FT_Set_Pixel_Sizes(v_face, 0, cm::Engine_Constant::PW_FONT_RESOLUTION));

						for (BYTE j = 0; j < 128; j++) {
							PW_FT_CALL(FT_Load_Char(v_face, j, FT_LOAD_RENDER));

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

							Character* v_symbol = pw::Engine_Memory::Allocate<Character, bool>(
								(wchar_t)j, v_face->glyph->bitmap.buffer,
								glm::vec2(v_face->glyph->bitmap.width, v_face->glyph->bitmap.rows),
								glm::vec2(v_face->glyph->bitmap_left, v_face->glyph->bitmap_top), v_face->glyph->advance.x);

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
						PW_FT_CALL(FT_Done_Face(v_face));
					}
					PW_FT_CALL(FT_Done_FreeType(v_ft_library));
				}
				catch (const er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Text_Renderer::Release_Engine_Fonts() {
				for (auto i = m_font_library->begin(); i != m_font_library->end(); i++) {
					for (auto j = i->second.begin(); j != i->second.end(); j++) {
						if (pw::Engine_Memory::Deallocate<Character>(j->second) == false) {
							if (j->second != nullptr) {
								delete j->second;
								j->second = nullptr;
							}
						}
						j->second = nullptr;
					}
				}
				if (pw::Engine_Memory::Deallocate<std::map<std::wstring, std::map<wchar_t, Character*>>>(m_font_library) == false) {
					if (m_font_library != nullptr) {
						delete m_font_library;
						m_font_library = nullptr;
					}
				}
			}
			Character* Text_Renderer::Create_Character(const wchar_t& p_letter_type, const std::wstring& p_font_type) {
				auto v_found = m_font_library->find(p_font_type);
				if (v_found != m_font_library->end()) {
					auto v_found_character = v_found->second.find(p_letter_type);
					if (v_found_character != v_found->second.end()) {
						return v_found_character->second;
					}
				}
				return nullptr;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////