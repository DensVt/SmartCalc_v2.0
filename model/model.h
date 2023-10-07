#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_MODEL_MODEL_H_

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
namespace s21 {
const std::vector<string> p_m_oper{"+", "-"};
const std::vector<string> other_oper{"*", "/", "^", "%"};
const std::vector<string> oper{"+", "-", "*", "/", "^", "%"};
const std::vector<string> func{"sin",  "cos", "tan", "asin", "acos",
                               "atan", "ln",  "log", "sqrt"};
const std::vector<string> left_scobe{"("};
const std::vector<string> right_scobe{")"};
const std::map<std::string, int> priorityTable_ = {
    {"num", -2}, {"(", -1},   {")", -1},   {"+", 1},    {"-", 1},   {"*", 2},
    {"/", 2},    {"^", 3},    {"%", 3},    {"sin", 4},  {"cos", 4}, {"tan", 4},
    {"asin", 4}, {"acos", 4}, {"atan", 4}, {"sqrt", 4}, {"ln", 4},  {"log", 4}};
const std::map<std::string, int> singNumOperations_ = {
    {"sin", 4},  {"cos", 4},  {"tan", 4}, {"asin", 4}, {"acos", 4},
    {"atan", 4}, {"sqrt", 4}, {"ln", 4},  {"log", 4}};
const std::map<std::string, int> worksWithUnary_ = {
    {"(", -1}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};

class Stack {
 protected:
  struct Node {
    double value_;
    std::map<std::string, int> operation_;
    Node(const double value, std::map<std::string, int> operation)
        : value_(value), operation_(operation) {}
  };

 public:
  Stack() {}
  ~Stack() {}

  void PushBack(const double value);
  void PushBack(const std::map<std::string, int> type);
  void PopBack();
  bool Empty();
  int Size();
  Node Top();
  std::vector<Node>::iterator Begin();
  std::vector<Node>::iterator End();
  void Clear();

 private:
  std::vector<Node> head_;
};

class Model : Stack {
 public:
  Model() {}
  ~Model() {}
  bool Reckoner(std::string str, double x, double *res);
  void Concat(std::string *lineEdit, const std::string src);

 private:
  Stack valuesStack_;
  Stack operationsStack_;

  void DataInterpretation(int *consecutive_opers, size_t *i, bool *unary,
                          std::string strStep, std::string str, double x);
  bool FunctionInterpretation(int *consecutive_opers, size_t *i, bool *unary,
                              std::string strStep, std::string str);
  void NotationOrganizer(std::string str);
  void BracketProcessor(bool *scobe);
  void FunctionHandler(bool scobe);
  void StringEndInterpreter(std::string str);
  void PolishNotation(bool flag);
  bool NotationAssistant(Node *down_oper, Node *current_oper, bool flag);
  void FunctionPerformer(double num1, double num2, Node *down_oper);

  bool DataVerifier(std::string str, int i);
  bool HasElement(std::vector<string> vec, std::string oper);
  size_t IgnoreValue(std::string str);
  std::string LocateOperation(std::string str);
  void Clear();
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_MODEL_H_