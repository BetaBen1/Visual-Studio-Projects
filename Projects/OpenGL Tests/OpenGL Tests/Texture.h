#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);
	void Bind(unsigned int uint);
	virtual ~Texture();
private:
	GLuint m_texture;
};

