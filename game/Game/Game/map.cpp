#include "map.h"
#include "tile.h"
#include <vector>



map::map(int width, int height, int mapdata[],int tempdata[]) {


	mapContainer.resize(height, std::vector<tile>(0));

	int j = 0;
	int k = 0;
	//for each piece of map data
	for (int i = 0; i < width*height; i++) {
		
		
		
		//if you hit the end of a line
		if (k >= width) {
			//mapContainer.push_back()
			j++;
			k = 0;
		}
		k++;
		//adds a tile to the end of the row at height k
		mapContainer[j].push_back(createTile(mapdata[i], tempdata[i]));
		std::cout << "row" << j << " colum " << i%width << std::endl;
	}

}




tile map::createTile(int noise, int temp){
	int jay[10] = { 3,4,5,6,7,8,5,4,3,6 };
	return tile(noise, temp, false, false, 0, 0, 0, jay );
}









