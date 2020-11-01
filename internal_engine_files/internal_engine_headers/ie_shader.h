#ifndef H_IE_SHADER
#define H_IE_SHADER

//(DUAL_FILE)

/* C++ Headers              */
#include <fstream>
#include <stdio.h>
/* Project Headers          */
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
/* Engine Headers           */
#include "ie_camera.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (IE_Shader)                                 ]
	 A class for handling the shaders in opengl.
	*/
	class IE_Shader {
/* Default Class Structures */
	public:
		IE_Shader();
		~IE_Shader();
	private:
/* Public Functions/Macros  */
	public:
		void Create_Shader(const std::string& vertex_location, const std::string& fragment_location);
		void Use();

		void Update_Matrices(glm::mat4 model, bool model_is_colored);
		void Update_Projection(IE_Camera camera);
		unsigned int Get() { return program_id; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		static std::string Load_Shader(const std::string& file_name);
		static GLuint Compile_Shader(const std::string shader_code, GLenum shader_type);
		static void Check_Error(GLuint object_id, GLenum error, bool is_program, const char* custom_error_msg);
/* Private Variables        */
	private:
		GLuint program_id;

		GLuint vertex_shader;
		GLuint fragment_shader;

		GLuint model_uniform;
		GLuint view_uniform;
		GLuint projection_uniform;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_SHADER