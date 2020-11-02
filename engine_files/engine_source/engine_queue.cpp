#include "engine_headers\engine_queue.h"

namespace pw {
/* Engine_Queue             */
/* Static Declarations      */
	size_t Engine_Queue::index = 0;
	std::vector<IE_Game_Scene> Engine_Queue::scene_vector;
/* Class Members            */
	void Engine_Queue::Run_Queue(IE_Shader shader) {
		if (index >= scene_vector.size()) {
			index = 0;
		}
		else {
			if (index < 0) {
				index = 0;
			}
		}
		scene_vector.at(index).Render(shader);
	}
	void Engine_Queue::Load_From_Dir(const char* dir) {
		std::string file_list = "";
		std::string path_to_dir = dir;
		size_t file_count = 0;
		for (const auto& file_finder : std::filesystem::directory_iterator(path_to_dir)) {
			std::string temp_str = file_finder.path().generic_string();
			size_t front_index = 0;
			size_t back_index = 0;
			temp_str.erase(0, temp_str.find("."));
			if (temp_str == ".pwsf") {
				file_list.append(file_finder.path().generic_string().c_str());
				file_count = file_count + 1;
			}
		}
		for (size_t i = 0; i < file_count; i++) {
			std::string temp_str = file_list.substr(0, file_list.find(".") + 5);

			IE_Game_Scene scene = IE_Game_Scene(temp_str.c_str());
			scene_vector.push_back(scene);

			file_list.erase(0, temp_str.size());
		}
		// Insertion Sort the orders of the vector
		Insertion_Sort();
	}
	void Engine_Queue::Add_Game_Scene(IE_Game_Scene scene) {
		scene_vector.push_back(scene);
		Insertion_Sort();
	}
	void Engine_Queue::Insertion_Sort() {
		IE_Game_Scene key = IE_Game_Scene(NULL);
		int less_index = 0;
		for (size_t i = 1; i < scene_vector.size(); i++) {
			key = scene_vector.at(i);
			less_index = (int)i - 1;

			while (less_index >= 0 && scene_vector.at(less_index).Get_Order_Number() > key.Get_Order_Number())
			{
				scene_vector.at(less_index + 1) = scene_vector.at(less_index);
				less_index = less_index - 1;
			}
			scene_vector.at(less_index + 1) = key;
		}
	}
}