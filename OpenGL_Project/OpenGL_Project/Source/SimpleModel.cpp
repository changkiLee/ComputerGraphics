#include "..\Include\SimpleModel.h"

void SimpleModel::renderFloor(const int &size)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < size; ++i)
	{
		float x, z;
		x = z = (float)i / (size - 1) * size - size / 2;

		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(x, 0.0f, -size / 2.0f);
		glVertex3f(x, 0.0f, size / 2.0f);
		glVertex3f(-size/2.0f, 0.0f, z);
		glVertex3f(size/2.0f, 0.0f, z);
		glEnd();
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void SimpleModel::renderSolidTeapot(const double &size)
{
	glutSolidTeapot(size);
}

void SimpleModel::renderSphere(const double &size, const int &slice, const int &stack)
{
	glutSolidSphere(size, slice, stack);
}

void SimpleModel::renderTorus(const double &in, const double &out, const int &side, const int &ring)
{
	glutSolidTorus(in, out, side, ring);
}

void SimpleModel::renderString(const char *str, const float &r, const float &g, const float &b)
{
	glPushMatrix();
	glScalef(0.01f, 0.01f, 0.01f);
	glColor3f(r, g, b);
	int len = (int) strlen(str);
	for(int i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}
