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
#include <unordered_set>
//////////////////////////////////
// Project Headers          
//////////////////////////////////
// Engine Headers     
#include "engine_structures\engine_event.h"
#include "engine_structures\engine_model.h"
#include "engine_structures\engine_physics.h"
#include "engine_structures\engine_animation.h"
#include "engine_control\engine_input.h"
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
		// PW_STRUCTURES_API Class Name: pw::st::Scene_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A template class for Asset models and Actor
		//  models.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Scene_Model {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Scene_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to render the model being used, 
			//  also may be used for changing animation frames.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Scene_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the class structure and
			//  delete all other allocated data.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Scene_Model::Refresh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to refresh the model when some sort of
			//  update happens to the engine.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CORE void Refresh();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Asset_Model
		// //////////////////////////////////////////////////																				 
		// Purpose: 
		//  A non-changing model that does not get updated
		//  frequently.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Asset_Model : public Scene_Model {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Asset_Model::Asset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize all class structures to
			//  default structures.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Asset_Model();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Asset_Model::Asset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize all class structures to
			//  a given model and default structures.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Static_Model) model;
			// Purpose:
			//  The model that the asset will use.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Asset_Model(PW_SRD_PTR(Static_Model) model);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Asset_Model::~Asset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to deconstruct all allocated memory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CLASS_FUNCTION ~Asset_Model();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Asset_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to render the model to the screen.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Asset_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the model and default class
			//  structures.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Asset_Model::Refresh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to refresh the model's data
			//  after a update of some sort happens to the
			//  engine.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Refresh();
			// Accessors
			ACCESSOR Static_Model& Model();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_SRD_PTR(Static_Model) model;
		};
		// //////////////////////////////////////////////////
		// Class Name: pw::st::AAsset_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A non-changing model that does not get updated
		//  frequently and has animations.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API AAsset_Model : public Asset_Model {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: AAsset_Model::AAsset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize a static model with
			//  an animation.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Static_Model) model;
			// Purpose:
			//  The model that the asset will use.
			// (2) PW_SRD_PTR(Animation) animation;
			// Purpose:
			//  The animation that the Asset will use.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION AAsset_Model(PW_SRD_PTR(Static_Model) model, PW_SRD_PTR(Animation) animation);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: AAsset_Model::~AAsset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to deallocate the class information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CLASS_FUNCTION ~AAsset_Model();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to draw the model information to the screen
			//  and run the necessary animation information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the class structure's and models.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Refresh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to update the model and animation
			//  information when the engine updates in some way.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Refresh();
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Run_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to update and change animation information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Run_Animation();
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_SRD_PTR(Animation) animation;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Actor_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A changing model that does get updated frequently
		//  .(IE. every frame)
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Actor_Model : public Scene_Model {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Actor_Model::Actor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the class structures.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Actor_Model();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Actor_Model::Actor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the class structures
			//  and initialize the model contained within.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Dynamic_Model) model;
			// Purpose:
			//  The model to be used.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Actor_Model(PW_SRD_PTR(Dynamic_Model) model);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Actor_Model::~Actor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to get rid of base class structures
			//  and deallocated allocated memory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CLASS_FUNCTION ~Actor_Model();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Actor_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to draw the model information to
			//  the screen.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Actor_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the model and
			//  default class information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Actor_Model::Refresh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to update model / class information
			//  when ever the engine updates in some sort of 
			//  way.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Refresh();
			// Mutators
			USER_INTERACTION
			MUTATOR void Set_Poly_Body(b2Body* poly_body);
			USER_INTERACTION
			MUTATOR void Set_Event_ID(PW_ID id);
			NO_USER_INTERACTION
			MUTATOR void Set_S_ID(std::wstring s_id);
			// Accessors
			USER_INTERACTION
			ACCESSOR Dynamic_Model& Model();
			USER_INTERACTION
			ACCESSOR PW_ID Event_ID() const;
			USER_INTERACTION
			ACCESSOR std::wstring* S_ID();
			// //////////////////////////////////////////////////
			// CORE Function: Actor_Model::Increment_ID_Index
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to increment the global id by 1.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Increment_ID_Index();
			// //////////////////////////////////////////////////
			// ACCESSOR Function: Actor_Model::Increment_ID_Index
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Returns the current global id from the
			//  actor class. This global id is incremented
			//  per new event.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static const ACCESSOR PW_ID Global_ID();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_SRD_PTR(Dynamic_Model) model;
			b2Body* poly_body;
			PW_ID event_id;
			std::wstring s_id; // This is a special string id used for accessing a specific model
			static PW_ID global_index;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::AActor_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A changing model that does get updated
		//  frequently with animations. (IE. every frame).
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API AActor_Model : public Actor_Model {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: AActor_Model::AActor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the actor's model and
			//  animation.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Dynamic_Model) model;
			// Purpose:
			//  The model to be used for the structure. 
			// (2) PW_SRD_PTR(Animation) animation;
			// Purpose:
			//  The animation to be used for the model.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION AActor_Model(PW_SRD_PTR(Dynamic_Model) model, PW_SRD_PTR(Animation) animation);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: AActor_Model::~AActor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to deallocate memory allocated by the actor
			//  model and the animation.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CLASS_FUNCTION ~AActor_Model();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to draw the actor model information to
			//  the screen and is also used to update animation
			//  information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the actor model data and animation
			//  .
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Refresh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to refresh all data in the AActor_Model
			//  class when ever the engine is updated in any way.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Refresh();
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Run_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to update animation information
			//  and change model texture information accordantly.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Run_Animation();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_SRD_PTR(Animation) animation;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Scene_Event
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A event that is triggered by a model event
		//  happening within a scene.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Scene_Event {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Scene_Event::Scene_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize all scene event
			//  structures and variables.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Actor_Model) model_pointer;
			// Purpose:
			//  The pointer to the model that the event triggers
			//  from.
			// (2) st::Event model_event;
			// Purpose:
			//  The event that will trigger upon a action.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Scene_Event(PW_SRD_PTR(Actor_Model) model_pointer, st::Event model_event);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Scene_Event::~Scene_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to deallocate all memory used 
			//  by this class.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Scene_Event();
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Scene_Event::Run_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used when the event is trigger is some
			//  sort of way. This is determined by the Game_Scene
			//  class.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			CORE void Run_Event();
			// Accessors
			USER_INTERACTION
			ACCESSOR st::Event Event() const;
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(Actor_Model) Model() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			PW_SRD_PTR(Actor_Model) model;
			st::Event model_event;
		};
		// //////////////////////////////////////////////////
		// Class Name: pw::st::Game_Scene
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A class for handling scene drawing and texture
		//  drawing in a scene, as well as sound and other
		//	events.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Game_Scene {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Game_Scene::Game_Scene
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize a scene.
			// //////////////////////////////////////////////////
			// Parameters: 7
			// (1) const wchar_t* scene_name;
			// Purpose:
			//  The name of the scene.
			// (2) std::vector<PW_SRD_PTR(Scene_Model)> scene_models;
			// Purpose:
			//  The models within the scene.
			// (3) std::vector<PW_SRD_PTR(Actor_Model)> collision_models;
			// Purpose:
			//  A vector of pointers to actor models that can collide.
			// (4) co::Engine_Input* scene_input;
			// Purpose:
			//  The input structure that controls the scene's input.
			// (5) std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, Scene_Event>>> scene_events;
			// Purpose:
			//  The events that the scene has.
			// (6) std::vector<PW_SRD_PTR(Scene_Event)> current_scene_events;
			// Purpose:
			//  The current scene events that are currently active.
			// (7) Pysics_Factory* scene_physics;
			// Purpose:
			//  The physics structure that controls physics for 
			//  the scene.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Game_Scene(const wchar_t* scene_name, std::vector<PW_SRD_PTR(Scene_Model)> scene_models, std::vector<PW_SRD_PTR(Actor_Model)> collision_models,
					co::Engine_Input* scene_input, Pysics_Factory* scene_physics);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Game_Scene::~Game_Scene
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to deallocate scenes and get rid of memory.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			~Game_Scene();
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to draw all members on to a screen.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete all of the related members
			//  within the scene and then delete the scene itself
			// .
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Refresh_Scene
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to refresh all of the scene members when
			//  ever the engine is updated.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Refresh_Scene();
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Create_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to create an event that is tied to a model
			//  and triggers a function when it happens.
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) PW_EVENT_ID event_type;
			// Purpose:
			//  The id of the pw event type.
			// (2) PW_BUTTON_CODE button;
			// Purpose:
			//  The button that has to be pressed in order for
			//  the event to trigger.
			// (3) PW_STATE state;
			// Purpose:
			//  The state of the button in order to trigger the
			//  event.
			// (4) PW_SRD_PTR(Actor_Model) model_pointer;
			// Purpose:
			//  A pointer to the model that has to be interacted
			//  with.
			// (5) PW_SRD_PTR(PW_FUNCTION) trigger_function;
			// Purpose:
			//  The function that will be triggered on event
			//  trigger.
			// (6) bool play_once;
			// Purpose:
			//  Should the event be triggered continuously until
			//  the opposite trigger is activated. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Create_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state, PW_SRD_PTR(Actor_Model) model_pointer, PW_SRD_PTR(PW_FUNCTION) trigger_function, bool play_once);
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Activate_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Activates a event if the present information is
			//  correct.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_EVENT_ID event_type;
			// Purpose:
			//  The id of the pw event type.
			// (2) PW_BUTTON_CODE button;
			// Purpose:
			//  The button that has to be pressed in order for
			//  the event to trigger.
			// (3) PW_STATE state;
			// Purpose:
			//  The state of the button in order to trigger the
			//  event.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Activate_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state);
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Activate_Event
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Activates a event if the present information is
			//  correct.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) std::wstring s_id;
			// Purpose:
			//  The new s_id to be tested.
			// (2) PW_SRD_PTR(Actor_Model) model;
			// Purpose:
			//  The model to register the id to.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Register_S_ID(std::wstring s_id, PW_SRD_PTR(Actor_Model) model);
			// Accessors
			USER_INTERACTION
			ACCESSOR COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) Event_Callback();
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(Actor_Model) Access_Model(std::wstring s_id);
		    USER_INTERACTION
			ACCESSOR std::vector<PW_SRD_PTR(Scene_Model)> Scene() const;
			USER_INTERACTION
			ACCESSOR Pysics_Factory* Scene_Physics();
			USER_INTERACTION
			ACCESSOR co::Engine_Input* Input();
			USER_INTERACTION
			ACCESSOR PW_FUNCTION Refresh_Scene_Callback();
			USER_INTERACTION
			static ACCESSOR int32_t Asset_Count();
			USER_INTERACTION
			static ACCESSOR int32_t Actor_Count();
		// Public Variables     
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			// General Scene Information
			const wchar_t* scene_name;
			// Model Information
			std::vector<PW_SRD_PTR(Scene_Model)> scene_models;
			std::vector<PW_SRD_PTR(Actor_Model)> collision_models;
			std::vector<PW_SRD_PTR(Actor_Model)> s_id_models; // We need to keep track of the models that have special id's
			std::unordered_set<std::wstring> s_ids; // We need to make sure that all of the s_ids are dissimilar
			// Input / Event Information
			co::Engine_Input* scene_input;

			std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, Scene_Event>>> scene_events;
			std::vector<PW_SRD_PTR(Scene_Event)> current_scene_events;
			// Physics ( If the scene has it in the first place )
			Pysics_Factory* scene_physics;
			// How many models are currently loaded
			static int32_t global_asset_count;
			static int32_t global_actor_count;
		};
		// Functions      
		// Macros / Definitions
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_GAME_SCENE
