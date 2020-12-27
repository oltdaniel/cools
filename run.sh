#!/usr/bin/env bash

# log function
log() {
    case $1 in
        "SUC")
            echo -ne "[\e[32mSUC\e[0m]"
            ;;
        "ERR")
            echo -ne "[\e[31mERR\e[0m]"
            ;;
        "INF")
            echo -ne "[\e[34mINF\e[0m]"
            ;;
        *)
            echo -ne "[$1]"
            ;;
    esac
    printf ": %s\n" "$2"
}

if [[ "$1" == "" ]]; then
    log "ERR" "no project given"
    exit 1
elif [[ ! -d $1 ]]; then
    log "ERR" "project does not exist"
    exit 1
fi

compile() {
    log "INF" "Compiling $1..."
    local filename=$(basename $1)
    local obj=$(dirname $1)/build/${filename%.c}.o
    mkdir -p "$(dirname $obj)"
    clang -c $1 -o "$obj" -I./$1
}

for src in $1/*.c; do
    compile "$src"
done

log "INF" "Linking..."
clang $1/build/*.o -o "$1/main"

log "INF" "Executing"
echo
$1/main