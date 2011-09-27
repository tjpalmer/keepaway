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
CFLAGS_OPT     	= #-O3 #-static
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

Connection.o: /usr/include/errno.h /usr/include/features.h
Connection.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Connection.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Connection.o: /usr/include/gnu/stubs-64.h /usr/include/bits/errno.h
Connection.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
Connection.o: /usr/include/asm-generic/errno.h
Connection.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
Connection.o: /usr/include/xlocale.h /usr/include/sys/types.h
Connection.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Connection.o: /usr/include/time.h /usr/include/endian.h
Connection.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
Connection.o: /usr/include/sys/select.h /usr/include/bits/select.h
Connection.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Connection.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Connection.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
Connection.o: /usr/include/bits/confname.h /usr/include/getopt.h
Connection.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
Connection.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
Connection.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
Connection.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
Connection.o: /usr/include/asm-generic/sockios.h Connection.h
Connection.o: /usr/include/stdio.h /usr/include/libio.h
Connection.o: /usr/include/_G_config.h /usr/include/wchar.h
Connection.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Connection.o: /usr/include/netdb.h /usr/include/netinet/in.h
Connection.o: /usr/include/stdint.h /usr/include/bits/wchar.h
Connection.o: /usr/include/bits/in.h /usr/include/rpc/netdb.h
Connection.o: /usr/include/bits/netdb.h /usr/include/arpa/inet.h Logger.h
Connection.o: /usr/include/sys/time.h
SenseHandler.o: SenseHandler.h Connection.h /usr/include/stdio.h
SenseHandler.o: /usr/include/features.h /usr/include/bits/predefs.h
SenseHandler.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
SenseHandler.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
SenseHandler.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
SenseHandler.o: /usr/include/libio.h /usr/include/_G_config.h
SenseHandler.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
SenseHandler.o: /usr/include/bits/sys_errlist.h /usr/include/netdb.h
SenseHandler.o: /usr/include/netinet/in.h /usr/include/stdint.h
SenseHandler.o: /usr/include/bits/wchar.h /usr/include/sys/socket.h
SenseHandler.o: /usr/include/sys/uio.h /usr/include/sys/types.h
SenseHandler.o: /usr/include/time.h /usr/include/endian.h
SenseHandler.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
SenseHandler.o: /usr/include/sys/select.h /usr/include/bits/select.h
SenseHandler.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
SenseHandler.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
SenseHandler.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
SenseHandler.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
SenseHandler.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
SenseHandler.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
SenseHandler.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
SenseHandler.o: /usr/include/arpa/inet.h WorldModel.h Objects.h SoccerTypes.h
SenseHandler.o: Geometry.h /usr/include/math.h /usr/include/bits/huge_val.h
SenseHandler.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
SenseHandler.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
SenseHandler.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
SenseHandler.o: ServerSettings.h GenericValues.h PlayerSettings.h Logger.h
SenseHandler.o: /usr/include/sys/time.h LoggerDraw.h Formations.h
SenseHandler.o: /usr/include/pthread.h /usr/include/sched.h
SenseHandler.o: /usr/include/bits/sched.h /usr/include/signal.h
SenseHandler.o: /usr/include/bits/setjmp.h ActHandler.h Parse.h
SenseHandler.o: WorldModelSayMsgFactory.h SayMsgFactory.h SayMsgTypes.h
SenseHandler.o: SayMsgIDs.h SayMsgDataTypes.h /usr/include/assert.h
SenseHandler.o: WorldModelSayMsgTypes.h /usr/include/string.h
SenseHandler.o: /usr/include/xlocale.h
ActHandler.o: ActHandler.h Connection.h /usr/include/stdio.h
ActHandler.o: /usr/include/features.h /usr/include/bits/predefs.h
ActHandler.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ActHandler.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ActHandler.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ActHandler.o: /usr/include/libio.h /usr/include/_G_config.h
ActHandler.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
ActHandler.o: /usr/include/bits/sys_errlist.h /usr/include/netdb.h
ActHandler.o: /usr/include/netinet/in.h /usr/include/stdint.h
ActHandler.o: /usr/include/bits/wchar.h /usr/include/sys/socket.h
ActHandler.o: /usr/include/sys/uio.h /usr/include/sys/types.h
ActHandler.o: /usr/include/time.h /usr/include/endian.h
ActHandler.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ActHandler.o: /usr/include/sys/select.h /usr/include/bits/select.h
ActHandler.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ActHandler.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ActHandler.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
ActHandler.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
ActHandler.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
ActHandler.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
ActHandler.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
ActHandler.o: /usr/include/arpa/inet.h WorldModel.h Objects.h SoccerTypes.h
ActHandler.o: Geometry.h /usr/include/math.h /usr/include/bits/huge_val.h
ActHandler.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
ActHandler.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
ActHandler.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
ActHandler.o: ServerSettings.h GenericValues.h PlayerSettings.h Logger.h
ActHandler.o: /usr/include/sys/time.h LoggerDraw.h Formations.h
ActHandler.o: /usr/include/pthread.h /usr/include/sched.h
ActHandler.o: /usr/include/bits/sched.h /usr/include/signal.h
ActHandler.o: /usr/include/bits/setjmp.h /usr/include/poll.h
ActHandler.o: /usr/include/sys/poll.h /usr/include/bits/poll.h
SoccerTypes.o: /usr/include/stdio.h /usr/include/features.h
SoccerTypes.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
SoccerTypes.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
SoccerTypes.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
SoccerTypes.o: /usr/include/bits/typesizes.h /usr/include/libio.h
SoccerTypes.o: /usr/include/_G_config.h /usr/include/wchar.h
SoccerTypes.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
SoccerTypes.o: /usr/include/string.h /usr/include/xlocale.h SoccerTypes.h
SoccerTypes.o: Geometry.h /usr/include/math.h /usr/include/bits/huge_val.h
SoccerTypes.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
SoccerTypes.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
SoccerTypes.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
SoccerTypes.o: ServerSettings.h GenericValues.h Parse.h
Objects.o: Objects.h SoccerTypes.h Geometry.h /usr/include/math.h
Objects.o: /usr/include/features.h /usr/include/bits/predefs.h
Objects.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Objects.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
Objects.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
Objects.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
Objects.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
Objects.o: /usr/include/bits/mathcalls.h ServerSettings.h GenericValues.h
Objects.o: /usr/include/stdlib.h /usr/include/sys/types.h
Objects.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Objects.o: /usr/include/time.h /usr/include/endian.h
Objects.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
Objects.o: /usr/include/sys/select.h /usr/include/bits/select.h
Objects.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Objects.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Objects.o: /usr/include/alloca.h /usr/include/string.h /usr/include/xlocale.h
WorldModel.o: /usr/include/stdio.h /usr/include/features.h
WorldModel.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
WorldModel.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
WorldModel.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
WorldModel.o: /usr/include/bits/typesizes.h /usr/include/libio.h
WorldModel.o: /usr/include/_G_config.h /usr/include/wchar.h
WorldModel.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
WorldModel.o: /usr/include/errno.h /usr/include/bits/errno.h
WorldModel.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
WorldModel.o: /usr/include/asm-generic/errno.h
WorldModel.o: /usr/include/asm-generic/errno-base.h /usr/include/strings.h
WorldModel.o: /usr/include/xlocale.h /usr/include/pthread.h
WorldModel.o: /usr/include/endian.h /usr/include/bits/endian.h
WorldModel.o: /usr/include/bits/byteswap.h /usr/include/sched.h
WorldModel.o: /usr/include/time.h /usr/include/bits/sched.h
WorldModel.o: /usr/include/signal.h /usr/include/bits/sigset.h
WorldModel.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/setjmp.h
WorldModel.o: /usr/include/string.h /usr/include/math.h
WorldModel.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
WorldModel.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
WorldModel.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
WorldModel.o: /usr/include/bits/mathcalls.h WorldModel.h Objects.h
WorldModel.o: SoccerTypes.h Geometry.h ServerSettings.h GenericValues.h
WorldModel.o: PlayerSettings.h Logger.h /usr/include/sys/time.h
WorldModel.o: /usr/include/bits/time.h /usr/include/sys/select.h
WorldModel.o: /usr/include/bits/select.h LoggerDraw.h Formations.h
WorldModelHighLevel.o: /usr/include/stdio.h /usr/include/features.h
WorldModelHighLevel.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
WorldModelHighLevel.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
WorldModelHighLevel.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
WorldModelHighLevel.o: /usr/include/bits/typesizes.h /usr/include/libio.h
WorldModelHighLevel.o: /usr/include/_G_config.h /usr/include/wchar.h
WorldModelHighLevel.o: /usr/include/bits/stdio_lim.h
WorldModelHighLevel.o: /usr/include/bits/sys_errlist.h WorldModel.h Objects.h
WorldModelHighLevel.o: SoccerTypes.h Geometry.h /usr/include/math.h
WorldModelHighLevel.o: /usr/include/bits/huge_val.h
WorldModelHighLevel.o: /usr/include/bits/huge_valf.h
WorldModelHighLevel.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
WorldModelHighLevel.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
WorldModelHighLevel.o: /usr/include/bits/mathcalls.h ServerSettings.h
WorldModelHighLevel.o: GenericValues.h PlayerSettings.h Logger.h
WorldModelHighLevel.o: /usr/include/sys/time.h /usr/include/time.h
WorldModelHighLevel.o: /usr/include/bits/time.h /usr/include/sys/select.h
WorldModelHighLevel.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
WorldModelHighLevel.o: LoggerDraw.h Formations.h /usr/include/pthread.h
WorldModelHighLevel.o: /usr/include/endian.h /usr/include/bits/endian.h
WorldModelHighLevel.o: /usr/include/bits/byteswap.h /usr/include/sched.h
WorldModelHighLevel.o: /usr/include/bits/sched.h /usr/include/signal.h
WorldModelHighLevel.o: /usr/include/bits/pthreadtypes.h
WorldModelHighLevel.o: /usr/include/bits/setjmp.h
WorldModelPredict.o: /usr/include/stdio.h /usr/include/features.h
WorldModelPredict.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
WorldModelPredict.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
WorldModelPredict.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
WorldModelPredict.o: /usr/include/bits/typesizes.h /usr/include/libio.h
WorldModelPredict.o: /usr/include/_G_config.h /usr/include/wchar.h
WorldModelPredict.o: /usr/include/bits/stdio_lim.h
WorldModelPredict.o: /usr/include/bits/sys_errlist.h WorldModel.h Objects.h
WorldModelPredict.o: SoccerTypes.h Geometry.h /usr/include/math.h
WorldModelPredict.o: /usr/include/bits/huge_val.h
WorldModelPredict.o: /usr/include/bits/huge_valf.h
WorldModelPredict.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
WorldModelPredict.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
WorldModelPredict.o: /usr/include/bits/mathcalls.h ServerSettings.h
WorldModelPredict.o: GenericValues.h PlayerSettings.h Logger.h
WorldModelPredict.o: /usr/include/sys/time.h /usr/include/time.h
WorldModelPredict.o: /usr/include/bits/time.h /usr/include/sys/select.h
WorldModelPredict.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
WorldModelPredict.o: LoggerDraw.h Formations.h /usr/include/pthread.h
WorldModelPredict.o: /usr/include/endian.h /usr/include/bits/endian.h
WorldModelPredict.o: /usr/include/bits/byteswap.h /usr/include/sched.h
WorldModelPredict.o: /usr/include/bits/sched.h /usr/include/signal.h
WorldModelPredict.o: /usr/include/bits/pthreadtypes.h
WorldModelPredict.o: /usr/include/bits/setjmp.h
WorldModelUpdate.o: WorldModel.h Objects.h SoccerTypes.h Geometry.h
WorldModelUpdate.o: /usr/include/math.h /usr/include/features.h
WorldModelUpdate.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
WorldModelUpdate.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
WorldModelUpdate.o: /usr/include/gnu/stubs-64.h /usr/include/bits/huge_val.h
WorldModelUpdate.o: /usr/include/bits/huge_valf.h
WorldModelUpdate.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
WorldModelUpdate.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
WorldModelUpdate.o: /usr/include/bits/mathcalls.h ServerSettings.h
WorldModelUpdate.o: GenericValues.h PlayerSettings.h Logger.h
WorldModelUpdate.o: /usr/include/sys/time.h /usr/include/bits/types.h
WorldModelUpdate.o: /usr/include/bits/typesizes.h /usr/include/time.h
WorldModelUpdate.o: /usr/include/bits/time.h /usr/include/sys/select.h
WorldModelUpdate.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
WorldModelUpdate.o: LoggerDraw.h Formations.h /usr/include/pthread.h
WorldModelUpdate.o: /usr/include/endian.h /usr/include/bits/endian.h
WorldModelUpdate.o: /usr/include/bits/byteswap.h /usr/include/sched.h
WorldModelUpdate.o: /usr/include/bits/sched.h /usr/include/signal.h
WorldModelUpdate.o: /usr/include/bits/pthreadtypes.h
WorldModelUpdate.o: /usr/include/bits/setjmp.h Parse.h SayMsgDecoder.h
WorldModelUpdate.o: SayMsgFactory.h SayMsgTypes.h /usr/include/stdio.h
WorldModelUpdate.o: /usr/include/libio.h /usr/include/_G_config.h
WorldModelUpdate.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
WorldModelUpdate.o: /usr/include/bits/sys_errlist.h SayMsgIDs.h
WorldModelUpdate.o: SayMsgDataTypes.h /usr/include/assert.h
WorldModelUpdate.o: WorldModelSayMsgFactory.h WorldModelSayMsgTypes.h
WorldModelUpdate.o: /usr/include/sys/times.h /usr/include/sys/resource.h
WorldModelUpdate.o: /usr/include/bits/resource.h /usr/include/unistd.h
WorldModelUpdate.o: /usr/include/bits/posix_opt.h
WorldModelUpdate.o: /usr/include/bits/confname.h /usr/include/getopt.h
WorldModelKeepaway.o: /usr/include/assert.h /usr/include/features.h
WorldModelKeepaway.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
WorldModelKeepaway.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
WorldModelKeepaway.o: /usr/include/gnu/stubs-64.h WorldModel.h Objects.h
WorldModelKeepaway.o: SoccerTypes.h Geometry.h /usr/include/math.h
WorldModelKeepaway.o: /usr/include/bits/huge_val.h
WorldModelKeepaway.o: /usr/include/bits/huge_valf.h
WorldModelKeepaway.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
WorldModelKeepaway.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
WorldModelKeepaway.o: /usr/include/bits/mathcalls.h ServerSettings.h
WorldModelKeepaway.o: GenericValues.h PlayerSettings.h Logger.h
WorldModelKeepaway.o: /usr/include/sys/time.h /usr/include/bits/types.h
WorldModelKeepaway.o: /usr/include/bits/typesizes.h /usr/include/time.h
WorldModelKeepaway.o: /usr/include/bits/time.h /usr/include/sys/select.h
WorldModelKeepaway.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
WorldModelKeepaway.o: LoggerDraw.h Formations.h /usr/include/pthread.h
WorldModelKeepaway.o: /usr/include/endian.h /usr/include/bits/endian.h
WorldModelKeepaway.o: /usr/include/bits/byteswap.h /usr/include/sched.h
WorldModelKeepaway.o: /usr/include/bits/sched.h /usr/include/signal.h
WorldModelKeepaway.o: /usr/include/bits/pthreadtypes.h
WorldModelKeepaway.o: /usr/include/bits/setjmp.h
WorldModelSayMsgTypes.o: WorldModelSayMsgTypes.h WorldModel.h Objects.h
WorldModelSayMsgTypes.o: SoccerTypes.h Geometry.h /usr/include/math.h
WorldModelSayMsgTypes.o: /usr/include/features.h /usr/include/bits/predefs.h
WorldModelSayMsgTypes.o: /usr/include/sys/cdefs.h
WorldModelSayMsgTypes.o: /usr/include/bits/wordsize.h
WorldModelSayMsgTypes.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
WorldModelSayMsgTypes.o: /usr/include/bits/huge_val.h
WorldModelSayMsgTypes.o: /usr/include/bits/huge_valf.h
WorldModelSayMsgTypes.o: /usr/include/bits/huge_vall.h
WorldModelSayMsgTypes.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
WorldModelSayMsgTypes.o: /usr/include/bits/mathdef.h
WorldModelSayMsgTypes.o: /usr/include/bits/mathcalls.h ServerSettings.h
WorldModelSayMsgTypes.o: GenericValues.h PlayerSettings.h Logger.h
WorldModelSayMsgTypes.o: /usr/include/sys/time.h /usr/include/bits/types.h
WorldModelSayMsgTypes.o: /usr/include/bits/typesizes.h /usr/include/time.h
WorldModelSayMsgTypes.o: /usr/include/bits/time.h /usr/include/sys/select.h
WorldModelSayMsgTypes.o: /usr/include/bits/select.h
WorldModelSayMsgTypes.o: /usr/include/bits/sigset.h LoggerDraw.h Formations.h
WorldModelSayMsgTypes.o: /usr/include/pthread.h /usr/include/endian.h
WorldModelSayMsgTypes.o: /usr/include/bits/endian.h
WorldModelSayMsgTypes.o: /usr/include/bits/byteswap.h /usr/include/sched.h
WorldModelSayMsgTypes.o: /usr/include/bits/sched.h /usr/include/signal.h
WorldModelSayMsgTypes.o: /usr/include/bits/pthreadtypes.h
WorldModelSayMsgTypes.o: /usr/include/bits/setjmp.h SayMsgTypes.h
WorldModelSayMsgTypes.o: /usr/include/stdio.h /usr/include/libio.h
WorldModelSayMsgTypes.o: /usr/include/_G_config.h /usr/include/wchar.h
WorldModelSayMsgTypes.o: /usr/include/bits/stdio_lim.h
WorldModelSayMsgTypes.o: /usr/include/bits/sys_errlist.h SayMsgIDs.h
WorldModelSayMsgTypes.o: SayMsgDataTypes.h /usr/include/assert.h
ServerSettings.o: ServerSettings.h Geometry.h /usr/include/math.h
ServerSettings.o: /usr/include/features.h /usr/include/bits/predefs.h
ServerSettings.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ServerSettings.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ServerSettings.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ServerSettings.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ServerSettings.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ServerSettings.o: /usr/include/bits/mathcalls.h GenericValues.h
ServerSettings.o: /usr/include/stdio.h /usr/include/bits/types.h
ServerSettings.o: /usr/include/bits/typesizes.h /usr/include/libio.h
ServerSettings.o: /usr/include/_G_config.h /usr/include/wchar.h
ServerSettings.o: /usr/include/bits/stdio_lim.h
ServerSettings.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
ServerSettings.o: /usr/include/xlocale.h
PlayerSettings.o: PlayerSettings.h GenericValues.h
GenericValues.o: GenericValues.h Parse.h /usr/include/stdio.h
GenericValues.o: /usr/include/features.h /usr/include/bits/predefs.h
GenericValues.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
GenericValues.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
GenericValues.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
GenericValues.o: /usr/include/libio.h /usr/include/_G_config.h
GenericValues.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
GenericValues.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
GenericValues.o: /usr/include/sys/types.h /usr/include/time.h
GenericValues.o: /usr/include/endian.h /usr/include/bits/endian.h
GenericValues.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
GenericValues.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
GenericValues.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
GenericValues.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
GenericValues.o: /usr/include/string.h /usr/include/xlocale.h
GenericValues.o: /usr/include/ctype.h
Formations.o: Formations.h SoccerTypes.h Geometry.h /usr/include/math.h
Formations.o: /usr/include/features.h /usr/include/bits/predefs.h
Formations.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Formations.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
Formations.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
Formations.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
Formations.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
Formations.o: /usr/include/bits/mathcalls.h ServerSettings.h GenericValues.h
Formations.o: Parse.h /usr/include/stdio.h /usr/include/bits/types.h
Formations.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Formations.o: /usr/include/_G_config.h /usr/include/wchar.h
Formations.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Geometry.o: Geometry.h /usr/include/math.h /usr/include/features.h
Geometry.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Geometry.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Geometry.o: /usr/include/gnu/stubs-64.h /usr/include/bits/huge_val.h
Geometry.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Geometry.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Geometry.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Geometry.o: /usr/include/stdio.h /usr/include/bits/types.h
Geometry.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Geometry.o: /usr/include/_G_config.h /usr/include/wchar.h
Geometry.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Parse.o: Parse.h /usr/include/ctype.h /usr/include/features.h
Parse.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Parse.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Parse.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Parse.o: /usr/include/bits/typesizes.h /usr/include/endian.h
Parse.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
Parse.o: /usr/include/xlocale.h /usr/include/math.h
Parse.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
Parse.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
Parse.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
Parse.o: /usr/include/bits/mathcalls.h /usr/include/string.h
Logger.o: Logger.h /usr/include/sys/time.h /usr/include/features.h
Logger.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Logger.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Logger.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Logger.o: /usr/include/bits/typesizes.h /usr/include/time.h
Logger.o: /usr/include/bits/time.h /usr/include/sys/select.h
Logger.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
Logger.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Logger.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Logger.o: /usr/include/bits/sys_errlist.h /usr/include/pthread.h
Logger.o: /usr/include/endian.h /usr/include/bits/endian.h
Logger.o: /usr/include/bits/byteswap.h /usr/include/sched.h
Logger.o: /usr/include/bits/sched.h /usr/include/signal.h
Logger.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/setjmp.h
LoggerDraw.o: LoggerDraw.h SoccerTypes.h Geometry.h /usr/include/math.h
LoggerDraw.o: /usr/include/features.h /usr/include/bits/predefs.h
LoggerDraw.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
LoggerDraw.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
LoggerDraw.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
LoggerDraw.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
LoggerDraw.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
LoggerDraw.o: /usr/include/bits/mathcalls.h ServerSettings.h GenericValues.h
BasicPlayer.o: BasicPlayer.h ActHandler.h Connection.h /usr/include/stdio.h
BasicPlayer.o: /usr/include/features.h /usr/include/bits/predefs.h
BasicPlayer.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
BasicPlayer.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
BasicPlayer.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
BasicPlayer.o: /usr/include/libio.h /usr/include/_G_config.h
BasicPlayer.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
BasicPlayer.o: /usr/include/bits/sys_errlist.h /usr/include/netdb.h
BasicPlayer.o: /usr/include/netinet/in.h /usr/include/stdint.h
BasicPlayer.o: /usr/include/bits/wchar.h /usr/include/sys/socket.h
BasicPlayer.o: /usr/include/sys/uio.h /usr/include/sys/types.h
BasicPlayer.o: /usr/include/time.h /usr/include/endian.h
BasicPlayer.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
BasicPlayer.o: /usr/include/sys/select.h /usr/include/bits/select.h
BasicPlayer.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
BasicPlayer.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
BasicPlayer.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
BasicPlayer.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
BasicPlayer.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
BasicPlayer.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
BasicPlayer.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
BasicPlayer.o: /usr/include/arpa/inet.h WorldModel.h Objects.h SoccerTypes.h
BasicPlayer.o: Geometry.h /usr/include/math.h /usr/include/bits/huge_val.h
BasicPlayer.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
BasicPlayer.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
BasicPlayer.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
BasicPlayer.o: ServerSettings.h GenericValues.h PlayerSettings.h Logger.h
BasicPlayer.o: /usr/include/sys/time.h LoggerDraw.h Formations.h
BasicPlayer.o: /usr/include/pthread.h /usr/include/sched.h
BasicPlayer.o: /usr/include/bits/sched.h /usr/include/signal.h
BasicPlayer.o: /usr/include/bits/setjmp.h Parse.h
KeepawayPlayer.o: KeepawayPlayer.h BasicPlayer.h ActHandler.h Connection.h
KeepawayPlayer.o: /usr/include/stdio.h /usr/include/features.h
KeepawayPlayer.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
KeepawayPlayer.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
KeepawayPlayer.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
KeepawayPlayer.o: /usr/include/bits/typesizes.h /usr/include/libio.h
KeepawayPlayer.o: /usr/include/_G_config.h /usr/include/wchar.h
KeepawayPlayer.o: /usr/include/bits/stdio_lim.h
KeepawayPlayer.o: /usr/include/bits/sys_errlist.h /usr/include/netdb.h
KeepawayPlayer.o: /usr/include/netinet/in.h /usr/include/stdint.h
KeepawayPlayer.o: /usr/include/bits/wchar.h /usr/include/sys/socket.h
KeepawayPlayer.o: /usr/include/sys/uio.h /usr/include/sys/types.h
KeepawayPlayer.o: /usr/include/time.h /usr/include/endian.h
KeepawayPlayer.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
KeepawayPlayer.o: /usr/include/sys/select.h /usr/include/bits/select.h
KeepawayPlayer.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
KeepawayPlayer.o: /usr/include/sys/sysmacros.h
KeepawayPlayer.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/uio.h
KeepawayPlayer.o: /usr/include/bits/socket.h /usr/include/bits/sockaddr.h
KeepawayPlayer.o: /usr/include/asm/socket.h /usr/include/asm-generic/socket.h
KeepawayPlayer.o: /usr/include/asm/sockios.h
KeepawayPlayer.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
KeepawayPlayer.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
KeepawayPlayer.o: /usr/include/arpa/inet.h WorldModel.h Objects.h
KeepawayPlayer.o: SoccerTypes.h Geometry.h /usr/include/math.h
KeepawayPlayer.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
KeepawayPlayer.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
KeepawayPlayer.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
KeepawayPlayer.o: /usr/include/bits/mathcalls.h ServerSettings.h
KeepawayPlayer.o: GenericValues.h PlayerSettings.h Logger.h
KeepawayPlayer.o: /usr/include/sys/time.h LoggerDraw.h Formations.h
KeepawayPlayer.o: /usr/include/pthread.h /usr/include/sched.h
KeepawayPlayer.o: /usr/include/bits/sched.h /usr/include/signal.h
KeepawayPlayer.o: /usr/include/bits/setjmp.h SMDPAgent.h Parse.h
KeepawayPlayer.o: SayMsgEncoder.h SayMsgTypes.h SayMsgIDs.h SayMsgDataTypes.h
KeepawayPlayer.o: /usr/include/assert.h
HandCodedAgent.o: /usr/include/string.h /usr/include/features.h
HandCodedAgent.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
HandCodedAgent.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
HandCodedAgent.o: /usr/include/gnu/stubs-64.h /usr/include/xlocale.h
HandCodedAgent.o: /usr/include/stdlib.h /usr/include/sys/types.h
HandCodedAgent.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
HandCodedAgent.o: /usr/include/time.h /usr/include/endian.h
HandCodedAgent.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
HandCodedAgent.o: /usr/include/sys/select.h /usr/include/bits/select.h
HandCodedAgent.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
HandCodedAgent.o: /usr/include/sys/sysmacros.h
HandCodedAgent.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
HandCodedAgent.o: HandCodedAgent.h SMDPAgent.h WorldModel.h Objects.h
HandCodedAgent.o: SoccerTypes.h Geometry.h /usr/include/math.h
HandCodedAgent.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
HandCodedAgent.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
HandCodedAgent.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
HandCodedAgent.o: /usr/include/bits/mathcalls.h ServerSettings.h
HandCodedAgent.o: GenericValues.h PlayerSettings.h Logger.h
HandCodedAgent.o: /usr/include/sys/time.h LoggerDraw.h Formations.h
HandCodedAgent.o: /usr/include/pthread.h /usr/include/sched.h
HandCodedAgent.o: /usr/include/bits/sched.h /usr/include/signal.h
HandCodedAgent.o: /usr/include/bits/setjmp.h
main.o: SenseHandler.h Connection.h /usr/include/stdio.h
main.o: /usr/include/features.h /usr/include/bits/predefs.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/netdb.h /usr/include/netinet/in.h /usr/include/stdint.h
main.o: /usr/include/bits/wchar.h /usr/include/sys/socket.h
main.o: /usr/include/sys/uio.h /usr/include/sys/types.h /usr/include/time.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
main.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/uio.h
main.o: /usr/include/bits/socket.h /usr/include/bits/sockaddr.h
main.o: /usr/include/asm/socket.h /usr/include/asm-generic/socket.h
main.o: /usr/include/asm/sockios.h /usr/include/asm-generic/sockios.h
main.o: /usr/include/bits/in.h /usr/include/rpc/netdb.h
main.o: /usr/include/bits/netdb.h /usr/include/arpa/inet.h WorldModel.h
main.o: Objects.h SoccerTypes.h Geometry.h /usr/include/math.h
main.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
main.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
main.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
main.o: /usr/include/bits/mathcalls.h ServerSettings.h GenericValues.h
main.o: PlayerSettings.h Logger.h /usr/include/sys/time.h LoggerDraw.h
main.o: Formations.h /usr/include/pthread.h /usr/include/sched.h
main.o: /usr/include/bits/sched.h /usr/include/signal.h
main.o: /usr/include/bits/setjmp.h ActHandler.h KeepawayPlayer.h
main.o: BasicPlayer.h SMDPAgent.h HandCodedAgent.h Parse.h
main.o: /usr/include/string.h /usr/include/xlocale.h /usr/include/stdlib.h
main.o: /usr/include/alloca.h
