#!/bin/bash
# Source this file to set up the 'dobld' alias for building the project from anywhere

alias bld="bash $(dirname $(realpath ${BASH_SOURCE[0]}))/scripts/build.sh"

alias test="$(dirname $(realpath ${BASH_SOURCE[0]}))/bin/core6502_tests.exe"


