/* Grace Provost
   gprovost@pdx.com
   CS162 Program 1
   10/14/19
   
   Purpose: Algorithm to find student cumulative and current term GPAs by entering grades and credit hours. Program will allow students to repeat as often as they like until they are done.
   
   Code Algorithm:
	1. Initialize three maps of grades based on +, -, and normal letter grade assigned to grade points
		This will be done using a function that will initialize at start of program in main
		They will be called plusGradeToGradePoints, minusGradeToGradePoints, and gradeToGradePoints
		Three are needed because only one character can be used to denote a place on a map, and we cannot use strings like “B+”
	2. Initialize other variables: 
		float cumulativeGPA
		int cumulativeCreditHours
		float cumulativeGradePoints
		float termGPA
		int termNumberOfClasses
		float termGradePoints
		int termCreditHours
		char grade
		int creditHours
		float gradePoints
		float newCumulativeGPA
		bool restartProgram
		char nextInput
		int i
	3. Create helper functions to tell if a stream is invalid for different primitive datatypes used in the program: float getGPA(), int getPositiveInteger(), char getGrade(), getRestartResponse(), clearBufferStream()
		These will re-prompt the user for valid data
	4. Explain the program to the user
	5. Prompt the user to enter their cumulative GPA
		Validate with getGPA()
		Store in cumulativeGPA
	6. Prompt user to enter cumulative credit hours
		Validate with getPositiveInteger(1000)
		Store in cumulativeCreditHours
	7. Calculate cumulative grade points
		cumulativeGradePoints = cumulativeGPA * cumulativeCreditHours
	8. Cout cumulativeGradePoints, cumulativeGPA, cumulativeCreditHours
		(Initialize the cout stream to showpoint() and setprecision() for each kind of variable when outputting)
	9. Wrap steps 10-19 in a do-while function so they can be repeated if the user wants to go again
	10. Prompt user to enter the number of classes they will be taking for the term
		Store in termNumberOfClasses
	11. Create a for loop that will go from 1 to < termNumberOfClasses + 1
		steps 12-15 are wrapped in this loop
	12. Prompt user for letter grade using getGrade()
		use cin.peek() to see if a user intered a '+' or '-'
		Convert that grade to grade points using the maps
		store in gradePoints
	13. Prompt user for credit hours of that class
		Store in creditHours
		Add those to termCreditHours
	14. Calculate quality points with gradePoints * creditHours
		Add those grade points to termGradePoints
	15. Cout the grade for this class
		(Initialize the cout stream to showpoint() and setprecision() for each kind of variable when outputting)
	16. cout the total termCreditHours and termGradePoints after the loop
		(Initialize the cout stream to showpoint() and setprecision() for each kind of variable when outputting)
	17. Calculate newCumulativeGPA	
		newCumulativeGPA = (termGradePoints + cumulativeGradePoints) / (termCreditHours + cumulativeCreditHours)
	18. Calculate termGPA
		termGPA = termGradePoints / termCreditHours
	19.Cout termGPA and newCumulativeGPA for user
		(Initialize the cout stream to showpoint() and setprecision() for each kind of variable when outputting)
	20. Prompt user if they would like to enter grades in again
		‘Y’ results in continuing the do-while loop that step 10-19 are in
			Reset termGradePoints, termCreditHours, termGPA, newCumulativeGPA, creditHours, gradePoints, nextInput, grad, termNumberOfClassese
		'N' will quit the program
*/

#include <iostream>
#include <cctype>
#include <iomanip>
#include <map>

using namespace std;
// HELPER FUNCTIONS

// this helper builds a map that equates letter grades
// to their grade points if there is the absence of a '+' or '-'
// (whole grades only, no 'A-', etc.
map<char,float> createGradesToGradePointsMap(void)
{	
	// instansiates the map that will hold grade points by 
	// letter grade
	map<char,float> gradesToGradePointsMap;

	gradesToGradePointsMap['A'] = 4.00;
	gradesToGradePointsMap['B'] = 3.00;
	gradesToGradePointsMap['C'] = 2.00;
	gradesToGradePointsMap['D'] = 1.00;
	gradesToGradePointsMap['F'] = 0.00;
	
	return gradesToGradePointsMap;
}



