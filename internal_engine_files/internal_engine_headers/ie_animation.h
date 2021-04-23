#ifndef H_IE_ANIMATION
#define H_IE_ANIMATION
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers    
#include <chrono>
#include <iomanip>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers 
#include "internal_engine_headers\ie_mesh.h"
//////////////////////////////////
// Engine Macro Includes  
#include "engine_headers\engine_error.h"
//////////////////////////////////
// Engine Macros           
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Internal Engine              //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		//////////////////////////////////
		// Class Name: pw::ie::Animation
		//
		// Purpose:  A base class for holding a base layout of
		// animations within the engine.
		//
		class PW_INTERNAL_API Animation {
		// Default Class Structures
		public:
			// Function: Animation::Animation
			//
			// Purpose: Used to initialize animation information
			// and data structures.
			//
			Animation(PW_FLOAT animation_length, PW_UINT frame_count, PW_UINT frame_size_x, ID_Vertex_Data* vertices, PW_SIZE vertices_count);
			//////////////////////////////////
			// Function: Animation::~Animation
			//
			// Purpose: Used to deallocate all animation information.
			//
			~Animation();
			//////////////////////////////////
			// Function: Animation::Animation
			//
			// Purpose: A standard copy constructor for animation information.
			//
			Animation(const Animation& copy);
			//////////////////////////////////
			// Function: Animation::Animation
			//
			// Purpose: A copy constructor for smart pointers.
			//
			Animation(const PW_SRD_PTR(Animation)& object);
		private:
		// Public Functions/Macros
		public:
			// Function: Animation::Change_Frame
			//
			// Purpose: Used to change the frame of the animation.
			//
			PW_VOID Change_Frame();
			// Function: Animation::Delete
			//
			// Purpose: Used to delete the current animation and 
			// all relevant data.
			//
			PW_VOID Delete();
			// Function: Animation::Vertices
			//
			// Purpose: Used to delete the current animation and 
			// all relevant data.
			//
			ID_Vertex_Data* Vertices();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
			// Function: Animation::Reset_Animation
			//
			// Purpose: Used to reset that animation back to its first frame.
			//
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

			PW_SRD_PTR(ID_Vertex_Data PW_SMART_ARRAY) vertices_default;
			PW_SRD_PTR(ID_Vertex_Data PW_SMART_ARRAY) animation_vertices;

			PW_SIZE vertices_count;
		};
		// Functions
		// Macros
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_ANIMATION
