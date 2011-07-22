#!/bin/bash
find api/ -path 'api/lib*api' -exec make -C {} \;
find . -path '*-build-desktop' -exec make -C {} \;
printf "build finish . press any key to escape:"
read -N 1
