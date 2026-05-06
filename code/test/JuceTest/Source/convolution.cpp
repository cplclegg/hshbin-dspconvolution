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
#include "LoadingBar.h"
#include "File.h"

//==============================================================================


std::vector<float> convolution(std::vector<float>& input, std::vector<float>& ir) {

  unsigned long inputLen {input.size()};
  unsigned long irLen {ir.size()};
  unsigned long outputLen {inputLen + irLen - 1};

  std::vector<float> output (outputLen, 0.0f); //<-- Initialisiere vector mit der Pufferlaenge = outputLen und 0.0f als Initialwerte

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
      inputFilePath = "guitar_02.wav";
      irFilePath = "impResp2.wav";
    } else {
      inputFilePath = argv[1];
      irFilePath = argv[2];
    }

    std::unique_ptr<juce::AudioFormatReader> inputReader {loadFile(inputFilePath, formatManager)};
    std::unique_ptr<juce::AudioFormatReader> irReader {loadFile(irFilePath, formatManager)};
    if (inputReader == nullptr) {
      std::cerr << "Fehler: Input Reader konnte nicht initialisiert werden!" << std::endl;
      return -1;
    }
    if (irReader == nullptr) {
      std::cerr << "Fehler: IR Reader konnte nicht initialisiert werden!" << std::endl;
      return -1;
    }
    
    // Folge des Eingangssignals laden
    int inputSignalSampleLen {(int)inputReader->lengthInSamples};
    std::vector<float> inputSamples (inputSignalSampleLen);
    float* channelInputPointers[] {inputSamples.data()};
    inputReader->read(channelInputPointers, 1, 0, inputSignalSampleLen);

       std::cout << "Eingangssignal geladen! Anzahl Samples: " << inputSignalSampleLen << std::endl;

    //Folge der Impulsantwort laden
    int irSignalSampleLen {(int)irReader->lengthInSamples};
    std::vector<float> irSamples (irSignalSampleLen);
    float* channelIRPointers[] {irSamples.data()};
    irReader->read(channelIRPointers, 1, 0, irSignalSampleLen);

    std::cout << "Impulsantwort geladen! Anzahl Samples: " << irSignalSampleLen << std::endl;
    
    //Wende direkte Faltung in Zeitdomaene an
    std::vector<float> output (convolution(inputSamples, irSamples));

    //Schreibe Ergebnis zurueck ins Dateisystem
    if (writeFile(output, inputReader->sampleRate) == 0) {
      std::cout << "Output File created successfully!" << std::endl;

    } else {
      std::cerr << "Error creating output file!" << std::endl;
      return -1;
    }

    return 0;
}