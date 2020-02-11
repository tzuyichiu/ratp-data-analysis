#include "logisticRegression.hpp"


logisticRegression::~logisticRegression(){
	
}

logisticRegression::logisticRegression(double eta, int niter, int labelcol, const char* file){
	Dataset* dataset = new Dataset(file);
	data = dataset;
	eta_ = eta;
	n_iter = niter;
	label_col = labelcol;
}


void logisticRegression::fit(){

	Eigen::MatrixXd x_train ( data->getNbrSamples(), data->getDim() - 1 );
	Eigen::ArrayXd y_train = Eigen::ArrayXd::Ones ( data->getNbrSamples());
	
	weights = Eigen::ArrayXd::Random(data->getDim());

	cost_ = {};

	for (int i=0; i<data->getNbrSamples(); i++) {
		y_train(i) = data->getInstance(i)[label_col];

		for (int j = 0, j2 = 0; j < data->getDim() - 1 && j2 < data->getDim(); j++, j2++) {
			if (j==label_col && j2==label_col) {
				j--;
				continue;
			}
	//		if (j>col_regr_) std::cout<<"Past the post"<<std::endl;
			x_train(i,j) = data->getInstance(i)[j2];
		}
	}


	/******** Add Intercept Term to X ********/

	Eigen::MatrixXd temp( x_train.rows(), x_train.cols() + 1 );
	temp << Eigen::VectorXd::Ones( x_train.rows() ), x_train;
	x_train = temp;
	temp.resize( 0, 0 ); // Lowers temp memory allocation

	//std::cout<< " x_train : \n" <<  x_train<<"\n";
	//std::cout<< " y_train : \n" <<  y_train<<"\n";
	
	Eigen::MatrixXd* x = &x_train;

	Eigen::ArrayXd err (x_train.rows());

	for(int i=0; i< n_iter; i++){

		Eigen::ArrayXd net_input_ = net_input(x);
		Eigen::ArrayXd output = activation(net_input_);

		err  =  (y_train - output);

		Eigen::MatrixXd Xt = x_train.transpose();
		Eigen::MatrixXd errt = err.matrix();


	
		weights = weights -  eta_*( Xt * errt) ;
	
		
	}

	std::cout<<"the weights are: \n"<<weights<<std::endl;

}


Eigen::ArrayXd logisticRegression::net_input(Eigen::MatrixXd* x){
	
	Eigen::ArrayXd z((*x).rows());

	for(int i = 0; i< (*x).rows(); i++){
		double s = (*x).row(i) * weights.matrix();
		z(i) = s;
	}
	return z;

}


Eigen::ArrayXd logisticRegression::activation( Eigen::ArrayXd z){
	Eigen::ArrayXd  one_  = Eigen::ArrayXd::Ones(z.size());
	z = one_/(one_ + (-z).exp());
	return z;
}

int logisticRegression::predict( Eigen::MatrixXd* x ){
	Eigen::ArrayXd z = net_input(x);
	z = activation( z);

	if(z(0)>= 0.5) return 1;

	else return 0;
};
