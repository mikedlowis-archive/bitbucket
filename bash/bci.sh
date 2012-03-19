#!/bin/env bash

START_BACKGROUND=0
START_CI=0
CONF_FILE=./repos
IDLE_TIME=5m
#ngfnote: i prefer $(pwd) to using backticks; don't think it makes a difference.
WORKING_DIR=`pwd`
REPO_LIST=()

#ngfnote: i prefer to do something like
#GIT="$(which git)"
#: ${GIT:?'git not found in path!'}
#then use '$GIT' instead of 'git' in code

#ngfnote, i'm sure you already know this, but cat <<-EOF will allow you to put
#indentation in before the lines being catted
#unfortunately, to get formatting of the cat correct, this requires you to mix tabs and spaces
#which is a no-no.
#alternatively, i've gotten in the habit of putting this in a USAGE file then doing something like
#usage(){ cat $USAGE_FILE }
usage() {
cat << EOF
usage $0 <options>

This script implements a primitive continuous integration server.

Options:
    -c <file>    Use the given configuration file
    -d <path>    Set the working directory for this script
    -B           Launch this script in the background
    -h           Prints usage message
    -S           Start the service in the foreground (do not daemonize)
    -t <time>    Time to wait between checking for repo changes
EOF
exit 1
}

#ngfnote: this is sort of conf file reading is done all the time
#so exactly the sort of thing i would prefer qball to have
load_config()
{
    if [[ -f $CONF_FILE && -r $CONF_FILE ]]; then
        REPO_LIST=(`cat $CONF_FILE`)
    else
        #ngfnote: i confused...why pass -n, then manually add newlines?
        #makes it clear that there's two newlines?
        #also, on the 8th day, god created stderr and saw it was good :-)
        echo -en "Error: Config file not found or is not readable: $CONF_FILE\n\n" &>2
        usage
    fi
}

#ngfnote: if you prefer functions to have a single return at the end in your C code
#they should only have one echo at the end in bash
has_updates()
{
    local curr_rev=`git rev-list --max-count=1 origin/master`
    local new_rev=`git ls-remote origin -h refs/heads/master | cut -f1`
    if [[ $curr_rev != $new_rev ]]; then
        echo 1
    else
        echo 0
    fi
}

#function qballcat(){
#    if [[ ! -r "$*" ]]; then
#        echo 'error!' &>2
#    else
#        cat "$*"
#    fi
#}
#
#blah="$(qballcat "somefile")"

build_repo()
{
    local fresh_checkout=0
    #ngfnote: local repodir="$2";
    #i hate using $1 and $2 beyond the first couple lines of a function :-(
    #unnamed variables makes the bash shitty to read
    #also, might be fun to use : ${repodir:=$DEFAULT}

    # Check out the repo if it isn't already
    if [[ ! -d $2 ]]; then
        mkdir $2
        git clone --recursive $1 $2
        fresh_checkout=1
    fi
    #ngfnote: if [[ ! -d "$repodir/.git/" ]]; then go_boom(); fi

    # change dir into the repo
    cd $2
    #ngfnote: quote your vars

    # Kickoff the build if we have updates
    #ngfnote: alot safer here if you put calls in quotes like:
    ##if [[ "$(has_updates)" == "1" || "$fresh_checkout" == "1" ]]; then ...
    if [[ `has_updates` == 1 || $fresh_checkout == 1 ]]; then
        local build_status=1 # Non zero means failed
        #ngfnote: make enums, probably global:
        #FAILED_BUILD=1
        #OK=0
        #then local build_status="$FAILED_BUILD"
        #or build_status="$OK"
        local build_cmd="`git config --local --get ci.cmd`"
        echo Build cmd: $build_cmd
        if [[ $build_cmd -ne '' ]]; then
            # Trigger the build and Log the results
            git pull
            $build_cmd > ../log/build.log
            build_status=$?
        else
            echo 'Error: No build command configured' > $WORKING_DIR/log/build.log
        fi
        echo $build_status,$2,`date` >> $WORKING_DIR/log/status.log
    fi
}

main_process() {
    #ngfnote: while [[ 1 ]]; do ...stop all the forking
    while [ 1 ]; do
        load_config

        #ngfnote: ooh, shiny! bash that i don't understand! :-)
        #i think that bash arrays aren't supported until version 4, and if memory serves
        #debian lenny (5) has 3.x, so i'd consider doing this differently
        #ngfnote: how i normally do this (no arrays)
        #while read $repo; do
        #    local repo_path="$(echo $repo | cut -d= -f1)"
        #    local repo_url="$(echo $repo | cut -d= -f2)"
        #    ...
        #done < $CONFIG_FILE
        for repo in "${REPO_LIST[@]}"
        do
            local repo_path=${repo%=*}
            local repo_url=${repo#*=}

            # Run the build in the background so that it doesn't kill our daemon
            build_repo $repo_url $repo_path &
        done

        #ngfnote: noooooooooooooooooooooooooooo! (sleep is for the weak)
        sleep $IDLE_TIME
    done
}

start_ci() {
    #ngfnote: again, quote everything for safety
    cd $WORKING_DIR
    if [[ $START_CI == 1 && $START_BACKGROUND == 1 ]]; then
        main_process &
    elif [[ $START_CI == 1 ]]; then
        main_process
    else
        usage
    fi
}

# parse our commandline options
while getopts “BSc:t:dh” OPTION
do
    #ngfnote: saves a lot of space to put casaes on one line, like
    #case $OPTION in
        #c) CONF_FILE="$OPTARG"     ;;
        #d) WORKING_DIR="$OPTARG"   ;;
        #...
    #esac
    case $OPTION in
        c)
            CONF_FILE=$OPTARG
            ;;

        d)
            WORKING_DIR=$OPTARG
            ;;
        B)
            START_BACKGROUND=1
            START_CI=1
            ;;

        S)
            START_CI=1
            ;;

        t)
            IDLE_TIME=$OPTARG
            ;;

        # Print usage and exit for -h and unknown
        h)
            usage
            ;;
        ?)
            usage
            ;;
    esac
done

# If we got this far then try to start the process
start_ci
#ngfnote: end file with blank line because it makes me happy for no apparent reason

