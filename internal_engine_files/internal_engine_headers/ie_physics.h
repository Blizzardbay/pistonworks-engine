#ifndef H_IE
#define H_IE
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
#include <box2d\b2_settings.h>
#include <box2d\b2_world.h>
#include <box2d\b2_collision.h>
#include <box2d\b2_polygon_shape.h>
#include <box2d\b2_body.h>
#include <box2d\b2_fixture.h>
//////////////////////////////////
// Engine Headers           
#include "engine_headers\engine_constant.h"
#include "internal_engine_headers\ie_model.h"
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
	// Internal Engine              //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		//////////////////////////////////
		// Class Name: pw::ie::Pysics_Object
		//																				 
		// Purpose: An object that has physics in the Box2D API.
		//
		class Pysics_Object {
		// Default Class Structures 
		public:
			// Function: Pysics_Object::Pysics_Object
			//
			// Purpose: Creates a Box2D API usable object. Note
			//  the object cannot be used itself but the body within.
			//
			Pysics_Object(PW_SRD_PTR(Dynamic_Model) model, b2BodyType type, b2World* world, PW_BOOL is_fixed);
			// Function: Pysics_Object::~Pysics_Object
			//
			// Purpose: Deallocates all the memory of the object.
			//
			~Pysics_Object();
		private:
		// Public Functions/Macros  
		public:
			// Function: Pysics_Object::Delete
			//
			// Purpose: Deletes the allocated information with the structure. 
			//
			PW_VOID Delete();
			// Function: Pysics_Object::X_Pixels_Position
			//
			// Purpose: Returns the position in screen coordinates scaled by a scale factor.
			//  To get accurate position use PW_SCALE_FACTOR as your scale factor.
			//
			PW_INT X_Pixels_Position(PW_INT scale_factor = Engine_Constant::PW_SCALE_FACTOR);
			// Function: Pysics_Object::Y_Pixels_Position
			//
			// Purpose: Returns the position in screen coordinates scaled by a scale factor.
			//  To get accurate position use PW_SCALE_FACTOR as your scale factor.
			//
			PW_INT Y_Pixels_Position(PW_INT scale_factor = Engine_Constant::PW_SCALE_FACTOR);
			// Function: Pysics_Object::Body
			//
			// Purpose: Returns body of the physics object.
			//
			b2Body* Body();
			// Function: Pysics_Object::Size
			//
			// Purpose: Returns the size of the physics object.
			//
			b2Vec2 Size();
			// Function: Pysics_Object::Set_Body
			//
			// Purpose: Sets the body of the physics object.
			//
			PW_VOID Set_Body(b2Body* body);
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
			PW_SIZE vertex_count;
			// Fixture holds physics data such as
			// Friction    (0.0f -> 1.0f)
			// Restitution (0.0f - > 1.0f)
			// Density     (dynamic (any) static (inf))
			// Shape       (&b2PolygonShape)
			b2Vec2 model_size;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Pysics_Factory
		//																				 
		// Purpose: A factory for creation and running of the world.
		//
		class Pysics_Factory {
		// Default Class Structures 
		public:
			// Function: Pysics_Factory::Pysics_Factory
			//
			// Purpose: Creates an empty Box2D factory.
			//
			Pysics_Factory(b2Vec2 gravity, PW_INT velocity_it, PW_INT position_it, PW_FLOAT time_step);
			// Function: Pysics_Factory::~Pysics_Factory
			//
			// Purpose: Deallocates memory for the factory.
			//
			~Pysics_Factory();
		private:
		// Public Functions/Macros 
		public:
			// Function: Pysics_Factory::Run
			//
			// Purpose: Does mathematical calculations for the physics simulation.
			//
			PW_VOID Run();
			// Function: Pysics_Factory::Delete
			//
			// Purpose: Deletes all memory allocated for the factory.
			//
			PW_VOID Delete();
		// Public Variables         
		public:
			// Function: Pysics_Factory::Add_Object
			//
			// Purpose: Adds an Pysics_Object to the factory.
			//
			PW_VOID Add_Object(PW_SRD_PTR(Dynamic_Model) model, b2BodyType type, PW_ID object_id = NULL, PW_BOOL is_fixed = false);
			// Function: Pysics_Factory::Access_Memeber
			//
			// Purpose: Returns the member accessed.
			//
			Pysics_Object* Access_Memeber(PW_ID id);
			// Function: Pysics_Factory::Last_Added_Body
			//
			// Purpose: Returns the last body added.
			//
			b2Body* Last_Added_Body();
			// Function: Pysics_Factory::Current_Rect
			//
			// Purpose: Returns if a body is a rectangle or not.
			//
			PW_BOOL Current_Rect();
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			b2World world;

			PW_INT velocity_it;
			PW_INT position_it;
			PW_FLOAT time_step;

			b2Body* last_added_body;
			PW_INT multiplier;
			PW_BOOL current_rect;

			std::vector<Pysics_Object*> factory_static;
			std::map<PW_ID, Pysics_Object*> factory_dynamic;
		};
		// Functions               
		// Macros                 
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE