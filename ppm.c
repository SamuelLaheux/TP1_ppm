
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

  // Create struct load
  picture* load = (picture*)malloc(sizeof(load));
  load->width = 0;
  load->height = 0;
  load->data = NULL;
  
  // Load gargouille in struct load
  ppm_read_from_file(load, "gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Create struct load_bw
  picture* load_bw = (picture*)malloc(sizeof(load_bw));
  load_bw->width = load->width;
  load_bw->height = load->height;
  load_bw->data = (u_char*) malloc(3 * load_bw->width * load_bw->height * sizeof(*load_bw->data));

  // Copy image into image_bw
  memcpy(load_bw->data, load->data, 3 * load_bw->width * load_bw->height * sizeof(*load_bw->data));

  // Desaturate image_bw
  ppm_desaturate(load_bw);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(load_bw, "gargouille_BW.ppm");

  // Free the desaturated image
  free(load_bw->data);
  free(load_bw);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Create struct load_small
  picture* load_small = (picture*)malloc(sizeof(load_small));  
  load_small->width = load->width;
  load_small->height = load->height;
  load_small->data = (u_char*) malloc(3 * load_small->width * load_small->height * sizeof(*load_small->data));

  // Copy image into image_small
  memcpy(load_small->data, load->data, 3 * load_small->width * load_small->height * sizeof(*load_small->data));

  // Shrink image_small size 2-fold
  ppm_shrink(load_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(load_small, "gargouille_small.ppm");

  // Free the not yet freed images
  free(load_small->data);
  free(load_small);

  free(load);
  free(load->data);

  return 0;
}































