extern "C"
{
	#include <psp2/kernel/modulemgr.h>
	#include <psp2/kernel/processmgr.h>
	#include <psp2/kernel/clib.h>
	#include <PVR_PSP2/EGL/eglplatform.h>
	#include <PVR_PSP2/EGL/egl.h>
	#include <PVR_PSP2/gpu_es4/psp2_pvr_hint.h>

	#include <PVR_PSP2/GLES2/gl2.h>
	#include <PVR_PSP2/GLES2/gl2ext.h>

	#include <psp2/ctrl.h>
}

#include <cmath>
#include <fstream>
#include <string>
#include <cstring>


#define M_PI 3.14159265358979323846 /* pi */

using namespace std;

//SCE
int _newlib_heap_size_user   = 16 * 1024 * 1024;
unsigned int sceLibcHeapSize = 3 * 1024 * 1024;

//EGL
EGLDisplay Display;
EGLConfig Config;
EGLSurface Surface;
EGLContext Context;
EGLint NumConfigs, MajorVersion, MinorVersion;
EGLint ConfigAttr[] =
{
	EGL_BUFFER_SIZE, EGL_DONT_CARE,
	EGL_DEPTH_SIZE, 16,
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_ALPHA_SIZE, 8,
	EGL_STENCIL_SIZE, 8,
	EGL_SURFACE_TYPE, 5,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_NONE
};
EGLint ContextAttributeList[] = 
{
	EGL_CONTEXT_CLIENT_VERSION, 2,
	EGL_NONE
};

//PIB cube egl stuff

static GLuint program;
static GLuint vertexID;
static GLuint colorID;
 
static GLuint mvpLoc;
static GLuint positionLoc;
static GLuint colorLoc;

typedef struct{
GLfloat mat[4][4];
}glMatrix;
 
static glMatrix *projectionMat;
static glMatrix *modelviewMat;
static glMatrix *mvpMat;

static EGLint surface_width, surface_height;

static const GLfloat vertices[] =
{
    /* front */
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
 
    /* right */
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
 
    /* back */
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
 
    /* left */
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
 
    /* top */
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
 
    /* bottom */
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f
};

static const GLfloat colors[] =
{
    /* front */
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
 
    /* right */
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
 
    /* back */
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
 
    /* left */
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
    0.0625f,0.57421875f,0.92578125f,1.0f,
 
    /* top */
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
    0.29296875f,0.66796875f,0.92578125f,1.0f,
 
    /* bottom */
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f,
    0.52734375f,0.76171875f,0.92578125f,1.0f
};

/* Define our CG shader here. They will be compiled at runtime */
const GLchar vShaderStr[] =
// Vertex Shader
        "precision mediump float;\n"
        "uniform mat4 u_mvpMat;\n"
        "attribute vec4 a_position;\n"
        "attribute vec4 a_color;\n"
        "varying vec4 v_color;\n"
        "void main()\n"
        "{\n"
        "gl_Position = u_mvpMat * a_position;\n"
        "v_color = a_color;\n"
        "}\n";

const GLchar fShaderStr[] = 
// Fragment Shader
        "varying lowp vec4 v_color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = v_color;\n"
        "}\n";

void multMatrix(glMatrix *result, glMatrix *srcA, glMatrix *srcB)
{
    glMatrix    tmp;
    int         i;
 
    for (i=0; i<4; i++)
    {
        tmp.mat[i][0] = (srcA->mat[i][0] * srcB->mat[0][0]) +
                        (srcA->mat[i][1] * srcB->mat[1][0]) +
                        (srcA->mat[i][2] * srcB->mat[2][0]) +
                        (srcA->mat[i][3] * srcB->mat[3][0]) ;
 
        tmp.mat[i][1] = (srcA->mat[i][0] * srcB->mat[0][1]) +
                        (srcA->mat[i][1] * srcB->mat[1][1]) +
                        (srcA->mat[i][2] * srcB->mat[2][1]) +
                        (srcA->mat[i][3] * srcB->mat[3][1]) ;
 
        tmp.mat[i][2] = (srcA->mat[i][0] * srcB->mat[0][2]) +
                        (srcA->mat[i][1] * srcB->mat[1][2]) +
                        (srcA->mat[i][2] * srcB->mat[2][2]) +
                        (srcA->mat[i][3] * srcB->mat[3][2]) ;
 
        tmp.mat[i][3] = (srcA->mat[i][0] * srcB->mat[0][3]) +
                        (srcA->mat[i][1] * srcB->mat[1][3]) +
                        (srcA->mat[i][2] * srcB->mat[2][3]) +
                        (srcA->mat[i][3] * srcB->mat[3][3]) ;
    }
    memcpy(result, &tmp, sizeof(glMatrix));
}

