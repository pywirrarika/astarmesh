# A * Mesh 

This work is an implementation of the A* algorithm applyed on a Mesh graph, ideal for a Game Engine. A Skiplist was used for the close list, combined with a array. I hope it can be usefull for future works.

To install use:

./configure
make
sudo make install

If you got this code from a git repo, use autoreconf --install before enter the ./configure step.

The program use a BMP file without compression as the graph, where #FFF pixels are not transitable nodes. Pleas enter the next information from your command line:

astar X Y X2 Y2 input_image.bmp output_image.bmp DEBUG

where: X and Y are the source coordinates; x2 and Y2 are the goal coordinates and DEBUG is a BOOL value to get a verbose output.
