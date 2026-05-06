/*
  ==============================================================================

    LoadingBar.h
    Created: 5 May 2026 4:29:25pm
    Author:  jm

  ==============================================================================
*/

#pragma once
#include <sstream>

class LoadingBar {

  private:
    int progress;
    long maxVal;
    long minVal;
    long currVal;
    std::stringstream stringstr {};

    public:
    LoadingBar(const long minVal, const long maxVal, const long currVal);
    LoadingBar(const long minVal, const long maxVal);
    LoadingBar();
    void print();
    void setProgress(const int val);
    int getProgress() const;
    void setCurrVal(const long val);
    long getCurrVal() const;
    void update();
};
