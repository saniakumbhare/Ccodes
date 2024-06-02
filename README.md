NetIDS:
Sania Kumbhare ssk208
Srishti Thakur st1090

How to compile:
gcc mysh.c myshlib.c -o mysh

How to run:
./mysh

1. init_shell():

Test Case: Verify initialization of the shell interface.
Input: N/A (Function called at program start)
Expected Output: Screen cleared, welcome message displayed, and shell prompt (mysh:<current_directory>$) printed.

2. execute_external_command():

Test Case: Execute a basic command (ls) and verify the output.
Input: ls
Expected Output: List of files and directories in the current directory.
Test Case: Execute a command with arguments and options (ls -l) and verify the output.
Input: ls -l
Expected Output: Detailed list of files and directories in the current directory.
Test Case: Execute an invalid command (xyz) and verify error handling.
Input: xyz
Expected Output: Error message indicating command not found.

3. parse_command():

Test Case: Parse a basic command (ls) and verify tokenization.
Input: "ls"
Expected Output: Array containing ls as the first element and NULL as the next element.
Test Case: Parse a command with arguments and options (ls -l) and verify tokenization.
Input: "ls -l"
Expected Output: Array containing ls as the first element, -l as the second element, and NULL as the next element.
Test Case: Parse an invalid command and verify error handling.
Input: " "
Expected Output: NULL returned with appropriate error message.

4. run_batch_script():

Test Case: Execute commands from a batch file containing multiple commands and verify the output.
Input: Batch file containing ls, pwd, echo "Hello".
Expected Output: List of files and directories, current directory path, and Hello printed.
Test Case: Execute commands from a batch file with an invalid command and verify error handling.
Input: Batch file containing xyz.
Expected Output: Error message indicating command not found.

5. get_input():

Test Case: Test input within buffer size limit.
Input: Enter a command within the buffer size limit (e.g., ls -l).
Expected Output: Input command should be read correctly without any errors.
Test Case: Test input exceeding buffer size limit.
Input: Enter a long command exceeding the buffer size limit.
Expected Output: Input command should be read correctly after reallocating memory.
Test Case: Test empty input.
Input: Press Enter without entering any command.
Expected Output: Empty string returned.

