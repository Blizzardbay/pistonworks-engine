#include "engine_structures\engine_shader.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Shader_Loader
		// Static Declarations
		// Class Members
			std::wstring Shader_Loader::Load_Shader(const std::wstring& p_file_name) {
				std::wstring v_content = L"";

				std::wstring v_file_location = pw::cm::Engine_Constant::Pistonworks_Path().generic_wstring() + p_file_name;

				std::wifstream v_fileStream(v_file_location, std::ios::in);

				if (!v_fileStream.is_open()) {
					wprintf(L"Shader: %s did not open\n", p_file_name.c_str());
					return L"";
				}

				std::wstring v_line = L"";
				while (!v_fileStream.eof()) {
					std::getline(v_fileStream, v_line);
					v_content.append(v_line + L"\n");
				}
				v_fileStream.close();
				return v_content;
			}
			GLuint Shader_Loader::Compile_Shader(const std::wstring& p_shader_code, const GLenum& p_shader_type) {
				GLuint v_shader = 0;

				PW_GL_CALL(std::move(v_shader = glCreateShader(p_shader_type)));

				const GLchar* v_shader_str_source[1];
				GLint v_shader_str_source_length[1];

				char* v_shader_code = TO_CHAR(p_shader_code.c_str());

				v_shader_str_source[0] = v_shader_code;
				v_shader_str_source_length[0] = (GLint)p_shader_code.size();

				glShaderSource(v_shader, 1, v_shader_str_source, v_shader_str_source_length);

				if (pw::Engine_Memory::Deallocate<char>(v_shader_code) == false) {
					if (v_shader_code != nullptr) {
						delete[] v_shader_code;
						v_shader_code = nullptr;
					}
				}

				glCompileShader(v_shader);

				try {
					Check_Error(v_shader, GL_COMPILE_STATUS, false, L"Shader Compile Error: ");
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}

				return v_shader;
			}
			void Shader_Loader::Check_Error(const uint32_t& p_object_id, const GLenum& p_error, const bool& p_is_program, const std::wstring& p_custom_error_msg) {
				GLint v_success = 0;
				GLchar v_error_message[1024] { 0 };

				if (p_is_program) {
					TRY_LINE glGetProgramiv(p_object_id, p_error, &v_success);
					if (v_success == GL_FALSE) {
						glGetProgramInfoLog(p_object_id, sizeof(v_error_message), NULL, v_error_message);
						throw pw::er::Warning_Error(L"Shader", std::move(std::wstring(p_custom_error_msg + TO_WSTRING(std::string(v_error_message)))), EXCEPTION_LINE, __FILEW__, L"glGetProgramInfoLog");
					}
				}
				else {
					TRY_LINE glGetShaderiv(p_object_id, p_error, &v_success);
					if (v_success == GL_FALSE) {
						glGetShaderInfoLog(p_object_id, sizeof(v_error_message), NULL, v_error_message);
						throw pw::er::Warning_Error(L"Shader", std::move(std::wstring(p_custom_error_msg + TO_WSTRING(std::string(v_error_message)))), EXCEPTION_LINE, __FILEW__, L"glGetProgramInfoLog");
					}
				}
			}
		// End of Class Members
		// Dynamic_Shader               
		// Static Declarations 
			uint32_t Dynamic_Shader::m_program_id{ 0 };

			uint32_t Dynamic_Shader::m_vertex_shader{ 0 };
			uint32_t Dynamic_Shader::m_fragment_shader{ 0 };

			uint32_t Dynamic_Shader::m_model_uniform{ 0 };
			uint32_t Dynamic_Shader::m_view_uniform{ 0 };
			uint32_t Dynamic_Shader::m_projection_uniform{ 0 };

			uint32_t Dynamic_Shader::m_color_uniform{ 0 };
			uint32_t Dynamic_Shader::m_text_uniform{ 0 };
		// Class Members            
			void Dynamic_Shader::Create_Shader(const std::wstring& p_vertex_location, const std::wstring& p_fragment_location) {
				try {
					PW_GL_CALL(std::move(m_program_id = glCreateProgram()));

					m_vertex_shader = Shader_Loader::Compile_Shader(Shader_Loader::Load_Shader(p_vertex_location), GL_VERTEX_SHADER);
					m_fragment_shader = Shader_Loader::Compile_Shader(Shader_Loader::Load_Shader(p_fragment_location), GL_FRAGMENT_SHADER);

					PW_GL_VOID_CALL(glAttachShader(m_program_id, m_vertex_shader), false);
					PW_GL_VOID_CALL(glAttachShader(m_program_id, m_fragment_shader), false);

					PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 0, "object_position"), false);
					PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 1, "object_texture_coords"), false);
					PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 2, "object_color"), false);

					PW_GL_VOID_CALL(glLinkProgram(m_program_id), false);

					Shader_Loader::Check_Error(m_program_id, GL_LINK_STATUS, true, L"Failed to link program error: ");

					PW_GL_VOID_CALL(glValidateProgram(m_program_id), false);

					Shader_Loader::Check_Error(m_program_id, GL_VALIDATE_STATUS, true, L"Program Is Invalid Error: ");

					PW_GL_VOID_CALL(m_view_uniform = glGetUniformLocation(m_program_id, "object_view"), false);
					PW_GL_VOID_CALL(m_projection_uniform = glGetUniformLocation(m_program_id, "object_projection"), false);

					PW_GL_VOID_CALL(m_model_uniform = glGetUniformLocation(m_program_id, "object_model"), false);
					PW_GL_VOID_CALL(m_color_uniform = glGetUniformLocation(m_program_id, "object_is_colored"), false);
					PW_GL_VOID_CALL(m_text_uniform = glGetUniformLocation(m_program_id, "object_is_text"), false);
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			void Dynamic_Shader::Release_Shader() {
				if (m_vertex_shader != NULL) {
					if (glIsShader(m_vertex_shader) == GL_TRUE) {
						PW_GL_VOID_CALL(glDetachShader(m_program_id, m_vertex_shader), false);
					}
				}
				if (m_fragment_shader != NULL) {
					if (glIsShader(m_fragment_shader) == GL_TRUE) {
						PW_GL_VOID_CALL(glDetachShader(m_program_id, m_fragment_shader), false);
					}
				}
				if (m_program_id != NULL) {
					if (glIsProgram(m_program_id) == GL_TRUE) {
						PW_GL_VOID_CALL(glDeleteProgram(m_program_id), false);
					}
				}
			}
			void Dynamic_Shader::Use() {
				PW_GL_VOID_CALL(glUseProgram(m_program_id), false);
			}
			void Dynamic_Shader::Update_Matrices(const glm::mat4& p_model_matrix, const int32_t& p_model_is_colored, const int32_t& p_model_is_text) {
				PW_GL_VOID_CALL(glUniformMatrix4fv(m_model_uniform, 1, GL_FALSE, glm::value_ptr(p_model_matrix)), false);
				PW_GL_VOID_CALL(glUniform1iv(m_color_uniform, 1, &p_model_is_colored), false);
				PW_GL_VOID_CALL(glUniform1iv(m_text_uniform, 1, &p_model_is_text), false);
			}
			void Dynamic_Shader::Update_Projection() {
				PW_GL_VOID_CALL(glUniformMatrix4fv(m_view_uniform, 1, GL_FALSE, glm::value_ptr(st::Camera::Update_Camera())), false);
				PW_GL_VOID_CALL(glUniformMatrix4fv(m_projection_uniform, 1, GL_FALSE, glm::value_ptr(st::Camera::Update_Projection())), false);
			}
			const uint32_t& Dynamic_Shader::Shader_Id() {
				return m_program_id;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////