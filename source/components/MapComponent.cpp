#include "MapComponent.hpp"

components::MapComponent::MapComponent(std::string const &heightmapPath, glm::vec2 size) : IComponent()
{
	// Load image from file with given path.
	this->image = SOIL_load_image(heightmapPath.c_str(), &twidth, &theight, &nrComponents, SOIL_LOAD_L);
	if (image)
	{
		// Get the unit distance for xy plane and y-axis
		//this->vertices.reserve(twidth * theight);
		this->unit = glm::vec3(twidth / size.x, (size.x / 2) / 255, theight / size.y);
		//this->yUnit = (twidth / 4) / 255;

		// Generate all vertecies
		for (int y = 0; y < size.y; y++)
		//for (int y = 0; y < theight; y++)
		{
			for (int x = 0; x < size.x; x++)			
			//for (int x = 0; x < twidth; x++)			
			{
				//this->vertices[x + (y * size.y)] = Vertex(glm::vec3(x * xzUnit.x, image[(x * xzUnit.x * )]));
				this->vertices.push_back(modeler::Vertex(glm::vec3(x * unit.x, this->image[x + (y * twidth)] * unit.y, y * unit.z), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
				//this->vertices.push_back(modeler::Vertex(glm::vec3(x, this->image[x + (y * twidth)] * yUnit, y), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
			}
		}
		SOIL_free_image_data(image); // Free the data read from file after creating opengl texture 
		
		// Generate indices, if not on the right/top edge of image.
		for (int y = 0; y < size.y - 1; y++)
		//for (int y = 0; y < theight - 1; y++)
		{
			for (int x = 0; x < size.x - 1; x++)			
			//for (int x = 0; x < twidth - 1; x++)
			{
				//this->indices.push_back(x);
				//this->indices.push_back(x + 1);
				//this->indices.push_back(x + (twidth * (y + 1)));
				//this->indices.push_back(x + (twidth * (y + 1)));
				//this->indices.push_back(x + 1);
				//this->indices.push_back((x + 1) + (twidth * (y + 1)));

				this->indices.push_back(x);
				this->indices.push_back(x + 1);
				this->indices.push_back(x + (size.x * (y + 1)));
				this->indices.push_back(x + (size.x * (y + 1)));
				this->indices.push_back(x + 1);
				this->indices.push_back((x + 1) + (size.x * (y + 1)));
			}
		}
	}
	else
	{
		printf("%s SOIL cannot load image \n%s\n", TAG_WARN.c_str(), heightmapPath);
	}

	for (int i = 504; i < 534; i++)
	{
		printf("(%f, %f, %f)\n", vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
	}

	this->model = new modeler::Model(this->vertices, this->indices, this->textures);
}

// Virtual
auto components::MapComponent::update(float dt) -> void
{

}

// Virtual
auto components::MapComponent::draw(modeler::Shader shader) -> void
{
	this->model->Draw(shader);
}

// Virtual
auto components::MapComponent::getType() -> int
{
	return MAP_GRAPHICS_COMPONENT;
}