#include "internal_engine_headers\ie_shader.h"
namespace pw {
/* IE_Shader                */
/* Static Declarations      */
	IE_Shader IE_Shader::this_shader = IE_Shader();
/* Class Members            */
	IE_Shader::IE_Shader() :
		program_id{ 0 }, vertex_shader{ 0 }, fragment_shader{ 0 },
		model_uniform{ 0 }, view_uniform{ 0 }, projection_uniform{ 0 } {
	}
	IE_Shader::~IE_Shader() {
		glDetachShader(program_id, vertex_shader);

		glDetachShader(program_id, fragment_shader);

		glDeleteProgram(program_id);
	}
	void IE_Shader::Create_Shader(const std::string& vertex_location, const std::string& fragment_location) {
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

		this_shader = *this;
	}
	void IE_Shader::Use() {
		glUseProgram(program_id);
	}
	void IE_Shader::Update_Matrices(glm::mat4 model, bool model_is_colored) {
		unsigned int model_location = glGetUniformLocation(program_id, "object_model");
		unsigned int model_is_colored_location = glGetUniformLocation(program_id, "object_is_colored");

		int int_model_is_colored = model_is_colored;

		glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1iv(model_is_colored_location, 1, &int_model_is_colored);
	}
	void IE_Shader::Update_Projection(IE_Camera camera) {
		unsigned int projection_location = glGetUniformLocation(program_id, "object_projection");
		unsigned int camera_location = glGetUniformLocation(program_id, "object_view");

		glUniformMatrix4fv(camera_location, 1, GL_FALSE, glm::value_ptr(camera.Update_Camera()));
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(camera.Update_Projection()));
	}
	std::string IE_Shader::Load_Shader(const std::string& file_name) {
		std::string content = "";
		std::ifstream fileStream(file_name, std::ios::in);

		if (!fileStream.is_open()) {
			printf("Shader: %s did not open\n", file_name.c_str());
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
		return content;
	}
	GLuint IE_Shader::Compile_Shader(const std::string shader_code, GLenum shader_type) {
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
	void IE_Shader::Check_Error(unsigned int object_id, GLenum error, bool is_program, const char* custom_error_msg) {
		GLint success = 0;
		GLchar error_message[1024] = { 0 };

		if (is_program) {
			glGetProgramiv(object_id, error, &success);
			if (success == GL_FALSE) {
				glGetProgramInfoLog(object_id, sizeof(error_message), NULL, error_message);
				printf("|%s:%s'\n", custom_error_msg, error_message);
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
}