#include <opencv4/opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <unistd.h>
#include <cerrno>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "include/pins.h"

// PINS
#define LED 1
#define BUZZER 2
#define WHITE_BUTTON 3
#define YELLOW_BUTTON 4
#define RED_BUTTON 5
#define BLUE_BUTTON 6
#define GREEN_BUTTON 7

#define INPUT 0
#define OUTPUT 1

using namespace std;
using namespace cv;


const char MAIN_ANIM_PATH[] = "videos/loop.mp4";

uint8_t GIF_REPEAT = 5;

int popen(int pin_n);
int pinMode(int pin_n, int mode);
int pclose(int pin_n);


int main(int argc, char **argv)
{
  cout << endl << "===============================";
  cout << endl << "BEGINNING OF THE GIFFER PROGRAM";
  cout << endl << "===============================" << endl << endl;

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, INPUT);
  pinMode(WHITE_BUTTON, INPUT);
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(BLUE_BUTTON, INPUT);


  return EXIT_SUCCESS;
}