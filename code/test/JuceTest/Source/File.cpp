/*
  ==============================================================================

    File.cpp
    Created: 6 May 2026 10:43:36am
    Author:  jm

  ==============================================================================
*/

#include "File.h"
#include <iostream>

int writeFile(std::vector<float>& outputSamples, double sampleRate) {

  juce::File outputFile {juce::File::getCurrentWorkingDirectory().getChildFile("ErgebnisDirekteFaltung.wav")};
  if (outputFile.exists()) {
    outputFile.deleteFile();
  }

  juce::WavAudioFormat wavFormat {};
  std::unique_ptr<juce::OutputStream> os {outputFile.createOutputStream()};

  if (os == nullptr) {
    std::cerr << "Error creating OutputStream!\n";
    return -1;
  }

  juce::AudioFormatWriterOptions options {};
  options = options.withSampleRate(sampleRate)
                   .withNumChannels(1)
                   .withBitsPerSample(16);

  std::unique_ptr<juce::AudioFormatWriter> writer { wavFormat.createWriterFor(
    os,
    options
  ) };

  if (writer == nullptr) {
    std::cerr << "Error creating File writer!" << std::endl;
    return -1; 
  }

  std::cout << "Normalisiere Ausgangssignal ..." << std::endl;
  normalizeSamples(outputSamples);

  float* channelPtr[] {outputSamples.data()};
  writer->writeFromFloatArrays(channelPtr, 1, (int)outputSamples.size());


  return 0;
}

std::unique_ptr<juce::AudioFormatReader> loadFile(std::string& filePath, juce::AudioFormatManager& aManager) {

  juce::File file {juce::File::getCurrentWorkingDirectory().getChildFile(filePath)};
  if (!file.exists()) {
    return nullptr;
  }

  return std::unique_ptr<juce::AudioFormatReader> (aManager.createReaderFor(file));
}

void normalizeSamples(std::vector<float>& samples) {

  float maxVal = 0.0f;
  for (float& sample : samples) {
    maxVal = maxVal < std::abs(sample) ? std::abs(sample) : maxVal;
  }

  if (maxVal > 1.0f) {
    for (float& sample : samples) {
      sample = sample / maxVal;
    }
  }
}