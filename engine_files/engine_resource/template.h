//FILE_TYPE i.e HEADER_ONLY , DUAL_FILE
#ifndef H
#define H

//(FILE_TYPE)

/* C++ Headers              */
/* Project Headers          */
/* Engine Headers           */
/* Engine Macro Includes    */
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
/* Classes                  */
//
	/*                                             */
	/* -Class_Name
	 Description of class goes here.
	*/
	class class_name {
/* Default Class Structures */
	public:
		class_name();
		~class_name();
	private:
/* Public Functions/Macros  */
	public:
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
	};
/* Functions                */
/* Macros                   */
}
#endif // !H

//FILE_TYPE i.e HEADER_ONLY , DUAL_FILE
#ifndef H_IE
#define H_IE

//(FILE_TYPE)

/* C++ Headers              */
/* Project Headers          */
/* Engine Headers           */
/* Engine Macro Includes    */
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
		/* Classes                  */
		//
			/* -Class_Name
			 Description of class goes here.
			*/
		class class_name {
			/* Default Class Structures */
		public:
			class_name();
			~class_name();
		private:
			class_name(const class_name& other_) = delete;
			void operator=(const class_name& rhs) = delete;
			/* Public Functions/Macros  */
		public:
			/* Public Variables         */
		public:
			/* Private Functions/Macros */
		private:
			/* Private Variables        */
		private:
		};
		/* Functions                */
		/* Macros                   */
	}
}
#endif // !H_IE
