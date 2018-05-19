#include "LightSource.hpp"

#include <GLFW/glfw3.h>

environment::LightSource::LightSource(){
	this->reqPos = {0.0f, 0.0f, 5.0f};
	this->lightColor = {1.0f, 1.0f, 1.0f};
	this->attenuation = {1.0f, 1.0f, 1.0f};
	this->ambientCoefficient = 0.1f;
	this->specualarExponent = 32.0f;
}

environment::LightSource::LightSource(glm::vec3 position, glm::vec3 lightColor, glm::vec3 attenuation, float ambientCoefficient, int specualarExponent){
	this->reqPos = position;
	this->lightColor = lightColor;
	this->attenuation = attenuation;
	this->ambientCoefficient = ambientCoefficient;
	this->specualarExponent = specualarExponent;
}

environment::LightSource::~LightSource(){

}

void environment::LightSource::update(float dt)
{
	this->position = glm::vec3(cos(dt * 2.0f * 3.14f) * 600.0f + this->reqPos.x, sin(dt * 2.0f * 3.14f) * 600.0f + this->reqPos.y, this->reqPos.z);
	// Make a rotation matrix that rotates the camera around 
	/*this->rotateBy(glm::vec3(0.0f, 0.0f, 1.0f), dt * 2 * 3.14f);

	// Rotate light for effect
	this->position = (glm::vec3) (this->rotMat * glm::vec4(this->position, 0.0f));*/
}

auto environment::LightSource::getAttenuation() -> glm::vec3
{
	return this->attenuation;
}

auto environment::LightSource::getColor() -> glm::vec3{
	return this->lightColor;
}

auto environment::LightSource::getPosition() -> glm::vec3{
	return this->position;
}

auto environment::LightSource::getAmbientCoefficient() -> float{
	return this->ambientCoefficient;
}

auto environment::LightSource::getSpecularExponent() -> int{
	return this->specualarExponent;
}

void environment::LightSource::setPosition(glm::vec3 position){
	this->position = position;
}

auto environment::LightSource::rotateBy(glm::vec3 rotAxis, float angle) -> void
{
	// Rotate light for effect
	this->rotMat = glm::rotate(glm::mat4(), angle, rotAxis);
}

auto environment::LightSource::translateBy(glm::vec3 vec) -> void
{
	// Translate light for effect
	this->position += vec;
}