# CS162_program1

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
