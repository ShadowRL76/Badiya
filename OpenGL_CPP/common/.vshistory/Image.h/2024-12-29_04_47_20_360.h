#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <string>
#include <stb/stb_image.h>

class Image
{
private:
	int m_width;
	int m_height;
	int m_channels;

	uint8_t* m_pixels;
public:
	Image(const std::string& filename)
	{
		m_pixels = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, NULL);
	}

	~Image()
	{
		stbi_image_free(m_pixels);
	}
	
};

#endif