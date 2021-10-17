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
#ifndef H_ENGINE_MODEL
#define H_ENGINE_MODEL
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers     
#include <cmath>
//////////////////////////////////
// Project Headers 
#include <glm\glm.hpp>
#include <box2d\b2_body.h>
//////////////////////////////////
// Engine Headers
#include "engine_structures\engine_mesh.h"
#include "engine_structures\engine_texture.h"
#include "engine_structures\engine_shader.h"
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
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Down_RS_Triangle
		// //////////////////////////////////////////////////
		// Purpose:
		//  Holds the data for a ID_Down_RS_Triangle.
		//    o TOP
		//   oo MIDDLE
		//  ooo BOTTOM
		//  Picture of triangle(o = triangle) 
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Down_RS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Down_RS_Triangle::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Down_RS_Triangle::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			static const uint16_t vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const uint16_t indices_size = 3;
			static uint32_t indices[3];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Down_LS_Triangle
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Down_LS_Triangle.
		//  o   TOP
		//  oo  MIDDLE
		//  ooo BOTTOM
		//  Picture of triangle(o = triangle)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Down_LS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Down_LS_Triangle::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Down_LS_Triangle::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables 
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const uint16_t indices_size = 3;
			static uint32_t indices[3];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Up_RS_Triangle
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Up_RS_Triangle.
		//  ooo TOP
		//   oo MIDDLE
		//    o BOTTOM
		//  Picture of triangle(o = triangle)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Up_RS_Triangle {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Up_RS_Triangle::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Up_RS_Triangle::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const uint16_t indices_size = 3;
			static uint32_t indices[3];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Up_LS_Triangle
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Up_LS_Triangle.
		//  ooo TOP
		//	oo  MIDDLE
		//	o   BOTTOM
		//	Picture of triangle(o = triangle)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Up_LS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Up_LS_Triangle::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Up_LS_Triangle::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables     
		private:
			static const uint16_t vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const uint16_t indices_size = 3;
			static uint32_t indices[3];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Square
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Square.
		//  ooo TOP
		//  ooo MIDDLE
		//  ooo BOTTOM
		//  Picture of square(o = square)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Square::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Square::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables  
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const uint16_t indices_size = 6;
			static uint32_t indices[6];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Hafe_RS_Square
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Hafe_RS_Square.
		//   oo TOP
		//   oo MIDDLE
		//   oo BOTTOM
		//  Picture of square(o = square)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Hafe_RS_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_RS_Square::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_RS_Square::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const uint16_t indices_size = 6;
			static uint32_t indices[6];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Hafe_LS_Square
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Hafe_LS_Square.
		//  oo  TOP
		//  oo  MIDDLE
		//  oo  BOTTOM
		//  Picture of square(o = square)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Hafe_LS_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_LS_Square::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_LS_Square::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables   
		private:
			static const uint16_t vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const uint16_t indices_size = 6;
			static uint32_t indices[6];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Hafe_UP_Square
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Hafe_UP_Square.
		//  ooo TOP
		//  ooo MIDDLE
		//  Picture of square(o = square)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Hafe_UP_Square {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros  
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_UP_Square::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_UP_Square::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const uint16_t vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const uint16_t indices_size = 6;
			static uint32_t indices[6];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Struct Name: pw::st::ID_Hafe_Down_Square
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  Holds the data for a ID_Hafe_Down_Square.
		//  ooo MIDDLE
		//  ooo BOTTOM
		//  Picture of square(o = square)
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API ID_Hafe_Down_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Accessors
			USER_INTERACTION
			static ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			static ACCESSOR uint32_t* Indices();
			USER_INTERACTION
			static ACCESSOR const uint16_t Vertices_Size();
			USER_INTERACTION
			static ACCESSOR const uint16_t Indices_Size();
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_Down_Square::Handle_Model_Data_NOC
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// //////////////////////////////////////////////////
			// CORE Function: ID_Hafe_Down_Square::Handle_Model_Data_C
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates the mesh for non-colored models.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) PW_SRD_PTR(Mesh)& model_mesh;
			// Purpose:
			//  The mesh that needs to be created.
			// (2) glm::vec4 model_color;
			// Purpose:
			//  The color of the mesh and or new color of the
			//  color.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			static const uint16_t vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const uint16_t indices_size = 6;
			static uint32_t indices[6];
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Enum Name: pw::st::Model_Types
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A structure that holds model type identifiers.
		// //////////////////////////////////////////////////
		enum class Mesh_Types {
			UNINIT,
			DOWN_RS_TRIANGLE,
			DOWN_LS_TRIANGLE,
			UP_RS_TRIANGLE,
			UP_LS_TRIANGLE,
			SQUARE,
			HAFE_RS_SQUARE,
			HAFE_LS_SQUARE,
			HAFE_UP_SQUARE,
			HAFE_DOWN_SQUARE,
			TYPE_COUNT
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A structure that ties static model's and dynamic
		//  models together.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Model {
			// Default Class Structures 
		public:
		private:
			// Public Functions/Macros  
		public:
			// Public Variables
			static uint64_t model_counter;
			static uint64_t model_id_assigner;
		public:
			// Private Functions/Macros 
		private:
			// Private Variables        
		private:
		};

		class PW_STRUCTURES_API Dynamic_Model;
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Static_Model
		// //////////////////////////////////////////////////																				 
		// Purpose:
		//  A structure that holds all data for a model. Does
		//  not update.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Static_Model : public Model {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Static_Model::Static_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Initializes the static model information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Static_Model();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Static_Model::Static_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a full static model, only
			//  updates once it is created and nevermore until
			//  window resize.
			//  Variation: NO-COLOR 
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (3) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (4) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (5) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Static_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Static_Model::Static_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a colored static model that only
			//  updates once it is created. May be updated on
			//  resize.
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (3) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (4) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (5) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// (6) glm::vec4 model_color;
			// Purpose:
			//  The color of the model. RGBA.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Static_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size, glm::vec4 model_color);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Static_Model::Static_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a full static model, only
			//  updates once it is created and nevermore until
			//  window resize.
			//  Variation: NO-COLOR 
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) ID_Vertex_Data* mesh_info;
			// Purpose:
			//  Specific non-engine data given to a mesh.
			// (3) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (4) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (5) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (6) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Static_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Static_Model::Static_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a colored static model that only
			//  updates once it is created. May be updated on
			//  resize. 
			// //////////////////////////////////////////////////
			// Parameters: 7
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) ID_Vertex_Data* mesh_info;
			// Purpose:
			//  Specific non-engine data given to a mesh.
			// (3) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (4) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (5) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (6) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// (7) glm::vec4 model_color;
			// Purpose:
			//  The color of the model. RGBA.
			// //////////////////////////////////////////////////
			USER_INTERACTION 
			CLASS_FUNCTION Static_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size, glm::vec4 model_color);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Static_Model::~Static_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates all of the static model memory. 
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Static_Model();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Static_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Renders the static model to the screen. 
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Static_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes active memory allocated for the model.
			//  Will not fully delete all memory until scope.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// Accessors
			USER_INTERACTION
			ACCESSOR glm::vec3 Position();
			USER_INTERACTION
			ACCESSOR glm::vec3& Position_Reference();
			USER_INTERACTION
			ACCESSOR Mesh_Types Model_Type();
			USER_INTERACTION
			ACCESSOR float Rotation();
			USER_INTERACTION
			ACCESSOR glm::vec2 Model_Size();
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(Mesh) Model_Mesh();
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(Mesh)& Model_Mesh_Reference();
			USER_INTERACTION
			ACCESSOR uint64_t Id();
		// Public Variables         
		public:
			static void(*model_functions_noc[(int32_t)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh);
			static void(*model_functions_c[(int32_t)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);

			static ID_Vertex_Data* model_vertices[(int32_t)Mesh_Types::TYPE_COUNT - 1];
			static const uint16_t model_vertices_count[(int32_t)Mesh_Types::TYPE_COUNT - 1];
			// //////////////////////////////////////////////////
			// CORE Function: Static_Model::Refresh_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Refreshes the model when the window is resized.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Refresh_Model();
		// Private Functions/Macros 
		private:
			// //////////////////////////////////////////////////
			// CORE Function: Static_Model::Handle_Calculations
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Calculates the position of the model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE glm::mat4 Handle_Calculations();
		// Private Variables        
		private:
			Mesh_Types model_type;
			PW_SRD_PTR(Mesh) model_mesh;
			Texture* model_texture;
			glm::vec4 model_color;
			int32_t model_is_colored;

			glm::vec3 model_position;
			glm::vec2 model_size;
			float model_rotation;

			glm::mat4 model_matrix;

			bool deleted;
			uint64_t id;
		};

		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Dynamic_Model
		// //////////////////////////////////////////////////																				 
		// Purpose: 
		//  A structure that holds all data for a
		//  model. Updates frequently.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Dynamic_Model : public Model {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Dynamic_Model::Dynamic_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a uninitialized Dynamic Model, with
			//  default values.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Dynamic_Model();
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Dynamic_Model::Dynamic_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a un-colored dynamic model. Updated
			//  every frame.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (3) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (4) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (5) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Dynamic_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Dynamic_Model::Dynamic_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a colored dynamic model. Updates every
			//  frame.
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (3) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (4) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (5) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// (6) glm::vec4 model_color;
			// Purpose:
			//  The color of the model. RGBA.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Dynamic_Model(Mesh_Types type, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size, glm::vec4 model_color);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Dynamic_Model::Dynamic_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a un-colored dynamic model. Updated every
			//  frame.
			// //////////////////////////////////////////////////
			// Parameters: 6
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) ID_Vertex_Data* mesh_info;
			// Purpose:
			//  Specific non-engine data given to a mesh.
			// (3) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (4) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (5) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (6) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Dynamic_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Dynamic_Model::Dynamic_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a colored dynamic model. Updates every
			//  frame.
			// //////////////////////////////////////////////////
			// Parameters: 7
			// (1) Mesh_Types type;
			// Purpose:
			//  The type of model to be created.
			// (2) ID_Vertex_Data* mesh_info;
			// Purpose:
			//  Specific non-engine data given to a mesh.
			// (3) Texture* texture;
			// Purpose:
			//  The texture for the model.
			// (4) glm::vec2 model_position;
			// Purpose:
			//  The in-game 2D coordinates of the top left of the
			// model.
			// (5) float model_rotation;
			//  The rotation of the model around its z-axis.
			//  Range(0.0f : 360.0f)
			// (6) glm::vec2 model_size;
			// Purpose:
			//  The size in screen pixels of the model in the 
			//  x and y direction.
			// (7) glm::vec4 model_color;
			// Purpose:
			//  The color of the model. RGBA.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Dynamic_Model(Mesh_Types type, ID_Vertex_Data* mesh_info, Texture* texture, glm::vec2 model_position, float model_rotation, glm::vec2 model_size, glm::vec4 model_color);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Dynamic_Model::~Dynamic_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates all memory used in the structure. 
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Dynamic_Model();
		private:
		// Public Functions/Macros  
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Renders the dynamic model to the screen. 
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			CORE void Render();
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Render
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Renders a dynamic model that is tied to a
			//  physics object.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) b2Body* model_body;
			// Purpose:
			//  The physics body of the model.
			// //////////////////////////////////////////////////
			CORE void Render(b2Body* model_body);
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes all memory allocated for this model.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			CORE void Delete();
			// Accessors
			USER_INTERACTION
			ACCESSOR glm::vec3 Position();
			USER_INTERACTION
			ACCESSOR glm::vec3& Position_Reference();
			USER_INTERACTION
			ACCESSOR glm::vec3 Last_Postition();
			USER_INTERACTION
			ACCESSOR glm::vec3& Last_Postition_Reference();
			USER_INTERACTION
			ACCESSOR Mesh_Types Model_Type();
			USER_INTERACTION
			ACCESSOR float Rotation();
			USER_INTERACTION
			ACCESSOR glm::vec2 Model_Size();
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(Mesh) Model_Mesh();
			USER_INTERACTION
			ACCESSOR PW_SRD_PTR(Mesh)& Model_Mesh_Reference();
			USER_INTERACTION
			ACCESSOR uint64_t Id();
			// Mutators
			USER_INTERACTION
			MUTATOR void Set_Model_Color(glm::vec4 new_model_color);
			USER_INTERACTION
			MUTATOR void Update_Position(glm::vec2 position);
			USER_INTERACTION
			MUTATOR void Update_Position(float x_pos, float y_pos);
			USER_INTERACTION
			MUTATOR void Set_Body_Pos(glm::vec2 body_pos);
			USER_INTERACTION
			MUTATOR void Set_Rotation(float new_rotation);
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Refresh_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Reloads the model. Called automatically on resize
			//	.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Refresh_Model();
		// Public Variables        
		public:
			static void(*model_functions_noc[(int32_t)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh);
			static void(*model_functions_c[(int32_t)Mesh_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh, glm::vec4 model_color);

			static ID_Vertex_Data* model_vertices[(int32_t)Mesh_Types::TYPE_COUNT - 1];
			static const uint16_t model_vertices_count[(int32_t)Mesh_Types::TYPE_COUNT - 1];
		// Private Functions/Macros 
		private:
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Handle_Calculations
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Converts engine screen information to world info.
			//  Called on refresh.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) bool dynamic_override;
			// Purpose: 
			//  The variable forces the re-calculation of the 
			//  models coords.
			// //////////////////////////////////////////////////
			CORE glm::mat4 Handle_Calculations(bool dynamic_override);
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Handle_Calculations
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Converts engine screen information to world info.
			//  Called if the dynamic model has a physics body.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) b2Body* model_body;
			// Purpose: 
			//  The physics body tied to the model.
			// //////////////////////////////////////////////////
			CORE glm::mat4& Handle_Calculations(b2Body* model_body);
			// //////////////////////////////////////////////////
			// CORE Function: Dynamic_Model::Handle_Calculations
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Converts engine screen information to world info.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			CORE glm::mat4& Handle_Calculations();
		// Private Variables      
		private:
			Mesh_Types model_type;
			PW_SRD_PTR(Mesh) model_mesh;
			Texture* model_texture;
			glm::vec4 model_color;
			int32_t model_is_colored;

			glm::vec3 model_position;
			glm::vec3 model_last_position;
			glm::vec2 model_size;
			float model_rotation;

			glm::vec2 last_body_pos;

			glm::mat4 model_matrix;

			bool deleted;
			uint64_t id;
		};
		// Functions                
		// Macros / Definitions
		#define PW_STATIC	0xf01
		#define PW_DYNAMIC	0xf02

		typedef int32_t PW_MODEL_TYPE;
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_MODEL