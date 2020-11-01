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
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (IE_Texture)                                ]
	 Handles textures in opengl.
	*/
	class IE_Texture {
/* Default Class Structures */
	public:
		enum class Default_Texture {
			RED, GREEN, BLUE, YELLOW,
			PINK, CYAN, ORANGE, MAGENTA,
			WHITE, BLACK, LIME, DARK_CYAN,
			PURPLE, LIGHT_BLUE, BROWN,
			DARK_GREY, GREY
		};
		IE_Texture();
		IE_Texture(const char* file_location);
		~IE_Texture() {};

	private:
/* Public Functions/Macros  */
	public:
		void Bind(unsigned int unit);
		void Delete();

		static std::string Find_Texture(const char* name);
		static std::string Find_Color_Texture(const char* d_bits, Default_Texture id, glm::vec3& color);

		static void Change_Texture_Dir(const char* new_dir) { has_user_dir_changed = true; user_dir = new_dir; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		GLuint texture_id;

		GLuint texture_width;
		GLuint texture_height;

		GLint texture_bit_depth;

		static bool has_user_dir_changed;
		static const char* user_dir;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_TEXTURE