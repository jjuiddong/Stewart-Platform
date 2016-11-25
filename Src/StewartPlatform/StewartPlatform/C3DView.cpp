// C3DView.cpp : implementation file
//

#include "stdafx.h"
#include "StewartPlatform.h"
#include "C3DView.h"
#include "ControlDlg.h"

using namespace graphic;


C3DView::C3DView()
: m_roll(0)
, m_pitch(0)
, m_yaw(0)
, m_heave(0)
, m_surge(0)
, m_sway(0)
, m_incT(0)
{
}

C3DView::~C3DView()
{
}

BEGIN_MESSAGE_MAP(C3DView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


void C3DView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}


bool C3DView::Init()
{
	const int WINSIZE_X = 800;		//초기 윈도우 가로 크기
	const int WINSIZE_Y = 600;	//초기 윈도우 세로 크기

	// Create DirectX
	if (!m_renderer.CreateDirectX(GetSafeHwnd(), WINSIZE_X, WINSIZE_Y))
	{
		::AfxMessageBox(L"DirectX Initialize Error!!");
		return 0;
	}

	m_camera.Init(&m_renderer);
	m_camera.SetProjection(D3DX_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.0f);
	m_camera.SetCamera(Vector3(-13.f, 10.f, -13.f), Vector3(0, 3, 0), Vector3(0, 1, 0));

	m_renderer.GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	m_renderer.GetDevice()->LightEnable(0, true);

	// 주 광원 초기화.
	const Vector3 lightPos(300, 300, -300);
	m_light.SetPosition(lightPos);
	m_light.SetDirection(-lightPos.Normal());
	m_light.Bind(m_renderer, 0);
	m_light.Init(cLight::LIGHT_DIRECTIONAL,
		Vector4(0.7f, 0.7f, 0.7f, 0), Vector4(0.2f, 0.2f, 0.2f, 0));

	m_isInitDx = true;

	// Create Platform
	m_baseRadius = 5;
	m_mobileRadius = 4;
	m_mobileHeight = 4;

	// base
	m_base.Create(m_renderer, Vector3(0, 0, 0), m_baseRadius, 7);
	m_base.m_mtrl.InitBlue();
	{
		Matrix44 rm1, rm2;
		rm1.SetRotationX(ANGLE2RAD(-90));
		//rm2.SetRotationY(ANGLE2RAD(90/3));
		m_base.m_tm = rm1 * rm2;
	}

	// mobile
	m_mobile.Create(m_renderer, Vector3(0, 0, 0), m_mobileRadius, 4);
	m_mobile.m_mtrl.InitGreen();
	{
		Matrix44 rm, tm;
		rm.SetRotationX(ANGLE2RAD(-90));
		tm.SetTranslate(Vector3(0, m_mobileHeight, 0));
		m_mobile.m_tm = rm * tm;
	}

	// actuator
	Matrix44 brm; // base rotate
	brm.SetRotationY(ANGLE2RAD(360 / 6));
	Matrix44 mrm; // mobile rotate
	mrm.SetRotationY(ANGLE2RAD(360 / 3));

	Matrix44 baseR = brm , mobileR;
	for (int i = 0; i < 3; ++i)
	{
		Vector3 actuatorPos = Vector3(m_baseRadius, 0, 0) * baseR;
		Vector3 mPos1 = Vector3(m_mobileRadius, m_mobileHeight, 0) * mobileR;
		Vector3 mPos2 = Vector3(m_mobileRadius, m_mobileHeight, 0) * mobileR * mrm;
		m_actuator[i*2].SetLine(m_renderer, actuatorPos, mPos1, 0.1f);
		m_actuator[i*2+1].SetLine(m_renderer, actuatorPos, mPos2, 0.1f);
		m_actuator[i * 2].GetMaterial().InitWhite();
		m_actuator[i * 2 + 1].GetMaterial().InitWhite();

		baseR *= brm * brm;
		mobileR *= mrm;
	}

	return true;
}


