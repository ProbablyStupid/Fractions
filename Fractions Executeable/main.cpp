#include <FractionsCore.h>
#include <FractionsLog.h>

void on_close()
{
	std::cout << "window should close" << std::endl;
	glfwTerminate();
	exit(0);
}

void on_loop()
{
	fout << "YES";
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

	add_fractions_core_loop_events(on_loop);

	fractions_core_shader_identifer shader_i;
	std::string source_code = fractions_core_get_file_text_s(
		"D:\\Fractions Project Again\\Fractions\\FractionsCore\\resources\\vertexbasic.shader"
	);
	shader_i.source_code = source_code.c_str();
	shader_i.type = FRACTIONS_CORE_VERTEX_SHADER;

	fractions_core_shader vertex_shader = create_fractions_core_shader(shader_i);

	fractions_core_shader_identifer shader_ii;
	std::string source_code_i = fractions_core_get_file_text_s(
		"D:\\Fractions Project Again\\Fractions\\FractionsCore\\resources\\fragmentbasic.shader"
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

	fractions_core_shader_uniforms u;
	u.F_uniforms = true;

	fractions_core_shader_uniform_F red_color_uniform;
	red_color_uniform.uniform_name = "red";
	red_color_uniform.value = 1.0f;

	u.uniforms_F.size = 1;
	u.uniforms_F.data = &red_color_uniform;

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

	fractions_core_object obj;
	obj.config = config;
	obj.visible = true;
	obj.shader_program = shader;
	obj.uniforms = u;
	create_fractions_core_object(&obj);
	append_fractions_core_object(&obj);

	start_fractions_core_loop();
}