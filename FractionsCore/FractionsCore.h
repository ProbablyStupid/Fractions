/*
* this header is part of the fractions project and the main
* header for the fractions core.
* This header has HORRIBLE organization.
* Most names for anything from macros to functions may be incredibly long.
* 
* Target Machine: Windows, x64
* Target Compiler: MSVC (Microsoft Visual C++)
* 
* This header contains many things, many of which
* are unrelated to fractions core, but required by
* fractions core.
* 
* a rough organization is this:
* 
* BUILD MACROS
* FOREIGN INCLUDE
* 
* MACROS
* ++ CONSOLE ++
* 
* STRUCTS & METHODS
* 
* ++ ANYTHING ADDITIONAL ++
* NOTE:
* Whilst the fractions project is mainly targeting windows,
* in this header (Fractions Core), there are some macros / preprocessor
* statements that may or may not help to build / run this on other
* platforms / compilers.
*/

#pragma once

// old deprecated code
/*
#include <gl/glew.h>
#include <gl/wglew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// TODO: make a better / more efficient dynamic array implementation if posibble
#include <vector>

#ifndef NO_WINDOWS
#include <windows.h>
#endif

#ifndef NO_FRACTIONS_CORE_NODISCARD

#define F_NODISCARD [[nodiscard]]

#else

#ifdef REPLACE_FRACTIONS_CORE_NODISCARD

#define F_NODISCARD

#endif

#endif

#ifndef NO_DEBUGBREAK
#ifndef NO_WINDOWS
#define __DEBUGBREAK() __debugbreak()
#else
// ******************** PLACE OTHER COMPILER SPECIFIC BREAKPOINT FUNCTIONS HERE 
#endif
#else
#define __DEBUGBREAK()
#endif

#ifndef NO_FRACTIONS_CORE_ASSERT
#define ASSERT(X) if (!(X)) __debugbreak();
#else
#define ASSERT(X) ;
#endif

#ifndef NO_FRACTIONS_CORE_OPENGL_ERROR_CHECKING

// TODO: this is horibble, I need to make this better
static void GLclearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		//std::cout << ANSI_COLOR_YELLOW << "ERROR CODE:" << error << ANSI_COLOR_RESET << std::endl;
		//char* log = (char*)glewGetErrorString(error);
		//RACTIONS_WARNING_(log);				// __LINE__ DOES NOT FULLY WORK YET - I don't know why...
		std::cout << "ERROR CODE: " << error << "\nLINE: " << __LINE__ << std::endl;
	}
	return true;
}

// TODO: maybe improve this
#ifndef RELEASE
#define GLCall(X) GLclearErrors(); \
					X;\
					ASSERT(GLLogCall())
#else
#define GLCall(x) x;
#endif

#else

#ifdef REPLACE_FRACTIONS_CORE_OPENGL_ERROR_CHECKING

#define GLclearErrors()
#define GLLogCall()
#define GLCall()

#endif

#endif

#define UINT8_F unsigned char
#define UINT16_F unsigned short int
#define UINT32_F unsigned int
#define UINT64_F unsigned long long int

typedef unsigned int fractions_core_id;
typedef void (*basic_action)(void);
typedef unsigned long long int fractions_core_size;
#define fractions_core_matrix glm::mat4

#ifndef NO_FRACTIONS_CORE_FILE_IO

// uses the C file API 
F_NODISCARD const char* fractions_core_get_file_text_f(const char*);
// uses the C++ file API 
F_NODISCARD std::string fractions_core_get_file_text_s(const char*);

#else

#ifdef REPLACE_FRACTIONS_CORE_FILE_IO

#define fractions_core_get_file_text_f()
#define fractions_core_get_file_text_s()

#endif

#endif

typedef struct fractions_core_vec4f
{
	float one, two, three, four;
} fractions_core_vec4f;

typedef struct fractions_core_shader_uniform_V4
{
	const char* uniform_name;
	fractions_core_vec4f value;
} fractions_core_shader_uniform_V4;
typedef struct fractions_core_shader_uniform_UI
{
	const char* uniform_name;
	unsigned int VALUE;
} fractions_core_shader_uniform_UI;
typedef struct fractions_core_shader_uniform_I
{
	const char* uniform_name;
	int VALUE;
} fractions_core_shader_uniform_I;
typedef struct fractions_core_shader_uniform_F
{
	const char* uniform_name;
	float value;
} fractions_core_shader_uniform_F;
typedef struct fractions_core_shader_uniform_M {

	const char* uniform_name;
	fractions_core_matrix matrix;

} fractions_core_shader_uniform_M;

#define FRACTIONS_CORE_VERTEX_SHADER GL_VERTEX_SHADER
#define FRACTIONS_CORE_FRAGMENT_SHADER GL_FRAGMENT_SHADER

template <typename t>
struct fractions_core_list
{
	t* data;
	fractions_core_size size;
};

typedef struct fractions_core_shader_uniforms
{
	
	bool UI_uniforms = false, I_uniforms = false,
		F_uniforms = false, M_uniforms = false, V4_uniforms = false;

	fractions_core_list<fractions_core_shader_uniform_UI> uniforms_UI;
	fractions_core_list<fractions_core_shader_uniform_I> uniforms_I;
	fractions_core_list<fractions_core_shader_uniform_F> uniforms_F;
	fractions_core_list<fractions_core_shader_uniform_M> uniforms_M;
	fractions_core_list<fractions_core_shader_uniform_V4> uniforms_V4; // TODO

} fractions_core_shader_uniforms;

typedef struct fractions_core_shader_identifer
{
	const char* source_code;
	unsigned int type;
} fractions_core_shader_identifier;

typedef unsigned int fractions_core_shader;
void delete_fractions_core_shader(fractions_core_shader);
F_NODISCARD fractions_core_shader create_fractions_core_shader(fractions_core_shader_identifer);

typedef struct fractions_core_shader_program_contents
{
	std::vector<fractions_core_shader_identifer> shaders;
} fractions_core_shader_program_contents;

typedef unsigned int fractions_core_shader_program;
F_NODISCARD fractions_core_shader_program
			create_fractions_core_shader_program();
void link_fractions_core_shader_fractions_core_shader_program(
	fractions_core_shader_program, fractions_core_shader
	);
void finalize_fractions_core_shader_program(fractions_core_shader_program);

// FRACTIONS CORE RENDERER OBJECT

typedef struct fractions_core_vertex_data
{
	float* data;
	int stride;
	int size;
	int vertex_data_points;
} fractions_core_vertex_data;

typedef bool fractions_core_geometry_mode;
#define FRACTIONS_CORE_STATIC_GEOMETRY true
#define FRACTIONS_CORE_DYNAMIC_GEMOETRY false

typedef struct fractions_core_texture
{
	
	unsigned int ID;
	unsigned int tex_type;
	unsigned int width, height;
	unsigned int bits_per_pixel;
	unsigned int channel; // e.g. RGBA -> 4

	std::vector<unsigned char> image;

} fractions_core_texture;

// TODO

void set_current_fractions_core_texture(fractions_core_texture*);
void supply_fractions_core_texture_img(std::vector<unsigned char>*);
void flush_current_fractions_core_texture(); // TODO : what does / should this do again?

typedef struct fractions_core_object_configuration
{
	fractions_core_vertex_data v_data;
	fractions_core_geometry_mode g_mode;

} fractions_core_object_configuration;

//
typedef struct fractions_core_object;
typedef void (*object_live_uniform)(fractions_core_object*);
//

typedef struct fractions_core_object
{
	fractions_core_object_configuration config;
	bool visible = true;
	fractions_core_shader_program shader_program;

	// internal

	unsigned int vao, vbo;

	fractions_core_shader_uniforms uniforms;

	fractions_core_texture texture;
	bool has_fractions_core_texture = false;

	// default value for error checking
	// will not execute if nullptr
	object_live_uniform on_draw_event = nullptr;

} fractions_core_object;

void create_fractions_core_object(fractions_core_object*);
void destroy_fractions_core_object(fractions_core_object*);
void append_fractions_core_object(fractions_core_object*);
void remove_fractions_core_object(fractions_core_object*);

// FRACTIONS CORE CONTEXT

typedef struct fractions_core_context
{
	// both window properties must be defined
	int window_width, window_height;
	const char* window_title;
	bool window_resizable;

	bool window_should_close;
	basic_action close_event;

	GLFWwindow* window = NULL;

	std::vector<std::pair<fractions_core_shader, fractions_core_shader_identifer>>
		fractions_core_temp_shaders;
	// TODO: this needs some rework...
	std::vector<fractions_core_object*> fractions_core_rendering_queue;

	// TODO: perhaps macro nullptr into something like FNULL
	basic_action loop_event = nullptr;

	bool loop_shall_stop = false;

} fractions_core_context;

void supply_fractions_core_context(fractions_core_context*);
void set_fractions_core_context();
void end_fractions_core_context();

void fractions_core_context_make_window();
void fractions_core_context_make_engine();
//void initialize_fractions_core_context_renderer();

void start_fractions_core_loop();
void stop_fractions_core_loop();

// The function to be added first will be run first.
// Functions are executed after rendering
void set_fractions_core_loop_events(basic_action);

void fractions_core_live_uniform_V4(fractions_core_object*, const char*, fractions_core_vec4f value);
void fractions_core_live_uniform_F(fractions_core_object*, const char*, float value);
void fractions_core_live_uniform_M(fractions_core_object*, const char*, fractions_core_matrix value);

#ifdef FRACTIONS_CORE_API_OPENGL_TEST_PROGRAM

// A simple test program to test OpenGL.
// This does not use any of the Fractions Core's functions

[[maybe_unused]] static void testProgram()
{
	glfwSetErrorCallback(glfw_onError);

	if (glfwInit() == GLFW_FALSE)
		__debugbreak();

	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	window = glfwCreateWindow(500, 500, "window", NULL, NULL);
	
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	unsigned int _err_ = glewInit();
	if (_err_ != GLEW_OK)
	{
		std::cout << glewGetErrorString(_err_) << std::endl;
	}

	std::stringstream vertex_source, fragment_source;

	std::string line;
	std::ifstream vertex("D:\\Fractions Project Again\\Fractions\\FractionsCore\\resources\\vertexbasic.shader");
	if (vertex.is_open())
		while (getline(vertex, line))
		{
			vertex_source << line << "\n";
		}
	else
		std::cout << "NOPE!" << std::endl;

	vertex.close();

	std::ifstream fragment("D:\\Fractions Project Again\\Fractions\\FractionsCore\\resources\\fragmentbasic.shader");
	if (fragment.is_open())
	{
		while (getline(fragment, line))
		{
			fragment_source << line << "\n";
		}
	}
	else
		std::cout << "NOPE!" << std::endl;

	fragment.close();

	std::string vertex_s = vertex_source.str();
	const char* v_source = vertex_s.c_str();

	glViewport(0, 0, 500, 500);

	unsigned int vs, fs, program;
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &v_source, NULL);
	glCompileShader(vs);

	std::string fragment_s = fragment_source.str();
	const char* f_source = fragment_s.c_str();

	GLCall(fs = glCreateShader(GL_FRAGMENT_SHADER));
	GLCall(glShaderSource(fs, 1, &f_source, NULL));
	GLCall(glCompileShader(fs));

	GLCall(program = glCreateProgram());
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	float triangle_2d[] =
	{
		0.0f, 0.0f,
		0.5f, 1.0f,
		1.0f, 0.0f
	};

	unsigned int vao;
	unsigned int vbo;

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_2d), &triangle_2d, GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, )

	GLCall(glUseProgram(program));

	// unbind
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glBindVertexArray(vao));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		GLCall(glBindVertexArray(0));

		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

#endif
*/

