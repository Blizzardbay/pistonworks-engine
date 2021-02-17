#include "engine_headers\engine_control.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace pw {
/* Engine_Control           */
/* Static Declarations      */
	PW_INT Engine_Error::PW_LINE_ = 0;
	PW_CSTRING Engine_Error::PW_FILE_ = "";

	PW_SUINT Engine_Constant::window_width = 0;
	PW_SUINT Engine_Constant::window_height = 0;
	PW_SUINT Engine_Constant::hafe_window_width = 0;
	PW_SUINT Engine_Constant::hafe_window_height = 0;

	PW_CSTRING Engine_Constant::window_name = (PW_CSTRING) "";

	PW_INT Engine_Constant::mouse_x_position;
	PW_INT Engine_Constant::mouse_y_position;

	const PW_FLOAT Engine_Constant::inverse_z_tan = -(1.0f / tan(glm::radians(45.0f / 2.0f)));

	std::chrono::system_clock::time_point Engine_Constant::previous_time;
	std::chrono::system_clock::time_point Engine_Constant::current_time;
	std::chrono::duration<PW_FLOAT, std::milli> Engine_Constant::delta_time(0);

	const std::chrono::duration<PW_FLOAT, std::milli> Engine_Constant::fps_constant(16.7000008f);

	PW_INT ie::Camera::camera_zoom = -1;
	PW_FLOAT ie::Camera::camera_x_position = 0.0f;
	PW_FLOAT ie::Camera::camera_y_position = 0.0f;

	ie::Dynamic_Model ie::Player::player_model;
/* Class Members            */
	PW_VOID Engine_Control::Init_Engine(PW_CSTRING display_name, PW_SINT display_width, PW_SINT display_height) {
#ifdef PW_DEBUG_MODE
		printf("|----------------------------------------\n");
		printf("|%s|Initialization Code\n", __TIME__);
		printf("|----------------------------------------\n");
#endif // !PW_DEBUG_CODE
		// For Handling GLFW Errors
		PW_GLFW_VOID_CALL(glfwSetErrorCallback(Engine_Error::PW_GLFW_Callback_Handle));

		/* For the initializing GLFW */
		PW_GLFW_CALL(glfwInit());
		/* For setting the major \/ and minor \/ version of GLFW*/
		/*Version---------------->3     .      3                */
		PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
		PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
		// For only using newer code and excluding other older code
		PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
		// For allowing newer than are defined version code for able use
		PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));
#ifdef PW_DEBUG_MODE
		printf("|----------------------------------------\n");
		printf("|%s|Display Creation Code\n", __TIME__);
		printf("|----------------------------------------\n");
