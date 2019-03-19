include ../Makefile.inc

GEN_EXE = 4.1_tee 4.2_hole 4.2_cp 5.1_atomic_append 5.2_append 5.3_atomic_append 5.5_dup_flags 5.6_dup

EXE = ${GEN_EXE}

all : ${EXE}

allgen : ${GEN_EXE}


clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
