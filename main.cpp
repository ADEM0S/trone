#include <opencv4/opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <unistd.h>
#include <cerrno>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "include/video.h"
#include "include/pins.h"
#include "include/dynamic_array.h"
#include "include/video_manipulation.hpp"


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


int main(int argc, char **argv)
{
  cout << endl << "===============================";
  cout << endl << "BEGINNING OF THE GIFFER PROGRAM";
  cout << endl << "===============================" << endl << endl;


  popen(LED);
  popen(BUZZER);
  popen(WHITE_BUTTON);
  popen(YELLOW_BUTTON);
  popen(RED_BUTTON);
  popen(BLUE_BUTTON);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, INPUT);
  pinMode(WHITE_BUTTON, INPUT);
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(BLUE_BUTTON, INPUT);


  

  DynArray vids_list;
  DynArray *vids_list_ptr = &vids_list;
  init_array(vids_list_ptr, 1);
  int length = read_structs(vids_list_ptr);

  int led_state, buss_state, white_state, yellow_state, \
        red_state, blue_state, green_state;

  int f_count = 0;
  
  while (1)
  {
    VideoCapture cap(MAIN_ANIM_PATH); // TO BE CHANGED
    if (!cap.isOpened()) break;
    
    namedWindow(MAIN_WIN_NAME, WINDOW_NORMAL);
    setWindowProperty(MAIN_WIN_NAME, WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
    
    while (1)
    {
      Mat frame;
      cap >> frame;
      f_count++;
      imshow(MAIN_WIN_NAME, frame);
      
      if (f_count == (int)cap.get(CAP_PROP_FRAME_COUNT))
      {
        f_count = 0;
        cap.set(CAP_PROP_POS_FRAMES, f_count);
      }
      
      handle_pins();
      
      char c = (char) waitKey(50);
      if (c == 27)
      {
        // destroy the Mainloop window
        destroyWindow(MAIN_WIN_NAME);
        
        char *type = NULL;
        strcpy(type, "drink");
        
        if (play_random_video(GIF_REPEAT, vids_list_ptr, type) == -1)
        {
          cout << "Error playing random video." << endl;
          return EXIT_FAILURE;
        }
        break; // goes to the mainloop initiation
      }
    }
  }
  
  destroyAllWindows();

  pclose(LED);
  pclose(BUZZER);
  pclose(WHITE_BUTTON);
  pclose(YELLOW_BUTTON);
  pclose(RED_BUTTON);
  pclose(BLUE_BUTTON);


  return EXIT_SUCCESS;
}
