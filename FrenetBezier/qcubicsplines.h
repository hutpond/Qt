#ifndef QCUBICSPLINES_H
#define QCUBICSPLINES_H

#include <vector>
#include <memory>
#include <Eigen/Dense>

class QCubicSplines
{
public:
  QCubicSplines() {
  }

  Eigen::Vector4d getCoefficient(int i) {
    assert(i >= 0 && i < coefficients_.size());
    return coefficients_[i];
  }
  void addPoint(const double x, const double y) {
    Eigen::Vector2d point;
    point[0] = x;
    point[1] = y;
    points_.push_back(point);
  }

  void calculate(){
    const int size_points = points_.size();
    const int size_splines = size_points - 1;
    std::shared_ptr<Eigen::MatrixXd> data(new Eigen::MatrixXd(4 * size_splines, 4 * size_splines));
    for (int i = 0; i < 4 * size_splines; ++i) {
      for (int j = 0; j < 4 * size_splines; ++j) {
        (*data)(i, j) = 0.0;
      }
    }

    Eigen::VectorXd value(4 * size_splines);

    int row = 0;
    for (int i = 0; i < size_points; ++i) {
      for (int j = 0; j < size_splines; ++j) {
        int index = 4 * j;
        if (j == i) {
          (*data)(row, index ++) = std::pow(points_[i][0], 3);
          (*data)(row, index ++) = std::pow(points_[i][0], 2);
          (*data)(row, index ++) = points_[i][0];
          (*data)(row, index ++) = 1;

          value[row] = points_[i][1];

          ++ row;
        }
        else if (j == i - 1) {
          (*data)(row, index ++) = std::pow(points_[i][0], 3);
          (*data)(row, index ++) = std::pow(points_[i][0], 2);
          (*data)(row, index ++) = points_[i][0];
          (*data)(row, index ++) = 1;

          value[row] = points_[i][1];

          ++ row;
        }
      }
    }

    for (int i = 1; i < size_points - 1; ++i) {
      int index = 4 * (i - 1);
      (*data)(row, index ++) = 3.0 * std::pow(points_[i][0], 2);
      (*data)(row, index ++) = 2.0 * points_[i][0];
      (*data)(row, index ++) = 1;
      (*data)(row, index ++) = 0;

      (*data)(row, index ++) = -3.0 * std::pow(points_[i][0], 2);
      (*data)(row, index ++) = -2.0 * points_[i][0];
      (*data)(row, index ++) = -1;
      (*data)(row, index ++) = 0;

      value[row] = 0;
      ++ row;

      index = 4 * (i - 1);
      (*data)(row, index ++) = 6.0 * points_[i][0];
      (*data)(row, index ++) = 2.0;
      (*data)(row, index ++) = 0;
      (*data)(row, index ++) = 0;

      (*data)(row, index ++) = -6.0 * points_[i][0];
      (*data)(row, index ++) = -2.0;
      (*data)(row, index ++) = 0;
      (*data)(row, index ++) = 0;

      value[row] = 0;
      ++ row;
    }

    int index = 0;
    (*data)(row, index ++) = 6.0 * points_[0][0];
    (*data)(row, index ++) = 2.0;
    (*data)(row, index ++) = 0;
    (*data)(row, index ++) = 0;
    value[row] = 0;
    ++ row;

    index = 4 * (size_splines - 1);
    (*data)(row, index ++) = 6.0 * points_[size_points - 1][0];
    (*data)(row, index ++) = 2.0;
    (*data)(row, index ++) = 0;
    (*data)(row, index ++) = 0;
    value[row] = 0;
    ++ row;

    Eigen::VectorXd solve(4 * size_splines);
    solve = data->colPivHouseholderQr().solve(value);

    for (int i = 0; i < size_splines; ++i) {
      Eigen::Vector4d coef;
      coef(0) = solve[4 * i];
      coef(1) = solve[4 * i + 1];
      coef(2) = solve[4 * i + 2];
      coef(3) = solve[4 * i + 3];

      coefficients_.push_back(coef);
    }
  }

  void reset() {
    points_.clear();
    coefficients_.clear();
  }

private:
  std::vector<Eigen::Vector2d> points_;
  std::vector<Eigen::Vector4d> coefficients_;
};

#endif // QCUBICSPLINES_H
