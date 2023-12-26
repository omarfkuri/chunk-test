
#include <iostream>

#include "ch/ChunkRen.h"


int main()
try {
	
	ChunkRen* ren = new ChunkRen(1, 1, 16, true);

	ren->run();
	delete ren;
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
