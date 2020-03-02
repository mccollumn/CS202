/**
 * CS-202 - Assignment 5 - Java Classes
 * Super class containing common methods for all question types.
 * 
 * @author McCollumN
 * @version 1.0
 */

abstract class Question {
	protected String question;
	protected String answer;
	protected boolean correct;
	
	// ------------------------------------------------------------------
	public Question(String question, String answer) {
		this.question = question;
		this.answer = answer;
		correct = false;
	}
	
	// ------------------------------------------------------------------
	/**
	 * Marks the question as having been answered correctly.
	 */
	public void markCorrect() {
		correct = true;
	}
	
	// ------------------------------------------------------------------
	/**
	 * Indicates if the question has already been answered correctly. 
	 * @return boolean	True if correct, false if not.
	 */
	public boolean isCorrect() {
		return correct;
	}
	
	// ------------------------------------------------------------------
	/**
	 * Displays the question text in the console.
	 */
	public abstract void showQuestion();
	
	// ------------------------------------------------------------------
	/**
	 * Displays the answer text in the console.
	 */
	public void showAnswer() {
		System.out.print(answer);
	}
	
	// ------------------------------------------------------------------
	/**
	 * Checks if the answer provided by the user was correct.
	 * @param givenAnswer	The answer entered by the user.
	 * @return boolean	True if the answer was correct, false if not.
	 */
	public abstract boolean checkAnswer(String givenAnswer);
	
	// ------------------------------------------------------------------
	protected String removeWhitespace(String str) {
		return str.replaceAll("\\s", "");
	}
}
