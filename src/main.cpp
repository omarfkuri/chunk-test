
#include <iostream>

#include "ch/ChunkRen.h"


int main()
try {
	/**
	 * ChunkRen is a subclass of Logic, which
	 * handles window creation and the main 
	 * loop. It renders a grid of Chunks, each
	 * with a single mesh procedurally generated
	 * depending on the following parameters:
	 * 
	 * 	1. The width and depth of the map
	 *  2. The height of the map
	 * 	3. The width, depth and height of each chunk
	 * 	4. Whether the chunk should be hollow or not
	 **/

	ChunkRen(4, 1, 32, true).run();
}
catch(std::string error)
{
	std::cerr << "Error " << error << "\n";
}
catch(unsigned char const* error)
{
	std::cerr << "Error " << error << "\n";
}
catch(char const* error)
{
	std::cerr << "Error " << error << "\n";
}
catch(std::out_of_range error)
{
	std::cerr << "Out of Range\n " << error.what() << "\n";
}
