/*
  ==============================================================================

    LoadingBar.cpp
    Created: 5 May 2026 4:29:25pm
    Author:  jm

  ==============================================================================
*/

#include "LoadingBar.h"
#include <iostream>

LoadingBar::LoadingBar(const long minVal, const long maxVal, const long currVal)
: minVal {minVal}, maxVal {maxVal}, currVal {currVal}, progress {0} {}


LoadingBar::LoadingBar(const long minVal, const long maxVal)
: LoadingBar {minVal, maxVal, 0} {}

LoadingBar::LoadingBar() : LoadingBar {0, 100} {}

void LoadingBar::print() {
  
  stringstr.str("");
  stringstr.clear();

  stringstr << "\r[";
  for (int i = 0; i < 100; i++) {
    if (i < progress) {
      stringstr << "#";
    } else {
      stringstr << "-";
    }
  }
  stringstr << "] " << progress << "%";
  std::cout << stringstr.str() << std::flush;
}

void LoadingBar::setProgress(const int val) {
  progress = val;
}

int LoadingBar::getProgress() const {
  return progress;
}

void LoadingBar::setCurrVal(const long val) {
  currVal = val;
}

long LoadingBar::getCurrVal() const {
  return currVal;
}

void LoadingBar::update() {
  progress = (double)(currVal / (double)(maxVal - minVal)) * 100;
}