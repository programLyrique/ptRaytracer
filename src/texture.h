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
			/** Parameters for the Phong reflection */
			int brillance;
			double ka;
			double kd;
			double ks;
		public:
			/** default constructor */
			Texture() {};
			/** default destructor */
			~Texture() {};
			/** Constructor
			* @param color
			* @param brillance
			*/
			Texture(color col, int b, double a, double d, double s) : c(col), brillance(b), ka(a), kd(d), ks(s) {};
			/** Accessor */
			color getColor() const;

	};
}

#endif //TEXTURE_H
