#include "FractionsCore.h"
/*
static fractions_core_context* current_context, * given_context;

static void glfw_onError(int error, const char* description)
{
	std::cout << description << std::endl;
	MessageBox(NULL, (LPCWSTR)WCHAR(description), L"GLFW error", MB_OK);
}

// primitive C style text file reading : THERE IS NO GUARANTEE THAT THIS WILL WORK
F_NODISCARD const char* fractions_core_get_file_text_f(const char* filepath)
{
	FILE* file;
	fopen_s(&file, filepath, "r");
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	const char* buffer = (char*)malloc(sizeof(char) * size);
	fscanf_s(file, "%s", buffer);
	fclose(file);
	return buffer;
}

// Fractions Core's native preferred method to read files
F_NODISCARD std::string fractions_core_get_file_text_s(const char* filepath)
{
	std::ifstream file(filepath);
	std::stringstream file_content;
	std::string line;
	if (file.is_open())
	{
		while (getline(file, line))
			file_content << line << "\n";
	}
	else
		__DEBUGBREAK();

	std::string final_file = file_content.str();
	return final_file;
}

void delete_fractions_core_shader(fractions_core_shader shader)
{
	GLCall(glDeleteShader(shader));
}

F_NODISCARD fractions_core_shader
	create_fractions_core_shader(fractions_core_shader_identifer identifier)
{
	fractions_core_shader shader = glCreateShader(identifier.type);

	GLCall(;);

	// maybe TOOD: IMPLEMENT A COUNT SYSTEM
	GLCall(glShaderSource(shader, 1, &identifier.source_code, NULL));
	GLCall(glCompileShader(shader));

	const char* shader_type_text;

	switch (identifier.type)
	{
	case FRACTIONS_CORE_VERTEX_SHADER: shader_type_text = "vertex"; break;
	case FRACTIONS_CORE_FRAGMENT_SHADER: shader_type_text = "fragment"; break;
	default: shader_type_text = "[ERROR NO SHADER]"; break;
	}
	std::cout << "compiled " << shader_type_text << std::endl;
	std::cout << "shader source code: \n" << identifier.source_code << std::endl;

	int success;
	char error_log[500];
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCall(glGetShaderInfoLog(shader, 500, NULL, error_log));
		std::cout << "error in " << shader_type_text << std::endl;
		std::cout << error_log << std::endl;
	}

	return shader;
}

F_NODISCARD fractions_core_shader_program
			create_fractions_core_shader_program()
{
	fractions_core_shader_program program = glCreateProgram();
	GLCall(;);
	return program;
}

void link_fractions_core_shader_fractions_core_shader_program(
	fractions_core_shader_program program,
	fractions_core_shader shader
)
{
	GLCall(glAttachShader(program, shader));
}

void finalize_fractions_core_shader_program(fractions_core_shader_program program)
{
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
}

void create_fractions_core_object(fractions_core_object* object)
{
	GLCall(glGenVertexArrays(1, &object->vao));
	GLCall(glBindVertexArray(object->vao));

	unsigned int usage;
	if (object->config.g_mode)
		usage = GL_STATIC_DRAW;
	else
		usage = GL_DYNAMIC_DRAW;

	GLCall(glGenBuffers(1, &object->vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, object->vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, object->config.v_data.size, object->config.v_data.data,
		usage));

	// TOOD: first argument -> check that it's working
	GLCall(glVertexAttribPointer(0, object->config.v_data.vertex_data_points, GL_FLOAT,
		false, object->config.v_data.stride, (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

// TOOD: confirm that this is working
void destroy_fractions_core_object(fractions_core_object* object)
{
	GLCall(glDeleteVertexArrays(1, &object->vao));
	GLCall(glDeleteBuffers(GL_VERTEX_ARRAY, &object->vbo));
}

void append_fractions_core_object(fractions_core_object* object)
{
	current_context->fractions_core_rendering_queue.push_back(object);
}

// This is inefficient, but I don't see a way around this as other ways may have an affect of IDs
void remove_fractions_core_object(fractions_core_object* object)
{
	unsigned int id, counter = 0;
	bool found = false;
	for (fractions_core_object* i : current_context->fractions_core_rendering_queue)
	{
		if (i == object)
		{
			id = counter;
			found = true;
			break;
		}
		counter++;
	}
	if (found)
		current_context->fractions_core_rendering_queue
		.erase(current_context->fractions_core_rendering_queue.begin() + id);
	else
		// TODO:  report some sort of error
		;
}

void supply_fractions_core_context(fractions_core_context* context)
{
	given_context = context;
}

void set_fractions_core_context()
{
	current_context = given_context;
}

void end_fractions_core_context()
{
	current_context = NULL;
}

void fractions_core_context_make_window()
{
	glfwSetErrorCallback(glfw_onError);
	if (!glfwInit())
		__DEBUGBREAK();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// user specified
	glfwWindowHint(GLFW_RESIZABLE, current_context->window_resizable);

	current_context->window = glfwCreateWindow(current_context->window_width,
		current_context->window_height, current_context->window_title, NULL, NULL);
}

void fractions_core_context_make_engine()
{
	if (current_context->window == NULL)
		__DEBUGBREAK();
	glfwMakeContextCurrent(current_context->window);

	glewExperimental = true;
	unsigned int error = glewInit();
	if (error != GLEW_NO_ERROR)
	{
		std::cout << glewGetErrorString(error) << std::endl;
		__DEBUGBREAK();
	}

	glEnable(GL_DEPTH_TEST);
}

static void _rendering_loop()
{
	while (!current_context->window_should_close && !current_context->loop_shall_stop)
	{
		glfwPollEvents();

		if (glfwWindowShouldClose(current_context->window))
			current_context->close_event();

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (fractions_core_object* o : current_context->fractions_core_rendering_queue)
		{
			GLCall(glUseProgram(o->shader_program));

			if (o->uniforms.F_uniforms)
			{
				int location;
				for (int i = 0; i < o->uniforms.uniforms_F.size; i++)
				{
					location = glGetUniformLocation(o->shader_program,
						o->uniforms.uniforms_F.data[i].uniform_name);
					GLCall(glUniform1f(location, o->uniforms.uniforms_F.data[i].value));
				}
			}
			if (o->uniforms.I_uniforms)
			{
				int location;
				for (int i = 0; i < o->uniforms.uniforms_I.size; i++)
				{
					location = glGetUniformLocation(o->shader_program,
						o->uniforms.uniforms_F.data[i].uniform_name);
					GLCall(glUniform1i(location, o->uniforms.uniforms_I.data[i].VALUE));
				}
			}
			if (o->uniforms.UI_uniforms)
			{
				int location;
				for (int i = 0; i < o->uniforms.uniforms_UI.size; i++)
				{
					location = glGetUniformLocation(o->shader_program,
						o->uniforms.uniforms_F.data[i].uniform_name);
					GLCall(glUniform1ui(location, o->uniforms.uniforms_UI.data[i].VALUE));
				}
			}
			if (o->uniforms.M_uniforms)
			{
				int location;
				for (int i = 0; i < o->uniforms.uniforms_M.size; i++)
				{
					location = glGetUniformLocation(o->shader_program,
						o->uniforms.uniforms_F.data[i].uniform_name);
					GLCall(glUniformMatrix4fv(location, 1, GL_FALSE,
						glm::value_ptr(o->uniforms.uniforms_M.data[i].matrix)));
				}
			}
			if (o->uniforms.V4_uniforms)
			{
				int location;
				for (int i = 0; i < o->uniforms.uniforms_V4.size; i++)
				{
					location = glGetUniformLocation(o->shader_program,
						o->uniforms.uniforms_V4.data[i].uniform_name);
					GLCall(glUniform4f(location,
						o->uniforms.uniforms_V4.data[i].value.one,
						o->uniforms.uniforms_V4.data[i].value.two,
						o->uniforms.uniforms_V4.data[i].value.three,
						o->uniforms.uniforms_V4.data[i].value.four));
				}
			}

			GLCall(glBindVertexArray(o->vao));
			glDrawArrays(GL_TRIANGLES, 0,
				(o->config.v_data.size / o->config.v_data.vertex_data_points));
			GLCall(glBindVertexArray(0));

			if (o->on_draw_event != nullptr)
				o->on_draw_event(o);
		}

		glfwSwapBuffers(current_context->window);

		if (current_context->loop_event != nullptr)
		current_context->loop_event();
	}
}

void start_fractions_core_loop()
{
	std::cout << "starting core loop!" << std::endl;
	_rendering_loop();
	std::cout << "core loop ended!" << std::endl;
}

void stop_fractions_core_loop()
{
	std::cout << "stopping core loop..." << std::endl;
	current_context->loop_shall_stop = true;
}

void set_fractions_core_loop_events(basic_action action)
{
	current_context->loop_event = action;
}

void fractions_core_live_uniform_V4(fractions_core_object* obj, const char* name,
	fractions_core_vec4f value)
{
	int location = glGetUniformLocation(obj->shader_program, name);
	glUniform4f(location, value.one, value.two, value.three, value.four);
}

void fractions_core_live_uniform_F(fractions_core_object* obj, const char* name, float value)
{
	int location = glGetUniformLocation(obj->shader_program, name);
	glUniform1f(location, value);
}

void fractions_core_live_uniform_M(fractions_core_object* obj, const char* name,
	fractions_core_matrix value)
{
	int location = glGetUniformLocation(obj->shader_program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
*/

