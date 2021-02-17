#ifndef H_IE_TEXTURE
#define H_IE_TEXTURE

//(DUAL_FILE)

/* C++ Headers              */
#include <cassert>
/* Project Headers          */
#include <glm\glm.hpp>
#include <stb_image.h>
/* Engine Headers           */
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
	/* Classes                  */
	//
		/* -Texture
		 Handles textures in opengl.
		*/
		class Texture {
	/* Default Class Structures */
		public:
			enum class Default_Texture {
				RED, GREEN, BLUE, YELLOW,
				PINK, CYAN, ORANGE, MAGENTA,
				WHITE, BLACK, LIME, DARK_CYAN,
				PURPLE, LIGHT_BLUE, BROWN,
				DARK_GREY, GREY, Color_Count
			};
			Texture();
			Texture(PW_CSTRING file_location);
			~Texture() {};

		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Bind(PW_UINT unit);
			PW_VOID Delete();

			static PW_STRING Find_Texture(PW_CSTRING name);
			static PW_STRING Find_Color_Texture(PW_CSTRING d_bits, Default_Texture id, glm::vec3& color);

			static PW_VOID Change_Texture_Dir(PW_CSTRING new_dir) { has_user_dir_changed = true; user_dir = new_dir; }

			static glm::vec3 Color(Default_Texture color_id) { return Engine_Colors[(PW_UINT)color_id]; }
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			PW_UINT texture_id;

			PW_UINT texture_width;
			PW_UINT texture_height;

			PW_INT texture_bit_depth;

			static PW_BOOL has_user_dir_changed;
			static PW_CSTRING user_dir;

			static glm::vec3 Engine_Colors[(PW_UINT)Default_Texture::Color_Count];
		};
		/* -Icon
		 Handles icons in opengl.
		*/
		class Icon {
	/* Default Class Structures */
		public:
			Icon();
			Icon(PW_CSTRING file_location);
			~Icon() {};

		private:
	/* Public Functions/Macros  */
		public:
			PW_VOID Delete();

			static PW_STRING Find_Icon(PW_CSTRING name);

			static PW_VOID Change_Icon_Dir(PW_CSTRING new_dir) { has_user_dir_changed = true; user_dir = new_dir; }

			PW_BYTE* Data() { return icon_data; }

			PW_UINT Width() { return icon_width; }
			PW_UINT Height() { return icon_height; }
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			PW_UINT icon_width;
			PW_UINT icon_height;

			PW_INT icon_bit_depth;

			PW_BYTE* icon_data;

			static PW_BOOL has_user_dir_changed;
			static PW_CSTRING user_dir;
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_TEXTURE