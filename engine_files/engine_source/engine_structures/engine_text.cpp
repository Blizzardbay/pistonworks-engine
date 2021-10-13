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
				type(type), character_data(), character_size((character_size.x / cm::Engine_Constant::PW_FONT_RESOLUTION) * cm::Engine_Constant::PW_SCALE_FACTOR, (character_size.y / cm::Engine_Constant::PW_FONT_RESOLUTION)* cm::Engine_Constant::PW_SCALE_FACTOR),
				baseline_offset(baseline_offset.x >> 6 , baseline_offset.y >> 6),
				spacing(spacing >> 6) {
			this->character_data = Texture(character_data, TO_32UINT(character_size.x), TO_32UINT(character_size.y), GL_RED, GL_RED);
		}
		Character::Character(wchar_t type, BYTE* character_data, glm::ivec2 character_size, glm::ivec2 baseline_offset, uint32_t spacing) :
				type(type), character_data(),
				character_size( TO_32INT(((float)(character_size.x)) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
							    TO_32INT(((float)(character_size.y)) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)),
				baseline_offset(TO_32INT(((float)(baseline_offset.x)) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
							    TO_32INT((float)(baseline_offset.y)) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR),
				spacing(TO_32INT((float)(spacing >> 6) / cm::Engine_Constant::PW_FONT_RESOLUTION * cm::Engine_Constant::PW_SCALE_FACTOR)) {
			if (character_data == NULL) {
				this->character_data = Texture();
			}
			else {
				this->character_data = Texture(character_data, character_size.x, character_size.y, GL_RED, GL_RED);
			}
		}
		Character::~Character() {
			character_data.Delete();
		}
		wchar_t Character::Type() {
			return type;
		}
		Texture* Character::Character_Data() {
			Texture* copy = new Texture(character_data);
			return copy;
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
		Text::Text(const wchar_t* text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type) :
				text_string(), type(model_type) {
			switch (model_type) {
				case PW_STATIC: {
					for (size_t i = 0; i < wcsnlen_s(text, SIZE_MAX); i++) {
						Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

						glm::vec2 adj_size = glm::vec2((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR, (float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						Static_Model* char_model = new Static_Model(Mesh_Types::SQUARE, current_char->Character_Data(),
							glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
								position.y + ((float)current_char->Baseline_Offset().y * adj_size.y)),
							0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
								((float)current_char->Character_Size().y * adj_size.y)),
							color);

						text_string.push_back(char_model);
						position.x = position.x + TO_32INT((float)current_char->Spacing() * adj_size.x);
					}
					break;
				}
				case PW_DYNAMIC: {
					for (size_t i = 0; i < wcsnlen_s(text, SIZE_MAX); i++) {
						Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

						glm::vec2 adj_size = glm::vec2((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR, (float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						Dynamic_Model* char_model = new Dynamic_Model(Mesh_Types::SQUARE, current_char->Character_Data(),
							glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
								position.y + ((float)current_char->Baseline_Offset().y * adj_size.y)),
							0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
								((float)current_char->Character_Size().y * adj_size.y)),
							color);

						text_string.push_back(char_model);
						position.x = position.x + TO_32INT((float)current_char->Spacing() * adj_size.x);
					}
					break;
				}
				default: {
					break;
				}
			}
		}
		Text::Text(std::wstring text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type) :
				text_string(), type(model_type) {
			switch (model_type) {
				case PW_STATIC: {
					for (size_t i = 0; i < text.size(); i++) {
						Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

						glm::vec2 adj_size = glm::vec2((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR, (float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						Static_Model* char_model = new Static_Model(Mesh_Types::SQUARE, current_char->Character_Data(),
							glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
								position.y + ((float)current_char->Baseline_Offset().y * adj_size.y)),
							0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
								((float)current_char->Character_Size().y * adj_size.y)),
							color);

						text_string.push_back(char_model);
						position.x = position.x + TO_32INT((float)current_char->Spacing() * adj_size.x);
					}
					break;
				}
				case PW_DYNAMIC: {
					for (size_t i = 0; i < text.size(); i++) {
						Character* current_char = Text_Renderer::Create_Character(text[i], font_type);

						glm::vec2 adj_size = glm::vec2((float)size.x / (float)cm::Engine_Constant::PW_SCALE_FACTOR, (float)size.y / (float)cm::Engine_Constant::PW_SCALE_FACTOR);

						Dynamic_Model* char_model = new Dynamic_Model(Mesh_Types::SQUARE, current_char->Character_Data(),
							glm::vec2(position.x + ((float)current_char->Baseline_Offset().x * adj_size.x),
								position.y + ((float)current_char->Baseline_Offset().y * adj_size.y)),
							0.0f, glm::vec2(((float)current_char->Character_Size().x * adj_size.x),
								((float)current_char->Character_Size().y * adj_size.y)),
							color);

						text_string.push_back(char_model);
						position.x = position.x + TO_32INT((float)current_char->Spacing() * adj_size.x);
					}
					break;
				}
				default: {
					break;
				}
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
	// End of Class Members
	// Text_Renderer  
	// Static Declarations
		std::map<PW_FONT_ID, std::map<wchar_t, Character*>> Text_Renderer::font_library;
	// Class Members  
		void Text_Renderer::Load_Engine_Font() {
			FT_Library ft_library;
			PW_FT_CALL(FT_Init_FreeType(&ft_library));
			for (size_t i = 0; i < TO_64UINT(Font::PW_FONT_COUNT); i++) {
				switch (i) {
					case TO_32INT(Font::PW_CAMBRIA): {
						FT_Face cambria;

						PW_FT_CALL(FT_New_Face(ft_library, "engine_files/engine_resource/engine_fonts/cambria_font/Cambria.ttf", 0, &cambria));

						PW_FT_CALL(FT_Set_Pixel_Sizes(cambria, 0, 256));

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

							Character* symbol = new Character(
								(wchar_t)j, cambria->glyph->bitmap.buffer,
								glm::vec2(cambria->glyph->bitmap.width, cambria->glyph->bitmap.rows),
								glm::vec2(cambria->glyph->bitmap_left, cambria->glyph->bitmap_top), cambria->glyph->advance.x);

							if (font_library.count(TO_32INT(Font::PW_CAMBRIA)) < 1) {
								std::map<wchar_t, Character*> map = std::map<wchar_t, Character*>();
								map.insert(std::make_pair((wchar_t)j, symbol));
								font_library.insert(std::make_pair(TO_32INT(Font::PW_CAMBRIA), map));
							}
							else {
								auto it = font_library.at(TO_32INT(Font::PW_CAMBRIA)).count((wchar_t)j);
								if (0 == font_library.at(TO_32INT(Font::PW_CAMBRIA)).count((wchar_t)j)) {
									font_library.at(TO_32INT(Font::PW_CAMBRIA)).insert(std::make_pair((wchar_t)j, symbol));
								}
							}
							symbol = nullptr;
						}
						PW_FT_CALL(FT_Done_Face(cambria));
						break;
					}
					case TO_32INT(Font::PW_ARIAL): {
						FT_Face arial;

						PW_FT_CALL(FT_New_Face(ft_library, "engine_files/engine_resource/engine_fonts/arial_font/arial 1.ttf", 0, &arial));

						PW_FT_CALL(FT_Set_Pixel_Sizes(arial, 0, 256));

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
			
							Character* symbol = new Character(
								(wchar_t)j, arial->glyph->bitmap.buffer,
								glm::vec2(arial->glyph->bitmap.width, arial->glyph->bitmap.rows),
								glm::vec2(arial->glyph->bitmap_left, arial->glyph->bitmap_top), arial->glyph->advance.x);

							if (font_library.count(TO_32INT(Font::PW_ARIAL)) < 1) {
								std::map<wchar_t, Character*> map = std::map<wchar_t, Character*>();
								map.insert(std::make_pair((wchar_t)j, symbol));
								font_library.insert(std::make_pair(TO_32INT(Font::PW_ARIAL), map));
							}
							else {
								auto it = font_library.at(TO_32INT(Font::PW_ARIAL)).count((wchar_t)j);
								if (0 == font_library.at(TO_32INT(Font::PW_ARIAL)).count((wchar_t)j)) {
									font_library.at(TO_32INT(Font::PW_ARIAL)).insert(std::make_pair((wchar_t)j, symbol));
								}
							}
							symbol = nullptr;
						}
						PW_FT_CALL(FT_Done_Face(arial));
						break;
					}
					case TO_32INT(Font::PW_ROBOTO): {
						FT_Face roboto;

						PW_FT_CALL(FT_New_Face(ft_library, "engine_files/engine_resource/engine_fonts/roboto_font/Roboto-Regular.ttf", 0, &roboto));

						PW_FT_CALL(FT_Set_Pixel_Sizes(roboto, 0, 256));

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

							Character* symbol = new Character(
								(wchar_t)j, roboto->glyph->bitmap.buffer,
								glm::vec2(roboto->glyph->bitmap.width, roboto->glyph->bitmap.rows),
								glm::vec2(roboto->glyph->bitmap_left, roboto->glyph->bitmap_top), roboto->glyph->advance.x);

							if (font_library.count(TO_32INT(Font::PW_ROBOTO)) < 1) {
								std::map<wchar_t, Character*> map = std::map<wchar_t, Character*>();
								map.insert(std::make_pair((wchar_t)j, symbol));
								font_library.insert(std::make_pair(TO_32INT(Font::PW_ROBOTO), map));
							}
							else {
								auto it = font_library.at(TO_32INT(Font::PW_ROBOTO)).count((wchar_t)j);
								if (0 == font_library.at(TO_32INT(Font::PW_ROBOTO)).count((wchar_t)j)) {
									font_library.at(TO_32INT(Font::PW_ROBOTO)).insert(std::make_pair((wchar_t)j, symbol));
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
		Character* Text_Renderer::Create_Character(wchar_t letter_type, Font font_type) {
			switch (TO_32INT(font_type)) {
				case TO_32INT(Font::PW_CAMBRIA): {
					auto it = font_library.at(TO_32INT(Font::PW_CAMBRIA)).count(letter_type);
					if (it > 0) {
						return font_library.at(TO_32INT(Font::PW_CAMBRIA)).at(letter_type);
					} 
					break;
				}
				case TO_32INT(Font::PW_ARIAL): {
					auto it = font_library.at(TO_32INT(Font::PW_ARIAL)).count(letter_type);
					if (it > 0) {
						return font_library.at(TO_32INT(Font::PW_ARIAL)).at(letter_type);
					}
					break;
				}
				case TO_32INT(Font::PW_ROBOTO): {
					auto it = font_library.at(TO_32INT(Font::PW_ROBOTO)).count(letter_type);
					if (it > 0) {
						return font_library.at(TO_32INT(Font::PW_ROBOTO)).at(letter_type);
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