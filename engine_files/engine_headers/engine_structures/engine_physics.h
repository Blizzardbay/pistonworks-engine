// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_ENGINE_PHYSICS
#define H_ENGINE_PHYSICS
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
// +(MACRO)
#define B2_USER_SETTINGS
//////////////////////////////////
// C++ Headers              
#include <map>
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable:26495)
#pragma warning(push)
#pragma warning(disable:26812)
#include <box2d\b2_settings.h>
#include <box2d\b2_world.h>
#include <box2d\b2_collision.h>
#include <box2d\b2_polygon_shape.h>
#include <box2d\b2_body.h>
#include <box2d\b2_fixture.h>
#pragma warning(pop)
#pragma warning(pop)
//////////////////////////////////
// Engine Headers           
#include "engine_common\engine_error.h"
#include "engine_structures\engine_model.h"
//////////////////////////////////
// Engine Macro Includes    
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
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Pysics_Object
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  An object that has physics in the Box2D API.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Pysics_Object {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Pysics_Object::Pysics_Object
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a physics object tied to a model.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) PW_SRD_PTR(Dynamic_Model) model;
			// Purpose: 
			//  The model to integrate physics.
			// (2) b2BodyType type;
			// Purpose: 
			//  The type of physics object.
			// (3) b2World* world;
			// Purpose: 
			//  A pointer to the world in which this object will
			//  live.
			// (4) bool is_fixed;
			// Purpose: 
			//  Can the character be able to be rotated.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Pysics_Object(PW_SRD_PTR(Dynamic_Model) model, b2BodyType type, b2World* world, bool is_fixed);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Pysics_Object::~Pysics_Object
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates all the memory of the object.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Pysics_Object();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Pysics_Object::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes the allocated information with the
			//  structure.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Pysics_Object::X_Pixels_Position
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Returns the position in screen coordinates scaled
			//  by a scale factor. To get accurate position use
			//  PW_SCALE_FACTOR as your scale factor.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) int32_t scale_factor;
			// Purpose:
			//  Define what the engine should use as a standard
			//  tile.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE int32_t X_Pixels_Position(int32_t scale_factor = cm::Engine_Constant::PW_SCALE_FACTOR);
			// //////////////////////////////////////////////////
			// CORE Function: Pysics_Object::Y_Pixels_Position
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Returns the position in screen coordinates scaled
			//  by a scale factor. To get accurate position use
			//  PW_SCALE_FACTOR as your scale factor.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) int32_t scale_factor;
			// Purpose:
			//  Define what the engine should use as a standard
			//  tile.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE int32_t Y_Pixels_Position(int32_t scale_factor = cm::Engine_Constant::PW_SCALE_FACTOR);
			// Accessors
			USER_INTERACTION
			ACCESSOR b2Body* Body();
			USER_INTERACTION
			ACCESSOR b2Vec2 Size();
			// Mutators
			USER_INTERACTION
			MUTATOR void Set_Body(b2Body* body);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			// Body holds the shape and the fixture information
			b2Body* body;
			// Vertices for the shape
			PW_SRD_PTR(b2Vec2) shape_vertices;
			size_t vertex_count;
			// Fixture holds physics data such as
			// Friction    (0.0f -> 1.0f)
			// Restitution (0.0f - > 1.0f)
			// Density     (dynamic (any) static (inf))
			// Shape       (&b2PolygonShape)
			b2Vec2 model_size;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Pysics_Factory
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A factory for creation and running of the world.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Pysics_Factory {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Pysics_Factory::Pysics_Factory
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates an empty Box2D factory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Pysics_Factory();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Pysics_Factory::Pysics_Factory
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates an empty Box2D factory.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) b2Vec2 gravity;
			// Purpose: 
			//  The gravity the pulls downwards on the dynamic
			//  objects. The units is x,y m/s/s
			//  1m/s/s       = 32px/s/s
			//  0.03125m/s/s = 1px/s/s
			// (2) int32_t velocity_it;
			// Purpose: 
			//  The amount of velocity iterations.
			// (3) int32_t position_it;
			// Purpose: 
			//  The amount of position iterations.
			// (4) float time_step;
			// Purpose: 
			//  The max fps of the game screen.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Pysics_Factory(b2Vec2 gravity, int32_t velocity_it, int32_t position_it, float time_step);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Pysics_Factory::~Pysics_Factory
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates memory for the factory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Pysics_Factory();
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Pysics_Factory::Run
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Does mathematical calculations for the physics
			//  simulation.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Run();
			// //////////////////////////////////////////////////
			// CORE Function: Pysics_Factory::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes all memory allocated for the factory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
		// Public Variables         
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Pysics_Factory::Add_Object
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Adds an Pysics_Object to the factory.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) PW_SRD_PTR(Dynamic_Model) model;
			// Purpose: 
			//  The model which will be added.
			// (2) b2BodyType type;
			// Purpose: 
			//  The type of model to be added.
			// (3) PW_ID object_id;
			// Purpose: 
			//  The id of the physics object.
			// (4) bool is_fixed;
			// Purpose: 
			//  Will this object rotate when colliding.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Add_Object(PW_SRD_PTR(Dynamic_Model) model, b2BodyType type, PW_ID object_id = NULL, bool is_fixed = false);
			// //////////////////////////////////////////////////
			// ACCESSOR Function: Pysics_Factory::Access_Memeber
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Returns a pointer to a physics object with the
			//  given id. Returns nullptr if not found.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_ID id;
			// Purpose: 
			//  The id of the Pysics_Object you want to access.
			//  Returns nullptr if it does not find the object.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			ACCESSOR Pysics_Object* Access_Memeber(PW_ID id);
			// Accessors
			USER_INTERACTION
			ACCESSOR b2Body* Last_Added_Body();
			USER_INTERACTION
			ACCESSOR bool Current_Rect();
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			b2World* world;

			int32_t velocity_it;
			int32_t position_it;
			float time_step;

			b2Body* last_added_body;
			int32_t multiplier;
			bool current_rect;

			std::vector<Pysics_Object*> factory_static;
			std::map<PW_ID, Pysics_Object*> factory_dynamic;
		};
		// Functions               
		// Macros / Definitions                
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_PHYSICS