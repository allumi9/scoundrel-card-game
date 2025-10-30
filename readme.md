# Scoundrel
Concept by Zach Gage and Kurt Bieg.\ It's probably horrible code in terms of good C, but this my first more than 50 lines of code C program.\
I actually made this because I don't have a d20 cube to record health and didn't wanna shuffle cards each time I died(there's a lot of that), but still wanted to win at least once.

## Executing
There is now an actual Makefile wow-wow.\
gcc version is 11.4.0\
\
**Compile:** `make`\
**Running after compilation:** `./app`\
**Test:** `make test` (Make sure to have [criterion](https://github.com/Snaipe/Criterion) installed)\
**Clean up:** `make clean` (this is for cleaning up .o objects)\

### Dev status
Game is done, but it might leak memory/crash since it's not fully tested yet. So if you are running an older OS, or something that doesn't do memory clean ups after program exit, I warned you!
