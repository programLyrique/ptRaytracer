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
			color cB;
			color cN;
			/** Parameters for the Phong reflection */
			int brillance;

		public:
			/** default constructor */
			Texture() {};
			/** default destructor */
			~Texture() {};
			/** Constructor
			* @param color
			* @param brillance and other coefficients
			*/
			Texture(color colB, color colN, int b) : cB(colB), cN(colN), brillance(b) {};
			/** Accessor */
			color getColorB() const { return cB; }
			color getColorN() const { return cN; }
			int getBrillance() { return brillance; }						
									

	};
}

#endif //TEXTURE_H
