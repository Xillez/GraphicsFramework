#include "Glider.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"
#include "../components/GraphicsComponent.hpp"

#include <random>

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;

std::random_device r;
std::default_random_engine generator(r());
std::uniform_real_distribution<float> genX(0.0f, 504.0f);
std::uniform_real_distribution<float> genY(0.0f, 1004.0f);

game::Glider::Glider(std::string const &modelPath)
{
	this->model = new modeler::Model(modelPath);
	
	this->genNewPos();
	this->direction = glm::vec3(-1.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->angle = glm::vec3(0.0f, 0.0f, 0.0f);
	this->speed = 3.0f;

	this->rotQuat = glm::quat(1, 0, 0, 0);

	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertexGlider.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragmentGlider.frag"},
	});
}

auto game::Glider::update(float dt) -> void
{
	this->position += (glm::normalize(((glm::vec3) (/*this->rotationMatrix */ glm::vec4(this->direction, 0.0f)))) * this->speed) * dt;
}

auto game::Glider::draw(float dt) -> void
{
	this->shaderProgram->bind();

	glm::mat4 view = camera->getViewMatrix(); 
	
	glm::mat4 projection = camera->getPerspectiveMatrix();
	glm::vec3 lightPosition = lightSource->getPosition();
	glm::vec3 attenuation = lightSource->getAttenuation(); 
	glm::vec3 lightColor = lightSource->getColor();
	float ambientCoefficient = lightSource->getAmbientCoefficient();
	int specularExponent = lightSource->getSpecularExponent();

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
		{"lightColorID", "lightColor"}
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform1f(uniforms["ambientCoefficientID"], ambientCoefficient);
	glUniform1i(uniforms["specularExponentID"], specularExponent);
	glUniform3fv(uniforms["lightColorID"], 1, glm::value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, glm::value_ptr(lightPosition));

	glUniform3fv(uniforms["camPosID"], 1, glm::value_ptr(camera->getPos()));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 modelm;

	//modelm = glm::rotate(modelm, glm::radians(this->angle.y), this->up);
	//modelm = glm::rotate(modelm, glm::radians(this->angle.z), glm::cross(this->direction, this->up));
	//modelm = glm::rotate(modelm, glm::radians(this->angle.x), this->direction);
	modelm = glm::translate(modelm, this->position); // Translate it down so it's at the center of the scene.
	modelm = modelm * glm::toMat4(this->rotQuat);
	modelm = glm::scale(modelm, glm::vec3(1.0f, 1.0f, 1.0f));	
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	this->model->Draw(*shaderProgram);

	shaderProgram->unbind();
}

auto game::Glider::setPos(glm::vec3 newPos) -> void {
	this->position = newPos;
}

auto game::Glider::rotateBy(glm::vec3 angle) -> void
{

	// Convert angles to radians
	angle = glm::vec3(glm::radians(angle.x), glm::radians(angle.y), glm::radians(angle.z));

	// Get a quaternion for rotation
	glm::quat quat = glm::quat(angle);

	// Update member quaternion
	this->rotQuat *= quat;

	// Rotate camera's current target with rotation around horizontal rotation axis (0, 1, 0).
	this->direction = (glm::vec3) (quat * glm::vec4(this->direction, 0));

	// Rotate camera's current target with rotation around vertical rotation axis ("vertRotAxis").
	this->up = (glm::vec3) (quat * glm::vec4(this->up, 0));
}

auto game::Glider::translateBy(glm::vec3 translate) -> void
{
	//glm::mat4 translationMatrix = glm::translate(glm::mat4(), translate);
	//this->pos = (glm::vec3) (translationMatrix * glm::vec4(pos, 0));
	this->position += translate;
}

auto game::Glider::incSpeed() -> void
{
	this->speed = glm::clamp(this->speed += 1.0f, 3.0f, 6.0f);
}
		
auto game::Glider::decSpeed() -> void
{
	this->speed = glm::clamp(this->speed -= 1.0f, 3.0f, 6.0f);
}

auto game::Glider::genNewPos() -> void
{
	glm::vec3 pos = glm::vec3(genX(generator), 125.0f, genX(generator));
	this->startPos = pos;
	this->position = pos;
}

auto game::Glider::resetPos() -> void
{
	this->position = this->startPos;
}

auto game::Glider::getPos() -> glm::vec3
{
	return this->position;
}

auto game::Glider::getRotQuat() -> glm::quat
{
	return this->rotQuat;
}

auto game::Glider::getSpeed() -> float
{
	return this->speed;
}