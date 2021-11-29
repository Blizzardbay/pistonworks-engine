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
#ifndef H_GAME_HEADER
#define H_GAME_HEADER
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_FILE)
//////////////////////////////////
// C++ Headers 
//////////////////////////////////
// Project Headers         
//////////////////////////////////
// Engine Headers     
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
		class PW_STRUCTURES_API Scene_Model;
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Asset_Model
		// //////////////////////////////////////////////////																				 
		// Purpose: 
		//  A non-changing model that does not get updated
		//  frequently.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Asset_Model;
		// //////////////////////////////////////////////////
		// Class Name: pw::st::AAsset_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A non-changing model that does not get updated
		//  frequently and has animations.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API AAsset_Model;
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Actor_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A changing model that does get updated frequently
		//  .(IE. every frame)
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Actor_Model;
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::AActor_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A changing model that does get updated
		//  frequently with animations. (IE. every frame).
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API AActor_Model;
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Scene_Event
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A event that is triggered by a model event
		//  happening within a scene.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Scene_Event;
		// //////////////////////////////////////////////////
		// Class Name: pw::st::Game_Scene
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A class for handling scene drawing and texture
		//  drawing in a scene, as well as sound and other
		//	events.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Game_Scene;
		// Functions      
		// Macros / Definitions
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_GAME_HEADER
