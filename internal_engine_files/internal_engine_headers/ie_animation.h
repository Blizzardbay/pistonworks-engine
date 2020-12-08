#ifndef H_IE_ANIMATION
#define H_IE_ANIMATION

//(DUAL_FILE)

/* C++ Headers              */
#include <chrono>
/* Project Headers          */
/* Engine Headers           */
#include "internal_engine_headers\ie_mesh.h"
#include "engine_headers\engine_constant.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (IE_Animation)                              ]
	 A base class for holding a base layout of 
	 animations within the engine.
	*/
	class IE_Animation {
/* Default Class Structures */
	public:
		IE_Animation();
		IE_Animation(PW_UINT animation_length, PW_UINT frame_count, PW_UINT frame_size_x);
		~IE_Animation() {}
	private:
/* Public Functions/Macros  */
	public:
		PW_VOID Change_Frame(ID_Vertex_Data*& vertices, PW_UINT size, ID_Vertex_Data* vertices_default);
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		// Animation time between frames
		PW_UINT animation_time;
		// The time at which the next frame plays
		std::chrono::system_clock::time_point activation_time;
		// The number of frames
		PW_UINT frame_count;
		// The step between frames
		PW_FLOAT animation_step;
		// This current frame
		PW_UINT current_frame;
		// The size of one frame.x
		PW_UINT frame_size_x;
	};
	/* Functions                */
	/* Macros                   */
}
#endif // !H_IE_ANIMATION
