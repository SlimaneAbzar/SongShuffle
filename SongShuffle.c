#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LENGTH 80

void insertArtistsAndSongs(char artists[4][80], char songsArtist1[3][80], char songsArtist2[3][80],
                           char songsArtist3[3][80], char songsArtist4[3][80],
                           int* numOfArtists, int numSongsPerArtist[4]);

void sortArtists(char artists[4][MAX_LENGTH], char sortedArtists[4][80], int numOfArtists);

void sortSongs(char songsArtist1[3][80], char songsArtist2[3][80],
               char songsArtist3[3][80], char songsArtist4[3][80], int numSongsPerArtist[4]);

void shuffleSongs(char playlist[12][80], char songsArtist1[3][80], char songsArtist2[3][80],
                  char songsArtist3[3][80], char songsArtist4[3][80], int* playListSongs,
                  int numSongsPerArtist[4], char artists[4][80]);

bool check(int j, char doubled[24][80]) {
    int max = j - 5;
    if (max < 0) {
        max = 0;
    }
    for (; max < j; max++) {
        if (strcmp(doubled[j], doubled[max]) == 0) {
            return false;
        }
    }
    return true;
}

void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int main(void) {
    char artists[4][80];
    char sortedArtists[4][80];
    char songsArtist1[3][80];
    char songsArtist2[3][80];
    char songsArtist3[3][80];
    char songsArtist4[3][80];
    int numOfArtists = 0;
    int numSongsPerArtist[4] = {0, 0, 0, 0};

    insertArtistsAndSongs(artists, songsArtist1, songsArtist2, songsArtist3, songsArtist4, &numOfArtists, numSongsPerArtist);
    sortArtists(artists, sortedArtists, numOfArtists);
    sortSongs(songsArtist1, songsArtist2, songsArtist3, songsArtist4, numSongsPerArtist);

    printf("\nSorted list of songs:\n");
    for (int i = 0; i < numOfArtists; i++) {
        printf("%s\n", sortedArtists[i]);

        if (i == 0) {
            for (int j = 0; j < numSongsPerArtist[0]; j++) {
                printf("-%s\n", songsArtist1[j]);
            }
        } else if (i == 1) {
            for (int j = 0; j < numSongsPerArtist[1]; j++) {
                printf("-%s\n", songsArtist2[j]);
            }
        } else if (i == 2) {
            for (int j = 0; j < numSongsPerArtist[2]; j++) {
                printf("-%s\n", songsArtist3[j]);
            }
        } else if (i == 3) {
            for (int j = 0; j < numSongsPerArtist[3]; j++) {
                printf("-%s\n", songsArtist4[j]);
            }
        }
    }

    srand(time(NULL));
    char playlist[12][80];
    int playListSongs = 0;
    shuffleSongs(playlist, songsArtist1, songsArtist2, songsArtist3, songsArtist4, &playListSongs, numSongsPerArtist, artists);

    return 0;
}

void insertArtistsAndSongs(char artists[4][80], char songsArtist1[4][80], char songsArtist2[4][80],
                           char songsArtist3[4][80], char songsArtist4[4][80],
                           int *numOfArtists, int numSongsPerArtist[4]) {
    int i = 0;
    while (i < 4) {
        printf("Insert an artist/group name: ");
        fgets(artists[i], sizeof(artists[i]), stdin);
        if (artists[i][0] == '\n') break;
        removeNewline(artists[i]);
        (*numOfArtists)++;

        int j = 0;
        while (j < 3) {
            printf("Insert song %d for %s: ", j + 1, artists[i]);
            if (i == 0) {
                fgets(songsArtist1[j], sizeof(songsArtist1[j]), stdin);
                if (songsArtist1[j][0] == '\n') break;
                removeNewline(songsArtist1[j]);
                numSongsPerArtist[i]++;
            } else if (i == 1) {
                fgets(songsArtist2[j], sizeof(songsArtist2[j]), stdin);
                if (songsArtist2[j][0] == '\n') break;
                removeNewline(songsArtist2[j]);
                numSongsPerArtist[i]++;
            } else if (i == 2) {
                fgets(songsArtist3[j], sizeof(songsArtist3[j]), stdin);
                if (songsArtist3[j][0] == '\n') break;
                removeNewline(songsArtist3[j]);
                numSongsPerArtist[i]++;
            } else if (i == 3) {
                fgets(songsArtist4[j], sizeof(songsArtist4[j]), stdin);
                if (songsArtist4[j][0] == '\n') break;
                removeNewline(songsArtist4[j]);
                numSongsPerArtist[i]++;
            }
            j++;
        }
        i++;
    }
}

