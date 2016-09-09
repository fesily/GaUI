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
				Element::GaSolidBorderElement* boardElement;//边框图元
				Element::GaGradientBackgroundElement* backgroundElement;//背景图元
				Element::GaSolidLabelElement* textElement;//文字图元
				Layout::BoundsComposition* mainComposition;//主布局器
				Layout::BoundsComposition* textComposition;//文字布局器
				Layout::BoundsComposition* backgroundComposition;//背景布局器

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