#include "sbl.h"

#include <sstring>

namespace rt
{


    Sbl::Sbl()
    {
        //ctor
    }

    Sbl::~Sbl()
    {
        //dtor
    }


    vector<string> Sbl::split(const string& str)
    {
        string word;
        vector<string> vect;

        // On ouvre un buffer depuis lequel on fera les entrées.
        istringstream iss(line, istringstream::in);

        while( iss >> word )
        {
            vect.push_back(word);
        }
        return vect;
    }

}