// new code

// A simple macro to keep all other headers from potentially redefining
// types etc.
#define FRACTIONS_CORE
#define GLEW_STATIC

#include <gl/glew.h>
#include <gl/wglew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "fstd.h"
#include "FractionsFiles.h"

#ifndef NO_FRACTIONS_CORE_ASSERT
#define ASSERT(X) if (!(X)) __debugbreak();
#else
#define ASSERT(X) ;
#endif

#ifndef NO_FRACTIONS_CORE_OPENGL_ERROR_CHECKING

// TODO: this is horibble, I need to make this better
inline void GLclearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall()
{
	while (GLenum error = glGetError())
		std::cout << "ERROR CODE: " << error << "\nLINE: " << __LINE__ << std::endl;
	return true;
}

// TODO: maybe improve this
#ifndef RELEASE
#define GLCall(X) GLclearErrors(); \
					X;\
					ASSERT(GLLogCall())
#else
#define GLCall(x) x;
#endif
#endif

namespace fractions_core {

	// uuid
	uuid generate_uuid();

	// context

	struct scene;
	struct shader;
	struct object;
	struct texture;

	typedef struct context
	{
		// window properties
		dimension window_dimension;
		const char* window_title;
		boolean window_resizable;

		// todo
		boolean fullscreen;
		
		bool window_should_close;

		GLFWwindow* api_window;

		// engine properties
		bool engine_active = false;
		bool engine_alive = false;

		// engine
		std::unordered_map<uuid, scene*> scenes;
		std::unordered_map<uuid, shader*> shaders;
		// is this really necessary?
		std::unordered_map<uuid, object*> objects;
		std::unordered_map<uuid, texture*> textures;

		// should this really be a vector?
		// let's keep it fool proof
		std::vector<function_pointer> on_draw_functions;

		function_pointer on_window_should_close = nullptr;

		// the scene that loads on startup
		uuid primary_scene;

		// the scene that is currently being displayed
		uuid current_scene;
	} fractions_core_context;

