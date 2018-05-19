#include "Map.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;

game::Map::Map(glm::vec3 position)
{
	this->position = position;
	this->heightLevels[0] = glm::vec3(40.0f, 60.0f, 80.0f);	// Summer
	this->heightLevels[1] = glm::vec3(30.0f, 40.0f, 60.0f);	// Autumn
	this->heightLevels[2] = glm::vec3(20.0f, 0.0f, 0.0f);	// Winter
	this->heightLevels[3] = glm::vec3(40.0f, 60.0f, 75.0f);	// Spring
	this->seasonName[0] = "Summer";
	this->seasonName[1] = "Autumn";
	this->seasonName[2] = "Winter";
	this->seasonName[3] = "Spring";
	this->monthName[0] = "June";
	this->monthName[1] = "July";
	this->monthName[2] = "August";
	this->monthName[3] = "September";
	this->monthName[4] = "October";
	this->monthName[5] = "November";
	this->monthName[6] = "December";
	this->monthName[7] = "January";
	this->monthName[8] = "Feburary";
	this->monthName[9] = "March";
	this->monthName[10] = "April";
	this->monthName[11] = "May";
	this->smoothBorders = true;

	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
	});
}

auto game::Map::buildTerrain(std::string const &heightmapPath, glm::vec3 size) -> void
{
	// Load image from file with given path.
	this->image = SOIL_load_image(heightmapPath.c_str(), &twidth, &theight, &nrComponents, SOIL_LOAD_L);
	if (image)
	{
		// Get the unit distance for xy plane and y-axis
		this->unit = glm::vec3(twidth, twidth / 255, theight);

		this->hight_low = glm::vec2(0.0f, 255.0f);

		modeler::Vertex vert;

		// Generate all vertecies
		// TODO: Rename y to z
		for (int z = 0; z < theight; z++)
		{
			for (int x = 0; x < twidth; x++)			
			{
				vert.Position = glm::vec3(x + this->position.x, 
										  (this->image[(int) (x + (z * twidth))] * unit.y) + this->position.y, 
										  z + this->position.z);
				vert.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
				vert.TexCoords = glm::vec2(0.0f, 0.0f);

				//printf("Height (%d, %d): %f. UnitY: %f\n", x, y, vert.Position.y, unit.y);

				this->vertices.push_back(vert);

				// If current value is higher, it is the newest highest height level (x-value)
				//if (this->hight_low.x < vert.Position.y)
				//	hight_low.x = vert.Position.y;
				//
				//// If current value is lower, it is the newest lowesest height level (y-value)
				//if (this->hight_low.y > vert.Position.y)
				//	hight_low.x = vert.Position.y;
			}
		}
		SOIL_free_image_data(image); // Free the data read from file after creating opengl texture 
		
		// Generate indices, if not on the right/top edge of image.
		// TODO: Rename y to z
		for (int z = 0; z < theight - 1; z++)
		{
			for (int x = 0; x < twidth - 1; x++)
			{
				this->indices.push_back( x 		+ (twidth *  z));
				this->indices.push_back((x + 1) + (twidth *  z));
				this->indices.push_back( x 		+ (twidth * (z + 1)));
				this->indices.push_back( x 		+ (twidth * (z + 1)));
				this->indices.push_back((x + 1) + (twidth *  z));
				this->indices.push_back((x + 1) + (twidth * (z + 1)));
			}
		}

		// Generate normals
		for (int i = 0; i < this->indices.size(); i += 3)
		{
			// Use indecied to find connected vertecies and build two vectors from them.
			glm::vec3 vec1 = this->vertices[this->indices[i + 2]].Position - this->vertices[this->indices[i + 1]].Position, 
				      vec2 = this->vertices[this->indices[i    ]].Position - this->vertices[this->indices[i + 1]].Position;

			// Calculate their cross product
			glm::vec3 normal = glm::cross(vec2, vec1);

			// Apply that new normal to the vertecies normal. 
			this->vertices[this->indices[i]].Normal += normal;
			this->vertices[this->indices[i]].Normal = glm::normalize(this->vertices[this->indices[i]].Normal);

			this->vertices[this->indices[i + 1]].Normal += normal;
			this->vertices[this->indices[i + 1]].Normal = glm::normalize(this->vertices[this->indices[i + 1]].Normal);

			this->vertices[this->indices[i + 2]].Normal += normal;
			this->vertices[this->indices[i + 2]].Normal = glm::normalize(this->vertices[this->indices[i + 2]].Normal);
		}
	}
	else
	{
		printf("%s SOIL cannot load image \n%s\n", TAG_WARN.c_str(), heightmapPath);
	}

	this->model = new modeler::Model(this->vertices, this->indices, this->textures);
}

auto game::Map::update(float dt) -> void
{
	float seasonDT = dt / 60; 			// A year is 60 seconds

	if (!pauseSeason)
		this->seasonTime += seasonDT;

	if (this->seasonTime > 1.0f)
		this->seasonTime = 0.0f;
}

auto game::Map::draw(float dt) -> void
{
	// Bind wanted shader program
	this->shaderProgram->bind();

	// Get view and projection matrix
	glm::mat4 view = camera->getViewMatrix(); 
	glm::mat4 projection = camera->getPerspectiveMatrix();
	
	// Get lighting information
	glm::vec3 lightPosition = lightSource->getPosition();
	glm::vec3 attenuation = lightSource->getAttenuation(); 
	glm::vec3 lightColor = lightSource->getColor();
	float ambientCoefficient = lightSource->getAmbientCoefficient();
	int specularExponent = lightSource->getSpecularExponent();

	// Map out uniform ID's with variable names
	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, std::string>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"lightSourcePositionID","lightSourcePosition"},
		{"camPosID", "CamPos"},
		{"attenuationAID", "attenuationA"},
		{"attenuationBID", "attenuationB"},
		{"attenuationCID", "attenuationC"},
		{"ambientCoefficientID", "ambientCoefficient"},
		{"specularExponentID", "specularExponent"},
		{"lightColorID", "lightColor"},
		{"heightLevelsID", "heightLevels"},
		{"smoothBordersID", "smoothBorders"}
	}));

	// Bind uniforms in shaders using above mapping
	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform1f(uniforms["ambientCoefficientID"], ambientCoefficient);
	glUniform1i(uniforms["specularExponentID"], specularExponent);
	glUniform3fv(uniforms["lightColorID"], 1, glm::value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, glm::value_ptr(lightPosition));
	glUniform3fv(uniforms["heightLevelsID"], 1, glm::value_ptr(this->heightLevels[(int) (this->seasonTime * 4)]));
	glUniform1f(uniforms["smoothBordersID"], this->smoothBorders);

	glUniform3fv(uniforms["camPosID"], 1, glm::value_ptr(camera->getPos()));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));

	// Build a model matrix to use for translation, rotation and scaling
	glm::mat4 modelm;
	modelm = glm::translate(modelm, this->position); // Translate it down so it's at the center of the scene.
	//modelm = glm::scale(modelm, glm::vec3(1.0f, 1.0f, 1.0f));	
	//modelm = glm::rotate(modelm, 0.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));

	// Draw model
	this->model->Draw(*shaderProgram);

	// Unbind shaders
	shaderProgram->unbind();
}

auto game::Map::setPos(glm::vec3 newPos) -> void
{
	this->position = newPos;
}

auto game::Map::toggleSmoothBorder() -> void
{
	this->smoothBorders = !this->smoothBorders;
}

auto game::Map::getCurrSeasonName() -> std::string
{
	// Wanted season name is season time (0 -> 1) times 4 (nr seasons's in a year)
	return this->seasonName[(int) (this->seasonTime * 4)];
}

auto game::Map::getCurrMonthName() -> std::string
{
	// Wanted month name is season time (0 -> 1) times 12 (nr month's in a year)
	return this->monthName[(int) (this->seasonTime * 12)];
}

auto game::Map::getSeasonPauseState() -> bool
{
	return this->pauseSeason;
}

auto game::Map::togglePauseSeason() -> void
{
	this->pauseSeason = !this->pauseSeason;
}

auto game::Map::selectSeason(float season) -> void
{
	// Season-time is the wanted season devidied by four (max four season in a year)
	this->seasonTime = season;
}