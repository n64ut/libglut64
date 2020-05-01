#include "../include/nus64.h"
#include "../include/assert64.h"
FILENUM(5)
#include "glut64.h"
#include "glut64_internal.h"
#include "../include/joy64.h"
#include "../include/joy_keyboard64.h"
#include "../include/ogl64.h"

#define CONTROLLER_COUNT 4
unsigned int controllers[CONTROLLER_COUNT];

void * audio_uc = NULL;
void * audio_data = NULL;

void __glut_si_handler()
{
	joyRecvResponse(joy_buffer_rx_ram_addr);	
	// Loop through controller count (1 - 4)
	int max_controllers =  glutState.ControllerCount;
	for (int idx = 0; idx < max_controllers; idx++)
	{
		// if no Joybus Port Error
		if (joy_console.port[idx].device.dev_type.id == N64_CONTROLLER ||
			joy_console.port[idx].device.dev_type.id == N64_DENSHA )
		{			
			if (controllerFunc_callback[idx])
				controllerFunc_callback[idx](joy_console.port[idx].data.controller);
		}
		else if (joy_console.port[idx].device.dev_type.id == N64_MOUSE)
		{			
			if (mouseFunc_callback)
			{
				mouseFunc_callback( 
					joy_console.port[idx].data.mouse.buttons, 
					0, // TODO: si_port[idx].data.controller.held/released
					joy_console.port[idx].data.mouse.movex, 
					joy_console.port[idx].data.mouse.movey );
			}
		}
		else if (joy_console.port[idx].device.dev_type.id == N64_KEYBOARD)
		{
			if (!KeyboardFunc_callback)
				continue;
			// the Keyboard, callback only supports 1 key at a time
			// N64 Keyboard supports 3 characters / query			
			for (int keyIdx = 0; keyIdx <3; keyIdx++)
			{
				// Decode the key to glut keycode data				
				KeyboardFunc_callback( 0, 0, 0 );
				if (KeyboardUpFunc_callback)
					KeyboardUpFunc_callback( 0, 0, 0 );

				else if (specialFunc_callback)
					specialFunc_callback( 0, 0, 0 );
				else if (specialUpFunc_callback)
					specialUpFunc_callback( 0, 0, 0 );
			}
		}
	}
}

void __glut_vi_handler()
{
	nusDmaImem(audio_uc, 0, 4 * 1024);
	joyPreparePort();
	nusDmaDmem(audio_data, 2 * 1024, 2 * 1024);
	nusSetFB(glutState.DisplayBuffer);
	nusRSPRun();
}

void __glut_timer_handler()
{
}

void __glut_rsp_handler()
{
}

void glutInit( int* pargc, char** argv )
{
	ASSERT(!pargc); // == NULL
	ASSERT(!argv); // == NULL
	nusInit();
	// Connect Exception Handlers to glut internal handlers	
	nusSetHandler(SYSCALL_INTERRUPT, nus_syscall_handler);
	// si_interrupt
	nusSetHandler(SI_INTERRUPT, __glut_si_handler);
	// vi_interrupt
	nusSetHandler(VI_INTERRUPT, __glut_vi_handler);
	// timer_interrupt
	nusSetHandler(TIMER_INTERRUPT, __glut_timer_handler);
	nusSetHandler(RSP_INTERRUPT, __glut_rsp_handler);
}

void glutInitDisplayMode( unsigned int displayMode )
{
	ASSERT(!displayMode); // == NULL
	// Only support what seems relevant and fail gracefully for everything else.
	// GLUT_INDEX
	// GLUT_RGB
	// GLUT_RGBA
	// GLUT_SINGLE
	// GLUT_DOUBLE 
	// GLUT_ACCUM
	// GLUT_ALPHA
	// GLUT_DEPTH
	// GLUT_STENCIL
	// GLUT_MULTISAMPLE
	// GLUT_LUMINANCE
	// GLUT_STEREO 
	
}

/* This is a parsing nightmare
void glutInitDisplayString( const char* displayMode )
{
	ASSERT(!displayMode); // == NULL
	// Parse displayMode to INT
	uint32_t mode = 0;
	glutInitDisplayMode(mode);
}
*/

void glutSwapBuffers()
{
	// Queue up a buffer swap for the next VI Interrupt
	glFlush();
}

void glutKeyboardFunc( keyboard_callback_void callback )
{
	KeyboardFunc_callback = callback;
}

// https://opensourceforu.com/2012/02/function-pointers-and-callbacks-in-c-an-odyssey/
void glutDisplayFunc( void_callback_void callback )
{
	displayFunc_callback = callback;
}

void glutTimerFunc( unsigned int time, void_callback_int callback, int value )
{
	// Real Implementation is more involved.
	// struct with time:value:callback
	// Array of the struct maybe limit to 5? 10 max.
	// When timer interrupt occurs, figure out which callbacks to trigger.
	ASSERT(time);
	ASSERT(value);
	timerFunc_callback = callback;
}

void glutSpecialFunc( special_callback callback)
{
	specialFunc_callback = callback;
}

void glutKeyboardUpFunc( keyboard_callback_void callback )
{
	KeyboardUpFunc_callback = callback;
}

void glutSpecialUpFunc( special_callback callback )
{
	specialUpFunc_callback = callback;
}

void glutMouseFunc( mouse_callback4i callback )
{
	mouseFunc_callback = callback;
}

void glutController1Func( controller_callback callback )
{
	controllerFunc_callback[0] = callback;
}

int glutCreateWindow( const char* title )
{
	ASSERT(title);
	return 0;
}
	
void glutLeaveMainLoop( void )
{
	glutState.ExecState = Init;
}

void glutMainLoopEvent(void)
{
	if (displayFunc_callback)
		displayFunc_callback();
	if (idleFunc_callback)
		idleFunc_callback();
}
 
void glutMainLoop(void)
{
	glutState.ExecState = Init;
	do
	{
		glutState.ExecState = Running;
		glutMainLoopEvent( );
	} while (glutState.ExecState != Stop);
	glutState.ExecState = Exit;
}