void C3DView::Update(const float deltaSeconds)
{
	RET(!g_controlDlg);

	m_renderer.Update(deltaSeconds);

	const float deltaT = min(deltaSeconds, 0.1f);
	m_incT += deltaT;
	if (m_incT < 0.03f)
		return;

	const float limit = 0.5f;

	if (0 == g_controlDlg->m_controlMode) // auto mode
	{
		if (m_isUp && (m_roll < limit))
			m_roll += m_incT * 0.4f;
		else if (m_isUp && (m_roll >= limit))
			m_isUp = !m_isUp;
		else if (!m_isUp && (m_roll > -limit))
			m_roll -= m_incT * 0.4f;
		else if (!m_isUp && (m_roll <= -limit))
			m_isUp = !m_isUp;

		if (m_isUp && (m_pitch < limit))
			m_pitch += m_incT * 0.4f;
		else if (m_isUp && (m_pitch >= limit))
			m_isUp = !m_isUp;
		else if (!m_isUp && (m_pitch > -limit))
			m_pitch -= m_incT * 0.4f;
		else if (!m_isUp && (m_pitch <= -limit))
			m_isUp = !m_isUp;

		if (m_isUp && (m_yaw < limit))
			m_yaw += m_incT * 0.4f;
		else if (m_isUp && (m_yaw >= limit))
			m_isUp = !m_isUp;
		else if (!m_isUp && (m_yaw > -limit))
			m_yaw -= m_incT * 0.4f;
		else if (!m_isUp && (m_yaw <= -limit))
			m_isUp = !m_isUp;

		if (m_isUp && (m_heave < limit))
			m_heave += m_incT * 0.4f;
		else if (m_isUp && (m_heave >= limit))
			m_isUp = !m_isUp;
		else if (!m_isUp && (m_heave > -limit))
			m_heave -= m_incT * 0.4f;
		else if (!m_isUp && (m_heave <= -limit))
			m_isUp = !m_isUp;

		if (m_isUp && (m_surge < limit))
			m_surge += m_incT * 0.4f;
		else if (m_isUp && (m_surge >= limit))
			m_isUp = !m_isUp;
		else if (!m_isUp && (m_surge > -limit))
			m_surge -= m_incT * 0.4f;
		else if (!m_isUp && (m_surge <= -limit))
			m_isUp = !m_isUp;

		if (m_isUp && (m_sway < limit))
			m_sway += m_incT * 0.4f;
		else if (m_isUp && (m_sway >= limit))
			m_isUp = !m_isUp;
		else if (!m_isUp && (m_sway > -limit))
			m_sway -= m_incT * 0.4f;
		else if (!m_isUp && (m_sway <= -limit))
			m_isUp = !m_isUp;

		g_controlDlg->m_editRoll = m_roll;
		g_controlDlg->m_editPitch = m_pitch;
		g_controlDlg->m_editYaw = m_yaw;
		g_controlDlg->m_editHeave = m_heave;
		g_controlDlg->m_editSurge = m_surge;
		g_controlDlg->m_editSway = m_sway;

		g_controlDlg->m_sliderRoll.SetPos(500 + (int)(m_roll / limit * 500.f));
		g_controlDlg->m_sliderPitch.SetPos(500 + (int)(m_pitch / limit * 500.f));
		g_controlDlg->m_sliderYaw.SetPos(500 + (int)(m_yaw / limit * 500.f));
		g_controlDlg->m_sliderHeave.SetPos(500 + (int)(m_heave / limit * 500.f));
		g_controlDlg->m_sliderSurge.SetPos(500 + (int)(m_surge / limit * 500.f));
		g_controlDlg->m_sliderSway.SetPos(500 + (int)(m_sway / limit * 500.f));
		g_controlDlg->UpdateData(FALSE);

	}
	else if (1 == g_controlDlg->m_controlMode) // manual mode
	{
		m_roll = (g_controlDlg->m_sliderRoll.GetPos() - 500) / 500.f * limit;
		m_pitch = (g_controlDlg->m_sliderPitch.GetPos() - 500) / 500.f * limit;
		m_yaw = (g_controlDlg->m_sliderYaw.GetPos() - 500) / 500.f * limit;
		m_heave = (g_controlDlg->m_sliderHeave.GetPos() - 500) / 500.f * limit;
		m_surge = (g_controlDlg->m_sliderSurge.GetPos() - 500) / 500.f * limit;
		m_sway = (g_controlDlg->m_sliderSway.GetPos() - 500) / 500.f * limit;

		g_controlDlg->m_editRoll = m_roll;
		g_controlDlg->m_editPitch = m_pitch;
		g_controlDlg->m_editYaw = m_yaw;
		g_controlDlg->m_editHeave = m_heave;
		g_controlDlg->m_editSurge = m_surge;
		g_controlDlg->m_editSway = m_sway;
		g_controlDlg->UpdateData(FALSE);
	}

	// mobile movement
	Quaternion q;
	q.Euler2(Vector3(m_roll, m_yaw, m_pitch));
	Matrix44 rotate = q.GetMatrix();

	Matrix44 rm, tm;
	rm.SetRotationX(ANGLE2RAD(-90));
	tm.SetTranslate(Vector3(m_surge, 4.f+m_heave, m_sway));
	m_mobile.m_tm = rm * rotate * tm;


	// actuator
	Matrix44 brm; // base rotate
	brm.SetRotationY(ANGLE2RAD(360 / 6));
	Matrix44 mrm; // mobile rotate
	mrm.SetRotationY(ANGLE2RAD(360 / 3));

	Vector3 mobileV[3];
	mobileV[0] = Vector3(m_mobileRadius, 0, 0) * rotate * tm; // front
	mobileV[1] = Vector3(m_mobileRadius, 0, 0) * mrm * rotate * tm; // right
	mobileV[2] = Vector3(m_mobileRadius, 0, 0) * mrm * mrm * rotate * tm; // left

	Matrix44 baseR = brm, mobileR;
	for (int i = 0; i < 3; ++i)
	{
		Vector3 actuatorPos = Vector3(m_baseRadius, 0, 0) * baseR;
		m_actuator[i * 2].SetLine(m_renderer, actuatorPos, mobileV[i], 0.1f);
		m_actuator[i * 2 + 1].SetLine(m_renderer, actuatorPos, mobileV[(i + 1) % 3], 0.1f);

		g_controlDlg->m_actuator[i*2] = sqrt(actuatorPos.LengthRoughly(mobileV[i]));
		g_controlDlg->m_actuator[i*2+1] = sqrt(actuatorPos.LengthRoughly(mobileV[(i + 1) % 3]));

		baseR *= brm * brm;
		mobileR *= mrm;
	}


	m_incT = 0;
}


