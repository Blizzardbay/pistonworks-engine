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
		Character::Character(wchar_t type, PW_SRD_PTR(BYTE*) character_data, glm::ivec2 character_size, glm::ivec2 baseline_offset, uint32_t spacing) :
				type(type), character_data(),
				character_size( TO_INT32((float)(character_size.x) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
								TO_INT32((float)(character_size.y) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)),
				baseline_offset(TO_INT32((float)(baseline_offset.x) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
								TO_INT32((float)(baseline_offset.y) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)),
				spacing(TO_INT32((float)(spacing / 64) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)) {
			try {
				if (character_data == NULL) {
					this->character_data = Texture();
				}
				else {
					this->character_data = Texture(character_data, character_size.x, character_size.y, GL_RED, GL_RED);
				}
			}
			catch (const er::Warning_Error& v_error) {
				throw v_error;
			}
		}
		Character::Character(wchar_t type, BYTE* character_data, glm::ivec2 character_size, glm::ivec2 baseline_offset, uint32_t spacing) :
				type(type), character_data(),
				character_size( TO_INT32((float)(character_size.x) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
							    TO_INT32((float)(character_size.y) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)),
				baseline_offset(TO_INT32((float)(baseline_offset.x) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
							    TO_INT32((float)(baseline_offset.y) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)),
				spacing(TO_INT32((float)(spacing / 64) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)) {
			try {
				if (character_data == NULL) {
					this->character_data = Texture();
				}
				else {
					this->character_data = Texture(character_data, character_size.x, character_size.y, GL_RED, GL_RED);
				}
			}
			catch (const er::Warning_Error& v_error) {
				throw v_error;
			}
		}
		Character::~Character() {
			character_data.Delete();
		}
		wchar_t Character::Type() {
			return type;
		}
		Texture* Character::Character_Data() {
			try {
				Texture* copy = pw::Engine_Memory::Allocate<st::Texture>(std::move(character_data));
				return copy;
			}
			catch (const er::Severe_Error& v_error) {
				throw v_error;
			}
		}
		glm::ivec2 Character::Character_Size() {
			return character_size;
		}
		glm::ivec2 Character::Baseline_Offset() {
			return baseline_offset;
		}
		uint32_t Character::Spacing() {
			return spacing;
		}
		void Character::Set_Texture(Texture& new_texture) {
			character_data = new_texture;
		}
		void Character::Set_Type(wchar_t type) {
			this->type = type;
		}
	// End of Class Members
	// Text
	// Static Declarations
	// Class Members
		Text::Text() :
				text_string(), text_position(glm::vec2(0.0f, 0.0f)), text_size(glm::vec2(0.0f, 0.0f)), type(0) {
		}
		Text::Text(const wchar_t* text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type) :
				text_string(), text_position(position), text_size(glm::vec2(0.0f, 0.0f)), type(model_type) {
			try {
				switch (model_type) {
					case PW_STATIC: {
						Character* height_char = Text_Renderer::Create_Character(L'E', font_type);

						float ratio_off = 1 / (height_char->Character_Size().y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						for (size_t i = 0; i < wcsnlen_s(text, SIZE_MAX); i++) {
							Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

							glm::vec2 adj_size = glm::vec2(((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off, ((float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off);

							Static_Model* char_model = pw::Engine_Memory::Allocate<Static_Model, bool>(Mesh_Types::SQUARE, current_char->Character_Data(),
								glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
									position.y - (size.y - ((float)current_char->Baseline_Offset().y * adj_size.y))),
								0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
									((float)current_char->Character_Size().y * adj_size.y)),
								color);

							text_string.push_back(char_model);
							position.x = position.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
							text_size.x = text_size.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
						}
						break;
					}
					case PW_DYNAMIC: {
						Character* height_char = Text_Renderer::Create_Character(L'E', font_type);

						float ratio_off = 1 / (height_char->Character_Size().y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						for (size_t i = 0; i < wcsnlen_s(text, SIZE_MAX); i++) {
							Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

							glm::vec2 adj_size = glm::vec2(((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off, ((float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off);

							Dynamic_Model* char_model = pw::Engine_Memory::Allocate<Dynamic_Model, bool>(Mesh_Types::SQUARE, current_char->Character_Data(),
								glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
									position.y - (size.y - ((float)current_char->Baseline_Offset().y * adj_size.y))),
								0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
									((float)current_char->Character_Size().y * adj_size.y)),
								color);

							text_string.push_back(char_model);
							position.x = position.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
							text_size.x = text_size.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
						}
						break;
					}
					default: {
						break;
					}
				}
			}
			catch (const er::Severe_Error& v_error) {
				throw v_error;
			}
			catch (const er::Warning_Error& v_error) {
				throw v_error;
			}
		}
		Text::Text(std::wstring text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type) :
				text_string(), text_position(position), text_size(glm::vec2(0.0f, 0.0f)), type(model_type) {
			try {
				switch (model_type) {
					case PW_STATIC: {
						Character* height_char = Text_Renderer::Create_Character(L'E', font_type);

						float ratio_off = 1 / (height_char->Character_Size().y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						for (size_t i = 0; i < text.size(); i++) {
							Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

							glm::vec2 adj_size = glm::vec2(((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off, ((float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off);

							Static_Model* char_model = pw::Engine_Memory::Allocate<Static_Model, bool>(Mesh_Types::SQUARE, current_char->Character_Data(),
								glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
									position.y - (size.y - ((float)current_char->Baseline_Offset().y * adj_size.y))),
								0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
									((float)current_char->Character_Size().y * adj_size.y)),
								color);

							text_string.push_back(char_model);
							position.x = position.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
							text_size.x = text_size.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
						}
						break;
					}
					case PW_DYNAMIC: {
						Character* height_char = Text_Renderer::Create_Character(L'E', font_type);

						float ratio_off = 1 / (height_char->Character_Size().y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						for (size_t i = 0; i < text.size(); i++) {
							Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

							glm::vec2 adj_size = glm::vec2(((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off, ((float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR) * ratio_off);

							Dynamic_Model* char_model = pw::Engine_Memory::Allocate<Dynamic_Model, bool>(Mesh_Types::SQUARE, current_char->Character_Data(),
								glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
									position.y - (size.y - ((float)current_char->Baseline_Offset().y * adj_size.y))),
								0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
									((float)current_char->Character_Size().y * adj_size.y)),
								color);

							text_string.push_back(char_model);
							position.x = position.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
							text_size.x = text_size.x + TO_INT32((float)current_char->Spacing() * adj_size.x);
						}
						break;
					}
					default: {
						break;
					}
				}
			}
			catch (const er::Severe_Error& v_error) {
				throw v_error;
			}
			catch (const er::Warning_Error& v_error) {
				throw v_error;
			}
		}
		Text::~Text() {
		}
		void Text::Render() {
			switch (type) {
				case PW_STATIC: {
					for (size_t i = 0; i < text_string.size(); i++) {
						static_cast<Static_Model*>(text_string.at(i))->Render();
					}
					break;
				}
				case PW_DYNAMIC: {
					for (size_t i = 0; i < text_string.size(); i++) {
						static_cast<Dynamic_Model*>(text_string.at(i))->Render();
					}
					break;
				}
				default: {
					break;
				}
			}
		}
		void Text::Delete() {
			switch (type) {
				case PW_STATIC: {
					for (size_t i = 0; i < text_string.size(); i++) {
						static_cast<Static_Model*>(text_string.at(i))->Delete();
					}
					break;
				}
				case PW_DYNAMIC: {
					for (size_t i = 0; i < text_string.size(); i++) {
						static_cast<Dynamic_Model*>(text_string.at(i))->Delete();
					}
					break;
				}
				default: {
					break;
				}
			}
		}
		void Text::Refresh() {
			switch (type) {
				case PW_STATIC: {
					for (size_t i = 0; i < text_string.size(); i++) {
						static_cast<Static_Model*>(text_string.at(i))->Refresh_Model();
					}
					break;
				}
				case PW_DYNAMIC: {
					for (size_t i = 0; i < text_string.size(); i++) {
						static_cast<Dynamic_Model*>(text_string.at(i))->Refresh_Model();
					}
					break;
				}
				default: {
					break;
				}
			}
		}
		void Text::Set_Position(const glm::vec2&& p_new_position) {
			if (text_position != p_new_position) {
				switch (type) {
					case PW_DYNAMIC: {
						float v_difference_x = p_new_position.x - text_position.x;
						float v_difference_y = p_new_position.y - text_position.y;
						for (size_t i = 0; i < text_string.size(); i++) {
							static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().x = static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().x + v_difference_x;
							static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().y = static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().y + v_difference_y;
						}
						break;
					}
					default: {
						break;
					}
				}
				text_position = p_new_position;
			}
		}
		void Text::Set_Position(const glm::vec2& p_new_position) {
			if (text_position != p_new_position) {
				switch (type) {
					case PW_DYNAMIC: {
						float v_difference_x = p_new_position.x - text_position.x;
						float v_difference_y = p_new_position.y - text_position.y;
						for (size_t i = 0; i < text_string.size(); i++) {
							static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().x = static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().x + v_difference_x;
							static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().y = static_cast<Dynamic_Model*>(text_string.at(i))->Position_Reference().y + v_difference_y;
						}
						break;
					}
					default: {
						break;
					}
				}
				text_position = p_new_position;
			}
		}
		glm::vec2& Text::Position_Reference() {
			return text_position;
		}
		const glm::vec2& Text::Position() {
			return text_position;
		}
		const glm::vec2& Text::Size() {
			return text_size;
		}
		const uint64_t Text::Count() {
			return text_string.size();
		}
	// End of Class Members
	// Text_Renderer  
	// Static Declarations
		std::map<PW_FONT_ID, std::map<wchar_t, Character*>> Text_Renderer::font_library;
	// Class Members  
		void Text_Renderer::Load_Engine_Font() {
			try {
				FT_Library ft_library;
				PW_FT_CALL(FT_Init_FreeType(&ft_library));
				for (size_t i = 0; i < TO_UINT64(Font::PW_FONT_COUNT); i++) {
					switch (i) {
						case TO_INT32(Font::PW_CAMBRIA): {
							FT_Face cambria;

							PW_FT_CALL(FT_New_Face(ft_library, "engine_files/engine_resource/engine_fonts/cambria_font/Cambria.ttf", 0, &cambria));

							PW_FT_CALL(FT_Set_Pixel_Sizes(cambria, 0, cm::Engine_Constant::PW_FONT_RESOLUTION));

							for (BYTE j = 0; j < 128; j++) {
								PW_FT_CALL(FT_Load_Char(cambria, j, FT_LOAD_RENDER));

								// Images are not flipped when loaded, so they need to be formated.
								// Flip across the horizontal axis{
								if (cambria->glyph->bitmap.rows % 2 == 0) {
									for (size_t k = 0; k < (cambria->glyph->bitmap.rows) / 2; k++) {
										for (size_t o = 0; o < cambria->glyph->bitmap.width; o++) {
											BYTE ch = cambria->glyph->bitmap.buffer[(k * cambria->glyph->bitmap.width) + o];
											cambria->glyph->bitmap.buffer[(k * cambria->glyph->bitmap.width) + o] =
												cambria->glyph->bitmap.buffer[((cambria->glyph->bitmap.rows - 1 - k) * cambria->glyph->bitmap.width) + o];
											cambria->glyph->bitmap.buffer[((cambria->glyph->bitmap.rows - 1 - k) * cambria->glyph->bitmap.width) + o] = ch;
										}
									}
								}
								else {
									for (size_t k = 0; k < (cambria->glyph->bitmap.rows - 1) / 2; k++) {
										for (size_t o = 0; o < cambria->glyph->bitmap.width; o++) {
											BYTE ch = cambria->glyph->bitmap.buffer[(k * cambria->glyph->bitmap.width) + o];
											cambria->glyph->bitmap.buffer[(k * cambria->glyph->bitmap.width) + o] =
												cambria->glyph->bitmap.buffer[((cambria->glyph->bitmap.rows - 1 - k) * cambria->glyph->bitmap.width) + o];
											cambria->glyph->bitmap.buffer[((cambria->glyph->bitmap.rows - 1 - k) * cambria->glyph->bitmap.width) + o] = ch;
										}
									}
								}

								Character* symbol = pw::Engine_Memory::Allocate<Character, bool>(
									(wchar_t)j, cambria->glyph->bitmap.buffer,
									glm::vec2(cambria->glyph->bitmap.width, cambria->glyph->bitmap.rows),
									glm::vec2(cambria->glyph->bitmap_left, cambria->glyph->bitmap_top), cambria->glyph->advance.x);

								if (font_library.count(TO_INT32(Font::PW_CAMBRIA)) < 1) {
									std::map<wchar_t, Character*> map = std::map<wchar_t, Character*>();
									map.insert(std::make_pair((wchar_t)j, symbol));
									font_library.insert(std::make_pair(TO_INT32(Font::PW_CAMBRIA), map));
								}
								else {
									auto it = font_library.at(TO_INT32(Font::PW_CAMBRIA)).count((wchar_t)j);
									if (0 == font_library.at(TO_INT32(Font::PW_CAMBRIA)).count((wchar_t)j)) {
										font_library.at(TO_INT32(Font::PW_CAMBRIA)).insert(std::make_pair((wchar_t)j, symbol));
									}
								}
								symbol = nullptr;
							}
							PW_FT_CALL(FT_Done_Face(cambria));
							break;
						}
						case TO_INT32(Font::PW_ARIAL): {
							FT_Face arial;

							PW_FT_CALL(FT_New_Face(ft_library, "engine_files/engine_resource/engine_fonts/arial_font/arial 1.ttf", 0, &arial));

							PW_FT_CALL(FT_Set_Pixel_Sizes(arial, 0, cm::Engine_Constant::PW_FONT_RESOLUTION));

							for (BYTE j = 0; j < 128; j++) {
								PW_FT_CALL(FT_Load_Char(arial, j, FT_LOAD_RENDER));

								// Images are not flipped when loaded, so they need to be formated.
								if (arial->glyph->bitmap.rows % 2 == 0) {
									for (size_t k = 0; k < (arial->glyph->bitmap.rows) / 2; k++) {
										for (size_t o = 0; o < arial->glyph->bitmap.width; o++) {
											BYTE ch = arial->glyph->bitmap.buffer[(k * arial->glyph->bitmap.width) + o];
											arial->glyph->bitmap.buffer[(k * arial->glyph->bitmap.width) + o] =
												arial->glyph->bitmap.buffer[((arial->glyph->bitmap.rows - 1 - k) * arial->glyph->bitmap.width) + o];
											arial->glyph->bitmap.buffer[((arial->glyph->bitmap.rows - 1 - k) * arial->glyph->bitmap.width) + o] = ch;
										}
									}
								}
								else {
									for (size_t k = 0; k < (arial->glyph->bitmap.rows - 1) / 2; k++) {
										for (size_t o = 0; o < arial->glyph->bitmap.width; o++) {
											BYTE ch = arial->glyph->bitmap.buffer[(k * arial->glyph->bitmap.width) + o];
											arial->glyph->bitmap.buffer[(k * arial->glyph->bitmap.width) + o] =
												arial->glyph->bitmap.buffer[((arial->glyph->bitmap.rows - 1 - k) * arial->glyph->bitmap.width) + o];
											arial->glyph->bitmap.buffer[((arial->glyph->bitmap.rows - 1 - k) * arial->glyph->bitmap.width) + o] = ch;
										}
									}
								}

								Character* symbol = pw::Engine_Memory::Allocate<Character, bool>(
									(wchar_t)j, arial->glyph->bitmap.buffer,
									glm::vec2(arial->glyph->bitmap.width, arial->glyph->bitmap.rows),
									glm::vec2(arial->glyph->bitmap_left, arial->glyph->bitmap_top), arial->glyph->advance.x);

								if (font_library.count(TO_INT32(Font::PW_ARIAL)) < 1) {
									std::map<wchar_t, Character*> map = std::map<wchar_t, Character*>();
									map.insert(std::make_pair((wchar_t)j, symbol));
									font_library.insert(std::make_pair(TO_INT32(Font::PW_ARIAL), map));
								}
								else {
									auto it = font_library.at(TO_INT32(Font::PW_ARIAL)).count((wchar_t)j);
									if (0 == font_library.at(TO_INT32(Font::PW_ARIAL)).count((wchar_t)j)) {
										font_library.at(TO_INT32(Font::PW_ARIAL)).insert(std::make_pair((wchar_t)j, symbol));
									}
								}
								symbol = nullptr;
							}
							PW_FT_CALL(FT_Done_Face(arial));
							break;
						}
						case TO_INT32(Font::PW_ROBOTO): {
							FT_Face roboto;

							PW_FT_CALL(FT_New_Face(ft_library, "engine_files/engine_resource/engine_fonts/roboto_font/Roboto-Regular.ttf", 0, &roboto));

							PW_FT_CALL(FT_Set_Pixel_Sizes(roboto, 0, cm::Engine_Constant::PW_FONT_RESOLUTION));

							for (BYTE j = 0; j < 128; j++) {
								PW_FT_CALL(FT_Load_Char(roboto, j, FT_LOAD_RENDER));

								// Images are not flipped when loaded, so they need to be formated.
								if (roboto->glyph->bitmap.rows % 2 == 0) {
									for (size_t k = 0; k < (roboto->glyph->bitmap.rows) / 2; k++) {
										for (size_t o = 0; o < roboto->glyph->bitmap.width; o++) {
											BYTE ch = roboto->glyph->bitmap.buffer[(k * roboto->glyph->bitmap.width) + o];
											roboto->glyph->bitmap.buffer[(k * roboto->glyph->bitmap.width) + o] =
												roboto->glyph->bitmap.buffer[((roboto->glyph->bitmap.rows - 1 - k) * roboto->glyph->bitmap.width) + o];
											roboto->glyph->bitmap.buffer[((roboto->glyph->bitmap.rows - 1 - k) * roboto->glyph->bitmap.width) + o] = ch;
										}
									}
								}
								else {
									for (size_t k = 0; k < (roboto->glyph->bitmap.rows - 1) / 2; k++) {
										for (size_t o = 0; o < roboto->glyph->bitmap.width; o++) {
											BYTE ch = roboto->glyph->bitmap.buffer[(k * roboto->glyph->bitmap.width) + o];
											roboto->glyph->bitmap.buffer[(k * roboto->glyph->bitmap.width) + o] =
												roboto->glyph->bitmap.buffer[((roboto->glyph->bitmap.rows - 1 - k) * roboto->glyph->bitmap.width) + o];
											roboto->glyph->bitmap.buffer[((roboto->glyph->bitmap.rows - 1 - k) * roboto->glyph->bitmap.width) + o] = ch;
										}
									}
								}

								Character* symbol = pw::Engine_Memory::Allocate<Character, bool>(
									(wchar_t)j, roboto->glyph->bitmap.buffer,
									glm::vec2(roboto->glyph->bitmap.width, roboto->glyph->bitmap.rows),
									glm::vec2(roboto->glyph->bitmap_left, roboto->glyph->bitmap_top), roboto->glyph->advance.x);

								if (font_library.count(TO_INT32(Font::PW_ROBOTO)) < 1) {
									std::map<wchar_t, Character*> map = std::map<wchar_t, Character*>();
									map.insert(std::make_pair((wchar_t)j, symbol));
									font_library.insert(std::make_pair(TO_INT32(Font::PW_ROBOTO), map));
								}
								else {
									auto it = font_library.at(TO_INT32(Font::PW_ROBOTO)).count((wchar_t)j);
									if (0 == font_library.at(TO_INT32(Font::PW_ROBOTO)).count((wchar_t)j)) {
										font_library.at(TO_INT32(Font::PW_ROBOTO)).insert(std::make_pair((wchar_t)j, symbol));
									}
								}
								symbol = nullptr;
							}
							PW_FT_CALL(FT_Done_Face(roboto));
							break;
						}
						default: {
							break;
						}
					}
				}
				PW_FT_CALL(FT_Done_FreeType(ft_library));
			}
			catch (const er::Severe_Error& v_error) {
				throw v_error;
			}
			catch (const er::Warning_Error& v_error) {
				throw v_error;
			}
		}
		void Text_Renderer::Delete_Engine_Font() {
			for (auto i = font_library.begin(); i != font_library.end(); i++) {
				for (auto j = i->second.begin(); j != i->second.end(); j++) {
					j->second->~Character();

					pw::Engine_Memory::Deallocate<Character>(j->second);
				}
			}
		}
		Character* Text_Renderer::Create_Character(wchar_t letter_type, Font font_type) {
			switch (TO_INT32(font_type)) {
				case TO_INT32(Font::PW_CAMBRIA): {
					auto it = font_library.at(TO_INT32(Font::PW_CAMBRIA)).count(letter_type);
					if (it > 0) {
						return font_library.at(TO_INT32(Font::PW_CAMBRIA)).at(letter_type);
					} 
					break;
				}
				case TO_INT32(Font::PW_ARIAL): {
					auto it = font_library.at(TO_INT32(Font::PW_ARIAL)).count(letter_type);
					if (it > 0) {
						return font_library.at(TO_INT32(Font::PW_ARIAL)).at(letter_type);
					}
					break;
				}
				case TO_INT32(Font::PW_ROBOTO): {
					auto it = font_library.at(TO_INT32(Font::PW_ROBOTO)).count(letter_type);
					if (it > 0) {
						return font_library.at(TO_INT32(Font::PW_ROBOTO)).at(letter_type);
					}
					break;
				}
				default: {
					return nullptr;
					break;
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