#define VIDEO_PATH_LENGTH 50
#define VIDEO_TYPE_LENGTH 20

typedef struct VIDEO_STRUCT
{
  char type[20];
  char path[50];
  int has_audio;
} Video;
