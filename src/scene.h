#ifndef SCENE_H
#define SCENE_H
#include <vector>


namespace rt
{
    class Scene
    {
        protected:
        private:
            std::vector<Mesh> objets;
            std::vector<Light> lampes;
            std::vector<Camera> cams;
        public:
            /** default constructor */
            Scene();

            /** default destructor */
            ~Scene();

            /**
            * Return objets
            */
            std::vector<Mesh>& getObjets();

            /**
            * Return lampes
            */
            std::vector<Light>& getLampes();

            /**
            * Return cams
            */
            std::vector<Camera> getCams();
    };
}

#endif //SCENE_H
