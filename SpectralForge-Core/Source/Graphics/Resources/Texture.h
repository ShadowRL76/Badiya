#pragma once

#include <stb/stb_image.h>
#include <cstdint>
#include <string>

namespace Badiya {
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


		[[nodiscard]] uint32_t GetWidth() const { return m_width; }
		[[nodiscard]] uint32_t GetHeight() const { return m_height; }

		[[nodiscard]] int GetChannels() const { return m_channels; }

		[[nodiscard]] uint8_t* GetPixels() const { return m_pixels; }
	};
}