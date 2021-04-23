#include "engine_headers\engine_queue.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	// Engine_Queue
	// Static Declarations
		PW_UINT Engine_Queue::index = 0;
		std::vector<PW_SRD_PTR(ie::Game_Scene)> Engine_Queue::scene_vector;
	// Class Members
		PW_VOID Engine_Queue::Run_Queue() {
			if (index >= scene_vector.size()) {
				index = 0;
			}
			else {
				if (index < 0) {
					index = 0;
				}
			}
			scene_vector.at(index)->Render();
		}
		PW_VOID Engine_Queue::Refresh_Queue() {
			if (scene_vector.size() > 0) {
				for (PW_SIZE i = 0; i < scene_vector.size(); i++) {
					scene_vector.at(i)->Refresh_Scene();
				}
			}
		}
		PW_VOID Engine_Queue::Load_From_Dir(PW_CSTRING dir) {
			std::string file_list = "";
			std::string path_to_dir = dir;
			PW_UINT file_count = 0;
			for (const auto& file_finder : std::filesystem::directory_iterator(path_to_dir)) {
				std::string temp_str = file_finder.path().generic_string();
				PW_UINT front_index = 0;
				PW_UINT back_index = 0;
				temp_str.erase(0, temp_str.find("."));
				if (temp_str == ".pwsf") {
					file_list.append(file_finder.path().generic_string().c_str());
					file_count = file_count + 1;
				}
			}
			for (PW_UINT i = 0; i < file_count; i++) {
				std::string temp_str = file_list.substr(0, file_list.find(".") + 5);

				std::shared_ptr<ie::Game_Scene> scene = std::make_shared<ie::Game_Scene>(temp_str.c_str());
				scene_vector.push_back(scene);

				file_list.erase(0, temp_str.size());
			}
			// Insertion Sort the orders of the vector
			Insertion_Sort();
		}
		PW_VOID Engine_Queue::Add_Game_Scene(PW_SRD_PTR(ie::Game_Scene) scene) {
			scene_vector.push_back(scene);
			Insertion_Sort();
		}
		PW_VOID Engine_Queue::Insertion_Sort() {
			PW_SRD_PTR(ie::Game_Scene) key{};
			PW_LLUINT less_index = 0;
			for (PW_UINT i = 1; i < scene_vector.size(); i++) {
				key = scene_vector.at(i);
				less_index = (PW_INT)i - 1;

				while (less_index >= 0 && scene_vector.at(less_index)->Order_Number() > key->Order_Number()) {
					scene_vector.at(less_index + 1) = scene_vector.at(less_index);
					less_index = less_index - 1;
				}
				scene_vector.at(less_index + 1) = key;
			}
		}
		PW_VOID Engine_Queue::Change_Scene(PW_UINT new_index) {
			index = new_index;
		}
		PW_UINT Engine_Queue::Scene_Index() {
			return index;
		}
		ie::Game_Scene* Engine_Queue::Current_Scene() {
			return scene_vector.at(index).get();
		}
		PW_VOID Engine_Queue::Clear_Queue() {
			for (PW_UINT i = 0; i < scene_vector.size(); i++) {
				scene_vector.at(i)->Delete();
			}
		}
	// End of Class Members
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////