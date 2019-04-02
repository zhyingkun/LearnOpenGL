#! /usr/bin/env bash

usage(){
	echo "
    [sudo] sh $0 <appName>

        <appName>: The OpenGL app you want to delete.
		"
}
exitWhileError(){
	if test $? -ne 0 ; then
		echo "
        Error Message: $1
        Please Check The Error And Test Again! Exit Now.
        "
		exit
	fi
}

if test $# -ne 1 ; then
	usage
	exit
fi

appName=`echo $1 | sed "s/\/$//"`
# echo ${appName}

if ! test -d ${appName} ; then
	echo \"${appName}\"" app does not exist!!! Exit Now."
	exit
fi

echo "Delete Directories ..."
rm -rf ${appName}
exitWhileError "Delete Directories failed"

echo "Delete features from CMakeLists.txt ..."
hostSystem=`uname -s`
if [ $hostSystem == "Darwin" ]; then
	sed -i "" '/add_subdirectory('${appName}')/d' CMakeLists.txt
	sed -i "" '/set_property(TARGET '${appName}' PROPERTY FOLDER "app")/d' CMakeLists.txt
else
	sed -i '/add_subdirectory('${appName}')/d' CMakeLists.txt
	sed -i '/set_property(TARGET '${appName}' PROPERTY FOLDER "app")/d' CMakeLists.txt
fi
exitWhileError "Delete features from CMakeLists.txt failed"

echo "All done."
