/*
// Old deprecated code
#include <FractionsCore.h>
#include <FractionsLog.h>
#include <../Fractions API/Frac.h>

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
*/

#include <FractionsCore.h>
#include <FractionsFiles.h>
#include <fstd.h>

int main()
{

#ifndef NO_MAIN
	log("log!");
	warn("warn!");
	err("error!");
	fatal("fatal!");
	print("print!");

	// bool check
	boolean yes = True;
	if (Bool(yes))
		std::cout << "hello world" << std::endl;

	// context
	fractions_core::context context;
	context.window_resizable = False;
	// TODO: make this better
	context.window_dimension = std::make_pair(200, 200);
	context.window_title = "YES";

	fractions_core::supply_context(&context);
	fractions_core::update_context();

	// setup
	fractions_core::make_window();
	fractions_core::make_engine();

	// scene
	fractions_core::scene my_scene;
	my_scene.visible = true;
	fractions_core::append_scene(my_scene);

	// object
	fractions_core::object obj;

	constexpr float data[] =
	{
		0.0f, 0.0f, 1.0f,
		0.5f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f
	};

	obj.verticies = (float*) & data;
	obj.vertex_count = 3;
	obj.vertex_size = 3;
	obj.static_draw = true;
	obj.loaded = True;

	fractions_core::append_object(obj);

	// shaders

	// TODO: make this work with universal directories
	in_file vertex_file("vertex.txt");
	std::string vertex_source = *vertex_file.get_contents();
	vertex_file.flush();

	in_file fragment_file("fragment.txt");
	std::string fragment_source = *fragment_file.get_contents();
	fragment_file.flush();

	fractions_core::shader myShader;
	myShader.vertex_source = vertex_source;
	myShader.fragment_source = fragment_source;
	myShader.loaded = True;
	fractions_core::append_shader(myShader);
	fractions_core::create_api_shader(myShader.id, obj.id);

	//my_scene.objects.push_back(obj.id);
	fractions_core::object_to_scene(obj.id, my_scene.id);
	context.primary_scene = my_scene.id;


	// engine startup
	fractions_core::engage();

	fractions_core::shutdown();

#else

	// alternatively, to test everything is working properly
	fractions_core::test_api();

#endif

	std::cout << "end!" << std::endl;

	return EXIT_SUCCESS;
}