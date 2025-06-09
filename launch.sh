set -euo pipefail
IFS=$' \n\t'

echo "##########################################################"
echo "#               Compile Grammar of Prime                 #"
echo "##########################################################"

if [[ "$PWD" != *"/GrammarOfPrime" ]]; then
    echo "[!] Refusing to run outside of project root."
    exit 1
fi

DEBUG_FLAGS="-fsanitize=address -g -O0 -Wall -Werror"
NO_OPT_FLAGS="-O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls"
LIGHT_DBG_FLAGS="-g -O0 -Wall -Werror -fno-optimize-sibling-calls"
INCLUDE_FLAGS="-Iinclude -Isrc -Isrc/tsp -Isrc/memory -Isrc/neon -Isrc/grammar -Isrc/triangle -Isrc/sieve"
CFLAGS=$LIGHT_DBG_FLAGS 
TEST_ONLY=false
CLEAN_ONLY=false
NO_RUN=false

for arg in "$@"; do 
    case "$arg" in 
        -r|--no-run)
            echo "[!] Compilation only - skipping run."
            NO_RUN=true
            ;;
        -c|--clean)
            echo "[!] Clean only."
            CLEAN_ONLY=true
            ;;
        -d|--debug)
            echo "[!] Debug mode enable."
            CFLAGS=$DEBUG_FLAGS
            ;;
        -t|--test-only)
            echo "[!] Running in test-only mode."
            TEST_ONLY=true;;
        -n|--no-optimize)
            echo "[!] Running with no compiler optimization."
            CFLAGS=$NO_OPT_FLAGS
            ;;
        *)
            echo "Syntax: launch.sh [flag][flag]"
            echo "Flags --no-run, -r, --clean, -c, --debug, -d, --test-only, -t, --no-optimize, -n (overwrites --debug)"
            ;;
    esac
done

mkdir -p build
mkdir -p bin

if [[ "$PWD" != *"/GrammarOfPrime" ]]; then
    echo "[!] Not in project root Aborting cleanup."
    exit 1
fi

if [[ -d "./build" ]]; then
    echo "[.] Clearing previous build....."
    rm -rf "./build/"*.o
fi

if [[ -d "./bin" ]]; then
    echo "[.] Clearing previous bin....."
    rm -rf "./bin/"*
fi

if [[ -d "./tests/test_lib/" ]]; then
    echo "[.] Clearing previous tests...."
    rm -rf ".tests/test_lib/"*
fi

if [ "$CLEAN_ONLY" = true ]; then
    echo "[X] Bin/Build clean up complete"
    exit 0
fi

echo "[.] Compiling object files..."
echo "[DBG] Compiling with flags: " $CFLAGS

clang -std=c99 $CFLAGS -c src/memory/page_arena.c -o build/page_arena.o $INCLUDE_FLAGS
clang -std=c99 $CFLAGS -c src/neon/neon_util.c -o build/neon_util.o $INCLUDE_FLAGS
clang -std=c99 $CFLAGS -c src/sieve/Gsub210.c -o build/Gsub210.o $INCLUDE_FLAGS
clang -std=c99 $CFLAGS -c src/grammar/alpha2.c -o build/alpha2.o $INCLUDE_FLAGS
clang -std=c99 $CFLAGS -c src/sieve/geometerPattern.c -o build/geometerPattern.o $INCLUDE_FLAGS
#add as needed here:

#add "runner" here:
TARGET="bin/gsub210"
clang -std=c99 $CFLAGS src/main.c build/*.o -o $TARGET $INCLUDE_FLAGS

if [ $? -ne 0 ]; then
    echo "[ ] Compilation/Linkage Failed."
    exit 1
fi

echo "[X] Main Compilation Complete"

if [ "$TEST_ONLY" = true ]; then
    echo
    echo "##########################################################"
    echo "#                   Running Unit Tests....               #"
    echo "##########################################################"

    if ! ./test.sh; then
        echo "[ ] Test compilation failed."
        exit 1
    fi

    if ! ./runtests.sh; then
        echo "[ ] Unit tests failed."
        exit 1
    fi

    echo "[X] All tests passed."
    exit 0

fi

echo 
echo "##########################################################"
echo "#                   Running Unit Tests....               #"
echo "##########################################################"

if ! ./test.sh; then
    echo "[ ] Test compilation failed."
    exit 1
fi

if ! ./runtests.sh; then
    echo "[ ] Unit tests failed."
    exit 1
fi

echo "[X] All tests passed."
echo
echo "##########################################################"
echo "#                  Begin Grammar of Prime                #"
echo "##########################################################"
echo

if [ "$NO_RUN" = true ]; then
    echo "[X] Compilation complete - exiting....."
    exit 0
fi

./$TARGET

