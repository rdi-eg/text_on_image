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
	},
	{'A', {"111111111111",
		   "111110011111",
		   "111110011111",
		   "111100001111",
		   "111100001111",
		   "111001100111",
		   "111001100111",
		   "111001100111",
		   "110011110011",
		   "110000000011",
		   "100000000001",
		   "100111111001",
		   "100111111001",
		   "001111111100",
		   "111111111111",
		   "111111111111",
		   "111111111111",
		   "111111111111"}
	},
	{'B', {"111111111",
		   "000000011",
		   "000000001",
		   "001110001",
		   "001111001",
		   "001110001",
		   "000000011",
		   "000000011",
		   "001111001",
		   "001111100",
		   "001111100",
		   "001111000",
		   "000000001",
		   "000000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'C', {"11111111111",
		   "11110000001",
		   "11000000000",
		   "10000111110",
		   "10011111111",
		   "00111111111",
		   "00111111111",
		   "00111111111",
		   "00111111111",
		   "00111111111",
		   "10011111111",
		   "10001111110",
		   "11000000000",
		   "11110000001",
		   "11111111111",
		   "11111111111",
		   "11111111111",
		   "11111111111"}
	},
	{'D', {"11111111111",
		   "00000000111",
		   "00000000011",
		   "00111110001",
		   "00111111000",
		   "00111111100",
		   "00111111100",
		   "00111111100",
		   "00111111100",
		   "00111111100",
		   "00111111000",
		   "00111110001",
		   "00000000011",
		   "00000000111",
		   "11111111111",
		   "11111111111",
		   "11111111111",
		   "11111111111"}
	},
	{'E', {"11111111",
		   "00000000",
		   "00000000",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00000000",
		   "00000000",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00000000",
		   "00000000",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'F', {"11111111",
		   "00000000",
		   "00000000",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00000001",
		   "00000001",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'G', {"11111111111",
		   "11100000001",
		   "11000000000",
		   "10001111100",
		   "00011111111",
		   "00111111111",
		   "00111100000",
		   "00111100000",
		   "00111111100",
		   "00111111100",
		   "00011111100",
		   "10001111000",
		   "11000000000",
		   "11100000011",
		   "11111111111",
		   "11111111111",
		   "11111111111",
		   "11111111111"}
	},
	{'H', {"1111111111",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0000000000",
		   "0000000000",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'I', {"11",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "11",
		   "11",
		   "11",
		   "11"}
	},
	{'J', {"11111",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11100",
		   "11000",
		   "00001",
		   "00011"}
	},
	{'K', {"1111111111",
		   "0011111000",
		   "0011110001",
		   "0011100111",
		   "0011001111",
		   "0010011111",
		   "0000111111",
		   "0000111111",
		   "0010011111",
		   "0011001111",
		   "0011100111",
		   "0011110011",
		   "0011110001",
		   "0011111000",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'L', {"11111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00000000",
		   "00000000",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'M', {"111111111111",
		   "000111111000",
		   "000011110000",
		   "000011110000",
		   "001001100100",
		   "001001100100",
		   "001001100100",
		   "001100001100",
		   "001100001100",
		   "001110011100",
		   "001110011100",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "111111111111",
		   "111111111111",
		   "111111111111",
		   "111111111111"}
	},
	{'N', {"1111111111",
		   "0001111100",
		   "0001111100",
		   "0000111100",
		   "0000111100",
		   "0010011100",
		   "0010001100",
		   "0011001100",
		   "0011000100",
		   "0011100100",
		   "0011110000",
		   "0011110000",
		   "0011111000",
		   "0011111000",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'O', {"111111111111",
		   "111000000111",
		   "110000000011",
		   "100011110001",
		   "000111111000",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "000111111000",
		   "100011110001",
		   "110000000011",
		   "111000000111",
		   "111111111111",
		   "111111111111",
		   "111111111111",
		   "111111111111"}
	},
	{'P', {"11111111",
		   "00000011",
		   "00000001",
		   "00111000",
		   "00111100",
		   "00111100",
		   "00111000",
		   "00000001",
		   "00000011",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'Q', {"111111111111",
		   "111000000111",
		   "110000000011",
		   "100011110001",
		   "000111111000",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "001111111100",
		   "000111111001",
		   "100011110001",
		   "110000000011",
		   "111000000111",
		   "111111100111",
		   "111111100011",
		   "111111111111",
		   "111111111111"}
	},
	{'R', {"1111111111",
		   "0000001111",
		   "0000000111",
		   "0011100011",
		   "0011110011",
		   "0011110011",
		   "0011100011",
		   "0000000111",
		   "0000001111",
		   "0011100111",
		   "0011100011",
		   "0011110001",
		   "0011111001",
		   "0011111000",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'S', {"111111111",
		   "110000011",
		   "100000001",
		   "000111101",
		   "001111111",
		   "000111111",
		   "100000111",
		   "110000001",
		   "111110000",
		   "111111100",
		   "111111100",
		   "001111000",
		   "000000001",
		   "100000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'T', {"111111111111",
		   "000000000000",
		   "000000000000",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111111111111",
		   "111111111111",
		   "111111111111",
		   "111111111111"}
	},
	{'U', {"1111111111",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0001111000",
		   "1000000001",
		   "1100000011",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'V', {"111111111111",
		   "001111111100",
		   "000111111000",
		   "100111111001",
		   "100011110001",
		   "110011110011",
		   "110011110011",
		   "110001100011",
		   "111001100111",
		   "111000000111",
		   "111100001111",
		   "111100001111",
		   "111100001111",
		   "111110011111",
		   "111111111111",
		   "111111111111",
		   "111111111111",
		   "111111111111"}
	},
	{'W', {"11111111111111111",
		   "00111110001111100",
		   "00011100000111000",
		   "10011100000111001",
		   "10011100100111001",
		   "10011100100111001",
		   "10001000100010001",
		   "11001001110010011",
		   "11001001110010011",
		   "11000001110010011",
		   "11000001110000011",
		   "11100011111000111",
		   "11100011111000111",
		   "11100011111000111",
		   "11111111111111111",
		   "11111111111111111",
		   "11111111111111111",
		   "11111111111111111"}
	},
	{'X', {"11111111111",
		   "10001111000",
		   "11001110001",
		   "11000110011",
		   "11100000011",
		   "11110000111",
		   "11110000111",
		   "11110001111",
		   "11110000111",
		   "11100000111",
		   "11000100011",
		   "11001110001",
		   "10001111001",
		   "00011111000",
		   "11111111111",
		   "11111111111",
		   "11111111111",
		   "11111111111"}
	},
	{'Y', {"111111111111",
		   "000111111000",
		   "100011110001",
		   "110011110011",
		   "110001100011",
		   "111000000111",
		   "111100001111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111110011111",
		   "111111111111",
		   "111111111111",
		   "111111111111",
		   "111111111111"}
	},
	{'Z', {"11111111111",
		   "00000000000",
		   "00000000000",
		   "11111110001",
		   "11111100011",
		   "11111100111",
		   "11111000111",
		   "11110001111",
		   "11100011111",
		   "11000111111",
		   "11001111111",
		   "10001111111",
		   "00000000000",
		   "00000000000",
		   "11111111111",
		   "11111111111",
		   "11111111111",
		   "11111111111"}
	},
	{'a', {"11111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11000011",
		   "10000001",
		   "10111000",
		   "11111100",
		   "10000000",
		   "00000000",
		   "00111100",
		   "00111000",
		   "00000000",
		   "10000100",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'b', {"001111111",
		   "001111111",
		   "001111111",
		   "001111111",
		   "001000011",
		   "000000001",
		   "000111000",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "000111000",
		   "000000001",
		   "001000011",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'c', {"11111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11000001",
		   "10000000",
		   "00001110",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00001110",
		   "10000000",
		   "11000001",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'d', {"111111100",
		   "111111100",
		   "111111100",
		   "111111100",
		   "110000100",
		   "100000000",
		   "000111000",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "000111000",
		   "100000000",
		   "110000100",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'e', {"1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1110000011",
		   "1000000001",
		   "1001111000",
		   "0011111100",
		   "0000000000",
		   "0000000000",
		   "0011111111",
		   "1001111110",
		   "1000000000",
		   "1110000001",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'f', {"1110000",
		   "1100000",
		   "1100111",
		   "1100111",
		   "0000000",
		   "0000000",
		   "1100111",
		   "1100111",
		   "1100111",
		   "1100111",
		   "1100111",
		   "1100111",
		   "1100111",
		   "1100111",
		   "1111111",
		   "1111111",
		   "1111111",
		   "1111111"}
	},
	{'g', {"111111111",
		   "111111111",
		   "111111111",
		   "111111111",
		   "110000100",
		   "100000000",
		   "000111000",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "000111000",
		   "100000000",
		   "110000100",
		   "111111100",
		   "101111000",
		   "100000001",
		   "110000011"}
	},
	{'h', {"00111111",
		   "00111111",
		   "00111111",
		   "00111111",
		   "00100001",
		   "00000000",
		   "00011000",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'i', {"00",
		   "00",
		   "11",
		   "11",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "11",
		   "11",
		   "11",
		   "11"}
	},
	{'j', {"1100",
		   "1100",
		   "1111",
		   "1111",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1100",
		   "1000",
		   "0000",
		   "0001"}
	},
	{'k', {"001111111",
		   "001111111",
		   "001111111",
		   "001111111",
		   "001111000",
		   "001110011",
		   "001100111",
		   "001001111",
		   "000011111",
		   "000011111",
		   "000001111",
		   "001000111",
		   "001100001",
		   "001110000",
		   "111111111",
		   "111111111",
		   "111111111",
		   "111111111"}
	},
	{'l', {"00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "00",
		   "11",
		   "11",
		   "11",
		   "11"}
	},
	{'m', {"11111111111111",
		   "11111111111111",
		   "11111111111111",
		   "11111111111111",
		   "00100001100001",
		   "00000001000001",
		   "00011000011000",
		   "00111100111100",
		   "00111100111100",
		   "00111100111100",
		   "00111100111100",
		   "00111100111100",
		   "00111100111100",
		   "00111100111100",
		   "11111111111111",
		   "11111111111111",
		   "11111111111111",
		   "11111111111111"}
	},
	{'n', {"11111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "00100001",
		   "00000000",
		   "00011000",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'o', {"1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1100000011",
		   "1000000001",
		   "0001110000",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0011111100",
		   "0001111000",
		   "1000000001",
		   "1100000011",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'p', {"111111111",
		   "111111111",
		   "111111111",
		   "111111111",
		   "001000011",
		   "000000001",
		   "000111000",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "000111000",
		   "000000001",
		   "001000011",
		   "001111111",
		   "001111111",
		   "001111111",
		   "001111111"}
	},
	{'q', {"111111111",
		   "111111111",
		   "111111111",
		   "111111111",
		   "110000100",
		   "100000000",
		   "000111000",
		   "001111100",
		   "001111100",
		   "001111100",
		   "001111100",
		   "000111000",
		   "100000000",
		   "110000100",
		   "111111100",
		   "111111100",
		   "111111100",
		   "111111100"}
	},
	{'r', {"111111",
		   "111111",
		   "111111",
		   "111111",
		   "001000",
		   "000000",
		   "000111",
		   "001111",
		   "001111",
		   "001111",
		   "001111",
		   "001111",
		   "001111",
		   "001111",
		   "111111",
		   "111111",
		   "111111",
		   "111111"}
	},
	{'s', {"1111111",
		   "1111111",
		   "1111111",
		   "1111111",
		   "1000001",
		   "0000000",
		   "0001110",
		   "0000111",
		   "1000001",
		   "1110000",
		   "1111100",
		   "0111000",
		   "0000000",
		   "1000001",
		   "1111111",
		   "1111111",
		   "1111111",
		   "1111111"}
	},
	{'t', {"111111",
		   "100111",
		   "100111",
		   "100111",
		   "000000",
		   "000000",
		   "100111",
		   "100111",
		   "100111",
		   "100111",
		   "100111",
		   "100111",
		   "100000",
		   "110000",
		   "111111",
		   "111111",
		   "111111",
		   "111111"}
	},
	{'u', {"11111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00111100",
		   "00011000",
		   "00000000",
		   "10000100",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{'v', {"1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "0011111100",
		   "0001111000",
		   "1001111001",
		   "1001111001",
		   "1000110001",
		   "1100110011",
		   "1100100011",
		   "1110000111",
		   "1110000111",
		   "1110000111",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'w', {"1111111111111",
		   "1111111111111",
		   "1111111111111",
		   "1111111111111",
		   "0011100011100",
		   "0011100011100",
		   "0001100011000",
		   "1001001001001",
		   "1001001001001",
		   "1001001001001",
		   "1000011100001",
		   "1100011100011",
		   "1100011100011",
		   "1100011100011",
		   "1111111111111",
		   "1111111111111",
		   "1111111111111",
		   "1111111111111"}
	},
	{'x', {"1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "0001111000",
		   "1001111001",
		   "1100110011",
		   "1100000011",
		   "1110000111",
		   "1110000111",
		   "1100000011",
		   "1100110011",
		   "1001111001",
		   "0001111000",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111"}
	},
	{'y', {"1111111111",
		   "1111111111",
		   "1111111111",
		   "1111111111",
		   "0011111100",
		   "0001111000",
		   "1001111001",
		   "1000111001",
		   "1100110011",
		   "1100110011",
		   "1110000011",
		   "1110000111",
		   "1111000111",
		   "1111001111",
		   "1110001111",
		   "1110011111",
		   "1000011111",
		   "1000111111"}
	},
	{'z', {"11111111",
		   "11111111",
		   "11111111",
		   "11111111",
		   "00000000",
		   "00000000",
		   "11111001",
		   "11110001",
		   "11100011",
		   "11000111",
		   "10001111",
		   "10001111",
		   "00000000",
		   "00000000",
		   "11111111",
		   "11111111",
		   "11111111",
		   "11111111"}
	},
	{' ', {"11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111",
		   "11111"}
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
			// the two ones are for spacing between characters
			text_overlay[i] += char_pixels[i] + "11";
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
