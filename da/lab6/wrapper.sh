#!/usr/bin/env bash

for test_file in `ls *.t`; do
    echo "Execute ${test_file}"
    if ! ./solution < $test_file > last_answer ; then
        echo "ERROR"
        continue
    fi
    answer_file="${test_file%.*}"

    if ! diff -u "${answer_file}.a" last_answer ; then
        echo "Failed"
    else
        echo "OK"
    fi 
done