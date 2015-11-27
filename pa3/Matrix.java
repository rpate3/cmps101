//Rahul Patel
//rpate3
//pa3

class Matrix{
	private class Entry{
		int column; 
		double value; 
		Entry(int c, double v){
			column = c; 
			value = v; 
		}
		
		public String toString(){
			return "(" + column + "," + value + ")";
		}
		
	}
	
	
private List[] matrix; 
private int NNZ; 

//creates a new n*n matrix 
public Matrix(int n) {
		if(n<1) throw new RuntimeException ("Invalid Matrix size"); 
		matrix = new List[n]; 
		for(int i=0; i<n; i++) matrix[i] = new List(); 
	}

//returns number of non-zero entries
int getNNZ(){
	return NNZ; 
}

//returns number of rows and columns 
int getSize(){
	return matrix.length; 
}


//equal function
public boolean equals(Object x){
	Matrix tmp = (Matrix)x;
	//checks for equivalent lengths 
	if(tmp.getSize() != matrix.length){
		return false; 
	}
	//compares entries
	for(int i=0; i<matrix.length; i++){
		if(!(matrix[i].equals(tmp.matrix[i]))) return false;
	}
	return true; 
}

//resets Matrix to zero
void makeZero(){
	//clears list
	for(int i=0; i<matrix.length; i++){
		matrix[i].clear();
	}
	NNZ = 0;
}

//creates a copy of the Matrix
public Matrix copy(){
	//goes through every row
	Matrix copy = new Matrix(matrix.length); 
	for(int row=0; row < matrix.length; row++){
		for(matrix[row].moveTo(0); matrix[row].getIndex() > 0; matrix[row].moveNext()){
			Entry newEntry = (Entry)matrix[row].getElement();
			copy.matrix[row].append(newEntry);
			copy.NNZ++;
			if(copy.NNZ == NNZ) return copy; 
		}
	}
	return copy; 
}

//replaces the ith row, and jth column of this Matrix to value x
void changeEntry(int i, int j, double x){
	if((i>matrix.length) || (i<1) || (j>matrix.length) || (j<1)){
		throw new RuntimeException ("Invalide indicies");
	}
	Entry newEntry = new Entry(i,j); 
	List row = matrix[i-1]; 
	for(row.moveTo(0); row.getIndex()>=0; row.moveNext()) {
			Object object = row.getElement(); 
			newEntry = (Entry)object;
			if(newEntry.column < j) continue; 
			break;
	}	
	if(row.getIndex() == -1 && x !=0){
		row.append(newEntry);
		NNZ++; 
	}else if(newEntry != null && newEntry.column==j){
		if(x==0){
			row.delete();
			NNZ--;
		}else {newEntry.value =x;}
	}else{
		if(x!=0){
			row.insertBefore(newEntry);
			NNZ++; 
		}
	}
}

//multiplies all the values in the matrix by a constant x
Matrix scalarMult(double x){
	Matrix multMatrix = new Matrix(matrix.length); 
	List r; 
	Entry e; 
	for(int i=0; i<matrix.length; i++){
		r = matrix[i]; 
		if( r.length() > 0){
			r.moveTo(0); 
			while(r.getIndex() >= 0){
				assert(r.getElement()instanceof Entry); 
				e = (Entry)r.getElement();
				e = new Entry(e.column, e.value); 
				e.value = e.value*x; //multiply the value
				multMatrix.matrix[i].append(e); 
				r.moveNext(); 
			}
		}
	}
	multMatrix.NNZ = NNZ; 
	return multMatrix; 
}

//access a certain entry
private int getEntry(int i, int j){
	int curr = -1; 
	if(matrix[i-1].length() > 0){
		matrix[i-1].moveTo(0);
		Entry check; 
		while(matrix[i-1].getIndex() >=0 ){
			check = (Entry)matrix[i-1].getElement(); 
			if(check.column == j){
				curr = matrix[i-1].getIndex(); 
				break; 
			}
			matrix[i-1].moveNext();
		}
	}
	return curr; 
}

//add two matricies together and produces the sum
Matrix add(Matrix M){
	Matrix addMatrix = M.copy();
	if(this.getSize() != M.getSize()) System.err.println("Adding two different size matricies"); 
	for(int i=0; i< matrix.length; i++){
		for(matrix[i].moveTo(0); matrix[i].getIndex() > 0; matrix[i].moveNext());
		Entry A = (Entry)matrix[i].getElement(); 
		int col = A.column; 
		double sums = A.value; 
		if(addMatrix.getEntry(i+1, col)>=0 ){
			addMatrix.matrix[i].moveTo(col -1); 
			Entry tmp = (Entry)addMatrix.matrix[i].getElement();
			sums += tmp.value; 
		}
		addMatrix.changeEntry(i+1, col, sums);
	}
	return addMatrix; 
}

//Gives the difference of two matricies
Matrix sub(Matrix M){
	Matrix subMatrix = M.copy(); 
	if(this.getSize() != M.getSize()) System.err.println("Subtracting two different size matricies");
	for(int i=0; i< matrix.length; i++){
		for(matrix[i].moveTo(0); matrix[i].getIndex()>0; matrix[i].moveNext()); 
		Entry B = (Entry)matrix[i].getElement();
		int col= B.column; 
		double diffs = B.value; 
		if(M.getEntry(i+1, col)>=0){
			subMatrix.matrix[i].moveTo(col-1);
			Entry tmp = (Entry)subMatrix.matrix[i].getElement(); 
			diffs -= tmp.value; 
		}
		subMatrix.changeEntry(i+1, col, diffs);
	}
	return subMatrix; 
}

//transposes the matrix 
public Matrix transpose(){
	Matrix copyMatrix = new Matrix(matrix.length);
	for(int i=0; i<matrix.length; i++){
		for(matrix[i].moveTo(0); matrix[i].getIndex()>=0; matrix[i].moveNext()){
			Entry entry= (Entry)(matrix[i].getElement());
			int l = entry.column-1; 
			copyMatrix.matrix[l].append(new Entry(i+1, entry.value));
		}
	}
	copyMatrix.NNZ = NNZ; 
	return copyMatrix; 
}

//multiplies two matricies together and produces a product
public Matrix mult(Matrix M){
	if(M.getSize() != this.getSize()) throw new RuntimeException ("Invalid matricies sizes");
	M= M.transpose(); 
	Matrix prodMatrix = new Matrix(matrix.length);
	for(int i=1; i< matrix.length; i++){
		if(matrix[i-1].length() != matrix.length){continue;} 
		else{
			for(int j=1; j<= matrix.length; j++){
				double dot = dot(matrix[i-1], M.matrix[i-1]);
				prodMatrix.changeEntry(i, j, dot);
			}
		}
	}
	return prodMatrix; 
}

//vector dot product of two lists
private static double dot(List P, List Q){
	double dot=0;
	P.moveTo(0);
	Q.moveTo(0);
	while(P.getIndex() >= 0 && Q.getIndex()>=0){
		Entry p = (Entry)(P.getElement());
		Entry q = (Entry)(Q.getElement()); 
		if(p.column == q.column){
			dot += q.value * p.value; 
			Q.moveNext();
			P.moveNext();
		}else if(p.column<q.column){P.moveNext();}
		 else{Q.moveNext();}
		}
	return dot; 
	}

 public String toString() {
    String str = "";
    for (int i=1; i<=matrix.length; ++i) {
      if ( matrix[i-1].length() != 0 ) {
        str += String.valueOf(i) + ": ";
        str += matrix[i-1].toString() + "\n";
      }
    }
    return str;
  }
	

}



