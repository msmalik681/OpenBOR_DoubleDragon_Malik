#!/bin/bash

function extract () {

#check if there is a valid pak file
if [ `ls *.pak | wc -l` == "0" ]
then
echo "No pak files found run from folder containing pak files"
exit 1
fi

echo "The following pak archives were found, select one:"

# set the prompt used by select, replacing "#?"
PS3="Use number to select a file or 'stop' to cancel: "

# allow the user to choose a file
select filename in *.pak
do
    # leave the loop if the user says 'stop'
    if [[ "$REPLY" == stop ]]; then break; fi

    # complain if no file was selected, and loop to ask again
    if [[ "$filename" == "" ]]
    then
        echo "'$REPLY' is not a valid number"
        continue
    fi

    # now we can use the selected file
    echo "$filename will be extracted"
    ./borpak "$filename"
    echo "finished extracting $filename"
    # it'll ask for another unless we leave the loop
    break
done

}

function build () {
	if [ ! -d "data" ]
	then
	echo "data folder is missing, run from same location as data folder and spell in lower case."
	exit 1 
    else
    read -p "please enter file name for pak file: " PAK_NAME
    ./borpak -d data -b "$PAK_NAME.pak"
	fi
}

################################## MAIN #############################################

#set the bash file directory as the working directory
path="$( dirname "$( which "$0" )" )"
cd "$path"
echo "*borpak linux helper script by msmalik681*"
#check if borpak utility is in the same folder
if [ `ls borpak | wc -l` != "1" ]
then
echo "borpak utility is missing run this script from the same directory as borpak"
exit 1
fi

PS3='Please enter your choice: '
options=("extract a pak file" "build a pak file" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "extract a pak file")
            extract
            break
            ;;
        "build a pak file")
            build
            break
            ;;
        "Quit")
			exit 1
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done

