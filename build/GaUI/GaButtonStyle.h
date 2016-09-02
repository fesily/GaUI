#pragma once
#include "GaControl.h"
namespace GaUI
{
	namespace Layout
	{
		class BoundsComposition;
	}
	namespace Element
	{
		class SolidBorderElement;
		class SolidLabelElement;
		class GradientBackgroundElement;
	}
	namespace Control
	{
		namespace Style
		{
			struct GaButtonElement
			{
				Element::SolidBorderElement* boardElement;//�߿�ͼԪ
				Element::GradientBackgroundElement* backgroundElement;//����ͼԪ
				Element::SolidLabelElement* textElement;//����ͼԪ
				Layout::BoundsComposition* mainComposition;//��������
				Layout::BoundsComposition* textComposition;//���ֲ�����
				Layout::BoundsComposition* backgroundComposition;//����������

				static GaButtonElement Create();
			};
			class GabuttonStyle
				:public Gabutton::IButtonStyle
			{
			public:
				GabuttonStyle();

				Layout::Composition* GetComposition()override;
				void Transf(Gabutton::eState newState)override;
			protected:
				GaButtonElement m_composition;
				Gabutton::eState m_eState;
			};
		}
	}
}