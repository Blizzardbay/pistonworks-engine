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
					activation_time(0), animation_time(0), frame_count(0), animation_step(0.0f),
					current_frame(0), vertices_default(),
					animation_vertices(), vertices_count(), keep_animating(true) {
			}
			Animation::Animation(float animation_length, uint32_t frame_count, uint32_t frame_size_x, ID_Vertex_Data* vertices, size_t vertices_count) :
					activation_time(0), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
					current_frame(0), vertices_default(std::make_shared<ID_Vertex_Data*>(pw::Engine_Memory::Allocate<ID_Vertex_Data>(vertices_count))),
					animation_vertices(std::make_shared<ID_Vertex_Data*>(pw::Engine_Memory::Allocate<ID_Vertex_Data>(vertices_count))), vertices_count(vertices_count), keep_animating(true) {

				animation_step = (float)(frame_size_x) / (float)(frame_count * (frame_size_x));

				for (size_t i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
					(*vertices_default)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
				}
			}
			Animation::Animation(float animation_length, uint32_t frame_count, uint32_t frame_size_x) :
					activation_time(0), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
					current_frame(0), vertices_default(NULL),
					animation_vertices(NULL), vertices_count(NULL), keep_animating (true) {

				animation_step = (float)(frame_size_x) / (float)(frame_count * (frame_size_x));
			}
			Animation::~Animation() {
			}
			Animation::Animation(const Animation& copy) :
					activation_time(copy.activation_time), animation_time(copy.animation_time), frame_count(copy.frame_count), animation_step(copy.animation_step),
				current_frame(0), vertices_default(copy.vertices_default), animation_vertices(copy.animation_vertices), vertices_count(copy.vertices_count), keep_animating(copy.keep_animating) {
			}
			Animation::Animation(const PW_SRD_PTR(Animation)& animation) : 
					Animation::Animation(*animation) {
			}
			void Animation::Change_Frame() {
				if (TRY_LINE vertices_default != nullptr) {
					if (activation_time <= cm::Engine_Constant::Current_Time() && keep_animating == true) {
						if (current_frame != frame_count && current_frame != 0) {
							for (size_t i = 0; i < vertices_count; i++) {
								(*animation_vertices)[i].Set_Texture_Coord(glm::vec2((*animation_vertices)[i].Texture_Coord().x + animation_step, (*animation_vertices)[i].Texture_Coord().y));
							}
							activation_time = cm::Engine_Constant::Current_Time() + ((1000 * (int32_t)animation_time) / CLOCKS_PER_SEC);
							current_frame++;
						}
						else {
							Reset_Animation();
						}
					}
				}
				else {
					throw pw::er::Warning_Error(L"Animation", L"vertices_default was nullptr", std::move(EXCEPTION_LINE), __FILEW__, L"Change_Frame");
				}
			}
			void Animation::Delete() {
				pw::Engine_Memory::Deallocate<st::ID_Vertex_Data>(*vertices_default.get());
				vertices_default.~shared_ptr();
				pw::Engine_Memory::Deallocate<st::ID_Vertex_Data>(*animation_vertices.get());
				animation_vertices.~shared_ptr();
			}
			void Animation::Finish_Init(ID_Vertex_Data* vertices, size_t vertices_count) {
				try {
					if (TRY_LINE vertices == nullptr) {
						throw pw::er::Warning_Error(L"Animation", L"vertices was nullptr", std::move(EXCEPTION_LINE), __FILEW__, L"Finish_Init");
					}
					vertices_default = std::make_shared<ID_Vertex_Data*>(pw::Engine_Memory::Allocate<ID_Vertex_Data>(vertices_count));
					animation_vertices = std::make_shared<ID_Vertex_Data*>(pw::Engine_Memory::Allocate<ID_Vertex_Data>(vertices_count));
					this->vertices_count = vertices_count;

					for (size_t i = 0; i < vertices_count; i++) {
						(*animation_vertices)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
						(*vertices_default)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
					}
				}
				catch (const pw::er::Severe_Error& v_error) {
					throw v_error;
				}
				catch (const pw::er::Warning_Error& v_error) {
					throw v_error;
				}
			}
			ID_Vertex_Data* Animation::Vertices() {
				return *animation_vertices;
			}
			void Animation::Reset_Animation() {
				for (size_t i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(glm::vec2(animation_step * (*vertices_default)[i].Texture_Coord().x, (*vertices_default)[i].Texture_Coord().y));
				}
				activation_time = cm::Engine_Constant::Current_Time() + ((1000 * (int32_t)animation_time) / CLOCKS_PER_SEC);
				current_frame = 1;
			}
			void Animation::Advance_Frame() {
				if (TRY_LINE vertices_default != NULL) {
					if (current_frame != frame_count && current_frame != 0) {
						for (size_t i = 0; i < vertices_count; i++) {
							(*animation_vertices)[i].Set_Texture_Coord(glm::vec2((*animation_vertices)[i].Texture_Coord().x + animation_step, (*animation_vertices)[i].Texture_Coord().y));
						}
						activation_time = cm::Engine_Constant::Current_Time() + ((1000 * (int32_t)animation_time) / CLOCKS_PER_SEC);
						current_frame++;
					}
					else {
						Reset_Animation();
					}
				}
				else {
					throw pw::er::Warning_Error(L"Animation", L"vertices_default was nullptr", std::move(EXCEPTION_LINE), __FILEW__, L"Advance_Frame");
				}
			}
			void Animation::Start_Animation() {
				keep_animating = true;
			}
			void Animation::Stop_Animation() {
				keep_animating = false;
			}
			// Animation_Structure
		// Static Declarations
		// Class Memebers
			Animation_Structure::Animation_Structure(PW_SRD_PTR(st::Animation) p_animation) :
				m_animations{}, m_single_animation{ true }, m_current_access{ nullptr } {
				m_animations.insert(std::make_pair(L"SINGLE", std::make_tuple(p_animation, nullptr)));
			}
			Animation_Structure::Animation_Structure(std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> p_animations, std::vector<std::wstring> p_animation_ids) :
				m_animations{}, m_single_animation{ false }, m_current_access{ p_animations.size() > 0 ? p_animations.at(0)._Get_rest()._Myfirst._Val : nullptr } {
				if (TRY_LINE p_animations.size() == p_animation_ids.size()) {
					for (size_t i = 0; i < p_animations.size(); i++) {
						m_animations.insert(std::make_pair(p_animation_ids.at(i), p_animations.at(i)));
					}
				}
				else {
					throw pw::er::Warning_Error(L"Animation_Structure", L"Animation count does not equal id count. Every animation must have an id.", std::move(EXCEPTION_LINE), __FILEW__, L"Animation_Structure");
				}
			}
			void Animation_Structure::Delete() {
				if (m_single_animation == true) {
					m_animations.at(L"SINGLE")._Myfirst._Val.get()->Delete();
					pw::Engine_Memory::Deallocate<st::Animation>(m_animations.at(L"SINGLE")._Myfirst._Val.get(), true);
				}
				else {
					for (auto i = m_animations.begin(); i != m_animations.end(); i++) {
						i->second._Myfirst._Val.get()->Delete();
						if (i->second._Get_rest()._Myfirst._Val != m_current_access) {
							i->second._Get_rest()._Myfirst._Val->Delete();
							pw::Engine_Memory::Deallocate<st::Texture>(i->second._Get_rest()._Myfirst._Val);
						}
						pw::Engine_Memory::Deallocate<st::Animation>(i->second._Myfirst._Val.get(), true);
					}
				}
				m_animations.clear();
			}
			const std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>& Animation_Structure::Animation() const {
				if (m_single_animation == true) {
					return m_animations.at(L"SINGLE");
				}
				else {
					return std::move(std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>());
				}
			}
			const std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>& Animation_Structure::Animation(const std::wstring&& p_animation_id) {
				auto v_found = m_animations.find(p_animation_id);
				if (v_found != m_animations.end()) {
					m_current_access = m_animations.at(p_animation_id)._Get_rest()._Myfirst._Val;
					return m_animations.at(p_animation_id);
				}
				else {
					return std::move(std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>());
				}
			}
			// End of Class Members
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////