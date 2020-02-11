
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Dataset.hpp"


int Dataset::getNbrSamples() {
	return nsamples;
}

int Dataset::getDim() {
	return dim;
}

Dataset::~Dataset() {
}

void Dataset::Show(bool verbose) {
	std::cout<<"Dataset with "<<nsamples<<" samples, and "<<dim<<" dimensions."<<std::endl;

	if (verbose) {
		for (int i=0; i<nsamples; i++) {
			for (int j=0; j<dim; j++) {
				std::cout<<instances_[i][j]<<" ";
			}
			std::cout<<std::endl;		
		}
	}
}

Dataset::Dataset(const char* file) {
	nsamples = 0;
	dim = -1;

	std::ifstream fin(file);
	
	if (fin.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
	
	std::vector<double> row; 
    std::string line, word, temp; 

	while (getline(fin, line)) {
		row.clear();
        std::stringstream s(line);
        
        int valid_sample = 1;
        int ncols = 0;
        while (getline(s, word, ',')) { 
            // add all the column data 
            // of a row to a vector 

//            try {
				double val = std::atof(word.c_str()); 
	            row.push_back(val); 
//			} catch (...) {
//				std::cerr << "Invalid value (sample "<<nsamples<<", column "<<ncols<< "), ignoring and skipping row." <<std::endl;
//				valid_sample=0;
//				break;
//	//				row.push_back(0.);
//	//				std::cerr << "Exception in reading datafile; inconsistent dataset."<<std::endl;
//	//				exit(1);
//			}
            ncols++;
        }
        if (!valid_sample) { 	// in this version, valid_sample is always 1
        	continue;
        }         
        instances_.push_back(row);
        if (dim==-1) dim = ncols;
        else if (dim!=ncols) {
        	std::cerr << "ERROR, inconsistent dataset" << std::endl;
        	exit(-1);
        }
        
		nsamples ++;
	}
	
	fin.close();
}

std::vector<double> Dataset::getInstance(int i) {
	return instances_[i];
}
