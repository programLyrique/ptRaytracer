#ifndef SBL_H
#define SBL_H


#include <map>
#include <vector>
#include <string>

#include "mesh.h"

namespace rt
{
    /**
     * SBL : scene building language
     * To describe a scene.
     *
     *
     * Instruction args
     */
    class Sbl
    {
        public:
            /**
             * Parser for an element in the scene
             * Implement it to be able to parse new objects
             */
            template <typename T>
            class Parser
            {
                public:
                    virtual T* parseMesh(const vector<string> args) = 0;
            }


            /** Default constructor */
            Sbl();
            /** Default destructor */
            virtual ~Sbl();

            /**
             * Read a file that describes a scene.
             */
             Scene* loadFile(const string& name);

            /**
             * To register a new mesh parser.
             */
            void registerMeshParser(const string& name, Parser<Mesh>* parser);

            /**
             * To register a new light parser.
             */
            void registerLightParser(const string& name, Parser<Light>* parser);

            /**
             * To register a new camera parser.
             */
             void registerCameraParser(const string& name, Parser<Light>* parser);

             /**
              * To
              */
            /**
             * Splits a string on whitespaces
             */
            static vector<string> split(const string& str);

    ;    protected:
        private:
            map<const string&, Parser<Mesh> > meshInstr;
    };

}

#endif // SBL_H
