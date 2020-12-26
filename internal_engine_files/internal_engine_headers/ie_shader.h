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
		PW_VOID Create_Shader(const PW_STRING& vertex_location, const PW_STRING& fragment_location);
		PW_VOID Use();

		PW_VOID Update_Matrices(glm::mat4 model, PW_BOOL model_is_colored);
		PW_VOID Update_Projection(IE_Camera camera);
		PW_UINT Shader_Id() { return program_id; }

		static IE_Shader Get_Shader() { return this_shader; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		static PW_STRING Load_Shader(const PW_STRING& file_name);
		static PW_UINT Compile_Shader(const PW_STRING shader_code, GLenum shader_type);
		static PW_VOID Check_Error(unsigned int object_id, GLenum error, PW_BOOL is_program, PW_CSTRING custom_error_msg);
/* Private Variables        */
	private:
		static IE_Shader this_shader;

		PW_UINT program_id;

		PW_UINT vertex_shader;
		PW_UINT fragment_shader;

		PW_UINT model_uniform;
		PW_UINT view_uniform;
		PW_UINT projection_uniform;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_SHADER