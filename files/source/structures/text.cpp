#include "structures\text.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		// Text
		// Static Declarations
		// Class Members
			Text::Text() :
					m_text{}, m_text_string{}, m_text_position{ glm::vec2(0.0f, 0.0f) }, m_text_size{ glm::vec2(0.0f, 0.0f) },
					m_current_settings{ Color_Settings::SOLID_ALL }, m_default_color{ 0.0f }, m_stored_cypher_colors{}, m_stored_colors{},
					m_raw_text_position{}, m_raw_text_size{}, m_is_copy{ false } {
			}
			Text::Text(const std::wstring& p_text, const glm::vec2& p_position, const glm::vec2& p_size, const glm::vec4& p_color, const std::wstring& p_font_type) :
					m_text{ p_text }, m_text_string{}, m_text_position{ p_position }, m_text_size{ glm::vec2(0.0f, p_size.y) }, m_text_font{ p_font_type },
					m_current_settings{ Color_Settings::SOLID_ALL }, m_default_color{ p_color }, m_stored_cypher_colors{}, m_stored_colors{},
					m_raw_text_position{ p_position }, m_raw_text_size{ p_size }, m_is_copy{ false } {
				float v_max_height = 0.0f;

				int32_t v_char_x_size{ 0 };
				int32_t v_char_y_size{ 0 };
				glm::vec2 v_baseline_size{ 0 };
				int32_t v_char_spacing{ 0 };
				pw::co::Text_Renderer::Character* v_current_char = nullptr;
				for (size_t i = 0; i < p_text.size(); i++) {
					v_current_char = pw::co::Text_Renderer::Create_Character(p_text[i], p_font_type);

					if (v_current_char == nullptr) {
						continue;
					}
					
					v_char_x_size = TO_INT32(((float)v_current_char->Character_Size().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);
					v_char_y_size = TO_INT32(((float)v_current_char->Character_Size().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y);
					v_baseline_size = glm::vec2(
						(((float)v_current_char->Baseline_Offset().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x),
						(((float)v_current_char->Baseline_Offset().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y)
					);
					v_char_spacing = TO_INT32(((float)v_current_char->Spacing() / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);

					st::Model* v_char_model{ nullptr };

					PW_CALL(v_char_model = pw::co::Memory::Allocate_Args<Model>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
						glm::vec2(m_text_position.x + v_baseline_size.x,
							m_text_position.y - (p_size.y - v_char_y_size) - (v_char_y_size - v_baseline_size.y)),
						0.0f, glm::vec2(v_char_x_size, v_char_y_size),
						p_color, false, false, 1), true
					);

					if (v_char_y_size > v_max_height) {
						v_max_height = TO_FLOAT(v_char_y_size);
					}

					m_text_string.push_back(v_char_model);
					m_text_position.x = m_text_position.x + v_char_spacing;
					m_text_size.x = m_text_size.x + v_char_spacing;
				}
				m_text_position.y = m_text_position.y - (m_text_size.y - v_max_height);
				m_text_size.y = v_max_height;
			}
			Text::Text(const std::wstring& p_text, const glm::vec2& p_position, const glm::vec2& p_size, const glm::vec4& p_default_color, const std::vector<glm::vec4>& p_colors, const std::wstring& p_font_type, const Color_Settings& p_settings) :
				m_text{ p_text }, m_text_string{}, m_text_position{ p_position }, m_text_size{ glm::vec2(0.0f, p_size.y) }, m_text_font{ p_font_type },
				m_current_settings{ p_settings }, m_default_color{ p_default_color }, m_stored_cypher_colors{}, m_stored_colors{ p_colors },
				m_raw_text_position{ p_position }, m_raw_text_size{ p_size }, m_is_copy{ false } {
				float v_max_height = 0.0f;

				int32_t v_char_x_size{ 0 };
				int32_t v_char_y_size{ 0 };
				glm::vec2 v_baseline_size{ 0 };
				int32_t v_char_spacing{ 0 };

				if (p_colors.empty() == true) {
					this->Text::Text(p_text, p_position, p_size, p_default_color, p_font_type);
					return;
				}

				switch (m_current_settings) {
					case Color_Settings::SINGLE_REPEAT: {
						std::vector<uint64_t> v_delimiters = pw::util::String::Find_All_Delimiters_English(m_text);
						std::vector<uint64_t>::iterator v_current_delimiter = v_delimiters.begin();

						std::vector<glm::vec4>::const_iterator v_current_color = p_colors.begin();

						for (size_t i = 0; i < p_text.size(); i++) {
							pw::co::Text_Renderer::Character* v_current_char = pw::co::Text_Renderer::Create_Character(p_text[i], p_font_type);

							if (v_current_char == nullptr) {
								continue;
							}

							v_char_x_size = TO_INT32(((float)v_current_char->Character_Size().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);
							v_char_y_size = TO_INT32(((float)v_current_char->Character_Size().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y);
							v_baseline_size = glm::vec2(
								(((float)v_current_char->Baseline_Offset().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x),
								(((float)v_current_char->Baseline_Offset().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y)
							);
							v_char_spacing = TO_INT32(((float)v_current_char->Spacing() / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);

							st::Model* v_char_model{ nullptr };

							if (v_current_delimiter != v_delimiters.end()) {
								if (i == (*v_current_delimiter)) {
									PW_CALL(v_char_model = pw::co::Memory::Allocate_Args<Model>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
										glm::vec2(m_text_position.x + v_baseline_size.x,
											m_text_position.y - (p_size.y - v_char_y_size) - (v_char_y_size - v_baseline_size.y)),
										0.0f, glm::vec2(v_char_x_size, v_char_y_size),
										p_default_color, false, false, 1), true
									);
								}
								else {
									PW_CALL(v_char_model = pw::co::Memory::Allocate_Args<Model>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
										glm::vec2(m_text_position.x + v_baseline_size.x,
											m_text_position.y - (p_size.y - v_char_y_size) - (v_char_y_size - v_baseline_size.y)),
										0.0f, glm::vec2(v_char_x_size, v_char_y_size),
										(*v_current_color), false, false, 1), true
									);
								}
							}
							else {
								PW_CALL(v_char_model = pw::co::Memory::Allocate_Args<Model>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
									glm::vec2(m_text_position.x + v_baseline_size.x,
										m_text_position.y - (p_size.y - v_char_y_size) - (v_char_y_size - v_baseline_size.y)),
									0.0f, glm::vec2(v_char_x_size, v_char_y_size),
									(*v_current_color), false, false, 1), true
								);
							}

							if (v_char_y_size > v_max_height) {
								v_max_height = TO_FLOAT(v_char_y_size);
							}

							m_text_string.push_back(v_char_model);
							m_text_position.x = m_text_position.x + v_char_spacing;
							m_text_size.x = m_text_size.x + v_char_spacing;
							if (v_current_delimiter != v_delimiters.end()) {
								if (i == (*v_current_delimiter)) {
									if ((v_current_delimiter + 1) != v_delimiters.end()) {
										v_current_delimiter = v_current_delimiter + 1;
									}
								}
								else {
									v_current_color = v_current_color + 1;
									if (v_current_color == p_colors.end()) {
										v_current_color = p_colors.begin();
									}
								}
							}
							else {
								v_current_color = v_current_color + 1;
								if (v_current_color == p_colors.end()) {
									v_current_color = p_colors.begin();
								}
							}
						}
						break;
					}
					case Color_Settings::WORD_REPEAT: {
						std::vector<uint64_t> v_delimiters = pw::util::String::Find_All_Delimiters_English(m_text);
						std::vector<glm::vec4>::const_iterator v_current_color = p_colors.begin();
						std::vector<uint64_t>::iterator v_current_delimiter = v_delimiters.begin();

						glm::vec4 v_color{ 0.0f };
						bool v_last_dilimiter{ false };

						if (v_current_delimiter == v_delimiters.end()) {
							this->Text::Text(p_text, p_position, p_size, p_default_color, p_font_type);
							return;
						}

						for (size_t i = 0; i < p_text.size(); i++) {
							if (i < (*v_current_delimiter)) {
								if (v_last_dilimiter == true) {
									v_current_color = v_current_color + 1;
									if (v_current_color == p_colors.end()) {
										v_current_color = p_colors.begin();
									}
									v_color = (*v_current_color);

									v_last_dilimiter = false;
								}
								else {
									v_color = (*v_current_color);
								}
							}
							else {
								if ((*v_current_delimiter) == v_delimiters.at(v_delimiters.size() - 1) && i != (*v_current_delimiter)) {
									if (v_last_dilimiter == true) {
										v_current_color = v_current_color + 1;
										if (v_current_color == p_colors.end()) {
											v_current_color = p_colors.begin();
										}
										v_color = (*v_current_color);

										v_last_dilimiter = false;
									}
									else {
										v_color = (*v_current_color);
									}
								}
								else {
									v_color = m_default_color;
									v_last_dilimiter = true;
									if ((v_current_delimiter + 1) != v_delimiters.end()) {
										v_current_delimiter = v_current_delimiter + 1;
									}
								}
							}
							pw::co::Text_Renderer::Character* v_current_char = pw::co::Text_Renderer::Create_Character(p_text[i], p_font_type);

							if (v_current_char == nullptr) {
								continue;
							}

							v_char_x_size = TO_INT32(((float)v_current_char->Character_Size().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);
							v_char_y_size = TO_INT32(((float)v_current_char->Character_Size().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y);
							v_baseline_size = glm::vec2(
								(((float)v_current_char->Baseline_Offset().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x),
								(((float)v_current_char->Baseline_Offset().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y)
							);
							v_char_spacing = TO_INT32(((float)v_current_char->Spacing() / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);

							st::Model* v_char_model{ nullptr };

							PW_CALL(v_char_model = pw::co::Memory::Allocate_Args<Model>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
								glm::vec2(m_text_position.x + v_baseline_size.x,
									m_text_position.y - (p_size.y - v_char_y_size) - (v_char_y_size - v_baseline_size.y)),
								0.0f, glm::vec2(v_char_x_size, v_char_y_size),
								v_color, false, false, 1), true
							);

							if (v_char_y_size > v_max_height) {
								v_max_height = TO_FLOAT(v_char_y_size);
							}

							m_text_string.push_back(v_char_model);
							m_text_position.x = m_text_position.x + v_char_spacing;
							m_text_size.x = m_text_size.x + v_char_spacing;
						}
						break;
					}
					default: {
						this->Text::Text(p_text, p_position, p_size, p_default_color, p_font_type);
						return;
					}
				}
				m_text_position.y = m_text_position.y - (m_text_size.y - v_max_height);
				m_text_size.y = v_max_height;
			}
			Text::Text(const std::wstring& p_text, const glm::vec2& p_position, const glm::vec2& p_size, const glm::vec4& p_default_color, const std::vector<std::pair<glm::vec4, std::vector<std::wstring>>>& p_colors, const std::wstring& p_font_type) :
				m_text{ p_text }, m_text_string{}, m_text_position{ p_position }, m_text_size{ glm::vec2(0.0f, p_size.y) }, m_text_font{ p_font_type },
				m_current_settings{ Color_Settings::TARGET_CYPHER }, m_default_color{ p_default_color }, m_stored_cypher_colors{ p_colors }, m_stored_colors{},
				m_raw_text_position{ p_position }, m_raw_text_size{ p_size }, m_is_copy{ false } {
				std::vector<std::wstring> v_words = pw::util::String::Parse_English(p_text);
				std::vector<uint64_t> v_dilimiters = pw::util::String::Find_All_Delimiters_English(p_text);
				std::vector<uint64_t> v_word_positions = pw::util::String::Find_All_Words_English(p_text);

				std::vector<const glm::vec4*> v_colors{};

				v_colors.resize(p_text.size(), nullptr);

				for (uint64_t i = 0; i < p_colors.size(); i++) {
					for (std::wstring v_phrase_1 : p_colors.at(i).second) {
						for (uint64_t j = 0; j < v_words.size(); j++) {
							std::wstring v_phrase_2 = v_words.at(j);
							if (v_phrase_1 == v_phrase_2) {
								uint64_t v_where = v_word_positions[j];
								if (v_where + v_phrase_2.size() == p_text.size() - 1) {
									for (uint64_t k = v_where; k <= v_where + v_phrase_2.size(); k++) {
										v_colors[k] = &p_colors.at(i).first;
									}
								}
								else {
									for (uint64_t k = v_where; k < v_where + v_phrase_2.size(); k++) {
										v_colors[k] = &p_colors.at(i).first;
									}
								}
							}
						}
					}
				}
				for (uint64_t i = 0; i < v_colors.size();i++) {
					if (v_colors[i] == nullptr) {
						v_colors[i] = &m_default_color;
					}
				}
				float v_max_height = 0.0f;

				int32_t v_char_x_size{ 0 };
				int32_t v_char_y_size{ 0 };
				glm::vec2 v_baseline_size{ 0 };
				int32_t v_char_spacing{ 0 };

				for (size_t i = 0; i < p_text.size(); i++) {
					pw::co::Text_Renderer::Character* v_current_char = pw::co::Text_Renderer::Create_Character(p_text[i], p_font_type);

					if (v_current_char == nullptr) {
						continue;
					}

					v_char_x_size = TO_INT32(((float)v_current_char->Character_Size().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);
					v_char_y_size = TO_INT32(((float)v_current_char->Character_Size().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y);
					v_baseline_size = glm::vec2(
						(((float)v_current_char->Baseline_Offset().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x),
						(((float)v_current_char->Baseline_Offset().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y)
					);
					v_char_spacing = TO_INT32(((float)v_current_char->Spacing() / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);

					st::Model* v_char_model{ nullptr };

					PW_CALL(v_char_model = pw::co::Memory::Allocate_Args<Model>(Geometry_Types::SQUARE, v_current_char->Character_Data(),
						glm::vec2(m_text_position.x + v_baseline_size.x,
							m_text_position.y - (p_size.y - v_char_y_size) - (v_char_y_size - v_baseline_size.y)),
						0.0f, glm::vec2(v_char_x_size, v_char_y_size),
						(*v_colors[i]), false, false, 1), true
					);

					if (v_char_y_size > v_max_height) {
						v_max_height = TO_FLOAT(v_char_y_size);
					}

					m_text_string.push_back(v_char_model);
					m_text_position.x = m_text_position.x + v_char_spacing;
					m_text_size.x = m_text_size.x + v_char_spacing;
				}
				m_text_position.y = m_text_position.y - (m_text_size.y - v_max_height);
				m_text_size.y = v_max_height;
			}
			Text& Text::operator=(Text&& p_rhs) noexcept {
				m_text = p_rhs.m_text;
				m_text_string = p_rhs.m_text_string;
				m_text_position = p_rhs.m_text_position;
				m_text_size = p_rhs.m_text_size;
				m_current_settings = p_rhs.m_current_settings;
				m_default_color = p_rhs.m_default_color;
				m_stored_cypher_colors = p_rhs.m_stored_cypher_colors;
				m_stored_colors = p_rhs.m_stored_colors;

				m_raw_text_position = p_rhs.m_raw_text_position;
				m_raw_text_size = p_rhs.m_raw_text_size;
				m_text_font = p_rhs.m_text_font;

				m_is_copy = false;
				p_rhs.m_is_copy = true;

				return *this;
			}
			Text::~Text() {
				if (m_is_copy != true) {
					for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {
						if (pw::co::Memory::Deallocate<st::Model>(*i) == false) {
							if (*i != nullptr) {
								delete* i;
								*i = nullptr;
							}
						}
					}
				}
			}
			void Text::Render(const uint32_t p_layer) {
				for (size_t i = 0; i < m_text_string.size(); i++) {
					PW_CALL(m_text_string.at(i)->Render(p_layer), true);
				}
			}
			void Text::Set_Position(const glm::vec2& p_new_position) {
				if (m_text_string.size() > 0) {
					if (m_text_string.at(0)->Is_Attached() == true) {
						return;
					}
				}
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
			void Text::Attach_To(glm::vec2* p_position) {
				for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {

					glm::vec2 v_origin = (*i)->Position();

					(*i)->Attach_To(p_position);

					(*i)->Set_Offset(glm::vec2(v_origin.x - p_position->x, v_origin.y - p_position->y));
				}
			}
			void Text::Set_Offset(const glm::vec2& p_offset) {
				for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {
					(*i)->Set_Offset((*i)->Offset() + p_offset);
				}
			}
			void Text::Set_Text(const std::wstring& p_new_text) {
				if (m_text != p_new_text) {
					for (auto i = m_text_string.begin(); i != m_text_string.end(); i++) {
						if (pw::co::Memory::Deallocate<st::Model>(*i) == false) {
							if (*i != nullptr) {
								delete* i;
								*i = nullptr;
							}
						}
					}
					m_text_string.clear();
					switch (m_current_settings) {
						case Color_Settings::SINGLE_REPEAT: {
							(*this) = Text::Text(p_new_text, m_raw_text_position, m_raw_text_size, m_default_color, m_stored_colors, m_text_font, Color_Settings::SINGLE_REPEAT);
							break;
						}
						case Color_Settings::WORD_REPEAT: {
							(*this) = Text::Text(p_new_text, m_raw_text_position, m_raw_text_size, m_default_color, m_stored_colors, m_text_font, Color_Settings::WORD_REPEAT);
							break;
						}
						case Color_Settings::TARGET_CYPHER: {
							(*this) = Text::Text(p_new_text, m_raw_text_position, m_raw_text_size, m_default_color, m_stored_cypher_colors, m_text_font);
							break;
						}
						default: {
							(*this) = Text::Text(p_new_text, m_raw_text_position, m_raw_text_size, m_default_color, m_text_font);
							return;
						}
					}
				}
			}
			void Text::Set_Size(const glm::vec2& p_size) {
				double v_x_ratio = p_size.x / m_text_size.x;
				double v_y_ratio = p_size.y / m_text_size.y;

				size_t v_spacing = 0;
				for (size_t i = 0; i < m_text_string.size(); i++) {
					Model* v_current_model = m_text_string.at(i);

					if (OFF_UINT64(i) < m_text_string.size()) {
						v_spacing = TO_UINT64((TO_UINT64(v_current_model->Position().x) + TO_UINT64(v_current_model->Size().x)) - TO_UINT64(m_text_string.at(OFF_UINT64(i))->Position().x));
					}

					v_spacing = TO_UINT64(TO_FLOAT(v_spacing) * v_x_ratio);

					if (i != 0) {
						v_current_model->Set_Position(glm::vec2(v_current_model->Position().x + v_spacing, v_current_model->Position().y));
					}
					v_current_model->Set_Size(glm::vec2(v_current_model->Size().x * v_x_ratio, v_current_model->Size().y * v_y_ratio));
				}
			}
			void Text::Set_Text_Color(const glm::vec4& p_new_color) {
				for (size_t i = 0; i < m_text_string.size(); i++) {
					Model* v_current_model = m_text_string.at(i);

					PW_CALL(v_current_model->Set_Model_Color(p_new_color), true);
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
			const std::wstring& Text::String() const {
				return m_text;
			}
			const std::vector<st::Model*>& Text::Models() const {
				return m_text_string;
			}
			glm::vec2 Text::Predict_Size_Top_Y(std::wstring p_font, glm::vec2 p_size, std::wstring p_text, bool p_include_last_space) {
				glm::vec2 v_predicted_size{};
				float v_max_height = 0.0f;

				int32_t v_char_y_size{ 0 };
				glm::vec2 v_baseline_size{ 0 };
				int32_t v_char_spacing{ 0 };

				for (size_t i = 0; i < p_text.size(); i++) {
					pw::co::Text_Renderer::Character* v_current_char = pw::co::Text_Renderer::Create_Character(p_text[i], p_font);

					if (v_current_char == nullptr) {
						continue;
					}

					v_char_y_size = TO_INT32(((float)v_current_char->Character_Size().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y);
					v_baseline_size = glm::vec2(
						(((float)v_current_char->Baseline_Offset().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x),
						(((float)v_current_char->Baseline_Offset().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y)
					);
					v_char_spacing = TO_INT32(((float)v_current_char->Spacing() / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);

					if (v_char_y_size > v_max_height) {
						v_max_height = TO_FLOAT(v_char_y_size);
					}

					if (i != p_text.size() - 1 || p_include_last_space == true) {
						v_predicted_size.x = v_predicted_size.x + v_char_spacing;
					}
				}
				v_predicted_size.y = v_max_height;

				return v_predicted_size;
			}
			glm::vec2 Text::Predict_Size_Bottom_Y(std::wstring p_font, glm::vec2 p_size, std::wstring p_text, bool p_include_last_space) {
				glm::vec2 v_predicted_size{};
				float v_lowest_height = 0.0f;

				int32_t v_char_y_size{ 0 };
				glm::vec2 v_baseline_size{ 0 };
				int32_t v_char_spacing{ 0 };

				for (size_t i = 0; i < p_text.size(); i++) {
					pw::co::Text_Renderer::Character* v_current_char = pw::co::Text_Renderer::Create_Character(p_text[i], p_font);

					if (v_current_char == nullptr) {
						continue;
					}

					v_char_y_size = TO_INT32(((float)v_current_char->Character_Size().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y);
					v_baseline_size = glm::vec2(
						(((float)v_current_char->Baseline_Offset().x / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x),
						(((float)v_current_char->Baseline_Offset().y / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.y)
					);
					v_char_spacing = TO_INT32(((float)v_current_char->Spacing() / pw::cm::Constant::PW_FONT_RESOLUTION) * p_size.x);


					float v_t1 = (p_size.y - v_char_y_size);
					float v_t2 = TO_FLOAT(v_char_y_size - v_baseline_size.y);
					if (0.0f - v_t1 - v_t2 < v_lowest_height) {
						v_lowest_height = v_t1 - v_t2;
					}

					if (i != p_text.size() - 1 || p_include_last_space == true) {
						v_predicted_size.x = v_predicted_size.x + v_char_spacing;
					}
				}
				v_predicted_size.y = v_lowest_height;

				return v_predicted_size;
			}
	ST_NAMESPACE_END
PW_NAMESPACE_END