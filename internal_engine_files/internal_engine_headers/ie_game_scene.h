#ifndef H_GAME_SCENE
#define H_GAME_SCENE

//(DUAL_FILE)

/* C++ Headers              */
#include <fstream>
/* Project Headers          */
/* Engine Headers           */
#include "ie_model.h"
#include "ie_texture.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (Scene_Model)                               ]
	 A name tag for Asset models and Actor models.
	*/
	class Scene_Model {
		/* Default Class Structures */
	public:
	private:
		/* Public Functions/Macros  */
	public:
		virtual void Render(IE_Shader& shader) {}
		virtual void Delete() {}
		/* Public Variables         */
	public:
		/* Private Functions/Macros */
	private:
		/* Private Variables        */
	private:
	};
	/*                                             */
	/*[ (Asset_Model)                               ]
	 A data class for holding model and use data.
	*/
	class Asset_Model : public Scene_Model {
/* Default Class Structures */
	public:
		Asset_Model() :
			model(IE_Model::Model_Types::UNINIT, 0, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f)) {
		}
		Asset_Model(IE_Model model) :
				model(model) {
		}
		virtual ~Asset_Model() {}
	private:
/* Public Functions/Macros  */
	public:
		void Render(IE_Shader& shader) { model.Render(shader); }
		void Delete() { model.Delete(); }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		IE_Model model;
	};
	/*[ (Asset_Model)                               ]
	 A data class for holding model and use data.
	*/
	class Actor_Model : public Scene_Model {
		/* Default Class Structures */
	public:
		Actor_Model() :
				model(IE_Model::Model_Types::UNINIT, 0, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f)) {
		}
		Actor_Model(IE_Model model) :
				model(model) {
		}
		virtual ~Actor_Model() {}
	private:
		/* Public Functions/Macros  */
	public:
		void Render(IE_Shader& shader) { model.Render(shader); }
		void Delete() { model.Delete(); }
		/* Public Variables         */
	public:
		/* Private Functions/Macros */
	private:
		/* Private Variables        */ 
	private:
		IE_Model model;
		bool collidable;
	};
	/*[ (Game_Scene)                                ]
	 A class for handling scene drawing and texture
	 drawing in a scene, as well as sound and other
	 events.
	*/
	class IE_Game_Scene {
/* Default Class Structures */
	public:
		IE_Game_Scene(std::vector<Scene_Model*> scene_models);
		IE_Game_Scene(std::string& scene_str);
		IE_Game_Scene(const char* file_location);
		~IE_Game_Scene() { }
	private:
/* Public Functions/Macros  */
	public:
		void Render(IE_Shader shader);
		void Delete();

		std::vector<Scene_Model*> Get_Scene() { return scene_models; }

		std::vector<Scene_Model*> Load_Scene_From_String(std::string scene_str);
		std::string Load_Scene_From_File(const char* file_location);

		size_t Get_Order_Number() { return order_number; }
		void Set_Order_Number(size_t new_order_number) { order_number = new_order_number; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		std::vector<Scene_Model*> scene_models;
		std::vector<Scene_Model> collision_models;

		size_t order_number;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_GAME_SCENE