// this helper builds a map that equates letter grades
// to their grade points if there is a '+' ('B+', 'C+',  etc.)
// since there is no 'A+' or 'F+', will assume the
// whole grade ('A', 'F')  point value for these instances
map<char,float> createPlusGradesToGradePointsMap(void)
{	
	// instansiates the map that will hold grade points by 
	// letter grade
	map<char,float> plusGradesToGradePointsMap;

	plusGradesToGradePointsMap['A'] = 4.00;
	plusGradesToGradePointsMap['B'] = 3.33;
	plusGradesToGradePointsMap['C'] = 2.33;
	plusGradesToGradePointsMap['D'] = 1.33;
	plusGradesToGradePointsMap['F'] = 0.00;
	
	return plusGradesToGradePointsMap;
}


// this helper builds a map that equates letter grades
// to their grade points if there is a '-' ('B-', 'C-',  etc.)
// since there is no 'F-', will assume the
// whole grade ('F')  point value for this instance
map<char,float> createMinusGradesToGradePointsMap(void)
{	
	// instansiates the map that will hold grade points by 
	// letter grade
	map<char,float> minusGradesToGradePointsMap;

	minusGradesToGradePointsMap['A'] = 3.67;
	minusGradesToGradePointsMap['B'] = 2.67;
	minusGradesToGradePointsMap['C'] = 1.67;
	minusGradesToGradePointsMap['D'] = 0.67;
	minusGradesToGradePointsMap['F'] = 0.00;
	
	return minusGradesToGradePointsMap;
}


// a helper function for cleaning out the buffer
// since we will be doing it multiple times
void clearBufferStream(void)
{
	// clear out the errorstate
	// just in case it exists
	cin.clear();
	// ignore the rest of what is in the stream
	// until carriage return is hit '\n' 
	// or the end of the stream 'numeric_limits<streamsize>::max()'
	// so no further errors are hit
	// and we can flush out the carriage return
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return;
}



// this helper provides sanitization of an integer 
// that cannot be negative, then returns the 
// value obtained
// we pass in the max possible integer
int getPositiveInteger(int max)
{	
	// to hold the number of classes
        int number = 0;

        // while the input stream is in an error state
        while(!(cin >> number)
		// students likely wont be entering more than the max
		// max + 1 so that the max is included in the possible
		// range
		|| number > max
		// classes cant be negative
		|| number < 0
		// don't allow negative zero
        	|| number == -0
		// if the next thing in the stream is a decimal
		// user likely intended to enter a decimal number
		|| cin.peek() == '.')
        {
		clearBufferStream();
                cout << "Invalid number. Must be less than " << (max + 1) << ", integer, and positive. Try again: ";
        }
	// clear the stream prior to finishing up
	clearBufferStream();

        return number;
}



// this helper provides sanitization of the GPA
// a student may enter, then returns the 
// value obtained
float getGPA(void)
{
	// to hold the GPA
        float GPA = 0.00;

        // while the input stream is in an error state
        while(!(cin >> GPA)
        // over valid gpa
        || GPA > 4.00
        // a negative number
        || GPA < 0.00
        // don't allow negative zero
        || GPA == -0.00)
        {
                clearBufferStream();
		cout << "Invalid GPA. GPAs are 4.00 through 0.00.  Try again: ";
        }
	// clear the stream prior to finishing up
	clearBufferStream();

        return GPA;
}


