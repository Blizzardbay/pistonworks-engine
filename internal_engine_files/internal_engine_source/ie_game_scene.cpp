#include "internal_engine_headers\ie_game_scene.h"

namespace pw {
/* IE_Game_Scene            */
/* Static Declarations      */
/* Class Members            */
	IE_Game_Scene::IE_Game_Scene(PW_CSTRING level_location) :
			scene_models(NULL), order_number(NULL), collision_models(NULL) {
		if (level_location != NULL) {
			scene_models = this->Load_Scene_From_String(this->Load_Scene_From_File(level_location));
		}
	}
	void IE_Game_Scene::Render() {
		if (collision_models.size() != 0) {
			for (size_t i = 0; i < collision_models.size(); i++) {
				collision_models.at(i)->Handle_Collision();
			}
		}
		for (size_t i = 0; i < scene_models.size(); i++) {
			scene_models.at(i)->Render();
		}
	}
	void IE_Game_Scene::Delete() {
		for (size_t i = 0; i < scene_models.size(); i++) {
			scene_models.at(i)->Delete();
			delete scene_models.at(i);
			scene_models.at(i) = nullptr;
		}
		scene_models.erase(scene_models.begin(), scene_models.end());
		scene_models.~vector();
		for (size_t i = 0; i < collision_models.size(); i++) {
			collision_models.at(i) = nullptr;
		}
		collision_models.erase(collision_models.begin(), collision_models.end());
		collision_models.~vector();
	}
	std::vector<Scene_Model*> IE_Game_Scene::Load_Scene_From_String(PW_STRING scene_str) {
		std::vector<Scene_Model*> models;
		PW_UINT index_front = 0;
		PW_UINT index_back = 0;
		PW_UINT index_prevf = 0;
		PW_UINT index_prevb = 0;
		PW_STRING str = "";
		PW_STRING str2 = "";
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
			if (scene_str.at(0) == '/' && scene_str.at(0) == '/') {
				index_back = scene_str.find(")", 0);
				scene_str.erase(0, index_back + 1);
				continue;
			}
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
				index_front = scene_str.find("[");
				index_back = scene_str.find("]", index_front);
				str = scene_str.substr(index_front + 1, index_back - index_front - 1);
				str2 = IE_Texture::Find_Texture(str.c_str());
				texture = IE_Texture(str2.c_str());
				model_color = glm::vec3(-1.0f);
			}
			str.clear();
			str2.clear();
			//Find out if it has animation data
			PW_INT boolean_expression = 0;
			PW_BOOL animated = false;
			PW_FLOAT animation_length = 0.0f;
			PW_UINT animation_frames = 0;
			PW_UINT animation_size_x = 0;

			index_prevb = index_back;

			index_front = scene_str.find("[", index_prevb);
			index_back = scene_str.find("=", index_front);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			boolean_expression = std::stoi(str);
			if (boolean_expression == 1) {
				animated = true;
			}
			str.clear();
			if (animated == true) {
				index_front = index_back;
				index_back = scene_str.find(",", index_front);
				str = scene_str.substr(index_front + 1, index_back - index_front - 1);
				animation_length = std::stof(str);
				index_front = index_back;
				index_back = scene_str.find(",", index_front + 1);
				str = scene_str.substr(index_front + 1, index_back - index_front - 1);
				animation_frames = std::stoi(str);
				index_front = index_back;
				index_back = scene_str.find("=", index_front + 1);
				str = scene_str.substr(index_front + 1, index_back - index_front - 1);
				animation_size_x = std::stoi(str);
				str.clear();
			}
			//Find out if it has collision data
			boolean_expression = 0;
			PW_BOOL collidable = false;

			index_prevb = index_back;

			index_front = scene_str.find("[", index_prevb);
			index_back = scene_str.find("]", index_front);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			boolean_expression = std::stoi(str);
			if (boolean_expression == 1) {
				collidable = true;
			}
			str.clear();
			//Get the model data
			PW_INT model_type = 0;
			glm::vec2 position(1.0f);
			PW_FLOAT rotation = 0.0f;
			glm::vec2 size(1.0f);
			//Model Type
			index_prevb = index_back;

