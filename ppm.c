
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
//                                   Struct
//============================================================================
typedef struct
{
  int width;
  int height;
  u_char* data;
}picture;

//============================================================================
//                           Function declarations
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(picture* im, char* nom);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(picture* im, char* nom);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(picture* im);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(picture* im, int factor);



//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  u_char* image = NULL;

  // Create struct load
  picture* load; // = (picture*)malloc(sizeof(picture));
  load->width = 0;
  load->height = 0;
  load->data = NULL;
  
  ppm_read_from_file(load, "gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  int width_bw  = load->width;
  int height_bw = load->height;
  u_char* image_bw = (u_char*) malloc(3 * load->width * load->height * sizeof(*image_bw));
  memcpy(image_bw, load->data, 3 * load->width * load->height * sizeof(*image_bw));

  // Desaturate image_bw
  ppm_desaturate(load);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(load, "gargouille_BW.ppm");

  // Free the desaturated image
  free(image_bw);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = load->width;
  int height_small = load->height;
  u_char* image_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*image_small));
  memcpy(image_small, load->data, 3 * width_small * height_small * sizeof(*image_small));

  // Shrink image_small size 2-fold
  ppm_shrink(load, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(load, "gargouille_small.ppm");

  // Free the not yet freed images
  free(image);
  free(image_small);
  free(load->data);

  return 0;
}



//============================================================================
//                           Function declarations
//============================================================================
void ppm_write_to_file(picture* im, char* nom)
{
  // Create a pointer on a file
  FILE* ppm_output = fopen(nom, "wb");

  // Write header
  fprintf(ppm_output, "P6\n%d %d\n255\n", im->width, im->height);

  // Write pixels
  fwrite(im->data, 3, (im->width)*(im->height), ppm_output);

  // Close the file
  fclose(ppm_output);
}

void ppm_read_from_file(picture* im, char* nom)
{
  // Create a pointer on a file
  FILE* ppm_input = fopen(nom,"rb");

  // Read file header
  fscanf(ppm_input, "P6\n%d %d\n255\n", &(im->width), &(im->height));

  // Allocate memory according to width and height
  im->data = (u_char*) malloc(3 * (im->width) * (im->height) * sizeof(*(im->data)));

  // Read the actual image data
  fread(im->data, 3, (im->width) * (im->height), ppm_input);

  // Close the file
  fclose(ppm_input);
}

void ppm_desaturate(picture* im)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < im->width ; x++)
  {
    for (y = 0 ; y < im->height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += im->data[ 3 * (y * im->width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&(im->data)[3 * (y * im->width + x)], grey_lvl, 3);
    }
  }
}

void ppm_shrink(picture* im, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (im->width) / factor;
  int new_height  = (im->height) / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (im->width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (im->width) + dx);

          // Accumulate RGB values
          red   += (im->data)[i0+delta_i];
          green += (im->data)[i0+delta_i+1];
          blue  += (im->data)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  im->width  = new_width;
  im->height = new_height;

  // Update image
  (im->data) = new_image;
}



































