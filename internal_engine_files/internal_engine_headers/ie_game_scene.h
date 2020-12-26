#ifndef H_GAME_SCENE
#define H_GAME_SCENE

//(DUAL_FILE)

/* C++ Headers              */
#include <fstream>
/* Project Headers          */
/* Engine Headers           */
#include "ie_model.h"
#include "ie_texture.h"
#include "ie_player.h"
#include "ie_animation.h"
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
		virtual PW_VOID Render() {}
		virtual PW_VOID Delete() {}
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
			model(IE_Static_Model::Model_Types::UNINIT, 0, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f)) {
		}
		Asset_Model(IE_Static_Model model) :
			model(model) {
		}
		virtual ~Asset_Model() {}
	private:
/* Public Functions/Macros  */
	public:
		PW_VOID Render() { model.Render(); }
		PW_VOID Delete() { model.Delete(); }

		IE_Static_Model& Model() { return model; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		IE_Static_Model model;
	};
	/*                                             */
	/*[ (Asset_Model)                               ]
	 A data class for holding model and use data.
	*/
	class AAsset_Model : public Scene_Model {
/* Default Class Structures */
	public:
		AAsset_Model(IE_Static_Model model, IE_Animation animation) :
			model(IE_Static_Model::IE_Static_Model(model)), animation(animation) {
		}
		virtual ~AAsset_Model() {}
	private:
/* Public Functions/Macros  */
	public:
		PW_VOID Render() { model.Render(); }
		PW_VOID Delete() { model.Delete(); animation.Delete();}

		Asset_Model Model() { return model; }

		PW_VOID Run_Animation() {
			animation.Change_Frame();
			model.Model().Mesh_Reference()->Change_Texture_Data(model.Model().Mesh_Reference()->Vertices());
		}
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		Asset_Model model;
		IE_Animation animation;
	};
	/*                                             */
	/*[ (Actor_Model)                               ]
	 A data class for holding model and use data.
	*/
	class Actor_Model : public Scene_Model {
/* Default Class Structures */
	public:
		Actor_Model() :
				model(IE_Dynamic_Model::Model_Types::UNINIT, 0, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f)) {
		}
		Actor_Model(IE_Dynamic_Model model) :
				model(model) {
		}
		virtual ~Actor_Model() {}
	private:
/* Public Functions/Macros  */
	public:
		PW_VOID Render() { model.Render(); }
		PW_VOID Delete() { model.Delete(); }

		PW_VOID Handle_Collision() { model.Handle_Collisions(IE_Player::Get_Model()); }

		IE_Dynamic_Model& Model() { return model; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */ 
	private:
		IE_Dynamic_Model model;
	};
	/*                                             */
	/*[ (Actor_Model)                               ]
	 A data class for holding model and use data.
	*/
	class AActor_Model : public Actor_Model {
/* Default Class Structures */
	public:
		AActor_Model(IE_Dynamic_Model model, IE_Animation animation) :
			model(IE_Dynamic_Model::IE_Dynamic_Model(model)), animation(animation) {
		}
		virtual ~AActor_Model() {}
	private:
/* Public Functions/Macros  */
	public:
		PW_VOID Render() { Run_Animation(); model.Render(); }
		PW_VOID Delete() { model.Delete(); animation.Delete(); }

		PW_VOID Handle_Collision() { model.Model().Handle_Collisions(IE_Player::Get_Model()); }

		Actor_Model& Model() { return model; }

		PW_VOID Run_Animation() { model.Model().Mesh()->Change_Texture_Data(animation.Change_Frame()); }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		Actor_Model model;
		IE_Animation animation;
	};
	/*[ (Game_Scene)                                ]
	 A class for handling scene drawing and texture
	 drawing in a scene, as well as sound and other
	 events.
	*/
	class IE_Game_Scene {
/* Default Class Structures */
	public:
		IE_Game_Scene(PW_CSTRING file_location);
		~IE_Game_Scene() {}
	private:
/* Public Functions/Macros  */
	public:
		PW_VOID Render();
		PW_VOID Delete();

		std::vector<Scene_Model*> Get_Scene() { return scene_models; }

		std::vector<Scene_Model*> Load_Scene_From_String(PW_STRING scene_str);
		PW_STRING Load_Scene_From_File(PW_CSTRING file_location);

		PW_UINT Get_Order_Number() { return order_number; }
		PW_VOID Set_Order_Number(PW_UINT new_order_number) { order_number = new_order_number; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		std::vector<Scene_Model*> scene_models;
		std::vector<Actor_Model*> collision_models;
		std::vector<IE_Animation*> animations;

		PW_UINT order_number;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_GAME_SCENE
