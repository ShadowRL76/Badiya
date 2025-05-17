#pragma once

#include <stb/stb_image.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

class Image
{
private:
	int m_width;
	int m_height;
	int m_channels;

	std::vector<uint8_t>m_pixels;
public:
	explicit Image(const std::string& filename)
	{
		int width, height, channels;
		uint8_t* data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, NULL);
		if (!data)
		{
			throw std::runtime_error("Failed to load image: " + filename);
		}

		m_width = width;
		m_height = height;
		m_channels = channels;

		const size_t imageSize = m_width * m_height * m_channels;
		m_pixels.assign(data, data + imageSize);
		stbi_image_free(data);
	}

	[[nodiscard]] uint32_t GetWidth() const { return m_width; }
	[[nodiscard]]  uint32_t GetHeight() const { return m_height; }
	[[nodiscard]] int GetChannels() const { return m_channels; }
	[[nodiscard]] const uint8_t* GetPixels() const { return m_pixels.data(); }
};
