#include "item_menu.hpp"

namespace Interface
{
	namespace Util
	{
		class PopUp;
	}
	namespace Items
	{
		class UI_DLL_API Arvore : public ItemMenu
		{
		public:
			Arvore() = default;
			Arvore(const std::string &label_shared, std::shared_ptr<Util::PopUp> popup);
			void atualizar() override;
			void renderizar() const override;
		private:
			std::shared_ptr<Util::PopUp> m_popup{ nullptr };
		};
	}
}