// this helper provides sanitization of the grade
// a student may enter, then returns the 
// value obtained
char getGrade(void)
{
	// to hold the grade
        char grade;

        // while the input stream is in an error state
	// make everything uppercase for case insensitivity 
        while(!(cin >> grade)
                // if input is less than 'A'
		// though this does include '+' or '-'
		// we will cin.peek() for the '+' or '-' 
		// outside of this sanitization function
                || toupper(grade) < 'A'
                // if input is greater than 'F'
                || toupper(grade) > 'F'
                // or if it is 'E'
                || toupper(grade) == 'E'
                // don't allow anything other than '+' or '-' after
		// except for newlines and spaces
		|| (cin.peek() != '-'
		&& cin.peek() != '+'
		&& cin.peek() != '\n'
		&& cin.peek() != ' '))
        {
        	// have a specific error message for P/NP classes       
		if (toupper(grade) == 'P'
			|| (toupper(grade) == 'N' 
			&& toupper(cin.peek()) == 'P'))cout << "Pass / No Pass classes have no effect on GPA and are not counted. Try again: ";
		else cout << "Invalid grade. Grades are A through F.  Try again: ";
	       	clearBufferStream();
        }
	// notice we do not clear the buffer stream here yet so we can peek for the next
	// input in case it is + or -
	
        return toupper(grade);
}



// this helper provides sanitization of the yes / no
// response a student may enter, then returns the 
// value obtained
bool getRestartResponse(void)
{
	// to hold the answer
        char answer;

        // while the input stream is in an error state
	// make everything uppercase for case insensitivity 
        while(!(cin >> answer)
                // if input is anything other than y/n
		|| (toupper(answer) != 'Y'
		&& toupper(answer) != 'N'))
        {
                clearBufferStream();
		cout << "Invalid answer. Anser 'y' or 'n'.  Try again: ";
        }
	// clean out the stream
	clearBufferStream();

	// retun a boolean as we are expecting that
        return toupper(answer) == 'Y';
}



