#ifndef ElementInterface_h__
#define ElementInterface_h__
#include "GaBaseClass.h"
#include <string>
namespace GaUI
{
	namespace Element
	{
		
		class IElement;
		class IRenderer;
		class IRenderTarget
		{
		public:
			virtual void StartRendering() = 0;
			virtual bool StopRendering() = 0;
			virtual void PushClipper(CRect clipper) = 0;
			//当前剪贴区已经被覆盖
			virtual bool IsClipperCoverWholeTarget() = 0;
			virtual void PoshClipper() = 0;
			virtual CRect GetClipper() = 0;
		};
		class IRendererFactory
			:public Interface
		{
		public:
			virtual IRenderer* Create() = 0;
		};

		class IRenderer 
			:public Interface
		{
		public:
			virtual IRendererFactory* GetFactory() = 0;
			virtual void SetRenderTarget(IRenderTarget* renderTarget) = 0;
			virtual void Render(CRect bounds) = 0;
			virtual CSize GetMinSize() = 0;
		};

		class IElementFactory
			:public Interface
		{
		public:
			virtual std::wstring GetElementTypeName() = 0;
			virtual IElement* Create() = 0;
		};

		class IElement 
			:public Interface
		{
		public:
			virtual IElementFactory* GetFactory() = 0;
			virtual	IRenderer* GetRender() = 0;
		};


	}













// 
// 
// 	class INativeWindow
// 	{
// 	public:
// 		HWND hWnd_;
// 		INativeWindow(HWND hWnd)
// 			:hWnd_(hWnd)
// 		{
// 
// 		}
// 		CSize GetClientSize()
// 		{
// 			return GetClientRect().Size();
// 		}
// 		CRect GetClientRect()
// 		{
// 			CRect result;
// 			if(::IsWindow(hWnd_))
// 			{
// 				RECT required = { 0 }, bounds;
// 				::AdjustWindowRect(&required, (DWORD)::GetWindowLongPtr(hWnd_, GWL_STYLE), FALSE);
// 				::GetWindowRect(hWnd_, &bounds);
// 				result = CRect(
// 					bounds.left - required.left,
// 					bounds.top - required.top,
// 					bounds.right - required.right,
// 					bounds.bottom - required.bottom
// 				);
// 			}
// 			return result;
// 		}
// 	};
// 
// 	class GdiRenderTarget
// 		:public IRenderTarget
// 	{
// 	public:
// 		INativeWindow* window_;
// 		CDC* dc_{ nullptr };
// 		std::stack<CRect> clippers_;
// 		int clipperCoverWholeTargetCounter_{ 0 };
// 	public:
// 		GdiRenderTarget(INativeWindow* window)
// 			:window_(window)
// 		{
// 
// 		}
// 		void ApplyClipper()
// 		{
// 			if(clipperCoverWholeTargetCounter_ == 0)
// 			{
// 				if(clippers_.empty())
// 				{
// 					dc_->SelectClipRgn(nullptr);
// 				}
// 				else
// 				{
// 					CRgn rgn;
// 					rgn.CreateEllipticRgnIndirect(GetClipper());
// 					dc_->SelectClipRgn(rgn);
// 				}
// 			}
// 
// 		}
// 		void StartRendering()override
// 		{
// 			dc_ = new CDC(::GetWindowDC(window_->hWnd_));
// 			CRect rc;
// 			::GetWindowRect(window_->hWnd_, rc);
// 			CPoint pt(rc.TopLeft());
// 			::ScreenToClient(window_->hWnd_, &pt);
// 			dc_->SetWindowOrg(pt);
// 		}
// 		bool StopRendering()override
// 		{
// 			::ReleaseDC(window_->hWnd_, dc_->m_hDC);
// 			delete dc_;
// 			dc_ = nullptr;
// 			return true;
// 		}
// 		void PushClipper(CRect clipper)
// 		{
// 			if(clipperCoverWholeTargetCounter_ > 0)
// 			{
// 				clipperCoverWholeTargetCounter_++;
// 			}
// 			else
// 			{
// 				const CRect& previousClipper = GetClipper();
// 				CRect currentClipper;
// 				currentClipper.left = max(previousClipper.left, clipper.left);
// 				currentClipper.top = max(previousClipper.top, clipper.top);
// 				currentClipper.right = min(previousClipper.right, clipper.right);
// 				currentClipper.bottom = min(previousClipper.bottom, clipper.bottom);
// 
// 				if(currentClipper.IsNormalize())
// 				{
// 					if(currentClipper != previousClipper)
// 						clippers_.emplace(currentClipper);
// 				}
// 				else
// 				{
// 					clipperCoverWholeTargetCounter_++;
// 				}
// 			}
// 			ApplyClipper();
// 		}
// 		//当前剪贴区已经被覆盖
// 		bool IsClipperCoverWholeTarget()override
// 		{
// 			return clipperCoverWholeTargetCounter_ > 0;
// 		}
// 		void PoshClipper()override
// 		{
// 			if(!clippers_.empty())
// 			{
// 				if(clipperCoverWholeTargetCounter_ > 0)
// 				{
// 					clipperCoverWholeTargetCounter_--;
// 				}
// 				else
// 				{
// 					clippers_.pop();
// 				}
// 				ApplyClipper();
// 			}
// 		}
// 		CRect GetClipper() override
// 		{
// 			if(clippers_.empty())
// 			{
// 				return CRect(CPoint(0, 0), window_->GetClientSize());
// 			}
// 			else
// 			{
// 				return clippers_.top();
// 			}
// 		}
// 		CDC* GetDC()
// 		{
// 			return dc_;
// 		}
// 	};
// 
// 	class BorderRenderer
// 		:public IRenderer
// 	{
// 		IElement* element_;
// 		GdiRenderTarget* renderTarget_;
// 		COLORREF CR;
// 	public:
// 		BorderRenderer(IElement* element)
// 			:element_(element)
// 		{
// 			CR = 0123;
// 		}
// 		void SetRenderTarget(IRenderTarget* renderTarget)override
// 		{
// 			renderTarget_ = dynamic_cast<GdiRenderTarget *>(renderTarget);
// 			ATLASSERT(renderTarget_);
// 		}
// 		void Render(CRect bounds)override
// 		{
// 			auto pDC = renderTarget_->GetDC();
// 			pDC->MoveTo(bounds.left + bounds.Width() / 2, bounds.top);
// 			pDC->LineTo(bounds.left + bounds.Width() / 2, bounds.bottom);
// 			pDC->FillSolidRect(CRect(bounds.left + 1, bounds.top + bounds.Height() / 3, bounds.right - 1, bounds.bottom - bounds.Height() / 3), CR);
// 		}
// 		CSize GetMinSize()override
// 		{
// 			return CSize();
// 		}
// 	};
// 
// 	class BorderElement
// 		:public IElement
// 	{
// 		BorderRenderer* renderer{ nullptr };
// 		IRenderer* GetRender()override
// 		{
// 			return renderer ? renderer : renderer = new BorderRenderer(this);
// 		}
// 	};
}
#endif // ElementInterface_h__
