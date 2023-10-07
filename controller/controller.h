#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_CONTROLLER_H_

#include <QString>

#include "../model/model.h"
#include "QLineEdit"
#include "qlistview.h"

namespace s21 {

class Controller {
 public:
  bool Calculate(QString str, double x, double *res);
  void Concat(QLineEdit *lineEdit, const QString src);

 private:
  Model model;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_CONTROLLER_H_