#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=i586-pc-elf-gcc
CCC=g++
CXX=g++
FC=gfortran
AS=nasm

# Macros
CND_PLATFORM=MinGW_ELF-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/0-Noyau_Start.o \
	${OBJECTDIR}/1-Noyau_Main.o \
	${OBJECTDIR}/API.o \
	${OBJECTDIR}/Allocation_Pages.o \
	${OBJECTDIR}/Appels_Systeme.o \
	${OBJECTDIR}/BitMap_Memoire.o \
	${OBJECTDIR}/Buffer_Manager.o \
	${OBJECTDIR}/CallBack_Clavier.o \
	${OBJECTDIR}/CallBack_Exception.o \
	${OBJECTDIR}/CallBack_IRQ.o \
	${OBJECTDIR}/CallBack_VIDEO.o \
	${OBJECTDIR}/Commutation.o \
	${OBJECTDIR}/Descripteurs.o \
	${OBJECTDIR}/EXCEPTIONS.o \
	${OBJECTDIR}/Ecran.o \
	${OBJECTDIR}/HARD_8042_Clavier.o \
	${OBJECTDIR}/HARD_8253_Timer.o \
	${OBJECTDIR}/IRQ.o \
	${OBJECTDIR}/Init_GDT.o \
	${OBJECTDIR}/Init_IDT.o \
	${OBJECTDIR}/Init_TSS.o \
	${OBJECTDIR}/Ordonnanceur.o \
	${OBJECTDIR}/Outils.o \
	${OBJECTDIR}/PIC_8259A.o \
	${OBJECTDIR}/Pagination.o \
	${OBJECTDIR}/Processus.o \
	${OBJECTDIR}/Screen_Manager.o


# C Compiler Flags
CFLAGS=-m32

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=-f elf

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	i586-pc-elf-ld.exe -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv ${OBJECTFILES} ${LDLIBSOPTIONS} -Ttext=0x100000 -Tdata=0x200000 --entry=_start --oformat i586-pc-elf -Map=Noyau.map -s

${OBJECTDIR}/0-Noyau_Start.o: 0-Noyau_Start.ASM 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/0-Noyau_Start.o 0-Noyau_Start.ASM

${OBJECTDIR}/1-Noyau_Main.o: 1-Noyau_Main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/1-Noyau_Main.o 1-Noyau_Main.c

${OBJECTDIR}/API.o: API.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/API.o API.c

${OBJECTDIR}/Allocation_Pages.o: Allocation_Pages.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Allocation_Pages.o Allocation_Pages.c

${OBJECTDIR}/Appels_Systeme.o: Appels_Systeme.ASM 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/Appels_Systeme.o Appels_Systeme.ASM

${OBJECTDIR}/BitMap_Memoire.o: BitMap_Memoire.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/BitMap_Memoire.o BitMap_Memoire.c

${OBJECTDIR}/Buffer_Manager.o: Buffer_Manager.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Buffer_Manager.o Buffer_Manager.c

${OBJECTDIR}/CallBack_Clavier.o: CallBack_Clavier.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/CallBack_Clavier.o CallBack_Clavier.c

${OBJECTDIR}/CallBack_Exception.o: CallBack_Exception.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/CallBack_Exception.o CallBack_Exception.c

${OBJECTDIR}/CallBack_IRQ.o: CallBack_IRQ.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/CallBack_IRQ.o CallBack_IRQ.c

${OBJECTDIR}/CallBack_VIDEO.o: CallBack_VIDEO.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/CallBack_VIDEO.o CallBack_VIDEO.c

${OBJECTDIR}/Commutation.o: Commutation.ASM 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/Commutation.o Commutation.ASM

${OBJECTDIR}/Descripteurs.o: Descripteurs.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Descripteurs.o Descripteurs.c

${OBJECTDIR}/EXCEPTIONS.o: EXCEPTIONS.asm 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/EXCEPTIONS.o EXCEPTIONS.asm

${OBJECTDIR}/Ecran.o: Ecran.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Ecran.o Ecran.c

${OBJECTDIR}/HARD_8042_Clavier.o: HARD_8042_Clavier.ASM 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/HARD_8042_Clavier.o HARD_8042_Clavier.ASM

${OBJECTDIR}/HARD_8253_Timer.o: HARD_8253_Timer.asm 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/HARD_8253_Timer.o HARD_8253_Timer.asm

${OBJECTDIR}/IRQ.o: IRQ.ASM 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -f elf -o ${OBJECTDIR}/IRQ.o IRQ.ASM

${OBJECTDIR}/Init_GDT.o: Init_GDT.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Init_GDT.o Init_GDT.c

${OBJECTDIR}/Init_IDT.o: Init_IDT.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -nostdlib -MMD -MP -MF $@.d -o ${OBJECTDIR}/Init_IDT.o Init_IDT.c

${OBJECTDIR}/Init_TSS.o: Init_TSS.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Init_TSS.o Init_TSS.c

${OBJECTDIR}/Ordonnanceur.o: Ordonnanceur.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Ordonnanceur.o Ordonnanceur.c

${OBJECTDIR}/Outils.o: Outils.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Outils.o Outils.c

${OBJECTDIR}/PIC_8259A.o: PIC_8259A.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/PIC_8259A.o PIC_8259A.c

${OBJECTDIR}/Pagination.o: Pagination.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Pagination.o Pagination.c

${OBJECTDIR}/Processus.o: Processus.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Processus.o Processus.c

${OBJECTDIR}/Screen_Manager.o: Screen_Manager.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Screen_Manager.o Screen_Manager.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
