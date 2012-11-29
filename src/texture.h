#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.hpp"

namespace rt
{
    /**
     * To give a texture to your meshes.
     * Supports only uniform color map.
     * @todo Supporting bump maps, normal maps etc.
     */
	class Texture
	{
		protected:
		private:
			color c;
		public:
			/** default constructor */
			Texture() {}
			/** default destructor */
			~Texture() {}
			/** Constructor
			* @param color
			*/
			Texture(color col) : c(col) {}
			/** Accessor */
			color getColor();

	};
}

#endif //TEXTURE_H
