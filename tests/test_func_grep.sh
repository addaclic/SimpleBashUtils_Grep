#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s test_0_grep.txt VAR"
"for My_grep.c My_grep.h Makefile VAR"
"for My_grep.c VAR"
"My_grep.c -e for -e ^int My_grep.h Makefile VAR"
"My_grep.c  -e for -e ^int VAR"
"My_grep.c -e regex -e ^print VAR -f test_ptrn_grep.txt"
"Makefile -e while -e void My_grep.c VAR -f test_ptrn_grep.txt"
)

declare -a extra=(
"for test_1_grep.txt test_2_grep.txt -n"
"for test_1_grep.txt -n"
"test_1_grep.txt -n -e ^\}"
"-ce ^int test_1_grep.txt test_2_grep.txt"
"test_1_grep.txt -e ^int"
"-nivh = test_1_grep.txt test_2_grep.txt"
"-ie INT test_5_grep.txt"
"-echar test_1_grep.txt test_2_grep.txt"
"test_5_grep.txt -ne = -e out"
"-iv int test_5_grep.txt"
"-in int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-l for test_1_grep.txt test_2_grep.txt"
# "-o -e int test_4_grep.txt"
"test_5_grep.txt -e = -e out"
"test_6_grep.txt -e ing -e as -e the -e not -e is"
"-c -e . test_1_grep.txt -e '.'"
"-l for no_file.txt test_2_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./My_grep $t > test_My_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_My_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_My_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
    fi
    rm test_My_grep.log test_sys_grep.log
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in v c l n h
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in v c l n h
do
    for var2 in v c l n h
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 параметра
for var1 in v c l n h
do
    for var2 in v c l n h
    do
        for var3 in v c l n h
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 2 сдвоенных параметра
for var1 in v c l n h
do
    for var2 in v c l n h
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done

# 3 строенных параметра
for var1 in v c l n h
do
    for var2 in v c l n h
    do
        for var3 in v c l n h
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    testing $i
                done
            fi
        done
    done
done

echo -e "\033[31mFAIL: $FAIL\033[0m"
echo -e "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
rm Makefile My_grep.c My_grep.h My_grep

if [ $FAIL -eq 0 ]
then
    exit 0
else
    exit 1
fi