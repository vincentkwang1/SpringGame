#include "map.h"
#include "tile.h"


map::map(int width /*Max Width 100*/, int height /*Max Height 100*/, int mapdata[]) {


	//make array got help from link at bottom of code at [1]
	std::unique_ptr<tile[]> mapContainer(tile[100][100]);
	////////////////////



	for (int i = 0; i < 100; i++) {

		for (int j = 0; j < 100; j++) {

			mapContainer
		}
	}

}









// [1] https://stackoverflow.com/questions/14345031/confused-with-object-arrays-in-c