#ifndef __GLUT64__
#define __GLUT64__

#include "../include/nus64.h"

// Really this API should be called "Inspired by FreeGLUT"
// https://github.com/dcnieho/FreeGLUT
// https://www.opengl.org/resources/libraries/glut/glut-3.spec.pdf
// No Sub Windows, always full screen, no cursor, no icon, no title
// No Overlays at all
// No Menus
// No Spaceball
// No Dials
// No Tablet
// Colormap ??? Probably don't need
// glut Game Mode Memory Map
//	Double Buffered, Z Buffered
// 320x240 @ 16 = 153,600 bytes
// 320x240 @ 32 = 307,200 bytes
// 640x480 @ 16 = 614,400 bytes
// 640x480 @ 32 = 1,228,800 bytes
// Z Buffer is always 16 bit version of resolution
// 4 MB of RAM limits resolution to 320x240 (16/32)
// 8 MB of RAM provides the option of 320x240 (16/32) OR 640x480 (16/32)

// glut uses the nus_(api's) directly, programmer doesn't have to assign 
//		handlers, etc. Any use of nus_ api's directly with glut, may 
//		cause undesired behavior. Exception: Audio

typedef enum {
	GLUT_ELAPSED_TIME
} glutenable_t;

typedef enum {
	GLUT_RGBA,
	GLUT_DOUBLE,
	GLUT_DEPTH
} glutdisplay_t;

typedef void (*void_callback_void)(void);
typedef void (*void_callback_int)(void);
typedef void (*keyboard_callback_void)( unsigned char, int, int );
typedef void (*special_callback)( int, int, int );
typedef void (*mouse_callback4i)( int, int, int, int );
typedef void (*controller_callback) (joy_controller_state_t controllerdata);

// TODO: GLUT Implementation Sequence

void 	glutBitmapCharacter( void* font, int character );
int 	glutBitmapLength( void* font, const unsigned char* string );
int 	glutBitmapWidth( void* font, int character );

void 	glutController1Func( controller_callback callback);
void 	glutController2Func( controller_callback callback);
void 	glutController3Func( controller_callback callback);
void 	glutController4Func( controller_callback callback);
void 	glutCopyColormap( int window );
int 	glutCreateWindow( const char* title );
void 	glutDestroyWindow( int window );
int 	glutDeviceGet( GLenum query );
void 	glutDisplayFunc( void (* callback)( void ) );

int 	glutEnterGameMode( void );
int 	glutExtensionSupported( const char* extension );

void 	glutForceJoystickFunc( void );

int 	glutGameModeGet( GLenum query );
void 	glutGameModeString( const char* string );
int 	glutGet( glutenable_t query );
GLfloat glutGetColor( int color, int component );
int 	glutGetModifiers( void );

void 	glutIdleFunc( void (* callback)( void ) );
void 	glutIgnoreKeyRepeat( int ignore );
void 	glutInit( int* pargc, char** argv );
// glutInitWindowPosition N/A
// glutInitWindowSize N/A
void 	glutInitDisplayMode( glutdisplay_t displayMode );
// glutInitDisplayString - Not Implementated: Parsing nightmare
// void glutInitDisplayString( const char* displayMode );

void 	glutKeyboardFunc( void (* callback)( unsigned char, int, int ) );
void 	glutKeyboardUpFunc( keyboard_callback_void callback );

void 	glutLeaveGameMode( void );
void 	glutLeaveMainLoop( void );

void 	glutMainLoop( void );
void 	glutMainLoopEvent(void);
void 	glutMouseFunc( mouse_callback4i callback );

void 	glutPostRedisplay( void );

void 	glutReportErrors( void );

void 	glutSetColor( int color, GLfloat red, GLfloat green, GLfloat blue );
void 	glutSetKeyRepeat( int repeatMode );
void 	glutSetupVideoResizing( void );
void 	glutSolidCone( double base, double height, GLint slices, GLint stacks );
void 	glutSolidCube( double size );
void 	glutSolidCylinder( double radius, double height, GLint slices, GLint stacks);
void 	glutSolidDodecahedron( void );
void 	glutSolidIcosahedron( void );
void 	glutSolidOctahedron( void );
void 	glutSolidRhombicDodecahedron( void );
void 	glutSolidSierpinskiSponge ( int num_levels, double offset[3], double scale );
void 	glutSolidSphere( double radius, GLint slices, GLint stacks );
void 	glutSolidTeacup( double size );
void 	glutSolidTeapot( double size );
void 	glutSolidTeaspoon( double size );
void 	glutSolidTetrahedron( void );
void 	glutSolidTorus( double innerRadius, double outerRadius, GLint sides, GLint rings );
void 	glutSpecialFunc( void (* callback)( int, int, int ) );
void 	glutSpecialUpFunc( special_callback callback );
void 	glutStopVideoResizing( void );
void 	glutStrokeCharacter( void* font, int character );
int 	glutStrokeLength( void* font, const unsigned char* string );
int 	glutStrokeWidth( void* font, int character );
void 	glutSwapBuffers( void );

void 	glutTimerFunc( unsigned int time, void_callback_int callback, int value );

void 	glutVideoResize( int x, int y, int width, int height );
int 	glutVideoResizeGet( GLenum query );
void 	glutVideoPan( int x, int y, int width, int height );

void 	glutWireCone( double base, double height, GLint slices, GLint stacks );
void 	glutWireCube( double size );
void 	glutWireCylinder( double radius, double height, GLint slices, GLint stacks);
void 	glutWireDodecahedron( void );
void 	glutWireIcosahedron( void );
void 	glutWireOctahedron( void );
void 	glutWireRhombicDodecahedron( void );
void 	glutWireSierpinskiSponge ( int num_levels, double offset[3], double scale );
void 	glutWireSphere( double radius, GLint slices, GLint stacks );
void 	glutWireTeacup( double size );
void 	glutWireTeapot( double size );
void 	glutWireTeaspoon( double size );
void 	glutWireTetrahedron( void );
void 	glutWireTorus( double innerRadius, double outerRadius, GLint sides, GLint rings );

// void glutInitErrorFunc( void (* callback)( const char *fmt, va_list ap ) );
// void glutInitWarningFunc( void (* callback)( const char *fmt, va_list ap ) );

#endif //__GLUT64__