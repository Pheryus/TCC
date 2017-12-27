#!/bin/bash

pushd imagens

for gp in `ls *.gp`
do
    gnuplot $gp
done

mv -v *.tex *.eps ..

popd