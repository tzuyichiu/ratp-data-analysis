#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;
using namespace std;

class logistic_regression
{
public:
   VectorXd w;
   double b;
   logistic_regression(int n_in)
   {
      this->w = VectorXd::Random(n_in);
      this->b = 0.0;
   }

   void train(MatrixXd train_datas, double lr)
   {
      VectorXd dw(this->w.rows());
      double db;
      dw = train_datas.rightCols(1) - calc(train_datas.leftCols(this->w.rows()));
      db = dw.mean();
      MatrixXd tmp = train_datas.leftCols(this->w.rows());
      tmp = tmp.array().colwise()*dw.array();
      dw = tmp.colwise().mean();
      w += lr * dw;
      b += lr * db;
   }

   VectorXd predict(MatrixXd inputs)
   {
      return ((1 / (1 + ((-inputs*this->w).array() - b).exp())).array() > 0.5).cast<double>();
   }

   double test_error(MatrixXd datas)
   {
      VectorXd outputs = predict(datas.leftCols(w.rows()));
      /*
      cout << outputs << endl << endl << endl;
      cout << datas.rightCols(1) << endl << endl << endl;
      cout << (outputs - datas.rightCols(1)) << endl;
      cout << ((outputs - datas.rightCols(1)).array() > 1e-5).count() << endl;*/

      return ((outputs - datas.rightCols(1)).array() > 1e-5).count() / (double)outputs.rows();

   }


};

MatrixXd linear_separable_dataset_generator(int n, int dim, VectorXd w, double b)
{
   int n_col = w.rows();
   MatrixXd datas = MatrixXd::Random(n, n_col + 1);

   datas.rightCols(1) = (((datas.leftCols(n_col)*w).array() + b) > 0).cast<double>();
   return datas;
}

void test_logistic_regression()
{
   logistic_regression lr(2);
   VectorXd w(2);
   double b = 0.2;
   w << 0.3, 0.6;
   MatrixXd train_datas = linear_separable_dataset_generator(1000, 2, w, b);
   for (int i = 0; i < 500; i++)
   {
      lr.train(train_datas.topRows(990), 0.1112);
      cout << "epoch:" << i << " error:" << lr.test_error(train_datas) << endl;
   }
   cout << "w:" << lr.w / (lr.b / 0.2) << endl;
   cout << "b:" << lr.b << endl;