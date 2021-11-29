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
// +(Disabled Warnings)
#pragma warning(push)
#pragma warning(disable:4172)
//////////////////////////////////
// C++ Headers 
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <unordered_set>
#include <algorithm>
//////////////////////////////////
// Project Headers
#include "Quadtree\Quadtree.h"          
//////////////////////////////////
// Engine Headers 
#include "engine_structures\engine_event.h"
#include "engine_structures\engine_model.h"
#include "engine_structures\engine_physics.h"
#include "engine_structures\engine_animation.h"
#include "engine_structures\engine_text.h"
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
			enum class Type_Identifier {
				NO_TYPE,
				ASSET_MODEL,
				AASSET_MODEL,
				ACTOR_MODEL,
				AACTOR_MODEL
			};
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
			// //////////////////////////////////////////////////
			// CORE Function: Scene_Model::Model_Identifier
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to find the type of model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			virtual CORE Type_Identifier Model_Identifier();
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
			CLASS_FUNCTION Asset_Model(PW_SRD_PTR(Static_Model) model, int32_t layer = 0);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Asset_Model::Asset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize all class structures to
			//  a given model and default structures.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Static_Model) model;
			// Purpose:
			//  The model that the asset will use.
			// (2) PW_SRD_PTR(Text) text;
			// Purpose:
			//  The text that will be displayed.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Asset_Model(PW_SRD_PTR(Static_Model) model, Text* text, int32_t layer = 0);
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
			// //////////////////////////////////////////////////
			// CORE Function: Asset_Model::Model_Identifier
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to find the type of model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE Type_Identifier Model_Identifier();
			// Accessors
			USER_INTERACTION
			ACCESSOR Static_Model& Model();
			USER_INTERACTION
			ACCESSOR st::Text* Text();
			USER_INTERACTION
			ACCESSOR int32_t Layer();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			PW_SRD_PTR(Static_Model) model;
			st::Text* m_text;
			// The layer the model will be drawn on.
			int32_t layer;
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
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION AAsset_Model();
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
			CLASS_FUNCTION AAsset_Model(PW_SRD_PTR(Static_Model) model, PW_SRD_PTR(Animation) animation, int32_t layer = 0);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: AAsset_Model::AAsset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the actor's model and
			//  animation.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_SRD_PTR(Static_Model) model;
			// Purpose:
			//  The model to be used for the structure. 
			// (2) std::vector<PW_SRD_PTR(st::Animation)> p_animations;
			// Purpose:
			//  The animations to go into the structure.
			// (3) std::vector<std::wstring> p_animation_ids;
			// Purpose:
			//  The id's of the animation in the order of the
			//  animations.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION AAsset_Model(PW_SRD_PTR(Static_Model) model, std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> p_animations, std::vector<std::wstring> p_animation_ids, int32_t layer = 0);
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
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Advance_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Forces the animation to the next frame.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Advance_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Start_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Makes the animation start to animate.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Start_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Stop_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Stops the animation from animating. Can still be
			//  advanced manually.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Stop_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: AAsset_Model::Model_Identifier
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to find the type of model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE Type_Identifier Model_Identifier();
			// Accessors
			USER_INTERACTION
			ACCESSOR st::Animation* Model_Animation();
		// Public Variables       		  
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			st::Animation* m_current_animation;
			Animation_Structure m_animations;
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
			CLASS_FUNCTION Actor_Model(PW_SRD_PTR(Dynamic_Model) model, int32_t layer = 0);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Actor_Model::Asset_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize all class structures to
			//  a given model and default structures.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Dynamic_Model) model;
			// Purpose:
			//  The model to be used.
			// (2) PW_SRD_PTR(Text) text;
			// Purpose:
			//  The text that will be displayed.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Actor_Model(PW_SRD_PTR(Dynamic_Model) model, Text* text, int32_t layer = 0);
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
			// //////////////////////////////////////////////////
			// CORE Function: Actor_Model::Model_Identifier
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to find the type of model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE Type_Identifier Model_Identifier();
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
			USER_INTERACTION
			ACCESSOR st::Text* Text();
			USER_INTERACTION
			ACCESSOR int32_t Layer();
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
			// This is a special string id used for accessing a specific model
			std::wstring s_id;
			// A pointer to possible text the structure may be covering.
			st::Text* m_text;
			// The layer the model will be drawn on.
			int32_t layer;
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
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION AActor_Model();
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
			CLASS_FUNCTION AActor_Model(PW_SRD_PTR(Dynamic_Model) model, PW_SRD_PTR(Animation) animation, int32_t layer = 0);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: AActor_Model::AActor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the actor's model and
			//  animation.
			// //////////////////////////////////////////////////
			// Parameters: 3
			// (1) PW_SRD_PTR(Dynamic_Model) model;
			// Purpose:
			//  The model to be used for the structure. 
			// (2) std::vector<PW_SRD_PTR(st::Animation)> p_animations;
			// Purpose:
			//  The animations to go into the structure.
			// (3) std::vector<std::wstring> p_animation_ids;
			// Purpose:
			//  The id's of the animation in the order of the
			//  animations.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION AActor_Model(PW_SRD_PTR(Dynamic_Model) model, std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> p_animations, std::vector<std::wstring> p_animation_ids, int32_t layer = 0);
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
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Advance_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Forces the animation to the next frame.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Advance_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Start_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Makes the animation start to animate.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Start_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Stop_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Stops the animation from animating. Can still be
			//  advanced manually.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Stop_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Change_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Stops the animation from animating. Can still be
			//  advanced manually.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const std::wstring&& p_animation_id;
			// Purpose:
			//  The Id of the other animation to change to.
			// (2) bool reset;
			// Purpose:
			//  Should we reset the animation when we change it.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Change_Animation(std::wstring p_animation_id, bool reset = true);
			// //////////////////////////////////////////////////
			// CORE Function: AActor_Model::Model_Identifier
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to find the type of model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE Type_Identifier Model_Identifier();
			// Accessors
			ACCESSOR st::Animation* Model_Animation();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			st::Animation* m_current_animation;
			Animation_Structure m_animations;
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
			CLASS_FUNCTION Scene_Event(Actor_Model* model_pointer, st::Event_Base* model_event);
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
			ACCESSOR st::Event_Base* Event() const;
			USER_INTERACTION
			ACCESSOR Actor_Model* Model() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			Actor_Model* m_model;
			st::Event_Base* m_model_event;
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
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Game_Scene();
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
			// CORE Function: Game_Scene::Pre_Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Updates render information before render.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Pre_Render();
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
			// (4) Actor_Model* model_pointer;
			// Purpose:
			//  A pointer to the model that has to be interacted
			//  with.
			// (5) PW_SRD_PTR(std::function<type(args...)>) trigger_function;
			// Purpose:
			//  The function that will be triggered on event
			//  trigger.
			// (6) bool play_once;
			// Purpose:
			//  Should the event be triggered continuously until
			//  the opposite trigger is activated. 
			// (7) args... p_arguments;
			// Purpose:
			//  The arguments for the function to be triggered. 
			// //////////////////////////////////////////////////
			// std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<PW_ID, st::Scene_Event>>>>
			NO_USER_INTERACTION
			template<class type, class ...args>
			CORE void Create_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state, Actor_Model* model_pointer, PW_SRD_PTR(std::function<type(args...)>) trigger_function, bool play_once, args... p_arguments) {
				if (scene_events.count(event_type) < 1) {
					std::map<PW_ID, Scene_Event> id_event = std::map<PW_ID, Scene_Event>();
					id_event.insert(std::make_pair(scene_id_counter, Scene_Event(model_pointer,
						pw::Engine_Memory::Allocate<st::Event<int, int, type, args...>>(st::Event<int, int, type, args...>(state, trigger_function, play_once, p_arguments...)))));

					scene_id_counter = scene_id_counter + 1;

					std::map<PW_STATE, std::map<PW_ID, Scene_Event>> state_event = std::map<PW_STATE, std::map<PW_ID, Scene_Event>>();
					state_event.insert(std::make_pair(state, id_event));

					std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<PW_ID, Scene_Event>>> button_event = std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<PW_ID, Scene_Event>>>();
					button_event.insert(std::make_pair(button, state_event));

					scene_events.insert(std::make_pair(event_type, button_event));
				}
				else {
					if (scene_events.at(event_type).count(button) < 1) {
						std::map<PW_ID, Scene_Event> id_event = std::map<PW_ID, Scene_Event>();
						id_event.insert(std::make_pair(scene_id_counter, Scene_Event(model_pointer,
							pw::Engine_Memory::Allocate<st::Event<int, int, type, args...>>(st::Event<int, int, type, args...>(state, trigger_function, play_once, p_arguments...)))));

						scene_id_counter = scene_id_counter + 1;

						std::map<PW_STATE, std::map<PW_ID, Scene_Event>> state_event = std::map<PW_STATE, std::map<PW_ID, Scene_Event>>();
						state_event.insert(std::make_pair(state, id_event));

						scene_events.at(event_type).insert(std::make_pair(button, state_event));
					}
					else {
						if (scene_events.at(event_type).at(button).count(state) < 1) {
							std::map<PW_ID, Scene_Event> id_event = std::map<PW_ID, Scene_Event>();
							id_event.insert(std::make_pair(scene_id_counter, Scene_Event(model_pointer,
								pw::Engine_Memory::Allocate<st::Event<int, int, type, args...>>(st::Event<int, int, type, args...>(state, trigger_function, play_once, p_arguments...)))));

							scene_id_counter = scene_id_counter + 1;

							scene_events.at(event_type).at(button).insert(std::make_pair(state, id_event));
						}
						else {
							scene_events.at(event_type).at(button).at(state).insert(std::make_pair(scene_id_counter,
								Scene_Event(model_pointer, pw::Engine_Memory::Allocate<st::Event<int, int, type, args...>>(st::Event<int, int, type, args...>(state, trigger_function, play_once, p_arguments...)))));

							scene_id_counter = scene_id_counter + 1;
						}
					}
				}
			}
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
			// (4) Actor_Model* model_pointer;
			// Purpose:
			//  A pointer to the model that has to be interacted
			//  with.
			// (6) bool play_once;
			// Purpose:
			//  Should the event be triggered continuously until
			//  the opposite trigger is activated. 
			// (7) std::_Mem_fn<function_type> function;
			// Purpose:
			//  A member function pointer to the function being
			//  executed.
			// (8) mem_class& object;
			// Purpose:
			//  The object the function is tied to.
			// (9) args... arguments;
			// Purpose:
			//  The arguments for the function.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			template<class function_type, class mem_class, class type, class ...args>
			CORE void Create_Event(PW_EVENT_ID event_type, PW_BUTTON_CODE button, PW_STATE state, Actor_Model* model_pointer, bool play_once, std::_Mem_fn<function_type> function, mem_class& object, args... arguments) {
				if (scene_events.count(event_type) < 1) {
					std::map<PW_ID, Scene_Event> id_event = std::map<PW_ID, Scene_Event>();
					id_event.insert(std::make_pair(scene_id_counter,
						Scene_Event(model_pointer, pw::Engine_Memory::Allocate<st::Event<function_type, mem_class, type, args...>>(st::Event<function_type, mem_class, type, args...>(state, play_once, function, object, arguments...)))));

					scene_id_counter = scene_id_counter + 1;

					std::map<PW_STATE, std::map<PW_ID, Scene_Event>> state_event = std::map<PW_STATE, std::map<PW_ID, Scene_Event>>();
					state_event.insert(std::make_pair(state, id_event));

					std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<PW_ID, Scene_Event>>> button_event = std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<PW_ID, Scene_Event>>>();
					button_event.insert(std::make_pair(button, state_event));

					scene_events.insert(std::make_pair(event_type, button_event));
				}
				else {
					if (scene_events.at(event_type).count(button) < 1) {
						std::map<PW_ID, Scene_Event> id_event = std::map<PW_ID, Scene_Event>();
						id_event.insert(std::make_pair(scene_id_counter,
							Scene_Event(model_pointer, pw::Engine_Memory::Allocate<st::Event<function_type, mem_class, type, args...>>(st::Event<function_type, mem_class, type, args...>(state, play_once, function, object, arguments...)))));

						scene_id_counter = scene_id_counter + 1;

						std::map<PW_STATE, std::map<PW_ID, Scene_Event>> state_event = std::map<PW_STATE, std::map<PW_ID, Scene_Event>>();
						state_event.insert(std::make_pair(state, id_event));

						scene_events.at(event_type).insert(std::make_pair(button, state_event));
					}
					else {
						if (scene_events.at(event_type).at(button).count(state) < 1) {
							std::map<PW_ID, Scene_Event> id_event = std::map<PW_ID, Scene_Event>();
							id_event.insert(std::make_pair(scene_id_counter,
								Scene_Event(model_pointer, pw::Engine_Memory::Allocate<st::Event<function_type, mem_class, type, args...>>(st::Event<function_type, mem_class, type, args...>(state, play_once, function, object, arguments...)))));

							scene_id_counter = scene_id_counter + 1;

							scene_events.at(event_type).at(button).insert(std::make_pair(state, id_event));
						}
						else {
							scene_events.at(event_type).at(button).at(state).insert(std::make_pair(scene_id_counter,
								Scene_Event(model_pointer, pw::Engine_Memory::Allocate<st::Event<function_type, mem_class, type, args...>>(st::Event<function_type, mem_class, type, args...>(state, play_once, function, object, arguments...)))));

							scene_id_counter = scene_id_counter + 1;
						}
					}
				}
			}
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
			CORE void Register_S_ID(std::wstring s_id, Actor_Model* model);
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Get_Box
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Returns the box that the model takes up.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) Scene_Model* p_model;
			// Purpose:
			//  The model to get the box from.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE quadtree::Box<float> Get_Box(Scene_Model* p_model);
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Re_Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Sets the first render parameter to true.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Re_Render();
			// //////////////////////////////////////////////////
			// CORE Function: Game_Scene::Re_Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Captures where the current camera position is
			//  for when the scene is re-rendered later.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) glm::vec2 camera_position;
			// Purpose:
			//  The camera's current position.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Capture_Instance(glm::vec2 camera_position);
			// Accessors
			USER_INTERACTION
			ACCESSOR COMPLEX_FUNCTION_3(PW_EVENT_ID, PW_BUTTON_CODE, PW_STATE) Event_Callback();
			USER_INTERACTION
			ACCESSOR Actor_Model& Access_Model(std::wstring s_id);
		    USER_INTERACTION
			ACCESSOR std::vector<PW_SRD_PTR(Scene_Model)> Scene() const;
			USER_INTERACTION
			ACCESSOR const size_t& Last_Render_Count() const;
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
			std::vector<Scene_Model*> render_queue;
			size_t m_last_render_count;
			std::vector<PW_SRD_PTR(Actor_Model)> collision_models;
			// We need to keep track of the models that have special id's
			std::map<std::wstring, Actor_Model*> s_id_models;
			// Input / Event Information
			co::Engine_Input* scene_input;

			std::map<PW_EVENT_ID, std::map<PW_BUTTON_CODE, std::map<PW_STATE, std::map<PW_ID, st::Scene_Event>>>> scene_events;
			std::vector<PW_SRD_PTR(st::Scene_Event)> current_scene_events;
			uint32_t scene_id_counter;
			// Physics ( If the scene has it in the first place )
			Pysics_Factory* scene_physics;

			// The game world will have 4 quadtree's to contain the models 
			quadtree::Quadtree<Scene_Model*, std::function<quadtree::Box<float>(Scene_Model*)>> quadrant_1;
			quadtree::Box<float> quadrant_1_box;
			quadtree::Quadtree<Scene_Model*, std::function<quadtree::Box<float>(Scene_Model*)>> quadrant_2;
			quadtree::Box<float> quadrant_2_box;
			quadtree::Quadtree<Scene_Model*, std::function<quadtree::Box<float>(Scene_Model*)>> quadrant_3;
			quadtree::Box<float> quadrant_3_box;
			quadtree::Quadtree<Scene_Model*, std::function<quadtree::Box<float>(Scene_Model*)>> quadrant_4;
			quadtree::Box<float> quadrant_4_box;

			// Layer Information
			// Bottom most is -3, Top most is 3
			// Camera following is 4
			
			// The scene can be changed from but when we return we need to do special coordinate
			// calculations for the layer 4 models
			// This will also be done for safety at the start of the scene's rendering anyways.
			bool re_render;

			glm::vec2 camera_position_instance;
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
