#include "internal_engine_headers\ie_animation.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// Animation
		// Static Declarations
		// Class Members
			Animation::Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x, ID_Vertex_Data* vertices, PW_SIZE vertices_count) :
					activation_time(0), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
					current_frame(0), vertices_default(std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count])),
					animation_vertices(std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count])), vertices_count(vertices_count) {

				animation_step = (PW_FLOAT)(frame_size_x) / (PW_FLOAT)(frame_count * (frame_size_x));

				for (PW_SIZE i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
					(*vertices_default)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
				}
			}
			Animation::Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x) :
				activation_time(0), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
				current_frame(0), vertices_default(NULL),
				animation_vertices(NULL), vertices_count(NULL) {

				animation_step = (PW_FLOAT)(frame_size_x) / (PW_FLOAT)(frame_count * (frame_size_x));
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
			PW_VOID Animation::Change_Frame() {
				if (vertices_default != NULL) {
					if (activation_time <= Engine_Constant::Current_Time()) {
						if (current_frame != frame_count && current_frame != 0) {
							for (size_t i = 0; i < vertices_count; i++) {
								(*animation_vertices)[i].Set_Texture_Coord(glm::vec2((*animation_vertices)[i].Texture_Coord().x + animation_step, (*animation_vertices)[i].Texture_Coord().y));
							}
							activation_time = Engine_Constant::Current_Time() + ((1000 * (PW_INT)animation_time) / CLOCKS_PER_SEC);
							current_frame++;
						}
						else {
							Reset_Animation();
						}
					}
				}
			}
			PW_VOID Animation::Delete() {
				vertices_default.~shared_ptr();
				animation_vertices.~shared_ptr();
			}
			PW_VOID Animation::Finish_Init(ID_Vertex_Data* vertices, PW_SIZE vertices_count) {
				vertices_default = std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count]);
				animation_vertices = std::make_shared<ID_Vertex_Data*>(new ID_Vertex_Data[vertices_count]);
				this->vertices_count = vertices_count;

				for (PW_SIZE i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
					(*vertices_default)[i].Set_Texture_Coord(vertices[i].Texture_Coord());
				}
			}
			ID_Vertex_Data* Animation::Vertices() {
				return *animation_vertices;
			}
			PW_VOID Animation::Reset_Animation() {
				for (size_t i = 0; i < vertices_count; i++) {
					(*animation_vertices)[i].Set_Texture_Coord(glm::vec2(animation_step * (*vertices_default)[i].Texture_Coord().x, (*vertices_default)[i].Texture_Coord().y));
				}
				activation_time = Engine_Constant::Current_Time() + ((1000 * (PW_INT)animation_time) / CLOCKS_PER_SEC);
				current_frame = 1;
			}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////