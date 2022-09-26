#include "engine_structures\engine_animation.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Animation
		// Static Declarations
		// Class Members
			Animation::Animation() :
					m_keep_animating{ true }, m_is_async{ false}, m_start{ false }, m_end{ false },
					m_frame_timer{ 0, true, false }, m_frame_count{ 0 }, m_animation_step{ 0.0f },
					m_current_frame{ 0 }, m_vertices_default{ nullptr },
					m_animation_vertices{ nullptr }, m_vertices_count{} {
			}
			Animation::Animation(const float& p_animation_length, const uint32_t& p_frame_count, const uint32_t& p_frame_size_x, Vertex_Data* p_vertices, const size_t& p_vertices_count, const bool& p_is_async) :
					m_keep_animating{ true }, m_is_async{ p_is_async }, m_start{ false }, m_end{ false }, m_frame_timer{ (p_animation_length / p_frame_count) * 1000, true, false }, m_frame_count{ p_frame_count },
					m_animation_step{ 0.0f }, m_current_frame{ 0 }, m_vertices_default{ nullptr },
					m_animation_vertices{ nullptr }, m_vertices_count{ p_vertices_count } {

				m_vertices_default = pw::Engine_Memory::Allocate<Vertex_Data>(p_vertices_count);
				m_animation_vertices = pw::Engine_Memory::Allocate<Vertex_Data>(p_vertices_count);

				m_animation_step = (float)(p_frame_size_x) / (float)(p_frame_count * (p_frame_size_x));

				for (size_t i = 0; i < m_vertices_count; i++) {
					m_animation_vertices[i].Set_Texture_Coord(p_vertices[i].Texture_Coord());
					m_vertices_default[i].Set_Texture_Coord(p_vertices[i].Texture_Coord());
				}
			}
			Animation::Animation(const float& p_animation_length, const uint32_t& p_frame_count, const uint32_t& p_frame_size_x, const bool& p_is_async) :
					m_keep_animating{ true }, m_is_async{ p_is_async }, m_start{ false }, m_end{ false }, m_frame_timer{ (p_animation_length / p_frame_count) * 1000, true, false },
					m_frame_count{ p_frame_count }, m_animation_step{ 0.0f },
					m_current_frame{ 0 }, m_vertices_default{ NULL },
					m_animation_vertices{ NULL }, m_vertices_count{ NULL } {

				m_animation_step = (float)(p_frame_size_x) / (float)(p_frame_count * (p_frame_size_x));
			}
			Animation::~Animation() {
				if (pw::Engine_Memory::Deallocate<st::Vertex_Data>(m_vertices_default) == false) {
					if (m_vertices_default != nullptr) {
						delete[] m_vertices_default;
						m_vertices_default = nullptr;
					}
				}
				if (pw::Engine_Memory::Deallocate<st::Vertex_Data>(m_animation_vertices) == false) {
					if (m_animation_vertices != nullptr) {
						delete[] m_animation_vertices;
						m_animation_vertices = nullptr;
					}
				}
			}
			Animation::Animation(const Animation& p_copy) :
					m_keep_animating{ p_copy.m_keep_animating }, m_is_async{ p_copy.m_is_async }, m_start{ p_copy.m_start }, m_end{ p_copy.m_end },
					m_frame_timer{ p_copy.m_frame_timer }, m_frame_count{ p_copy.m_frame_count }, m_animation_step{ p_copy.m_animation_step },
					m_current_frame{ p_copy.m_current_frame }, m_vertices_default{ p_copy.m_vertices_default }, m_animation_vertices{ p_copy.m_animation_vertices },
					m_vertices_count{ p_copy.m_vertices_count } {
			}
			Animation::Animation(const std::shared_ptr<Animation>& p_animation) : 
					Animation::Animation(*p_animation) {
			}
			void Animation::Change_Frame(bool p_render_call) {
				if (p_render_call == false) {
					if (m_is_async == true) {
						if (TRY_LINE m_vertices_default != nullptr) {
							if (m_frame_timer.Use() == true) {
								if (m_current_frame != m_frame_count && m_current_frame != 0) {
									for (size_t i = 0; i < m_vertices_count; i++) {
										m_animation_vertices[i].Set_Texture_Coord(glm::vec2(m_animation_vertices[i].Texture_Coord().x + m_animation_step, m_animation_vertices[i].Texture_Coord().y));
									}
									m_frame_timer.Reset();
									m_current_frame = m_current_frame + 1;
									m_start = false;
									if (m_frame_count == m_current_frame) {
										m_end = true;
									}
									else {
										m_end = false;
									}
								}
								else {
									m_end = false;
									Reset_Animation();
								}
							}
							else {
								m_start = false;
								m_end = false;
							}
						}
						else {
							throw pw::er::Warning_Error(L"Animation", L"vertices_default was nullptr", EXCEPTION_LINE, __FILEW__, L"Change_Frame");
						}
					}
				}
				else {
					if (m_is_async == false) {
						if (TRY_LINE m_vertices_default != nullptr) {
							if (m_frame_timer.Use() == true && m_keep_animating == true) {
								if (m_current_frame != m_frame_count && m_current_frame != 0) {
									for (size_t i = 0; i < m_vertices_count; i++) {
										m_animation_vertices[i].Set_Texture_Coord(glm::vec2(m_animation_vertices[i].Texture_Coord().x + m_animation_step, m_animation_vertices[i].Texture_Coord().y));
									}
									m_frame_timer.Reset();
									m_current_frame = m_current_frame + 1;
									m_start = false;
									if (m_frame_count == m_current_frame) {
										m_end = true;
									}
									else {
										m_end = false;
									}
								}
								else {
									m_end = false;
									Reset_Animation();
								}
							}
							else {
								m_start = false;
								m_end = false;
							}
						}
						else {
							throw pw::er::Warning_Error(L"Animation", L"vertices_default was nullptr", EXCEPTION_LINE, __FILEW__, L"Change_Frame");
						}
					}
				}
			}
			void Animation::Finish_Init(Vertex_Data* p_vertices, size_t p_vertices_count) {
				try {
					if (TRY_LINE p_vertices == nullptr) {
						throw pw::er::Warning_Error(L"Animation", L"vertices was nullptr", EXCEPTION_LINE, __FILEW__, L"Finish_Init");
					}
					m_vertices_default = pw::Engine_Memory::Allocate<Vertex_Data>(p_vertices_count);
					m_animation_vertices = pw::Engine_Memory::Allocate<Vertex_Data>(p_vertices_count);

					m_vertices_count = p_vertices_count;

					for (size_t i = 0; i < m_vertices_count; i++) {
						m_animation_vertices[i].Set_Texture_Coord(p_vertices[i].Texture_Coord());
						m_vertices_default[i].Set_Texture_Coord(p_vertices[i].Texture_Coord());
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			Vertex_Data* Animation::Vertices() {
				return m_animation_vertices;
			}
			void Animation::Reset_Animation() {
				m_start = true;
				for (size_t i = 0; i < m_vertices_count; i++) {
					m_animation_vertices[i].Set_Texture_Coord(glm::vec2(m_animation_step * m_vertices_default[i].Texture_Coord().x, m_vertices_default[i].Texture_Coord().y));
				}
				m_frame_timer.Reset();
				m_current_frame = 1;
			}
			void Animation::Advance_Frame() {
				if (TRY_LINE m_vertices_default != NULL) {
					if (m_current_frame != m_frame_count && m_current_frame != 0) {
						for (size_t i = 0; i < m_vertices_count; i++) {
							m_animation_vertices[i].Set_Texture_Coord(glm::vec2(m_animation_vertices[i].Texture_Coord().x + m_animation_step, m_animation_vertices[i].Texture_Coord().y));
						}
						m_frame_timer.Reset();
						m_current_frame = m_current_frame + 1;
						m_start = false;
						m_end = false;
					}
					else {
						m_end = true;
						Reset_Animation();
					}
				}
				else {
					throw pw::er::Warning_Error(L"Animation", L"vertices_default was nullptr", EXCEPTION_LINE, __FILEW__, L"Advance_Frame");
				}
			}
			void Animation::Start_Animation() {
				m_keep_animating = true;
			}
			void Animation::Stop_Animation() {
				m_keep_animating = false;
			}
			const bool& Animation::Start() {
				return m_start;
			}
			const bool& Animation::End() {
				return m_end;
			}
			const bool& Animation::Is_Async() {
				return m_is_async;
			}
		// End of Class Members
		// Animation_Structure
		// Static Declarations
		// Class Members
			Animation_Structure::Animation_Structure(st::Animation* p_animation) :
					m_animations{}, m_single_animation{ true }, m_current_access{ nullptr } {
					m_animations.insert(std::make_pair(L"SINGLE", std::make_tuple(p_animation, nullptr)));
			}
			Animation_Structure::Animation_Structure(const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids) :
						m_animations{}, m_single_animation{ false }, m_current_access{ p_animations.size() > 0 ? p_animations.at(0)._Get_rest()._Myfirst._Val : nullptr } {
				if (TRY_LINE p_animations.size() == p_animation_ids.size()) {
					for (size_t i = 0; i < p_animations.size(); i++) {
						m_animations.insert(std::make_pair(p_animation_ids.at(i), p_animations.at(i)));
					}
				}
				else {
					throw pw::er::Warning_Error(L"Animation_Structure", L"Animation count does not equal id count. Every animation must have an id.", EXCEPTION_LINE, __FILEW__, L"Animation_Structure");
				}
			}
			Animation_Structure::~Animation_Structure() {
				for (auto i = m_animations.begin(); i != m_animations.end(); i++) {
					if (pw::Engine_Memory::Deallocate<st::Animation>(std::get<0>(i->second)) == false) {
						if (std::get<0>(i->second) != nullptr) {
							delete std::get<0>(i->second);
							std::get<0>(i->second) = nullptr;
						}
					}
					if (m_current_access != std::get<1>(i->second)) {
						if (pw::Engine_Memory::Deallocate<st::Texture>(std::get<1>(i->second)) == false) {
							if (std::get<1>(i->second) != nullptr) {
								delete std::get<1>(i->second);
								std::get<1>(i->second) = nullptr;
							}
						}
					}
				}
				m_animations.clear();
			}
			std::tuple<st::Animation*, st::Texture*> Animation_Structure::Animation() const {
				if (m_single_animation == true) {
					return m_animations.at(L"SINGLE");
				}
				else {
					return std::move(std::tuple<st::Animation*, st::Texture*>());
				}
			}
			std::tuple<st::Animation*, st::Texture*> Animation_Structure::Animation(const std::wstring& p_animation_id) {
				auto v_found = m_animations.find(p_animation_id);
				if (v_found != m_animations.end()) {
					m_current_access = m_animations.at(p_animation_id)._Get_rest()._Myfirst._Val;
					return m_animations.at(p_animation_id);
				}
				else {
					return std::move(std::tuple<st::Animation*, st::Texture*>());
				}
			}
			std::map<std::wstring, std::tuple<st::Animation*, st::Texture*>>& Animation_Structure::Animations() {
				return m_animations;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////