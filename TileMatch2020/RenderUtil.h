#pragma once

#include "glad/glad.h"
#include <string>
#include <cmath>

struct CardGeom {

	GLuint FrontVAO;
	GLuint FrontVCount;
		
	GLuint BackVAO;
	GLuint BackVCount;
	
	GLuint SideVAO;
	GLuint SideVCount;

};

struct ScreenRect {

	GLint x;
	GLint y;
	GLint width;
	GLint height;
};



// Sets glScissor and glViewport according to the screen rect
inline void SetDrawArea(ScreenRect rect) {

	glViewport(rect.x, rect.y, rect.width, rect.height);
	glScissor(rect.x, rect.y, rect.width, rect.height);

}

namespace DrawUtil{

	struct Coord2D{

		float x, y; 

	};

}


namespace TextureUtil {

	struct TexCoordinates {

		float xStart, xEnd, yStart, yEnd;
	};

	TexCoordinates GetAtlasCoordinates(int slotCountX, int slotCountY, int slot, int texSizeX, int texSizeY); 

}

namespace LoadUtil{

	GLuint LoadTexture(std::string filepath);

}