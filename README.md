# text_on_image
A small header file that helps you write text on images. (It currently supports numbers only lol sorry text is on the way)

It could be helpful for debugging and stuff.

# Usage
* Drop the `rdi_text_on_image.h` into your project and include it.
* It uses `stb_image_resize.h` so make sure you drop that as well.
* You must define STB_IMAGE_RESIZE_IMPLEMENTATION before you include it.

### nuff talking, let's learn with an example:
```c++
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "rdi_text_on_image.h"

int main()
{
  int height, width, channels;
  std::uint8_t* image_data = stbi_load("../test/001_002_mgi_118.jpg", &width, &height, &channels, 0);

  RDI::Public::Image image{
    image_data, // pixels array
    (size_t)channels, // number of channels
    (size_t)width, // input image width
    (size_t)height // input image height
  };

  RDI::Public::Text text{
    "24345543", // text you'd like to display
    10, // size
    100, // x coordinate
    100 // y coordinate as to where you'd like the text to be displayed on the image
  };

  // WARNING: this function changes the pixels in the image that you've passed
  RDI::Public::write_text_on_image(image, text);

  stbi_write_png("../001_002_mgi_118.png", width, height, channels, image_data, 0);

  stbi_image_free(image_data);
}
```

I'm using `stb_image` to load the image. Maybe you use something else, that's okay but 
the byte stream needs to be a one dimentional array of `char` or `std::uint8_t` in the form of `rgbrgbrgb... etc`
where `r`, `g` and `b` are red, green and blue 0 to 255 values respectively.
or if it's a single channel then `ppppp...` where `p` is the pixel value from 0 to 255.

### WARNING
`RDI::Public::write_text_on_image` changes the pixels in the image that you've passed.
If you'd like to preserve the original image, take a copy before sending it to this function.
