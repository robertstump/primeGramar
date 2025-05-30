echo
echo "##########################################################"
echo "#                 Compiling All Tests....                #"
echo "##########################################################"

clang -std=c99 -Wall -Werror tests/test_alpha2.c build/*.o -o tests/test_lib/alpha_tests2 -Iinclude -Isrc -Isrc/tsp -Isrc/memory -Isrc/grammar

if [ $? -eq 0 ]; then
    echo "[X] Tests compilation complete...."
    exit 0

fi

echo "[X] Compilation Failed"

