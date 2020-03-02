/**
 * CS-202 - Assignment 5 - Java Classes
 * Main method that drives the quiz app.
 * Captures the questions file name from the command line and instantiates a Quiz object.
 * 
 * @author Nick McCollum
 * @version 1.0
 *
 */

import java.util.Scanner;

public class QuizApp {

	public static void main(String[] args) {
		try {
			Scanner in = new Scanner(System.in);
			String dataFileName = getFilename(args, in);
			Quiz quiz = new Quiz(dataFileName);
			
			boolean again = false;
			do {
				quiz.deliverQuiz(again, in);
				int numIncorrect = quiz.getIncorrectCount();
				again = numIncorrect > 0 ? takeAgain(numIncorrect, in) : false;
			} while (again);
			in.close();
		}
		catch (Exception e) {
			System.err.println("Error: Something has gone terribly wrong.");
			System.err.println(e.getMessage());
			System.exit(-1);
		}

	}
	
	// -------------------------------------------------------------------
	/**
	 * Captures the filename if one was provided as a cmd line argument.
	 * If not, prompts the user to enter the filename.
	 * @param args	Cmd line arguments from main.
	 * @param input	The Scanner to use for user input.
	 * @return String	The name of the file.
	 */
	public static String getFilename(String[] args, Scanner input) {
		String filename;
		if (args.length > 0) {
			filename = args[0];
		}
		else {
			System.out.println("Please enter a filename:");
			filename = input.nextLine();
		}
		return filename;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Prompts the user to take the quiz again.
	 * @param numIncorrect	Number of questions that were incorrect.
	 * @param againInput	The Scanner to use for user input.
	 * @return	boolean	True if the user wants to take the quiz again,
	 * 					false if not.
	 */
	public static boolean takeAgain(int numIncorrect, Scanner againInput) {
		boolean takeAgain = false;
		String s = numIncorrect > 1 ? "s" : "";
		System.out.println("You got " + numIncorrect + " question" + s + " wrong.");
		System.out.println("Would you like to try the one" + s + " you missed again? (Yes / No)");
		
		String again = againInput.nextLine();
		if (again.toLowerCase().startsWith("y")) {
			System.out.println();
			takeAgain = true;
		}
		
		return takeAgain;
	}

}
