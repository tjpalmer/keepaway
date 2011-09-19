# Makefile for Keepaway Players

CC    	= g++
COMPILE = $(CC) $(INCLUDES) ${FLAGS} ${DEFINES}
YACC = bison

SRC_DIR = .
DST_DIR = .
TARGET  = keepaway_player

# ==== INCLUDES =================================================

SOCCER_INCLUDES	= 
INCLUDES	= $(SOCCER_INCLUDES)

# ==== FLAGS ====================================================

# Substitute operating system that is used:
# SunOS_5 linux
OSFLAGS      	= ${OSFLAGS_linux}
CFLAGS_LIBS     = ${CLIBS_linux}
#OSFLAGS        = $(OSFLAGS_SunOS_5)
#CFLAGS_LIBS    = ${CLIBS_SunOS_5}

CFLAGS_DEBUG	= -g
CFLAGS_OPT     	= -O3 #-static
CFLAGS_WARN     = -Wall

OSFLAGS_SunOS_5 = -DSolaris 
OSFLAGS_linux   = -Dlinux 

CLIBS_SunOS_5   = 
CLIBS_linux     =

FLAGS           = ${OSFLAGS} ${CFLAGS_OPT} ${CFLAGS_DEBUG} ${CFLAGS_WARN}

# ==== LIBS ====================================================

CLIBS_SunOS_5   = -lsocket -lnsl -lpthread
CLIBS_linux     = -lpthread

# ==== DEFINES =================================================
#DEFINES	        = -DEC_LOG_ENABLED=1

# ==== SOURCES =================================================

SRCS		=	\
		Connection.cc \
		SenseHandler.cc \
		ActHandler.cc \
		SoccerTypes.cc \
		Objects.cc \
		WorldModel.cc \
		WorldModelHighLevel.cc \
		WorldModelPredict.cc \
		WorldModelUpdate.cc \
		WorldModelKeepaway.cc \
		WorldModelSayMsgTypes.cc \
		ServerSettings.cc \
		PlayerSettings.cc \
		GenericValues.cc \
		Formations.cc \
		Geometry.cc \
		Parse.cc \
		Logger.cc \
		LoggerDraw.cc \

SRCS_PLAYER 	= ${SRCS} \
		BasicPlayer.cc \
		KeepawayPlayer.cc \
		HandCodedAgent.cc \
		main.cc

OBJS_PLAYER	= $(SRCS_PLAYER:.cc=.o)

# ==== RULES ==================================================

all::	$(TARGET)

.cc.o:
	$(COMPILE) -c -o $@ $(@F:%.o=%.cc)

keepaway_player: $(OBJS_PLAYER)  
	$(COMPILE) -o  $@ $(OBJS_PLAYER) ${CFLAGS_LIBS}

update:
	cvs update

commit:
	cvs commit

clean:
	rm -f $(TARGET) $(OBJS_PLAYER) *core *~ a.out

depend:
	makedepend $(DEPENDFLAGS) -s "# DO NOT DELETE THIS LINE" -- $(INCLUDES) -- $(SRCS_PLAYER)

# DO NOT DELETE THIS LINE

