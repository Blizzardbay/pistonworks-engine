#include "internal_engine_headers\ie_shader.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// Shader               
		// Static Declarations     
			Shader Shader::this_shader = Shader();
		// Class Members            
			Shader::Shader() :
					program_id{ 0 }, vertex_shader{ 0 }, fragment_shader{ 0 },
					model_uniform{ 0 }, texture_uniform{ 0 }, view_uniform{ 0 }, projection_uniform{ 0 } {
			}
			Shader::~Shader() {
				glDetachShader(program_id, vertex_shader);

				glDetachShader(program_id, fragment_shader);

				glDeleteProgram(program_id);
			}
			PW_VOID Shader::Create_Shader(const PW_STRING& vertex_location, const PW_STRING& fragment_location) {
				PW_GL_CALL(program_id = glCreateProgram());

				vertex_shader = Compile_Shader(Load_Shader(vertex_location), GL_VERTEX_SHADER);
				fragment_shader = Compile_Shader(Load_Shader(fragment_location), GL_FRAGMENT_SHADER);

				glAttachShader(program_id, vertex_shader);
				glAttachShader(program_id, fragment_shader);

				glBindAttribLocation(program_id, 0, "object_position");
				glBindAttribLocation(program_id, 1, "object_texture_coords");

				glLinkProgram(program_id);

				Check_Error(program_id, GL_LINK_STATUS, true, "Failed to link program error: ");

				glValidateProgram(program_id);

				Check_Error(program_id, GL_VALIDATE_STATUS, true, "Program Is Invalid Error: ");

				PW_GL_VOID_CALL(model_uniform  = glGetUniformLocation(program_id, "object_model"), false);
				PW_GL_VOID_CALL(texture_uniform = glGetUniformLocation(program_id, "object_is_colored"), false);
				PW_GL_VOID_CALL(view_uniform = glGetUniformLocation(program_id, "object_view"), false);
				PW_GL_VOID_CALL(projection_uniform = glGetUniformLocation(program_id, "object_projection"), false);

				this_shader = *this;
			}
			PW_VOID Shader::Use() {
				glUseProgram(program_id);
			}
			PW_VOID Shader::Update_Matrices(glm::mat4 model, PW_INT& model_is_colored) {
				glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
				glUniform1iv(texture_uniform, 1, &model_is_colored);
			}
			PW_VOID Shader::Update_Projection() {
				glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(ie::Camera::Update_Camera()));
				glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(ie::Camera::Update_Projection()));
			}
			PW_UINT Shader::Shader_Id() {
				return program_id;
			}
			Shader Shader::Get_Shader() {
				return this_shader;
			}
			PW_STRING Shader::Load_Shader(const PW_STRING& file_name) {
				PW_STRING content = "";
				std::ifstream fileStream(file_name, std::ios::in);

				if (!fileStream.is_open()) {
					printf("Shader: %s did not open\n", file_name.c_str());
					return "";
				}

				PW_STRING line = "";
				while (!fileStream.eof()) {
					std::getline(fileStream, line);
					content.append(line + "\n");
				}
				fileStream.close();
				return content;
			}
			GLuint Shader::Compile_Shader(const PW_STRING shader_code, GLenum shader_type) {
				GLuint shader = 0;

				PW_GL_CALL(shader = glCreateShader(shader_type));

				const GLchar* shader_str_source[1];
				GLint shader_str_source_length[1];

				shader_str_source[0] = shader_code.c_str();
				shader_str_source_length[0] = shader_code.length();
				glShaderSource(shader, 1, shader_str_source, shader_str_source_length);
				glCompileShader(shader);

				Check_Error(shader, GL_COMPILE_STATUS, false, "Shader Compile Error: ");

				return shader;
			}
			PW_VOID Shader::Check_Error(PW_UINT object_id, GLenum error, PW_BOOL is_program, PW_CSTRING custom_error_msg) {
				GLint success = 0;
				GLchar error_message[1024] = { 0 };

				if (is_program) {
					glGetProgramiv(object_id, error, &success);
					if (success == GL_FALSE) {
						glGetProgramInfoLog(object_id, sizeof(error_message), NULL, error_message);
						printf("|%s:%s\n", custom_error_msg, error_message);
					}
				}
				else {
					glGetShaderiv(object_id, error, &success);
					if (success == GL_FALSE) {
						glGetShaderInfoLog(object_id, sizeof(error_message), NULL, error_message);
						printf("|%s:%s\n", custom_error_msg, error_message);
					}
				}
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////