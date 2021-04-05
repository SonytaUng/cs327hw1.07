#ifndef DIMS_H
#define DIMS_H
#include <vector>



/* You can't forward reference enums or array types, so most of the headers *
 * need this, thus we put it in it's own file.                              */

typedef enum dim {
  dim_x,
  dim_y,
  num_dims
} dim_t;

typedef int8_t pair_t[2]; // original 

//typedef std::vector<int8_t> pair_t; // think this works, not tested // modified 

#endif
