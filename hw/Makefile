# Author: Vincenzo Merola <vincenzo.merola2@unina.it>
# Description:
#   This Makefile uses Vitis compiler to simulate and synthesize HLS kernel

DIR = matmul

VITIS_HLS = vitis-run --mode hls
VPP = v++
VFLAGS = -c --mode hls
CSIM = ${VITIS_HLS} --csim
COSIM = ${VITIS_HLS} --cosim
SYN = ${VPP} ${VFLAGS}
PACK = ${VITIS_HLS} --package
IMPL = ${VITIS_HLS} --impl
IP = ${DIR}_hls

CONFIG = --config src/hls_config.cfg
WORK_DIR = --work_dir ${DIR}


.PHONY: csim
csim:
	@echo
	@echo "C-Simulation starting..."
	${CSIM} ${CONFIG} ${WORK_DIR}
	@echo "C-Simulation ended"
	@echo


.PHONY: syn
syn:
	@echo
	@echo "Synthesis starting..."
	${SYN} ${CONFIG} ${WORK_DIR}
	@echo "Synthesis ended"
	@echo


.PHONY: cosim
cosim:
	@echo
	@echo "Cosimulation starting ..."
	${COSIM} ${CONFIG} ${WORK_DIR}
	@echo "Cosimulation ended"
	@echo


.PHONY: package
package:
	@echo
	@echo "Packaging IP..."
	${PACK} ${CONFIG} ${WORK_DIR}
	@echo "Packaging ended"
	@echo


.PHONY: impl
impl:
	@echo
	@echo "Running implementation"
	${IMPL} ${CONFIG} ${WORK_DIR}
	@echo "Implementation ended"
	@echo


.PHONY: clean
clean:
	@echo "Cleaning..."
	rm -f ${IP}.zip

	rm -fr ${DIR}
	rm -f xcd.log
	rm -fr .Xil