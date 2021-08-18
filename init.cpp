#include <iostream>
#include <string.h>
#include "include/video.h"

using namespace std;

#define VIDEO_FORMAT_OUT "(%s, %s, %d)\n"
#define LEN_FORMAT_OUT "length : %d\n"
#define FFMPEG_CMD_FORMAT "ffmpeg -y -i %s.mp4 %s.mp3"
#define CMD_LENGTH (23 + 2*VIDEO_PATH_LENGTH)



int serialize(const char *path, Video videos_list[], int list_size);
int init_mp3(Video videos_list[], int list_size);

int main(int argc, char** argv)
{
  cout << endl << "Beginning of the process." << endl;

  cout << endl << "======== Init of the GIFs structs ========" << endl;

  Video afond_jack = {"drink", "videos/random_gif/drink/afond_jack.mp4", 0};
  Video dancing_solo_girl = {"drink", "videos/random_gif/drink/dancing_solo_girl.mp4", 0};
  Video dicaprio = {"drink", "videos/random_gif/drink/dicaprio.mp4", 0};
  Video dj_khaled = {"drink", "videos/random_gif/drink/dj_khaled.mp4", 0};
  Video jump_shot = {"drink", "videos/random_gif/drink/jump_shot.mp4", 0};
  Video lannister = {"drink", "videos/random_gif/drink/lannister.mp4", 0};
  Video laugh = {"drink", "videos/random_gif/drink/laugh.mp4", 0};
  Video random_anim = {"drink", "videos/random_gif/drink/random_anim.mp4", 0};
  Video wine_girl = {"drink", "videos/random_gif/drink/wine_girl.mp4", 0};
  Video wwe = {"drink", "videos/random_gif/drink/WWE.mp4", 0};

  Video coffin = {"coffin", "videos/random_gif/coffin/minecraft_coffin.mp4", 0};

  Video mainloop = {"mainloop", "videos/mainloop.mp4", 0};

  Video aglou = {"miscelleanous", "videos/vids/aglou.mp4", 1};
  Video baise = {"miscelleanous", "videos/vids/BAISE.mp4", 1};
  Video raf = {"miscelleanous", "videos/vids/RienAFoutre.mp4", 1};
  Video sasageyo = {"miscelleanous", "videos/vids/sasageyo.mp4", 1};

  Video point_pour_le_mamouth = {"point", "videos/point/point_pour_le_mamouth.mp4", 1};



  Video videos_list[] = {  mainloop, \
                                afond_jack, dancing_solo_girl, dicaprio, dj_khaled, jump_shot, lannister, laugh, random_anim, wine_girl, wwe, \
                                coffin, \
                                point_pour_le_mamouth, \
                                aglou, baise, raf, sasageyo \
                              };

  cout << "=> OK" << endl;


  cout << endl << "======== Random drink GIFs Serialization ========" << endl;

  size_t list_size = sizeof(videos_list)/sizeof(videos_list[0]);

  if (serialize("assets/video_structs.dat", videos_list, list_size) != 0)
  {
    cout << "=> GONE WRONG !!" << endl << "Exiting the program." << endl;
    return 1;
  }
  cout << "=> OK" << endl;



  list_size = sizeof(videos_list)/sizeof(videos_list[0]);

  cout << endl << "======== Init MP3s files ========" << endl;

  if (init_mp3(videos_list, list_size) != 0)
  {
    cout << "=> GONE WRONG !!" << endl << "Exiting the program." << endl;
    return 1;
  }
  cout << "=> OK" << endl;


  cout << endl << "======== End of the process ========" << endl << endl;
  return 0;
}

int serialize(const char *path, Video videos_list[], int list_size)
{

  FILE* fptr;
  fptr = fopen(path, "w");
  if (fptr == NULL)
  {
    cout << "Error opening the file : "<< path << "." << endl;
    return 0;
  }

  fprintf(fptr, LEN_FORMAT_OUT, list_size);

  for (int i = 0; i < list_size; i++)
  {
    fprintf(fptr, VIDEO_FORMAT_OUT, videos_list[i].type, videos_list[i].path, videos_list[i].has_audio);
  }

  if (fclose(fptr) != 0)
  {
    cout << "Error closing the file." << endl;
    return 0;
  }

  return 0;
}

char *str_trim_extention(char *path)
{
  char *ret = (char*) malloc( (VIDEO_PATH_LENGTH+1) * sizeof(char) );

  int length = strlen(path) - 4;

  for (int i = 0; i < length; i++)
  {
    printf("%c", path[i]);
    ret[i] = path[i];
  }
  ret[length] = '\0';
  return ret;
}


int init_mp3(Video videos_list[], int list_size)
{
  for (int i = 0; i < list_size; i++)
  {
    if (videos_list[i].has_audio == 1)
    {
      char *trimmed_path = str_trim_extention(videos_list[i].path);

      char *cmd = (char *) malloc(CMD_LENGTH * sizeof(char));
      sprintf(cmd, FFMPEG_CMD_FORMAT, trimmed_path, trimmed_path);

      FILE *fp = popen(cmd, "r");
      if (fp == NULL)
      {
        printf("Error while popen.\n");
        return EXIT_FAILURE;
      }
      free(cmd);
      free(trimmed_path);
      fclose(fp);
    }
  }

  return 0;
}
