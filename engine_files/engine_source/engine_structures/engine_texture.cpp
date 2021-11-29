#include "engine_structures\engine_texture.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Texture               
		// Static Declarations   
		// Class Members            
			Texture::Texture() :
					texture_id(0), texture_width(0), texture_height(0) {
			}
			Texture::Texture(BYTE* tex_data, uint32_t target, uint32_t tex_width, uint32_t tex_height, int32_t internal_format, int32_t format) :
					texture_id(0), texture_width(tex_width), texture_height(tex_height) {
				if (TRY_LINE tex_data != nullptr) {
					PW_GL_VOID_CALL(glGenTextures(1, &texture_id), false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, texture_id), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
											
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);

					PW_GL_VOID_CALL(glTexImage2D(target, 0, internal_format, tex_width, tex_height, 0, format, GL_UNSIGNED_BYTE, tex_data), false);

					PW_GL_VOID_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), false);
				}
				else {
					throw er::Warning_Error(L"Texture", L"Texture data was nullptr.", std::move(EXCEPTION_LINE), __FILEW__, L"Texture");
				}
			}
			Texture::Texture(BYTE* tex_data, uint32_t tex_width, uint32_t tex_height, int32_t internal_format, int32_t format) :
					texture_id(0), texture_width(tex_width), texture_height(tex_height) {
				if (tex_data != nullptr) {
					PW_GL_VOID_CALL(glGenTextures(1, &texture_id), false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, texture_id), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);

					PW_GL_VOID_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internal_format, tex_width, tex_height, 0, format, GL_UNSIGNED_BYTE, tex_data), false);

					PW_GL_VOID_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), false);
				}
				else {
					throw er::Warning_Error(L"Texture", L"Texture data was nullptr.", std::move(EXCEPTION_LINE), __FILEW__, L"Texture");
				}
			}
			Texture::Texture(PW_SRD_PTR(BYTE*) tex_data, uint32_t tex_width, uint32_t tex_height, int32_t internal_format, int32_t format) :
					texture_id(0), texture_width(tex_width), texture_height(tex_height) {
				if (tex_data != nullptr) {
					PW_GL_VOID_CALL(glGenTextures(1, &texture_id), false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, texture_id), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);

					PW_GL_VOID_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internal_format, tex_width, tex_height, 0, format, GL_UNSIGNED_BYTE, *tex_data), false);

					PW_GL_VOID_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), false);
				}
				else {
					throw er::Warning_Error(L"Texture", L"Texture data was nullptr.", std::move(EXCEPTION_LINE), __FILEW__, L"Texture");
				}
			}
			Texture::~Texture() {
				LET_CPP_IMPLEMENT;
			}
			void Texture::Bind(uint32_t unit) {
				assert(unit >= 0 && unit <= 31);

				PW_GL_VOID_CALL(glActiveTexture(GL_TEXTURE0 + unit), false);
				PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, texture_id), false);
			}
			void Texture::Delete() {
				PW_GL_VOID_CALL(glDeleteTextures(1, &texture_id), false);
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////