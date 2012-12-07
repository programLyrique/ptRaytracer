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
     * To give a texture to your solides.
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

			/** transparency of the object */
			double transparence;
			/** refraction parameter*/
			double indice;

		public:
			/** default constructor */
			Texture() : brillance(0), transparence(0), indice(0) {};
			/** default destructor */
			~Texture() {};

			/** Constructor
			* @param cB color when illuminated
			* @param cN inner color
			* @param b brillance
			* @param t transparency between 0 and 1 (0 not transparent at all, 1 perfectly transparent)
			* @param n refraction parameter
			*/
			Texture(color colB, color colN, int b, double t, double n) : cB(colB), cN(colN), brillance(b), transparence(t), indice(n) {};

			/** \return brillance color */
			color getColorB() const { return cB; }
			/** \return inner color */
			color getColorN() const { return cN; }
			/** \return brillance */
			int getBrillance() { return brillance; }
			/** \return transparency */
			double getTransparence() { return transparence; }
			/** \return refraction parameter */
			double getIndice() { return indice; }


	};
}

#endif //TEXTURE_H
