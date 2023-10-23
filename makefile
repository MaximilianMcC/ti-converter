# ----------------------------
# Makefile Options
# ----------------------------

NAME = CONVERT
ICON = icon.png
DESCRIPTION = "Convert measurements"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

SRC = src/main.c

# ----------------------------

include $(shell cedev-config --makefile)