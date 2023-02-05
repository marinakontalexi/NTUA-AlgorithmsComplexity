from subprocess import PIPE, Popen

for n in range(1,34):
    inputFile = f'teleports_test/input{n}.txt'
    outputFile = f'teleports_test/output{n}.txt'
    f = open(outputFile)
    output = f.read()
    command = "a.exe " + inputFile
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if output.split() == producedOutput.decode("utf-8").split():
        print(f'+++ Testcase {n} passed!')
    else:
        print(f'--- Testcase {n} failed!')
        print(f'Expected Output:\n{output}')
        print(f'Produced Output:\n{producedOutput.decode("utf-8")}')
