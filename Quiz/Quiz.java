/**
 * CS-202 - Assignment 5 - Java Classes
 * This class is responsible for loading questions from file and
 * delivering them as a quiz to the user.
 * 
 * @author Nick McCollum
 * @version 1.0
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;

public class Quiz {
	// Map of question types and the number of fields they have
	private final Map<String, Integer> QUESTION_TYPES = Map.of(
			"SA", 4,
			"TF", 4,
			"MC", 5,
			"MA", 5);
	private final int TYPE_FIELD = 1;
	private final int LEVEL_FIELD = 2;
	private final int QUESTION_FIELD = 3;
	private final int CHOICES_FIELD = 4;
	private final int MIN_LEVEL = 1;
	private final int MAX_LEVEL = 9;

	private ArrayList<Question> questions;
	private String filename;
	private boolean filenameIsValid;
	
	// -------------------------------------------------------------------
	public Quiz() {
		filename = "";
		filenameIsValid = false;
		questions = new ArrayList<Question>();
	}
	
	// -------------------------------------------------------------------
	public Quiz(String dataFile) {
		filename = dataFile;
		filenameIsValid = false;
		questions = new ArrayList<Question>();
		loadQuestions(filename);
	}
	
	// -------------------------------------------------------------------
	/**
	 * Loads questions from the provided file.
	 * @param dataFile	Name of the questions file.
	 * @return boolean	True if questions were loaded successfully,
	 * 					False is not.	
	 */
	public boolean loadQuestions(String dataFile) {
		Scanner file = readFile(dataFile);
		filenameIsValid = true;
		int lineNumber = 1;
		
		if (questions != null) {
			questions.clear();
		}
		
		if (filenameIsValid) {
			while (file.hasNextLine()) {
				String line = file.nextLine();
				if (!isComment(line) && !line.isBlank() && validateLine(line, lineNumber)) {
					addQuestion(line);
				}
				lineNumber++;
			}
			file.close();
		}
		
		return true;
	}
	

	// -------------------------------------------------------------------
	/**
	 * Delivers a quiz to the user using the currently loaded questions.
	 * @param input	The Scanner to use for user input
	 */
	public void deliverQuiz(Scanner input) {
		deliverQuiz(false, input);
	}
	
	// -------------------------------------------------------------------
	/**
	 * Delivers a quiz to the user using the currently loaded questions.
	 * Accepts an argument indicating whether all questions should be delivered,
	 * or only questions that were answered incorrectly.
	 * @param showIncorrectOnly	True to display incorrect answers only,
	 * 							false to display all questions.
	 * @param input	The Scanner to use for user input
	 */
	public void deliverQuiz(boolean showIncorrectOnly, Scanner input) {
		if (!questionsLoaded()) {
			return;
		}
		
		if (!showIncorrectOnly) {
			System.out.println("\nHope your brain's warmed up, it's Quiz Time!!!");
			System.out.println("After each answer is displayed, press Enter to see the next question.\n");
		}
		
		for (Question question : questions) {
			if (!showIncorrectOnly || (showIncorrectOnly && !question.isCorrect())) {
				question.showQuestion();
				System.out.println();				
				String givenAnswer = input.nextLine();
				
				if (question.checkAnswer(givenAnswer)) {
					System.out.println("\nCorrect!  Great Job!\n");
					question.markCorrect();
				}
				else {
					System.out.print("\nSorry, the answer is ");
					question.showAnswer();
					System.out.println(".\n");
				}
			}
		}
		
		displayGrade(totalQuestions(), getCorrectCount());
	}
	
	// -------------------------------------------------------------------
	/**
	 * Returns the number of answers currently marked correct.
	 * @return int	Number of correct answers.
	 */
	public int getCorrectCount() {
		int numCorrect = 0;
		for (Question question : questions) {
			if (question.isCorrect()) {
				numCorrect++;
			}
		}
		return numCorrect;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Returns the number of answers currently marked incorrect.
	 * @return int	Number of incorrect answers.
	 */
	public int getIncorrectCount() {
		return questions.size() - getCorrectCount();
	}
	
	// -------------------------------------------------------------------
	/**
	 * Provides the number of questions currently loaded.
	 * @return int	The number of questions.
	 */
	private int totalQuestions() {
		return questions.size();
	}
	
	
	// -------------------------------------------------------------------
	/**
	 * Displays the results of the quiz.
	 * @param numQuestions	Total number of quiz questions.
	 * @param numCorrect	Number of questions answered correctly.
	 */
	private void displayGrade(int numQuestions, int numCorrect) {
		float percentage = ((float) numCorrect / (float) numQuestions) * 100;
		
		System.out.print("You got " + numCorrect + " of " + numQuestions + " correct: ");
		System.out.print(Math.round(percentage) + "%.");
		
		if (percentage < 70) {
			System.out.println("\tBetter study More!");
		}
		else {
			System.out.println("\tGood job!");
		}
		System.out.println();
	}
	
	// -------------------------------------------------------------------
	/**
	 * Opens specified file.
	 * @param filename	Name of the file to open.
	 * @return Scanner	File Scanner object.
	 */
	private Scanner readFile(String filename) {
		File file = new File(filename);
		Scanner fsc = null;

		try {
			fsc = new Scanner(file);
		}
		catch (FileNotFoundException e) {
			System.err.println("Error: " + file.getAbsolutePath() + " not found or cannot be opened.");
			System.exit(-1);
		}
		
		return fsc;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Adds a question to the quiz
	 * @param line	The line from the questions file to add.
	 */
	private void addQuestion(String line) {
		String type = getType(line);
		String question = getQuestion(line);
		String answer = getAnswer(line);
		
		if (type.equalsIgnoreCase("SA")) {
			questions.add(new QuestionSA(question, answer));
		}
		else if (type.equalsIgnoreCase("TF")) {
			questions.add(new QuestionTF(question, answer));
		}
		else if (type.equalsIgnoreCase("MC")) {
			questions.add(new QuestionMC(question, answer, getChoices(line)));
		}
	}
	
	// -------------------------------------------------------------------
	/**
	 * Validates a line from the question file
	 * 
	 * @param line	The line to validate
	 * @param lineNum	The line number in the file
	 * @return boolean	True if the line is valid, false if not
	 */
	private boolean validateLine(String line, int lineNum) {
		if (isComment(line)) {
			return true;
		}
		if (line.isBlank()) {
			return true;
		}
		if (!isValidLine(line, lineNum)) {
			return false;
		}
		if (getLevel(line, lineNum) == null) {
			return false;
		}
		if (!validateType(getType(line), line, lineNum)) {
			return false;
		}
	
		return true;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Performs validation for specific question types
	 * 
	 * @param type	Question type
	 * @param line	The line to validate
	 * @param lineNum	The line number from the file
	 * @return boolean	True if question type if valid, false if not
	 */
	private boolean validateType(String type, String line, int lineNum) {
		boolean isValid = true;
		
		if (!QUESTION_TYPES.containsKey(type)) {
			printError(line, lineNum, "Invalid question type");
			isValid = false;
		}
		else if (numFields(line) != QUESTION_TYPES.get(type)) {
			printError(line, lineNum, "Invalid number of fields (must have " + QUESTION_TYPES.get(type) + ")");
			isValid = false;
		}
		else if (type.equalsIgnoreCase("TF")) {
			isValid = validateTF(line, lineNum);
		}
		else if (type.equalsIgnoreCase("MC")) {
			isValid = validateMC(line, lineNum);
		}
		else if (type.equalsIgnoreCase("MA")) {
			isValid = validateMA(line, lineNum);
		}
		
		return isValid;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Validates T/F questions
	 * 
	 * @param line	Line to validate
	 * @param lineNum	Line number from the file
	 * @return boolean	True if valid T/F question, false if not
	 */
	private boolean validateTF(String line, int lineNum) {
		String answer = getAnswer(line).toLowerCase();
		if (answer.contentEquals("t") || answer.contentEquals("f") || answer.contentEquals("true") || answer.contentEquals("false")) {
			return true;
		}
		else {
			printError(line, lineNum, "Invalid true/false answer (valid options are T/F or True/False)");
			return false;
		}
	}
	
	// -------------------------------------------------------------------
	/**
	 * Validates multiple choice questions
	 * 
	 * @param line	Line to validate
	 * @param lineNum	Line number from the file
	 * @return boolean	True if valid MC question, false if not
	 */
	private boolean validateMC(String line, int lineNum) {
		boolean isValid = true;
		String answer = getAnswer(line).toUpperCase();
		String choices = getChoices(line);
		
		if (answer.length() != 1) {
			printError(line, lineNum, "Invalid multiple choice answer");
			isValid = false;
		}
		else if (!isValidChoice(answer, numChoices(choices))) {
			printError(line, lineNum, "Multiple choice answer is not one of the choices");
			isValid = false;
		}
		if (numChoices(choices) <= 1) {
			printError(line, lineNum, "Multiple choice questions need at least two answers");
			isValid = false;
		}
		
		return isValid;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Validates multiple answer questions
	 * 
	 * @param line	Line to validate
	 * @param lineNum	Line number from the file
	 * @return boolean	True if question is valid, false if not
	 */
	private boolean validateMA(String line, int lineNum) {
		boolean isValid = true;
		String answer = getAnswer(line).toUpperCase();
		String choices = getChoices(line);
		
		if (answer.length() > numChoices(choices)) {
			printError(line, lineNum, "Invalid answer");
			isValid = false;
		}
		else {
			String[] answers = answer.split("");
			for (String a : answers) {
				if (!isValidChoice(a, numChoices(choices))) {
					printError(line, lineNum, "Answer " + a + " is not one of the choices");
					isValid = false;
				}
			}
		}
		if (numChoices(choices) <= 1) {
			printError(line, lineNum, "Multiple answer questions need at least two answers");
			isValid = false;
		}
		
		return isValid;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Outputs message to std error if no questions are loaded.
	 * @return boolean	True if questions are loaded, false if not.
	 */
	private boolean questionsLoaded() {
		if (questions == null || questions.isEmpty()) {
			System.err.println("ERROR: Cannot deliver quiz.");
			System.err.println("No questions have been loaded.");
			return false;
		}
		return true;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Check if the line is a comment
	 * 
	 * @param line	The line to check
	 * @return boolean	True if line is a comment, false if not
	 */
	private boolean isComment(String line) {
		if (line.stripLeading().startsWith("#") || line.stripLeading().startsWith("//")) {
			return true;
		}
		return false;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Determines if the line is a properly delimited question.
	 * Used to check for bad lines before validating specific conditions.
	 * 
	 * @param line	The line to validate.
	 * @param lineNum	The line number in the file.
	 * @return boolean	True if line if valid, false if not
	 */
	private boolean isValidLine(String line, int lineNum) {
		if (numFields(line) <= 1) {
			printError(line, lineNum, "Invalid line");
			return false;
		}
		return true;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Checks if the answer correlates with the choices.
	 * For MA and MC question types.
	 * 
	 * @param answer	Answer
	 * @param numChoices	Number of choices
	 * @return boolean	True if choice is valid, false if not.
	 */
	private boolean isValidChoice(String answer, int numChoices) {
		return (answer.charAt(0) - 'A') < numChoices;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Check if the question type is valid
	 * 
	 * @param type	Type of question
	 * @return boolean	True if question type is valid, false if not
	 */
	private boolean isValidType(String type) {
			for (String validType: QUESTION_TYPES.keySet()) {
				if (type == validType);
				return true;
			}
		return false;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Checks if the question level is valid
	 * 
	 * @param levelStr	The level value as a string
	 * @return boolean	True if the level is valid, false if not
	 */
	private boolean isValidLevel(String levelStr) {
		boolean isValid = true;
		try {
			int level = Integer.parseInt(levelStr);
			if (level < MIN_LEVEL || level > MAX_LEVEL) {
				isValid = false;
			}
		}
		catch (NumberFormatException e) {
			isValid = false;
		}

		return isValid;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Gets the question type
	 * 
	 * @param line	The question line
	 * @return String	The question type
	 */
	private String getType(String line) {
		String[] tokens = parseLine(line);
		String type = tokens.length >= TYPE_FIELD ? tokens[TYPE_FIELD - 1].strip().toUpperCase() : null;
		
		if (isValidType(type)) {
			return type;
		}
		return null;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Gets the question level
	 * 
	 * @param line	Question line
	 * @param lineNum	Line number from the file
	 * @return String	The question level
	 */
	private String getLevel(String line, int lineNum) {
		String[] tokens = parseLine(line);
		String level = tokens.length >= LEVEL_FIELD ? tokens[LEVEL_FIELD - 1].strip() : null;
		
		if (isValidLevel(level)) {
			return level;
		}
		else {
			printError(line, lineNum, "Invalid level");
			return null;
		}
	}
	
	// -------------------------------------------------------------------
	/**
	 * Gets the question text
	 * @param line	Question line from file.
	 * @return String	The question text.
	 */
	private String getQuestion(String line) {
		String[] tokens = parseLine(line);
		String question = tokens.length >= QUESTION_FIELD ? tokens[QUESTION_FIELD - 1].strip() : null;
		return question;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Gets the answer text.
	 * @param line	Question line from file.
	 * @return String	The answer text.
	 */
	private String getAnswer(String line) {
		String[] tokens = parseLine(line);
		return tokens[tokens.length - 1].strip();
	}
	
	// -------------------------------------------------------------------
	/**
	 * Gets the answer choices
	 * @param line	Question line form file.
	 * @return String	The choice text.
	 */
	private String getChoices(String line) {
		String[] tokens = parseLine(line);
		String choices = tokens.length >= CHOICES_FIELD ? tokens[CHOICES_FIELD - 1].strip() : null;
		if (numChoices(choices) <= 1) {
			return "";
		}
		return choices;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Gets the number of choices for the question
	 * 
	 * @param choices
	 * 		String of : delimited choices
	 * @return	Number of choices
	 */
	private int numChoices(String choices) {
		long numChoices = choices.chars().filter(ch -> ch == ':').count() + 1;
		return (int)numChoices;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Provides the number of fields for the question
	 * 
	 * @param line
	 * 		The question
	 * @return	Number of fields
	 */
	private int numFields(String line) {
		String[] tokens = parseLine(line);
		return tokens.length;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Splits a line on the | delimiter
	 * 
	 * @param line	Line to parse
	 * @return String	Array of strings
	 */
	private String[] parseLine(String line) {
		return line.split("\\|");
	}
	
	// -------------------------------------------------------------------
	/**
	 * Prints question validation error messages to std error.
	 * @param line	The line with an error.
	 * @param lineNum	The line number in the file.
	 * @param message	The error message to print.
	 */
	private void printError(String line, int lineNum, String message) {
		System.err.println("Line " + lineNum + " - " + line);
		System.err.println("\t" + message);
	}
}
