#pragma once

#include "../modeler/Shader.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/struct.hpp"

#include <SOIL/SOIL.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

// Boilder plate code needed to avoid circular inclusion with IComponent
namespace components
{
	class IComponent;
}

/**
 * @brief Container for content specific to chess game.
 */
namespace game
{
	/**
	 * @brief General Map with components.
	 */
	class Map
	{
	public:
		
		/**
		 * @brief Board constructor.
		 */
		Map(glm::vec3 positio);

		/**
		 * @brief 
		 */
		~Map();

		/**
		 * @brief 
		 * 
		 * @param component - component added to current obect.
		 */
		auto buildTerrain(std::string const &heightmapPath, glm::vec3 size) -> void;

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

		auto setPos(glm::vec3 newPos) -> void;

		auto toggleSmoothBorder() -> void;

		auto getCurrSeasonName() -> std::string;

		auto getCurrMonthName() -> std::string;

		auto getSeasonPauseState() -> bool;

		auto togglePauseSeason() -> void;

		auto selectSeason(float season) -> void;
				
	private:

		std::vector<components::IComponent*> componentList;
	
		glm::vec3 position;								//!< Position of map / terrain.
		bool smoothBorders;
		float seasonTime = 0.0f;
		bool pauseSeason = false;
		glm::vec3 heightLevels[4];
		std::string seasonName[4];
		std::string monthName[12];

		glm::vec2 hight_low;

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by map for drawing.

		// Heightmap variables
		int twidth, theight, nrComponents;
		unsigned char* image;

		// Mesh gen variables
		glm::vec3 unit;
		float yUnit;
		std::vector<modeler::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<modeler::TextureA> textures;

		modeler::Model* model = nullptr;
	};
}