
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "picture.h"

//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "picture.ppm" into image (width and height)
  //--------------------------------------------------------------------------

  // Create an object load to type picture
  // picture* load1 = new picture(); // Allocation dynamique
  // delete(load1);
  picture load2 = picture(); // Appel explicite
  
  // Load picture.ppm in object load2
  load2.ppm_read_from_file("gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Create an object load_bw of type picture
  picture load_bw = picture(load2);

  // Desaturate image_bw
  load_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  load_bw.ppm_write_to_file("gargouille_BW.ppm");


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Create an object load_small of type picture
  picture load_small = picture(load2);  

  // Shrink image_small size 2-fold
  load_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  load_small.ppm_write_to_file("gargouille_small.ppm");

  return 0;
}































