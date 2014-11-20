
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
  picture* load = new picture[1];
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
  picture* load_bw = new picture[1];
  load_bw->width = load->width;
  load_bw->height = load->height;
  load_bw->data = new u_char[(3 * load_bw->width * load_bw->height)];

  // Copy image into image_bw
  memcpy(load_bw->data, load->data, 3 * load_bw->width * load_bw->height * sizeof(*load_bw->data));

  // Desaturate image_bw
  ppm_desaturate(load_bw);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(load_bw, "gargouille_BW.ppm");

  // Free the desaturated image
  delete(load_bw->data);
  delete(load_bw);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Create struct load_small
  picture* load_small = new picture[1];  
  load_small->width = load->width;
  load_small->height = load->height;
  load_small->data = new u_char[(3 * load_small->width * load_small->height)];

  // Copy image into image_small
  memcpy(load_small->data, load->data, 3 * load_small->width * load_small->height * sizeof(*load_small->data));

  // Shrink image_small size 2-fold
  ppm_shrink(load_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(load_small, "gargouille_small.ppm");

  // Free the not yet freed images
  delete(load_small->data);
  delete(load_small);

  delete(load);
  delete(load->data);

  return 0;
}































