#include "pch.h"
#include "GLDevice.h"


CGLDevice::CGLDevice()
{
	renderContext = NULL;
	deviceContext = NULL;
}

CGLDevice::CGLDevice(const HDC& deviceContext)
{
	
}

CGLDevice::CGLDevice(const HWND& window)
{
	create(window);
}

CGLDevice::~CGLDevice()
{
	destroy();
}

void CGLDevice::destroy()
{
	if (renderContext != NULL)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(renderContext);
	}
}

bool CGLDevice::create(const HDC& deviceContext)
{
	if (!deviceContext)
	{
		return false;
	}

	if (!setDCPixelFormat(deviceContext))
	{
		return false;
	}

	renderContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, renderContext);

	CGLDevice::deviceContext = deviceContext;

	return true;
}

bool CGLDevice::create(const HWND& window)
{
	HDC deviceContext = ::GetDC(window);

	if (!create(deviceContext))
	{
		::ReleaseDC(window, deviceContext);

		return false;
	}

	::ReleaseDC(window, deviceContext);

	return true;
}

void CGLDevice::makeCurrent(bool disableOther)
{
	if (renderContext != NULL)
	{
		//should all other device contexts
		//be disabled then?
		if (disableOther)
			wglMakeCurrent(NULL, NULL);

		wglMakeCurrent(deviceContext, renderContext);
	}
}

bool CGLDevice::setDCPixelFormat(const HDC& deviceContext)
{
	PIXELFORMATDESCRIPTOR pixelFormatDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_SWAP_EXCHANGE |
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		24,								// Want 24bit color 
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		32,								// Size of depth buffer
		1,								// Not used to select mode
		0,								// Not used to select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to select mode
		0,0,0							// Not used to select mode
	};

	int pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);

	if (!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
		return false;

	return true;
}