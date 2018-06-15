#pragma once

#include "../modeler/Shader.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/struct.hpp"
#include "../components/IComponent.hpp"

#include <SOIL/SOIL.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

/**
 * @brief Container for content specific to game.
 */
namespace game
{
	/**
	 * @brief General Entity with components.
	 */
	class Entity
	{
	public:
		
		/**
		 * @brief Entity constructor.
		 */
		Entity();

		/**
		 * @brief Entity deconstructor.
		 */
		~Entity();

		/**
		 * @brief A function for registering components.
		 * 
		 * @param component - component added to current object.
		 */
		auto registerComponent(components::IComponent* component) -> bool;

		/**
		 * @brief updates state for next frame.
		 * 
		 * @param dt - Deltatime since last frame.
		 */
		auto update(float dt) -> void;

		/**
		 * @brief Draw the entity and possible subcomponents.
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

		auto setPos(glm::vec3 newPos) -> void;
				
	private:

		std::vector<unsigned int> componentList;
	
		// TODO: Move velocity (split to direction(unit vector)) and speed(int)), acceleration and tourque to the physics engine.
		glm::vec3 position;								//!< Posistion of entity.
		glm::vec3 velocity;								//!< Velocity of entity.
		glm::vec3 acceleration;							//!< Acceleration of entity.
		//glm::vec3 torque;								//!< Torque of entity.

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
		modeler::Mesh* model = nullptr;

		
	};
}