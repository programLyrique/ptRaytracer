#ifndef PLAN_H
#define PLAN_H

#include "texture.h"
#include "mesh.h"
#include "position.h"
#include "vector.hpp" 

namespace rt
{
	class Plan :	public Mesh {
	
		protected:
			
			
		private:
			Position point;
			vector normal;
		public:
			/** Constructor */
			Plan() {}
			~Plan() {}
			Plan(Texture t, Position& p, vector n) : Mesh(t), point(p), normal(n.unit()) {}
			
			vector getNormal() { return normal; }
			
			bool intersect(const Position& pos, const vector& vect);
			
			Position getIntersection(const Position& pos, const vector& vect);
		
	};
}

#endif //PLAN_H
