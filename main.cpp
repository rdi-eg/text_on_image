#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#define RDI_TEXT_ON_IMAGE_IMPLEMENTATION
#include "rdi_text_on_image.h"

int main()
{
  int height, width, channels;
  std::uint8_t* image_data = stbi_load("../test/kitten_png_image.png", &width, &height, &channels, 0);

  RDI::Public::Image image{
	image_data, // pixels array
	(size_t)channels, // number of channels
	(size_t)width, // input image width
	(size_t)height // input image height
  };

  RDI::Public::Text text{
	"Here are some text and numbers 5539", // text you'd like to display
	42, // size
	100, // x coordinate
	100 // y coordinate as to where you'd like the text to be displayed on the image
  };

  // WARNING: this function changes the pixels in the image that you've passed
  RDI::Public::write_text_on_image(image, text);

  stbi_write_png("../kitten_png_image.png", width, height, channels, image_data, 0);

  stbi_image_free(image_data);
}