	void bind_on_window_should_close(function_pointer);

	// context affectING
	void supply_context(context*);
	void update_context();

	// context affectED
	void make_window();
	void make_engine();

	void shutdown();

	// (we like star trek)
	// loads the primary scene and starts the rendering loop
	void engage();

	// engine

	void bind_draw(function_pointer);

	typedef struct shader
	{
		uuid id;
		std::string vertex_source;
		std::string fragment_source;
		bool interpreted = false;

		boolean loaded = undef;
		bool has_api_object = false;

		uint64_t api_id;
	} shader;

	typedef struct texture
	{
		const char* tex;
		// R, G, B, A
		size_t stride;
		size_t length;
		uuid id;

		boolean loaded = undef;
		boolean has_api_object = undef;
	} texture;

	typedef struct object
	{
		uuid id;

		// x, y, z
		// location of the object in the local coordinate system
		float* location;

		std::vector<uuid> shaders;

		bool visible;
		bool acting = false;

		std::vector<function_pointer> on_draw;

		unsigned int api_id;

		// x, y, z
		float* verticies;
		// how many floats one vertex is
		unsigned vertex_size;
		// amount of VERTICIES e.g. one coordinate
		// to get the total size: vertex_size * vertex_count
		uint64_t vertex_count;

		boolean loaded = undef;
		boolean has_api_object = undef;

		bool static_draw = true;

		// api

		// GL -> Vertex Array
		unsigned int API_KEY0;
		// GL -> Buffer
		unsigned int API_KEY1;
		 
		// not yet implemented
		// TODO: implement normalization (or maybe not)
		bool expr_normalization = false;

	} object;

