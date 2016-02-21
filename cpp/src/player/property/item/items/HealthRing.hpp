#ifndef __HEALTHRING_CLASS__
#define __HEALTHRING_CLASS__

#include <string>

#include "../Item.hpp"

class HealthRing : public Item
{
	public:
		virtual TextureID getIconTextureID() const override;
		float getHealthStat() const;
		std::string getDescription() const;
};

#endif