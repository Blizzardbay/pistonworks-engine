#include "internal_engine_headers\ie_texture.h"
namespace pw {
/* IE_Texture               */
/* Static Declarations      */
	PW_BOOL IE_Texture::has_user_dir_changed = false;
	PW_CSTRING IE_Texture::user_dir = "\0";

	glm::vec3 IE_Texture::Engine_Colors[(PW_UINT)Default_Texture::Color_Count]{
		glm::vec3(1.0000000f, 0.0000000f, 0.0000000f),
		glm::vec3(0.0000000f, 0.5019607f, 0.0000000f),
		glm::vec3(0.0500000f, 0.0500000f, 1.0000000f),
		glm::vec3(1.0000000f, 1.0000000f, 0.0000000f),
		glm::vec3(1.0000000f, 0.7529411f, 0.7960784f),
		glm::vec3(0.0000000f, 1.0000000f, 1.0000000f),
		glm::vec3(1.0000000f, 0.5000000f, 0.0000000f),
		glm::vec3(1.0000000f, 0.0000000f, 1.0000000f),
		glm::vec3(1.0000000f, 1.0000000f, 1.0000000f),
		glm::vec3(0.0000000f, 0.0000000f, 0.0000000f),
		glm::vec3(0.0000000f, 1.0000000f, 0.0000000f),
		glm::vec3(0.0000000f, 0.5450980f, 0.5450980f),
		glm::vec3(0.5019607f, 0.0000000f, 0.5019607f),
		glm::vec3(0.6784313f, 0.8470588f, 0.9019607f),
		glm::vec3(0.5450980f, 0.2705882f, 0.0745098f),
		glm::vec3(0.4117647f, 0.4117647f, 0.4117647f),
		glm::vec3(0.7450980f, 0.7450980f, 0.7450980f)
	};
/* Class Members            */
	IE_Texture::IE_Texture() :
		texture_id(0), texture_width(0), texture_height(0), texture_bit_depth(0) {
	}
	IE_Texture::IE_Texture(PW_CSTRING file_location) :
			texture_id(0), texture_width(0), texture_height(0), texture_bit_depth(0) {
		if (file_location != NULL) {
			PW_BYTE* texture_data = nullptr;

			stbi_set_flip_vertically_on_load(true);

			PW_STBI_CALL(texture_data = stbi_load(file_location, (PW_INT*)&texture_width, (PW_INT*)&texture_height, &texture_bit_depth, 0));

			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			stbi_image_free(texture_data);
			texture_data = nullptr;
		}
	}
	void IE_Texture::Bind(PW_UINT unit) {
		assert(unit >= 0 && unit <= 31);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}
	void IE_Texture::Delete() {
		glDeleteTextures(1, &texture_id);
	}
	PW_STRING IE_Texture::Find_Texture(PW_CSTRING name) {
		if (has_user_dir_changed == true) {
			PW_STRING file_path = user_dir;
			file_path.append(name);
			return file_path;
		}
		else {
			PW_STRING file_path = "internal_engine_files/internal_engine_resource/textures/";
			file_path.append(name);
			return file_path;
		}
	}
	PW_STRING IE_Texture::Find_Color_Texture(PW_CSTRING d_bits, Default_Texture id, glm::vec3& color) {
		PW_STRING file_path = d_bits;
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
		color = Color(id);
		return file_path;
	}
/* IE_Texture               */
/* Static Declarations      */
	PW_BOOL IE_Icon::has_user_dir_changed = false;
	PW_CSTRING IE_Icon::user_dir = "\0";
/* Class Members            */
	IE_Icon::IE_Icon() :
			icon_width(0), icon_height(0), icon_bit_depth(0), icon_data(nullptr) {
	}
	IE_Icon::IE_Icon(PW_CSTRING file_location) :
			icon_width(0), icon_height(0), icon_bit_depth(0), icon_data(0) {
		if (file_location != NULL) {
			PW_BYTE* icon_data = nullptr;

			stbi_set_flip_vertically_on_load(true);

			PW_STBI_CALL(icon_data = stbi_load(file_location, (PW_INT*)&icon_width, (PW_INT*)&icon_height, &icon_bit_depth, 0));
			
			this->icon_data = new PW_BYTE[sizeof(icon_data)];

			this->icon_data = icon_data;

			icon_data = nullptr;
		}
	}
	void IE_Icon::Delete() {
		delete[] icon_data;
		icon_data = nullptr;
	}
	PW_STRING IE_Icon::Find_Icon(PW_CSTRING name) {
		if (has_user_dir_changed == true) {
			PW_STRING file_path = user_dir;
			file_path.append(name);
			return file_path;
		}
		else {
			PW_STRING file_path = "internal_engine_files/internal_engine_resource/icons/";
			file_path.append(name);
			return file_path;
		}
	}

}
