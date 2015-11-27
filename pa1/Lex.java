//Rahul Patel
//UserID: rpate3
//pa1

import java.io.*;
import java.lang.System;
import java.util.Scanner;

class Lex{

	
	public static void main(String[] args){
		if(args.length < 2){				//Checks if command line is valid
			System.err.println("Invalid inputs");
			System.exit(1); 		
	} 
	//Allocated space for file being read in and one being outputted with exception handling
	Scanner in = open(args[0]);
	PrintWriter out = null;	
	try{
		out = new PrintWriter(new FileWriter(args[1]) );
	} catch (FileNotFoundException e){
		System.err.println("File can not be created"); 
		System.exit(1); 
	} catch(IOException e){
		System.err.println("File can not be created");
		System.exit(1);
	}	
	int linec = countlines(in); //Number of lines n in file arg[0]
	in = open(args[0]);
	String [] array = read(in, linec);
	List l = insertsort(array);//A list with the sorted items	
	for(l.moveTo(0); l.getIndex()>=0; l.moveNext()){//Print out the elements of indicies
		out.println(array[l.getElement()]);
	}
	out.close();
}
	//Used to access/open the .txt file
	static Scanner open(String filename){ 
		Scanner in = null; 
		try{
			in = new Scanner(new File(filename)); 
		} catch (IOException e){ 
			System.err.println("Invalid file");
			System.exit(1); 
		}
		return in; 
	}

	//keeps track of the number of lines in the file 
	static int countlines(Scanner file){ 
		int i = 0; 
		for(i=i; file.hasNextLine(); file.nextLine()) i++; 
		return i; 
	}
	
	//goes through each line and stores it into a String array
	static String[] read(Scanner file, int lines){
		String[] Stringarray = new String[lines]; 
		for(int i=0; file.hasNextLine(); i++){
		Stringarray[i] = file.nextLine();  
		}
		return Stringarray; 
		
	}
	
	//sorts the list
	static List insertsort(String[] file){
		List list = new List(); //creates new list  
		list.append(0);//appends a 0
		for(int j =1; j< file.length; j++){ 
			String hold = file[j]; 
			int cursor = j-1; 
			list.moveTo(cursor); //sets cursor to current position
		
		while(cursor > -1 && hold.compareTo(file[list.getElement()])<0){//while loop to move the cursor along the list to find the proper position for insertion
				cursor--; 
				list.movePrev(); 
			}
		if(list.getIndex() == -1){ //if cursor = null, prepend
			list.prepend(j); 
		}else{
			list.insertAfter(j); 
		
			}	
			}
	return list; 
	}

}
