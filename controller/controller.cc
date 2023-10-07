#include "controller.h"

using namespace s21;

bool Controller::Calculate(QString str, double x, double *res) {
  if (model.Reckoner(str.toStdString(), x, res)) {
    return true;
  }
  return false;
}

void Controller::Concat(QLineEdit *lineEdit, const QString src) {
  std::string lineE = lineEdit->text().toStdString();
  model.Concat(&lineE, src.toStdString());
  lineEdit->setText(QString::fromStdString(lineE));
}