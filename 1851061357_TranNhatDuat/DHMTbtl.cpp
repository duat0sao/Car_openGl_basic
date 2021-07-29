#include <GL/glut.h>









static int dichchuyen = 0;
float spin = 0.0f;
int td = 1;




//Hàm Xử lý tốc độ quay của bánh xe.
void spinDisplay(void) {
	spin = spin + 1;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}



//Hàm khai bao thao tác xử lý chiếu sáng: ánh sáng bao quanh, ánh sáng khuếch tán, ánh sáng phản chiếu Red, Green, Blue.
void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
	GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
	GLfloat specularR, GLfloat specularG, GLfloat specularB,
	GLfloat shininess)
{
	GLfloat ambient[] = { ambientR, ambientG, ambientB }; //Ánh sáng môi trường.
	GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB }; //Ánh sáng khuếch tán.
	GLfloat specular[] = { specularR, specularG, specularB }; //Ánh sáng phản chiếu.
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	//Thao tác điều khiển ngăn xếp ma trận vẽ thanh nghiên giống đường đi.
	glColor3f(1.0, 1.0, 0.0);
	setMaterial(0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 50);
	glPushMatrix();


	


	//Thao tác ma trận vẽ ô tô biến đổi điểm nhìn và biến đổi mô hình.
	glPushMatrix();
	glPushMatrix();
	setMaterial(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 50);



	//Vẽ ngăn xếp trên thân dưới hình
	glTranslatef((GLfloat)dichchuyen / 5.3, (GLfloat)dichchuyen / 5.3, 0);
	glScalef(1.0, 0.5, 2.0);
	glutSolidCube(0.5);
	glPopMatrix();



	//Vẽ ngăn xếp thân trên hình.
	glPushMatrix();
	glTranslatef((GLfloat)dichchuyen / 6, (GLfloat)dichchuyen / 6, 0);
	setMaterial(0.0, 0.0, 0.0, 0.6, 0.6, 0.0, 1.0, 1.0, 1.0, 50);
	glTranslatef(0.55, 0.75, 0.5);
	glScalef(1.0, 0.5, 1.5);
	glutSolidCube(0.35);
	glPopMatrix();
	glTranslatef(0.0, 0.0, 0.25);
	glPushMatrix();



	// Thao tác ma trận thao tác vẽ bánh xe và chuyển động.
	setMaterial(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 50);
	glTranslatef((GLfloat)dichchuyen / 5, (GLfloat)dichchuyen / 5, 0);




	//Bánh trước 1.
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(0.1, -0.4, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glutSolidTorus(0.05, .1, 9.0, 9.0);



	//Bánh trước 2.
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, -0.3);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, -0.1);
	glutSolidTorus(0.05, 0.1, 9.0, 9.0);
	glPopMatrix();
	glTranslatef(0.0, 0.0, -0.6);
	glPushMatrix();
	glTranslatef((GLfloat)dichchuyen / 5, (GLfloat)dichchuyen / 5, 0);
	setMaterial(1.0, 1.0, 1.0, 0.0, 0.0, .0, 1.0, 1.0, 1.0, 50);



	//Bánh sau 1.
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(0.2, -0.45, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glutSolidTorus(.05, .1, 9.0, 9.0);



	//Bánh sau 2.
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.007, -0.2);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glutSolidTorus(0.05, .1, 9.0, 9.0);



	glPopMatrix();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();






}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}



//Hàm sử lý sự kiện hoạt cảnh bàn phím
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd': //Xe di chuyển xuống dốc.
		if (dichchuyen >= 13) {
			td = 0;
		}
		else
		{
			td = 1;
		}
		dichchuyen += td;
		glutPostRedisplay();
		break;


	case 'a': //Xe di chuyển lên dốc.
		if (dichchuyen <= -50) {
			td = 0;
		}
		else {
			td = 1;
		}
		dichchuyen -= td;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
//Hàm xử lý sự kiện thao tác với chuột
void MouseButton(int type_button, int state, GLint x, GLint y)
{
	switch (type_button)
	{
	case GLUT_LEFT_BUTTON: //click chuột trái bánh xe chuyển động quay.
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	default:
		break;
	}
}
void MouseMove(int x, int y) {
	int a = 5;
}
void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init();

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Oto");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(MouseButton);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, 1, 4, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
