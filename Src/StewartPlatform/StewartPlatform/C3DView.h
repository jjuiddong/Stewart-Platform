#pragma once


class C3DView : public CView
{
public:
	C3DView();
	virtual ~C3DView();

	bool Init();
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void Update(const float deltaSeconds);
	virtual void Render();


protected:
	bool m_isInitDx = false;
	bool m_isFixedFrame = true; // 고정 프레임모드시 true, (100 frame)
	bool m_isRenderCube = false;

	graphic::cCamera m_camera;
	graphic::cLight m_light;
	graphic::cRenderer m_renderer;
	graphic::cCircle m_base;
	graphic::cCircle m_mobile;
	graphic::cLine m_actuator[6];

	float m_baseRadius;
	float m_mobileRadius;
	float m_mobileHeight;

	bool m_isUp = true;
	float m_roll;
	float m_pitch;
	float m_yaw;
	float m_heave;
	float m_surge;
	float m_sway;

	float m_incT;
	bool m_RButtonDown = false;
	bool m_MButtonDown = false;
	CPoint m_curPos;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


