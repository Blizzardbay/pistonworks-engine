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
			Animation::Animation(float animation_length, uint32_t frame_count, uint32_t frame_size_x, ID_Vertex_Data* vertices, size_t vertices_count) :
					activation_time(0), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
					current_frame(0), vertices_default(std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count])),
					animation_vertices(std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count])), vertices_count(vertices_count) {

				animation_step = (float)(frame_size_x) / (float)(frame_count * (frame_size_x));

				for (size_t i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
					(*vertices_default)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
				}
			}
			Animation::Animation(float animation_length, uint32_t frame_count, uint32_t frame_size_x) :
				activation_time(0), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
				current_frame(0), vertices_default(NULL),
				animation_vertices(NULL), vertices_count(NULL) {

				animation_step = (float)(frame_size_x) / (float)(frame_count * (frame_size_x));
			}
			Animation::~Animation() {
			}
			Animation::Animation(const Animation& copy) :
					activation_time(copy.activation_time), animation_time(copy.animation_time), frame_count(copy.frame_count), animation_step(copy.animation_step),
					current_frame(0), vertices_default(copy.vertices_default), animation_vertices(copy.animation_vertices), vertices_count(copy.vertices_count) {
			}
			Animation::Animation(const PW_SRD_PTR(Animation)& animation) : 
					Animation::Animation(*animation) {
			}
			void Animation::Change_Frame() {
				if (vertices_default != NULL) {
					if (activation_time <= cm::Engine_Constant::Current_Time()) {
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
			}
			void Animation::Delete() {
				vertices_default.~shared_ptr();
				animation_vertices.~shared_ptr();
			}
			void Animation::Finish_Init(ID_Vertex_Data* vertices, size_t vertices_count) {
				vertices_default = std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count]);
				animation_vertices = std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count]);
				this->vertices_count = vertices_count;

				for (size_t i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
					(*vertices_default)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
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
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////