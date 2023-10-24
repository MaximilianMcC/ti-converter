# ----------------------------
# Makefile Options
# ----------------------------

NAME = CONVERT
ICON = icon.png
DESCRIPTION = "Convert measurements"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)