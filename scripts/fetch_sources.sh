#!/bin/bash
# Author: Vincenzo Merola <vincenzo.merola2@unina.it>

# Description:
# This script downloads Vitis HLS GEMM sources and flattens them into an rtl/ directory.

# To execute: ./fetch_sources.sh
# To execute you need:
#   git
#   Vitis 2024.2

# Colors
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

COMP_NAME=matmul
GIT_URL=https://github.com/Vincenzo0709/Vitis_HLS_accelerators.git
GIT_TAG=${COMP_NAME}
CLONE_DIR=Vitis_HLS_accelerators
HW=${CLONE_DIR}/hw

# Display help
Help()
{
   echo
   echo "This script downloads Vitis HLS matmul sources and flattens them into an rtl/ directory."
   echo
   echo "Syntax: fetch_source.sh [--option]"
   echo
   echo "options:"
   echo "-h | --help            Prints help"
   echo
}

Flatten()
{
    # Create build dir
    if ! [ -d hw/ ]; then
        mkdir hw
    fi
    cd hw
    rm -rf build/
    mkdir build/
    mkdir build/rtl
    mkdir build/ip

    # Clone repo and update submodule to specific branch
    printf "${YELLOW}[FETCH_SOURCES] Cloning source repository${NC}\n"
    git clone ${GIT_URL} -b ${GIT_TAG} ${CLONE_DIR}

    # Clone Bender (future development)
    # printf "${YELLOW}[FETCH_SOURCES] Download Bender${NC}\n"
    # curl --proto '=https' --tlsv1.2 https://pulp-platform.github.io/bender/init -sSf | sh

    # Copy all RTL files into rtl dir
    printf "${YELLOW}[FETCH_SOURCES] Copying all sources into rtl${NC}\n"
    cd ${HW}
    make syn
    cp -r ${COMP_NAME}/hls/syn/verilog/* ../../build/rtl
    make package
    cp ${COMP_NAME}_hls.zip ../../build/
    cp -r ${COMP_NAME}/hls/impl/ip/* ../../build/ip
    cd ../..

    # Delete the cloned repo
    printf "${YELLOW}[FETCH_SOURCES] Cleaning all artifacts${NC}\n"
    sudo rm -r ${CLONE_DIR}
    printf "${GREEN}[FETCH_SOURCES] Completed${NC}\n"
}


OPTS=$(getopt -o h --long help -n 'fetch_sources.sh' -- "$@")
eval set -- "$OPTS"

if [ "$OPTS" != " --" ]; then
    while true; do
        case "$1" in
            -h | --help) 
                # Print help
                Help
                exit 0
                ;;
            --)
                shift
                break
                ;;
            ?)
                # Unrecognized options
                echo "Invalid option: -${OPTARG}."
                exit 1
                ;;
        esac
    done
fi


# Moving to right directory (if you cloned the whole repository instead of using only fetch_sources.sh)
cd "$(dirname "$0")" ; printf "\n${GREEN}[FETCH_SOURCES] Starting from directory `pwd -P`${NC}\n"
if [ "$(basename `pwd -P`)" == "scripts" ]; then
    cd .. ; printf "${GREEN}[FETCH_SOURCES] Moving to directory `pwd -P`${NC}\n"
fi

Flatten

