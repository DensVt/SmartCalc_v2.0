#ifndef CPP3_SMARTCALC_V2_SRC_VIEW_APLICATION_RECKONER_H_
#define CPP3_SMARTCALC_V2_SRC_VIEW_APLICATION_RECKONER_H_

#include <QWidget>

#include "../../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Reckoner;
}
QT_END_NAMESPACE

namespace s21 {
class Reckoner : public QWidget {
  Q_OBJECT

 public:
  Reckoner(QWidget *parent = nullptr);
  ~Reckoner();

 private:
  Ui::Reckoner *ui;
  Controller controller;

 private slots:
  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();

  void on_pushButton_cos_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_atan_clicked();

  void on_pushButton_pow_clicked();
  void on_pushButton_mod_clicked();

  void on_pushButton_square_open_clicked();
  void on_pushButton_square_close_clicked();

  void on_pushButton_div_clicked();
  void on_pushButton_mult_clicked();

  void on_pushButton_ln_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_sqrt_clicked();

  void on_pushButton_minus_clicked();
  void on_pushButton_plus_clicked();

  void on_pushButton_dot_clicked();
  void on_pushButton_C_clicked();
  void on_pushButton_x_clicked();

  void on_pushButton_eq_clicked();
  void drawGraph();
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_VIEW_APLICATION_RECKONER_H_
