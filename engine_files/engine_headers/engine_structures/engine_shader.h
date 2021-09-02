#ifndef H_IE_SHADER
#define H_IE_SHADER
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers              
#include <fstream>
#include <stdio.h>
//////////////////////////////////
// Project Headers          
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
//////////////////////////////////
// Engine Headers           
#include "ie_camera.h"
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

		//////////////////////////////////
		// Class Name: pw::ie::Shader
		//																				 
		// Purpose: A class for handling the shaders in opengl.
		//
		class PW_INTERNAL_API Shader {
		// Default Class Structures 
		public:
			// Function: Shader::Shader
			//
			// Purpose: Creates a uninitialized shader.
			//
			Shader();
			// Function: Shader::~Shader
			//
			// Purpose: Deallocates all data used for the shader.
			//
			~Shader();
		private:
		// Public Functions/Macros  
		public:
			// Function: Shader::Create_Shader
			//
			// Purpose: Creates a new shader after one has been loaded from
			//  file.
			//
			PW_VOID Create_Shader(const PW_STRING& vertex_location, const PW_STRING& fragment_location);
			// Function: Shader::Use
			//
			// Purpose: Gets the shader ready for use.
			//
			PW_VOID Use();
			// Function: Shader::Update_Matrices
			//
			// Purpose: Updates the matrices of the model.
			//
			PW_VOID Update_Matrices(glm::mat4 model, PW_INT& model_is_colored);
			// Function: Shader::Update_Projection
			//
			// Purpose: Updates the camera projection.
			//
			PW_VOID Update_Projection();
			// Function: Shader::Shader_Id
			//
			// Purpose: Returns the shader's id.
			//
			PW_UINT Shader_Id();
			// Function: Shader::Get_Shader
			//
			// Purpose: Returns the current shader created by this class.
			//
			static Shader Get_Shader();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
			// Function: Shader::Load_Shader
			//
			// Purpose: Loads a shader from file.
			//
			static PW_STRING Load_Shader(const PW_STRING& file_name);
			// Function: Shader::Compile_Shader
			//
			// Purpose: Complies the shader for use.
			//
			static PW_UINT Compile_Shader(const PW_STRING shader_code, GLenum shader_type);
			// Function: Shader::Check_Error
			//
			// Purpose: Checks if the shader is not correctly made.
			//
			static PW_VOID Check_Error(PW_UINT object_id, GLenum error, PW_BOOL is_program, PW_CSTRING custom_error_msg);
		// Private Variables        
		private:
			static Shader this_shader;

			PW_UINT program_id;

			PW_UINT vertex_shader;
			PW_UINT fragment_shader;

			PW_UINT model_uniform;
			PW_UINT texture_uniform;
			PW_UINT view_uniform;
			PW_UINT projection_uniform;
		};
		// Functions                
		// Macros / Definitions                  
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_SHADER