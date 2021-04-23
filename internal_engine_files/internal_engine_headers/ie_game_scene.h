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
		class Scene_Model {
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
		class Asset_Model : public Scene_Model {
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
		class AAsset_Model : public Asset_Model {
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
		class Actor_Model : public Scene_Model {
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
		class AActor_Model : public Actor_Model {
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
		class Scene_Event {
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
		// Class Name: pw::ie::Scene_Player
		//																				 
		// Purpose:  A static class for holding the player related
		//  data and variables.
		//
		class Scene_Player : Actor_Model {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Function: Scene_Player::Init_Player
			//
			// Purpose: Used to initialize the player information
			//  ,note that the player information may change between
			//  scene changes, but as the class is static most things will
			//  not change.
			//  Tied events to the player must be specially assigned either by the engine or
			//  by Scene_Player functions.
			//
			static PW_VOID Init_Player(PW_SRD_PTR(Dynamic_Model) player_model, b2Body* poly_body);
			// Function: Scene_Player::Render
			//
			// Purpose: Used to render the play on to the screen every frame
			//
			static PW_VOID Render();
			// Function: Scene_Player::Delete
			//
			// Purpose: Used to delete class structures and clean up
			//  physics body information.
			//
			static PW_VOID Delete();
			// Function: Scene_Player::Model
			//
			// Purpose: Returns the model of the player to the user.
			//
			static Actor_Model& Model();
			static PW_VOID Move_Right() { player_body->ApplyForceToCenter(b2Vec2(10.f,0.0f), true); }
			static PW_VOID Move_Left() { player_body->ApplyForceToCenter(b2Vec2(-10.f, 0.0f), true); }
			static PW_VOID Move_Up() { player_body->ApplyForceToCenter(b2Vec2(0.0f, 500.00f), true); }
			static PW_VOID Move_Down() { player_body->ApplyForceToCenter(b2Vec2(0.0f, -5.00f), true); }
			/* Public Variables         */
		public:
			/* Private Functions/Macros */
		private:
			/* Private Variables        */
		private:
			static Actor_Model model;
			static b2Body* player_body;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Game_Scene
		//																				 
		// Purpose: A class for handling scene drawing and texture
		//  drawing in a scene, as well as sound and other
		//	events.
		//
		class Game_Scene {
		// Default Class Structures
		public:
			// Function: Game_Scene::Game_Scene
			//
			// Purpose: Used to initialize a scene from a file location.
			//
			Game_Scene(PW_CSTRING file_location);
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
			// Function: Game_Scene::Load_Scene_From_String
			//
			// Purpose: Used to load a file loaded scene to real data.
			//
			std::vector<PW_SRD_PTR(Scene_Model)> Load_Scene_From_String(PW_STRING scene_str);
			// Function: Game_Scene::Load_Scene_From_File
			//
			// Purpose: Used to load a .pwsf from memory
			//
			//
			PW_STRING Load_Scene_From_File(PW_CSTRING file_location);
			// Function: Game_Scene::Create_Event
			//
			// Purpose: Used to create an event that is tied to a model
			//  and triggers a function when it happens.
			//
			PW_VOID Create_Event(PW_ID event_type, PW_SRD_PTR(Actor_Model) model_pointer, PW_SRD_PTR(PW_FUNCTION) trigger_function, PW_BOOL play_once);
			// Function: Game_Scene::Set_Order_Number
			//
			// Purpose: Used to set old order number to a new
			//  order number.
			//
			PW_VOID Set_Order_Number(PW_UINT new_order_number);
			// Function: Game_Scene::Order_Number
			//
			// Purpose: Returns the order number of the scene
			//
			PW_UINT Order_Number() const;
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
			// Function: Game_Scene::Player
			//
			// Purpose: Returns the player that the scene has.
			//
			static Scene_Player Player();
			// Function: Game_Scene::Asset_Count
			//
			// Purpose: Returns asset count. Includes aasset.
			//
			static PW_INT Asset_Count() { return global_asset_count; }
			// Function: Game_Scene::Actor_Count
			//
			// Purpose: Returns the actor count. Includes aactor.
			//
			static PW_INT Actor_Count() { return global_actor_count; }
		// Public Variables     
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			std::vector<PW_SRD_PTR(Scene_Model)> scene_models;
			std::vector<PW_SRD_PTR(Actor_Model)> collision_models;
			std::vector<PW_SRD_PTR(Scene_Event)> current_scene_events;

			std::map<PW_EVENT_ID, std::map<PW_ID, Scene_Event>> scene_events;

			Pysics_Factory scene_physics;

			PW_UINT order_number;

			static Scene_Player player;

			static PW_INT global_asset_count;
			static PW_INT global_actor_count;
		};
		// Functions      
		// Macros 
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_GAME_SCENE
