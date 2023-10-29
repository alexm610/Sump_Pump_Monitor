#!/bin/sh

#
# resolve symlinks
#

PRG=$0

while [ -h "$PRG" ]; do
    ls=`ls -ld "$PRG"`
    link=`expr "$ls" : '^.*-> \(.*\)$' 2>/dev/null`
    if expr "$link" : '^/' 2> /dev/null >/dev/null; then
	PRG="$link"
    else
	PRG="`dirname "$PRG"`/$link"
    fi
done

export here=`dirname $PRG`
export mplabx_dir=$here/..
export netbeans_dir=$mplabx_dir
export development_netbeans_dir=$mplabx_dir/mplabide-nb-platform/nbbuild/netbeans
export MPLABX_THIRDPARTY_LIB_PATH=$mplabx_dir/thirdparty/
if [ -d $development_netbeans_dir ];
    then export netbeans_dir=$development_netbeans_dir
fi
export mdb_jar=$mplabx_dir/lib/mdb.jar
export DYLD_LIBRARY_PATH=$here

# the file ../mplab_ide.conf contains the jdkhome. Extract this value.
# if you are using bash you can simply do:
# source ../etc/mplab_ide.conf
# instead of the following line
export eval `cat $here/../etc/mplab_ide.conf | sed -n /^jdkhome/p | sed -e 's/\"//g' -e 's/\/$//'`
export jvm=$jdkhome/bin/java

# Linux will ignore headless mode if DISPLAY is set
unset DISPLAY  
$jvm -Dfile.encoding=UTF-8 -Djava.awt.headless=true -jar $mdb_jar $@
