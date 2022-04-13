#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stack>

std::string input;
std::string output;
std::string nl = "\n";  // newline
std::string g_s = " ";  // space
int idt = 0;  // indentation
int idx = 0;
std::stack<std::pair<std::string, bool>> brackets;  // {


bool isKey(std::string s) {
  return s == "for" || s == "while" || s == "if" || s == "else";
}

void ignoreS() {
  while(input[idx] == ' ') idx++;
}

std::string Idt(int i) {
  std::string s;
  while(i--) s += "  ";
  return s;
}

bool is_bracket() {
  int j = idx;
  while(input[j] == ' ') j++;
  return input[j] == '{';
}

void add_bracket() {  // add '}'
  ignoreS();
  while(!brackets.empty() && brackets.top().second == false) {
    std::string l = brackets.top().first;
    brackets.pop();
    idt--;
    output += Idt(idt) + '}';
    if (!is_bracket()) output += nl;
    if (input.size() - idx >= 4 && l == "if" && input.substr(idx, 4) == "else") break;
  }
}

void solvekey(std::string s) {
  ignoreS();
  output += g_s;
  if (s != "else") {
    int little_b = 0;
    output += input[idx++];
    while (input[idx] != ')' || little_b) {
      if (input[idx] == '(') little_b++;
      if (input[idx] == ')') little_b--;
      output += input[idx++];
    }
    output += input[idx++];
    output += g_s;
    ignoreS();
  }
  if (input[idx] != '{') {
    brackets.push(std::make_pair(s, false));
  } else {
    brackets.push(std::make_pair(s, true));
    idx++;
  }
  idt++;
  output += '{';
  ignoreS();
  if (!is_bracket()) output += nl;
}

void run() {
  ignoreS();
  while(idx < input.size()) {
    if (isalpha(input[idx]) || input[idx] == '_' || input[idx] == '*' || input[idx] == '-' || input[idx] == '+') {
      int i = idx;
      while(isalnum(input[idx]) || input[idx] == '_' || input[idx] == '*' || input[idx] == '-' || input[idx] == '+') idx++;
      output += Idt(idt) + input.substr(i, idx - i);
      if (isKey(input.substr(i, idx - i))) solvekey(input.substr(i, idx - i));
    } else {
      while (idx < input.size()) {
        if (input[idx] == '{') {
          output += nl + Idt(idt) + input[idx++];
          if (!is_bracket()) output += nl;
          idt++;
          brackets.push(std::make_pair("", true));
          ignoreS();
          break;
        } else if (input[idx] == '}') {
          add_bracket();
          idt--;
          output += Idt(idt) + input[idx++];
          if (!is_bracket()) output += nl;
          brackets.pop();
          ignoreS();
          if (idx == input.size()) output[output.size() - 1] = '\0';
          add_bracket();
          break;
        } else if (input[idx] == '(') {
          output += input[idx++];
          while (input[idx] != ')') output += input[idx++];
          output += input[idx++];
          // if (is_bracket()) ignoreS();  // NOTICE: '{'
          ignoreS();
          break;
        } else if (input[idx] == '"' || input[idx] == '\'') {
          char symbol = input[idx];
          output += input[idx++];
          while (input[idx] != symbol || input[idx - 1] == '\\') output += input[idx++];
          output += input[idx++];
          break;
        } else if (input[idx] == ';') {
          output += input[idx++];
          if (!is_bracket()) output += nl;
          ignoreS();
          add_bracket();
          break;
        } else {
          output += input[idx++];
        }
      }
    }
  }
}

int main() {
  std::getline(std::cin, input);
  run();
  std::cout << output << std::endl;
  return 0;
}
