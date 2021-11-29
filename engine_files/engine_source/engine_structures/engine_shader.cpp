#include "engine_structures\engine_shader.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
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
			void Shader::Create_Shader(const std::wstring& vertex_location, const std::wstring& fragment_location) {
				try {
					PW_GL_CALL(std::move(program_id = glCreateProgram()));

					vertex_shader = Compile_Shader(Load_Shader(vertex_location), GL_VERTEX_SHADER);
					fragment_shader = Compile_Shader(Load_Shader(fragment_location), GL_FRAGMENT_SHADER);

					glAttachShader(program_id, vertex_shader);
					glAttachShader(program_id, fragment_shader);

					glBindAttribLocation(program_id, 0, "object_position");
					glBindAttribLocation(program_id, 1, "object_texture_coords");

					glLinkProgram(program_id);

					Check_Error(program_id, GL_LINK_STATUS, true, L"Failed to link program error: ");

					glValidateProgram(program_id);

					Check_Error(program_id, GL_VALIDATE_STATUS, true, L"Program Is Invalid Error: ");

					PW_GL_VOID_CALL(model_uniform = glGetUniformLocation(program_id, "object_model"), false);
					PW_GL_VOID_CALL(texture_uniform = glGetUniformLocation(program_id, "object_is_colored"), false);
					PW_GL_VOID_CALL(view_uniform = glGetUniformLocation(program_id, "object_view"), false);
					PW_GL_VOID_CALL(projection_uniform = glGetUniformLocation(program_id, "object_projection"), false);

					this_shader = *this;
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Shader::Use() {
				glUseProgram(program_id);
			}
			void Shader::Update_Matrices(glm::mat4* model, int32_t& model_is_colored) {
				glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(*model));
				glUniform1iv(texture_uniform, 1, &model_is_colored);
			}
			void Shader::Update_Projection() {
				glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(st::Camera::Update_Camera()));
				glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(st::Camera::Update_Projection()));
			}
			uint32_t Shader::Shader_Id() {
				return program_id;
			}
			Shader Shader::Get_Shader() {
				return this_shader;
			}
			std::wstring Shader::Load_Shader(const std::wstring& file_name) {
				std::wstring content = L"";
				std::wifstream fileStream(file_name, std::ios::in);

				if (!fileStream.is_open()) {
					wprintf(L"Shader: %s did not open\n", file_name.c_str());
					return L"";
				}

				std::wstring line = L"";
				while (!fileStream.eof()) {
					std::getline(fileStream, line);
					content.append(line + L"\n");
				}
				fileStream.close();
				return content;
			}
			GLuint Shader::Compile_Shader(const std::wstring shader_code, GLenum shader_type) {
				GLuint shader = 0;

				PW_GL_CALL(std::move(shader = glCreateShader(shader_type)));

				const GLchar* shader_str_source[1];
				GLint shader_str_source_length[1];
				
				shader_str_source[0] = TO_CHAR(shader_code.c_str());
				shader_str_source_length[0] = shader_code.size();

				glShaderSource(shader, 1, shader_str_source, shader_str_source_length);
				glCompileShader(shader);

				try {
					Check_Error(shader, GL_COMPILE_STATUS, false, L"Shader Compile Error: ");
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}

				return shader;
			}
			void Shader::Check_Error(uint32_t object_id, GLenum error, bool is_program, std::wstring custom_error_msg) {
				GLint success = 0;
				GLchar error_message[1024] = { 0 };

				if (is_program) {
					TRY_LINE glGetProgramiv(object_id, error, &success);
					if (success == GL_FALSE) {
						glGetProgramInfoLog(object_id, sizeof(error_message), NULL, error_message);
						throw pw::er::Warning_Error(L"Shader", std::move(std::wstring(custom_error_msg + TO_WSTRING(error_message))), std::move(EXCEPTION_LINE), __FILEW__, L"glGetProgramInfoLog");
					}
				}
				else {
					TRY_LINE glGetShaderiv(object_id, error, &success);
					if (success == GL_FALSE) {
						glGetShaderInfoLog(object_id, sizeof(error_message), NULL, error_message);
						throw pw::er::Warning_Error(L"Shader", std::move(std::wstring(custom_error_msg + TO_WSTRING(error_message))), std::move(EXCEPTION_LINE), __FILEW__, L"glGetProgramInfoLog");
					}
				}
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////