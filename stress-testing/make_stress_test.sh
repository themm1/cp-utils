# Creates directory 'stress-test' in CWD and sets up stress testing files.
# By default creates 'program.cpp' from first .cpp file in CWD. If not,
# program.cpp will contain default template. Creates also 'generator.py', 'run.sh',
# 'solution.cpp' from default templates and 'chcecker.py' if 'add_checker' is
# given as command line argument.

STRESS_PATH="/home/madzin/code/cp-utils/stress-testing"
OTHER_PATH="/home/madzin/code/cp-utils/other"

TEST_DIR="stress-test"

if [[ ! -d $TEST_DIR ]]; then
    mkdir $TEST_DIR
fi

if [[ ! -f $TEST_DIR ]]; then
    cp $STRESS_PATH/run.sh $TEST_DIR/run.sh
fi

if [[ ! -f "$TEST_DIR/generator_utils.py" ]]; then
    cp "$STRESS_PATH/generator_utils.py" $TEST_DIR/generator_utils.py
fi

if [[ ! -f "$TEST_DIR/generator.py" ]]; then
    cp "$STRESS_PATH/generator.py" $TEST_DIR/generator.py
fi

if [[ ! -f "$TEST_DIR/checker.py" ]] && [[ $1 == "add_checker" ]]; then
    cp "$STRESS_PATH/checker.py" $TEST_DIR/checker.py
fi

found=false
for f in *.cpp; do
    cp $f $TEST_DIR/program.cpp 
    found=true
    break
done
if [[ ! found ]]; then
    cp "$OTHER_PATH/template.cpp" $TEST_DIR/program.cpp
fi
cp "$OTHER_PATH/template.cpp" $TEST_DIR/solution.cpp

