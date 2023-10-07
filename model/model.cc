#include "model.h"

#include <list>

using namespace s21;
// Стэк
void Stack::PushBack(const double value) {
  head_.push_back({value, {{"num", priorityTable_.at("num")}}});
}

void Stack::PushBack(const std::map<std::string, int> type) {
  head_.push_back({0, type});
}

void Stack::PopBack() { head_.pop_back(); }
Stack::Node Stack::Top() { return head_.back(); }
std::vector<s21::Stack::Node>::iterator Stack::Begin() { return head_.begin(); }
std::vector<s21::Stack::Node>::iterator Stack::End() { return head_.end(); }
bool Stack::Empty() { return head_.empty(); }
int Stack::Size() { return head_.size(); }
void Stack::Clear() { head_.clear(); }

bool Model::Reckoner(std::string str, double x, double *res) {
  int consecutive_opers = 0;
  bool unary = true;
  bool success = true;
  size_t i = 0;

  while (i < str.size() && success) {
    std::string str_step = (str.begin() + i).base();
    if (std::isdigit(str[i]) || str[i] == 'x' || str[i] == 'X') {
      try {
        DataInterpretation(&consecutive_opers, &i, &unary, str_step, str, x);
      } catch (std::out_of_range const &err) {
        success = false;
      }
    } else {
      if (!FunctionInterpretation(&consecutive_opers, &i, &unary, str_step,
                                  str)) {
        success = false;
      }
    }
    str_step = (str.begin() + i).base();
    if (success) {
      try {
        NotationOrganizer(str_step);
      } catch (std::out_of_range const &err) {
        success = false;
      }
    }
  }

  if (!operationsStack_.Empty() || str.empty()) {
    success = false;
  }
  success ? *res = valuesStack_.Top().value_ : *res = 0;
  Clear();
  return success;
}

void Model::DataInterpretation(int *consecutive_opers, size_t *i, bool *unary,
                               std::string str_step, std::string str,
                               double x) {
  *consecutive_opers = 0;
  *unary = false;
  double value = 0;
  if (str[*i] == 'x' || str[*i] == 'X') {
    value = x;
    *i += 1;
  } else {
    value = std::atof(str_step.c_str());
    *i += IgnoreValue(str_step);
  }
  valuesStack_.PushBack(value);
}

bool Model::FunctionInterpretation(int *consecutive_opers, size_t *i,
                                   bool *unary, std::string str_step,
                                   std::string str) {
  bool success = true;
  std::string operation = LocateOperation(str_step);
  if (operation.size() > 0) {
    *consecutive_opers += 1;
    if (operation == "(" || operation == ")") {
      *consecutive_opers = 0;
    }
    if (*consecutive_opers > 1) {
      if (*consecutive_opers > 2 || DataVerifier(str, *i) == false) {
        success = false;
      }
    }
    if (success) {
      if (*unary && (operation == "+" || operation == "-")) {
        valuesStack_.PushBack(0);
      }
      operationsStack_.PushBack({{operation, priorityTable_.at(operation)}});
      (*i) += operation.size();
      if (worksWithUnary_.find(operation) != worksWithUnary_.end()) {
        *unary = true;
      }
    }
  } else {
    *consecutive_opers = 0;
    (*i)++;
    *unary = false;
  }
  return success;
}

void Model::NotationOrganizer(std::string str) {
  bool scobe = false;
  if (!operationsStack_.Empty()) {
    BracketProcessor(&scobe);
    FunctionHandler(scobe);
    StringEndInterpreter(str);
  }
}

void Model::BracketProcessor(bool *scobe) {
  if (operationsStack_.Top().operation_.begin()->first == ")") {
    while (!operationsStack_.Empty() && !valuesStack_.Empty()) {
      if (operationsStack_.Size() == 1) {
        break;
      }
      Node *rs = operationsStack_.End().operator-(1).base();
      Node *ls = operationsStack_.End().operator-(2).base();
      if (rs->operation_.begin()->first == ")" &&
          ls->operation_.begin()->first == "(") {
        *scobe = true;
        break;
      }
      PolishNotation(false);
    }
    if (*scobe) {
      operationsStack_.PopBack();
      operationsStack_.PopBack();
    } else {
      throw std::out_of_range("Error calculation!");
    }
  }
}

