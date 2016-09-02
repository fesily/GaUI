#include "stdafx.h"
#include "GaButtonStyle.h"
#include "BasicComposition.h"
#include "Element.h"

namespace GaUI
{
	namespace Control
	{
		namespace Style
		{
			GaButtonElement GaButtonElement::Create()
			{
				GaButtonElement button;
				{
					button.mainComposition = new Layout::BoundsComposition;
					button.mainComposition->m_eLimitMode = Layout::Composition::Limit2ElementAndChildren;
				}
				
				{
				}
				return button;
			}
			GabuttonStyle::GabuttonStyle()
			{
				m_composition = GaButtonElement::Create();
			}

			Layout::Composition* GabuttonStyle::GetComposition()
			{
				return m_composition.mainComposition;
			}

			void GabuttonStyle::Transf(Gabutton::eState newState)
			{
				if(m_eState != newState)
				{
					m_eState = newState;
					
				}
			}

		

		}
	}
}