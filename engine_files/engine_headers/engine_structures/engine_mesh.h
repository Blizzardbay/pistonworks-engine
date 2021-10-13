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
#ifndef H_ENGINE_MESH
#define H_ENGINE_MESH
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers      
#include <vector>
//////////////////////////////////
// Project Headers   
#include <GL\glew.h>
#include <glm\glm.hpp>
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
		// INTERNAL_DATA_API Class: pw::st::ID_Vertex_Data
		// //////////////////////////////////////////////////
		// Purpose:
		//  Holds the data for each vertex in the model. 
		// //////////////////////////////////////////////////
		struct INTERNAL_DATA_API ID_Vertex_Data {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// INTERNAL_DATA_API CLASS FUNCTION: ID_Vertex_Data::ID_Vertex_Data
			// //////////////////////////////////////////////////
			// Purpose:
			//  Initializes empty vertex data.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ID_Vertex_Data();
			// //////////////////////////////////////////////////
			// INTERNAL_DATA_API CLASS FUNCTION: ID_Vertex_Data::ID_Vertex_Data
			// //////////////////////////////////////////////////
			// Purpose:
			//  Initializes vertex data using user given values.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord);
			// //////////////////////////////////////////////////
			// INTERNAL_DATA_API CLASS FUNCTION: ID_Vertex_Data::~ID_Vertex_Data
			// //////////////////////////////////////////////////
			// Purpose:
			//  Clears allocated vertex data. 
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~ID_Vertex_Data();
		private:
		// Public Functions/Macros  
		public:
			// Accessors
			USER_INTERACTION
			ACCESSOR glm::vec3 Vertex_Position();
			USER_INTERACTION
			ACCESSOR glm::vec2 Texture_Coord();
			USER_INTERACTION
			ACCESSOR glm::vec4 Color_Data();
			// Mutators
			USER_INTERACTION
			MUTATOR void Set_Vertex_Position(glm::vec3 vertex_position);
			USER_INTERACTION
			MUTATOR void Set_Texture_Coord(glm::vec2 texture_coord);
			USER_INTERACTION
			MUTATOR void Set_Color_Data(glm::vec4 color_data);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			glm::vec3 vertex_position;
			glm::vec2 texture_coord;
			glm::vec4 color_data;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class: pw::st::Mesh
		// //////////////////////////////////////////////////
		// Purpose:
		//  Creates and send the vertex data to the shader. 
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Mesh {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Mesh::Mesh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates an empty mesh. Do not draw.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Mesh();
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Mesh::Mesh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Creates a mesh. A mesh's data may be changed at
			//  runtime.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) ID_Vertex_Data* vertices;
			// Purpose: 
			//  A pointer to all of the vertices in the mesh. 
			// (2) const uint16_t vertex_count;
			// Purpose: 
			//  The total count of the vertices.
			// (3) uint32_t* indices;
			// Purpose: 
			//  The indices of the mesh. Used for texture
			//  coordinates. 
			// (4) const uint16_t indice_count;
			// Purpose:
			//  The total count of the indices. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Mesh(ID_Vertex_Data* vertices, const uint16_t vertex_count, uint32_t* indices, const uint16_t indice_count);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Mesh::~Mesh
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deallocates memory contained by the mesh.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Mesh();
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Mesh::operator=
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Handles the copying of one mesh to another.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const Mesh& rhs;
			// Purpose:
			//  The other mesh to be copied to this mesh.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Mesh operator=(const Mesh& rhs);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Mesh::operator==
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Allows for the testing of a mesh's likeness to
			//  another.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const Mesh& rhs;
			// Purpose:
			//  The other mesh to be compared to this mesh.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION bool operator==(const Mesh& rhs);
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Mesh::Draw
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Draws the mesh.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Draw();
			// //////////////////////////////////////////////////
			// CORE Function: Mesh::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes and frees the memory of the mesh.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// Accessors
			USER_INTERACTION
			ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			ACCESSOR uint32_t Vertex_Count();
			// Mutators
			USER_INTERACTION
			MUTATOR void Update_Vertices(ID_Vertex_Data* new_vertices);
			USER_INTERACTION
			MUTATOR void Change_Color_Data(glm::vec4 new_color_data);
			USER_INTERACTION
			MUTATOR void Change_Texture_Data(ID_Vertex_Data* new_texture_data);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			PW_SRD_PTR(ID_Vertex_Data*) vertices;

			uint32_t draw_count;
			uint32_t vertex_count;

			uint32_t vertex_array_object;
			uint32_t vertex_buffer_object;
			uint32_t vertex_texture_object;
			uint32_t vertex_color_object;
			uint32_t vertex_element_object;
		};
		// Functions               
		// Macros / Definitions       
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_MESH