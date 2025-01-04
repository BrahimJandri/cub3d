ghila mapy ary9lay oggar n 3adad lkhanat li illan gh lmap[y][x]

mapx and mapy n is_it_wall arditachka z --> next_y_touch and next_x_touch --> x_intercept and y_intercept

VERTICAL KAGHILA LMOCHKIL
alhamdu lillah lmochkil katin illa gh S_Height S_width ikhsa adskrgh map->y * tile and same thing with x


9199999999999999999
_________________________________________________________________________________________________________
PROBLEM : ILA GH DRAW_RAYS  IGHGIS CAST_RAYS
{
    
} 
Alhamdullah
______________________________________________________________________
PROBLEM : rendering is too slow 
{
    psuedo code to solve it:

    1 Create the Image: Use mlx_new_image to create an off-screen image. This image will act as your canvas.

    2 Get the Image Data: Use mlx_get_data_addr to get a pointer to the image’s pixel data. This is where you'll modify pixels.

    3 Set Pixels: Use your custom my_mlx_pixel_put function to manipulate the pixel values in the image's data.

    4 Render the Image: Use mlx_put_image_to_window to render the prepared image onto the window.
}