#include </usr/include/eigen3/Eigen/Dense>
#include </usr/include/eigen3/Eigen/Core>
#include <vector>
#include <assert.h>
#include "Dataset.hpp"

using namespace std;

/*
	here we implement logistic regssion for classification (0: late,  1: on time)
*/

class logisticRegression{
private:
	double eta_;
	int n_iter;
	int label_col;
	Eigen::VectorXd weights ;
	vector<double> cost_;
	Dataset* data;
	

public:
	logisticRegression(double eta, int niter,int label_col,const char* file);
	~logisticRegression();
	void fit();
	int predict( Eigen::MatrixXd* x );

	Eigen::ArrayXd net_input(Eigen::MatrixXd* x);
	Eigen::ArrayXd activation( Eigen::ArrayXd z);
	
};