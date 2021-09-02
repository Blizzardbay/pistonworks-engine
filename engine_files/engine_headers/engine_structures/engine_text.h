#ifndef H_IE_TEXT
#define H_IE_TEXT
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
#include "ie_model.h"
//////////////////////////////////
// Engine Macro Includes  
#include "engine_headers\engine_error.h"
//////////////////////////////////
// Engine Macros    
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Internal Engine              //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		class PW_INTERNAL_API Text_Renderer;
		//////////////////////////////////
		// Class Name: pw::ie::Font
		//
		// Purpose: Handles loading of text within the engine.
		//
		enum class Font {
			PW_CAMBRIA,
			PW_ARIAL,
			PW_ROBOTO,
			PW_FONT_COUNT
		};
		//////////////////////////////////
		// Class Name: pw::ie::Character
		//
		// Purpose: Holds character texture information.
		//
		class PW_INTERNAL_API Character {
		// Default Class Structures
		public:
			// Function: Character::Character
			//
			// Purpose: Creates a character object that holds the character texture data
			//  and the character it represents.
			//
			Character(PW_CHAR type, PW_SRD_PTR(PW_BYTE*) character_data, glm::ivec2 character_size, PW_UINT texture_depth, glm::ivec2 baseline_offset, PW_UINT spacing);
			// Function: Character::Character
			//
			// Purpose: Creates a character object that holds the character texture data
			//  and the character it represents.
			//
			Character(PW_CHAR type, PW_BYTE* character_data, glm::ivec2 character_size, PW_UINT texture_depth, glm::ivec2 baseline_offset, PW_UINT spacing);
			// Function: Character::~Character
			//
			// Purpose: Cleans up character data, does not delete allocated memory of character data.
			//
			~Character();
		private:
		// Public Functions/Macros
		public:
		// Public Variables   
		public:
			// Function: Character::Type
			//
			// Purpose: Returns the character it represents.
			//
			PW_CHAR Type();
			// Function: Character::Character_Data
			//
			// Purpose: Returns the texture data of the character.
			//
			Texture* Character_Data();
			// Function: Character::Character_Size
			//
			// Purpose: Returns the size of a character.
			//
			glm::ivec2 Character_Size();
			// Function: Character::Baseline_Offset
			//
			// Purpose: Returns the offset from the baseline of a character.
			//
			glm::ivec2 Baseline_Offset();
			// Function: Character::Spacing
			//
			// Purpose: Returns the texture data of the character.
			//
			PW_UINT Spacing();
			// Function: Character::Set_Type
			//
			// Purpose: Sets the character representation to another character.
			//
			PW_VOID Set_Type(PW_CHAR type);
			// Function: Character::Set_Texture
			//
			// Purpose: Sets the current texture to a new one.
			//
			PW_VOID Set_Texture(Texture& new_texture);
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			PW_CHAR type;
			Texture character_data;
			glm::ivec2 character_size;
			glm::ivec2 baseline_offset;
			PW_UINT spacing;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Character
		//
		// Purpose: Holds character texture information.
		//
		class PW_INTERNAL_API Text {
			// Default Class Structures
		public:
			// Function: Text::Text
			//
			// Purpose: Creates a vector of character objects to be drawn as a line of text.
			//
			Text(PW_CSTRING text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type);
			// Function: Text::Text
			//
			// Purpose: Creates a vector of character objects to be drawn as a line of text.
			//
			Text(PW_STRING text, glm::ivec2 position, glm::ivec2 size, glm::vec4 color, PW_MODEL_TYPE model_type, Font font_type);
			// Function: Text::~Text
			//
			// Purpose: Cleans up text data.
			//
			~Text();
		private:
			// Public Functions/Macros
		public:
			// Public Variables   
		public:
			// Function: Text::Render
			//
			// Purpose: Renders the line of text.
			//
			PW_VOID Render();
			// Function: Text::Delete
			//
			// Purpose: Deletes the line of text.
			//
			PW_VOID Delete();
			// Private Functions/Macros 
		private:
			// Private Variables  
		private:
			std::vector<Model*> text_string;
			PW_MODEL_TYPE type;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Text_Renderer
		//
		// Purpose: Handles loading of text within the engine.
		//
		class PW_INTERNAL_API Text_Renderer {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// Function: Text_Renderer::Load_Engine_Font
			//
			// Purpose: Loads the engine font that are built in.
			//
			static PW_VOID Load_Engine_Font();
			// Function: Text_Renderer::Render_Text
			//
			// Purpose: Creates a character form a font stash and returns it to the user.
			//
			static Character* Create_Character(PW_CHAR letter_type, Font font_type);
		// Public Variables   
		public:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			static std::map<PW_FONT_ID, std::map<PW_CHAR, Character*>> font_library;
		};
		// Functions  
		// Macros / Definitions
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_TEXT