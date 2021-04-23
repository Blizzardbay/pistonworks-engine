#include "engine_headers\engine_control.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	// Engine_Control::Destroy_GLFW
	// Static Declarations
	// Class Members
		PW_VOID pw::Engine_Control::Destroy_GLFW::operator()(GLFWwindow* window) {
			PW_GLFW_VOID_CALL(glfwDestroyWindow(window));
		}
	// End of Class Members
	// Engine_Control
	// Static Declarations
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

		PW_INT Engine_Constant::frames = 0;
		PW_INT Engine_Constant::last_frames = 0;
		PW_BOOL Engine_Constant::engine_start = true;

		std::clock_t Engine_Constant::start_time{ 0 };
		std::clock_t Engine_Constant::end_time{ 0 };
		PW_FLOAT Engine_Constant::delta_time{ 0.0f };
		PW_FLOAT Engine_Constant::elapsed_time{ 0 };
		const PW_FLOAT Engine_Constant::fps_max{ 144.0f };
		const PW_FLOAT Engine_Constant::fps_constant{ 1.0f / fps_max };

		const glm::vec2 Engine_Constant::physics_gravity{ glm::vec2(0.0f, -9.8f) };
	// Class Members
		Engine_Control::Engine_Control():
				main_window{} {
		}
		Engine_Control::~Engine_Control() {
		}
		PW_VOID Engine_Control::Init_Engine(PW_CSTRING display_name, PW_SINT display_width, PW_SINT display_height) {
			//////////////////////////////////
			// Settings
			//////////////////////////////////
			{
				#ifdef PW_DEBUG_MODE
					printf("|----------------------------------------\n");
					printf("|%s|Load Settings      ( Complete )\n", __TIME__);
					printf("|----------------------------------------\n");
				#endif // PW_DEBUG_CODE

				// For Handling GLFW Errors
				PW_GLFW_VOID_CALL(glfwSetErrorCallback(Engine_Error::PW_GLFW_Callback_Handle));

				// For the initializing GLFW
				PW_GLFW_CALL(glfwInit());
				// For setting the major  \/ and minor \/ version of GLFW
				// Version---------------->3     .      3
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
				// For only using newer code and excluding other older code
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
				// For allowing newer than are defined version code for able use
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));

				// For allowing modern extension features
				glewExperimental = GL_TRUE;

				// Enable Transparent textures
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
			}
			//////////////////////////////////
			// Window Creation
			//////////////////////////////////
			{
				#ifdef PW_DEBUG_MODE
					printf("|----------------------------------------\n");
					printf("|%s|Display Creation   ( Complete )\n", __TIME__);
					printf("|----------------------------------------\n");
				#endif // PW_DEBUG_MODE

				// For creating a window to use for the application
				main_window = PW_DUNI_PTR(GLFWwindow, Destroy_GLFW)(glfwCreateWindow(
					display_width, display_height,
					(const char*)display_name,
					NULL, NULL));
				// For checking if any errors occurred
				if (!main_window) {
					printf("|%s|GL Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, "Function Error", __LINE__ - 6, __FILE__);
				}
				#ifdef PW_DEBUG_MODE
					else {
						printf("|%s|GLFW Function Succeed: %s\n", __TIME__, "No Error");
					}
				#endif // PW_DEBUG_MODE

				// For setting the current context for GLEW to use 
				PW_GLFW_VOID_CALL(glfwMakeContextCurrent(main_window.get()));
			}
			//////////////////////////////////
			// Constant Settings
			//////////////////////////////////
			{
				PW_INT buffer_width = display_width;
				PW_INT buffer_height = display_height;

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window.get(), &buffer_width, &buffer_height));

				Engine_Constant::Set_Window_Width(buffer_width);
				Engine_Constant::Set_Window_Height(buffer_height);
				Engine_Constant::Set_Hafe_Window_Width(buffer_width / 2);
				Engine_Constant::Set_Hafe_Window_Height(buffer_height / 2);
				Engine_Constant::Set_Window_Name(display_name);
			}
			//////////////////////////////////
			// Input Callback Init
			//////////////////////////////////
			{
				// For enabling various callbacks to input functions
				Create_Callbacks();
				/* For enabling or disabling certain settings for window properties*/
				/* GLFW_CURSOR : For enabling or disabling the mouse in the window */
				/* GLFW_CURSOR_DISABLED : For off , GLFW_CURSOR_NORMAL : For on    */
				PW_GLFW_VOID_CALL(glfwSetInputMode(main_window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL));
				//PW_GLFW_VOID_CALL(glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
			}
			//////////////////////////////////
			// Glew/Program Initialization
			//////////////////////////////////
			{
				// For checking if initializing GLEW failed
				PW_GL_CALL(glewInit() == GLEW_OK);
				#ifdef PW_DEBUG_MODE
					printf("|----------------------------------------\n");
					printf("|%s|Glew/Program Initialization\n", __TIME__);
					printf("|%s|%s\n", __TIME__, glGetString(GL_VERSION));
					printf("|----------------------------------------\n");
				#endif // !PW_DEBUG_CODE
			}
			//////////////////////////////////
			// Icon Setting
			//////////////////////////////////
			{
				ie::Icon icon_data = ie::Icon(ie::Icon::Find_Icon("Test_Icon.png").c_str());
				PW_SRD_PTR(GLFWimage) icon = std::make_shared<GLFWimage>();
				icon->width = icon_data.Width();
				icon->height = icon_data.Height();
				icon->pixels = icon_data.Data();

				PW_GLFW_VOID_CALL(glfwSetWindowIcon(main_window.get(), 1, icon.get()));

				icon_data.Delete();
			}
			//////////////////////////////////
			// Finish Up Program Things
			//////////////////////////////////
			{
				// For setting up view port size
				PW_GL_VOID_CALL(glViewport(0, 0, Engine_Constant::Window_Width(), Engine_Constant::Window_Height()), true);
				// For specifying which instance of the window will be used for callback
				PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(main_window.get(), this));

				PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT), true);
			}
		}
		PW_VOID Engine_Control::Run_Engine() {
			//////////////////////////////////
			// Init Key Engine Objects
			//////////////////////////////////
			ie::Shader shader{};
			{
				shader.Create_Shader("engine_files/engine_resource/vertex_shader.shader", "engine_files/engine_resource/fragment_shader.shader");

				Engine_Input::Init_Default_Binds();

				Engine_Queue::Load_From_Dir("engine_files/engine_resource/");

				Engine_Control::Create_Player();

				#ifdef PW_DEBUG_MODE
					printf("|----------------------------------------\n");
					printf("|%s|Object Creation\n", __TIME__);
					printf("|----------------------------------------\n");
				#endif // !PW_DEBUG_CODE
			}
			//////////////////////////////////
			// Run Engine
			//////////////////////////////////
			{
				while (Engine_Control::Should_Close()) {
					// Calculated needed time constants
					Engine_Constant::Calc_Elapsed_Time(main_window.get());
					Engine_Constant::Calc_Delta_Time();

					// Engine Input
					PW_GLFW_VOID_CALL(glfwPollEvents());

					Engine_Input::Poll_Active_Events();
					// Engine Frame / Shader
					glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
					PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);

					shader.Update_Projection();
				
					// Engine Queue
					Engine_Queue::Run_Queue();
				  
					// Swap Open GL Buffers
					Update_Engine_State();
					// Wait until the next frame should run
					Engine_Constant::Wait();
				}
			}
		}
		PW_VOID Engine_Control::Create_Player() {
			glm::vec3 player_color(0.0f);
			ie::Texture texture_2 = ie::Texture(ie::Texture::Find_Color_Texture("D16", ie::Texture::Default_Texture::BLUE, player_color).c_str());
			PW_SRD_PTR(ie::Dynamic_Model) model = std::make_shared<ie::Dynamic_Model>(
				ie::Model_Types::SQUARE, texture_2, glm::vec2(400.0f, 200.f), 0.0f, glm::vec2(32.0f, 32.0f), player_color);
			Engine_Queue::Current_Scene()->Scene_Physics()->Add_Object(model, b2_dynamicBody, Engine_Constant::PW_PLAYER_ID, true);
			ie::Game_Scene::Player().Init_Player(model, Engine_Queue::Current_Scene()->Scene_Physics()->Access_Memeber(Engine_Constant::PW_PLAYER_ID)->Body());
		}
		PW_VOID Engine_Control::Terminate_Engine() {
			//////////////////////////////////
			// Engine Clean Up
			//////////////////////////////////
			{
				Engine_Queue::Clear_Queue();
				PW_GLFW_VOID_CALL(glfwTerminate());
			}
		}
		PW_VOID Engine_Control::Create_Callbacks() const {
			// Set up callback functions for handling key/mouse input
			PW_GLFW_VOID_CALL(glfwSetKeyCallback(main_window.get(), Engine_Input::Handle_Keyboard));
			PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(main_window.get(), Engine_Input::Handle_Mouse_Movement));
			PW_GLFW_VOID_CALL(glfwSetMouseButtonCallback(main_window.get(), Engine_Input::Handle_Mouse_Button))
			// Handle resizing events with ease
			PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(main_window.get(), Engine_Input::Handle_Resize));
			// Handle Scroll Wheel Input
			PW_GLFW_VOID_CALL(glfwSetScrollCallback(main_window.get(), Engine_Input::Handle_Mouse_Scroll));
		}
		PW_VOID Engine_Control::Update_Engine_State() {
			PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window.get()));
		}
		PW_BOOL Engine_Control::Should_Close() const {
			return !glfwWindowShouldClose(main_window.get());
		}
	// End of Class Members
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////

int main(int argc, char* argv[]) {
	pw::Engine_Control engine = pw::Engine_Control();
	engine.Init_Engine((pw::PW_CSTRING)"Pistonworks Window");
	engine.Run_Engine();
	engine.Terminate_Engine();
	engine.~Engine_Control();
	return 0;
}