int main(void) 
{
	// VARIABLES
	 
	// will hold the cumulative GPA a student enters
	float cumulativeGPA = 0.00;
	// will hold the cumulative credit hours a student enters
	int cumulativeCreditHours = 0;
	// will hold the cumulative grade points calculated from the 
	// cumulativeGPA and cumulativeCreditHours entered by student
	float cumulativeGradePoints = 0.00;
	// will hold the calculated term GPA
	float termGPA = 0.00;
	// will hold the number of classes a student
	// wants to enter
	int termNumberOfClasses = 0;
	// will hold total term grade points
	// each time a letter grade is converted to 
	// grade points, it will add to this total
	float termGradePoints = 0.0;
	// will hold total term credit hours
	// each time the student enters credit hours
	// for a class, it will be added to this total 
	int termCreditHours = 0;
	// will hold the temporary grade 
	// for user input
	// before it is converted to grade points
	// and added to termGradePoints
	char grade = '\0';
	// will hold the temporary grade points
	// for user input
	// before it is converted to quality points
	// and added to termGradePoints
	float gradePoints = 0.00;
	// will hold the temporary credit hours
	// for user input
	// before it is converted to quality points
	// and added to termCreditHours
	int creditHours = 0;
	// will hold the newly calculated cumulative GPA
	// with the clases entered for the term
	float newCumulativeGPA = 0.00;
	// a boolean to keep track of if the user would
	// like to restart the program
	// with new classes
	bool restartProgram = true;
	// this is to hold the next possible input the 
	// stream might have
	char nextInput = '\0';
	// map to hold plus grade to gradepoints conversion
	map<char, float> plusGradeToGradePoints = createPlusGradesToGradePointsMap();
	// map to hold minus grade to gradepoints conversion
	map<char, float> minusGradeToGradePoints = createMinusGradesToGradePointsMap();
	// map to hold grade to gradepoints conversion
	map<char, float> gradeToGradePoints = createGradesToGradePointsMap();
	// for the for-loop because we have to do it up here
	int i = 0;

	// CODE <3
	
	// obtain current cumulative stats
	
	cout << "This is a program for calculating your term and cumulative GPAs. You will need:" << endl;
      	cout << "cumulative GPA"<< endl;
       	cout << "cumulative credit hours" << endl;
	cout << "number of classes" << endl;
	cout << "term letter grades" << endl;
       	cout << "term credit hours" << endl;
	cout << "You may exit the program at any time by pressing the \"control\" + \"c\" keys." << endl;
	cout << "Let's being by entering your current cumulative GPA: ";
	cumulativeGPA = getGPA();
	cout << showpoint << setprecision(3) << "Your cumulative GPA: " << cumulativeGPA << endl;
	cout << "Enter your current cumulative credit hours: ";
	// obtain credit hours with 1000 as the possible max
	cumulativeCreditHours = getPositiveInteger(1000);
	cout << noshowpoint << "Your cumulative credit hours: " << cumulativeCreditHours << endl;
	
	// calculate cumulative grade points	
	cumulativeGradePoints = cumulativeGPA * cumulativeCreditHours;
	cout << showpoint << setprecision(4) << "Your cumulative grade points: " << cumulativeGradePoints << endl;
	
	// obtain information about current term
	
	// place in a do-while loop so we
	// can return to this point if they want to 
	// attempt recalculation of term classes 	
	do 
	{
		cout << "Enter the number of classes you would like to enter grades for: ";
		// obtain number of classes with 10 as the possible max
		termNumberOfClasses = getPositiveInteger(10);
		cout << "For the next part you will enter grades and credit hours one at a time for each class." << endl;
	       cout << "A+ , F+, and F- are not real grades and will be counted as A and F respectively. P/NP classes have no effect on GPA and will not be counted." << endl;

		// a for loop to have the student enter in each letter grade and credit hours
		// we start at 1 so we can print out each iteration which class this is for
		// we add 1 to the total so we can be inclusive of the desired total classes
		for (i = 1; i < (termNumberOfClasses + 1); i++)
		{
			cout << "Enter a letter grade for class " << i << ": "; 
			grade = getGrade();
			nextInput = cin.peek();
			// we need to manually clean up the stream here
			// instead of in getGrade()
			// since we wanted to peek for '+' and '-'
			clearBufferStream();
			cout << "Your grade: " << grade;
			if (nextInput == '+' || nextInput == '-')
			{
				// obtain the grade points from the correct map
				// depending on the sign	
		       		gradePoints = nextInput == '+'
					? plusGradeToGradePoints[grade]
					: minusGradeToGradePoints[grade];
				 // print out the '+' or '-' to go with the grade
				 // as long as it is not A+ or F- or F+
				if (!(grade == 'A' && nextInput == '+')
					&& !(grade == 'F' 
						&& (nextInput == '+' 
						|| nextInput == '-'))) cout << nextInput;
			}
			// if there is no sign, obtain a normal grade
		       	else gradePoints = gradeToGradePoints[grade];
			// end line here completes the cout of the grade above
			cout << endl;
			cout << "Enter the credit hours for this class: ";
			// classes are typically 5 credit hours at most
			creditHours = getPositiveInteger(5);
			// add to term values
			termGradePoints += creditHours * gradePoints;
			termCreditHours += creditHours;
		}
		// display the totals
		// in case they are curious
		cout << noshowpoint <<  setprecision(3) << "Your total term credit hours with this class are: " << termCreditHours << endl;
		cout << showpoint << setprecision(4) << "Your total term grade points with this class are: " << termGradePoints << endl;
		
		// calculate newCumulativeGPA
		newCumulativeGPA = (termGradePoints + cumulativeGradePoints) / (termCreditHours + cumulativeCreditHours);

		// caluclate termGPA
		termGPA = termGradePoints / termCreditHours;
		
		// initialize for GPA presentation
		cout << showpoint << setprecision(4);
		cout << "Your term GPA with these " << termNumberOfClasses << " classes: " << termGPA << endl;
		cout << "Your cumulative GPA with the additional term classes: " << newCumulativeGPA << endl;
		cout << "Would you like to re-calculate your possible GPAs with classes again (y/n)?" << endl;
		
		// restart the program
		
		// obtain restart response
		restartProgram = getRestartResponse(); 		
		if (restartProgram) 
		{
			// reset all the values
			cout << "Restarting program..." << endl;		
			termGPA = 0.00;
			termGradePoints = 0.00;
			termCreditHours = 0;
			newCumulativeGPA = 0.00;
			creditHours = 0;
			gradePoints = 0.00;
			nextInput = '\0';
			termNumberOfClasses = 0;
			grade = '\0';
		}
	} while (restartProgram);
		
	// if we are out of the do-while loop
	// they quit
	cout << "Goodbye!" << endl;	
}
