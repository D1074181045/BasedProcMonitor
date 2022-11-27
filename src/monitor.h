#define STOP 0
#define START 1
#define PAUSE 2

struct Path {
    char *output;
    char *strace;
    char *killall;
};
