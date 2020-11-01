#include "internal_engine_headers\ie_game_scene.h"

namespace pw {
/* IE_Game_Scene            */
/* Static Declarations      */
/* Class Members            */
	IE_Game_Scene::IE_Game_Scene(std::vector<Scene_Model*> scene_models) :
			scene_models(scene_models) {
	}
	IE_Game_Scene::IE_Game_Scene(std::string& scene_str) :
			scene_models(NULL), order_number(NULL) {
		this->IE_Game_Scene::IE_Game_Scene(Load_Scene_From_String(scene_str));
	}
	IE_Game_Scene::IE_Game_Scene(const char* level_location) :
			scene_models(NULL), order_number(NULL) {
		if (level_location != NULL) {
			this->IE_Game_Scene::IE_Game_Scene(Load_Scene_From_String(Load_Scene_From_File(level_location)));
		}
	}
	void IE_Game_Scene::Render(IE_Shader shader) {
		for (size_t i = 0; i < scene_models.size(); i++) {
			scene_models.at(i)->Render(shader);
		}
	}
	void IE_Game_Scene::Delete() {
		for (size_t i = 0; i < scene_models.size(); i++) {
			scene_models.at(i)->Delete();
			delete scene_models.at(i);
			scene_models.at(i) = nullptr;
		}
	}
	std::vector<Scene_Model*> IE_Game_Scene::Load_Scene_From_String(std::string scene_str) {
		std::vector<Scene_Model*> models;
		size_t index_front = 0;
		size_t index_back = 0;
		size_t index_prevf = 0;
		size_t index_prevb = 0;
		std::string str = "";
		std::string str2 = "";
		//Get order
		index_front = scene_str.find("*");
		index_back = scene_str.find("*", index_front + 1);
		str = scene_str.substr(index_front + 1, index_back - index_front - 1);
		if (str != "") {
			order_number = std::stoi(str);
		}

		while (scene_str.empty() != true) {
			index_front = 0;
			index_back = 0;
			index_prevf = 0;
			index_prevb = 0;
			str = "";
			str2 = "";
			//Get the texture data
			index_front = scene_str.find("[");
			index_back = scene_str.find("-",index_front);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			index_front = index_back;
			index_back = scene_str.find("]");
			str2 = scene_str.substr(index_front + 1, index_back - index_front - 1);
			IE_Texture texture;
			glm::vec3 model_color(1.0f);
			if (str == "D16" || str == "D32" || str == "D64") {
				str = IE_Texture::Find_Color_Texture(str.c_str(), (IE_Texture::Default_Texture)std::stoi(str2.c_str()), model_color);
				texture = IE_Texture(str.c_str());
			}
			else {
				str = IE_Texture::Find_Texture(str2.c_str());
				texture = IE_Texture(str.c_str());
				model_color = glm::vec3(-1.0f);
			}
			str.clear();
			str2.clear();
			//Get the texture data
			index_front = scene_str.find("[");
			index_back = scene_str.find("]", index_front);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			str.clear();
			//Get the texture data
			index_front = scene_str.find("[");
			index_back = scene_str.find("]", index_front);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			str.clear();
			//Get the model data
			int model_type = 0;
			glm::vec2 position(1.0f);
			float rotation = 0.0f;
			glm::vec2 size(1.0f);
			//Model Type
			index_front = scene_str.find("(");
			index_back = scene_str.find(",");
			index_prevb = index_back;
			str = scene_str.substr(index_front + 1, index_back - index_front);
			model_type = std::stoi(str.c_str());
			str.clear();
			//Model Position
			index_front = scene_str.find("=");
			index_prevf = index_front;
			index_back = scene_str.find(",",index_prevb + 1);
			index_prevb = index_back;
			str = scene_str.substr(index_front + 1, index_back - index_front);
			position.x = std::stof(str.c_str()) * 32;
			str.clear();
			index_front = index_back;
			index_back = scene_str.find("=", index_prevf + 1);
			str = scene_str.substr(index_front + 1, index_back - index_front);
			position.y = std::stof(str.c_str()) * 32;
			str.clear();
			//Model Rotation
			index_front = scene_str.find(",", index_prevb + 1);
			index_prevf = index_front;
			index_back = scene_str.find(",", index_prevf + 1);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			rotation = std::stof(str.c_str());
			str.clear();
			//Model Size
			index_front = scene_str.find("=", index_prevf);
			index_prevf = index_front;
			index_back = scene_str.find(",", index_prevf + 1);
			index_prevb = index_back;
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			size.x = std::stof(str.c_str());
			str.clear();
			index_front = index_back;
			index_back = scene_str.find("=", index_prevf + 1);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			size.y = std::stof(str.c_str());
			str.clear();
			IE_Model model = IE_Model();
			if (model_color.x != -1.0f) {
				model = IE_Model((IE_Model::Model_Types)model_type, texture, position, rotation, size, model_color);
			}
			else {
				model = IE_Model((IE_Model::Model_Types)model_type, texture, position, rotation, size);
			}
			Scene_Model* scene_model = new Asset_Model(model);
			models.push_back(scene_model);
			scene_model = nullptr;
			delete scene_model;
			index_back = scene_str.find(")");
			scene_str.erase(0, index_back + 1);
		}
		scene_str.clear();
		return models;
	}
	std::string IE_Game_Scene::Load_Scene_From_File(const char* file_location) {
		std::string content = "";
		std::ifstream fileStream(file_location, std::ios::in);

		if (!fileStream.is_open()) {
			printf("Scene File: %s did not open\n", file_location);
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line);
		}
		fileStream.close();
		return content;
	}
}