namespace fractions_core
{
	// if any object has the uuid 0 it is a faulty object and can be disregarded
	// the algorithm first increments the uuid, then returns it
	uuid current_uuid = 0;

	uuid generate_uuid()
	{
		current_uuid++;
		return current_uuid;
	}

	static context* current_context, * supplied_context;

#define con current_context

#define object(x) con->objects.at(x)
#define scene(x) con->scenes[x]
#define shader(x) con->shaders.at(x)
#define texture(x) con->textures.at(x)

	void create_api_object(uuid o)
	{
		unsigned int vao = 0;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		unsigned int vbo = 0;
		GLCall(glGenBuffers(1, &vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, (object(o)->vertex_count * object(o)->vertex_size) * sizeof(float),
			object(o)->verticies, 
		//	object(o)->static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW)
			GL_STATIC_DRAW
		));

		// TODO: standardize this in some way
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void*)0);
		glEnableVertexAttribArray(1));

		object(o)->api_id = vao;

		GLCall(glBindVertexArray(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		object(o)->has_api_object = True;
	}

	// Also binds the shader to the object
	void create_api_shader(uuid s, 
		// TODO: This name needs to be fixed
		uuid object)
	{
#define _shader current_context->shaders.at(s)

		GLCall(glBindVertexArray(object(object)->api_id));

		const char* vsource = _shader->vertex_source.c_str();
		debug(std::cout << vsource << std::endl);
		int vlength = static_cast<int>(_shader->vertex_source.length());

		// vertex shader
		GLCall(auto vertex_shader = glCreateShader(GL_VERTEX_SHADER));

		GLCall(glShaderSource(vertex_shader, 1, &vsource, &vlength));
		GLCall(glCompileShader(vertex_shader));

		// TODO: add support for more than vertex and fragment shader

		// fragment shader

		const char* fsource = _shader->fragment_source.c_str();
		debug(std::cout << fsource << std::endl;)
		int flength = static_cast<int>(_shader->fragment_source.length());

		GLCall(auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));

		GLCall(glShaderSource(fragment_shader, 1, &fsource, &flength));
		GLCall(glCompileShader(fragment_shader));


		// Shader program

		GLCall(_shader->api_id = glCreateProgram());

		GLCall(glAttachShader(_shader->api_id, vertex_shader));
		GLCall(glAttachShader(_shader->api_id, fragment_shader));

		GLCall(glLinkProgram(_shader->api_id));
		GLCall(glValidateProgram(_shader->api_id));

		GLCall(glDeleteShader(vertex_shader));
		GLCall(glDeleteShader(fragment_shader));

		GLCall(glUseProgram(_shader->api_id));

		GLCall(glBindVertexArray(0));
#undef _shader
	}

	void create_all_api_shader(uuid o)
	{
		for (uuid i : object(o)->shaders)
		{
			if (shader(i)->has_api_object == false)
				create_api_shader(i, o);
		}
	}

	bool is_scene_loaded(uuid s)
	{
		for (uuid i : current_context->scenes.at(s)->objects)
			if (object(i)->loaded == False)
				return false;
		return true;
	}

	void supply_context(context* c)
	{
		supplied_context = c;
	}

	void update_context()
	{
		current_context = new context;
		current_context = supplied_context;
	}

	void internal_glfw_error_callback(int x, const char* y)
	{
		std::cout << y << std::endl;
	}

	void internal_glfw_window_close_callback(GLFWwindow* window)
	{
		std::cout << "window close requested by \t\t[[ GLFW ]]" << std::endl;
		if (con->on_window_should_close != nullptr)
			con->on_window_should_close();
	}

	void make_window()
	{
		if (!glfwInit())
			throw std::runtime_error("UNABLE TO INITIALIZE GLFW");
		glfwSetErrorCallback(internal_glfw_error_callback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		
		// resizable
		if (con->window_resizable != boolean::Undefined)
			glfwWindowHint(GLFW_RESIZABLE, (bool)con->window_resizable);

		// creating the window
		auto [width, height] = con->window_dimension;
		GLFWwindow* window =
			glfwCreateWindow(width, height,
				con->window_title, NULL, NULL);
		con->api_window = window;

		glfwSetWindowCloseCallback(con->api_window, internal_glfw_window_close_callback);
	}

	void make_engine()
	{
		glfwMakeContextCurrent(con->api_window);
		glewExperimental = true;
		unsigned error = glewInit();
		if (error != GLEW_OK)
		{
			std::cerr << "UNABLE TO INITIALIZE GLEW: " << glewGetErrorString(error) << std::endl;
			throw std::runtime_error("UNABLE TO INITIALIZE GLEW");
		}
		con->engine_alive = true;

		auto [width, height] = con->window_dimension;
		glViewport(0, 0, width, height);
	}

	void shutdown()
	{
		con->engine_alive = false;
		con->engine_active = false;
		glfwDestroyWindow(con->api_window);
		glfwTerminate();
	}

	void engine_update();

	void engage()
	{
		con->current_scene = con->primary_scene;
		if (!is_scene_loaded(con->current_scene))
			throw std::runtime_error("INVALID CURRENT SCENE");
		show_scene(con->primary_scene);

		while (con->engine_alive)
		{
			engine_update();
		}
	}

	//

	void bind_on_window_should_close(function_pointer p)
	{
		con->on_window_should_close = p;
	}

	void bind_draw(function_pointer p)
	{
		con->on_draw_functions.push_back(p);
	}

	void bind_ObjectDraw(object& o, function_pointer p)
	{
		o.on_draw.push_back(p);
	}

	void bind_SceneDraw(scene& s, function_pointer p)
	{
		s.on_draw.push_back(p);
	}

	void append_object(object& o)
	{
		o.id = generate_uuid();
		con->objects[o.id] = &o;
		if (o.loaded != false)
			create_api_object(o.id);
		for (uuid i : o.shaders)
			if (shader(i)->loaded != false)
				create_api_shader(i, o.id);
	}

	void append_scene(scene& s)
	{
		s.id = generate_uuid();
		con->scenes[1] = &s;
	}

	void append_shader(shader& s)
	{
		s.id = generate_uuid();
		con->shaders[s.id] = &s;
	}

	void append_texture(texture& t)
	{
		t.id = generate_uuid();
		con->textures[t.id] = &t;
	}

	void object_to_scene(uuid id, uuid s)
	{
		scene(s)->objects.push_back(id);
	}

	void draw_object(uuid o)
	{
		for (function_pointer i : object(o)->on_draw)
			i();

		GLCall(glBindVertexArray(object(o)->api_id));
		glDrawArrays(GL_TRIANGLES, 0, object(o)->vertex_count);
		GLCall(glBindVertexArray(0));
	}

	void show_scene(uuid s)
	{
		// TODO: perhaps make this a little smarter
		scene(con->current_scene)->visible = false;
		scene(s)->visible = true;
		con->current_scene = s;
	}

	void update_object(uuid i)
	{
		// perhaps have update functions?
		// or physics?
	}

	void engine_update()
	{
		glfwPollEvents();


		glClear(GL_COLOR_BUFFER_BIT);

		for (uuid i : scene(con->current_scene)->objects)
		{
			if (object(i)->visible)
				draw_object(i);
			if (object(i)->acting)
				update_object(i);
		}
		
		glfwSwapBuffers(con->api_window);
	}

	void test_api()
	{
		glfwInit();

		glfwSetErrorCallback(internal_glfw_error_callback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

		GLFWwindow* window = glfwCreateWindow(200, 200, "TEST WINDOW", NULL, NULL);

		glfwMakeContextCurrent(window);

		glewExperimental = true;
		auto glew = glewInit();
		if (glew != GLEW_OK)
			std::cout << glewGetErrorString(glew) << std::endl;

		glViewport(0, 0, 200, 200);

		const float verticies[] =
		{
			0.0f, 0.0f, 1.0f,
			0.5f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
		};

		unsigned int vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), &verticies, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(vao);

		auto vertex = glCreateShader(GL_VERTEX_SHADER);
		auto vfile = in_file("vertex.txt");
		std::string vstring = *vfile.get_contents();
		auto vsource = vstring.c_str();
		std::cout << vsource << std::endl;
		const GLint vlength = (const GLint)vstring.length();
		
		glShaderSource(vertex, 1, &vsource, &vlength);
		glCompileShader(vertex);


		auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
		auto ffile = in_file("fragment.txt");
		std::string fstring = *ffile.get_contents();
		auto fsource = fstring.c_str();
		std::cout << fsource << std::endl;
		const GLint flength = fstring.length();

		glShaderSource(fragment, 1, &fsource, &flength);
		glCompileShader(fragment);

		auto program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		glUseProgram(program);

		glBindVertexArray(0);

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			
			glBindVertexArray(vao);

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}