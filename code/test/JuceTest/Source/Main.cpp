/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

//==============================================================================

int writeFile(std::vector<float>& outputSamples, double sampleRate) {

  juce::File outputFile {juce::File::getCurrentWorkingDirectory().getChildFile("ErgebnisDirekteFaltung.wav")};
  if (outputFile.exists()) {
    outputFile.deleteFile();
  }

  juce::WavAudioFormat wavFormat {};
  std::unique_ptr<juce::FileOutputStream> fos {outputFile.createOutputStream()};
  std::unique_ptr<juce::OutputStream> os {fos.get()};

  juce::AudioFormatWriterOptions options {};
  options = options.withSampleRate(sampleRate)
                   .withNumChannels(0)
                   .withBitsPerSample(16);

  std::unique_ptr<juce::AudioFormatWriter> writer { wavFormat.createWriterFor(
    os,
    options
  ) };

  if (writer == nullptr) {
    std::cerr << "Error creating File writer!" << std::endl;
    return -1; 
  }

  float* channelPtr[] {outputSamples.data()};
  juce::AudioBuffer<float> outputBuffer (channelPtr, 1, 0,  (int)outputSamples.size());
  

  return 0;
}

std::vector<float> convolution(std::vector<float>& input, std::vector<float>& ir) {

  unsigned long inputLen {input.size()};
  unsigned long irLen {ir.size()};
  unsigned long outputLen {inputLen + irLen - 1};

  std::vector<float> output (outputLen, 0.0f); //<-- Initialisiere vector mit der Pufferlänge = outputLen und 0.0f als Werte

  for (int i = 0; i < outputLen; i++) {
    for (int k = 0; k < irLen; k++) {
      if (i - k < 0 || inputLen <= i - k) {
        continue;
      }
      output[i] += ir[k] * input[i - k];
    }
  }

  return output;
}

int main (int argc, char* argv[])
{

    //Audioformate initialisieren
    juce::AudioFormatManager formatManager {};
    formatManager.registerBasicFormats();

    std::string inputFilePath {};
    std::string irFilePath {};

    if (argc < 3) {
      inputFilePath = "testInput.wav";
      irFilePath = "testIRPath";
    } else {
      inputFilePath = argv[1];
      irFilePath = argv[2];
    }

    juce::File inputFile {inputFilePath};
    juce::File irFile {irFilePath};

    if (!inputFile.exists()) {
      std::cerr << "Error: File " << inputFilePath <<  " is not existing!" << std::endl;
      return -1;
    }
    if (!irFile.exists()) {
      std::cerr << "Error: File " << irFilePath << " is not existing!" << std::endl;
      return -1;
    }

    std::unique_ptr<juce::AudioFormatReader> inputReader {formatManager.createReaderFor(inputFile)};
    std::unique_ptr<juce::AudioFormatReader> irReader {formatManager.createReaderFor(irFile)};
    if (inputReader == nullptr) {
      std::cerr << "Fehler: Input Reader konnte nicht initialisiert werden!" << std::endl;
      return -1;
    }
    if (irReader == nullptr) {
      std::cerr << "Fehler: IR Reader konnte nicht initialisiert werden!" << std::endl;
    }
    
    // Folge des Eingangssignals laden
    int inputSignalSampleLen {(int)inputReader->lengthInSamples};
    std::vector<float> inputSamples {};
    float* channelInputPointers[] {inputSamples.data()};
    inputReader->read(channelInputPointers, 1, 0, inputSignalSampleLen);

       std::cout << "Eingangssignal geladen! Anzahl Samples: " << inputSignalSampleLen << std::endl;

    //Folge der Impulsantwort laden
    int irSignalSampleLen {(int)irReader->lengthInSamples};
    std::vector<float> irSamples {};
    float* channelIRPointers[] {irSamples.data()};
    irReader->read(channelIRPointers, 1, 0, irSignalSampleLen);

    std::cout << "Impulsantwort geladen! Anzahl Samples: " << irSignalSampleLen << std::endl;
    
    //Wende direkte Faltung in Zeitdomäne an
    std::vector<float> output (convolution(inputSamples, irSamples));

    //Schreibe Ergebnis zurück ins Dateisystem
    if (writeFile(output, inputReader->sampleRate) == 0) {
      std::cout << "Output File created successfully!" << std::endl;

    } else {
      std::cerr << "Error creating output file!" << std::endl;
      return -1;
    }

    return 0;
}