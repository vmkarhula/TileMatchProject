#pragma once

#include "glad/glad.h"

struct CardGeom {

	GLuint CardVAO;
	GLuint CardVertexCount;

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