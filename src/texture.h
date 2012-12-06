/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
		    /** colors of the object:
		    * cB: Color when illuminated
		    * cN: inner color
		    */
			color cB;
			/**/
			color cN;
			/** Parameter for the Phong reflection */
			int brillance;

			/** transparency of the object (0 not at all, 1 perfectly)*/
			double transparence;
			/** refraction parameter*/
			double indice;

		public:
			/** default constructor */
			Texture() {};
			/** default destructor */
			~Texture() {};

			/** Constructor
			* @param color
			* @param brillance and other coefficients
			*/
			Texture(color colB, color colN, int b, double t, double n) : cB(colB), cN(colN), brillance(b), transparence(t), indice(n) {};

			/** Accessors */
			color getColorB() const { return cB; }
			color getColorN() const { return cN; }
			int getBrillance() { return brillance; }
			double getTransparence() { return transparence; }
			double getIndice() { return indice; }


	};
}

#endif //TEXTURE_H
