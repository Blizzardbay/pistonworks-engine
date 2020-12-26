#include "internal_engine_headers\ie_animation.h"

namespace pw {
	/* Ie_Default_Animation     */
	/* Static Declarations      */
	/* Class Members            */
	IE_Animation::IE_Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x, ID_Vertex_Data* vertices_default, PW_SIZE vertices_count, ID_Vertex_Data*& vertices) :
			activation_time(), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
			current_frame(0), vertices_default(nullptr), vertices(nullptr), vertices_count(vertices_count) {
		animation_step = (PW_FLOAT)(frame_size_x) / (PW_FLOAT)(frame_count * (frame_size_x));
		this->vertices_default = new ID_Vertex_Data[vertices_count];
		this->vertices = new ID_Vertex_Data[vertices_count];
		for (size_t i = 0; i < vertices_count; i++) {
			this->vertices_default[i] = vertices[i];
		}
		for (size_t i = 0; i < vertices_count; i++) {
			this->vertices[i] = vertices[i];
		}
	}
	ID_Vertex_Data* IE_Animation::Change_Frame() {
		if (activation_time <= Engine_Constant::Current_Time()) {
			if (current_frame != frame_count && current_frame != 0) {
				for (size_t i = 0; i < vertices_count; i++) {
					vertices[i].Set_Texture_Coord(glm::vec2(vertices[i].Texture_Coord().x + animation_step, vertices[i].Texture_Coord().y));
				}
				activation_time = Engine_Constant::Current_Time() + std::chrono::milliseconds((PW_INT)animation_time);
				current_frame++;
				return vertices;
			}
			else {
				Reset_Animation();
				return vertices;
			}
		}
		return vertices;
	}
	PW_VOID IE_Animation::Reset_Animation() {
		for (size_t i = 0; i < vertices_count; i++) {
			vertices[i].Set_Texture_Coord(glm::vec2(animation_step * vertices_default[i].Texture_Coord().x, vertices_default[i].Texture_Coord().y));
		}
		activation_time = Engine_Constant::Current_Time() + std::chrono::milliseconds((PW_INT)animation_time);
		current_frame = 1;
	}
}