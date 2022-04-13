#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::isalpha;
using std::isalnum;

std::string input;
std::string output;
std::string newline = "\n";
std::string g_space = " ";
int indentation = 0;
int idx = 0;
bool is_newline = true;
std::vector<std::string> stack;
int is_else = 0;

std::string Space(int c) {
  std::string s;
  for (int i = 0; i < c; i++)
    s += "  ";
  return s;
}

bool isKey(std::string s) {
  return s == "for" || s == "while" || s == "if" || s == "else";
}

void ignoreSpace() {
  while(idx < input.size() && input[idx] == ' ') idx++;
}

void solveKey(std::string s) {
  output += g_space;
  ignoreSpace();
  if (s != "else") {
    while (input[idx] != ')') {
      output += input[idx++];
    }
    output += input[idx++];
    output += g_space;
    ignoreSpace();
  }
  if (input[idx] != '{') {
    stack.push_back(s);
    output += '{' + newline;
  }
  else {
    idx++;
    if (s != "else") is_else++;
    if (input[idx] == '{') output += '{';
    else output += '{' + newline;
  }
  indentation++;
  ignoreSpace();
}

void run() {
  std::string temp;
  ignoreSpace();
  while (idx < input.size()) {
    if (isalpha(input[idx]) || input[idx] == '_') {
      int i = idx;
      while(isalnum(input[idx]) || input[idx] == '_') {
        idx++;
      }
      output += Space(indentation) + input.substr(i, idx - i);
      if (isKey(input.substr(i, idx - i))) {
        solveKey(input.substr(i, idx - i));
      }
    } else {
      while (idx < input.size()) {
        if (input[idx] == '{') {
          if (is_newline) {
            output += newline;
          }
          is_newline = true;
          output += Space(indentation) + input[idx] + newline;
          indentation++;
          idx++;
          ignoreSpace();
          if (input[idx] == '{') is_newline = false;
          break;
        } else if (input[idx] == '}') {
          indentation--;
          output += Space(indentation) + input[idx];
          idx++;
          ignoreSpace();
          if (input[idx] != '{') output += newline;
          if (idx == input.size()) output[output.size() - 1] = '\0';
          if (is_else) is_else--;
          if (!stack.empty() && input.substr(idx, 4) == "else" && stack.back() == "if") {
            stack.pop_back();
            indentation--;
            output += Space(indentation) + "}" + newline;
          }
          break;
        } else if (input[idx] == ';') {
          output += input[idx] + newline;
          idx++;
          while(is_else == 0 && !stack.empty()) {
            ignoreSpace();
            indentation--;
            output += Space(indentation) + "}";
            if (input[idx] != '{') output += newline;
            std::string last = stack.back();
            stack.pop_back();
            if (last == "if" && input.substr(idx, 4) == "else") break;
          }
          break;
        } else if (input[idx] == '"') {
          output += input[idx++];
          while (input[idx] != '"' || input[idx - 1] == '\\') {
            output += input[idx++];
          }
          output += input[idx++];
        } else {
          output += input[idx++];
          if (input[idx - 1] == ')') {
            int j = idx;
            while (input[j] == ' ') j++;
            if (input[j] == '{')
              ignoreSpace();
          }
        }
      }
      ignoreSpace();
    }
  }
}

int main() {
  std::getline(std::cin, input);
  run();
  std::cout << output << std::endl;
  return 0;
}
