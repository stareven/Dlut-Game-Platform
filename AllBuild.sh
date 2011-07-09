#!/bin/bash
find . -path '*-build-desktop' -exec make -C {} \;
read -N 1
