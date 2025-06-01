#include <stdio.h>
#include <stdlib.h>

#define VIDEO_DURATION 3600
#define CHUNK_SIZE 5

typedef struct {
    int start_time;
    int end_time;
} VideoChunk;

int main() {
    int num_chunks = VIDEO_DURATION / CHUNK_SIZE;
    if (VIDEO_DURATION % CHUNK_SIZE != 0)
        num_chunks++;

    VideoChunk* chunks = (VideoChunk*)malloc(sizeof(VideoChunk) * num_chunks);

    int current_time = 0;
    for (int i = 0; i < num_chunks; i++) {
        chunks[i].start_time = current_time;
        chunks[i].end_time = current_time + CHUNK_SIZE;
        if (chunks[i].end_time > VIDEO_DURATION)
            chunks[i].end_time = VIDEO_DURATION;
        current_time += CHUNK_SIZE;
    }

    printf("Video has been chunked into %d segments:\n", num_chunks);
    for (int i = 0; i < num_chunks; i++) {
        printf("Segment %d: Start = %d seconds, End = %d seconds\n",
               i + 1, chunks[i].start_time, chunks[i].end_time);
    }

    free(chunks);
    return 0;
}
