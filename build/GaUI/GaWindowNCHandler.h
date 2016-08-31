#pragma once
namespace GaUI
{
	class GaWindowNCHandler
	{
	protected:
		enum eNcMsg
		{
			Msg_Start = WM_NCCREATE,

#if (_WIN32_WINNT >= 0x500)
			Msg_End = WM_NCXBUTTONDBLCLK,
#else
			Msg_End = WM_NCMBUTTONDBLCLK,
#endif // 
		};
	public:
		GaWindowNCHandler();
		virtual ~GaWindowNCHandler();
		//��Ϣ����
	public:
		BOOL ProcessWindowMessage(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam,
								  _In_ LPARAM lParam, _Inout_ LRESULT& lResult, _In_ DWORD dwMsgMapID = 0);
	protected:
		void OnNcPaint();
		void OnDispalayChange(DWORD dwColorBit, const CSize& szScreen);
		void OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
		LRESULT OnNcCalcSize(BOOL wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcHitTest(CPoint& pt);
	public:
		CRect GetClientRectEx();
		CRect GetCaptionRect();
	protected:
		bool IsDiscardMsg(UINT uMsg);
		void SetWindow(HWND hWnd);
	protected:
		CRect m_NcMargin;//�������ڵĻ��з�Χ
		long m_nCaptionHeight;//�������߶�
		CSize m_szMinSize;//������С�ߴ�
	private:
		CWindow m_window;
	};

	inline bool GaWindowNCHandler::IsDiscardMsg(UINT uMsg)
	{//����True ���˸���Ϣ,false ����
		if(uMsg >= Msg_Start && uMsg <= Msg_End)
		{
			if(uMsg == WM_GETDLGCODE || uMsg == WM_SYNCPAINT)
				return true;
			return false;
		}
		else
		{
			if(uMsg == WM_GETMINMAXINFO || uMsg == WM_DISPLAYCHANGE)
				return false;
			return true;
		}
	}
}
