#include "internal_engine_headers\ie_texture.h"
namespace pw {
/* IE_Texture               */
/* Static Declarations      */
	bool IE_Texture::has_user_dir_changed = false;
	const char* IE_Texture::user_dir = "\0";
/* Class Members            */
	IE_Texture::IE_Texture() :
		texture_id(0), texture_width(0), texture_height(0), texture_bit_depth(0) {
	}
	IE_Texture::IE_Texture(const char* file_location) :
			texture_id(0), texture_width(0), texture_height(0), texture_bit_depth(0) {
		if (file_location != NULL) {
			unsigned char* texture_data = nullptr;

			stbi_set_flip_vertically_on_load(true);

			PW_STBI_CALL(texture_data = stbi_load(file_location, (int*)&texture_width, (int*)&texture_height, &texture_bit_depth, STBI_rgb_alpha));

			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			stbi_image_free(texture_data);
			texture_data = nullptr;
		}
	}
	void IE_Texture::Bind(unsigned int unit) {
		assert(unit >= 0 && unit <= 31);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}
	void IE_Texture::Delete() {
		glDeleteTextures(1, &texture_id);
	}
	std::string IE_Texture::Find_Texture(const char* name) {
		if (has_user_dir_changed == true) {
			std::string file_path = user_dir;
			file_path.append(name);
			return file_path;
		}
		else {
			std::string file_path = "internal_engine_files/internal_engine_resource/textures/";
			file_path.append(name);
			return file_path;
		}
	}
	std::string IE_Texture::Find_Color_Texture(const char* d_bits, Default_Texture id, glm::vec3& color) {
		std::string file_path = d_bits;
		if (file_path == "D16") {
			file_path = "internal_engine_files/internal_engine_resource/d16px/White.png";
		}
		else {
			if (file_path == "D32") {
				file_path = "internal_engine_files/internal_engine_resource/d32px/White.png";
			}
			else {
				if (file_path == "D64") {
					file_path = "internal_engine_files/internal_engine_resource/d64px/White.png";
				}
			}
		}
		switch (id) {
			case Default_Texture::RED: {
				color = glm::vec3(1.0f, 0.0f, 0.0f);
				break;
			}
			case Default_Texture::GREEN: {
				color = glm::vec3(0.0f, 0.5019607f, 0.0f);
				break;
			}
			case Default_Texture::BLUE: {
				color = glm::vec3(0.0f, 0.0f, 1.0f);
				break;
			}
			case Default_Texture::YELLOW: {
				color = glm::vec3(1.0f, 1.0f, 0.0f);
				break;
			}
			case Default_Texture::PINK: {
				color = glm::vec3(1.0f, 0.7529411f, 0.7960784f);
				break;
			}
			case Default_Texture::CYAN: {
				color = glm::vec3(0.0f, 1.0f, 1.0f);
				break;
			}
			case Default_Texture::ORANGE: {
				color = glm::vec3(1.0f, 0.5f, 0.0f);
				break;
			}
			case Default_Texture::MAGENTA: {
				color = glm::vec3(1.0f, 0.0f, 1.0f);
				break;
			}
			case Default_Texture::WHITE: {
				color = glm::vec3(1.0f, 1.0f, 1.0f);
				break;
			}
			case Default_Texture::BLACK: {
				color = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			case Default_Texture::LIME: {
				color = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			}
			case Default_Texture::DARK_CYAN: {
				color = glm::vec3(0.0f, 0.545098f, 0.545098f);
				break;
			}
			case Default_Texture::PURPLE: {
				color = glm::vec3(0.5019607f, 0.0f, 0.5019607f);
				break;
			}
			case Default_Texture::LIGHT_BLUE: {
				color = glm::vec3(0.6784313f,0.8470588f,0.9019607f);
				break;
			}
			case Default_Texture::BROWN: {
				color = glm::vec3();
				break;
			}
			case Default_Texture::DARK_GREY: {
				color = glm::vec3();
				break;
			}
			case Default_Texture::GREY: {
				color = glm::vec3();
				break;
			}
			default:
				break;
		}
		return file_path;
	}
}
