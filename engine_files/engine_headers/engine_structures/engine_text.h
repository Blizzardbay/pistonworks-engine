// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
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
#ifndef H_ENGINE_TEXT
#define H_ENGINE_TEXT
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <map>
#include <algorithm>
#include <cstring>
#include <cmath>
//////////////////////////////////
// Project Headers 
#include <glm\glm.hpp>
//////////////////////////////////
// Engine Headers
#include "engine_structures\engine_model.h"
//////////////////////////////////
// Engine Macro Includes  
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Macros    
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		class PW_STRUCTURES_API Text_Renderer;
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Enum: pw::st::Font
		// //////////////////////////////////////////////////
		// Purpose:
		//  Handles loading of text within the engine.
		// //////////////////////////////////////////////////
		enum class Font {
			PW_CAMBRIA,
			PW_ARIAL,
			PW_ROBOTO,
			PW_FONT_COUNT
		};
		// //////////////////////////////////////////////////
		// INTERNAL_DATA_API Class Name: pw::st::Character
		// //////////////////////////////////////////////////
		// Purpose:
		//  Holds character texture information.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Character {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Character::Character
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a character object that holds the
			//  character texture data and the character it
			//  represents.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) wchar_t type;
			// Purpose: 
			//  The type of character.
			// (2) PW_SRD_PTR(BYTE*) character_data;
			// Purpose: 
			//  The font data / texture data of the character.
			// (3) glm::ivec2 character_size;
			// Purpose: 
			//  The size of the character.
			// (4) glm::ivec2 baseline_offset;
			// Purpose: 
			//  The position that the character would be in.
			// (5) uint32_t spacing;
			// Purpose: 
			//  The space between two characters.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Character(wchar_t type, PW_SRD_PTR(BYTE*) character_data, glm::ivec2 character_size, glm::ivec2 baseline_offset, uint32_t spacing);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Character::Character
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a character object that holds the
			//  character texture data and the character it
			//  represents.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) wchar_t type;
			// Purpose: 
			//  The type of character.
			// (2) BYTE* character_data;
			// Purpose: 
			//  The font data / texture data of the character.
			// (3) glm::ivec2 character_size;
			// Purpose: 
			//  The size of the character.
			// (4) glm::ivec2 baseline_offset;
			// Purpose: 
			//  The position that the character would be in.
			// (5) uint32_t spacing;
			// Purpose: 
			//  The space between two characters.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Character(wchar_t type, BYTE* character_data, glm::ivec2 character_size, glm::ivec2 baseline_offset, uint32_t spacing);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Character::~Character
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Cleans up character data, does not delete
			//  allocated memory of character data.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Character();
		private:
		// Public Functions/Macros
		public:
		// Public Variables   
		public:
			// Accessors
			USER_INTERACTION
			ACCESSOR wchar_t Type();
			USER_INTERACTION
			ACCESSOR st::Texture* Character_Data();
			USER_INTERACTION
			ACCESSOR glm::ivec2 Character_Size();
			USER_INTERACTION
			ACCESSOR glm::ivec2 Baseline_Offset();
			USER_INTERACTION
			ACCESSOR uint32_t Spacing();
			// Mutators
			USER_INTERACTION
			MUTATOR void Set_Type(wchar_t type);
			USER_INTERACTION
			MUTATOR void Set_Texture(st::Texture& new_texture);
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			wchar_t type;
			st::Texture character_data;
			glm::ivec2 character_size;
			glm::ivec2 baseline_offset;
			uint32_t spacing;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Text
		// //////////////////////////////////////////////////
		// Purpose: 
		//  Holds a vector of characters.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Text {
			// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Text::Text
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a vector of character objects to be drawn
			//  as a line of text.
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) const wchar_t* text;
			// Purpose: 
			//  The text to be drawn to the screen.
			// (2) glm::ivec2 position;
			// Purpose: 
			//  The position of the left most character.
			// (3) glm::ivec2 size;
			// Purpose: 
			//  The size of the character string.
			// (4) glm::vec4 color;
			// Purpose: 
			//  The color of the text.
			// (5) PW_MODEL_TYPE model_type;
			// Purpose: 
			//  The type of model you want to use for the text.
			// (6) Font font_type;
			// Purpose: 
			//  The type of loaded engine font to use.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Text(const wchar_t* text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Text::Text
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a vector of character objects to be drawn
			//  as a line of text.
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) std::wstring text;
			// Purpose: 
			//  The text to be drawn to the screen.
			// (2) glm::ivec2 position;
			// Purpose: 
			//  The position of the left most character.
			// (3) glm::ivec2 size;
			// Purpose: 
			//  The size of the character string.
			// (4) glm::vec4 color;
			// Purpose: 
			//  The color of the text.
			// (5) PW_MODEL_TYPE model_type;
			// Purpose: 
			//  The type of model you want to use for the text.
			// (6) Font font_type;
			// Purpose: 
			//  The type of loaded engine font to use.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Text(std::wstring text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Text::~Text
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Cleans up text data.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Text();
		private:
			// Public Functions/Macros
		public:
			// Public Variables   
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Text::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Renders the line of text.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Text::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes the line of text.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// Private Functions/Macros 
		private:
			// Private Variables  
		private:
			std::vector<Model*> text_string;
			PW_MODEL_TYPE type;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::ie::Text_Renderer
		// //////////////////////////////////////////////////
		// Purpose:
		//  Handles loading of text within the engine.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Text_Renderer {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Text_Renderer::Load_Engine_Font
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads the engine font that are built in.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Load_Engine_Font();
			// //////////////////////////////////////////////////
			// CORE Function: Text_Renderer::Create_Character
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a character from a font and returns
			//  it to the user.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) wchar_t letter_type;
			// Purpose: 
			//  The character to be created.
			// (2) Font font_type;
			// Purpose: 
			//  The type of loaded engine font to use.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static CORE Character* Create_Character(wchar_t letter_type, Font font_type);
		// Public Variables   
		public:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			static std::map<PW_FONT_ID, std::map<wchar_t, Character*>> font_library;
		};
		// Functions  
		// Macros / Definitions
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_TEXT