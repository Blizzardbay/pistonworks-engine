#include "engine_headers\engine_control.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace pw {
/* Engine_Control           */
/* Static Declarations      */
	int Engine_Error::PW_LINE_ = 0;
	const char* Engine_Error::PW_FILE_ = "";

	GLfloat Engine_Constant::window_width = 0.0f;
	GLfloat Engine_Constant::window_height = 0.0f;
	GLint Engine_Constant::buffer_width = 0;
	GLint Engine_Constant::buffer_height = 0;
	GLint Engine_Constant::hafe_buffer_width = 0;
	GLint Engine_Constant::hafe_buffer_height = 0;

	const char* Engine_Constant::window_name = "";

	float Engine_Constant::previous_time = 0.0f;
	float Engine_Constant::current_time = 0.0f;
	float Engine_Constant::delta_time = 0.0f;

	const float Engine_Constant::fps_constant = (1.0f / 60.0f);
/* Class Members            */
	void Engine_Control::Init_Engine(const char* display_name, short int display_width, short int display_height) {
#ifdef PW_DEBUG_MODE
		printf("|****************************************\n");
		printf("|Initialization Code\n");
		printf("|****************************************\n");
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
		printf("|****************************************\n");
		printf("|Display Creation Code\n");
		printf("|****************************************\n");
#endif // PW_DEBUG_MODE

		// For creating a window to use for the application
		main_window = glfwCreateWindow(
			display_width, display_height,
			display_name,
			NULL, NULL);
		// For checking if any errors occurred
		if (!main_window) {
			printf("|GL Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", "Function Error", __LINE__ - 1, __FILE__);
		}
#ifdef PW_DEBUG_MODE
		else {
			printf("|GLFW Function Succeed: %s\n", "No Error");
		}
#endif // !PW_DEBUG_MODE

		GLint buffer_width = 0;
		GLint buffer_height = 0;

		// For retrieving the buffer sizes for our given window
		PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height));

		Engine_Constant::Set_Buffer_Width(buffer_width);
		Engine_Constant::Set_Buffer_Height(buffer_height);
		Engine_Constant::Set_Hafe_Buffer_Width(buffer_width);
		Engine_Constant::Set_Hafe_Buffer_Height(buffer_height);

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
		printf("|****************************************\n");
		printf("|Glew/Program Initialization\n");
		printf("|%s\n", glGetString(GL_VERSION));
		printf("|****************************************\n");
#endif // !PW_DEBUG_CODE

		PW_GL_CALL(glewInit() == GLEW_OK);

		// Enable Transparent textures
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// For enabling testing of depth in a window
		//glEnable(GL_DEPTH_TEST);
		// For setting up view port size
		PW_GL_VOID_CALL(glViewport(0, 0, Engine_Constant::GetBufferWidth(), Engine_Constant::GetBufferHeight()));
		// For specifying which instance of the window will be used for callback
		PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(main_window, this));

		PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT));

		Engine_Constant::Set_Window_Width(display_width);
		Engine_Constant::Set_Window_Height(display_height);
		Engine_Constant::Set_Window_Name(display_name);
	}
	void Engine_Control::Run_Engine() {
#ifdef PW_DEBUG_MODE
		printf("|****************************************\n");
		printf("|Shader Creation\n");
		printf("|****************************************\n");
#endif // !PW_DEBUG_CODE
		IE_Shader shader {};
		
		shader.Create_Shader("engine_files/engine_resource/vertex_shader.shader", "engine_files/engine_resource/fragment_shader.shader");
#ifdef PW_DEBUG_MODE
		printf("|****************************************\n");
		printf("|Texture Loading\n");
		printf("|****************************************\n");
#endif // !PW_DEBUG_CODE

		IE_Camera camera( glm::vec3(0.0f,0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f),-90.0f,0.0f,5.0f,1.0f );

		glm::vec3 player_color(0.0f);
		IE_Texture texture_2 = IE_Texture(IE_Texture::Find_Color_Texture("D16", IE_Texture::Default_Texture::BLUE, player_color).c_str());
		IE_Model model = IE_Model(IE_Model::Model_Types::SQUARE, texture_2, glm::vec2(400.0f, 400.0f), 0.0f, glm::vec2(32.0f, 32.0f),player_color);
		IE_Player::Init_Player(model);

		Engine_Input::Set_Default_Binds(true);

		Engine_Input::Init_Default_Binds();

		Engine_Queue::Load_From_Dir("engine_files/engine_resource/");

		float start_time = (float)glfwGetTime();
		float end_time = (float)glfwGetTime();
		float elapsed_time = end_time - start_time;

		int frames = 0;

		while (pw::Engine_Control::Should_Close()) {
			elapsed_time = end_time - start_time;
			if (elapsed_time >= 1.0f) {
				std::string str = Engine_Constant::Get_Window_Name();
				str.insert(str.size(), " Fps:");
				str.insert(str.size(), std::to_string(frames).c_str());
				frames = 0;
				start_time = end_time;
				glfwSetWindowTitle(this->main_window, str.c_str());
			}
			Engine_Constant::Calc_Delta_Time();
			if (Engine_Constant::Get_Delta_Time() <= Engine_Constant::Get_FPS_Constant()) {
				glfwPollEvents();

				frames++;

				Engine_Input::Poll_Active_Events();

				glClearColor(0.0f, 0.16f, 0.16f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				shader.Update_Projection(camera);

				Engine_Queue::Run_Queue(shader);
				/*
				move.Update_Position(glm::vec2(
					floorf(Engine_Input::Get_Cursor_Position().x / 32.0f) * 32.0f,
					ceilf(Engine_Input::Get_Cursor_Position().y / 32.0f) * 32.0f));
				move.Render(shader);
				*/

				IE_Player::Draw_Player(shader);

				Update_Engine_State();
				auto duration = std::chrono::duration_cast<std::chrono::seconds>((std::chrono::duration<float>)(Engine_Constant::Get_FPS_Constant() - Engine_Constant::Get_Delta_Time()));
				std::this_thread::sleep_for(duration);
			}
			end_time = (float)glfwGetTime();
		}
		IE_Player::Delete_Player();
	}
	void Engine_Control::Terminate_Engine() {
		PW_GLFW_VOID_CALL(glfwDestroyWindow(main_window));
		main_window = nullptr;
		PW_GLFW_VOID_CALL(glfwTerminate());
	}
	void Engine_Control::Create_Callbacks() const {
		/* Set up callback functions for handling key/mouse input */
		PW_GLFW_VOID_CALL(glfwSetKeyCallback(main_window, Engine_Input::Handle_Keys));
		PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(main_window, Engine_Input::Handle_Mouse));
		/* Handle resizing events with ease                       */
		PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(main_window, Engine_Input::Handle_Resize));
	}
	void Engine_Control::Update_Engine_State() {
		PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window));
	}
}
int main(int argc, char* argv[]) {
	pw::Engine_Control engine{};
	engine.Init_Engine("Pistonworks Window");
	engine.Run_Engine();
	engine.Terminate_Engine();
	return 0;
}