void Model::FunctionHandler(bool scobe) {
  if (!operationsStack_.Empty()) {
    if (singNumOperations_.find(
            operationsStack_.Top().operation_.begin()->first) !=
            singNumOperations_.end() &&
        scobe) {
      PolishNotation(true);
    }
    if (operationsStack_.Size() > 1) {
      Node *fp = operationsStack_.End().operator-(1).base();
      Node *sp = operationsStack_.End().operator-(2).base();
      if (!(fp->operation_.begin()->first == "^" &&
            sp->operation_.begin()->first == "^")) {
        while (!valuesStack_.Empty() && operationsStack_.Size() > 1) {
          Node *fps = operationsStack_.End().operator-(1).base();
          Node *sps = operationsStack_.End().operator-(2).base();
          if (fps->operation_.begin()->second >
                  sps->operation_.begin()->second ||
              fps->operation_.begin()->first == "(" ||
              sps->operation_.begin()->first == "(") {
            break;
          }
          PolishNotation(false);
        }
      }
    } else {
      PolishNotation(false);
    }
  }
}

void Model::StringEndInterpreter(std::string str) {
  if (str.empty()) {
    while (!valuesStack_.Empty() && !operationsStack_.Empty()) {
      if (operationsStack_.Top().operation_.begin()->first == "(" ||
          operationsStack_.Top().operation_.begin()->first == ")") {
        throw std::out_of_range("Error calculation!");
        break;
      }
      PolishNotation(true);
    }
  }
}
void Model::PolishNotation(bool flag) {
  if (!operationsStack_.Empty()) {
    Node *down_oper = nullptr;
    if (flag) {
      down_oper = operationsStack_.End().operator-(1).base();
    } else if (operationsStack_.Size() > 1) {
      down_oper = operationsStack_.End().operator-(2).base();
    }

    Node *current_oper = operationsStack_.End().operator-(1).base();
    if (NotationAssistant(down_oper, current_oper, flag)) {
      std::map<std::string, int> op = current_oper->operation_;
      operationsStack_.PopBack();
      if (!operationsStack_.Empty() && !flag) {
        operationsStack_.PopBack();
        operationsStack_.PushBack(op);
      }
    }
  }
}

bool Model::NotationAssistant(Node *down_oper, Node *current_oper, bool flag) {
  bool make_operations = false;
  if (down_oper != nullptr) {
    if (down_oper->operation_.begin()->second >=
        current_oper->operation_.begin()->second) {
      make_operations = true;
    } else if (flag && valuesStack_.Size() > 1) {
      make_operations = true;
    }
    if (current_oper->operation_.begin()->first == "(") {
      make_operations = false;
    }
    if (make_operations) {
      double num1 = 0;
      double num2 = 0;
      if (singNumOperations_.find(down_oper->operation_.begin()->first) !=
          singNumOperations_.end()) {
        num2 = valuesStack_.Top().value_;
      } else {
        if (valuesStack_.Size() > 1) {
          num1 = valuesStack_.End().operator-(2).base()->value_;
          num2 = valuesStack_.End().operator-(1).base()->value_;
          valuesStack_.PopBack();
        } else {
          throw std::out_of_range("Error calculation!");
        }
      }
      FunctionPerformer(num1, num2, down_oper);
    }
  }
  return make_operations;
}

void Model::FunctionPerformer(double num1, double num2, Node *down_oper) {
  if (down_oper->operation_.begin()->first == "+") {
    valuesStack_.End().operator-(1).base()->value_ = num1 + num2;
  } else if (down_oper->operation_.begin()->first == "-") {
    valuesStack_.End().operator-(1).base()->value_ = num1 - num2;
  } else if (down_oper->operation_.begin()->first == "/") {
    valuesStack_.End().operator-(1).base()->value_ = num1 / num2;
  } else if (down_oper->operation_.begin()->first == "*") {
    valuesStack_.End().operator-(1).base()->value_ = num1 * num2;
  } else if (down_oper->operation_.begin()->first == "^") {
    valuesStack_.End().operator-(1).base()->value_ = pow(num1, num2);
  } else if (down_oper->operation_.begin()->first == "%") {
    valuesStack_.End().operator-(1).base()->value_ = fmod(num1, num2);
  } else if (down_oper->operation_.begin()->first == "cos") {
    valuesStack_.End().operator-(1).base()->value_ = cos(num2);
  } else if (down_oper->operation_.begin()->first == "sin") {
    valuesStack_.End().operator-(1).base()->value_ = sin(num2);
  } else if (down_oper->operation_.begin()->first == "tan") {
    valuesStack_.End().operator-(1).base()->value_ = tan(num2);
  } else if (down_oper->operation_.begin()->first == "acos") {
    valuesStack_.End().operator-(1).base()->value_ = acos(num2);
  } else if (down_oper->operation_.begin()->first == "asin") {
    valuesStack_.End().operator-(1).base()->value_ = asin(num2);
  } else if (down_oper->operation_.begin()->first == "atan") {
    valuesStack_.End().operator-(1).base()->value_ = atan(num2);
  } else if (down_oper->operation_.begin()->first == "sqrt") {
    valuesStack_.End().operator-(1).base()->value_ = sqrt(num2);
  } else if (down_oper->operation_.begin()->first == "ln") {
    valuesStack_.End().operator-(1).base()->value_ = log10(num2);
  } else if (down_oper->operation_.begin()->first == "log") {
    valuesStack_.End().operator-(1).base()->value_ = log(num2);
  }
}

