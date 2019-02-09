/* 
  Homework 5 Problem 1
  CS 350
  Dr. Akis

  Simple 3D Scene
  and Practice Excercise 5.6.3

 */
#include <windows.h>	
#include <iostream.h>
#include <gl/gl.h>
#include <gl/Glu.h>	
#include <gl/glut.h>
#include "Canvas.h"
#include "Mesh.h"


Canvas cvs (640, 480, "Wine Glass 3D" );


//<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>
void myMouse ( int button, int state, GLint x, GLint y )
{
   
   if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
      exit ( -1 );
 }

//<<<<<<<<<<<<<<< wall >>>>>>>>>>>>>>>>
void wall(double thickness)
{ //	draw thin wall with top = xz-plane, corner at origin
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

//<<<<<<<<<<<<<<<<<< tableLeg >>>>>>>>>>>>>>>>>>>
void tableLeg(double thick, double len)
{
	glPushMatrix();
	glTranslated(0, len/2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<< jack part >>>>>>>>>>>>> 
void jackPart()
{ // draw one axis of the unit jack - a stretched sphere
	glPushMatrix(); 
	glScaled(0.2,0.2,1.0);
	glutSolidSphere(1,15,15); 
	glPopMatrix(); 
	glPushMatrix();
	glTranslated(0,0,1.2); // ball on one end
	glutSolidSphere(0.2,15,15); 
	glTranslated(0,0, -2.4);
	glutSolidSphere(0.2,15,15); // ball on the other end
	glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<< jack >>>>>>>>>>>>>>>>>>>> 
void jack() 
{ // draw a unit jack out of spheroids
	glPushMatrix(); 
	jackPart();
	glRotated(90.0, 0, 1,0); 
	jackPart();
	glRotated(90.0, 1,0,0); 
	jackPart();
	glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< table >>>>>>>>>>>>>>>>>>>>
void table(double topWid, double topThick, double legThick, double legLen)
{ // draw the table - a top and four legs
	glPushMatrix(); // draw the table top
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist = 0.95 * topWid/2.0 - legThick / 2.0;
	glPushMatrix();	// draw the four table legs
	glTranslated(dist, 0, dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	tableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	tableLeg(legThick, legLen);
	glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<< displaySolid >>>>>>>>>>>>>>>>>>>>>>
void displaySolid(void)
{
//set properties of the surface material
	GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f}; // gray
	GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	// set the light source properties
	GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	// set the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 1.0; // half-height of the window
	glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3, 1.3, 2.0, 0.0, 0.25, 0.0, 0.0, 1.0, 0.0); //original
	
// start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
	glPushMatrix();
	/* Translation changed to place jack on the floor */
	//Original was
	//glTranslated(0.4, 0.4, 0.6);
	glTranslated(0.4, 0.2, 0.8); //placing jack on the floor
	glRotated(45,0,0,1);
	glScaled(0.08, 0.08, 0.08);
	jack();							// draw the jack
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6, 0.38, 0.5);
	glRotated(30,0,1,0);
	glutSolidTeapot(0.08);			// draw the teapot
	glPopMatrix();
	glPushMatrix();
	/* Translation changed to place sphere on top of the teapot */
	//original was
	//glTranslated(0.25, 0.42, 0.35);
	glTranslated(0.6, 0.54, 0.5); //placing the ball on the teapot
	glutSolidSphere(0.1, 15, 15);// draw the sphere
	glPopMatrix() ;
	glPushMatrix();
	glTranslated(0.4, 0, 0.4);
	table(0.6, 0.02, 0.02, 0.3);	// draw the table
	glPopMatrix() ;
	wall(0.02);						//wall #1: in xz-plane
	glPushMatrix();
	glRotated(90.0, 0.0, 0.0, 1.0);
	wall(0.02);						//wall #2: in yz-plane
	glPopMatrix() ;

	glPushMatrix();
	glRotated(-90.0,1.0, 0.0, 0.0);
	wall(0.02);						//wall #3: in xy-plane
	glPopMatrix();
	glFlush();
}

void baseWine ( void )
{
		cvs.pushCT();

		
	for ( int h = 0; h < 360; h+=5)
	{
		
		glRotated( 5, 0, 1.0, 0.0 ); //rotated 45 at the z-axis
		//wall ( .02 );
	//} // interesting rotation
	
	
		cvs.pushCT();
				
		for ( int t = 0; t < 5; t++)
		{
				glTranslated ( .1, -.05, -.05 ); // x-axis
				//glutSolidTeapot( .2 );						
				glutSolidSphere (.02, 15, 15);
		}
		cvs.popCT();
	}//for loop brace for rotaton	
		
		cvs.pushCT();
		for ( int q = 0; q < 15; q++)
		{
				glTranslated ( 0, .05, 0 ); // y-axis
				glutSolidSphere (.02, 15, 15);				
		}
		cvs.popCT();
		
/*
		cvs.pushCT();
		for ( int w = 0; w < 5; w++)
		{
				glTranslated ( 0, 0, .1 ); // z-axis
				glutSolidSphere (.02, 15, 15);				
		}
		cvs.popCT();
*/

	cvs.popCT();

	
}

void practice3D(void)
{
/*
	cvs.pushCT();

	glBegin ( GL_POINT );

		glNormal3f ( 10.0, 10.0 , 50);
		
	glEnd();

		glTranslated ( .75, .5, .05 );
		glutWireSphere( .2, 10, 5 );

	cvs.popCT();
*/
		

/*
	cvs.pushCT();

		glTranslated ( 0, 1, 0);
		wall (.02 ); // Top
	
	cvs.popCT();

	cvs.pushCT();

		glRotated ( 90, 0, 0, 1 );
		wall ( 0.02 );  // Left side

	cvs.popCT();

	cvs.pushCT();

		glRotated ( -90, 1, 0, 0 );
		wall ( 0.02 );  // Right Side

	cvs.popCT();
*/

	cvs.pushCT();
	
	for ( int h = 0; h < 360; h+=5)
	{
		glRotated( 5, 0, 1.0, 0.0 ); //rotated 45 at the z-axis
		//wall ( .02 );
	//}
	
	
		cvs.pushCT();
				
		for ( int t = 0; t < 5; t++)
		{
				glTranslated ( .1, 0, 0 ); // x-axis
				//glutSolidTeapot( .2 );						
				glutSolidSphere (.02, 15, 15);
		}
		cvs.popCT();
	}//For loop rotation
		
		cvs.pushCT();
		for ( int q = 0; q < 10; q++)
		{
				glTranslated ( 0, .1, 0 ); // y-axis
				glutSolidSphere (.02, 15, 15);				
		}
		cvs.popCT();
/*
		cvs.pushCT();
		for ( int w = 0; w < 5; w++)
		{
				glTranslated ( 0, 0, .1 ); // z-axis
				glutSolidSphere (.02, 15, 15);				
		}
		cvs.popCT();
*/
	cvs.popCT();

	
	

	glPushMatrix();
	/*
	glRotated(90.0, 0.0, 0.0, 1.0);
	wall(0.02);						//wall #2: in yz-plane
	glPopMatrix();
	*/

	
	/*
	glPushMatrix();
	
	for ( int j = 0 ; j < 360 ; j += 10 )
	{
		glRotated( j, 0.0, 0.0, 1.0);		
		wall(.02 );
	}
	*/

		//glutWireSphere( .5, 15.0, 15.0 );
		//glutWireTeapot( .50 );


	glPopMatrix();

	cvs.pushCT();
		glTranslated ( 0, .75, 0 );
		glRotated ( -45, 1, 0, 0 );
		for ( int o = 0; o < 180; o+=5 )
		{
			glRotated ( o, 0, 0, 1 );			
			wall (.02 );
		}
	cvs.popCT();
	

	glFlush();
}

void buildMesh()
{
	cvs.pushCT();

	//glutSolidSphere( .05, 15, 15 );
	//wall ( .02 );

	cvs.popCT();
	
	//Mesh house;
	//house.readMesh( "house.dat" );
	//house.drawOpenGL();

	//Mesh tetra;
	//tetra.readMesh( "tetrahedron.dat" );
	//cvs.rotate2D ( 45 );
	//tetra.drawOpenGL();
	//wall (.02);

	Mesh wine;
	wine.readMesh ( "WineProfile.dat" );
	
	
	cvs.pushCT();

	try
	{
		
		
	glBegin ( GL_POLYGON );
	for ( int w = 0; w < 180; w += 5 )
	{
		glVertex3f ( 100, 0, w );
		glVertex3f ( 100, 10, w );
		glVertex3f ( 20, 12, w);
	    glVertex3f ( 20, 20, w );
		glVertex3f ( 10, 20, w );
		glVertex3f ( 10, 100, w );
		glVertex3f ( 120, 200, w );
		glVertex3f ( 100, 200, w );
		glVertex3f ( 0, 100, w );
	}	

	}
	catch (...)
	{
	}

	cvs.popCT();

	glEnd();

	wine.drawOpenGL();

	glFlush();

}

//<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	//set properties of the surface material
	GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f}; // gray
	GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	// set the light source properties
	GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	// set the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 1.0; // half-height of the window
	glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0.1, 100.0); //original
	//glOrtho ( -3.2, 3.2, -2.4, 2.4, 1, 50 );
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	//gluLookAt(2.3, 1.3, 2.0, 0.0, 0.25, 0.0, 0.0, 1.0, 0.0); //original
	gluLookAt( 2.3, 1.3, 2, 0, .25, 0, 0, 1, 0 );
	
// start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
	glPushMatrix();	


	practice3D();

	
	cvs.pushCT();
	cvs.translate2D( .25, -.02 );
	//baseWine();
	cvs.popCT();
/*
	glTranslated ( .25, -.25, -.60);
	for (int i =0; i < 360; i += 30 )
	{
		cvs.pushCT();
		glRotated ( i, 0, 0, 1 );
		buildMesh();
		cvs.popCT();
	}
*/
	//buildMesh();
	
}

void myInit ( void )
{
   glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );      // set white background color
   //glClearColor(0.1f,0.1f,0.1f,0.0f);	// background is light gray
   glColor3f ( 0.0f, 0.0f, 0.0f );         // set the drawing color
   glPointSize ( 4.0 );               // a 'dot' is 10 by 10 pixels
   //glMatrixMode ( GL_PROJECTION ); // with shading
   glMatrixMode ( GL_MODELVIEW ); // no shading
   glLoadIdentity ();
   gluOrtho2D ( 0.0, 640.0, 0.0, 480.0 );

};

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	//glutInitWindowSize(640,480);
	//glutInitWindowPosition(100, 100);
	//glutCreateWindow("shaded example - 3D scene");

	glutDisplayFunc(displaySolid);

	//myInit(); // helps draw points?
	//glutDisplayFunc( myDisplay );
	

	
	
	glEnable(GL_LIGHTING);				// enable the light source
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);			// for removal of hidden surfaces
	glEnable(GL_NORMALIZE);				// normalize vectors for proper shading
	//glClearColor(0.1f,0.1f,0.1f,0.0f);	// background is light gray
	glClearColor(1.0f,1.0f,1.0f,1.0f);	// background is white 
	glViewport(0, 0, 640, 480);

	glutMouseFunc ( myMouse );
	glutMainLoop();
}