			index_front = scene_str.find("(", index_prevb);
			index_back = scene_str.find(",", index_prevb);
			index_prevb = index_back;
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			model_type = std::stoi(str.c_str());
			str.clear();
			//Model Position
			index_front = scene_str.find("=", index_prevb + 1);
			index_prevf = index_front;
			index_back = scene_str.find(",",index_prevb + 1);
			index_prevb = index_back;
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			position.x = std::stof(str.c_str()) * 32.0f;
			str.clear();
			index_front = index_back;
			index_back = scene_str.find("=", index_prevf + 1);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			position.y = std::stof(str.c_str()) * 32.0f;
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
			index_front = index_back;
			index_back = scene_str.find(")", index_prevf + 1);
			str = scene_str.substr(index_front + 1, index_back - index_front - 1);
			PW_CHAR type = str.at(0);
			str.clear();
			Scene_Model* scene_model = NULL;
			if (type == 'd') {
				if (model_color.x != -1.0f) {
					IE_Dynamic_Model model = IE_Dynamic_Model();
					model = IE_Dynamic_Model((IE_Dynamic_Model::Model_Types)model_type, texture, position, rotation, size, model_color);
					if (collidable == true) {
						if (animated == true) {
							IE_Animation animation = IE_Animation::IE_Animation(
								animation_length, animation_frames, animation_size_x,
								model.Mesh()->Vertices(),
								model.Mesh()->Vertex_Count(),
								model.Mesh()->Vertices_Ref());
							scene_model = new AActor_Model(model, animation);
							IE_Animation* animation_ptr = new IE_Animation(animation);
							animations.push_back(animation_ptr);
							collision_models.push_back(static_cast<AActor_Model*>(scene_model));
						}
						else {
							scene_model = new Actor_Model(model);
							collision_models.push_back(static_cast<Actor_Model*>(scene_model));
						}
					}
					else {
						if (animated == true) {
							IE_Animation animation = IE_Animation::IE_Animation(
								animation_length, animation_frames, animation_size_x,
								model.Mesh()->Vertices(),
								model.Mesh()->Vertex_Count(),
								model.Mesh()->Vertices_Ref());
							scene_model = new AActor_Model(model, animation);
							IE_Animation* animation_ptr = new IE_Animation(animation);
							animations.push_back(animation_ptr);
						}
						else {
							scene_model = new Actor_Model(model);
						}
					}
				}
				else {
					IE_Dynamic_Model model = IE_Dynamic_Model();
					model = IE_Dynamic_Model((IE_Dynamic_Model::Model_Types)model_type, texture, position, rotation, size);
					if (collidable == true) {
						if (animated == true) {
							IE_Animation animation = IE_Animation::IE_Animation(
								animation_length, animation_frames, animation_size_x,
								model.Mesh()->Vertices(),
								model.Mesh()->Vertex_Count(),
								model.Mesh()->Vertices_Ref());
							scene_model = new AActor_Model(model, animation);
							IE_Animation* animation_ptr = new IE_Animation(animation);
							animations.push_back(animation_ptr);
							collision_models.push_back(static_cast<AActor_Model*>(scene_model));
						}
						else {
							scene_model = new Actor_Model(model);
							collision_models.push_back(static_cast<Actor_Model*>(scene_model));
						}
					}
					else {
						if (animated == true) {
							IE_Animation animation = IE_Animation::IE_Animation(
								animation_length, animation_frames, animation_size_x,
								model.Mesh()->Vertices(),
								model.Mesh()->Vertex_Count(),
								model.Mesh()->Vertices_Ref());
							scene_model = new AActor_Model(model, animation);
							IE_Animation* animation_ptr = new IE_Animation(animation);
							animations.push_back(animation_ptr);
						}
						else {
							scene_model = new Actor_Model(model);
						}
					}
				}
			}
			else {
				if (model_color.x != -1.0f) {
					IE_Static_Model model = IE_Static_Model();
					model = IE_Static_Model((IE_Static_Model::Model_Types)model_type, texture, position, rotation, size, model_color);
					if (animated == true) {
						IE_Animation animation = IE_Animation::IE_Animation(
							animation_length, animation_frames, animation_size_x,
							model.Mesh()->Vertices(),
							model.Mesh()->Vertex_Count(),
							model.Mesh()->Vertices_Ref());
						scene_model = new AAsset_Model(model, animation);
						IE_Animation* animation_ptr = new IE_Animation(animation);
						animations.push_back(animation_ptr);
					}
					else {
						scene_model = new Asset_Model(model);
					}
				}
				else {
					IE_Static_Model model = IE_Static_Model();
					model = IE_Static_Model((IE_Static_Model::Model_Types)model_type, texture, position, rotation, size);
					if (animated == true) {
						IE_Animation animation = IE_Animation::IE_Animation(
							animation_length, animation_frames, animation_size_x,
							model.Mesh()->Vertices(),
							model.Mesh()->Vertex_Count(),
							model.Mesh()->Vertices_Ref());
						scene_model = new AAsset_Model(model, animation);
						IE_Animation* animation_ptr = new IE_Animation(animation);
						animations.push_back(animation_ptr);
					}
					else {
						scene_model = new Asset_Model(model);
					}
				}
			}
			models.push_back(scene_model);
			scene_model = nullptr;
			delete scene_model;
			index_back = scene_str.find(")");
			scene_str.erase(0, index_back + 1);
		}
		scene_str.clear();
		return models;
	}
	PW_STRING IE_Game_Scene::Load_Scene_From_File(PW_CSTRING file_location) {
		PW_STRING content = "";
		std::ifstream fileStream(file_location, std::ios::in);

		if (!fileStream.is_open()) {
			printf("Scene File: %s did not open\n", file_location);
			return "";
		}

		PW_STRING line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line);
		}
		fileStream.close();
		return content;
	}
}
