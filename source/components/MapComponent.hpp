#pragma once

#include "../modeler/Shader.hpp"
#include "../modeler/Model.hpp"
#include "IComponent.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/struct.hpp"

#include <SOIL/SOIL.h>
#include <stdio.h>
//#include <cstdio>

/**
 * @brief Container for classes and structures associated with components. 
 */
namespace components
{
	/**
	 * @brief Interface class for components.
	 */
	class MapComponent : public IComponent
	{	
		protected: 
			// Heightmap variables
			int twidth, theight, nrComponents;
			unsigned char* image;

			// Mesh gen variables
			glm::vec3 unit;
			std::vector<modeler::Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<modeler::TextureA> textures;

			modeler::Model* model = nullptr;

		public:
			/**
			 * @brief Interface component class constructor.
			 */
			MapComponent(std::string const &modelPath, glm::vec2 size);

			/**
			 * @brief Update function for components. 
			 */
			virtual auto update(float dt) -> void;
	
			/**
			 * @brief Draw the mesh on the screen using given shader program.
			 * @param shader A shader program for GL pipeline.
			 */
			virtual auto draw(modeler::Shader shader) -> void;

			virtual auto getType() -> int;
	};
}
