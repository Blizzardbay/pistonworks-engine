// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
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
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
// +(MACRO)
#define B2_USER_SETTINGS
//////////////////////////////////
// C++ Headers 
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <map>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <box2d\b2_settings.h>
#include <box2d\b2_contact.h>
#include <box2d\b2_world.h>
#include <box2d\b2_collision.h>
#include <box2d\b2_polygon_shape.h>
#include <box2d\b2_circle_shape.h>
#include <box2d\b2_body.h>
#include <box2d\b2_fixture.h>
#pragma warning (pop)         
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_model.h"
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
		class Physics_Object {
		// Default Class Structures 
		public:
			enum class Object_Type {
				POLYGON,
				CIRCLE
			};

			Physics_Object(st::Model* p_model, const b2BodyType& p_type, b2World* p_world, const bool& p_is_fixed, const float& p_friction, const float& p_restitution, const float& p_density, const Object_Type& p_polygon, const bool& p_is_sensor);
			~Physics_Object();
		private:
			// Public Functions/Macros  
		public:
			int32_t X_Pixels_Position(const int32_t& p_scale_factor = cm::Engine_Constant::PW_SCALE_FACTOR);

			int32_t Y_Pixels_Position(const int32_t& p_scale_factor = cm::Engine_Constant::PW_SCALE_FACTOR);

			b2Body* Body();

			const b2Vec2& Size();

			void Set_Size_Px(const b2Vec2& p_size_px);
			void Set_Size_M(const b2Vec2& p_size_m);

			void Set_Size_Px(const glm::vec2& p_size_px);
			void Set_Size_M(const glm::vec2& p_size_m);

			void Set_Body(b2Body* p_body);
			// Public Variables         
		public:
			// Private Functions/Macros 
		private:
			// Private Variables       
		private:
			// Body holds the shape and the fixture information
			b2Body* m_body;
			// Vertices for the shape
			b2Vec2* m_shape_vertices;
			uint32_t m_vertex_count;
			// Fixture holds physics data such as
			// Friction    (0.0f -> 1.0f)
			// Restitution (0.0f -> 1.0f)
			// Density     (dynamic (any) static (inf))
			// Shape       (&b2PolygonShape)
			b2Vec2 m_model_size;
			Object_Type m_body_type;

			float m_friction;
			float m_restitution;
			float m_density;

			b2Fixture* m_current_fixture;
		};
		class Physics_Factory {
		// Default Class Structures 
		public:
			Physics_Factory();
			Physics_Factory(const b2Vec2& p_gravity, const int32_t& p_velocity_it, const int32_t& p_position_it, const float& p_time_step);
			
			~Physics_Factory();
		private:
		// Public Functions/Macros 
		public:
			void Run();
		// Public Variables         
		public:
			void Add_Object(st::Model* p_model, const b2BodyType& p_type, const st::Physics_Object::Object_Type& p_polygon, const bool& p_is_sensor, const PW_ID& p_object_id = NULL, const bool& p_is_fixed = false, const float& p_friction = 0.0f, const float& p_restitution = 0.0f, const float& p_density = 0.0f);
			
			st::Physics_Object* Access_Memeber(const PW_ID& p_id);
			
			b2Body* Last_Added_Body();
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			b2World* m_world;

			int32_t m_velocity_it;
			int32_t m_position_it;
			float m_time_step;

			b2Body* m_last_added_body;

			std::vector<st::Physics_Object*> m_factory_static;
			std::map<PW_ID, st::Physics_Object*> m_factory_dynamic;
		};               
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_PHYSICS