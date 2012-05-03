#============================================================================
#  Name:
#    $(TARGET).MAK
#
#  Description:
#    Makefile to build the $(TARGET) downloadable module.
#
#   The following nmake targets are available in this makefile:
#
#     all           - make .elf and .mod image files (default)
#     clean         - delete object directory and image files
#     filename.o    - make object file
#
#   The above targets can be made with the following command:
#
#     nmake /f $(TARGET).mak [target]
#
#  Assumptions:
#    1. The environment variable ADSHOME is set to the root directory of the
#       arm tools.
#    2. The version of ADS is 1.2 or above.
#
#  Notes:
#    None.
#
#
#        Copyright ?2000-2001 QUALCOMM Incorporated.
#               All Rights Reserved.
#            QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#============================================================================
ARM_HOME       =$(ARMHOME)
BREW_HOME      =$(BREWDIR)
TARGET         =sxmDemo1
OBJS           = AEEAPP~1.o AEEMOD~1.o \
                 MTK/APageScreen.o MTK/AppGlobal.o MTK/AppHandler.o MTK/BaseScreen.o \
                 Frame/Configure.o Frame/Page.o Frame/pre.o Frame/ResPool.o Frame/Tasks.o \
                 Page/PreLoad.o Page/Session1.o
                
APP_INCLUDES   =
APP_LIBS       = $(BREWDIR)/sxmsdk/sxm_jlib.a   $(BREWDIR)/sxmsdk/sxm_font.a  $(BREWDIR)/sxmsdk/libappdll.a
#-------------------------------------------------------------------------------
# Target file name and type definitions
#-------------------------------------------------------------------------------

EXETYPE    = elf                # Target image file format
MODULE     = mod                # Downloadable module extension

#-------------------------------------------------------------------------------
# Target compile time symbol definitions
#
# Tells the SDK source stuffs that we're building a dynamic app.
#-------------------------------------------------------------------------------

DYNAPP          = -DDYNAMIC_APP


#-------------------------------------------------------------------------------
# Software tool and environment definitions
#-------------------------------------------------------------------------------

AEESRCPATH = $(BREW_HOME)\src
AEEINCPATH = $(BREW_HOME)\inc

ARMBIN = $(ARM_HOME)\bin        # ARM ADS application directory
ARMINC = $(ARM_HOME)\include    # ARM ADS include file directory
ARMLIB = $(ARM_HOME)\lib        # ARM ADS library directory

ARMCC    = $(ARMBIN)\armcc      # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
ARMCPP   = $(ARMBIN)\tcpp     #$(ARMBIN)\armcpp     # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
LD       = $(ARMBIN)\armlink     # ARM ADS linker
HEXTOOL  = $(ARMBIN)\lbmg     # ARM ADS utility to create hex file from image

OBJ_CMD    = -o                 # Command line option to specify output filename

#-------------------------------------------------------------------------------
# Processor architecture options
#-------------------------------------------------------------------------------

CPU = -cpu ARM7EJ-S             # ARM7TDMI target processor

#-------------------------------------------------------------------------------
# ARM Procedure Call Standard (APCS) options
#-------------------------------------------------------------------------------

ROPI     = ropi                 # Read-Only(code) Position independence
INTERWRK = interwork            # Allow ARM-Thumb interworking

APCS = -apcs /$(ROPI)/$(INTERWRK)/norwpi

#-------------------------------------------------------------------------------
# Additional compile time error checking options
#-------------------------------------------------------------------------------

CHK = -fa                       # Check for data flow anomolies

#-------------------------------------------------------------------------------
# Compiler output options
#-------------------------------------------------------------------------------

OUT = -c                        # Object file output only

#-------------------------------------------------------------------------------
# Compiler/assembler debug options
#-------------------------------------------------------------------------------

DBG = -g                        # Enable debug

#-------------------------------------------------------------------------------
# Compiler optimization options
#-------------------------------------------------------------------------------

OPT = -Ospace -O2               # Full compiler optimization for space

#-------------------------------------------------------------------------------
# Compiler code generation options
#-------------------------------------------------------------------------------

END = -littleend                # Compile for little endian memory architecture
ZA  = -zo                       # LDR may only access 32-bit aligned addresses

CODE = $(END) $(ZA)


#-------------------------------------------------------------------------------
# Include file search path options
#-------------------------------------------------------------------------------

INC = -I. -I$(AEEINCPATH) $(APP_INCLUDES)


#-------------------------------------------------------------------------------
# Compiler pragma emulation options
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
# Linker options
#-------------------------------------------------------------------------------

LINK_CMD = -o                    #Command line option to specify output file
                                 #on linking

ROPILINK = -ropi                 #Link image as Read-Only Position Independent

LINK_ORDER = -first AEEMod_Load

