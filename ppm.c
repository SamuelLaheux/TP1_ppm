
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gargouille.h"

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
  picture* load;
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































