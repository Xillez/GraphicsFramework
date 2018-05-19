#include "global_function.hpp"
#include "../header/globalVar.hpp"
#include "../environment/Camera.hpp"	
#include "../game/Glider.hpp"
#include "../game/Map.hpp"

#include <unordered_map>
#include <iostream>
#include <stdio.h>

extern GLFWwindow* window;
extern environment::Camera* camera;
extern game::Glider* glider;
extern game::Map* map;
bool middleMousePressed = false;

std::unordered_map<std::string, std::vector<std::string>> moves;
glm::vec2 prevMousePos(0.0f, 0.0f);

void helpers::setup_EventHandling()
{
	glfwSetCursorPosCallback(window, helpers::OnMouseMove);
	glfwSetMouseButtonCallback(window, helpers::OnMouseClick);
	glfwSetKeyCallback(window, helpers::OnKeyPress);
}

void helpers::OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
	// Calculate 2d difference in 2d (window) mouse position
	// and update last pos to be current
	glm::vec2 deltaPos(xpos - prevMousePos.x, ypos - prevMousePos.y);
	prevMousePos = {xpos,ypos};

	if (!middleMousePressed)
		return;
	
	// Rotate camera around both rotational axes
	camera->rotateBy(-deltaPos.x / 200.0f, (deltaPos.y * -1) / 200.f);
}

void helpers::OnMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec3 pointerPos = convertMousePosToWorld(xpos, ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
	{
		middleMousePressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
	{
		middleMousePressed = false;
	}
}

glm::vec3 helpers::convertMousePosToWorld(double xpos, double ypos)
{
	// Get window size.
	glm::vec2 wSize = environment::Camera::windowSize();
    GLfloat viewportY, z;

	// Flip y axis to see where we are in viewport's y.
    viewportY = wSize.y - ypos;

	// Get the z-axis value that generated this pixel.
    glReadPixels(xpos, viewportY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	// Assemble were we were inside viewport with z depth.
    glm::vec3 mousePosInViewport = glm::vec3(xpos, viewportY, z);

	// Get the view and projection matrix form camera.
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getPerspectiveMatrix();

	// Unproject the view and projection, based on the viewport and get the position within the world.
	return glm::unProject(mousePosInViewport, viewMatrix, projectionMatrix,
		glm::vec4(0.0f, 0.0f, wSize.x, wSize.y));
}

void helpers::OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// W Key
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	glider->rotateBy(glm::vec3(0.0f, 0.0f, 1.0f));
    	//camera->translateBy(camera->getDir());

    }
	// S Key
	else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	glider->rotateBy(glm::vec3(0.0f, 0.0f, -1.0f));    	
    	//camera->translateBy(-camera->getDir());
   
    }
	// A Key
	else if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	glider->rotateBy(glm::vec3(0.0f, 1.0f, 0.0f));
    	//camera->translateBy(glm::cross(camera->getUp(), camera->getDir()));
   
    }
	// D Key
	else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	glider->rotateBy(glm::vec3(0.0f, -1.0f, 0.0f));
    	//camera->translateBy(glm::cross(camera->getDir(), camera->getUp()));
    }
	// Q Key
	else if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	glider->rotateBy(glm::vec3(1.0f, 0.0f, 0.0f));
    	//camera->translateBy(glm::cross(camera->getUp(), camera->getDir()));
   
    }
	// E Key
	else if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	glider->rotateBy(glm::vec3(-1.0f, 0.0f, 0.0f));
    	//camera->translateBy(glm::cross(camera->getDir(), camera->getUp()));
    }
	// Space Key
	else if (key == GLFW_KEY_SPACE && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::vec3(0.0f, 1.0f, 0.0f));
    }
	// Left Shift Key
	else if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::vec3(0.0f, -1.0f, 0.0f));
    }
	// I Key
	else if (key == GLFW_KEY_I && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.0f, 0.1f);
    	camera->translateBy(camera->getDir());

    }
	// K Key
	else if (key == GLFW_KEY_K && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.0f, -0.1f);
    	camera->translateBy(-camera->getDir());
   
    }
	// J Key
	else if (key == GLFW_KEY_J && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(-0.1f, 0.0f);
    	camera->translateBy(glm::cross(camera->getUp(), camera->getDir()));
   
    }
	// L Key
	else if (key == GLFW_KEY_L && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::cross(camera->getDir(), camera->getUp()));
    }
	// Y Key
	else if ((key == GLFW_KEY_Y || key == GLFW_KEY_SPACE) && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::vec3(0.0f, 1.0f, 0.0f));
    }
	// H Key
	else if ((key == GLFW_KEY_H || key == GLFW_KEY_LEFT_SHIFT) && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::vec3(0.0f, -1.0f, 0.0f));
    }
	// Comma Key
	else if ((key == GLFW_KEY_COMMA) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		glider->decSpeed();
	}
	// Period Key
	else if ((key == GLFW_KEY_PERIOD) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		glider->incSpeed();
	}
	// F Key
	else if ((key == GLFW_KEY_F) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		glider->genNewPos();
	}
	// R Key
	else if ((key == GLFW_KEY_R) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		glider->resetPos();
	}
	// Minus Key
	else if ((key == GLFW_KEY_SLASH || key == GLFW_KEY_MINUS) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->toggleLockToGlider(glm::vec3(20.0f, 7.5f, 0.0f));
	}
	// O Key
	else if ((key == GLFW_KEY_O) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		map->toggleSmoothBorder();
	}
	// N Key
	else if ((key == GLFW_KEY_N) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->zoom(true);
	}
	// M Key
	else if ((key == GLFW_KEY_M) && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->zoom(false);		
	}
	// 5 Key
	else if ((key == GLFW_KEY_5) && action == GLFW_PRESS) {
		map->togglePauseSeason();	
	}
	// 1 Key
	else if ((key == GLFW_KEY_1) && action == GLFW_PRESS) {
		if (!map->getSeasonPauseState())
			map->togglePauseSeason();
		
		map->selectSeason(0.00f);
	}
	// 2 Key
	else if ((key == GLFW_KEY_2) && action == GLFW_PRESS) {
		if (!map->getSeasonPauseState())
			map->togglePauseSeason();
		
		map->selectSeason(0.25f);	
	}
	// 3 Key
	else if ((key == GLFW_KEY_3) && action == GLFW_PRESS) {
		if (!map->getSeasonPauseState())
			map->togglePauseSeason();
		
		map->selectSeason(0.50f);	
	}
	// 4 Key
	else if ((key == GLFW_KEY_4) && action == GLFW_PRESS) {
		if (!map->getSeasonPauseState())
			map->togglePauseSeason();
		
		map->selectSeason(0.75f);	
	}
}