#pragma once

#include <windows.h>

class CGLDevice
{
public:
	CGLDevice();
	CGLDevice(const HDC& deviceContext, int stencil = 0);
	CGLDevice(const HWND& window, int stencil = 0);
	virtual ~CGLDevice();

	void destroy();

	bool create(const HDC& deviceContext, int  stencil = 0);
	bool create(const HWND& window, int stencil = 0);
	
	void makeCurrent(bool disableOther = true);

protected:
	bool setDCPixelFormat(const HDC& deviceContext, int stencil);

	HGLRC renderContext;
	HDC deviceContext;

private:

};