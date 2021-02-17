#ifndef H_IE_ANIMATION
#define H_IE_ANIMATION

//(DUAL_FILE)

/* C++ Headers              */
#include <chrono>
#include <iomanip>
/* Project Headers          */
/* Engine Headers           */
#include "internal_engine_headers\ie_mesh.h"
#include "engine_headers\engine_constant.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
	/* Classes                  */
	//
		/* -Animation
		 A base class for holding a base layout of
		 animations within the engine.
		*/
		class Animation {
	/* Default Class Structures */
		public:
			Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x, ID_Vertex_Data* vertices_default, PW_SIZE vertices_count, ID_Vertex_Data*& vertices);
			~Animation() {}
		private:
	/* Public Functions/Macros  */
		public:
			ID_Vertex_Data* Change_Frame();
			PW_VOID Delete() { delete[] vertices_default; vertices_default = nullptr; delete[] vertices; vertices = nullptr; }
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
			PW_VOID Reset_Animation();
	/* Private Variables        */
		private:
			// Animation time between frames
			PW_FLOAT animation_time;
			// The time at which the next frame plays
			std::chrono::system_clock::time_point activation_time;
			// The number of frames
			PW_UINT frame_count;
			// The step between frames
			PW_FLOAT animation_step;
			// This current frame
			PW_UINT current_frame;

			ID_Vertex_Data* vertices_default;
			ID_Vertex_Data* vertices;

			PW_SIZE vertices_count;
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_ANIMATION
