#ifndef __OGL64INTERNAL__
#define __OGL64INTERNAL__

#include "../include/nus64.h"

#ifndef VERSION_MAJOR
#define VERSION_MAJOR 3
#endif

#ifndef VERSION_MINOR
#define VERSION_MINOR 0
#endif

#ifndef VERSION_PATCH
#define VERSION_PATCH 64
#endif

#define OP_Normal 1
#define OP_Vertex 2

#define OP_BUFFER_MAX_SIZE 512
#define MAX_DISPLAY_LISTS 1024

typedef union {
  int op;
  float f;
  int i;
  unsigned int ui;
  void *p;
} GLParam;

typedef struct GLParamBuffer {
  GLParam ops[OP_BUFFER_MAX_SIZE];
  struct GLParamBuffer *next;
} GLParamBuffer;

typedef struct GLList {
  GLParamBuffer *first_op_buffer;
  /* TODO: extensions for an hash table or a better allocating scheme */
} GLList;

typedef struct GLContext {
	uint64_t EnabledModes;
	uint64_t SupportedModes;
	int exec_flag,compile_flag,print_flag;	
} GLContext;

typedef enum {
	Stop = 0,
	Init,
	Running,
	Exit,
} ExecState_t;

typedef struct glutState {
	void * DisplayBuffer;
	ExecState_t ExecState;
	uint8_t ControllerCount;
	uint8_t exit;
} glutState_t;

glutState_t glutState;
void_callback_void displayFunc_callback;
keyboard_callback_void KeyboardFunc_callback;
keyboard_callback_void KeyboardUpFunc_callback;
void_callback_void idleFunc_callback;
void_callback_int timerFunc_callback;
special_callback specialFunc_callback;
special_callback specialUpFunc_callback;
mouse_callback4i mouseFunc_callback;
controller_callback controllerFunc_callback[4];

extern GLContext *gl_ctx;
void gl_add_op(GLParam *p);
GLContext *gl_get_context(void);

#endif // __OGL64INTERNAL__