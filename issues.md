# L7WAYJ LI BA9I KHASIN:
{
    1 - A, D, W, S for moving in the map.✅
    2 - use keypress release to use multiple key at the same time
    3 - fix the gaps between the walls✅
    4 - sprites (bonus)
    5 - mouse_hook (bonus)
    6 - circular map (bonus)
    11 - Wall Collisions (bonus) ✅
    7 - fixing the problem of walls do not appear when it is a long map
    8 - setting the player depending on the N,S,W,E
    9 - getting the textures of the SO, NO ,EA, WE
    10 - leaks


}










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
PROBLEM AFTER MERGE : 
{
    X AND Y are too big see why:
    map_height = 6, map_width = 14
    ----> distance is so big that's why it stucks in the while loop. figure out whit it has a big number !!!
    ----> found_horz_wall and found_vertical_wall are not set to true when i press a key. WHY !!!
    ----> vert_next_touches are getting bigger after moving. WHY!!!
    ----> because player->x and player->y get a big number after moving then the reason in in move function. HOW!!!
    THE PROBLEM CAME FROM THE DRAW CIRCLE WHERE I SET THE CIRCLE TO BE IN THE MIDDLE OF THE SQUARE (0 w 0)
    ALHAMDU LILLAH
}
STEPS to the BREAK DOWN THE CODE
{
    clear the code from every useless comment. ✅
    convert every for loop to while loop.
}

ISSUES:
1 - It goes through the walls.
2 - when I use textures, after turning left the walls become black
3 - one picture is taken to represent the whole wall. 