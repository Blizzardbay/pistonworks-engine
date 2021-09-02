#ifndef H_IE_MESH
#define H_IE_MESH
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
		// PW_INTERNAL_DATA_API Class: pw::st::ID_Vertex_Data
		// //////////////////////////////////////////////////
		// Purpose:
		//  Holds the data for each vertex in the model. 
		// //////////////////////////////////////////////////
		struct PW_INTERNAL_DATA_API ID_Vertex_Data {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// PW_INTERNAL_DATA_API CLASS FUNCTION: ID_Vertex_Data::ID_Vertex_Data
			// //////////////////////////////////////////////////
			// Purpose:
			//  Initializes empty vertex data.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ID_Vertex_Data();
			// //////////////////////////////////////////////////
			// PW_INTERNAL_DATA_API CLASS FUNCTION: ID_Vertex_Data::ID_Vertex_Data
			// //////////////////////////////////////////////////
			// Purpose:
			//  Initializes vertex data using user given values.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord);
			// //////////////////////////////////////////////////
			// PW_INTERNAL_DATA_API CLASS FUNCTION: ID_Vertex_Data::~ID_Vertex_Data
			// //////////////////////////////////////////////////
			// Purpose:
			//  Clears allocated vertex data. 
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
			MUTATOR PW_VOID Set_Vertex_Position(glm::vec3 vertex_position);
			USER_INTERACTION
			MUTATOR PW_VOID Set_Texture_Coord(glm::vec2 texture_coord);
			USER_INTERACTION
			MUTATOR PW_VOID Set_Color_Data(glm::vec4 color_data);
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
			// (2) const PW_SUINT vertex_count;
			// Purpose: 
			//  The total count of the vertices.
			// (3) PW_UINT* indices;
			// Purpose: 
			//  The indices of the mesh. Used for texture
			//  coordinates. 
			// (4) const PW_SUINT indice_count;
			// Purpose:
			//  The total count of the indices. 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION Mesh(ID_Vertex_Data* vertices, const PW_SUINT vertex_count, PW_UINT* indices, const PW_SUINT indice_count);
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
			CLASS_FUNCTION PW_BOOL operator==(const Mesh& rhs);
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
			CORE PW_VOID Draw();
			// //////////////////////////////////////////////////
			// CORE Function: Mesh::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Deletes and frees the memory of the mesh.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE PW_VOID Delete();
			// Accessors
			USER_INTERACTION
			ACCESSOR ID_Vertex_Data* Vertices();
			USER_INTERACTION
			ACCESSOR PW_UINT Vertex_Count();
			// Mutators
			USER_INTERACTION
			MUTATOR PW_VOID Update_Vertices(ID_Vertex_Data* new_vertices);
			USER_INTERACTION
			MUTATOR PW_VOID Change_Color_Data(glm::vec4 new_color_data);
			USER_INTERACTION
			MUTATOR PW_VOID Change_Texture_Data(ID_Vertex_Data* new_texture_data);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			PW_SRD_PTR(ID_Vertex_Data*) vertices;

			PW_UINT draw_count;
			PW_UINT vertex_count;

			PW_UINT vertex_array_object;
			PW_UINT vertex_buffer_object;
			PW_UINT vertex_texture_object;
			PW_UINT vertex_color_object;
			PW_UINT vertex_element_object;
		};
		// Functions               
		// Macros / Definitions       
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_MESH