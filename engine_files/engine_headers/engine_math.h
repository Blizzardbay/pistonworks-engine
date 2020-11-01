#ifndef H_ENGINE_MATH
#define H_ENGINE_MATH

//(HEADER_ONLY)

/* C++ Headers              */
/* Project Headers          */
#include "glm\glm.hpp"
/* Engine Headers           */
/* Engine Macro Includes    */
#include "engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
		/*                                             */
		/*[ (Engine_2D_PVector)                         ]
		 A basic 2D vector structure with getters and
		 setters. It also comes with position of the
		 vector, represented as a glm::vec2.
		*/
	class Engine_2D_PVector {
/* Default Class Structures */
	public:
		Engine_2D_PVector() :
				position(NULL), direction(NULL), magnitude(NULL) {
		}
		Engine_2D_PVector(glm::vec2 position) :
			position(position), direction(NULL), magnitude(NULL) {
		}
		Engine_2D_PVector(glm::vec2 position, float direction) :
			position(position), direction(direction), magnitude(NULL) {
		}
		Engine_2D_PVector(glm::vec2 position, float direction, int magnitude) :
			position(position), direction(direction), magnitude(magnitude) {
		}
		~Engine_2D_PVector() {}
	private:
/* Public Functions/Macros  */
	public:
		glm::vec2 Get_Position_Vec() { return position; }
		float Get_X_Position() { return position.x; }
		float Get_Y_Position() { return position.y; }

		float Get_Direction() { return direction; }
		int Get_Magnitude() { return magnitude; }

		void Set_Position_Vec(glm::vec2 new_position) { position = new_position; }
		void Set_X_Position(float x_position) { position.x = x_position; }
		void Set_Y_Position(float y_position) { position.y = y_position; }

		void Set_Direction(float new_direction) { direction = new_direction; }
		void Set_Magnitude(int new_magnitude) { magnitude = new_magnitude; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		glm::vec2 position;
		float direction;
		int magnitude;
	};
	/* Functions                */
	/* Macros                   */
}
#endif // !H_ENGINE_MATH