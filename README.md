<h1>Cub3D</h1>
<p>This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Our goal will be to make a dynamic view inside a maze, in which you’ll have to find your way</p>

<h2>Parsing Part</h2>
<p>First we parse the map configuration the textures and color so we set a counter for config. We skip empty lines at the beginning of the map, then we start trim whitespaces and comparing textures with their exact sides like NO, EA, WE, SO also colors C for ceiling and F for floor if one of them is the right so we store it and go on after we increment the counter config at the end if we get the counter is less than 6 than the config is wrong .</p>
