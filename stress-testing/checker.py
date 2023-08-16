import sys


def get_content(file_to_read):
    with open(file_to_read, "r") as f:
        return f.read().split("\n")

def main(input_file, solution_output, your_output):
    inpt = get_content(input_file)
    solution = get_content(solution_output)
    your = get_content(your_output)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])

