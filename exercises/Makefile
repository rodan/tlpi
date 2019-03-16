include ../Makefile.inc

GEN_EXE = 4.1_tee 4.2_hole 4.2_cp

EXE = ${GEN_EXE}

all : ${EXE}

allgen : ${GEN_EXE}


clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
