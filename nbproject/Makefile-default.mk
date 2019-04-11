#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c Stacks.c Algorithm/Dijekstra.c Algorithm/MapMaze.c Algorithm/MappingFunctions.c Integration/Motors.c Integration/Sensors.c Integration/Setup.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/Stacks.o ${OBJECTDIR}/Algorithm/Dijekstra.o ${OBJECTDIR}/Algorithm/MapMaze.o ${OBJECTDIR}/Algorithm/MappingFunctions.o ${OBJECTDIR}/Integration/Motors.o ${OBJECTDIR}/Integration/Sensors.o ${OBJECTDIR}/Integration/Setup.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/Stacks.o.d ${OBJECTDIR}/Algorithm/Dijekstra.o.d ${OBJECTDIR}/Algorithm/MapMaze.o.d ${OBJECTDIR}/Algorithm/MappingFunctions.o.d ${OBJECTDIR}/Integration/Motors.o.d ${OBJECTDIR}/Integration/Sensors.o.d ${OBJECTDIR}/Integration/Setup.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/Stacks.o ${OBJECTDIR}/Algorithm/Dijekstra.o ${OBJECTDIR}/Algorithm/MapMaze.o ${OBJECTDIR}/Algorithm/MappingFunctions.o ${OBJECTDIR}/Integration/Motors.o ${OBJECTDIR}/Integration/Sensors.o ${OBJECTDIR}/Integration/Setup.o

# Source Files
SOURCEFILES=main.c Stacks.c Algorithm/Dijekstra.c Algorithm/MapMaze.c Algorithm/MappingFunctions.c Integration/Motors.c Integration/Sensors.c Integration/Setup.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4011
MP_LINKER_FILE_OPTION=,-Tp30F4011.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    
	
${OBJECTDIR}/Stacks.o: Stacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stacks.o.d 
	@${RM} ${OBJECTDIR}/Stacks.o.ok ${OBJECTDIR}/Stacks.o.err 
	@${RM} ${OBJECTDIR}/Stacks.o 
	@${FIXDEPS} "${OBJECTDIR}/Stacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Stacks.o.d" -o ${OBJECTDIR}/Stacks.o Stacks.c    
	
${OBJECTDIR}/Algorithm/Dijekstra.o: Algorithm/Dijekstra.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Algorithm" 
	@${RM} ${OBJECTDIR}/Algorithm/Dijekstra.o.d 
	@${RM} ${OBJECTDIR}/Algorithm/Dijekstra.o.ok ${OBJECTDIR}/Algorithm/Dijekstra.o.err 
	@${RM} ${OBJECTDIR}/Algorithm/Dijekstra.o 
	@${FIXDEPS} "${OBJECTDIR}/Algorithm/Dijekstra.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Algorithm/Dijekstra.o.d" -o ${OBJECTDIR}/Algorithm/Dijekstra.o Algorithm/Dijekstra.c    
	
${OBJECTDIR}/Algorithm/MapMaze.o: Algorithm/MapMaze.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Algorithm" 
	@${RM} ${OBJECTDIR}/Algorithm/MapMaze.o.d 
	@${RM} ${OBJECTDIR}/Algorithm/MapMaze.o.ok ${OBJECTDIR}/Algorithm/MapMaze.o.err 
	@${RM} ${OBJECTDIR}/Algorithm/MapMaze.o 
	@${FIXDEPS} "${OBJECTDIR}/Algorithm/MapMaze.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Algorithm/MapMaze.o.d" -o ${OBJECTDIR}/Algorithm/MapMaze.o Algorithm/MapMaze.c    
	
${OBJECTDIR}/Algorithm/MappingFunctions.o: Algorithm/MappingFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Algorithm" 
	@${RM} ${OBJECTDIR}/Algorithm/MappingFunctions.o.d 
	@${RM} ${OBJECTDIR}/Algorithm/MappingFunctions.o.ok ${OBJECTDIR}/Algorithm/MappingFunctions.o.err 
	@${RM} ${OBJECTDIR}/Algorithm/MappingFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/Algorithm/MappingFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Algorithm/MappingFunctions.o.d" -o ${OBJECTDIR}/Algorithm/MappingFunctions.o Algorithm/MappingFunctions.c    
	
${OBJECTDIR}/Integration/Motors.o: Integration/Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Integration" 
	@${RM} ${OBJECTDIR}/Integration/Motors.o.d 
	@${RM} ${OBJECTDIR}/Integration/Motors.o.ok ${OBJECTDIR}/Integration/Motors.o.err 
	@${RM} ${OBJECTDIR}/Integration/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/Integration/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Integration/Motors.o.d" -o ${OBJECTDIR}/Integration/Motors.o Integration/Motors.c    
	
