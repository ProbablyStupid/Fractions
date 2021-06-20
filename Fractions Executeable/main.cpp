#include <FractionsCore.h>
#include <FractionsLog.h>

void on_close()
{
	std::cout << "window should close" << std::endl;
	glfwTerminate();
	exit(0);
}

fractions_core_object obj;

fractions_core_matrix projection(1.0);

void on_loop(fractions_core_object* i)
{
	fractions_core_live_uniform_F(i, "red", 1.0f);

	fractions_core_matrix view(1.0);
	fractions_core_matrix model(1.0);

	model = glm::rotate(model, 10.0f, glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	fractions_core_live_uniform_M(i, "projection", projection);
	fractions_core_live_uniform_M(i, "view", view);
	fractions_core_live_uniform_M(i, "model", model);
}

int main()
{

	fractions_core_context* context = new fractions_core_context;
	context->window_width = 500;
	context->window_height = 500;
	context->window_title = "hello, test!";
	context->close_event = on_close;
	context->window_should_close = false;
	supply_fractions_core_context(context);
	set_fractions_core_context();
	fractions_core_context_make_window();
	fractions_core_context_make_engine();

	projection = glm::perspective(90.0f,
		(float)context->window_width / (float)context->window_height,
		0.1f, 1000.0f);

	fractions_core_shader_identifer shader_i;
	std::string source_code = fractions_core_get_file_text_s(
		"FractionsCore\\resources\\vertexbasic.shader"
	);
	
	shader_i.source_code = source_code.c_str();
	shader_i.type = FRACTIONS_CORE_VERTEX_SHADER;

	fractions_core_shader vertex_shader = create_fractions_core_shader(shader_i);

	fractions_core_shader_identifer shader_ii;
	std::string source_code_i = fractions_core_get_file_text_s(
		"FractionsCore\\resources\\fragmentbasic.shader"
	);
	
	shader_ii.source_code = source_code_i.c_str();
	shader_ii.type = FRACTIONS_CORE_FRAGMENT_SHADER;

	fractions_core_shader fragment_shader = create_fractions_core_shader(shader_ii);

	fractions_core_shader_program shader
		= create_fractions_core_shader_program();
	
	link_fractions_core_shader_fractions_core_shader_program(shader, vertex_shader);
	link_fractions_core_shader_fractions_core_shader_program(shader, fragment_shader);

	finalize_fractions_core_shader_program(shader);
	
	delete_fractions_core_shader(vertex_shader);
	delete_fractions_core_shader(fragment_shader);

	fractions_core_object_configuration config;
	config.g_mode = FRACTIONS_CORE_STATIC_GEOMETRY;
	float data[] =
	{
		0.0f, 0.0f,
		0.5f, 1.0f,
		1.0f, 0.0f
	};
	config.v_data.data = data;
	config.v_data.vertex_data_points = 2;
	config.v_data.size = sizeof(data);
	config.v_data.stride = 0;

	obj.config = config;
	obj.visible = true;
	obj.shader_program = shader;
	obj.on_draw_event = on_loop;

	create_fractions_core_object(&obj);
	append_fractions_core_object(&obj);

	start_fractions_core_loop();
}