#!/bin/bash

#get source directory and move to it
WORKINGDIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd "$WORKINGDIR"


#function to update github and creditials should be saved
git_update()
{
if [ -d $1 ]; then
	cd $1
	if git status | grep modified > /dev/null;
	then
		git add .
		git commit -m "auto commit"
		git push
		notify-send "$1 updated!"
	fi
fi
}

#update my repos
git_update "/home/malik/Documents/GitHub/OpenBOR_DoubleDragon_Malik"

#find and run scorpion
cd "$WORKINGDIR"
./OpenBOR_3.0_6391.AppImage
