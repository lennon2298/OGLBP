#pragma once

#include "ErrorHandling.h"
#include <stb_image.h>
#include <string>

class Texture {
private:
	unsigned int m_RendererID;
	int m_Width, m_Height;
	unsigned char* m_LocalBuffer;
public:
	Texture() {};
	Texture(const std::string& filePath);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};
