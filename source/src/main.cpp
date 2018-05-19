#include "../helpers/glfw_setup.hpp"
#include "../helpers/global_function.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/MapComponent.hpp"
#include "../game/Object.hpp"
#include "../game/Map.hpp"
#include "../game/Glider.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

environment::Camera* camera;
environment::LightSource* lightSource;
GLFWwindow* window;
game::Map* map;
game::Glider* glider;
modeler::ShaderManager* shaderManager;

int main(int argc, char const *argv[])
{	
	// Create camera
	printf("%s Setting up camera\n",TAG_INFO.c_str());
	//camera = new environment::Camera(glm::vec3(0, 50, 25), glm::vec3(2, -1, 2), glm::vec3(0, 1, 0));
	camera = new environment::Camera(glm::vec3(250, 200, -150), glm::vec3(0, -0.25f, 1), glm::vec3(0, 1, 0), 60.0f);

	// Setting up light
	printf("%s Setting up LightSource\n",TAG_INFO.c_str());
	lightSource = new environment::LightSource(glm::vec3(250.0f, 40.0f, 500.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 32.0f);

	// Create common interface for shaders
	printf("%s Creating shadermanager\n", TAG_INFO.c_str());
	shaderManager = new modeler::ShaderManager();

	// OpenGL setup
	printf("%s Creating window\n", TAG_INFO.c_str());
	window = helpers::glfw_setup();

	// Setup ImGui
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(window, true);

    // Setup ImGui style
    ImGui::StyleColorsDark();
	
	// Make map
	printf("%s Creating board\n", TAG_INFO.c_str());
	map = new game::Map(glm::vec3(-250.0f, 0.0f, 500.0f));
	map->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	map->buildTerrain("../asset/heightmap/height100.png", glm::vec3(10.0f, 1.0f, 20.0f));

	glider = new game::Glider("../asset/models/glider.obj");

	// setup event handler
	printf("%s Setting up event handler\n", TAG_INFO.c_str());
	helpers::setup_EventHandling();

	// Setting up time info for calculating deltatime (dt)
	float currentTime = 0.0f, lastTime = 0.0f, dt = 0.0f, seasonDT = 0.0f, dayTime = 0.0f, dayDT = 0.0f;
	lastTime = glfwGetTime();
	
	// Run until close event is given to the window
	printf("%s Starting gameloop\n", TAG_INFO.c_str());
		
	while(!glfwWindowShouldClose(window))
	{
		// Clearing screen for next draw
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculating delta time
		currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;

		dayDT = dt / 10;		// A day takes 10 seconds
		dayTime += dayDT;

		if (dayTime > 1.0f)
			dayTime = 0.0f;
		
		// Updating all game obects
		map->update(dt);
		glider->update(dt);
		camera->update();
		lightSource->update(dayTime);
		//camera->setPos(lightSource->getPosition());

		// Drawing game objects
		map->draw(dt);
		glider->draw(dt);

		// Start a new ImGui UI Frame
		ImGui_ImplGlfwGL3_NewFrame();

		// Assign text fields
		ImGui::Text("Glider speed: %f", glider->getSpeed());
		ImGui::Text("Season: %s", map->getCurrSeasonName().c_str());
		ImGui::Text("Month: %s", map->getCurrMonthName().c_str());
		ImGui::Text("Month: %d:00", (int) (dayTime * 24));

		// Draw the frame
		ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);    // SWAP BUFFERS
        glfwPollEvents();           // LISTEN FOR WINDOW EVENTS
	}

	printf("%s Closing application\n", TAG_INFO.c_str());
	glfwDestroyWindow(window);

	return 0;
}