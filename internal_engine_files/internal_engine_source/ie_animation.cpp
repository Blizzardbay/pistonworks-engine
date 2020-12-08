#include "internal_engine_headers\ie_animation.h"

namespace pw {
	/* Ie_Default_Animation     */
	/* Static Declarations      */
	/* Class Members            */
	IE_Animation::IE_Animation() :
			activation_time(), animation_time(0), frame_count(0), animation_step(0.0f),
			current_frame(-1), frame_size_x(0) {
	}
	IE_Animation::IE_Animation(PW_UINT animation_length, PW_UINT frame_count, PW_UINT frame_size_x) :
			activation_time(), animation_time((animation_length / frame_count) * 1000), frame_count(frame_count), animation_step(0.0f),
			current_frame(-1), frame_size_x(frame_size_x) {
		animation_step = (PW_FLOAT)(frame_size_x + 1) / (PW_FLOAT)(frame_count * (frame_size_x + 1));
	}
	PW_VOID IE_Animation::Change_Frame(ID_Vertex_Data*& vertices, PW_UINT size, ID_Vertex_Data* vertices_default) {
		if (current_frame == 0) {
			for (size_t i = 0; i < size; i++) {
				vertices[i].Set_Texture_Coord(glm::vec2(animation_step * vertices->Texture_Coord().x, vertices->Texture_Coord().y));
			}
			activation_time = Engine_Constant::Current_Time() + std::chrono::milliseconds(animation_time);
			current_frame++;
		}
		if (activation_time <= Engine_Constant::Current_Time()) {
			if (current_frame != frame_count) {
				for (size_t i = 0; i < size; i++) {
					vertices[i].Set_Texture_Coord(glm::vec2(vertices[i].Texture_Coord().x + animation_step, vertices[i].Texture_Coord().y));
				}
				current_frame++;
				activation_time = Engine_Constant::Current_Time() + std::chrono::milliseconds(animation_time);
			}
			else {
				current_frame = 0;
				vertices = vertices_default;
			}
		}
	}
}