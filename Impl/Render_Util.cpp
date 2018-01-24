#include <windows.h>
#include <iostream>
#include <GL/freeglut.h>
#include "../Render_Util.h"

namespace RenderUtil
{
	static bool initialized = false;
	static int width;
	static int height;
	static int width_count;
	static int height_count;
	static void(*OnMouseClick)(float posX, float posY);

	void mouseClicks(int button, int state, int x, int y) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (RenderUtil::OnMouseClick){

				GLint viewport[4];                  // Where The Viewport Values Will Be Stored
				glGetIntegerv(GL_VIEWPORT, viewport);           // Retrieves The Viewport Values (X, Y, Width, Height)
				GLdouble modelview[16];                 // Where The 16 Doubles Of The Modelview Matrix Are To Be Stored
				glGetDoublev(GL_MODELVIEW_MATRIX, modelview);       // Retrieve The Modelview Matrix
				GLdouble projection[16];                // Where The 16 Doubles Of The Projection Matrix Are To Be Stored
				glGetDoublev(GL_PROJECTION_MATRIX, projection);     // Retrieve The Projection Matrix
				GLfloat winX, winY, winZ=0.0f;               // Holds Our X, Y and Z Coordinates

				winX = (float)x;                  // Holds The Mouse X Coordinate
				//winY = (float)y;                  // Holds The Mouse Y Coordinate
				winY = (float)viewport[3] - (float)y;

				GLdouble posX, posY, posZ=0.0f;              // Hold The Final Values
				gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

				RenderUtil::OnMouseClick(posX, posY);
			}
		}
	}

	void StartScene()
	{
		if (!initialized)
			return;
		glClear(GL_COLOR_BUFFER_BIT);
		//std::cout << "Begin of scene\n";
	}

	void Render(DWORD color, RECT quad)
	{
		if (!initialized)
			return;
		glBegin(GL_QUADS);
		glColor4bv((const GLbyte*)&color);
		glVertex2i(quad.left , quad.top );
		glVertex2i(quad.right, quad.top);
		glVertex2i(quad.right, quad.bottom);
		glVertex2i(quad.left, quad.bottom);
		glEnd();
	}

	void EndScene()
	{
		if (!initialized)
			return;
		//std::cout << "End of scene\n";
		glutSwapBuffers();
	}


	void Init(int argc, char**argv, void(*displayFunc)(), void(*m)(float posX, float posY), int w, int h, int wcount, int hcount)
	{
		if (!initialized)
		{
			OnMouseClick = m;
			width_count = wcount;
			height_count = hcount;
			width = w;
			height = h;
			glutInit(&argc, argv);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
			glutInitWindowSize(w, h);
			glutInitWindowPosition(100, 100);
			glutCreateWindow("OGL");
			glutIdleFunc(displayFunc);
			glutMouseFunc(mouseClicks);
			initialized = true;

			std::cout << "Cellsize = " << GetCellSize() << std::endl;
		}
	}

	void Loop()
	{
		if (!initialized)
			return;
		glClearColor(0.0f, 0.5f, 0.5f, 0.0f);
		glOrtho(0, width_count*GetCellSize(),0,height_count*GetCellSize(), 0, 100);
		glutMainLoop();
	}

	int GetCellSize()
	{
		return ((width / width_count + 1) + (height / height_count + 1)) / 2;
	}

}