void C3DView::Render()
{
	RET(!m_isInitDx);

	//화면 청소
	if (m_renderer.ClearScene())
	{
		m_renderer.BeginScene();

		m_light.Bind(m_renderer, 0);

		// 백그라운드 그리드, 축 출력.
		//m_renderer.RenderGrid();
		//m_renderer.RenderAxis();

		//m_base.Render(m_renderer);
		//m_mobile.Render(m_renderer);
		for (int i=0; i < 6; ++i)
			m_actuator[i].Render(m_renderer);

		//m_renderer.RenderFPS();

		m_renderer.EndScene();
		m_renderer.Present();
	}
}


void C3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
}


void C3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
}


void C3DView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	SetCapture();
	m_RButtonDown = true;
	m_curPos = point;
	CView::OnRButtonDown(nFlags, point);
}


void C3DView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_RButtonDown = false;
	CView::OnRButtonUp(nFlags, point);
}

void C3DView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_RButtonDown)
	{
		const CPoint pos = point - m_curPos;
		m_curPos = point;

		m_camera.Yaw2(pos.x * 0.005f);
		m_camera.Pitch2(pos.y * 0.005f);
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL C3DView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	const float len = m_camera.GetDistance();
	float zoomLen = (len > 100) ? 50 : (len / 4.f);
	if (nFlags & 0x4)
		zoomLen = zoomLen / 10.f;

	m_camera.Zoom((zDelta < 0) ? -zoomLen : zoomLen);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
