/**
 * CS-202 - Assignment 6 - Java Collections
 * Spell checks the specified text file.
 * 
 * Usage: SpellCheck [file] [dictionary]
 * 
 * @author Nick McCollum
 * @version 1.0
 */

import java.util.Scanner;
import java.util.TreeMap;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Map;

public class SpellCheck {
	
	private final static String DICTIONARY_FILE = "words.txt";
	
	// -------------------------------------------------------------------
	/**
	 * Checks if any command line arguments were provided
	 * and captures the first as the name of the file to be spell checked.
	 * If no arguments were provided, the user is prompted for the filename.
	 * @param args	Command line arguments from main
	 * @return String	The name of the file to check
	 */
	public static String getFilename(String[] args) {
		String filename;
		Scanner input = new Scanner(System.in);

		if (args.length > 0) {
			filename = args[0];
		}
		else {
			System.out.println("Please enter a filename:");
			filename = input.nextLine();
		}
		
		input.close();
		return filename;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Checks if a second command line argument was provided
	 * and captures it as the dictionary file to use.
	 * If no argument was provided, the default file is used.
	 * @param args	Command line arguments from main
	 * @return String	The name of the dictionary file
	 */
	public static String getDictionary(String[] args) {;
		if (args.length > 1) {
			return args[1];
		}

		return DICTIONARY_FILE;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Opens specified file for reading.
	 * @param filename	Name of the file to open.
	 * @return Scanner	File Scanner object.
	 */
	private static Scanner readFile(String filename) {
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
	 * Loads the dictionary file into a hash set
	 * @param filename	Name of the dictionary file
	 * @return HashSet	The object containing all dictionary words
	 */
	public static HashSet<String> loadDictionary(String filename) {
		HashSet<String> words = new HashSet<String>();
		Scanner file = readFile(filename);
		while (file.hasNext()) {
			words.add(file.next());
		}
		return words;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Loads the file to check into an array list
	 * @param filename	Name of the file
	 * @return ArrayList	The object containing all words to spell check
	 */
	public static ArrayList<String> loadFile(String filename) {
		ArrayList<String> words = new ArrayList<String>();
		Scanner file = readFile(filename);
		// Parse on space first, then replace non-alpha chars
		//file.useDelimiter("[^a-zA-Z]+");
		while (file.hasNext()) {
			String word = file.next();
			word = word.replaceAll("[^a-zA-Z]", " ").strip().toLowerCase();
			if (!word.isBlank()) {
				words.add(word);
			}
		}
		return words;
	}
	
	// -------------------------------------------------------------------
	/**
	 * Keeps track of all misspelled words and the number of occurrences of each.
	 * @param word	The misspelled word to add to the list
	 * @param misspelledWords	The map containing all misspelled words
	 */
	public static void addMisspelledWord(String word, TreeMap<String, Integer> misspelledWords) {
		Integer wordCount = misspelledWords.get(word);
		if (wordCount == null) {
			wordCount = 1;
		}
		else {
			wordCount++;
		}
		misspelledWords.put(word, wordCount);
	}
	
	// -------------------------------------------------------------------
	/**
	 * Prints a list of all misspelled words and then number of occurrences.
	 * @param misspelledWords	The map containing all misspelled words
	 */
	public static void printMisspelledWords(TreeMap<String, Integer> misspelledWords) {
		for (Map.Entry<String, Integer> word : misspelledWords.entrySet()) {
			System.out.println(word.getKey() + " (" + word.getValue() + ")");
		}
		
	}
	
	// -------------------------------------------------------------------
	/**
	 * Checks spelling of all words in the provided file.
	 * @param fileToCheck	Name of the file to spell check
	 * @param dictionaryFile	Name of the dictionary file
	 */
	public static void spellCheck(String fileToCheck, String dictionaryFile) {
		HashSet<String> dictionary = new HashSet<String>();
		dictionary.addAll(loadDictionary(dictionaryFile));
		
		ArrayList<String> file = new ArrayList<String>();
		file.addAll(loadFile(fileToCheck));
		
		TreeMap<String, Integer> misspelledWords = new TreeMap<String, Integer>();
		int numMisspelled = 0;
		
		for (String word : file) {
			if (!dictionary.contains(word)) {
//				System.out.println(word);
				addMisspelledWord(word, misspelledWords);
				numMisspelled++;
			}
		}
		
		printMisspelledWords(misspelledWords);
		
		System.out.println("\nWords checked: " + file.size());
		System.out.println("Words misspelled: " + misspelledWords.size());
		System.out.println("Total instances of misspelled words: " + numMisspelled);
	}
	
	// -------------------------------------------------------------------
	public static void main(String[] args) {
		String fileToCheck = getFilename(args);
		String dictionaryFile = getDictionary(args);
		
		System.out.println("\nSpell checking: " + fileToCheck);
		System.out.println("Using dictionary: " + dictionaryFile);
		
		System.out.println("\nMisspelled words:");
		spellCheck(fileToCheck, dictionaryFile);
	}

}