void loadIdentity(glMatrix *result)
{
    memset(result, 0x0, sizeof(glMatrix));
    result->mat[0][0] = 1.0f;
    result->mat[1][1] = 1.0f;
    result->mat[2][2] = 1.0f;
    result->mat[3][3] = 1.0f;
}
 
void scaleMatrix(glMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz)
{
    result->mat[0][0] *= sx;
    result->mat[0][1] *= sx;
    result->mat[0][2] *= sx;
    result->mat[0][3] *= sx;
 
    result->mat[1][0] *= sy;
    result->mat[1][1] *= sy;
    result->mat[1][2] *= sy;
    result->mat[1][3] *= sy;
 
    result->mat[2][0] *= sz;
    result->mat[2][1] *= sz;
    result->mat[2][2] *= sz;
    result->mat[2][3] *= sz;
}

void translationMatrix(glMatrix *result, float x, float y, float z)  // Currently Unused
{
	glMatrix m1;

    loadIdentity(&m1);

	m1.mat[0][3] = x;
	m1.mat[1][3] = y;
	m1.mat[2][3] = z;

	multMatrix(result, &m1, result);
}

void rotationMatrix(glMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat sinAngle, cosAngle;
    GLfloat mag = sqrtf(x * x + y * y + z * z);
 
    sinAngle = sin ( angle * M_PI / 180.0f );
    cosAngle = cos ( angle * M_PI / 180.0f );
    if ( mag > 0.0f )
    {
        GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
        GLfloat oneMinusCos;
        glMatrix rotMat;
 
        x /= mag;
        y /= mag;
        z /= mag;
 
        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;
 
        rotMat.mat[0][0] = (oneMinusCos * xx) + cosAngle;
        rotMat.mat[0][1] = (oneMinusCos * xy) - zs;
        rotMat.mat[0][2] = (oneMinusCos * zx) + ys;
        rotMat.mat[0][3] = 0.0F;
 
        rotMat.mat[1][0] = (oneMinusCos * xy) + zs;
        rotMat.mat[1][1] = (oneMinusCos * yy) + cosAngle;
        rotMat.mat[1][2] = (oneMinusCos * yz) - xs;
        rotMat.mat[1][3] = 0.0F;
 
        rotMat.mat[2][0] = (oneMinusCos * zx) - ys;
        rotMat.mat[2][1] = (oneMinusCos * yz) + xs;
        rotMat.mat[2][2] = (oneMinusCos * zz) + cosAngle;
        rotMat.mat[2][3] = 0.0F;
 
        rotMat.mat[3][0] = 0.0F;
        rotMat.mat[3][1] = 0.0F;
        rotMat.mat[3][2] = 0.0F;
        rotMat.mat[3][3] = 1.0F;
 
        multMatrix( result, &rotMat, result );
    }
}