${OBJECTDIR}/Integration/Sensors.o: Integration/Sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Integration" 
	@${RM} ${OBJECTDIR}/Integration/Sensors.o.d 
	@${RM} ${OBJECTDIR}/Integration/Sensors.o.ok ${OBJECTDIR}/Integration/Sensors.o.err 
	@${RM} ${OBJECTDIR}/Integration/Sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/Integration/Sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Integration/Sensors.o.d" -o ${OBJECTDIR}/Integration/Sensors.o Integration/Sensors.c    
	
${OBJECTDIR}/Integration/Setup.o: Integration/Setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Integration" 
	@${RM} ${OBJECTDIR}/Integration/Setup.o.d 
	@${RM} ${OBJECTDIR}/Integration/Setup.o.ok ${OBJECTDIR}/Integration/Setup.o.err 
	@${RM} ${OBJECTDIR}/Integration/Setup.o 
	@${FIXDEPS} "${OBJECTDIR}/Integration/Setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Integration/Setup.o.d" -o ${OBJECTDIR}/Integration/Setup.o Integration/Setup.c    
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    
	
${OBJECTDIR}/Stacks.o: Stacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stacks.o.d 
	@${RM} ${OBJECTDIR}/Stacks.o.ok ${OBJECTDIR}/Stacks.o.err 
	@${RM} ${OBJECTDIR}/Stacks.o 
	@${FIXDEPS} "${OBJECTDIR}/Stacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Stacks.o.d" -o ${OBJECTDIR}/Stacks.o Stacks.c    
	
${OBJECTDIR}/Algorithm/Dijekstra.o: Algorithm/Dijekstra.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Algorithm" 
	@${RM} ${OBJECTDIR}/Algorithm/Dijekstra.o.d 
	@${RM} ${OBJECTDIR}/Algorithm/Dijekstra.o.ok ${OBJECTDIR}/Algorithm/Dijekstra.o.err 
	@${RM} ${OBJECTDIR}/Algorithm/Dijekstra.o 
	@${FIXDEPS} "${OBJECTDIR}/Algorithm/Dijekstra.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Algorithm/Dijekstra.o.d" -o ${OBJECTDIR}/Algorithm/Dijekstra.o Algorithm/Dijekstra.c    
	
${OBJECTDIR}/Algorithm/MapMaze.o: Algorithm/MapMaze.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Algorithm" 
	@${RM} ${OBJECTDIR}/Algorithm/MapMaze.o.d 
	@${RM} ${OBJECTDIR}/Algorithm/MapMaze.o.ok ${OBJECTDIR}/Algorithm/MapMaze.o.err 
	@${RM} ${OBJECTDIR}/Algorithm/MapMaze.o 
	@${FIXDEPS} "${OBJECTDIR}/Algorithm/MapMaze.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Algorithm/MapMaze.o.d" -o ${OBJECTDIR}/Algorithm/MapMaze.o Algorithm/MapMaze.c    
	
${OBJECTDIR}/Algorithm/MappingFunctions.o: Algorithm/MappingFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Algorithm" 
	@${RM} ${OBJECTDIR}/Algorithm/MappingFunctions.o.d 
	@${RM} ${OBJECTDIR}/Algorithm/MappingFunctions.o.ok ${OBJECTDIR}/Algorithm/MappingFunctions.o.err 
	@${RM} ${OBJECTDIR}/Algorithm/MappingFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/Algorithm/MappingFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Algorithm/MappingFunctions.o.d" -o ${OBJECTDIR}/Algorithm/MappingFunctions.o Algorithm/MappingFunctions.c    
	
${OBJECTDIR}/Integration/Motors.o: Integration/Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Integration" 
	@${RM} ${OBJECTDIR}/Integration/Motors.o.d 
	@${RM} ${OBJECTDIR}/Integration/Motors.o.ok ${OBJECTDIR}/Integration/Motors.o.err 
	@${RM} ${OBJECTDIR}/Integration/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/Integration/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Integration/Motors.o.d" -o ${OBJECTDIR}/Integration/Motors.o Integration/Motors.c    
	
${OBJECTDIR}/Integration/Sensors.o: Integration/Sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Integration" 
	@${RM} ${OBJECTDIR}/Integration/Sensors.o.d 
	@${RM} ${OBJECTDIR}/Integration/Sensors.o.ok ${OBJECTDIR}/Integration/Sensors.o.err 
	@${RM} ${OBJECTDIR}/Integration/Sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/Integration/Sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Integration/Sensors.o.d" -o ${OBJECTDIR}/Integration/Sensors.o Integration/Sensors.c    
	
${OBJECTDIR}/Integration/Setup.o: Integration/Setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Integration" 
	@${RM} ${OBJECTDIR}/Integration/Setup.o.d 
	@${RM} ${OBJECTDIR}/Integration/Setup.o.ok ${OBJECTDIR}/Integration/Setup.o.err 
	@${RM} ${OBJECTDIR}/Integration/Setup.o 
	@${FIXDEPS} "${OBJECTDIR}/Integration/Setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Integration/Setup.o.d" -o ${OBJECTDIR}/Integration/Setup.o Integration/Setup.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ADC_testing.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
