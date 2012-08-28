#include <cmath>
#include <glut.h>

void render();
void update(int);

struct LocalTransform
{
	LocalTransform()
		:inLocal(true)
	{
		glPushMatrix();
	}

	~LocalTransform()
	{
		glPopMatrix();
	}
	
	bool push()
	{
		return inLocal;
	}
	
	void pop()
	{
		inLocal = false;
	}
	
	bool inLocal;
};

#define CONCAT(A, B) CONCAT2(A, B)
#define CONCAT2(A,B) A##B
#define GUARD_NAME(A) CONCAT(A, __LINE__)
#define withCurrentTransform for(LocalTransform GUARD_NAME(trans);GUARD_NAME(trans).push();GUARD_NAME(trans).pop())

float angle = 30.f;

float degToRad(float angle)
{
	return (angle / 180.f) * 3.141592653589f;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snow");
	glutDisplayFunc(&render);
	float len = tanf(degToRad(30.f)) / 2;
	glScalef(1.6f, 1.6f, 1.6f);
	glTranslatef(-0.5f, len, 0.f);
	
	glutMainLoop();
	return 0;
}

template<int n>
void drawTree();

template<>
void drawTree<0>() {}//no-op

template<int n>
void drawTree()
{	
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(0.25f, 0.f);
		glVertex2f(.25f, 0.5f);
		glVertex2f(-.25f, 0.5f);
		glVertex2f(-.25f, 0.f);
	}
	glEnd();

	withCurrentTransform
	{
		glTranslatef(0.f, 0.5f, 0.f);

		float angleInRad = degToRad(angle);
		float adjacent = cosf(angleInRad) * 0.5f;
		float opposite = sinf(angleInRad) * 0.5f;
		
		withCurrentTransform
		{
			glRotatef(angle, 0.f, 0.f, 1.f);
			glTranslatef(0.f, opposite / 2.f, 0.f);
			float scale = adjacent / .5f;
			glScalef(scale, scale, 1.f);
			drawTree<n - 1>();
		}

		withCurrentTransform
		{
			glRotatef(90 - angle, 0.f, 0.f, -1.f);
			glTranslatef(0.f, adjacent / 2.f, 0.f);
			float scale = opposite / .5f;
			glScalef(scale, scale, 1.f);
			drawTree<n - 1>();
		}
	}
}

template<int n>
void drawKoch();

template<>
void drawKoch<0>()
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(0.f, 0.f);
		glVertex2f(1.f, 0.f);
	glEnd();
}

float oneThird = 1.f/3.f;
template<int n>
void drawKoch()
{
	withCurrentTransform
	{
		glScalef(oneThird, oneThird, 1.f);
		drawKoch<n - 1>();
	}
	
	withCurrentTransform
	{
		glTranslatef(oneThird, 0.f, 0.f);
		glRotatef(60.f, 0.f, 0.f, 1.f);
		glScalef(oneThird, oneThird, 1.f);
		drawKoch<n - 1>();
	}
	
	withCurrentTransform
	{
		glTranslatef(oneThird + oneThird / 2, oneThird * sinf(degToRad(60.f)), 0.f);
		glRotatef(60.f, 0.f, 0.f, -1.f);
		glScalef(oneThird, oneThird, 1.f);
		drawKoch<n - 1>();
	}
	
	withCurrentTransform
	{
		glTranslatef(oneThird*2, 0.f, 0.f);
		glScalef(oneThird, oneThird, 1.f);
		drawKoch<n - 1>();
	}
}

template<int n>
void drawSnowFlake()
{
	drawKoch<n>();
	
	withCurrentTransform
	{		
		glRotatef(60.f, 0.f, 0.f, -1.f);
		glScalef(1.f, -1.f, 1.f);
		drawKoch<n>();
	}
	
	withCurrentTransform
	{
		glTranslatef(1.f, 0.f, 0.f);
		glRotatef(120.f, 0.f, 0.f, -1.f);
		drawKoch<n>();
	}
}

void render()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glColor3f(1.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawSnowFlake<5>();
	glutSwapBuffers();
}
