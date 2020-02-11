#include "logisticRegression.hpp"

int main(){

    //Dataset data = Dataset("test.csv");
	logisticRegression lreg (1, 300, 3,"log_reg_train_2.csv");

    std::cout<< "fitting the model :\n";

    lreg.fit();

    std::cout<< "*********** first test **************\n"<<"\n";

    Eigen::MatrixXd a(1,4);
    a<<1,9, 2.709854, 48.83665;

    Eigen::MatrixXd b(1,4);
    b<<1,319,2.709854, 48.83665;

    Eigen::MatrixXd* a1 = &a;
    Eigen::MatrixXd* b1 = &b;
    

    int q = lreg.predict(a1);
    std::cout<< "for the entry :  "<< a<<"   the prediction is :  "<< q <<std::endl;
    
    int q1 = lreg.predict(b1);
    std::cout<< "for the entry :  "<< a<<"   the prediction is :  "<<  q1 <<std::endl;;


     std::cout<< " running tests on test-set ..." <<std::endl;

    Dataset test_data = Dataset("log_reg_test_2.csv");
    
    int s_rate = 0;

    for(int i=0; i<100 ; i++){ // cause we have 100 samples in the test set
        Eigen::MatrixXd x(1,4);
        vector<double> v = test_data.getInstance(i);

        x << 1, v[0], v[1],v[2];
        Eigen::MatrixXd* px = &x;

        int res = lreg.predict(px);

        if(res == (int)v[3]){
            s_rate += 1;
    }

    }

    std::cout<< "Results:  \n" <<std::endl;

    std::cout<< "Success rate :  " << s_rate/10 << " %" <<std::endl;

    return 0;
}