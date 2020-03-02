/**
 * CS-202 - Assignment 5 - Java Classes
 * Multiple Choice question object used by Quiz.
 * Displays MC question and checks the user's answer.
 * 
 * @author Nick McCollum
 * @version 1.0
 *
 */

public class QuestionMC extends Question {

	public QuestionMC(String question, String answer, String choices) {
		super(question, answer);
		this.question = question;
		this.answer = answer;
		this.choices = choices;
		correct = false;
	}

	// ------------------------------------------------------------------
	/**
	 * Displays the MC question text in the console.
	 */
	public void showQuestion() {
		String[] choiceArray = parseChoices(choices);
		System.out.print(question + "?");
		
		char choiceLetter = 'a';
		for (String choice : choiceArray)  {
			System.out.print("\n\t" + choiceLetter + ") " + choice);
			choiceLetter++;
		}
			
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
		
		if (givenAnswer.charAt(0) != actualAnswer.charAt(0)) {
			return false;
		}
		
		markCorrect();
		return true;
	}
	
	protected String choices;
	
	protected String[] parseChoices(String choices) {
		return choices.split(":");
	}
}
