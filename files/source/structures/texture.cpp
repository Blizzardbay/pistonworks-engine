#include "structures\texture.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		// Texture               
		// Static Declarations   
		// Class Members            
			Texture::Texture() :
					m_copy{ false }, m_texture_id{ 0 }, m_texture_width{ 0 }, m_texture_height{ 0 }, m_texture_handle{ 0 }{
			}
			Texture::Texture(BYTE* p_tex_data, const uint32_t& p_target, const uint32_t& p_texture_width, const uint32_t& p_texture_height,
								const int32_t& p_internal_format, const int32_t& p_format, const bool& p_repeat, const bool& p_linear) :
					m_copy{ false }, m_texture_id{ 0 }, m_texture_width{ p_texture_width }, m_texture_height{ p_texture_height }, m_texture_handle{ 0 } {
				if (TRY_LINE p_tex_data == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE_W(L"Invalid Parameter: p_tex_data was nullptr");
					return;
				}
				else {
					PW_GL_VOID_CALL(glGenTextures(1, &m_texture_id), true, false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id), true, false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), true, false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), true, false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), true, false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), true, false);

					PW_GL_VOID_CALL(glTexImage2D(p_target, 0, p_internal_format, TO_INT32(p_texture_width), TO_INT32(p_texture_height), 0, p_format, GL_UNSIGNED_BYTE, p_tex_data), true, false);

					m_texture_handle = glGetTextureHandleARB(m_texture_id);

					if (m_texture_handle != NULL) {
						PW_GL_VOID_CALL(glMakeTextureHandleResidentARB(m_texture_handle), true, true);
					}
					else {
						PW_GL_VOID_CALL(glDeleteTextures(1, &m_texture_id), true, true);
					}
				}
			}
			Texture::Texture(BYTE* p_tex_data, const uint32_t& p_texture_width, const uint32_t& p_texture_height,
								const int32_t& p_internal_format, const int32_t& p_format, const bool& p_repeat, const bool& p_linear) :
					m_copy{ false }, m_texture_id{ 0 }, m_texture_width{ p_texture_width }, m_texture_height{ p_texture_height }, m_texture_handle{ 0 } {
				if (TRY_LINE p_tex_data == nullptr) {
					SET_ERROR_STATE(PW_NULL_PARAMETER_W);
					SET_ERROR_TYPE_W(L"Invalid Parameter: p_tex_data was nullptr");
					return;
				}
				else {
					PW_GL_VOID_CALL(glGenTextures(1, &m_texture_id), true, false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id), true, false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), true, false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), true, false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), true, false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), true, false);

					PW_GL_VOID_CALL(glTexImage2D(GL_TEXTURE_2D, 0, p_internal_format, TO_INT32(p_texture_width), TO_INT32(p_texture_height), 0, p_format, GL_UNSIGNED_BYTE, p_tex_data), true, false);

					m_texture_handle = glGetTextureHandleARB(m_texture_id);

					if (TRY_LINE m_texture_handle != NULL) {
						PW_GL_VOID_CALL(glMakeTextureHandleResidentARB(m_texture_handle), true, false);
					}
					else {
						PW_GL_VOID_CALL(glDeleteTextures(1, &m_texture_id), true, false);
					}
				}
			}
			Texture::Texture(const Texture& p_other):
					m_texture_id{ p_other.m_texture_id }, m_texture_width{ p_other.m_texture_width }, m_texture_height{ p_other.m_texture_height }, m_copy{ true }, m_texture_handle{p_other.m_texture_handle}{
			}
			Texture::~Texture() {
				if (m_copy != true) {
					PW_GL_VOID_CALL(glDeleteTextures(1, &m_texture_id), true, false);
				}
			}
			glm::vec2 Texture::Size() {
				return glm::vec2(m_texture_width, m_texture_height);
			}
			const uint64_t& Texture::Texture_Handle() const {
				return m_texture_handle;
			}
		// Texture_Structure
		// Static Declarations
		// Class Members
			Texture_Structure::Texture_Structure(st::Texture* p_texture) :
				m_textures{}, m_single_texture{ true }, m_current_access{ nullptr } {
				m_textures.insert(std::make_pair(L"SINGLE", p_texture));
			}
			Texture_Structure::Texture_Structure(const std::vector<st::Texture*>& p_textures, const std::vector<std::wstring>& p_texture_ids) :
				m_textures{}, m_single_texture{ false }, m_current_access{ p_textures.size() > 0 ? p_textures.at(0) : nullptr } {
				if (TRY_LINE p_textures.size() == p_texture_ids.size()) {
					for (size_t i = 0; i < p_textures.size(); i++) {
						m_textures.insert(std::make_pair(p_texture_ids.at(i), p_textures.at(i)));
					}
				}
				else {
					SET_ERROR_STATE(PW_ANIMATION_ID_SIZE_MISMATCH);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::cm::Constant", L"Texture count does not equal id count. Every texture must have an id.", ERROR_LINE, __FILEW__, L"Texture_Structure"));
					return;
				}
			}
			Texture_Structure::~Texture_Structure() {
				m_textures.clear();
			}
			st::Texture* Texture_Structure::Texture() const {
				if (m_single_texture == true) {
					return m_textures.at(L"SINGLE");
				}
				else {
					return nullptr;
				}
			}
			st::Texture* Texture_Structure::Texture(const std::wstring& p_texture_id) {
				auto v_found = m_textures.find(p_texture_id);
				if (v_found != m_textures.end()) {
					m_current_access = m_textures.at(p_texture_id);
					return m_textures.at(p_texture_id);
				}
				else {
					return nullptr;
				}
			}
	ST_NAMESPACE_END
PW_NAMESPACE_END