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
					m_copy{ false }, m_texture_id{ 0 }, m_texture_width{ 0 }, m_texture_height{ 0 } {
			}
			Texture::Texture(BYTE* p_tex_data, const uint32_t& p_target, const uint32_t& p_texture_width, const uint32_t& p_texture_height,
								const int32_t& p_internal_format, const int32_t& p_format, const bool& p_repeat, const bool& p_linear) :
					m_copy{ false }, m_texture_id{ 0 }, m_texture_width{ p_texture_width }, m_texture_height{ p_texture_height } {
				if (TRY_LINE p_tex_data != nullptr) {
					PW_GL_VOID_CALL(glGenTextures(1, &m_texture_id), false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id), false);
																					
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), false);

					PW_GL_VOID_CALL(glTexImage2D(p_target, 0, p_internal_format, p_texture_width, p_texture_height, 0, p_format, GL_UNSIGNED_BYTE, p_tex_data), false);
				}
				else {
					throw er::Warning_Error(L"Texture", L"Texture data was nullptr.", EXCEPTION_LINE, __FILEW__, L"Texture");
				}
			}
			Texture::Texture(BYTE* p_tex_data, const uint32_t& p_texture_width, const uint32_t& p_texture_height,
								const int32_t& p_internal_format, const int32_t& p_format, const bool& p_repeat, const bool& p_linear) :
					m_copy{ false }, m_texture_id{ 0 }, m_texture_width{ p_texture_width }, m_texture_height{ p_texture_height } {
				if (p_tex_data != nullptr) {
					PW_GL_VOID_CALL(glGenTextures(1, &m_texture_id), false);
					PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE), false);

					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), false);
					PW_GL_VOID_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p_linear ? GL_LINEAR : GL_NEAREST), false);

					PW_GL_VOID_CALL(glTexImage2D(GL_TEXTURE_2D, 0, p_internal_format, p_texture_width, p_texture_height, 0, p_format, GL_UNSIGNED_BYTE, p_tex_data), false);
				}
				else {
					throw er::Warning_Error(L"Texture", L"Texture data was nullptr.", EXCEPTION_LINE, __FILEW__, L"Texture");
				}
			}
			Texture::Texture(const Texture& p_other):
					m_texture_id{ p_other.m_texture_id }, m_texture_width{ p_other.m_texture_width }, m_texture_height{ p_other.m_texture_height }, m_copy{ true } {
			}
			Texture::~Texture() {
				if (m_copy != true) {
					PW_GL_VOID_CALL(glDeleteTextures(1, &m_texture_id), false);
				}
			}
			void Texture::Bind(const uint32_t& p_unit) {
				assert(p_unit >= 0 && p_unit <= 31);

				PW_GL_VOID_CALL(glActiveTexture(GL_TEXTURE0 + p_unit), false);
				PW_GL_VOID_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id), false);
			}
			glm::vec2 Texture::Size() {
				return glm::vec2(m_texture_width, m_texture_height);
			}
		// End of Class Members
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
					throw pw::er::Warning_Error(L"Texture_Structure", L"Texture count does not equal id count. Every texture must have an id.", EXCEPTION_LINE, __FILEW__, L"Texture_Structure");
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
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////