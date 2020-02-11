#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#ifndef DATASET_HPP
#define DATASET_HPP 
class Dataset {
    public:
        Dataset(const char* file);
        ~Dataset();
        
        void Show(bool verbose);
    	std::vector<double> getInstance(int i);
    	int getNbrSamples();
    	int getDim();

    private:
		int dim;
		int nsamples;
        std::vector<std::vector<double> > instances_;
};
#endif //DATASET_HPP