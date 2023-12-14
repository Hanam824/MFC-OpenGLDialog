#pragma once

#include <windows.h>

class CGLDevice
{
public:
	CGLDevice();
	CGLDevice(const HDC& deviceContext);
	CGLDevice(const HWND& window);
	virtual ~CGLDevice();

	void destroy();

	bool create(const HDC& deviceContext);
	bool create(const HWND& window);
	
	void makeCurrent(bool disableOther = true);

protected:
	bool setDCPixelFormat(const HDC& deviceContext);

	HGLRC renderContext;
	HDC deviceContext;

private:

};