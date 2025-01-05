#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <string>
#include <stb/stb_image.h>

class Image
{
private:
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_channels;

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

	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }

	uint32_t GetChannels() const { return m_channels; }

	uint8_t* GetPixels() const { return m_pixels; }
};

#endif