bool Model::DataVerifier(std::string str, int i) {
  string prev_oper;
  string curr_oper;

  bool start = false;
  if (!str.empty()) {
    prev_oper = LocateOperation(&str[0]);
    curr_oper = LocateOperation(&str[prev_oper.size()]);
    if (!prev_oper.empty() && !curr_oper.empty()) {
      if ((HasElement(p_m_oper, prev_oper) &&
           HasElement(left_scobe, curr_oper)) ||
          (HasElement(p_m_oper, prev_oper) && HasElement(func, curr_oper)) ||
          (HasElement(left_scobe, prev_oper) && HasElement(func, curr_oper)) ||
          (HasElement(func, prev_oper) && HasElement(left_scobe, curr_oper)) ||
          (HasElement(left_scobe, prev_oper) &&
           HasElement(left_scobe, curr_oper)) ||
          (HasElement(left_scobe, prev_oper) &&
           HasElement(p_m_oper, curr_oper))) {
        start = true;
      }
    } else if (!prev_oper.empty() && curr_oper.empty()) {
      if (HasElement(p_m_oper, prev_oper) ||
          HasElement(left_scobe, prev_oper)) {
        start = true;
      }
    } else if (prev_oper.empty()) {
      start = true;
    }
  }

  bool mid = true;
  if (!str.empty() && str.size() > 1 && i < int((str.size() - 1)) && i > 0) {
    curr_oper = LocateOperation(&str[i]);
    prev_oper = LocateOperation(&str[i - 1]);
    if (!curr_oper.empty() && !prev_oper.empty()) {
      if ((HasElement(oper, prev_oper) && HasElement(right_scobe, curr_oper)) ||
          (HasElement(left_scobe, prev_oper) &&
           HasElement(other_oper, curr_oper)) ||
          (HasElement(other_oper, prev_oper) &&
           HasElement(other_oper, curr_oper)) ||
          (HasElement(p_m_oper, prev_oper) &&
           HasElement(other_oper, curr_oper)) ||
          (HasElement(right_scobe, prev_oper) &&
           HasElement(left_scobe, curr_oper))) {
        mid = false;
      }
    }
  }

  if (!str.empty()) {
    for (size_t j = 0; j < str.size(); j++) {
      prev_oper = LocateOperation(&str[j]);
      if ((j + prev_oper.size()) < str.size()) {
        curr_oper = LocateOperation(&str[j + prev_oper.size()]);
      } else {
        break;
      }
      if (!curr_oper.empty() && !prev_oper.empty()) {
        if (HasElement(left_scobe, prev_oper) &&
            HasElement(right_scobe, curr_oper)) {
          mid = false;
          break;
        }
      }
    }
  }

  bool end = true;
  curr_oper = LocateOperation(&str[str.size() - 1]);
  if (!curr_oper.empty()) {
    if (!HasElement(right_scobe, curr_oper)) {
      end = false;
    }
  }

  return (start && mid && end) ? true : false;
}

bool Model::HasElement(std::vector<string> vec, std::string oper) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec.at(i) == oper) {
      return true;
    }
  }
  return false;
}

size_t Model::IgnoreValue(std::string str) {
  int dot = 0;
  size_t step = 0;
  for (char c : str) {
    if (isdigit(c) || c == '.') {
      if (c == '.') {
        dot++;
      }
    } else {
      break;
    }
    step++;
  }
  if (dot > 1) {
    throw std::out_of_range("Error calculation!");
  }
  return step;
}

std::string Model::LocateOperation(std::string str) {
  std::string operation;
  for (int i = 0; i < 4; i++) {
    operation += str[i];
    std::map<std::string, int>::const_iterator it =
        priorityTable_.find(operation);
    if (it != priorityTable_.end()) {
      return operation;
    }
  }
  operation.clear();
  return operation;
}

void Model::Clear() {
  valuesStack_.Clear();
  operationsStack_.Clear();
}

void Model::Concat(std::string *lineEdit, const std::string src) {
  if (!lineEdit->empty()) {
    char c = lineEdit->back();
    string oper;
    oper.append({c});
    if (src == "+" || src == "-") {
      if (worksWithUnary_.find(string(oper)) != worksWithUnary_.end()) {
        lineEdit->append("(");
      }
    }
  }
  if (src == ".") {
    if (lineEdit->empty() ||
        (!lineEdit->empty() && !isdigit(lineEdit->back()))) {
      return;
    }
  }
  lineEdit->append(src);
}