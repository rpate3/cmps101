//Rahul Patel
//rpate3	
//pa3

import java.io.*;
import java.util.Scanner;


public class Sparse {
	//checks input line 
	public static void main(String args[]) throws FileNotFoundException{
	if(args.length != 2){
		System.out.println("Incorrect argument length");
	}
	//reads in files
	PrintWriter out = new PrintWriter(args[1]);
	Scanner scan = new Scanner(new File(args[0]));
	int size = scan.nextInt(); 
	int one = scan.nextInt(); 
	int two = scan.nextInt();
	Matrix A = new Matrix (size); 
	Matrix B = new Matrix (size); 
	scan.nextLine(); 
	//stores information
	for(int i =0; i< one; i++){
		int r = scan.nextInt(); 
		int c = scan.nextInt();
		double v = scan.nextDouble(); 
		A.changeEntry(r, c, v);
	}
	scan.nextLine(); 
	for(int i=0; i<two; i++){
		int r = scan.nextInt();
		int c = scan.nextInt(); 
		double v = scan.nextDouble(); 
		B.changeEntry(r, c, v);
	}
	//appropriate command lines 
	out.println("A has" + one + "NNZ entries");
	out.println(A);
	out.println("B has" + two + "NNZ entries");
	out.println(B);
	out.println("(1.5)*A =");
	out.println(A.scalarMult(1.5));
	out.println("A + A =");
	out.println(A.add(A));
	out.println("A - A =");
	out.println(A.sub(A));
	out.println("B transpose = ");
	out.println(B.transpose());
	out.println("B*B =");
	out.println(B.mult(B));

	scan.close(); 
	out.close();
}
	
}
