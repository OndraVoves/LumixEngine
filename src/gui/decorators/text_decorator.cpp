#include "gui/decorators/text_decorator.h"
#include "gui/irenderer.h"
#include "gui/block.h"


namespace Lumix
{
namespace UI
{


	TextDecorator::TextDecorator(const char* name)
		: DecoratorBase(name)
	{
		m_is_text_centered = false;
	}

	
	void TextDecorator::render(IRenderer& renderer, Block& block)
	{
		if(m_is_text_centered)
		{
			float w, h;
			renderer.measureText(block.getBlockText().c_str(), &w, &h, block.getGlobalWidth());
			renderer.renderText(block.getBlockText().c_str(), (block.getGlobalRight() + block.getGlobalLeft() - w) / 2, (float)block.getGlobalTop(), block.getZ(), block.getGlobalWidth());
		}
		else
		{
			renderer.renderText(block.getBlockText().c_str(), block.getGlobalLeft(), (float)block.getGlobalTop(), block.getZ(), block.getGlobalWidth());
		}
	}

} // ~namespace UI
} // ~namespace Lumix