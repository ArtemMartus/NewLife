#include "../Header.h"
#include "../Render_Util.h"

namespace RenderUtil
{
	static bool initialized = false;
	static unsigned int width;
	static unsigned int height;
	static unsigned int width_count;
	static unsigned int height_count;
	static unsigned int ratio;
	static float tax;
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

				RenderUtil::OnMouseClick((float)posX, (float)posY);
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

		auto cell = RenderUtil::GetCellSize();

		quad.left = quad.left*cell + cell / 10;
		quad.right = quad.right*cell + cell - cell / 10;
		quad.top = quad.top*cell + cell / 10;
		quad.bottom = quad.bottom*cell + cell - cell / 10;

		glBegin(GL_QUADS);
		glColor4bv((const GLbyte*)&color);
		glVertex2i(quad.left , quad.top );
		glVertex2i(quad.right, quad.top);
		glVertex2i(quad.right, quad.bottom);
		glVertex2i(quad.left, quad.bottom);
		glEnd();
		/*glBegin(GL_POINT);
		glVertex2i(quad.top,quad.right);
		glEnd();*/
	}

	void EndScene()
	{
		if (!initialized)
			return;
		//std::cout << "End of scene\n";
		glutSwapBuffers();
	}


	void Init(int argc, char**argv, void(*displayFunc)(), void(*m)(float posX, float posY), unsigned int w, unsigned int h, unsigned int wcount, unsigned int hcount,int rate,float taxs)
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
			ratio = rate;
			if (ratio > 100)
				ratio = 100;
			if (ratio < 5)
				ratio = 5;
			tax = taxs;
		}
	}

	void Loop()
	{
		if (!initialized)
			return;
		glClearColor(0.0f, 0.5f, 0.5f, 0.0f);
		gluOrtho2D(width_count*GetCellSize(),0,0,height_count*GetCellSize());
		glutMainLoop();
	}

	int GetCellSize()
	{
		return (((float)width / width_count + 1.0f) + ((float)height / height_count + 1.0f)) / 2.0f;
	}

	int GetRatio()
	{
		return ratio;
	}

	float GetTax()
	{
		return tax + 1.0f;
	}

}