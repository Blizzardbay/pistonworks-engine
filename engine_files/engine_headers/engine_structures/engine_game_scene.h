#ifndef H_GAME_SCENE
#define H_GAME_SCENE
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers 
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
//////////////////////////////////
// Project Headers          
//////////////////////////////////
// Engine Headers     
#include "ie_event.h"
#include "ie_model.h"
#include "ie_physics.h"
#include "ie_texture.h"
#include "ie_animation.h"
#include "ie_file_loader.h"
#include "engine_headers\engine_input.h"
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
		// Class Name: pw::ie::Scene_Model
		//																				 
		// Purpose: A name tag for Asset models and Actor models.
		//
		class PW_INTERNAL_API Scene_Model {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Function: Scene_Model::Render
			//
			// Purpose: Used to render the model being used, 
			//  also may be used for changing animation frames.
			//
			virtual PW_VOID Render();
			// Function: Scene_Model::Delete
			//
			// Purpose: Used to delete the class structure and
			//  delete all other allocated data.
			//
			virtual PW_VOID Delete();
			// Function: Scene_Model::Refresh
			//
			// Purpose: Used to refresh the model when some sort of
			//  update happens to the engine.
			//
			virtual PW_VOID Refresh();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
		};
		//////////////////////////////////
		// Class Name: pw::ie::Asset_Model
		//																				 
		// Purpose: A non-changing model that does not get updated
		//  frequently.
		//
		class PW_INTERNAL_API Asset_Model : public Scene_Model {
		// Default Class Structures 
		public:
			// Function: Asset_Model::Asset_Model
			//
			// Purpose: Used to initialize all class structures to
			//  default structures.
			//
			Asset_Model();
			// Function: Asset_Model::Asset_Model
			//
			// Purpose: Used to initialize all class structures to
			//  a given model and default structures.
			//
			Asset_Model(PW_SRD_PTR(Static_Model) model);
			// Function: Asset_Model::~Asset_Model
			//
			// Purpose: Used to deconstruct all allocated memory.
			//
			virtual ~Asset_Model();
		private:
		// Public Functions/Macros  
		public:
			// Function: Asset_Model::Render
			//
			// Purpose: Used to render the model to the screen.
			//
			PW_VOID Render();
			// Function: Asset_Model::Delete
			//
			// Purpose: Used to delete the model and 
			//  default class structures.
			//  
			PW_VOID Delete();
			// Function: Asset_Model::Refresh
			//
			// Purpose: Used to refresh the model's data
			//  after a update of some sort happens to the
			//  engine.
			//
			PW_VOID Refresh();
			// Function: Asset_Model::Model
			// Purpose: Return the model contained in this
			//  class.
			//
			Static_Model& Model();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_SRD_PTR(Static_Model) model;
		};
		//////////////////////////////////
		// Class Name: pw::ie::AAsset_Model
		//																				 
		// Purpose: A non-changing model that does not get updated
		//  frequently and has animations.
		//
		class PW_INTERNAL_API AAsset_Model : public Asset_Model {
		// Default Class Structures
		public:
			// Function: AAsset_Model::AAsset_Model
			//
			// Purpose: Used to initialize a static model with
			//  an animation.
			//
			AAsset_Model(PW_SRD_PTR(Static_Model) model, PW_SRD_PTR(Animation) animation);
			// Function: AAsset_Model::~AAsset_Model
			//
			// Purpose: Used to deallocate the class
			//  information
			//
			virtual ~AAsset_Model();
		private:
		// Public Functions/Macros  
		public:
			// Function: AAsset_Model::Render
			//
			// Purpose: Used to draw the model information to the screen
			//  and run the necessary animation information.
			//
			PW_VOID Render();
			// Function: AAsset_Model::Delete
			// Purpose: Used to delete the class structure's
			//  and models.
			//
			PW_VOID Delete();
			// Function: AAsset_Model::Refresh
			//
			// Purpose: Used to update the model and
			//  animation information when the engine
			//  updates in some way.
			//
			PW_VOID Refresh();
			// Function: AAsset_Model::Run_Animation
			//
			// Purpose: Used to update and change animation information.
			//
			PW_VOID Run_Animation();
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_SRD_PTR(Animation) animation;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Actor_Model
		//																				 
		// Purpose: A changing model that does get updated
		//  frequently. (IE. every frame)
		//
		class PW_INTERNAL_API Actor_Model : public Scene_Model {
		// Default Class Structures 
		public:
			// Function: Actor_Model::Actor_Model
			//
			// Purpose: Used to initialize the class
			//  structures.
			//
			Actor_Model();
			// Function: Actor_Model::Actor_Model
			//
			// Purpose: Used to initialize the class structures
			//  and initialize the model contained within.
			//
			Actor_Model(PW_SRD_PTR(Dynamic_Model) model);
			// Function: Actor_Model::~Actor_Model
			//
			// Purpose: Used to get rid of base class structures
			//  and deallocated allocated memory.
			//
			virtual ~Actor_Model();
		private:
		// Public Functions/Macros  
		public:
			// Function: Actor_Model::Render
			//
			// Purpose: Used to draw the model information to
			//  the screen.
			//
			PW_VOID Render();
			// Function: Actor_Model::Delete
			//
			// Purpose: Used to delete the model and
			// default class information.
			//
			PW_VOID Delete();
			// Function: Actor_Model::Refresh
			//
			// Purpose: Used to update model / class information
			//  when ever the engine updates in some sort of 
			//  way.
			//
			PW_VOID Refresh();
			// Function: Actor_Model::Set_Poly_Body
			//
			// Purpose: Used to set the body of the model to
			//  a new body / location of that body.
			//
			PW_VOID Set_Poly_Body(b2Body* poly_body);
			// Function: Actor_Model::Set_Event_ID
			// 
			// Purpose: Used to set a new event_id.
			//
			PW_VOID Set_Event_ID(PW_ID id);
			// Function: Actor_Model::Increment_ID_Index
			// 
			// Purpose: Used to increment the global id by 1
			//											    
			static PW_VOID Increment_ID_Index();
			// Function: Actor_Model::Model
			//
			// Purpose: Used to gain access to the actor's
			//  dynamic model.
			//
			Dynamic_Model& Model();
			// Function: Actor_Model::Event_ID
			//
			// Purpose: Returns the actor's event id.
			//  If the actor does not have a event id
			//  then it will return 0 which is the default non-value
			//  to be used.
			//
			PW_ID Event_ID() const;
			// Function: Actor_Model::Global_ID
			//
			// Purpose: Returns the current global id from the
			//  actor class. This global id is incremented per new event.
			//
			static const PW_ID Global_ID();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_SRD_PTR(Dynamic_Model) model;
			b2Body* poly_body;
			PW_ID event_id;
			static PW_ID global_index;
		};
		//////////////////////////////////
		// Class Name: pw::ie::AActor_Model
		//																				 
		// Purpose: A changing model that does get updated
		//  frequently with animations. (IE. every frame)
		//
		class PW_INTERNAL_API AActor_Model : public Actor_Model {
		// Default Class Structures 
		public:
			// Function: AActor_Model::AActor_Model
			//
			// Purpose: Used to initialize the actor's model and animation.
			//
			AActor_Model(PW_SRD_PTR(Dynamic_Model) model, PW_SRD_PTR(Animation) animation);
			// Function: AActor_Model::~AActor_Model
			//
			// Purpose: Used to deallocate memory allocated by
			// the actor model and the animation.
			//
			virtual ~AActor_Model();
		private:
		// Public Functions/Macros  
		public:
			// Function: AActor_Model::Render
			//
			// Purpose: Used to draw the actor model information to
			//  the screen and is also used to update animation information.
			//
			PW_VOID Render();
			// Function: AActor_Model::Delete
			//
			// Purpose: Used to delete the actor model data and animation. 
			//
			PW_VOID Delete();
			// Function: AActor_Model::Refresh
			//
			// Purpose: Used to refresh all data in the AActor_Model class
			//  when ever the engine is updated in any way.
			//
			PW_VOID Refresh();
			// Function: AActor_Model::Run_Animation
			//
			// Purpose: Used to update animation information
			// and change model texture information accordantly.
			//
			PW_VOID Run_Animation();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_SRD_PTR(Animation) animation;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Scene_Event
		//																				 
		// Purpose: A event that is triggered by a model
		//  event happening within a scene.
		//
		class PW_INTERNAL_API Scene_Event {
		// Default Class Structures 
		public:
			// Function: Scene_Event::Scene_Event
			//
			// Purpose: Used to initialize all scene event
			//  structures and variables.
			//
			Scene_Event(PW_SRD_PTR(Actor_Model) model_pointer, Model_Event model_event);
			// Function: Scene_Event::~Scene_Event
			//
			// Purpose: Used to deallocate all memory used 
			//  by this class.
			//
			~Scene_Event();
		private:
		// Public Functions/Macros 
		public:
			// Function: Scene_Event::Run_Event
			//
			// Purpose: Used when the event is trigger is some
			//  sort of way. This is determined by the Game_Scene class.
			//
			PW_VOID Run_Event();
			// Function: Scene_Event::Event
			//
			// Purpose: Returns the event for use.
			//
			Model_Event Event() const;
			// Function: Scene_Event::Model
			//
			// Purpose: Returns a pointer to the model tied to the event.
			//
			PW_SRD_PTR(Actor_Model) Model() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_SRD_PTR(Actor_Model) model;
			Model_Event model_event;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Game_Scene
		//																				 
		// Purpose: A class for handling scene drawing and texture
		//  drawing in a scene, as well as sound and other
		//	events.
		//
		class PW_INTERNAL_API Game_Scene {
		// Default Class Structures
		public:
			// Function: Game_Scene::Game_Scene
			//
			// Purpose: Used to initialize a scene.
			//
			Game_Scene(PW_CSTRING scene_name, std::vector<PW_SRD_PTR(Scene_Model)> scene_models, std::vector<PW_SRD_PTR(Actor_Model)> collision_models,
					Engine_Input* scene_input, std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, Scene_Event>>> scene_events,
					std::vector<PW_SRD_PTR(Scene_Event)> current_scene_events, Pysics_Factory* scene_physics);
			// Function: Game_Scene::~Game_Scene
			//
			// Purpose: Used to deallocate scenes and get rid of memory.
			//
			~Game_Scene();
		private:
		// Public Functions/Macros 
		public:
			// Function: Game_Scene::Render
			//
			// Purpose: Used to draw all members on to a screen.
			//
			PW_VOID Render();
			// Function: Game_Scene::Delete
			//
			// Purpose: Used to delete all of the related members
			//  within the scene and then delete the scene itself.
			//
			PW_VOID Delete();
			// Function: Game_Scene::Refresh_Scene
			//
			// Purpose: Used to refresh all of the scene members when
			//  ever the engine is updated.
			//
			PW_VOID Refresh_Scene();
			// Function: Game_Scene::Create_Event
			//
			// Purpose: Used to create an event that is tied to a model
			//  and triggers a function when it happens.
			//
			PW_VOID Create_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state, PW_SRD_PTR(Actor_Model) model_pointer, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
			// Function: Game_Scene::Scene
			//
			// Purpose: Returns a pointer to the scene
			//
			std::vector<PW_SRD_PTR(Scene_Model)> Scene() const;
			// Function: Game_Scene::Scene_Physics
			//
			// Purpose: Returns the physics simulated world
			//  that the scene owns.
			//
			Pysics_Factory* Scene_Physics();
			// Function: Game_Scene::Asset_Count
			//
			// Purpose: Returns asset count. Includes aasset.
			//
			static PW_INT Asset_Count();
			// Function: Game_Scene::Actor_Count
			//
			// Purpose: Returns the actor count. Includes aactor.
			//
			static PW_INT Actor_Count();
			// Function: Game_Scene::Activate_Event
			//
			// Purpose: Activates a event if the present information is correct.
			//
			PW_VOID Activate_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state);
			// Function: Game_Scene::Input
			//
			// Purpose: Returns a handle to the input class of this scene.
			//
			Engine_Input* Input();
		// Public Variables     
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			// General Scene Information
			PW_CSTRING scene_name;
			// Model Information
			std::vector<PW_SRD_PTR(Scene_Model)> scene_models;
			std::vector<PW_SRD_PTR(Actor_Model)> collision_models;
			// Input / Event Information
			Engine_Input* scene_input;

			std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, Scene_Event>>> scene_events;
			std::vector<PW_SRD_PTR(Scene_Event)> current_scene_events;
			// Physics ( If the scene has it in the first place )
			Pysics_Factory* scene_physics;
			// How many models are currently loaded
			static PW_INT global_asset_count;
			static PW_INT global_actor_count;
		};
		// Functions      
		// Macros / Definitions
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_GAME_SCENE
