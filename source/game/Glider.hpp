#pragma once

#include "../modeler/Shader.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/struct.hpp"

#include <SOIL/SOIL.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include <vector>

/**
 * @brief Container for content specific to chess game.
 */
namespace game
{
	/**
	 * @brief General Glider with components.
	 */
	class Glider
	{
	public:
		
		/**
		 * @brief Board constructor.
		 */
		Glider(std::string const &modelPath);

		/**
		 * @brief 
		 */
		~Glider();

		/**
		 * @brief 
		 * 
		 * @param component - component added to current obect.
		 */
		//auto registerComponent(components::IComponent* component) -> bool;

		/**
		 * @brief updates state for next frame.
		 * 
		 * @param dt - Deltatime since last frame.
		 */
		auto update(float dt) -> void;

		/**
		 * @brief Draw the board and every piece found.
		 */

		auto draw(float dt) -> void;

	
		/**
		 * @brief Uses bezeir curve to interpolate between three control points. 
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is middle of point a and b.
		 * @param c - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 3 points.
		 */
		//auto jumpCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, float dt) -> glm::vec3;
			
		/**
		 * @brief Uses LERP to interpolate between two control points.
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 2 points.
		 */
		//auto lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3;

		auto rotateBy(glm::vec3 angle) -> void;
	
		auto translateBy(glm::vec3 translate) -> void;
	
		auto setPos(glm::vec3 newPos) -> void;

		auto setDir(glm::vec3 target) -> void;

		auto incSpeed() -> void;
		
		auto decSpeed() -> void;

		auto genNewPos() -> void;

		auto resetPos() -> void;

		auto getPos() -> glm::vec3;
		
		auto getRotQuat() -> glm::quat;

		auto getSpeed() -> float;

	private:
		modeler::Model* model = nullptr;
	
		glm::vec3 startPos;
		glm::vec3 position;								//!< Origin of board.
		glm::vec3 direction;
		glm::vec3 up;
		glm::vec3 angle;
		float speed;

		glm::quat rotQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}