void frustumMatrix(glMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    glMatrix    frust;
 
    if ( (nearZ <= 0.0f) || (farZ <= 0.0f) ||
            (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f) )
            return;
 
    frust.mat[0][0] = 2.0f * nearZ / deltaX;
    frust.mat[0][1] = frust.mat[0][2] = frust.mat[0][3] = 0.0f;
 
    frust.mat[1][1] = 2.0f * nearZ / deltaY;
    frust.mat[1][0] = frust.mat[1][2] = frust.mat[1][3] = 0.0f;
 
    frust.mat[2][0] = (right + left) / deltaX;
    frust.mat[2][1] = (top + bottom) / deltaY;
    frust.mat[2][2] = -(nearZ + farZ) / deltaZ;
    frust.mat[2][3] = -1.0f;
 
    frust.mat[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.mat[3][0] = frust.mat[3][1] = frust.mat[3][3] = 0.0f;
 
    multMatrix(result, &frust, result);
}

GLuint LoadShader(const GLchar *shaderSrc, GLenum type, GLint *size)
{
    GLuint shader;
    GLint compiled;

    sceClibPrintf("Creating Shader...\n");

    shader = glCreateShader(type);

    if(shader == 0)
    {
        sceClibPrintf("Failed to Create Shader\n");
        return 0;
    }

    glShaderSource(shader, 1, &shaderSrc, size);

    sceClibPrintf("Compiling Shader: %s...\n", shaderSrc);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1)
        {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);  // Shader Logs through GLES functions work :D
            sceClibPrintf("Error compiling shader:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    sceClibPrintf("Shader Compiled!\n");
    return shader;
}

void render(void){
    glViewport(0, 0, surface_width, surface_height);
 
    /* Typical render pass */
    glClear(GL_COLOR_BUFFER_BIT);
 
    glUseProgram(program);
 
    /* Enable and bind the vertex information */
    glEnableVertexAttribArray(positionLoc);
    glBindBuffer(GL_ARRAY_BUFFER, vertexID);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), 0);
 
    /* Enable and bind the color information */
    glEnableVertexAttribArray(colorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, colorID);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE,
                          4 * sizeof(GLfloat), 0);
 
    rotationMatrix( modelviewMat, 2.0f, -0.8f, -1.0f, -0.3f);
    multMatrix( mvpMat, modelviewMat, projectionMat);
    glUniformMatrix4fv(mvpLoc, 1, false, &mvpMat->mat[0][0]);

    /* Same draw call as in GLES1 */
    glDrawArrays(GL_TRIANGLES, 0 , 36);
 
    /* Disable attribute arrays */
    glDisableVertexAttribArray(positionLoc);
    glDisableVertexAttribArray(colorLoc);
 
    eglSwapBuffers(Display, Surface);
}

/* How we load shaders */
int initShaders(void)
{
    GLint status;

    GLuint vshader = LoadShader(vShaderStr, GL_VERTEX_SHADER, NULL);
    GLuint fshader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER, NULL);
    program = glCreateProgram();
    if (program)
    {
        glAttachShader(program, vshader);
        glAttachShader(program, fshader);
        glLinkProgram(program);
    
        glGetProgramiv(program, GL_LINK_STATUS, &status);
	sceClibPrintf("Status: %d\n", status);
        if (status == GL_FALSE)    {
            GLchar log[256];
            glGetProgramInfoLog(fshader, 256, NULL, log);
    
            sceClibPrintf("Failed to link shader program: %s\n", log);
    
            glDeleteProgram(program);
            program = 0;
    
            return -1;
        }
    } else {
        sceClibPrintf("Failed to create a shader program\n");
    
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        return -1;
    }
 
    /* Shaders are now in the programs */
    glDeleteShader(fshader);
    glDeleteShader(vshader);
    return 0;
}

