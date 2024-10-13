#include "utility\algorithm.h"

PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		ALG_NAMESPACE_SRT
			bool Line_Intersection(glm::vec2 p_point_1, glm::vec2 p_point_2, glm::vec2 p_point_3, glm::vec2 p_point_4) {
				return Line_Intersection(p_point_1.x, p_point_1.y, p_point_2.x, p_point_2.y, p_point_3.x, p_point_3.y, p_point_4.x, p_point_4.y);
			}
			bool Line_Intersection(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3, float p_y3, float p_x4, float p_y4) {
				// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
				float v_divisor = (((p_x1 - p_x2) * (p_y3 - p_y4)) - ((p_y1 - p_y2) * (p_x3 - p_x4)));
				// Possible can't be zero, check for zero anyways for safety
				if (v_divisor == 0.0f) {
					return false;
				}

				float t = (((p_x1 - p_x3) * (p_y3 - p_y4)) - ((p_y1 - p_y3) * (p_x3 - p_x4)))
					/ v_divisor;
				float u = -(((p_x1 - p_x2) * (p_y1 - p_y3)) - ((p_y1 - p_y2) * (p_x1 - p_x3)))
					/ v_divisor;
				if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
					return true;
				}
				return false;
			}
			bool Point_In_Shape(glm::vec2 p_point, st::Model* p_shape) {
				return Point_In_Shape(p_point.x, p_point.y, p_shape);
			}
			bool Point_In_Shape(float p_x, float p_y, st::Model* p_shape) {
				// https://wrfranklin.org/Research/Short_Notes/pnpoly.html
				// Use algorithm to find if the point was within the model range
				// Early exit
				if (p_y > p_shape->Position().y || p_y < p_shape->Position().y - p_shape->Size().y) {
					return false;
				}
				if (p_x < p_shape->Position().x || p_x > p_shape->Position().x + p_shape->Size().x) {
					return false;
				}

				st::Mesh* v_mesh = p_shape->Mesh();
				glm::vec2 v_position = glm::vec2(p_shape->Position().x, p_shape->Position().y);
				glm::vec2 v_size = glm::vec2(p_shape->Size());
				// Very costly, allocating memory like this is very slow
				std::vector<glm::vec2> v_points{};
				// Makes it a bit faster but not by much
				v_points.reserve(v_mesh->Vertex_Count());

				for (uint64_t i{ 0 }; i < v_mesh->Vertex_Count(); i++) {
					v_points.emplace_back(glm::vec2(
						// x
						v_position.x + (v_size.x * v_mesh->Vertices()[i].Vertex_Position().x),
						// y
						v_position.y + (v_size.y * v_mesh->Vertices()[i].Vertex_Position().y)
					));
				}
				bool v_contained = false;
				// We need to capture any and all cases, even when dealing with edge collisions
				// The upper 50% of a shape's size indicates that we need to switch to a inclusion
				// The lower 50% of a shape's size indicates that we need to switch to a exclusion
				if (p_x > p_shape->Position().x + (p_shape->Size().x / 2.0f) || p_y > p_shape->Position().y - (p_shape->Size().y / 2.0f)) {
					for (uint64_t i{ 0 }, j{ v_mesh->Vertex_Count() - 1 }; i < v_mesh->Vertex_Count(); j = i++) {
						if (((v_points[i].y >= p_y) != (v_points[j].y >= p_y)) &&
							(p_x <= (v_points[j].x - v_points[i].x) * (p_y - v_points[i].y) / (v_points[j].y - v_points[i].y) + v_points[i].x)) {
							v_contained = !v_contained;
						}
					}
					return v_contained;
				}
				else {
					for (uint64_t i{ 0 }, j{ v_mesh->Vertex_Count() - 1 }; i < v_mesh->Vertex_Count(); j = i++) {
						if (((v_points[i].y > p_y) != (v_points[j].y > p_y)) &&
							(p_x < (v_points[j].x - v_points[i].x) * (p_y - v_points[i].y) / (v_points[j].y - v_points[i].y) + v_points[i].x)) {
							v_contained = !v_contained;
						}
					}
					return v_contained;
				}
			}
		ALG_NAMESPACE_END
	UTIL_NAMESPACE_END
PW_NAMESPACE_END
/* Dead Code
bool Point_In_Shape(float p_x, float p_y, st::Model* p_shape) {
				uint32_t v_intersections{ 0 };

				st::Mesh* v_mesh = p_shape->Mesh();
				std::vector<glm::vec2> v_points{};

				for (uint64_t i{ 0 }; i < v_mesh->Vertex_Count(); i++) {
					v_points.push_back(glm::vec2(
						// x
						p_shape->Position().x + (p_shape->Size().x * v_mesh->Vertices()[i].Vertex_Position().x),
						// y
						p_shape->Position().y + (p_shape->Size().y * v_mesh->Vertices()[i].Vertex_Position().y)
					));
				}

				std::vector<glm::vec2>::iterator v_first = v_points.begin();
				std::vector<glm::vec2>::iterator v_second = v_points.begin();

				for (uint64_t i = 0; i < v_points.size(); i++) {
					v_second++;
					if (v_second == v_points.end()) {
						v_second = v_points.begin();
					}
					if (Line_Intersection(*v_first, *v_second, glm::vec2(p_x, p_y), glm::vec2(-0.0f, p_y)) == true) {
						v_intersections = v_intersections + 1;
					}
					v_first = v_second;
				}
				if (v_intersections % 2 == 0) {
					return false;
				}
				return true;
			}
			*/