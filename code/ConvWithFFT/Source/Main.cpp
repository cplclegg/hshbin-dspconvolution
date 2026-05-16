/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include <string>
#include <memory>
#include <vector>
#include <complex>

//==============================================================================
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

int main (int argc, char* argv[])
{

    juce::AudioFormatManager aFormManager {};
    aFormManager.registerBasicFormats();

    std::string inputFile {"guitar_02.wav"};
    std::string impulseFile {"ImpResp.wav"};

    std::unique_ptr<AudioFormatReader> inputReader {loadFile(inputFile, aFormManager)};
    std::unique_ptr<AudioFormatReader> impulseReader {loadFile(impulseFile, aFormManager)};
    long inputSampleCount {(long)inputReader->lengthInSamples};
    long impulseSampleCount {(long)impulseReader->lengthInSamples};
    std::vector<float> inputSamples (inputSampleCount);
    std::vector<float> impulseSamples (impulseSampleCount);
    float* channelInputPtrs[] {inputSamples.data()};
    float* channelImpulsePtrs[] {impulseSamples.data()};

    inputReader->read(channelInputPtrs, 1, 0, inputSampleCount);
    impulseReader->read(channelImpulsePtrs, 1, 0, impulseSampleCount);

    std::cout << "Input signal: " << inputSampleCount << " samples" << std::endl;
    std::cout << "Impulse signal: " << impulseSampleCount << " samples" << std::endl;

    

    return 0;
}

void convolute
