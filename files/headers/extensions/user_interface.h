// BSD 3 - Clause License
//
// Copyright(c) 2021-2024, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_USER_INTERFACE
#define H_USER_INTERFACE
//////////////////////////////////
#include <codeanalysis\warnings.h>
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\macro.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "structures\game_scene.h"
//////////////////////////////////
// Engine Utility Headers
#include "utility\algorithm.h"
//////////////////////////////////

// User Interface namespace
#define UI_NAMESPACE_SRT namespace ui {
#define UI_NAMESPACE_END }

PW_NAMESPACE_SRT
	EX_NAMESPACE_SRT
		UI_NAMESPACE_SRT
			class User_Interface {
			// Friends
				friend class pw::co::Control;
			// Public Functions/Macros  
			public:
				static st::Texture* const Default_Empty_Texture();
				static st::Texture* const Default_Filled_Texture();
			// Public Variables        
			public:
			// Private Functions/Macros 
			private:
				static void Initialize(st::Texture* p_default_empty, st::Texture* p_default_filled);
			// Private Variables      
			private:
				static st::Texture* m_default_empty;
				static st::Texture* m_default_filled;
			};
			struct Button_Events {
			// Default Class Structures 
			public:
				/* Error List: NONE */
				Button_Events();
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				st::Event_Base* m_on_lclick_mouse;
				st::Event_Base* m_on_lrelease_mouse;

				st::Event_Base* m_on_rclick_mouse;
				st::Event_Base* m_on_rrelease_mouse;

				st::Event_Base* m_on_scroll_up;
				st::Event_Base* m_on_scroll_down;

				st::Event_Base* m_on_click_button;
				st::Event_Base* m_on_release_button;

				st::Event_Base* m_on_hover_button_area;
				st::Event_Base* m_no_hover_button_area;

				st::Event_Base* m_on_hover_background;
				st::Event_Base* m_no_hover_background;

				st::Event_Base* m_on_hover_border;
				st::Event_Base* m_no_hover_border;

				std::vector<st::Event_Base*> m_keyboard_events;
			};
			struct Button_Structure {
			// Friends
			// Default Class Structures 
			public:
				enum class Button_Orientation {
					// Always is centered to the best of its ability inside the background
					CENTERED,
					// Is freely positioned where an offset
					// may put it within the bounds of the button
					FREE
				};
				enum class Display_Style {
					// Only displays button area
					BUTTON_AREA_ONLY,
					// Only displays button area and background
					BUTTON_AREA_BACKGROUND_ONLY,
					// Displays all
					DISPLAY_ALL,
					// Button disabled, no events for button, still events for background / border
					DISABLE_BUTTON
				};
				enum class Border_Style {
					// Border expands inwards
					INNER,
					// Border is centered on the edge of the background
					SPLIT,
					// Border is surrounding the background adding padding
					OUTER
				};
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				uint32_t m_layer;

				glm::vec2 m_position;
				glm::vec2 m_size;
				float m_rotation;

				glm::vec2 m_button_area_offset;
				glm::vec2 m_button_area_size;
				st::Texture* m_button_area_texture;
				glm::vec4 m_button_area_color;

				st::Texture* m_background_texture;
				glm::vec4 m_background_color;

				float m_border_size;
				st::Texture* m_border_texture;
				glm::vec4 m_border_color;

				Button_Events m_events;

				Button_Orientation m_orientation;
				Display_Style m_display_style;
				Border_Style m_border_style;
			};
			class Button {
			// Friends
			// Default Class Structures
			public:
				/* Error List: PW_INVALID_LAYER, PW_FUNCTION_ERROR */
				Button(const Button_Structure& p_button);
				/* Error List: NONE */
				~Button();

				Button() = delete;
				Button(const Button&) = delete;
			private:
			// Public Functions/Macros 
			public:
				/* Error List: PW_FUNCTION_ERROR */
				void Render();

				void Process_Events(PW_EVENT_ID p_event_id, PW_BUTTON_CODE p_button_code, PW_STATE p_state);

				/* Error List: PW_INVALID_LAYER */
				void Set_Layer(uint32_t p_layer);
				/* Error List: NONE */
				void Set_Position(const glm::vec2& p_position);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Size(const glm::vec2& p_size);
				/* Error List: NONE */
				void Set_Rotation(const float p_rotation);

				/* Error List: NONE */
				void Attach_To(glm::vec2* p_position);
				/* Error List: NONE */
				void Set_Offset(const glm::vec2& p_offset);

				/* Error List: NONE */
				void Set_On_LClick(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_On_LRelease(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_On_RClick(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_On_RRelease(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_On_Scroll_Up(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_On_Scroll_Down(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_On_Click_Button(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_On_Release_Button(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_On_Hover_Button_Area(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_No_Hover_Button_Area(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_On_Hover_Background(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_No_Hover_Background(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_On_Hover_Border(st::Event_Base* p_event);
				/* Error List: NONE */
				void Set_No_Hover_Border(st::Event_Base* p_event);

				/* Error List: NONE */
				void Set_Button_Area_Offset(const glm::vec2& p_position);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Button_Area_Size(const glm::vec2& p_size);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Button_Area_Color(const glm::vec4& p_color);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Button_Area_Texture(st::Texture* p_texture);

				/* Error List: PW_FUNCTION_ERROR */
				void Set_Backaround_Color(const glm::vec4& p_color);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Backaround_Texture(st::Texture* p_texture);

				/* Error List: PW_FUNCTION_ERROR */
				void Set_Border_Size(const float& p_size);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Border_Color(const glm::vec4& p_color);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Border_Texture(st::Texture* p_texture);

				/* Error List: NONE */
				const uint32_t& Layer() const;
				/* Error List: NONE */
				const glm::vec2& Position() const;
				/* Error List: NONE */
				const glm::vec2& Size() const;
				/* Error List: NONE */
				const float& Rotation() const;

				/* Error List: NONE */
				st::Actor* const Button_Area() const;
				/* Error List: NONE */
				st::Actor* const Backaround() const;
				// Ordered in clock-wise order from [1, 4] starting at PI
				// Error List: NONE
				st::Actor* const Border(uint32_t p_part) const;

				/* Error List: NONE */
				const st::Event_Base* const On_LClick() const;
				/* Error List: NONE */
				const st::Event_Base* const On_LRelease() const;
				/* Error List: NONE */
				const st::Event_Base* const On_RClick() const;
				/* Error List: NONE */
				const st::Event_Base* const On_RRelease() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Scroll_Up() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Scroll_Down() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Click_Button() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Release_Button() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Hover_Button_Area() const;
				/* Error List: NONE */
				const st::Event_Base* const No_Hover_Button_Area() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Hover_Background() const;
				/* Error List: NONE */
				const st::Event_Base* const No_Hover_Background() const;
				/* Error List: NONE */
				const st::Event_Base* const On_Hover_Border() const;
				/* Error List: NONE */
				const st::Event_Base* const No_Hover_Border() const;
				/* Error List: NONE */
				std::vector<st::Event_Base*>& On_Keyboard();
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
				uint32_t m_layer;

				glm::vec2 m_position;
				glm::vec2 m_size;
				float m_rotation;

				st::Actor* m_button_area;
				st::Actor* m_backaround;
				st::Actor* m_border[4];

				float m_border_size;

				Button_Events m_events;

				const Button_Structure::Button_Orientation m_orientation;
				const Button_Structure::Display_Style m_display_style;
				const Button_Structure::Border_Style m_border_style;

				uint64_t m_id;
				static uint64_t m_button_id_assigner;
			};
			struct Slider_Structure {
			// Friends
			// Default Class Structures 
			public:
				enum class Type {
					// Horizontal
					// |***_____|
					// Fills to the left when moved to the right
					// When moved changes value increasing on [left, right]
					// Vertical
					// |*|
					// |*|
					// |*|
					// |-|
					// |-|
					// Fills to the top when moved to the bottom
					// When moved changes value increasing on [top, bottom]
					LEFT_TOP_FILL,
					// Horizontal
					// |_____***|
					// Fills to the right when moved to the left
					// When moved changes value increasing on [right, left]
					// Vertical
					// |-|
					// |-|
					// |*|
					// |*|
					// |*|
					// Fills to the bottom when moved to the top
					// When moved changes value increasing on [bottom, top]
					RIGHT_BOTTOM_FILL,
					// Horizontal / Vertical
					// |__****__|
					// |-|
					// |*|
					// |*|
					// |*|
					// |-|
					// When moved to either the left or right is filled from the center
					// When moved changes value increasing on [center, left] , [center, right]
					// When moved to either the top or bottom is filled from the center
					// When moved changes value increasing on [center, top] , [center, bottom]
					CENTER_FILL,
					// Horizontal
					// |<+>-----|
					// When moved changes value increasing on [left, right]
					// Vertical
					// |/\|
					// |&|
					// |\/|
					// |-|
					// |-|
					// When moved changes value increasing on [top, bottom]
					LEFT_TOP_SLIDER,
					// Horizontal
					// |-----<+>|
					// When moved changes value increasing on [right, left]
					// Vertical
					// |-|
					// |-|
					// |/\|
					// |&|
					// |\/|
					// When moved changes value increasing on [bottom, top]
					RIGHT_BOTTOM_SLIDER,
					// Horizontal / Vertical
					// |--<+>---|
					// |-|
					// |/\|
					// |&|
					// |\/|
					// |-|
					// When moved changes value increasing on [center, left] , [center, right]
					// When moved changes value increasing on [center, top] , [center, bottom]
					CENTER_SLIDER
				};
				enum class Trigger {
					// Press the mouse click and hold for slider change
					// Also the slider jumps to position
					PRESS_HOLD,
					// Release the mouse click and the slider jumps to position
					RELEASE_JUMP,
					// Slider follows mouse when in selected area
					HOVER
				};
				enum class Movement {
					// The slider is moved horizontally
					HORIZONTAL,
					// The slider is moved vertically
					VERTICAL
				};
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				uint32_t m_layer;

				glm::vec2 m_position;
				glm::vec2 m_size;

				float m_starting_value;

				glm::vec2 m_slider_size;
				st::Texture* m_slider_texture;
				glm::vec4 m_slider_color;

				st::Texture* m_bar_texture;
				glm::vec4 m_bar_color;

				float m_border_size;
				st::Texture* m_border_texture;
				glm::vec4 m_border_color;

				Button_Events m_user_defined_events;

				Button_Structure::Display_Style m_display_style;
				Button_Structure::Border_Style m_border_style;

				Slider_Structure::Type m_type;
				Slider_Structure::Trigger m_trigger;
				Slider_Structure::Movement m_movement;
			};
			class Slider {
			// Friends
			// Default Class Structures
			public:
				Slider(const Slider_Structure& p_slider);

				~Slider();

				Slider() = delete;
				Slider(const Slider&) = delete;
			private:
			// Public Functions/Macros 
			public:
				/* Error List: PW_FUNCTION_ERROR */
				void Render();

				/* Error List: PW_FUNCTION_ERROR */
				void Set_Layer(uint32_t p_layer);
				/* Error List: NONE */
				void Set_Position(const glm::vec2& p_position);
				/* Error List: PW_FUNCTION_ERROR */
				void Set_Size(const glm::vec2& p_size);

				/* Error List: NONE */
				void Attach_To(glm::vec2* p_position);
				/* Error List: NONE */
				void Set_Offset(const glm::vec2& p_offset);

				/* Error List: NONE */
				const uint32_t& Layer() const;
				/* Error List: NONE */
				const glm::vec2& Position() const;
				/* Error List: NONE */
				const glm::vec2& Size() const;
				/* Error List: NONE */
				const float& Value() const;
				/* Error List: NONE */
				Button* const Base() const;
				/* Error List: NONE */
				Button_Events& User_Events();
			// Public Variables
			public:
			// Private Functions/Macros
			private:
				/* Error List: NONE */
				void Handle_LClick();
				/* Error List: NONE */
				void Handle_LRelease();
				/* Error List: NONE */
				void Handle_RClick();
				/* Error List: NONE */
				void Handle_RRelease();
				/* Error List: NONE */
				void Handle_Scroll_Up();
				/* Error List: NONE */
				void Handle_Scroll_Down();
				/* Error List: NONE */
				void Handle_Click_Button();
				/* Error List: NONE */
				void Handle_Release_Button();
				/* Error List: NONE */
				void Handle_Hover_Button_Area();
				/* Error List: NONE */
				void Handle_No_Hover_Button_Area();
				/* Error List: NONE */
				void Handle_Hover_Background();
				/* Error List: NONE */
				void Handle_No_Hover_Background();
				/* Error List: NONE */
				void Handle_Hover_Border();
				/* Error List: NONE */
				void Handle_No_Hover_Border();
				/* Error List: NONE */
				void Handle_Keyboard();
				/* Error List: NONE */
				void Move_Slider();
			// Private Variables
			private:
				Button* m_slider;

				float m_value;
				bool m_pressed;

				Button_Events m_user_defined_events;

				const Slider_Structure::Type m_type;
				const Slider_Structure::Trigger m_trigger;
				const Slider_Structure::Movement m_movement;
			};
			struct Text_Box_Structure {
			// Friends
			// Default Class Structures 
			public:
				enum class Type {
					// Automatically shrinks text down to a size that will fit inside the
					// given box area
					SHRINK_TO_FIT,
					// Does not resize the text to fit inside the box, instead just puts as much
					// text in the box as possible before terminating
					MAX_FIT_SET_SIZE
				};
				enum class Wrapping_Style {
					// If there is too much text the word is wrapped using nothing
					// Ex.
					// |The fox jumped over the brid|
					// |ge.                         |
					NONE,
					// If there is too much text the word is wrapped using a hyphen
					// Ex.
					// |The fox jumped over the bri-|
					// |dge.                        |
					HYPHEN,
					// If there is too much text the word is wrapped using the closest
					// defined delimiter
					// |My favorite colors are: red,|
					// | blue, green, yellow and    |
					// |purple.                     |
					DELIMITER,
					// If there is too much text the word is wrapped using the closest
					// defined delimiter in English using a preset amount of delimiters
					// |My favorite colors are: red,|
					// | blue, green, yellow and    |
					// |purple.                     |
					// This looks the same as above but English delimiters cross over
					// a lot with common spacing programming delimiters
					ENGLISH_DELIMITER
				};
				enum class Vertical_Bias {
					// |RED                         |
					// |                            |
					// |                            |
					TOP,
					// |                            |
					// |RED                         |
					// |                            |
					CENTER,
					// |                            |
					// |                            |
					// |RED                         |
					BOTTOM
				};
				enum class Horizontal_Bias {
					// |RED                         |
					LEFT,
					// |            RED             |
					CENTER,
					// |                         RED|
					RIGHT
				};
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				std::wstring_view m_text;
				std::wstring_view m_font_type;
				glm::vec2 m_font_size;

				uint32_t m_layer;

				glm::vec2 m_position;
				glm::vec2 m_size;

				st::Texture* m_backaround_texture;
				glm::vec4 m_backaround_color;

				float m_border_size;
				st::Texture* m_border_texture;
				glm::vec4 m_border_color;

				Button_Events m_user_defined_events;

				Button_Structure::Border_Style m_border_style;

				Text_Box_Structure::Type m_box_type;
				Text_Box_Structure::Wrapping_Style m_wrapping_type;
				Text_Box_Structure::Vertical_Bias m_vertical_bias;
				Text_Box_Structure::Horizontal_Bias m_horizontal_bias;
			};
			struct Text_Settings_1 {
			// Friends
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				const glm::vec4 m_default_color;
				const std::vector<glm::vec4> m_colors;
				const st::Text::Color_Settings m_settings;
				const std::wstring_view p_font_type;
			};
			struct Text_Settings_2 {
			// Friends
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				const glm::vec4 m_default_color;
				const std::vector<glm::vec4> m_colors;
				const std::vector<std::string> m_delimiters;
				const st::Text::Color_Settings m_settings;
				const std::wstring_view p_font_type;
			};
			struct Text_Settings_3 {
			// Friends
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				const glm::vec4 m_default_color;
				const std::wstring m_font_type;
				const st::Text::Color_Settings m_settings;
				const std::wstring_view p_font_type;
				const std::vector<std::pair<glm::vec4, std::vector<std::wstring>>> m_colors;
			};
			struct Text_Settings_4 {
			// Friends
			// Default Class Structures 
			public:
			private:
			// Public Functions/Macros  
			public:
			// Public Variables        
			public:
				const glm::vec4 m_default_color;
				const std::vector<std::string> m_delimiters;
				const std::wstring m_font_type;
				const st::Text::Color_Settings m_settings;
				const std::vector<std::pair<glm::vec4, std::vector<std::wstring>>> m_colors;
			};
			class Text_Box {
			// Friends
			// Default Class Structures
			public:
				Text_Box(const Text_Box_Structure& p_text_box, const glm::vec4& p_color);

				Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_1& p_settings);
				Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_2& p_settings);
				Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_3& p_settings);
				Text_Box(const Text_Box_Structure& p_text_box, const Text_Settings_4& p_settings);

				~Text_Box();

				Text_Box() = delete;
				Text_Box(const Text_Box&) = delete;
			private:
			// Public Functions/Macros 
			public:
				void Render();

				void Set_Layer(uint32_t p_layer);
				void Set_Position(const glm::vec2& p_position);
				void Set_Size(const glm::vec2& p_size);
				void Set_Color(const glm::vec4& p_color);

				void Attach_To(glm::vec2* p_position);
				void Set_Offset(const glm::vec2& p_offset);

				const uint32_t& Layer() const;
				const glm::vec2& Position() const;
				const glm::vec2& Size() const;
				Button* Backaround() const;
				const std::wstring_view& Text() const;
				const std::vector<st::Text*>& Lines() const;
				const glm::vec2 Text_Size() const;

				const Text_Box_Structure::Type Fitting_Type() const;
				const Text_Box_Structure::Wrapping_Style Wrapping_Style() const;
			// Public Variables
			public:
			// Private Functions/Macros
			private:
				//void Process_Text();
			// Private Variables
			private:
				uint32_t m_layer;

				Button* m_backaround;

				std::wstring m_text_string;
				std::vector<st::Text*> m_lines;
				glm::vec2 m_text_size;
				glm::vec4 m_default_color;

				const Text_Box_Structure::Type m_box_type;
				const Text_Box_Structure::Wrapping_Style m_wrapping_type;
			};
			class Nested_Drop_Down_Box {
			// Friends
			// Default Class Structures
			public:
			private:
			// Public Functions/Macros 
			public:
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
			};
			class Text_Input_Box {
			// Friends
			// Default Class Structures
			public:
			private:
			// Public Functions/Macros 
			public:
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
			};
			class Drop_Box {
			// Default Class Structures
			public:
			private:
			// Public Functions/Macros 
			public:
			// Public Variables
			public:
			// Private Functions/Macros
			private:
			// Private Variables
			private:
			};
		UI_NAMESPACE_END
	EX_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_USER_INTERFACE