/* This handles creating a view matrix for the Vita */
int initViewMatrix(void)
{
    mvpLoc = glGetUniformLocation(program, "u_mvpMat");
    positionLoc = glGetAttribLocation(program, "a_position");
    colorLoc = glGetAttribLocation(program, "a_color");

    /* Generate vertex and color buffers and fill with data */
    glGenBuffers(1, &vertexID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                GL_STATIC_DRAW);
    
    glGenBuffers(1, &colorID);
    glBindBuffer(GL_ARRAY_BUFFER, colorID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors,
                GL_STATIC_DRAW);

    projectionMat = (glMatrix*)malloc( sizeof(glMatrix) );
    loadIdentity( projectionMat );
    
    GLfloat aspect = (float)surface_width/(float)surface_height;
    GLfloat near = -1.0f;
    GLfloat far  = 1.0f;
    GLfloat yFOV  = 75.0f;
    GLfloat height = tanf( yFOV / 360.0f * M_PI ) * near;
    GLfloat width = height * aspect;
    
    
    frustumMatrix( projectionMat, -width, width, -height, height, near,
                far );
    
    if ( surface_width > surface_height ){
        scaleMatrix( projectionMat, (float)surface_height/(float)surface_width,
                    1.0f, 1.0f );
    } else {
        scaleMatrix( projectionMat, 1.0f,
                    (float)surface_width/(float)surface_height, 1.0f );
    }
    modelviewMat = (glMatrix*)malloc( sizeof(glMatrix) );
    loadIdentity( modelviewMat );
    mvpMat = (glMatrix*)malloc( sizeof(glMatrix) );
    return 0;
}

void ModuleInit()
{
	sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, NULL, 0, NULL, NULL);
	sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, NULL, 0, NULL, NULL);
	sceKernelLoadStartModule("app0:module/libgpu_es4_ext.suprx", 0, NULL, 0, NULL, NULL);
  	sceKernelLoadStartModule("app0:module/libIMGEGL.suprx", 0, NULL, 0, NULL, NULL);
	sceClibPrintf("Module init OK\n");
}

void PVR_PSP2Init()
{
	PVRSRV_PSP2_APPHINT hint;
  	PVRSRVInitializeAppHint(&hint);
  	PVRSRVCreateVirtualAppHint(&hint);
	sceClibPrintf("PVE_PSP2 init OK.\n");
}

void EGLInit()
{
	EGLBoolean Res;
	Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if(!Display)
	{
		sceClibPrintf("EGL display get failed.\n");
		return;
	}

	Res = eglInitialize(Display, &MajorVersion, &MinorVersion);
	if (Res == EGL_FALSE)
	{
		sceClibPrintf("EGL initialize failed.\n");
		return;
	}

	//PIB cube demo
	eglBindAPI(EGL_OPENGL_ES_API);

	Res = eglChooseConfig(Display, ConfigAttr, &Config, 1, &NumConfigs);
	if (Res == EGL_FALSE)
	{
		sceClibPrintf("EGL config initialize failed.\n");
		return;
	}

	Surface = eglCreateWindowSurface(Display, Config, (EGLNativeWindowType)0, nullptr);
	if(!Surface)
	{
		sceClibPrintf("EGL surface create failed.\n");
		return;
	}

	Context = eglCreateContext(Display, Config, EGL_NO_CONTEXT, ContextAttributeList);
	if(!Context)
	{
		sceClibPrintf("EGL content create failed.\n");
		return;
	}

	eglMakeCurrent(Display, Surface, Surface, Context);

	// PIB cube demo
	eglQuerySurface(Display, Surface, EGL_WIDTH, &surface_width);
	eglQuerySurface(Display, Surface, EGL_HEIGHT, &surface_height);
	sceClibPrintf("Surface Width: %d, Surface Height: %d\n", surface_width, surface_height);
	glClearDepthf(1.0f);
	glClearColor(0.0f,0.0f,0.0f,1.0f); // You can change the clear color to whatever
	 
	glEnable(GL_CULL_FACE);

	sceClibPrintf("EGL init OK.\n");
}

void EGLEnd()
{
	eglDestroySurface(Display, Surface);
  	eglDestroyContext(Display, Context);
  	eglTerminate(Display);
	sceClibPrintf("EGL terminated.\n");
}

void SCEInit()
{
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	sceClibPrintf("SCE init OK\n");
}

int main()
{
	ModuleInit();
	PVR_PSP2Init();
	EGLInit();

	SCEInit();
	sceClibPrintf("All init OK.\n");

	initShaders();
	initViewMatrix();
	
	while(1)
	{
	    render();
	}

	EGLEnd();

	sceKernelExitProcess(0);
	return 0;
}