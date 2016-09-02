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
				Element::SolidBorderElement* boardElement;//边框图元
				Element::GradientBackgroundElement* backgroundElement;//背景图元
				Element::SolidLabelElement* textElement;//文字图元
				Layout::BoundsComposition* mainComposition;//主布局器
				Layout::BoundsComposition* textComposition;//文字布局器
				Layout::BoundsComposition* backgroundComposition;//背景布局器

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