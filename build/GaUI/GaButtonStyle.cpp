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
			void CreateSolidLabelElement(Element::GaSolidLabelElement*& element, Layout::BoundsComposition*& composition,
										 Alignment horizontal, Alignment vertical)
			{
				element = Element::GaSolidLabelElement::Create();
				element->SetAlignments(horizontal, vertical);

				composition = new Layout::BoundsComposition;
				composition->SetElement(element);
				composition->m_margin = CMargin();
				composition->m_eLimitMode = Layout::Composition::Limit2Element;
				composition->m_alignment2Parent = CMargin();

			}
			GaButtonElement GaButtonElement::Create(Alignment horizontal, Alignment vertical)
			{
				GaButtonElement button;
				{
					button.mainComposition = new Layout::BoundsComposition;
					button.mainComposition->m_eLimitMode = Layout::Composition::Limit2ElementAndChildren;
				}
				
				{
					auto boardElement = Element::GaSolidBorderElement::Create();
					button.boardElement = boardElement;

					auto boardComposition = new Layout::BoundsComposition;
					button.mainComposition->AddChild(boardComposition);
					boardComposition->AlignmentToParentEmpty();
					boardComposition->SetElement(boardElement);
				}

				{
					auto bkElment = Element::GaGradientBackgroundElement::Create();
					button.backgroundElement = bkElment;
					bkElment->m_eDirection = Element::GaGradientBackgroundElement::Vertical;
					bkElment->m_eShape = Element::Rectangle;

					auto bkComposition = new Layout::BoundsComposition;
					button.backgroundComposition = bkComposition;
					button.mainComposition->AddChild(bkComposition);
					bkComposition->m_alignment2Parent = CMargin(1, 1, 1, 1);
					bkComposition->SetElement(bkElment);
				}

				{
					CreateSolidLabelElement(button.textElement, button.textComposition, horizontal, vertical);
					button.mainComposition->AddChild(button.textComposition);
				}
				return button;
			}
			//////////////////////////////////////////////////////////////////////////
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