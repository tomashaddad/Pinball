#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>
#include <iostream>

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader, const bool& fromFile)
	: m_programID(0)
	, m_vertexID(0)
	, m_fragmentID(0)
	, m_geometryID(0)
	, m_compiled(false)
{
	std::string vs;
	std::string fs;
	std::string gs;

	if (fromFile) {
		vs = parseFile(vertexShader);
		fs = parseFile(fragmentShader);
		if (!geometryShader.empty()) {
			gs = parseFile(geometryShader);
		}
	} else {
		vs = vertexShader;
		fs = fragmentShader;
		if (!geometryShader.empty()) {
			gs = geometryShader;
		}
	}

	m_programID = glCreateProgram();
	m_vertexID = compileShader(GL_VERTEX_SHADER, vs);
	m_fragmentID = compileShader(GL_FRAGMENT_SHADER, fs);
	if (!geometryShader.empty()) {
		m_geometryID = compileShader(GL_GEOMETRY_SHADER, gs);
	}

	attachShaderByID(m_vertexID);
	attachShaderByID(m_fragmentID);
	if (!geometryShader.empty()) {
		attachShaderByID(m_geometryID);
	}

	glLinkProgram(m_programID);

	GLint linkResult;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE) {
		GLsizei infoLength;
		glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &infoLength);
		std::vector<char> message(infoLength);
		glGetProgramInfoLog(m_programID, infoLength, &infoLength, &message[0]);
		std::cerr << &message[0] << std::endl;

		glDeleteProgram(m_programID);
	}
	else
	{
		glValidateProgram(m_programID);
		m_compiled = true;
	}

	glDetachShader(m_programID, m_vertexID);
	glDeleteShader(m_vertexID);

	glDetachShader(m_programID, m_fragmentID);
	glDeleteShader(m_fragmentID);

	if (!geometryShader.empty()) {
		glDetachShader(m_programID, m_geometryID);
		glDeleteShader(m_geometryID);
	}
}

GLuint Shader::compileShader(const GLenum& type, const std::string& shader) {
	GLuint shaderID = glCreateShader(type);
	if (shaderID) {
		const char* cStrShader = shader.c_str();
		glShaderSource(shaderID, 1, &cStrShader, nullptr);
		glCompileShader(shaderID);

		GLsizei compileResult;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == GL_FALSE) {
			GLsizei infoLength;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLength);
			std::vector<char> message(infoLength);
			glGetShaderInfoLog(shaderID, infoLength, &infoLength, &message[0]);
			std::cerr << &message[0] << std::endl;
			return 0;
		}
	}
	return shaderID;
}

void Shader::attachShaderByID(const GLuint id) {
	if (id != 0) {
		glAttachShader(m_programID, id);
	}
}

std::string Shader::parseFile(const std::string& file) {
	if (file.empty()) {
		return "";
	}

	std::ifstream stream(file);

	if (!stream.is_open()) {
		std::cerr << "Shader " << file << " could not be opened." << std::endl;
		return "";
	}

	return std::string(
		(std::istreambuf_iterator<char>(stream)),
		(std::istreambuf_iterator<char>())
	);
}

Shader::~Shader() {
	glDeleteProgram(m_programID);
}

void Shader::bind() const {
	glUseProgram(m_programID);
}

void Shader::unbind() const {
	glUseProgram(0);
}

const GLuint Shader::getID() const {
	return m_programID;
}

GLint Shader::getUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());

	if (location == -1) {
		std::cerr << uniformName << " could not be found" << std::endl;
	}

	return location;
}

void Shader::setInt(const std::string& uniformName, int value) {
	glUniform1i(getUniformLocation(uniformName), value);
}

void Shader::setFloat(const std::string& uniformName, float value) {
	glUniform1f(getUniformLocation(uniformName), value);
}

void Shader::setVec2f(const std::string& uniformName, const glm::vec2& value) {
	glUniform2f(getUniformLocation(uniformName), value.x, value.y);
}

void Shader::setVec3f(const std::string& uniformName, const glm::vec3& value) {
	glUniform3f(getUniformLocation(uniformName), value.x, value.y, value.z);
}

void Shader::setVec4f(const std::string& uniformName, const glm::vec4& value) {
	glUniform4f(getUniformLocation(uniformName), value.x, value.y, value.z, value.w);
}

void Shader::setMat3(const std::string& uniformName, const glm::mat3& matrix) {
	glUniformMatrix3fv(getUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setMat4(const std::string& uniformName, const glm::mat4& matrix) {
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setMaterial(const std::string& materialName, const Material& material) {
	const std::string ambient = materialName + ".ambient";
	const std::string diffuse = materialName + ".diffuse";
	const std::string specular = materialName + ".specular";
	const std::string shininess = materialName + ".shininess";

	glUniform3fv(getUniformLocation(ambient), 1, glm::value_ptr(material.ambient));
	glUniform3fv(getUniformLocation(diffuse), 1, glm::value_ptr(material.diffuse));
	glUniform3fv(getUniformLocation(specular), 1, glm::value_ptr(material.specular));
	glUniform1f(getUniformLocation(shininess), material.shininess);
}