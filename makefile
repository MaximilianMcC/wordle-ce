# ----------------------------
# Makefile Options
# ----------------------------

NAME = WORDLE
ICON = icon.png
DESCRIPTION = "Wordle clone"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

SRC = src/main.c src/words.c

# ----------------------------

include $(shell cedev-config --makefile)