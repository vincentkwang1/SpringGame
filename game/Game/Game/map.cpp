#include "map.h"
#include "tile.h"
#include <vector>



map::map(int width, int height, int mapdata[],int tempdata[]) {


	mapContainer.resize(height, std::vector<tile>(width));

	int j = 0;
	
	//for each piece of map data
	for (int i = 0; i < width*height; i++) {
		
		std::cout << "row" << j << " colum " << i  << std::endl;
		
		//if you hit the end of a line
		if (i >= width+1) {
			
			j++;
		}
		//adds a tile to the end of the row at height k
		mapContainer[j].push_back(createTile(mapdata[i], tempdata[i]));

	}

}




tile map::createTile(int noise, int temp){
	return tile();
}









