# ----------------------------
# Makefile Options
# ----------------------------

NAME = WORDLE
ICON = icon.png
DESCRIPTION = "Wordle clone"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
