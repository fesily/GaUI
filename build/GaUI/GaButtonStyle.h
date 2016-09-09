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
		class GaSolidBorderElement;
		class GaSolidLabelElement;
		class GaGradientBackgroundElement;
	}
	namespace Control
	{
		namespace Style
		{
			struct GaButtonElement
			{
				Element::GaSolidBorderElement* boardElement;//�߿�ͼԪ
				Element::GaGradientBackgroundElement* backgroundElement;//����ͼԪ
				Element::GaSolidLabelElement* textElement;//����ͼԪ
				Layout::BoundsComposition* mainComposition;//��������
				Layout::BoundsComposition* textComposition;//���ֲ�����
				Layout::BoundsComposition* backgroundComposition;//����������

				static GaButtonElement Create(Alignment horizontal = Alignment::Center, Alignment vertical = Alignment::Center);
			};
			class GabuttonStyle
				:public Gabutton::IButtonStyle
			{
			public:
				GabuttonStyle();

				Layout::Composition* GetComposition()override;
				void Transf(Gabutton::eStatus newState)override;
			protected:
				GaButtonElement m_composition;
				Gabutton::eStatus m_eState;
			};
		}
	}
}