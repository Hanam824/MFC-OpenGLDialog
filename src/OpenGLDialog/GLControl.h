#pragma once

#include <GL\gl.h>
#include <GL\glu.h>

#include "GLDevice.h"

class CGLCtrlView : public CWnd
{
public:
	CGLCtrlView();
	virtual ~CGLCtrlView();

	// Implement
public:
	void Create(CRect rect, CWnd* parent);


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	void InitGL();
	void DrawGLScene();

private:
	CGLDevice glDevice;
	std::unique_ptr<CGLDevice> m_pDevice = nullptr;

	CClientDC* pDC = nullptr;
	float rotation = 0.0f;
};