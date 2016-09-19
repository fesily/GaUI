#pragma once
#include "ElementInterface.h"
#include "ResourceManager.h"
#include "memory.h"
#include <functional>
namespace GaUI
{
	namespace Element
	{
		namespace Detail
		{
			template<typename _Ty>
			struct ElementPropertyAssignment
			{
				bool operator()(_Ty& des, const _Ty& source)
				{
					if(des != source)
					{
						des = source;
						return true;
					}
					return false;
				}
			};

			//图元属性类的特殊处理
			//赋值时调用_Func_assignment函数对象进行赋值操作
			//赋值成功时调用绑定函数对象通知容器对象
			template<typename _Ty, typename _Func_assignment = ElementPropertyAssignment<_Ty>>
			class ElementProperty
				:public GaProperty::_property_base_value<_Ty>
			{
				typedef std::function<void(void)> Function_notify_type;
				typedef ElementPropertyAssignment<_Ty> Function_assignment;
			public:
				//自动绑定
				template<typename _TContainer>
				ElementProperty(_TContainer* container_point, const _Ty& value)
					: _property_base_value(std::forward<_Ty>(value))
					, m_funcNotify(std::bind(&_TContainer::NotifyRendererStateChanged, container_point))
				{
				}
				template<typename _TContainer>
				ElementProperty(_TContainer* container_point, _Ty&& value)
					: _property_base_value(std::forward<_Ty>(value))
					, m_funcNotify(std::bind(&_TContainer::NotifyRendererStateChanged, container_point))
				{
				}
				template<typename _TContainer>
				ElementProperty(_TContainer* container_point)
					: m_funcNotify(std::bind(&_TContainer::NotifyRendererStateChanged, container_point))
				{
				}



				//手动绑定
				ElementProperty(const _Ty& value)
					: _property_base_value(std::forward<_Ty>(value))
				{

				}
				ElementProperty(_Ty&& value)
					: _property_base_value(std::forward<_Ty>(value))
				{

				}
				void Initialize(Function_notify_type&& func)
				{
					m_funcNotify = std::forward<Function_notify_type>(func);
				}
				void Initialize(const Function_notify_type& func)
				{
					m_funcNotify = std::forward<Function_notify_type>(func);
				}

				//put
				void operator=(value_const_reference value)
				{
					if(m_funcAssignment(Get(), value))
					{
						if(m_funcNotify)
							m_funcNotify();
					}
				}
				//get
				operator value_reference()throw()
				{
					return Get();
				}
				operator value_reference()const throw()
				{
					return Get();
				}
				//operator
				friend bool operator==(const ElementProperty& value1, const ElementProperty& value2)
				{
					return value1.operator==(value2);
				}
				friend bool operator!=(const ElementProperty& value1, const ElementProperty& value2)
				{
					return value1.operator!=(value2);
				}
				inline bool operator==(const ElementProperty& value)
				{
					return operator==(value.Get());
				}
				inline bool operator==(value_const_reference value)
				{
					return Get() == value;
				}
				inline bool operator!=(const ElementProperty& value)
				{
					return operator!=(value.Get());
				}
				inline bool operator!=(value_const_reference value)
				{
					return Get() != value;
				}
			protected:
				Function_notify_type m_funcNotify;
			private:
				Function_assignment m_funcAssignment;
			};

			template<typename TElement>
			class IElementEx
				:public IElement
			{
			public:
				class Factory
					:public IElementFactory
				{
				public:
					std::wstring GetElementTypeName()override
					{
						return TElement::GetElementTypeName();
					}
					IElement* Create()override
					{
						TElement* element = new TElement;
						element->m_pFactory = this;
						IRendererFactory* renderFactory = GetGraphicsResourcesManager()->GetRendererFactory(GetElementTypeName());
						if(renderFactory)
						{
							element->m_renderer = renderFactory->Create();
							element->m_renderer->Initialize(element);
						}
					}
				};
			public:
				static std::wstring GetElementTypeName()
				{
					return C2W(typeid(TElement).name());
				}
				static TElement* Create()
				{
					return dynamic_cast<TElement*>(GetGraphicsResourcesManager()->GetElementFactory(TElement::GetElementTypeName())->Create());
				}
				IElementFactory* GetFactory()override
				{
					return m_pFactory;
				}
				IRenderer* GetRender()override
				{
					return m_renderer.get();
				}
			public:
				inline void NotifyRendererStateChanged()
				{
					if(m_renderer)
						m_renderer->OnElementStateChanged();
				}
			protected:
				IElementFactory* m_pFactory;
				std::shared_ptr<IRenderer> m_renderer;
			};
		}
		using namespace Detail;
		enum eElementShape
		{
			Rectangle,
			Ellipse,
		};
		class GaSolidBorderElement
			:public IElementEx<GaSolidBorderElement>
		{
		protected:
			GaSolidBorderElement();
		public:
			~GaSolidBorderElement();

		public:
			eElementShape m_eShape;
			ElementProperty<Color> m_color;
		};
		class GaRoundBorderElement
			:public IElement
		{

		};
		class Ga3DBorderElement
			:public IElement
		{

		};
		class Ga3DSplitterElement
			:public IElement
		{

		};
		class GaSoildBackgroundElement
			:public IElement
		{

		};
		class GaGradientBackgroundElement
			:public IElementEx<GaGradientBackgroundElement>
		{
		public:
			enum eDirection
			{
				Horizontal,
				Vertical,
				Slash,
				Backslash,
			};
		protected:
			GaGradientBackgroundElement();
		public:
			~GaGradientBackgroundElement();

			void SetColor(const Color& value1, const Color& value2);
		public:
			eElementShape m_eShape;
			ElementProperty<Color> m_color1;
			ElementProperty<Color> m_color2;
			ElementProperty<eDirection> m_eDirection;
		};
		class GaSolidLabelElement
			:public IElementEx<GaSolidLabelElement>
		{
		protected:
			GaSolidLabelElement();
		public:
			~GaSolidLabelElement();

			void SetAlignments(const Alignment& h, const Alignment& v);
		public:
			ElementProperty<bool>			m_isMulitiline;
			ElementProperty<bool>			m_isWrapLine;
			ElementProperty<bool>			m_isEllipse;
			ElementProperty<bool>			m_isWrapLineHeightCalculation;
			ElementProperty<Alignment>		m_hAlignment;
			ElementProperty<Alignment>		m_vAlignment;
			ElementProperty<FontProperties>	m_font;
			ElementProperty<Color>			m_color;
			ElementProperty<std::wstring>	m_text;
		};
		class GaImageFrameElement
			:public IElement
		{

		};
		class GaPolygonElement
			:public IElement
		{

		};
	}
}