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
#include <glm/glm.hpp>
//////////////////////////////////
// Engine Headers  
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
		// Struct Name: pw::ie::ID_Vertex_Data
		//																				 
		// Purpose: Holds the data for each vertex in the model.
		//
		struct ID_Vertex_Data {
		// Default Class Structures 
		public:
			// Function: ID_Vertex_Data::ID_Vertex_Data
			//
			// Purpose: Initializes empty vertex data.
			//
			ID_Vertex_Data();
			// Function: ID_Vertex_Data::ID_Vertex_Data
			//
			// Purpose: Initializes vertex data using user given values.
			//
			ID_Vertex_Data(const glm::vec3& vertex_position, const glm::vec2& texture_coord);
			// Function: ID_Vertex_Data::~ID_Vertex_Data
			//
			// Purpose: Clears allocated vertex data.
			//
			~ID_Vertex_Data();
		private:
		// Public Functions/Macros  
		public:
			// Function: ID_Vertex_Data::Set_Vertex_Position
			//
			// Purpose: Sets the vertex position.
			//
			PW_VOID Set_Vertex_Position(glm::vec3 vertex_position);
			// Function: ID_Vertex_Data::Set_Texture_Coord
			//
			// Purpose: Sets the texture drawing coordinate's position.
			//
			PW_VOID Set_Texture_Coord(glm::vec2 texture_coord);
			// Function: ID_Vertex_Data::Set_Color_Data
			//
			// Purpose: Sets the color data of the mesh. If the
			//  mesh is un-colored the shader will not change this mesh.
			//
			PW_VOID Set_Color_Data(glm::vec3 color_data);
			// Function: ID_Vertex_Data::Vertex_Position
			//
			// Purpose: Returns the vertex position.
			//
			glm::vec3 Vertex_Position();
			// Function: ID_Vertex_Data::Texture_Coord
			//
			// Purpose: Returns the texture coordinates.
			//
			glm::vec2 Texture_Coord();
			// Function: ID_Vertex_Data::Color_Data
			//
			// Purpose: Returns the color data for the mesh. 
			//
			glm::vec3 Color_Data();
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			glm::vec3 vertex_position;
			glm::vec2 texture_coord;
			glm::vec3 color_data;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Mesh
		//																				 
		// Purpose: Creates and send the vertex data to the
		//  shader.
		//
		class Mesh {
		// Default Class Structures 
		public:
			// Function: Mesh::Mesh
			//
			// Purpose: Creates an empty mesh. Do not draw.
			//
			Mesh();
			// Function: Mesh::Mesh
			//
			// Purpose: Creates a mesh. A mesh's data may be changed at
			//  runtime.
			//
			Mesh(ID_Vertex_Data* vertices, const PW_SUINT vertex_count, PW_UINT* indices, const PW_SUINT indice_count);
			// Function: Mesh::~Mesh
			//
			// Purpose: Deallocates memory contained by the mesh.
			//
			~Mesh();
			// Function: Mesh::operator=
			//
			// Purpose: Handles the copying of one mesh to another.
			//
			Mesh operator=(const Mesh& rhs);
			// Function: Mesh::operator==
			//
			// Purpose: Allows for the testing of a mesh's likeness to another.
			//
			PW_BOOL operator==(const Mesh& rhs);
		private:
		// Public Functions/Macros 
		public:
			// Function: Mesh::Draw
			//
			// Purpose: Draws the mesh. 
			//
			PW_VOID Draw();
			// Function: Mesh::Delete
			//
			// Purpose: Deletes and frees the memory of the mesh.
			//
			PW_VOID Delete();
			// Function: Mesh::Vertices
			//
			// Purpose: Returns the vertices of this shape.
			//
			ID_Vertex_Data* Vertices();
			// Function: Mesh::Vertex_Count
			//
			// Purpose: Returns the vertex count of this shape.
			//
			PW_UINT Vertex_Count();
			// Function: Mesh::Update_Vertices
			//
			// Purpose: Updates the vertices of the shape. Will affect vertices
			//  next frame.
			//
			PW_VOID Update_Vertices(ID_Vertex_Data* new_vertices);
			// Function: Mesh::Change_Color_Data
			//
			// Purpose: Updates the color data of the shape. Takes affect
			//  next frame.
			//
			PW_VOID Change_Color_Data(glm::vec3 new_color_data);
			// Function: Mesh::Change_Texture_Data
			//
			// Purpose: Updates the texture data of the mesh. Takes affect
			//  next frame.
			//
			PW_VOID Change_Texture_Data(ID_Vertex_Data* new_texture_data);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables      
		private:
			PW_SRD_PTR(ID_Vertex_Data PW_SMART_ARRAY) vertices;

			PW_UINT draw_count;
			PW_UINT vertex_count;

			PW_UINT vertex_array_object;
			PW_UINT vertex_buffer_object;
			PW_UINT vertex_texture_object;
			PW_UINT vertex_color_object;
			PW_UINT vertex_element_object;
		};
		// Functions               
		// Macros       
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_MESH