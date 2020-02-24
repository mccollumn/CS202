/**
 * 
 * @file	Validate.java
 * @author 	Nick McCollum
 * @version	1.0
 * 
 * CS-202 - Assignment 4 - Java Basics
 * Validates a file containing quiz questions.
 * 
 */

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Validate {

	public static void main(String[] args) {
		String filename = getFilename(args);
		Scanner file = readFile(filename);
		
		System.out.println("\nValidating " + filename + "...\n");
		
		int lineNum = 1;
		int errorCount = 0;
		while (file.hasNextLine()) {
			String line = file.nextLine();
			if (!validateLine(line, lineNum)) {
				errorCount++;
				System.err.println();
			}
			lineNum++;
		}
		file.close();
		
		System.out.println(lineNum + " questions processed.");
		System.out.println(errorCount + " lines with errors found.");
	}

	/**
	 * Gets the filename argument entered.
	 * Prompts for a filename if one was not provided on the cmd line.
	 * 
	 * @param args
	 * 		The cmd line arguments
	 * @return	The filename.
	 */
	public static String getFilename(String[] args) {
		String filename;
		if (args.length > 0) {
			filename = args[0];
		}
		else {
			Scanner in = new Scanner(System.in);
			System.out.println("Please enter a filename:");
			filename = in.nextLine();
			in.close();
		}
		return filename;
	}
	
	/**
	 * Opens a file and returns a Scanner object
	 * 
	 * @param filename
	 * 		Name of file to open.
	 * @return	Scanner object for open file.
	 */
	public static Scanner readFile(String filename) {
		File file = new File(filename);
		Scanner fsc = null;
		try {
			 fsc = new Scanner(file);
		}
		catch (FileNotFoundException e){
			System.err.println("Error: " + file.getAbsolutePath() + " not found.");
			System.exit(-1);
		}
		return fsc;
	}
	
	/**
	 * Validates a line from the question file
	 * 
	 * @param line
	 * 		The line to validate
	 * @param lineNum
	 * 		The line number in the file
	 * @return	True if the line is valid, false if not
	 */
	public static boolean validateLine(String line, int lineNum) {
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
	
	/**
	 * Determines if the line is a properly delimited question.
	 * Used to check for bad lines before validating specific conditions.
	 * 
	 * @param line
	 * 		The line to validate.
	 * @param lineNum
	 * 		The line number in the file.
	 * @return	True if line if valid, false if not
	 */
	public static boolean isValidLine(String line, int lineNum) {
		if (numFields(line) <= 1) {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tInvalid line");
			return false;
		}
		return true;
	}
	
	/**
	 * Performs validation for specific question types
	 * 
	 * @param type
	 * 		Question type
	 * @param line
	 * 		The line to validate
	 * @param lineNum
	 * 		The line number from the file
	 * @return	True if question type if valid, false if not
	 */
	public static boolean validateType(String type, String line, int lineNum) {
		boolean isValid = true;
		int fields = 0;
		
		if (type.equalsIgnoreCase("SA") || type.equalsIgnoreCase("TF")) {
			fields = 4;
		}
		else if (type.equalsIgnoreCase("MC") || type.equalsIgnoreCase("MA")) {
			fields = 5;
		}
		else {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tInvalid question type");
		}
		
		if (fields != 0 && numFields(line) != fields) {
			printFieldsError(line, lineNum, fields);
			isValid = false;
		}
		
		if (type.equalsIgnoreCase("TF")) {
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
	
	/**
	 * Validates T/F questions
	 * 
	 * @param line
	 * 		Line to validate
	 * @param lineNum
	 * 		Line number from the file
	 * @return	True if valid T/F question, false if not
	 */
	public static boolean validateTF(String line, int lineNum) {
		String[] tokens = parseLine(line);
		String answer = tokens[3].strip().toLowerCase();
		if (answer.equals("t") || answer.contentEquals("f") || answer.equals("true") || answer.contentEquals("false")) {
			return true;
		}
		else {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tInvalid true/false answer (valid options are T/F or True/False)");
			return false;
		}
	}
	
	/**
	 * Validates multiple choice questions
	 * 
	 * @param line
	 * 		Line to validate
	 * @param lineNum
	 * 		Line number from the file
	 * @return	True if valid MC question, false if not
	 */
	public static boolean validateMC(String line, int lineNum) {
		boolean isValid = true;
		String[] tokens = parseLine(line);
		String answer = tokens[4].strip().toUpperCase();
		String choices = tokens[3].strip();
		
		if (answer.length() != 1) {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tInvalid multiple choice answer");
			isValid = false;
		}
		else if (!isValidChoice(answer, numChoices(choices))) {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tMultiple choice answer is not one of the choices");
			isValid = false;
		}
		if (numChoices(choices) <= 1) {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tMultiple choice questions need at least two answers");
			isValid = false;
		}
		
		return isValid;
	}
	
	/**
	 * Validates multiple answer questions
	 * 
	 * @param line
	 * 		Line to validate
	 * @param lineNum
	 * 		Line number from the file
	 * @return	True if question is valid, false if not
	 */
	public static boolean validateMA(String line, int lineNum) {
		boolean isValid = true;
		String[] tokens = parseLine(line);
		String answer = tokens[4].strip().toUpperCase();
		String choices = tokens[3].strip();
		
		if (answer.length() > numChoices(choices)) {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tInvalid answer");
			isValid = false;
		}
		else {
			String[] answers = answer.split("");
			for (String a : answers) {
				if (!isValidChoice(a, numChoices(choices))) {
					System.err.println("Line " + lineNum + " - " + line);
					System.err.println("\tAnswer " + a + " is not one of the choices");
					isValid = false;
				}
			}
		}
		if (numChoices(choices) <= 1) {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tMultiple answer questions need at least two answers");
			isValid = false;
		}
		
		return isValid;
	}
	
	/**
	 * Gets the number of choices for the question
	 * 
	 * @param choices
	 * 		String of : delimited choices
	 * @return	Number of choices
	 */
	public static int numChoices(String choices) {
		long numChoices = choices.chars().filter(ch -> ch == ':').count() + 1;
		return (int)numChoices;
	}
	
	/**
	 * Checks if the answer correlates with the choices.
	 * For MA and MC question types.
	 * 
	 * @param answer
	 * 		Answer
	 * @param numChoices
	 * 		Number of choices
	 * @return
	 */
	public static boolean isValidChoice(String answer, int numChoices) {
		return (answer.charAt(0) - 'A') < numChoices;
	}
	
	/**
	 * Splits a line on the | delimiter
	 * 
	 * @param line
	 * 		Line to parse
	 * @return	Array of strings
	 */
	public static String[] parseLine(String line) {
		return line.split("\\|");
	}
	
	/**
	 * Check if the line is a comment
	 * 
	 * @param line
	 * 		The line to check
	 * @return	True if line is a comment, false if not
	 */
	public static boolean isComment(String line) {
		if (line.stripLeading().startsWith("#") || line.stripLeading().startsWith("//")) {
			return true;
		}
		return false;
	}
	
	/**
	 * Provides the number of fields for the question
	 * 
	 * @param line
	 * 		The question
	 * @return	Number of fields
	 */
	public static int numFields(String line) {
		String[] tokens = parseLine(line);
		return tokens.length;
	}
	
	/**
	 * Prints error message for invalid number of fields
	 * 
	 * @param line
	 * 		The line with incorrect number of fields
	 * @param lineNum
	 * 		The line number from the file
	 * @param fields
	 * 		Number of fields expected
	 */
	public static void printFieldsError(String line, int lineNum, int fields) {
		System.err.println("Line " + lineNum  + " - " + line);
		System.err.println("\tInvalid number of fields (must have " + fields + ")");
	}
	
	/**
	 * Check if the question type is valid
	 * 
	 * @param type
	 * 		Type of question
	 * @return	True if question type is valid, false if not
	 */
	public static boolean isValidType(String type) {
		String[] validTypes = {"SA", "TF", "MC", "MA"};
			for (String validType: validTypes) {
				if (type == validType);
				return true;
			}
		return false;
	}
	
	/**
	 * Gets the question type
	 * 
	 * @param line
	 * 		The question line
	 * @return	The question type
	 */
	public static String getType(String line) {
		String[] tokens = parseLine(line);
		String type = tokens[0].strip().toUpperCase();
		
		if (isValidType(type)) {
			return type;
		}
		return null;
	}
	
	/**
	 * Checks if the question level is valid
	 * 
	 * @param levelStr
	 * 		The level value as a string
	 * @return	True if the level is valid, false if not
	 */
	public static boolean isValidLevel(String levelStr) {
		boolean isValid = true;
		try {
			int level = Integer.parseInt(levelStr);
			if (level < 1 || level > 9) {
				isValid = false;
			}
		}
		catch (NumberFormatException e) {
			isValid = false;
		}
		
		return isValid;
	}
	
	/**
	 * Gets the question level
	 * 
	 * @param line
	 * 		Question line
	 * @param lineNum
	 * 		Line number from the file
	 * @return	The question level
	 */
	public static String getLevel(String line, int lineNum) {
		String[] tokens = parseLine(line);
		String level = tokens[1].strip();
		
		if (isValidLevel(level)) {
			return level;
		}
		else {
			System.err.println("Line " + lineNum + " - " + line);
			System.err.println("\tInvalid level");
			return null;
		}
	}
}
