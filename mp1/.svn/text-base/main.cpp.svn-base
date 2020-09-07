#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;
PNG rotate(PNG a, PNG b)
{       
        for(size_t yi=0; yi<a.height(); yi++)
        {       
                for(size_t xi=0; xi<a.width();xi++)
                {      
			b(xi,yi)->red=a(a.width()-xi-1,a.height()-yi-1)->red;
			 b(xi,yi)->green=a(a.width()-xi-1,a.height()-yi-1)->green;
			 b(xi,yi)->blue=a(a.width()-xi-1,a.height()-yi-1)->blue;
		}
	}
	return b;
}

int main(){
		PNG	image("in.png");
		
		PNG	rotateImage=PNG( image.width(), image.height());
		rotateImage = rotate(image, rotateImage);
		rotateImage.writeToFile("out.png");
		return 0;
}
