#include <QApplication>

#include "application/reckoner.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Reckoner w;
  w.show();
  return a.exec();
}
