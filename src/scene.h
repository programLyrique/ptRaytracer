#ifndef SCENE_H
#define SCENE_H
#include <vector>


namespace rt
{
    class Scene
    {
        protected:
        private:
            vector<Mesh> objets;
            vector<Light> lampes;
            vector<Camera> cams;
        public:
            /** default constructor */
            Scene();

            /** default destructor */
            ~Scene();

            /**
            * Return objets
            */
            vector<Mesh>& getObjets();

            /**
            * Return lampes
            */
            vector<Light>& getLampes();

            /**
            * Return cams
            */
            vector<Camera> getCams();
    };
}

#endif //SCENE_H
