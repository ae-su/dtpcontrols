#!/bin/bash

#------------------------------------------------------------------------------
declare -a missing_pypkg
missing_pypkg=()

function chkpypkg() {
  if python -c "import pkgutil; raise SystemExit(1 if pkgutil.find_loader('${1}') is None else 0)" &> /dev/null; then

    if [[ ! -z "$2" ]]; then
        if python -c "import ${1}; assert ${1}.__version__=='${2}'" &> /dev/null; then
            echo "${1} (${2}) is installed"
        else
            echo "${1} - wrong version installed - expected ${2}, detected $(python -c "import ${1}; print ${1}.__version__")"
            missing_pypkg+=(${1})
        fi
    else
        echo "${1} is installed"
    fi

else
    echo "Error: package '${1}' is not installed"
    missing_pypkg+=(${1})
fi
}
#------------------------------------------------------------------------------

chkpypkg uhal
chkpypkg click
chkpypkg future

(( ${#missing_pypkg[@]} > 0 )) &&  return 1
unset missing_pypkg

# get installation location
SCRIPT=$(readlink -f "$BASH_SOURCE")
INSTALL_LOC=$(dirname "$SCRIPT")

echo "Installation location :" $INSTALL_LOC

export DF_ROOT="$INSTALL_LOC"
# set environment variables
export CONNECTION_FILE="$DF_ROOT/etc/connections.xml"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/opt/cactus/lib"
export PYTHONPATH="$PYTHONPATH:$DF_ROOT/controls"
export PATH="$PATH:$DF_ROOT/bin"

eval "$(_HFBUTLER_COMPLETE=source hfButler.py)"
eval "$(_HFDRIVER_COMPLETE=source hfDriver.py)"
eval "$(_HFWATCHER_COMPLETE=source hfWatcher.py)"
eval "$(_HFWIBULATOR_COMPLETE=source hfWibulator.py)"

