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
		    /** color of the object */
			color c;
			/** when the object start reflecting */
			double brillance;
		public:
			/** default constructor */
			Texture() {};
			/** default destructor */
			~Texture() {};
			/** Constructor
			* @param color
			* @param brillance
			*/
			Texture(color col, double b) : c(col), brillance(b) {};
			/** Accessor */
			color getColor() const;

	};
}

#endif //TEXTURE_H