#endif // PW_DEBUG_MODE
		// For creating a window to use for the application
		main_window = glfwCreateWindow(
			display_width, display_height,
			(const char*)display_name,
			NULL, NULL);
		// For checking if any errors occurred
		if (!main_window) {
			printf("|%s|GL Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, "Function Error", __LINE__ - 6, __FILE__);
		}
#ifdef PW_DEBUG_MODE
		else {
			printf("|%s|GLFW Function Succeed: %s\n", __TIME__, "No Error");
		}
#endif // !PW_DEBUG_MODE

		PW_INT buffer_width = display_width;
		PW_INT buffer_height = display_height;

		// For retrieving the buffer sizes for our given window
		PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height));

		Engine_Constant::Set_Window_Width(buffer_width);
		Engine_Constant::Set_Window_Height(buffer_height);
		Engine_Constant::Set_Hafe_Window_Width(buffer_width / 2);
		Engine_Constant::Set_Hafe_Window_Height(buffer_height / 2);
		Engine_Constant::Set_Window_Name(display_name);

		// For setting the current context for GLEW to use 
		PW_GLFW_VOID_CALL(glfwMakeContextCurrent(main_window));
		// For enabling various callbacks to input functions
		Create_Callbacks();
		/* For enabling or disabling certain settings for window properties*/
		/* GLFW_CURSOR : For enabling or disabling the mouse in the window */
		/* GLFW_CURSOR_DISABLED : For off , GLFW_CURSOR_NORMAL : For on    */
		PW_GLFW_VOID_CALL(glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
		//PW_GLFW_VOID_CALL(glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
		// For allowing modern extension features
		glewExperimental = GL_TRUE;
		// For checking if initializing GLEW failed
#ifdef PW_DEBUG_MODE
		printf("|----------------------------------------\n");
		printf("|%s|Glew/Program Initialization\n", __TIME__);
		printf("|%s|%s\n", __TIME__, glGetString(GL_VERSION));
		printf("|----------------------------------------\n");
#endif // !PW_DEBUG_CODE

		PW_GL_CALL(glewInit() == GLEW_OK);

		// Enable Transparent textures
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		ie::Icon icon_data = ie::Icon(ie::Icon::Find_Icon("Test_Icon.png").c_str());
		GLFWimage* icon = new GLFWimage();
		icon->width = icon_data.Width();
		icon->height = icon_data.Height();
		icon->pixels = icon_data.Data();

		PW_GLFW_VOID_CALL(glfwSetWindowIcon(main_window, 1, icon));

		icon_data.Delete();
		delete icon;
		icon = nullptr;

		// For setting up view port size
		PW_GL_VOID_CALL(glViewport(0, 0, Engine_Constant::Window_Width(), Engine_Constant::Window_Height()), true);
		// For specifying which instance of the window will be used for callback
		PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(main_window, this));

		PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT), true);
	}
	PW_VOID Engine_Control::Run_Engine() {
#ifdef PW_DEBUG_MODE
		printf("|----------------------------------------\n");
		printf("|%s|Shader Creation\n", __TIME__);
		printf("|----------------------------------------\n");
#endif // !PW_DEBUG_CODE
		ie::Shader shader {};
		
		shader.Create_Shader("engine_files/engine_resource/vertex_shader.shader", "engine_files/engine_resource/fragment_shader.shader");

		glm::vec3 player_color(0.0f);
		ie::Texture texture_2 = ie::Texture(ie::Texture::Find_Color_Texture("D16", ie::Texture::Default_Texture::BLUE, player_color).c_str());
		ie::Dynamic_Model model = ie::Dynamic_Model(ie::Dynamic_Model::Model_Types::SQUARE, texture_2, glm::vec2(400.0f, 400.0f), 0.0f, glm::vec2(32.0f, 32.0f),player_color);
		ie::Player::Init_Player(model);

		Engine_Input::Init_Default_Binds();

		Engine_Queue::Load_From_Dir("engine_files/engine_resource/");

		std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();
		std::chrono::duration<PW_FLOAT, std::milli> elapsed_time = end_time - start_time;

		PW_INT frames = 0;
		PW_INT last_frames = 0;

		while (Engine_Control::Should_Close()) {
			elapsed_time = end_time - start_time;
			if (last_frames != frames) {
				if (elapsed_time >= (std::chrono::duration<float, std::milli>)1000) {
					std::string str = (const char*)Engine_Constant::Window_Name();
					str.insert(str.size(), " Fps:");
					str.insert(str.size(), std::to_string(frames));
					frames = 0;
					start_time = end_time;
					glfwSetWindowTitle(this->main_window, str.c_str());
					last_frames = frames;
				}
			}
			Engine_Constant::Calc_Delta_Time();

			/* engine loop */
			glfwPollEvents();

			Engine_Input::Poll_Active_Events();

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Update_Projection();

			Engine_Queue::Run_Queue();

			ie::Player::Draw_Player();

			Update_Engine_State();

			frames++;

			/* wait until next frame */
			std::chrono::duration<PW_FLOAT, std::milli> calc(Engine_Constant::Delta_Time());
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(calc);
			std::this_thread::sleep_for(duration);

			end_time = std::chrono::system_clock::now();
		}
	}
	PW_VOID Engine_Control::Terminate_Engine() {
		Engine_Queue::Clear_Queue();
		ie::Player::Delete_Player();
		PW_GLFW_VOID_CALL(glfwDestroyWindow(main_window));
		main_window = nullptr;
		PW_GLFW_VOID_CALL(glfwTerminate());
	}
	PW_VOID Engine_Control::Create_Callbacks() const {
		/* Set up callback functions for handling key/mouse input */
		PW_GLFW_VOID_CALL(glfwSetKeyCallback(main_window, Engine_Input::Handle_Keyboard));
		PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(main_window, Engine_Input::Handle_Mouse_Movement));
		PW_GLFW_VOID_CALL(glfwSetMouseButtonCallback(main_window, Engine_Input::Handle_Mouse_Button))
		/* Handle resizing events with ease                       */
		PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(main_window, Engine_Input::Handle_Resize));
		/* Handle Scroll Wheel Input */
		PW_GLFW_VOID_CALL(glfwSetScrollCallback(main_window, Engine_Input::Handle_Mouse_Scroll));
	}
	PW_VOID Engine_Control::Update_Engine_State() {
		PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window));
	}
}
int main(int argc, char* argv[]) {
	pw::Engine_Control engine = pw::Engine_Control();
	engine.Init_Engine((PW_CSTRING)"Pistonworks Window");
	engine.Run_Engine();
	engine.Terminate_Engine();
	engine.~Engine_Control();
	return 0;
}
// Pending change to IE turned into as namespace....