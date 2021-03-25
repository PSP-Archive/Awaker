TARGET = Awaker
OBJS = main.o fonction.o menu.o jeu.o

INCDIR = ../include
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS) -c

LIBDIR = ../lib
LDFLAGS =
LIBS = -lSDLmain -lSDL_image -lSDL_mixer -lSDL -lpng -ljpeg -lvorbisidec -lm -lz\
	-lpspsdk -lpspctrl -lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio -lpsphprm  -lpspwlan

PSP_FW_VERSION = 371

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Awaker
PSP_EBOOT_ICON = ICON0.png
PSP_EBOOT_PIC1 = PIC1.png
PSP_EBOOT_SND0 = snd0.at3

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
