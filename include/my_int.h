#pragma once

#include "logsloth.h"

class MyInt {
 public:
  int _i;

  MyInt() {
    LOGSLOTH("MyInt()");
  }

  MyInt(int i) {
    _i = i;
    LOGSLOTH("MyInt() _i:%d", _i);
  }

  ~MyInt() {
    LOGSLOTH("~MyInt() _i:%d", _i);
  }
};

