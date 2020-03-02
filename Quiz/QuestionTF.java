/**
 * CS-202 - Assignment 5 - Java Classes
 * True / False question object used by Quiz.
 * Displays TF question and checks the user's answer.
 * 
 * @author Nick McCollum
 * @version 1.0
 *
 */

public class QuestionTF extends Question{

	public QuestionTF(String question, String answer) {
		super(question, answer);
		this.question = question;
		this.answer = answer;
		correct = false;
	}

	// ------------------------------------------------------------------
	/**
	 * Displays the TF question text in the console.
	 */
	public void showQuestion() {
		System.out.print(question + ". (True or False)");
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
		
		if (givenAnswer.length() == 1 && givenAnswer.charAt(0) == actualAnswer.charAt(0)) {
			markCorrect();
			return true;
		}
		if (givenAnswer.contentEquals(actualAnswer)) {
			markCorrect();
			return true;
		}
		
		return false;
	}
}
