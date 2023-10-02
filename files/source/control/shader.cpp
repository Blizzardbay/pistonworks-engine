#include "control\shader.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Shader_Loader
		// Static Declarations
		// Class Members
			std::wstring Shader_Loader::Load_Shader(const std::wstring& p_file_name) {
				std::wstring v_content{ L"" };

				std::wstring v_file_location{ pw::cm::Constant::Pistonworks_Path().generic_wstring() + p_file_name };

				std::wifstream v_fileStream{ v_file_location, std::ios::in };

				if (!v_fileStream.is_open()) {
					SET_ERROR_STATE(PW_FILE_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Shader_Loader", std::wstring(p_file_name).insert(0, L"Could not find shader "), ERROR_LINE, __FILEW__, L"Load_Shader"));

					return L"";
				}

				std::wstring v_line{ L"" };
				while (!v_fileStream.eof()) {
					std::getline(v_fileStream, v_line);
					v_content.append(v_line + L"\n");
				}
				v_fileStream.close();
				return v_content;
			}
			uint32_t Shader_Loader::Compile_Shader(const std::wstring& p_shader_code, const uint32_t& p_shader_type) {
				uint32_t v_shader{ 0 };

				if (p_shader_code == L"") {
					SET_ERROR_STATE(PW_FUNCTION_ERROR);
					MAINTAIN_ERROR_TYPE(L"pw::co::Shader_Loader", L"Shader_Loader::Load_Shader(p_vertex_location)", ERROR_LINE, __FILEW__, L"Compile_Shader");

					return 0;
				}

				PW_GL_CALL(std::move(v_shader = glCreateShader(p_shader_type)), false);

				if (pw::er::Error_State::Get() > PW_NO_ERROR) {
					return uint32_t(0);
				}

				char* v_shader_code{ TO_CHAR(p_shader_code.c_str()) };

				const char* v_shader_str_source[1]{ v_shader_code };
				int32_t v_shader_str_source_length[1]{ TO_INT32(p_shader_code.size()) };

				glShaderSource(v_shader, 1, v_shader_str_source, v_shader_str_source_length);

				if (pw::co::Memory::Deallocate<char>(v_shader_code) == false) {
					if (v_shader_code != nullptr) {
						delete[] v_shader_code;
						v_shader_code = nullptr;
					}
				}

				glCompileShader(v_shader);

				PW_CALL(Check_Error(v_shader, GL_COMPILE_STATUS, false, L"Shader Compile Error: "), false);

				return v_shader;
			}
			void Shader_Loader::Check_Error(const uint32_t& p_object_id, const uint32_t& p_error, const bool& p_is_program, const std::wstring& p_custom_error_msg) {
				int32_t v_success{ 0 };
				char v_error_message[1024]{ 0 };
				wchar_t v_werror_message[1024]{ 0 };

				if (p_is_program) {
					TRY_LINE glGetProgramiv(p_object_id, p_error, &v_success);
					if (v_success == GL_FALSE) {
						glGetProgramInfoLog(p_object_id, sizeof(v_error_message), NULL, v_error_message);

						for (uint32_t i = 0; i < 1024; i++) {
							v_werror_message[i] = (wchar_t)v_error_message[i];
						}

						SET_ERROR_STATE(PW_GL_ERROR);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Shader_Loader", std::wstring(p_custom_error_msg + std::wstring(v_werror_message)), ERROR_LINE, __FILEW__, L"Check_Error"));
						return;
					}
				}
				else {
					TRY_LINE glGetShaderiv(p_object_id, p_error, &v_success);
					if (v_success == GL_FALSE) {
						glGetShaderInfoLog(p_object_id, sizeof(v_error_message), NULL, v_error_message);
						
						for (uint32_t i = 0; i < 1024; i++) {
							v_werror_message[i] = (wchar_t)v_error_message[i];
						}

						SET_ERROR_STATE(PW_GL_ERROR);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Shader_Loader", std::wstring(p_custom_error_msg + std::wstring(v_werror_message)), ERROR_LINE, __FILEW__, L"Check_Error"));
						return;
					}
				}
			}
		// Shader               
		// Static Declarations 
			uint32_t Shader::m_program_id{ 0 };

			uint32_t Shader::m_vertex_shader{ 0 };
			uint32_t Shader::m_fragment_shader{ 0 };

			int32_t Shader::m_view_uniform{ 0 };
			int32_t Shader::m_projection_uniform{ 0 };
		// Class Members            
			void Shader::Create_Shader(const std::wstring& p_vertex_location, const std::wstring& p_fragment_location) {
				PW_GL_CALL(std::move(m_program_id = glCreateProgram()), true);

				PW_CALL(m_vertex_shader = Shader_Loader::Compile_Shader(Shader_Loader::Load_Shader(p_vertex_location), GL_VERTEX_SHADER), true);
				PW_CALL(m_fragment_shader = Shader_Loader::Compile_Shader(Shader_Loader::Load_Shader(p_fragment_location), GL_FRAGMENT_SHADER), true);

				PW_GL_VOID_CALL(glAttachShader(m_program_id, m_vertex_shader), false, false);
				PW_GL_VOID_CALL(glAttachShader(m_program_id, m_fragment_shader), false, false);

				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 0, "object_position"), false, false);
				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 1, "object_texture_coords"), false, false);
				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 2, "object_color"), false, false);
				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 3, "object_model"), false, false);
				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 7, "object_is_colored"), false, false);
				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 8, "object_is_text"), false, false);
				PW_GL_VOID_CALL(glBindAttribLocation(m_program_id, 9, "object_texture_handle"), false, false);

				PW_GL_VOID_CALL(glLinkProgram(m_program_id), false, false);

				PW_CALL(Shader_Loader::Check_Error(m_program_id, GL_LINK_STATUS, true, L"Failed to link program error: "), true);

				PW_GL_VOID_CALL(glValidateProgram(m_program_id), false, false);

				PW_CALL(Shader_Loader::Check_Error(m_program_id, GL_VALIDATE_STATUS, true, L"Program Is Invalid Error: "), true);

				PW_GL_VOID_CALL(m_view_uniform = glGetUniformLocation(m_program_id, "object_view"), false, false);
				PW_GL_VOID_CALL(m_projection_uniform = glGetUniformLocation(m_program_id, "object_projection"), false, false);
			}
			void Shader::Release() {
				if (m_vertex_shader != NULL) {
					if (glIsShader(m_vertex_shader) == GL_TRUE) {
						PW_GL_VOID_CALL(glDetachShader(m_program_id, m_vertex_shader), false, false);
					}
				}
				if (m_fragment_shader != NULL) {
					if (glIsShader(m_fragment_shader) == GL_TRUE) {
						PW_GL_VOID_CALL(glDetachShader(m_program_id, m_fragment_shader), false, false);
					}
				}
				if (m_program_id != NULL) {
					if (glIsProgram(m_program_id) == GL_TRUE) {
						PW_GL_VOID_CALL(glDeleteProgram(m_program_id), false, false);
					}
				}
			}
			void Shader::Use() {
				PW_GL_VOID_CALL(glUseProgram(m_program_id), false, false);
			}
			void Shader::Update_Projection() {
				PW_GL_VOID_CALL(glUniformMatrix4fv(m_view_uniform, 1, GL_FALSE, glm::value_ptr(st::Camera::Update_Camera())), false, false);
				PW_GL_VOID_CALL(glUniformMatrix4fv(m_projection_uniform, 1, GL_FALSE, glm::value_ptr(st::Camera::Update_Projection())), false, false);
			}
			const uint32_t& Shader::Shader_Id() {
				return m_program_id;
			}
	CO_NAMESPACE_END
PW_NAMESPACE_END