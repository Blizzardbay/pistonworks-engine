#include "internal_engine_headers\ie_texture.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// Texture               
		// Static Declarations     
			PW_BOOL Texture::has_user_dir_changed = false;
			PW_CSTRING Texture::user_dir = "\0";

			glm::vec3 Texture::Engine_Colors[(PW_UINT)Default_Texture::Color_Count] {
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
		// Class Members            
			Texture::Texture() :
					texture_id(0), texture_width(0), texture_height(0), texture_bit_depth(0) {
			}
			Texture::Texture(PW_CSTRING file_location) :
				texture_id(0), texture_width(0), texture_height(0), texture_bit_depth(0) {
				if (file_location != NULL) {
					PW_BYTE* texture_data = nullptr;

					stbi_set_flip_vertically_on_load(true);

					PW_STBI_CALL(texture_data = stbi_load(file_location, (PW_INT*)&texture_width, (PW_INT*)&texture_height, &texture_bit_depth, 0));

					PW_GL_VOID_CALL(glGenTextures(1, &texture_id), false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, texture_id), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);

					PW_GL_VOID_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data), false);

					PW_GL_VOID_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), false);

					stbi_image_free(texture_data);
					texture_data = nullptr;
				}
			}
			void Texture::Bind(PW_UINT unit) {
				assert(unit >= 0 && unit <= 31);

				glActiveTexture(GL_TEXTURE0 + unit);
				PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, texture_id), false);
			}
			void Texture::Delete() {
				PW_GL_VOID_CALL(glDeleteTextures(1, &texture_id), false);
			}
			PW_STRING Texture::Find_Texture(PW_CSTRING name) {
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
			PW_STRING Texture::Find_Color_Texture(PW_CSTRING d_bits, Default_Texture id, glm::vec3& color) {
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
			PW_VOID Texture::Change_Texture_Dir(PW_CSTRING new_dir) {
				has_user_dir_changed = true;
				user_dir = new_dir;
			}
			glm::vec3 Texture::Color(Default_Texture color_id) {
				return Engine_Colors[(PW_UINT)color_id];
			}
		// End of Class Members
		// Icon              
		// Static Declarations      
			PW_BOOL Icon::has_user_dir_changed = false;
			PW_CSTRING Icon::user_dir = "\0";
		// Class Members            
			Icon::Icon() :
					icon_width(0), icon_height(0), icon_bit_depth(0), icon_data(nullptr) {
			}
			Icon::Icon(PW_CSTRING file_location) :
					icon_width(0), icon_height(0), icon_bit_depth(0), icon_data(0) {
				if (file_location != NULL) {
					PW_BYTE* icon_data = nullptr;

					stbi_set_flip_vertically_on_load(true);

					PW_STBI_CALL(icon_data = stbi_load(file_location, (PW_INT*)&icon_width, (PW_INT*)&icon_height, &icon_bit_depth, 0));

					this->icon_data = std::make_shared<PW_BYTE PW_SMART_ARRAY>(new PW_BYTE[sizeof(icon_data)]);

					(*this->icon_data) = icon_data;
				}
			}
			Icon::~Icon() {
			}
			void Icon::Delete() {
				icon_data.~shared_ptr();
			}
			PW_STRING Icon::Find_Icon(PW_CSTRING name) {
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
			PW_VOID Icon::Change_Icon_Dir(PW_CSTRING new_dir) {
				has_user_dir_changed = true;
				user_dir = new_dir;
			}
			PW_BYTE* Icon::Data() {
				return *icon_data;
			}
			PW_UINT Icon::Width() {
				return icon_width;
			}
			PW_UINT Icon::Height() {
				return icon_height;
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////