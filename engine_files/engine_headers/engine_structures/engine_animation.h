#ifndef H_IE_ANIMATION
#define H_IE_ANIMATION
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers    
#include <chrono>
#include <iomanip>
#include <fstream>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers 
#include "engine_structures\engine_mesh.h"
#include "engine_structures\engine_texture.h"
//////////////////////////////////
// Engine Macro Includes  
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Macros           
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes
		
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class: pw::st::Animation
		// //////////////////////////////////////////////////
		// Purpose:
		//  A base class for holding a base layout of
		//  animations within the engine.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Animation {
		// Default Class Structures
		public:
			// Function: Animation::Animation
			//
			// Purpose: Used to initialize animation information
			// and data structures.
			//
			USER_INTERACTION
			Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x, ID_Vertex_Data* vertices, PW_SIZE vertices_count);
			// Function: Animation::Animation
			//
			// Purpose: Used to initialize animation information
			// and data structures. Cannot be animated.
			//
			USER_INTERACTION
			Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x);
			//////////////////////////////////
			// Function: Animation::~Animation
			//
			// Purpose: Used to deallocate all animation information.
			//
			NO_USER_INTERACTION
			~Animation();
			//////////////////////////////////
			// Function: Animation::Animation
			//
			// Purpose: A standard copy constructor for animation information.
			//
			USER_INTERACTION
			Animation(const Animation& copy);
			//////////////////////////////////
			// Function: Animation::Animation
			//
			// Purpose: A copy constructor for smart pointers.
			//
			USER_INTERACTION
			Animation(const PW_SRD_PTR(Animation)& object);
		private:
		// Public Functions/Macros
		public:
			// Function: Animation::Change_Frame
			//
			// Purpose: Used to change the frame of the animation.
			//
			NO_USER_INTERACTION
			PW_VOID Change_Frame();
			// Function: Animation::Delete
			//
			// Purpose: Used to delete the current animation and 
			// all relevant data.
			//
			NO_USER_INTERACTION
			PW_VOID Delete();
			// Function: Animation::Change_Frame
			//
			// Purpose: If a animation is loaded from a gif or other file type,
			//  in the engine we cannot directly create a model of a known type for it
			//  so the work around is to init the animation after the model is created.
			//
			NO_USER_INTERACTION
			PW_VOID Finish_Init(ID_Vertex_Data* vertices, PW_SIZE vertices_count);
			// Function: Animation::Vertices
			//
			// Purpose: Used to delete the current animation and 
			// all relevant data.
			//
			USER_INTERACTION
			ID_Vertex_Data* Vertices();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
			// Function: Animation::Reset_Animation
			//
			// Purpose: Used to reset that animation back to its first frame.
			//
			NO_USER_INTERACTION
			PW_VOID Reset_Animation();
		// Private Variables 
		private:
			// Animation time between frames
			PW_FLOAT animation_time;
			// The time at which the next frame plays
			std::clock_t activation_time;
			// The number of frames
			PW_UINT frame_count;
			// The step between frames
			PW_FLOAT animation_step;
			// This current frame
			PW_UINT current_frame;

			PW_SRD_PTR(ID_Vertex_Data*) vertices_default;
			PW_SRD_PTR(ID_Vertex_Data*) animation_vertices;

			PW_SIZE vertices_count;
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_ANIMATION
