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
			double kaR;
			double kdR;
			double ksR;
            double kaG;
			double kdG;
			double ksG;
            double kaB;
			double kdB;
			double ksB;
		public:
			/** default constructor */
			Texture() {};
			/** default destructor */
			~Texture() {};
			/** Constructor
			* @param color
			* @param brillance and other coefficients
			*/
			Texture(color col, int b, double aR, double dR, double sR, double aG, double dG, double sG, double aB, double dB, double sB) : c(col), brillance(b), kaR(aR), kdR(dR), ksR(sR), kaG(aG), kdG(dG), ksG(sG), kaB(aB), kdB(dB), ksB(sB) {};
			/** Accessor */
			color getColor() const;

	};
}

#endif //TEXTURE_H
