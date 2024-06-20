/*
    Algorithms and data structures - Summer Semester 2024
    Exercise01 - Basic data structures and their operations and input processing
    ---
    © FH Aachen - Facultie 5, Electrical Engineering and Information Technology - Insitute for Mobile Autonomous Systems and Cognitive Robotics
    Prof. Ingrid Scholl - scholl@fh-aachen.de
    ---
    Please refer to the tasks provided in the PDF for this exercise. 
    The PDF for this exercise can be found in the ILIAS course at https://www.ili.fh-aachen.de/.
*/

////// =================================================
////// Task06
////// =================================================

# include <string>
// NOTE: The stack should be used to calculate the postfix
# include <stack>
// NOTE: Stringstream is used to process strings with a streaming operator, similar to cout.
# include <sstream>

// NOTE: This is should be used insinde infix_to_postfix
std::string extract_num(const std::string& input, const int& start_index)
{
    std::string result_nextNumbers = "";

    // TODO: Determine the next sub-string of the input that consists only of numbers and return it
    
    return result_nextNumbers;
}

// NOTE: This should be used directly after input for verification before further processing
bool test_infix_brackets(std::string input)
{
    bool result_isInfix = false;
    
    // TODO: Verify that the users initial text input format uses the correct infix notation.

    return result_isInfix;
}

std::string infix_to_postfix(const std::string& input)
{
    // Should be used as a container for the mathematical operators.
    std::stack<char> operators;
    // Should be used to build the postfix expression during iterative processing.
    std::stringstream ss_postfix;
    
    // TODO: Convert the user's initial input from infix notation to postfix notation and return it.

    // Return postfix string from stringstream
    return ss_postfix.str();
}

// NOTE: The input is the result of infix_to_postfix
double calculate_postfix(const std::string& input)
{
    std::stack<double> results_calculations;

    // TODO: Process the input in postfix notation using a stack.

    return results_calculations.top();
}

int main()
{
    

    // TODO: Get user input in infix notation
    std::string input_infix = "";

    // Verify format of the user input
    bool precondition_format = test_infix_brackets(input_infix);

    if (!precondition_format) {

        return 1;
    
    }

    // Get postfix notation
    std::string input_postfix = infix_to_postfix(input_infix);

    // Caclucate result of mathematical expression
    double result = calculate_postfix(input_postfix);

    

    // TODO: Print the infix expression, the postfix expression, and the final result to the console.

    return 0;
}
