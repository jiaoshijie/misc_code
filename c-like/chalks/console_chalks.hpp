#pragma once
#include <iostream>
#include <string>

namespace chalks {
  namespace fg_colors {
    /* normal color */
    constexpr const char *block = "\033[30m";
    constexpr const char *red = "\033[31m";
    constexpr const char *green = "\033[32m";
    constexpr const char *yellow = "\033[33m";
    constexpr const char *blue = "\033[34m";
    constexpr const char *purple = "\033[35m";
    constexpr const char *cyan = "\033[36m";
    constexpr const char *gray = "\033[37m";
    /* bright color */
    constexpr const char *bblock = "\033[90m";
    constexpr const char *bred = "\033[91m";
    constexpr const char *bgreen = "\033[92m";
    constexpr const char *byellow = "\033[93m";
    constexpr const char *bblue = "\033[94m";
    constexpr const char *bpurple = "\033[95m";
    constexpr const char *bcyan = "\033[96m";
    constexpr const char *bgray = "\033[97m";

    inline void showAllColors() {
      for (int i = 30; i < 38; i++)
        printf("\033[%dmNormal Color%d\n\033[%dmBright Color%d\n",\
            i, i, i + 60, i + 60);
    }
  }
  namespace reset {
    constexpr const char *textColor = "\033[0m";  // reset all color(bg and fg)
    constexpr const char *tc = textColor;  // abbreviation
    constexpr const char *textStyle = "\033[;0m";  // reset text sytle
    constexpr const char *ts = textStyle;
  }
  namespace bg_colors {
    /* normal color */
    constexpr const char *block = "\033[40m";
    constexpr const char *red = "\033[41m";
    constexpr const char *green = "\033[42m";
    constexpr const char *yellow = "\033[43m";
    constexpr const char *blue = "\033[44m";
    constexpr const char *purple = "\033[45m";
    constexpr const char *cyan = "\033[46m";
    constexpr const char *gray = "\033[47m";
    /* bright color */
    constexpr const char *bblock = "\033[100m";
    constexpr const char *bred = "\033[101m";
    constexpr const char *bgreen = "\033[102m";
    constexpr const char *byellow = "\033[103m";
    constexpr const char *bblue = "\033[104m";
    constexpr const char *bpurple = "\033[105m";
    constexpr const char *bcyan = "\033[106m";
    constexpr const char *bgray = "\033[107m";

    inline void showAllColors() {
      for (int i = 40; i < 48; i++)
        printf("\033[%dmNormal Color%d\033[0m\n\033[%dmBright Color%d\033[0m\n",\
            i, i, i + 60, i + 60);
    }
  }
  namespace textStyle {
    constexpr const char *bold = "\033[;1m";
    constexpr const char *light = "\033[;2m";
    constexpr const char *italcs = "\033[;3m";
    constexpr const char *underline = "\033[;4m";
    constexpr const char *blink = "\033[;5m";
    // constexpr const char *Blink = "\033[;6m";
    constexpr const char *reverse = "\033[;7m";
    constexpr const char *hide = "\033[;8m";
    constexpr const char *deleteline = "\033[;9m";

    inline void showAlltextStyle() {
      for(int i = 0; i < 10; i++) {
        if (i == 6) continue;
        printf("\033[;%dm style%d\n\033[0m", i, i);
      }
    }
  }
  namespace _256colors {
    /* 256 colors */
    inline std::string colors(std::string color) {
      std::string prefix = "\033[38;5;", suffix = "m";
      return prefix + color + suffix;
    }

    inline void showAll256Color() {
      for (int i = 0; i < 256; i++) {
        printf("\033[38;5;%dm color%d\n", i, i);
      }
    }
  }
  inline void printColors(const char* color, std::string str, bool is_newline = false) {
    std::cout << color << str << reset::tc;
    if (is_newline) std::cout << std::endl;
  }
}
