#ifndef H_IE_MODEL
#define H_IE_MODEL
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
#include "ie_mesh.h"
#include "ie_texture.h"
#include "ie_shader.h"
#include "engine_headers\engine_constant.h"
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
		// Struct Name: pw::ie::ID_DOWN_RS_Triangle
		//																				 
		// Purpose:
		//  Holds the data for a ID_DOWN_RS_Triangle.
		//  XXo
		//  Xoo
		//  ooo
		//  Picture of triangle(X = blank) (o = triangle)
		//
		struct ID_DOWN_RS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Function: ID_DOWN_RS_Triangle::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_DOWN_RS_Triangle::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_DOWN_RS_Triangle::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_DOWN_RS_Triangle::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_DOWN_RS_Triangle::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_DOWN_RS_Triangle::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_DOWN_LS_Triangle
		//																				 
		// Purpose:
		//  Holds the data for a ID_DOWN_LS_Triangle.
		//  oXX
		//  ooX
		//  ooo
		//  Picture of triangle(X = blank) (o = triangle)
		//
		struct ID_DOWN_LS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Function: ID_DOWN_LS_Triangle::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_DOWN_LS_Triangle::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_DOWN_LS_Triangle::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_DOWN_LS_Triangle::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_DOWN_LS_Triangle::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_DOWN_LS_Triangle::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables 
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_UP_RS_Triangle
		//																				 
		// Purpose:
		//  Holds the data for a ID_UP_RS_Triangle.
		//	XXo
		//	Xoo
		//	ooo
		//	Picture of triangle(X = blank) (o = triangle)
		//
		struct ID_UP_RS_Triangle {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			// Function: ID_UP_RS_Triangle::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_UP_RS_Triangle::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_UP_RS_Triangle::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_UP_RS_Triangle::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_UP_RS_Triangle::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_UP_RS_Triangle::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_UP_LS_Triangle
		//																				 
		// Purpose:
		//  Holds the data for a ID_UP_LS_Triangle.
		//  ooo
		//	ooX
		//	oXX
		//	Picture of triangle(X = blank) (o = triangle)
		//
		struct ID_UP_LS_Triangle {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Function: ID_UP_LS_Triangle::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_UP_LS_Triangle::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_UP_LS_Triangle::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_UP_LS_Triangle::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_UP_LS_Triangle::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_UP_LS_Triangle::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables       
		public:
		// Private Functions/Macros 
		private:
		// Private Variables     
		private:
			static const PW_SUINT vertices_size = 3;
			static ID_Vertex_Data vertices[3];
			static const PW_SUINT indices_size = 3;
			static PW_UINT indices[3];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_Square
		//																				 
		// Purpose:
		//  Holds the data for a ID_Square.
		//  ooo
		//	ooo
		//	ooo
		//	Picture of square(x = blank) (o = square)
		//
		struct ID_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros 
		public:
			// Function: ID_Square::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_Square::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_Square::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_Square::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_Square::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_Square::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables  
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_HAFE_RS_Square
		//																				 
		// Purpose:
		//  Holds the data for a ID_HAFE_RS_Square.
		//  ooo
		//	ooo
		//	ooo
		//	Picture of square(x = blank) (o = square)
		//
		struct ID_HAFE_RS_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Function: ID_HAFE_RS_Square::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_HAFE_RS_Square::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_HAFE_RS_Square::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_HAFE_RS_Square::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_HAFE_RS_Square::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_HAFE_RS_Square::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_HAFE_LS_Square
		//																				 
		// Purpose:
		//  Holds the data for a ID_HAFE_LS_Square.
		//  ooo
		//	ooo
		//	ooo
		//	Picture of square(x = blank) (o = square)
		//
		struct ID_HAFE_LS_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Function: ID_HAFE_LS_Square::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_HAFE_LS_Square::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_HAFE_LS_Square::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_HAFE_LS_Square::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_HAFE_LS_Square::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_HAFE_LS_Square::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables   
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_HAFE_UP_Square
		//																				 
		// Purpose:
		//  Holds the data for a ID_HAFE_UP_Square.
		//  ooo
		//	ooo----(cut in two)
		//	XXX
		//	Picture of square(x = blank) (o = square)
		//
		struct ID_HAFE_UP_Square {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros  
		public:
			// Function: ID_HAFE_UP_Square::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_HAFE_UP_Square::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_HAFE_UP_Square::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_HAFE_UP_Square::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_HAFE_UP_Square::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_HAFE_UP_Square::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables        
		public:
		// Private Functions/Macros 
		private:
		// Private Variables       
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		//////////////////////////////////
		// Struct Name: pw::ie::ID_HAFE_DOWN_Square
		//																				 
		// Purpose:
		//  Holds the data for a ID_HAFE_DOWN_Square.
		//  XXX
		//	ooo----(cut in two)
		//	ooo
		//	Picture of square(x = blank) (o = square)
		//
		struct ID_HAFE_DOWN_Square {
		// Default Class Structures 
		public:
		private:
		// Public Functions/Macros  
		public:
			// Function: ID_HAFE_DOWN_Square::Vertices
			//
			// Purpose: Returns the vertices of this shape. Unchanged.
			//
			static ID_Vertex_Data* Vertices();
			// Function: ID_HAFE_DOWN_Square::Indices
			//
			// Purpose: Returns the indices of this shape. Unchanged.
			//
			static PW_UINT* Indices();
			// Function: ID_HAFE_DOWN_Square::Vertices_Size
			//
			// Purpose: Returns the amount of vertices of this shape. Unchanged.
			//
			static const PW_SUINT Vertices_Size();
			// Function: ID_HAFE_DOWN_Square::Indices_Size
			//
			// Purpose: Returns the amount of indices of this shape. Unchanged.
			//
			static const PW_SUINT Indices_Size();
			// Function: ID_HAFE_DOWN_Square::Handle_Model_Data_NOC
			//
			// Purpose: Creates the mesh for non-colored models.
			//
			static PW_VOID Handle_Model_Data_NOC(PW_SRD_PTR(Mesh)& model_mesh);
			// Function: ID_HAFE_DOWN_Square::Handle_Model_Data_C
			//
			// Purpose: Creates the mesh for colored models, can be used to change
			//  color information.
			//
			static PW_VOID Handle_Model_Data_C(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			static const PW_SUINT vertices_size = 4;
			static ID_Vertex_Data vertices[4];
			static const PW_SUINT indices_size = 6;
			static PW_UINT indices[6];
		};
		//////////////////////////////////
		// Enum Name: pw::ie::Model_Types
		//																				 
		// Purpose: A structure that holds model type
		//  identifiers.
		//
		enum class Model_Types {
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
		class Dynamic_Model;
		//////////////////////////////////
		// Class Name: pw::ie::Static_Model
		//																				 
		// Purpose: A structure that holds all data for a
		//  model. Does not update.
		//
		class Static_Model {
		// Default Class Structures 
		public:
			// Function: Static_Model::Static_Model
			//
			// Purpose: Initializes the static model information. 
			//
			Static_Model();
			// Function: Static_Model::Static_Model
			//
			// Purpose: Creates a full static model, only
			//  updates once it is created and nevermore until
			//  window resize.
			//  Variation: NO-COLOR 
			//
			Static_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size);
			// Function: Static_Model::Static_Model
			//
			// Purpose: Creates a colored static model that only
			//  updates once it is created. May be updated on resize.
			//
			Static_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec3 model_color);
			// Function: Static_Model::~Static_Model
			//
			// Purpose: Deallocates all of the static model memory.
			//
			~Static_Model() {};
		private:
		// Public Functions/Macros  
		public:
			// Function: Static_Model::Render
			//
			// Purpose: Renders the static model to the screen.
			//
			PW_VOID Render();
			// Function: Static_Model::Delete
			//
			// Purpose: Deletes active memory allocated for the model.
			//  Will not fully delete all memory until scope.
			//
			PW_VOID Delete();
			// Function: Static_Model::Position
			//
			// Purpose: Returns the position of the model.
			//
			glm::vec3 Position();
			// Function: Static_Model::Position_Reference
			//
			// Purpose: Returns the reference to the position.
			//
			glm::vec3& Position_Reference();
			// Function: Static_Model::Model_Type
			//
			// Purpose: Returns the type of the model.
			//
			Model_Types Model_Type();
			// Function: Static_Model::Rotation
			//
			// Purpose: Returns the rotation of the model.
			//
			PW_FLOAT Rotation();
			// Function: Static_Model::Model_Size
			//
			// Purpose: Returns the size in width and height.
			//
			glm::vec2 Model_Size();
			// Function: Static_Model::Model_Mesh
			//
			// Purpose: Returns the current mesh of the model.
			//
			PW_SRD_PTR(Mesh) Model_Mesh();
			// Function: Static_Model::Model_Mesh_Reference
			//
			// Purpose: Returns directly the reference of the mesh.
			//
			PW_SRD_PTR(Mesh)& Model_Mesh_Reference();
		// Public Variables         
		public:
			static PW_VOID(*model_functions_noc[(PW_INT)Model_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh);
			static PW_VOID(*model_functions_c[(PW_INT)Model_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);

			static ID_Vertex_Data* model_vertices[(PW_INT)Model_Types::TYPE_COUNT - 1];
			static const PW_SUINT model_vertices_count[(PW_INT)Model_Types::TYPE_COUNT - 1];
			// Function: Static_Model::Refresh_Model
			//
			// Purpose: Refreshes the model when the window is resized.
			//
			PW_VOID Refresh_Model();
		// Private Functions/Macros 
		private:
			// Function: Static_Model::Handle_Calculations
			//
			// Purpose: Calculates the position of the model.
			//
			glm::mat4 Handle_Calculations();
		// Private Variables        
		private:
			Model_Types model_type;
			PW_SRD_PTR(Mesh) model_mesh;
			Texture model_texture;
			glm::vec3 model_color;
			PW_INT model_is_colored;

			glm::vec3 model_position;
			glm::vec2 model_size;
			PW_FLOAT model_rotation;

			glm::mat4 model_matrix;
		};
		//////////////////////////////////
		// Class Name: pw::ie::Dynamic_Model
		//																				 
		// Purpose: A structure that holds all data for a
		// model. Updates frequently.
		//
		class Dynamic_Model {
		// Default Class Structures 
		public:
			// Function: Dynamic_Model::Dynamic_Model
			//
			// Purpose: Creates a uninitialized Dynamic Model,
			//  with default values.
			//
			Dynamic_Model();
			// Function: Dynamic_Model::Dynamic_Model
			//
			// Purpose: Creates a un-colored dynamic model. Updated
			//  every frame.
			//
			Dynamic_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size);
			// Function: Dynamic_Model::Dynamic_Model
			//
			// Purpose: Creates a colored dynamic model. Updates
			//  every frame.
			//
			Dynamic_Model(Model_Types type, Texture texture, glm::vec2 model_position, PW_FLOAT model_rotation, glm::vec2 model_size, glm::vec3 model_color);
			// Function: Dynamic_Model::~Dynamic_Model
			//
			// Purpose: Deallocates all memory used in the structure.
			//
			~Dynamic_Model() {};
		private:
		// Public Functions/Macros  
		public:
			// Function: Dynamic_Model::Render
			//
			// Purpose: Renders the dynamic model to the screen.
			//
			PW_VOID Render();
			// Function: Dynamic_Model::Render
			//
			// Purpose: Renders a dynamic model that is tied to a
			//  physics object.
			//
			PW_VOID Render(b2Body* model_body);
			// Function: Dynamic_Model::Delete
			//
			// Purpose: Deletes all memory allocated for this model.
			//
			PW_VOID Delete();
			// Function: Dynamic_Model::Position
			//
			// Purpose: Returns the position of the model.
			//
			glm::vec3 Position();
			// Function: Dynamic_Model::Position_Reference
			//
			// Purpose: Returns the reference to the position of the model.
			//
			glm::vec3& Position_Reference();
			// Function: Dynamic_Model::Last_Postition
			//
			// Purpose: Returns the last position of the model.
			//
			glm::vec3 Last_Postition();
			// Function: Dynamic_Model::Last_Postition_Reference
			//
			// Purpose: Returns the last position reference of the model.
			//
			glm::vec3& Last_Postition_Reference();
			// Function: Dynamic_Model::Model_Type
			//
			// Purpose: Returns the model type of the model.
			//
			Model_Types Model_Type();
			// Function: Dynamic_Model::Rotation
			//
			// Purpose: Returns the current rotation value of the model.
			//
			PW_FLOAT Rotation();
			// Function: Dynamic_Model::Model_Size
			//
			// Purpose: Returns the current model size of the model.
			//
			glm::vec2 Model_Size();
			// Function: Dynamic_Model::Model_Mesh
			//
			// Purpose: Returns a pointer to the model's mesh.
			//
			PW_SRD_PTR(Mesh) Model_Mesh();
			// Function: Dynamic_Model::Model_Mesh_Reference
			//
			// Purpose: Returns a reference to the pointer to the model's mesh.
			//
			PW_SRD_PTR(Mesh)& Model_Mesh_Reference();
			// Function: Dynamic_Model::Set_Model_Color
			//
			// Purpose: Set the model color. Takes affect next call to render.
			//
			PW_VOID Set_Model_Color(glm::vec3 new_model_color);
			// Function: Dynamic_Model::Update_Position
			//
			// Purpose: Updates the potion of the model. Takes affect next
			//  call to render.
			//
			PW_VOID Update_Position(glm::vec2 position);
			// Function: Dynamic_Model::Update_Position
			//
			// Purpose: Updates the potion of the model. Takes affect next
			//  call to render.
			//
			PW_VOID Update_Position(PW_FLOAT x_pos, PW_FLOAT y_pos);
			// Function: Dynamic_Model::Set_Body_Pos
			//
			// Purpose: Sets the physics object body of the model
			//  to a location.
			//
			PW_VOID Set_Body_Pos(glm::vec2 body_pos);
			// Function: Dynamic_Model::Refresh_Model
			//
			// Purpose: Reloads the model. Called automatically on resize.
			//
			PW_VOID Refresh_Model();
		// Public Variables        
		public:
			static PW_VOID(*model_functions_noc[(PW_INT)Model_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh);
			static PW_VOID(*model_functions_c[(PW_INT)Model_Types::TYPE_COUNT - 1])(PW_SRD_PTR(Mesh)& model_mesh, glm::vec3 model_color);

			static ID_Vertex_Data* model_vertices[(PW_INT)Model_Types::TYPE_COUNT - 1];
			static const PW_SUINT model_vertices_count[(PW_INT)Model_Types::TYPE_COUNT - 1];
		// Private Functions/Macros 
		private:
			// Function: Dynamic_Model::Handle_Calculations
			//
			// Purpose: Converts engine screen information to world info.
			//  Called on refresh.
			//
			glm::mat4 Handle_Calculations(PW_BOOL dynamic_override);
			// Function: Dynamic_Model::Handle_Calculations
			//
			// Purpose: Converts engine screen information to world info.
			//  Called if the dynamic model has a physics body.
			//
			glm::mat4 Handle_Calculations(b2Body* model_body);
			// Function: Dynamic_Model::Handle_Calculations
			//
			// Purpose: Converts engine screen information to world info.
			//
			glm::mat4 Handle_Calculations();
		// Private Variables      
		private:
			Model_Types model_type;
			PW_SRD_PTR(Mesh) model_mesh;
			Texture model_texture;
			glm::vec3 model_color;
			PW_INT model_is_colored;

			glm::vec3 model_position;
			glm::vec3 model_last_position;
			glm::vec2 model_size;
			PW_FLOAT model_rotation;

			glm::vec2 last_body_pos;

			glm::mat4 model_matrix;
		};
		// Functions                
		// Macros                   
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_MODEL