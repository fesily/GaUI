#include "stdafx.h"
#include "GraphicesHost.h"
#include "NativeWindowInterface.h"
#include "ResourceManager.h"

namespace GaUI
{
	using namespace Layout;

	GaGraphicesHost::GaGraphicesHost()
	{
		m_pComposition = new Layout::WindowComposition;
		m_pComposition->SetAssociateHost(this);
		m_pComposition->SetLimitMode(Layout::Composition::Limit2ElementAndChildren);
	}

	GaGraphicesHost::~GaGraphicesHost()
	{
		SAFE_DELETE(m_pComposition);
	}

	Native::INativeWindow* GaGraphicesHost::GetNativeWindow() const
	{
		return m_pWnd;
	}

	void GaGraphicesHost::SetNativeWindow(Native::INativeWindow* val)
	{
		if(val != m_pWnd)
		{
			if(m_pWnd)
			{
				///...
			}
			m_pWnd = val;
			m_pComposition->SetAttachedWindow(m_pWnd);
			if(m_pWnd)
			{
				///....
			}
		}
	}

	Layout::WindowComposition* GaGraphicesHost::GetMainComposition() const
	{
		return m_pComposition;
	}

	void Layout::GaGraphicesHost::Render()
	{
		if(m_pWnd && m_pWnd->IsWindowVisible())
		{
			m_pComposition->GetRenderTarget()->StartRendering();
			m_pComposition->Render(CSize());
			bool ret = m_pComposition->GetRenderTarget()->StopRendering();
			m_pWnd->RedrawWindow();

			//����ʧ��,��������ȾĿ����Ч���ߵ��ô���,�ؽ���ȾĿ��;
			if(!ret)
			{
				m_pComposition->SetAttachedWindow(nullptr);
				GetGraphicsResourcesManager()->RecreateRenderTarget(m_pWnd);
				m_pComposition->SetAttachedWindow(m_pWnd);
			}
		}
	}

}