	void bind_ObjectDraw(object&, function_pointer);

	typedef struct scene
	{
		uuid id;

		bool visible = false;
		std::vector<uuid> objects;

		std::vector<function_pointer> on_draw;

		// scenes do not have a boolean loaded as they do not need one
		// they are simply an assortment of objects
		// the objects can be loaded
		// and if all the objects are loaded then the scene is effectively
		// loaded. But then the `boolean` `loaded` wouldn't make any
		// sense, as it is just the check of whether every objec is loaded.
		// Therefore, it's easier to simply call a function to check if it
		// is loaded, then have a variable that needs the call of a function.
		// (This system may get redesigned in the future however, because
		// I may have thought of a way to outsmart myself).
	} scene;

	void bind_SceneDraw(scene&, function_pointer);

	bool is_scene_loaded(uuid);

	void append_object(object&);
	void append_scene(scene&);
	void append_shader(shader&);
	void append_texture(texture&);

	// TODO : figure this one out
	void show_scene(uuid);
	void hide_scene(uuid);
	void show_object(uuid);
	void hide_object(uuid);

	// object, id
	void object_to_scene(uuid id, uuid s);

	// TODO: Maybe create two seperate functions so that the VAO may exist
	//		 without the coords in place so that shaders can already be
	//		 applied.
	void create_api_object(uuid);
	// will only work if the object already has an API object
	void create_api_shader(uuid shader, uuid object);
	void create_all_api_shader(uuid object);

	void test_api();
}