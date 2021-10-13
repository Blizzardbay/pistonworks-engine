#include "engine_control\engine_control.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	int32_t er::Engine_Error::PW_LINE_ = 0;
	const wchar_t* er::Engine_Error::PW_FILE_ = new wchar_t[2];

	int32_t cm::Engine_Constant::m_window_width = 0;
	int32_t cm::Engine_Constant::m_window_height = 0;
	int32_t cm::Engine_Constant::m_hafe_window_width = 0;
	int32_t cm::Engine_Constant::m_hafe_window_height = 0;

	const wchar_t* cm::Engine_Constant::m_window_name = L"";
	PW_DUNI_PTR(GLFWwindow, cm::Engine_Constant::Destroy_GLFW) cm::Engine_Constant::m_current_window = nullptr;

	int32_t cm::Engine_Constant::m_mouse_x_position;
	int32_t cm::Engine_Constant::m_mouse_y_position;

	const float cm::Engine_Constant::m_inverse_z_tan = -(1.0f / tan(glm::radians(45.0f / 2.0f)));

	int32_t cm::Engine_Constant::m_frames = 0;
	int32_t cm::Engine_Constant::m_last_frames = -1;
	bool cm::Engine_Constant::m_engine_start = true;

	std::clock_t cm::Engine_Constant::m_start_time{ 0 };
	std::clock_t cm::Engine_Constant::m_end_time{ 0 };
	float cm::Engine_Constant::m_delta_time{ 0.0f };
	float cm::Engine_Constant::m_elapsed_time{ 0 };
	const float cm::Engine_Constant::m_fps_max{ 100000.0f };
	const float cm::Engine_Constant::m_fps_constant{ 1.0f / m_fps_max };

	const glm::vec2 cm::Engine_Constant::m_physics_gravity{ glm::vec2(0.0f, -10.0f) };

	uint64_t st::Model::model_counter{ 0 };
	uint64_t st::Model::model_id_assigner{ 0 };

	std::wstring co::Engine_Queue::project_name{ };

	std::wstring* co::Engine_Queue::current_scene{ nullptr };
	std::map<std::wstring, st::Game_Scene*> co::Engine_Queue::scene_directory{};
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
	// Engine_Control::Destroy_GLFW
	// Static Declarations
	// Class Members
	// End of Class Members
	// Engine_Control
	// Static Declarations
		

	// Class Members
		Engine_Control::Engine_Control():
				main_window{} {
		}
		Engine_Control::~Engine_Control() {
		}
		void Engine_Control::Init_Engine(const wchar_t* display_name, int32_t display_width, int32_t display_height) {
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
				PW_GLFW_VOID_CALL(glfwSetErrorCallback(er::Engine_Error::PW_GLFW_Callback_Handle));

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

				char* v_display_name = pw::cm::Engine_Constant::To_Char(display_name);
				// For creating a window to use for the application
				main_window = PW_DUNI_PTR(GLFWwindow, cm::Engine_Constant::Destroy_GLFW)(glfwCreateWindow(
					display_width, display_height,
					v_display_name,
					NULL, NULL));
				delete[] v_display_name;
				// For checking if any errors occurred
				if (!main_window) {
					printf("|%s|GL Function Error: %s\n|The Error Is On Line: %d\n|In File: %s\n", __TIME__, "Function Error", __LINE__ - 6, __FILE__);
				}
				#ifdef PW_DEBUG_MODE
					else {
						printf("|%s|GLFW Function Succeed: %s\n", __TIME__, "No Error");
					}
				#endif // PW_DEBUG_MODE
				// Set the current window
				cm::Engine_Constant::Set_Window(&*main_window);
				// For setting the current context for GLEW to use 
				PW_GLFW_VOID_CALL(glfwMakeContextCurrent(main_window.get()));

				// Enable Transparent textures
				PW_GL_VOID_CALL(glEnable(GL_BLEND), false);
				PW_GL_VOID_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);
			}
			//////////////////////////////////
			// Constant Settings
			//////////////////////////////////
			{
				int32_t buffer_width = display_width;
				int32_t buffer_height = display_height;

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window.get(), &buffer_width, &buffer_height));

				cm::Engine_Constant::Set_Window_Width((uint32_t*)&buffer_width);
				cm::Engine_Constant::Set_Window_Height((uint32_t*)&buffer_height);
				buffer_width = buffer_width / 2;
				cm::Engine_Constant::Set_Hafe_Window_Width((uint32_t*)&buffer_width);
				buffer_height = buffer_height / 2;
				cm::Engine_Constant::Set_Hafe_Window_Height((uint32_t*)&buffer_height);
				cm::Engine_Constant::Set_Window_Name(display_name);
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

				#ifdef FREEIMAGE_LIB
					PW_FI_VOID_CALL(FreeImage_Initialise());
				#endif
				
			}
			//////////////////////////////////
			// Icon Setting
			//////////////////////////////////
			{
				PW_SRD_PTR(GLFWimage) icon = std::make_shared<GLFWimage>(pw::co::File_Loader::Load_Icon(L"Icon.png", true));

				PW_GLFW_VOID_CALL(glfwSetWindowIcon(main_window.get(), 1, icon.get()));

				pw::co::File_Loader::Unload_Icon();
			}
			//////////////////////////////////
			// Finish Up Program Things
			//////////////////////////////////
			{
				// For setting up view port size
				PW_GL_VOID_CALL(glViewport(0, 0, cm::Engine_Constant::Window_Width(), cm::Engine_Constant::Window_Height()), true);
				// For specifying which instance of the window will be used for callback
				PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(main_window.get(), this));

				PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT), true);
			}
		}
		void Engine_Control::Run_Engine() {
			//////////////////////////////////
			// Init Key Engine Objects
			//////////////////////////////////
			st::Shader shader{};
			{
				shader.Create_Shader(L"engine_files/engine_resource/engine_essential/engine_shader/vertex_shader.shader", L"engine_files/engine_resource/engine_essential/engine_shader/fragment_shader.shader");

				st::Text_Renderer::Load_Engine_Font();

				Init_Game();

				Engine_Queue::Load_From_Dir(L"game/");

				#ifdef PW_DEBUG_MODE
					printf("|----------------------------------------\n");
					printf("|%s|Object Creation\n", __TIME__);
					printf("|----------------------------------------\n");
				#endif // !PW_DEBUG_CODE
			}
			//ie::Game_Scene* scene = Engine_Queue::Current_Scene();
			//scene->Create_Event(cm::Engine_Constant::PW_CLICK_EVENT, GLFW_MOUSE_BUTTON_1, GLFW_PRESS, std::make_shared<ie::Actor_Model>(*static_cast<ie::Actor_Model*>(scene->Scene().at(0).get())),
				//std::make_shared<PW_FUNCTION>((PW_FUNCTION)Function), true);
			//scene->Create_Event(cm::Engine_Constant::PW_CLICK_EVENT, GLFW_MOUSE_BUTTON_2, GLFW_PRESS, std::make_shared<ie::Actor_Model>(*static_cast<ie::Actor_Model*>(scene->Scene().at(1).get())),
				//std::make_shared<PW_FUNCTION>((PW_FUNCTION)Function1), true);
			//////////////////////////////////
			// Run Engine
			//////////////////////////////////
			{
				while (Engine_Control::Should_Close()) {
					// Calculate needed time constants
					cm::Engine_Constant::Calc_Elapsed_Time(main_window.get());
					cm::Engine_Constant::Calc_Delta_Time();

					// Engine Input
					PW_GLFW_VOID_CALL(glfwPollEvents());
				    // Any concurrent events need to be dealt with 
					//Engine_Queue::Current_Scene()->Input()->Poll_Active_Events();
					// Engine Frame / Shader
					PW_GL_VOID_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f), false);
					PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
					// Update the projection information for the vertex shader / fragment shader
					shader.Update_Projection();
				
					Before_Queue();

					// Engine Queue
					Engine_Queue::Run_Queue();

					After_Queue();

					// Swap Open GL Buffers
					Update_Engine_State();
					// Wait until the next frame should run
					cm::Engine_Constant::Wait();
				}
			}
		}
		void Engine_Control::Terminate_Engine() {
			//////////////////////////////////
			// Engine Clean Up
			//////////////////////////////////
			{
				Engine_Queue::Clear_Queue();
				#ifdef FREEIMAGE_LIB
					PW_FI_VOID_CALL(FreeImage_DeInitialise());
				#endif
				PW_GLFW_VOID_CALL(glfwTerminate());
			}
		}
		void Engine_Control::Create_Callbacks() const {
			// Set up callback functions for handling key/mouse input
			PW_GLFW_VOID_CALL(glfwSetKeyCallback(main_window.get(), Engine_Input::Handle_Keyboard));
			PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(main_window.get(), Engine_Input::Handle_Mouse_Movement));
			PW_GLFW_VOID_CALL(glfwSetMouseButtonCallback(main_window.get(), Engine_Input::Handle_Mouse_Button))
			// Handle resizing events with ease
			PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(main_window.get(), Engine_Input::Handle_Resize));
			// Handle Scroll Wheel Input
			PW_GLFW_VOID_CALL(glfwSetScrollCallback(main_window.get(), Engine_Input::Handle_Mouse_Scroll));
			// Create callback for image loading using FreeImage
			PW_FI_VOID_CALL(FreeImage_SetOutputMessage(er::Engine_Error::PW_FI_Callback_Handle));
		}
		void Engine_Control::Update_Engine_State() {
			PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window.get()));
		}
		bool Engine_Control::Should_Close() const {
			return !glfwWindowShouldClose(main_window.get());
		}
	// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////

int main(int argc, char* argv[]) {
	pw::co::Engine_Control engine{};
	engine.Init_Engine(L"Pistonworks Window");
	engine.Run_Engine();
	engine.Terminate_Engine();
	engine.~Engine_Control();
	return 0;
}