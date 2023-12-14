#include "pch.h"
#include "GLDevice.h"


CGLDevice::CGLDevice()
{
	renderContext = NULL;
	deviceContext = NULL;
}

CGLDevice::CGLDevice(const HDC& deviceContext, int stencil)
{
	
}

CGLDevice::CGLDevice(const HWND& window, int stencil)
{
	create(window, stencil);
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

bool CGLDevice::create(const HDC& deviceContext, int stencil)
{
	if (!deviceContext)
	{
		return false;
	}

	if (!setDCPixelFormat(deviceContext, stencil))
	{
		return false;
	}

	renderContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, renderContext);

	CGLDevice::deviceContext = deviceContext;

	return true;
}

bool CGLDevice::create(const HWND& window, int stencil)
{
	HDC deviceContext = ::GetDC(window);

	if (!create(deviceContext, stencil))
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

bool CGLDevice::setDCPixelFormat(const HDC& deviceContext, int stencil)
{
	DEVMODE resolution;

	//PIXELFORMAT->BPP = DESKTOP->BPP
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &resolution);

	static PIXELFORMATDESCRIPTOR pixelFormatDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		resolution.dmBitsPerPel,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		stencil,
		0,
		0,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);

	if (!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
		return false;

	return true;
}