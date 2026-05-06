/*
  ==============================================================================

    File.h
    Created: 6 May 2026 10:43:36am
    Author:  jm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>
#include <memory>
#include <string>

int writeFile(std::vector<float>& outputSamples, double sampleRate);
std::unique_ptr<juce::AudioFormatReader> loadFile(std::string& filePath, juce::AudioFormatManager& aManager);
void normalizeSamples(std::vector<float>& samples);
