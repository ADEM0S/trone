#define MAIN_WIN_NAME "Main Window"

using namespace cv;

int get_structs_length(FILE *fptr)
{
	int length = 0;
	fscanf(fptr, "length : %d\n", &length);
	return length;
}

void fill_dynarray_from_file(FILE *fptr, DynArray *videos_list)
{
	Video temp;
	
	for (int i = 0; i < videos_list->size; i++)
	{
		fscanf(fptr, "(%[^,], %[^,])", temp.path, temp.type);
		insert_array(videos_list, temp);
	}
}

int read_structs(DynArray *videos_list)
{
	FILE *fptr = fopen("assets/structs.dat", "r");
	
	if (fptr == NULL) return 0;
	
	int length = get_structs_length(fptr);
	
	fill_dynarray_from_file(fptr, videos_list);
	
	fclose(fptr);
	return length;
}

void fill_videos_list_by_type(DynArray *good_type_list, DynArray *videos_list, char *type)
{
	for (int i = 0; i < videos_list->used; i++)
	{
		if (strcmp(videos_list->array[i].type, type) == 0)
		{
			insert_array(good_type_list, videos_list->array[i]);
		}
	}
}

Video get_random_video(DynArray *videos_list, char *type)
{
	time_t t;
	srand((unsigned) time(&t));
	
	DynArray g_type;
	init_array(&g_type, 1);
	
	fill_videos_list_by_type(&g_type, videos_list, type);
	
	return g_type.array[rand() % g_type.used];
}

int play_random_video(int playtime, DynArray *videos_list, char *type)
{
	Video vid_to_play = get_random_video(videos_list, type);
	
	VideoCapture cap(vid_to_play.path);
	if(!cap.isOpened())
	{
		cap.release();
		return -1;
	}
	
	float utts = (playtime * 1000000) / cap.get(CAP_PROP_FRAME_COUNT);
	
	Mat frame;
	namedWindow(MAIN_WIN_NAME, WINDOW_NORMAL);
	setWindowProperty(MAIN_WIN_NAME, WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	
	while (1)
	{
		cap >> frame;
		
		if (frame.empty()) break;
		
		imshow(MAIN_WIN_NAME, frame);
		usleep(utts);
		char c = (char) waitKey(1); // utts ?
		
		if (c = 27) break;
	}
	
	cap.release();
	destroyWindow(MAIN_WIN_NAME);
	
	return 1;
}
