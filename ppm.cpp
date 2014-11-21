
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "gargouille.h"

//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------

  // Create an object load to type gargouille
  //gargouille* load1 = new gargouille(); // Allocation dynamique
  gargouille load2 = gargouille(); // Appel explicite
  
  // Load gargouille.ppm in object load2
  load2.ppm_read_from_file("gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Create an object load_bw of type gargouille
  gargouille load_bw = gargouille(load2);

  // Desaturate image_bw
  load_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  load_bw.ppm_write_to_file("gargouille_BW.ppm");

  // Delete the desaturated image
  delete(load_bw.GetData());
  

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Create an object load_small of type gargouille
  gargouille load_small = gargouille(load2);  

  // Shrink image_small size 2-fold
  load_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  load_small.ppm_write_to_file("gargouille_small.ppm");

  // delete the not yet deleted images
  delete(load_small.GetData());
  delete(load2.GetData());

  return 0;
}































