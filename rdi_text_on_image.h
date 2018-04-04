#ifndef RDI_TEXT_ON_IMAGE_H
#define RDI_TEXT_ON_IMAGE_H

#include <vector>
#include <map>
#include <tuple>
#include <memory>

#include "stb_image_resize.h"

/// Use this macro to create a smart pointer to an array
#define MAKE_UNIQUE_ARRAY(TYPE, NAME, SIZE) \
	std::unique_ptr<TYPE[]> NAME = std::make_unique<TYPE[]>((SIZE))

#define TEXT_OVERLAY_SIZE_Y 18.0

namespace RDI
{
namespace Internal
{

typedef std::map<char, std::vector<std::string>> PixelsMap;

const PixelsMap char_to_pixels =
{
	{'0', {"111111111",
		   "110000011",
		   "100000001",
		   "100111001",
		   "000111000",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "000111000",
		   "100111001",
		   "100000001",
		   "110000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'1', {"11111111",
		   "10000111",
		   "00000111",
		   "00100111",
		   "11100111",
		   "11100111",
		   "11100111",
		   "11100111",
		   "11100111",
		   "11100111",
		   "11100111",
		   "11100111",
		   "00000000",
		   "00000000",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'2', {"11111111",
		   "10000011",
		   "00000001",
		   "01111000",
		   "11111100",
		   "11111100",
		   "11111000",
		   "11111001",
		   "11110011",
		   "11000111",
		   "10001111",
		   "00001111",
		   "00000000",
		   "00000000",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'3', {"111111111",
		   "100000011",
		   "000000001",
		   "001111000",
		   "111111100",
		   "111111000",
		   "110000001",
		   "110000001",
		   "111111000",
		   "111111100",
		   "111111100",
		   "011111000",
		   "000000001",
		   "100000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'4', {"1111111111",
		   "1111100011",
		   "1111100011",
		   "1111000011",
		   "1110010011",
		   "1100110011",
		   "1100110011",
		   "1001110011",
		   "0011110011",
		   "0000000000",
		   "0000000000",
		   "1111110011",
		   "1111110011",
		   "1111110011",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'5', {"11111111",
		   "10000001",
		   "10000001",
		   "10011111",
		   "10011111",
		   "10000011",
		   "10000001",
		   "10111000",
		   "11111100",
		   "11111100",
		   "11111100",
		   "01111000",
		   "00000001",
		   "10000011",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'6', {"111111111",
		   "111000011",
		   "110000001",
		   "100011101",
		   "000111111",
		   "000111111",
		   "001000011",
		   "000000001",
		   "000111000",
		   "001111100",
		   "001111100",
		   "100111000",
		   "100000001",
		   "110000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'7', {"11111111",
		   "00000000",
		   "00000000",
		   "11111000",
		   "11111001",
		   "11111001",
		   "11110001",
		   "11110011",
		   "11110011",
		   "11100011",
		   "11100111",
		   "11100111",
		   "11000111",
		   "11001111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'8', {"111111111",
		   "110000011",
		   "000000000",
		   "000111000",
		   "001111100",
		   "000111000",
		   "100000001",
		   "100000001",
		   "000111000",
		   "001111100",
		   "001111100",
		   "000111000",
		   "100000001",
		   "110000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'9', {"111111111",
		   "110000011",
		   "100000001",
		   "000111001",
		   "001111100",
		   "001111100",
		   "000111000",
		   "100000000",
		   "110000100",
		   "111111000",
		   "111111000",
		   "101110001",
		   "100000011",
		   "110000111",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	}
};

} // namespace Internal

namespace Public
{

// DOES NOT OWN std::uint8_t* data
// which means you are responsible of freeing it yourself.
struct Image
{
	std::uint8_t* data;
	size_t channels;
	size_t width;
	size_t height;

	// works with 1 channel only lol
	std::uint8_t get_pixel(int x, int y)
	{
		return data[((x + y*width))];
	}

	void set_pixel(int x, int y, uint8_t value)
	{
		for(size_t c = 0; c < channels; c++)
		{
			data[((x + y*width) * channels) + c] = value;
		}
	}
};

struct Text
{
	std::string text;
	float size;
	size_t position_x;
	size_t position_y;
};

std::vector<std::string> make_text_overlay(std::string text)
{
	using namespace Internal;
	std::vector<std::string> text_overlay(TEXT_OVERLAY_SIZE_Y, "");

        for(char c : text)
	{
		PixelsMap::const_iterator it = char_to_pixels.find(c);
		if (it == char_to_pixels.end())
		{
			throw std::runtime_error("Unknown Character");
		}

		std::vector<std::string> char_pixels = it->second;

		for(size_t i = 0; i < char_pixels.size(); i++)
		{
			text_overlay[i] += char_pixels[i];
		}
	}

	return text_overlay;
}

void write_text_on_image(Image image, Text text)
{
	if(!text.text.size())
	{
		return;
	}

	std::vector<std::string> text_overlay = make_text_overlay(text.text);

	//				  Type		  , Name			 , Size
	MAKE_UNIQUE_ARRAY(std::uint8_t, text_overlay_data, text_overlay.size() * text_overlay[0].size());

	Image text_overlay_image
	{
		text_overlay_data.get(),
		1,
		text_overlay[0].size(),
		text_overlay.size()
	};

	Image text_overlay_resized
	{
		nullptr,
		1,
		text_overlay_image.width * (size_t)(text.size/TEXT_OVERLAY_SIZE_Y),
		text_overlay_image.height * (size_t)(text.size/TEXT_OVERLAY_SIZE_Y)
	};

	//				  Type		  , Name					, Size
	MAKE_UNIQUE_ARRAY(std::uint8_t, text_overlay_resized_data, text_overlay_resized.width * text_overlay_resized.height);

	text_overlay_resized.data = text_overlay_resized_data.get();

	for(size_t y = 0; y < TEXT_OVERLAY_SIZE_Y; y++)
	{
		for(size_t x = 0; x < text_overlay[y].size(); x++)
		{
			text_overlay_image.set_pixel(x, y, text_overlay[y][x]);
		}
	}

	stbir_resize_uint8(text_overlay_image.data, text_overlay_image.width, text_overlay_image.height, 0,
					   text_overlay_resized.data, text_overlay_resized.width, text_overlay_resized.height, 0,
					   1);

	for(size_t y = 0; y < text_overlay_resized.height; y++)
	{
		for(size_t x = 0; x < text_overlay_resized.width; x++)
		{
			if(text_overlay_resized.get_pixel(x, y) == '0')
			{
				image.set_pixel(text.position_x + x, text.position_y + y, 0);
			}
		}
	}
}

} // namespace Public

} // namespace RDI

#endif // RDI_TEXT_ON_IMAGE_H
