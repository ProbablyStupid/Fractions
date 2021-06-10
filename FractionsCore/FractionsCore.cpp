#include "FractionsCore.h"

static fractions_core_context* current_context, * given_context;

static void glfw_onError(int error, const char* description)
{
	std::cout << description << std::endl;
	MessageBox(NULL, (LPCWSTR)WCHAR(description), L"GLFW error", MB_OK);
}

/* primitive C style text file reading : THERE IS NO GUARANTEE THAT THIS WILL WORK */
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
		current_context->fractions_core_rendering_queue.erase(current_context->fractions_core_rendering_queue.begin() + id);
	else
		/* TODO:  report some sort of error */;
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
}

static void _rendering_loop()
{
	while (!current_context->window_should_close && !current_context->loop_shall_stop)
	{

		glfwPollEvents();

		if (glfwWindowShouldClose(current_context->window))
			current_context->close_event();

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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

			for (object_live_uniform i : current_context->fractions_core_object_live_uniforms)
				i(o);

			GLCall(glBindVertexArray(o->vao));
			glDrawArrays(GL_TRIANGLES, 0, 
				(o->config.v_data.size / o->config.v_data.vertex_data_points));
			GLCall(glBindVertexArray(0));
		}

		glfwSwapBuffers(current_context->window);
		
		for (basic_action i : current_context->fractions_core_loop_events)
			i();
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

void add_fractions_core_loop_events(basic_action action)
{

}