#-------------------------------------------------------------------------------
# HEXTOOL options
#-------------------------------------------------------------------------------

BINFORMAT = -bin


#-------------------------------------------------------------------------------
# Compiler flag definitions
#-------------------------------------------------------------------------------

CFLAGS0 = $(OUT) $(DYNAPP) $(CPU) $(APCS) $(CODE) $(CHK) $(DBG)
CFLAGS  = $(CFLAGS0) $(OPT)

#-------------------------------------------------------------------------------
# Linker flag definitions
#-------------------------------------------------------------------------------

# the -entry flag is not really needed, but it keeps the linker from reporting
# warning L6305W (no entry point).  The address
#LFLAGS = $(ROPILINK) -rwpi -entry 0x8000#
LFLAGS = $(ROPILINK) -reloc -entry AEEMod_Load  -info totals -info unused -map -symbols -list sxmsdk.lst -info sizes -xref  -v

#----------------------------------------------------------------------------
# Default target
#----------------------------------------------------------------------------

all :  $(TARGET).$(MODULE)

#----------------------------------------------------------------------------
# Clean target
#----------------------------------------------------------------------------

# The object subdirectory, target image file, and target hex file are deleted.

clean :
	@echo ---------------------------------------------------------------
	@echo CLEAN
	-del /f *.o
	-del /f test.bin
	-del /f $(TARGET).$(EXETYPE)
	-del /f $(TARGET).$(MODULE)
	@echo ---------------------------------------------------------------

#============================================================================
#                           DEFAULT SUFFIX RULES
#============================================================================

# The following are the default suffix rules used to compile all objects that
# are not specifically included in one of the module specific rules defined
# in the next section.

# The following macros are used to specify the output object file, MSG_FILE
# symbol definition and input source file on the compile line in the rules
# defined below.

SRC_CPP_FILE = $(@F:.o=.cpp)      # Input source file specification
SRC_C_FILE   = $(@F:.o=.c)      # Input source file specification
OBJ_FILE = $(OBJ_CMD) $(@F)   # Output object file specification

.SUFFIXES :
.SUFFIXES : .o .dep .c .cpp

#--------------------------------------------------------------------------
# C code inference rules
#----------------------------------------------------------------------------

.cpp.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCPP) $(CFLAGS) $(INC) $(OBJ_FILE) $(SRC_CPP_FILE)
	@echo ---------------------------------------------------------------


{$(AEESRCPATH)}.c.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE) $(AEESRCPATH)\$(SRC_C_FILE)
	@echo ---------------------------------------------------------------

#===============================================================================
#                           MODULE SPECIFIC RULES
#===============================================================================

APP_OBJS =  $(OBJS)

#----------------------------------------------------------------------------
# Lib file targets
#----------------------------------------------------------------------------

$(TARGET).$(MODULE) : $(TARGET).$(EXETYPE)
	@echo ---------------------------------------------------------------
	@echo TARGET $@
# $(HEXTOOL)  $(TARGET).$(EXETYPE) $(BINFORMAT) $(TARGET).$(MODULE)
	$(HEXTOOL)  --verbose  $(TARGET).$(EXETYPE)

$(TARGET).$(EXETYPE) : $(APP_OBJS)
	@echo ---------------------------------------------------------------
	@echo TARGET $@
	$(LD) $(LINK_CMD) $(TARGET).$(EXETYPE) $(LFLAGS) $(**F) $(APP_LIBS) $(LINK_ORDER)

#----------------------------------------------------------------------------
# Applet Specific Rules
#----------------------------------------------------------------------------


RULE1 = r:\brew\sdk2\src
{$(RULE1)}.c.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE)  $(RULE1)\$(SRC_C_FILE)
	@echo ---------------------------------------------------------------


RULE2 = r:\SXMSDK~1\demos\sxmDemo1
{$(RULE2)}.c.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE)  $(RULE2)\$(SRC_C_FILE)
	@echo ---------------------------------------------------------------

RULE3= MTK
{$(RULE3)}.cpp.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCPP) $(CFLAGS) $(INC) -o $(@F) $(RULE3)\$(SRC_CPP_FILE)
	@echo ---------------------------------------------------------------

RULE4= Frame
{$(RULE4)}.cpp.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCPP) $(CFLAGS) $(INC) -o $(@F) $(RULE4)\$(SRC_CPP_FILE)
	@echo ---------------------------------------------------------------

RULE5= Page
{$(RULE5)}.cpp.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCPP) $(CFLAGS) $(INC) -o $(@F) $(RULE5)\$(SRC_CPP_FILE)
	@echo ---------------------------------------------------------------

# --------------------------------------------
# DEPENDENCY LIST, DO NOT EDIT BELOW THIS LINE
# --------------------------------------------
