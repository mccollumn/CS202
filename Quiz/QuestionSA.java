/**
 * CS-202 - Assignment 5 - Java Classes
 * Short Answer question object used by Quiz.
 * Displays SA question and checks the user's answer.
 * 
 * @author Nick McCollum
 * @version 1.0
 *
 */

public class QuestionSA extends Question {

	public QuestionSA(String question, String answer) {
		super(question, answer);
		this.question = question;
		this.answer = answer;
		correct = false;
	}

	// ------------------------------------------------------------------
	/**
	 * Displays the MC question text in the console.
	 */
	public void showQuestion() {
		System.out.print(question + "?");
	}
	
	// ------------------------------------------------------------------
	/**
	 * Checks if the answer provided by the user was correct.
	 * @param givenAnswer	The answer entered by the user.
	 * @return boolean	True if the answer was correct, false if not.
	 */
	public boolean checkAnswer(String givenAnswer) {
		givenAnswer = removeWhitespace(givenAnswer.toLowerCase());
		String actualAnswer = removeWhitespace(answer.toLowerCase());
		
		if (!givenAnswer.contentEquals(actualAnswer)) {
			return false;
		}
		
		markCorrect();
		return true;
	}
}
