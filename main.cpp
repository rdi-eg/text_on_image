#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "rdi_text_on_image.h"

TEST_CASE("Write a number")
{
	int height, width, channels;
	std::uint8_t* image_data = stbi_load("../test/kitten_png_image.png", &width, &height, &channels, 0);

	RDI::Public::Image image{
		image_data,
		(size_t)channels,
		(size_t)width,
		(size_t)height
	};

	RDI::Public::Text text{
		"Hey nice kitty 123",
		72,
		100,
		100
	};

	RDI::Public::write_text_on_image(image, text);

	stbi_write_png("../001_002_mgi_118.png", width, height, channels, image_data, 0);

	stbi_image_free(image_data);
}
