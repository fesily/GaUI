#ifndef MessageDefined_h__
#define MessageDefined_h__


#define MESSAGE_HANDLER_EX(msg, func) \
	if(uMsg == msg) \
	{ \
		bHandled = TRUE; \
		lResult = func(uMsg, wParam, lParam, bHandled); \
		return bHandled;\
	}
#define MESSAGE_PAINT(func)\
	if(uMsg == WM_PAINT)\
	{\
		lResult = 0;\
		func();\
		return TRUE;\
	}
#endif // MessageDefined_h__