void sortArtists(char artists[4][MAX_LENGTH], char sortedArtists[4][80], int numOfArtists) {
    int step, i;
    char swap[MAX_LENGTH];
    for (step = 0; step < (numOfArtists - 1); step++) {
        for (i = 0; i < numOfArtists - step - 1; i++) {
            if (strcmp(artists[i + 1], artists[i]) < 0) {
                strcpy(swap, artists[i]);
                strcpy(artists[i], artists[i + 1]);
                strcpy(artists[i + 1], swap);
            }
        }
    }
    for (i = 0; i < numOfArtists; i++) {
        strcpy(sortedArtists[i], artists[i]);
    }
}

void sortSongs(char songsArtist1[3][80], char songsArtist2[3][80],
               char songsArtist3[3][80], char songsArtist4[3][80], int numSongsPerArtist[4]) {
    int step, i, j;
    char swap[MAX_LENGTH];
    for (i = 0; i < 4; i++) {
        int numOfSongs = numSongsPerArtist[i];
        for (step = 0; step < (numOfSongs - 1); step++) {
            for (j = 0; j < numOfSongs - step - 1; j++) {
                if (i == 0 && strcmp(songsArtist1[j + 1], songsArtist1[j]) < 0) {
                    strcpy(swap, songsArtist1[j]);
                    strcpy(songsArtist1[j], songsArtist1[j + 1]);
                    strcpy(songsArtist1[j + 1], swap);
                }
                if (i == 1 && strcmp(songsArtist2[j + 1], songsArtist2[j]) < 0) {
                    strcpy(swap, songsArtist2[j]);
                    strcpy(songsArtist2[j], songsArtist2[j + 1]);
                    strcpy(songsArtist2[j + 1], swap);
                }
                if (i == 2 && strcmp(songsArtist3[j + 1], songsArtist3[j]) < 0) {
                    strcpy(swap, songsArtist3[j]);
                    strcpy(songsArtist3[j], songsArtist3[j + 1]);
                    strcpy(songsArtist3[j + 1], swap);
                }
                if (i == 3 && strcmp(songsArtist4[j + 1], songsArtist4[j]) < 0) {
                    strcpy(swap, songsArtist4[j]);
                    strcpy(songsArtist4[j], songsArtist4[j + 1]);
                    strcpy(songsArtist4[j + 1], swap);
                }
            }
        }
    }
}

void shuffleSongs(char playlist[12][80], char songsArtist1[3][80], char songsArtist2[3][80],
                  char songsArtist3[3][80], char songsArtist4[3][80], int* playListSongs,
                  int numSongsPerArtist[4], char artists[4][80]) {

    int totalsongs = 0;
    char doubled[24][80];  // Array to hold all songs doubled
    int used[24] = {0};    // Flags for used songs

    // Build playlist with each song repeated twice
    for (int i = 0; i < numSongsPerArtist[0]; i++) {
        sprintf(doubled[totalsongs++], "%s:%s", artists[0], songsArtist1[i]);
        sprintf(doubled[totalsongs++], "%s:%s", artists[0], songsArtist1[i]);
    }
    for (int i = 0; i < numSongsPerArtist[1]; i++) {
        sprintf(doubled[totalsongs++], "%s:%s", artists[1], songsArtist2[i]);
        sprintf(doubled[totalsongs++], "%s:%s", artists[1], songsArtist2[i]);
    }
    for (int i = 0; i < numSongsPerArtist[2]; i++) {
        sprintf(doubled[totalsongs++], "%s:%s", artists[2], songsArtist3[i]);
        sprintf(doubled[totalsongs++], "%s:%s", artists[2], songsArtist3[i]);
    }
    for (int i = 0; i < numSongsPerArtist[3]; i++) {
        sprintf(doubled[totalsongs++], "%s:%s", artists[3], songsArtist4[i]);
        sprintf(doubled[totalsongs++], "%s:%s", artists[3], songsArtist4[i]);
    }

    char finalPlaylist[24][80];
    int count = 0;

    while (count < totalsongs) {
        int index = rand() % totalsongs;

        // Skip if already used
        if (used[index]) continue;

        // Check last 5 songs for repeat
        bool recentRepeat = false;
        for (int k = (count >= 5 ? count - 5 : 0); k < count; k++) {
            if (strcmp(finalPlaylist[k], doubled[index]) == 0) {
                recentRepeat = true;
                break;
            }
        }

        if (recentRepeat) continue;

        // Accept this song
        strcpy(finalPlaylist[count], doubled[index]);
        used[index] = 1;
        count++;
    }

    printf("Shuffled playlist:\n");
    for (int i = 0; i < totalsongs; i++) {
        printf("%s\n", finalPlaylist[i]);
    }

    *playListSongs = totalsongs;
}

