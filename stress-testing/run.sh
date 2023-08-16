# For running the script, it's needed to have files 'program.cpp' and 'generator.py'.
# In that case program.cpp is run on N generated test cases.
# If 'solution.cpp' is present, program.cpp outputs are tested against solution.cpp
# outputs on each generated test using the diff command.
# If 'checker.py' is present, instead of diff, checker.py is used for determining
# output match.

# Example usage: 'run.sh 10' run the script on 10 randomly generated tests.
echo "----- Testing started -----"

SOL=./solution.cpp
CHECKER=./checker.py

g++ program.cpp -o exe_your
if [[ -f "$SOL" ]]; then
    g++ solution.cpp -o exe_sol
fi

n=1
if [[ $1 != "" ]]; then
    n=$1
fi

for (( i=1; i<=n; ++i )) do
    python3 generator.py > input.txt

    if [[ ! -f $SOL ]]; then
        echo "Test $i:"
        ./exe_your < input.txt
    else
        ./exe_your < input.txt > out_your.txt
        ./exe_sol < input.txt > out_sol.txt
        if [[ -f $CHECKER ]]; then
            MESSAGE=$(python3 $CHECKER input.txt out_sol.txt out_your.txt)
        else
            MESSAGE=$(diff out_sol.txt out_your.txt)
        fi
        if [[ $MESSAGE != "" ]]; then
            echo
            echo $MESSAGE
            echo "WA on test $i"
            echo
            break
        else
            echo "AC on test $i"
        fi
    fi
done

rm exe_your
if [[ -f $SOL ]]; then
    rm exe_sol
fi

echo "----- Testing done --------"
