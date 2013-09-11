#!/bin/bash

# alamode-sentry.sh
# sample getopts and 
# input validation code

while getopts "f:" OPTIONS
  do
    case "$OPTIONS" in
			# N for NAME INPUT
      f)  if [ ! -z $READ_FILE ] # Check if we've parsed this flag already
          then
            echo "$0: does not support nultiple -f's"
            exit 1
          else
            if [ ! -z $OPTARG ] # Check to make sure a token was given with this flag
            then
              READ_FILE=$OPTARG
            else
              echo "$0: Must specify a file with hostnames/IPs with -f"
              exit 1
            fi
          fi;;
      \?) echo "usage: $0 [-d directory (OPTIONAL)] [-n IP or Name of computer] or [-f File containing names or IPs]"
          exit 1;;
    esac
  done

######## Begin input validation for -f flag ############

  if [ ! -f $READ_FILE ] #Check if file exists
  then
    echo "$0: The file \"$READ_FILE\" does not exist."
    exit 1
  fi
  
  if [ ! -r $READ_FILE ] #Check if we have read permissions
  then
    echo "$0: Cannot read \"$READ_FILE\"; check permissions."
    exit 1
  fi
########################################################