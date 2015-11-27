//Rahul Patel
//UserID: rpate3
//pa1
//
 class List {
	private class node{
		int data;
		node next;
		node prev;
		
		node(int num){ //constructor
			data = num; 
			next = null;
			prev = null;
		}
		
		//second constructor (dummynode) having links to next and prev
		node(int num, node previous, node post){
			data = num;
			prev = previous;
			next = post; 
		}
		public String toString(){ 
			return "" + data;
			}
	}
	
	//variable declaration
	private static final node OFF = null; 
	private node cursor; 
	private node front; 
	private node back; 
	private int length; 
	
	public List(){ //creates empty list
		cursor = OFF;
		front = null; 
		back = null; 
		length = 0; 
	}
	
	public int length() { //returns number of elements in list
		return length;
	}
	
	//returns index of cursor element
	public int getIndex(){
		int index = -1;  //-1 if it is undefined 
		if(cursor == OFF) return index; 
		for(node temp = front; temp !=null; temp=temp.next){
			index++; 
			if(temp == cursor) break; 
		}
	return index;
	}
	
	//returns front element if length>0
	public int front(){
		if(length() > 0){
			return front.data;
		}
		throw new RuntimeException(); 
	}
	
	//returns back element if length>0 
	public int back() { 
		if(length() > 0){
			return back.data; 
		}
		throw new RuntimeException();
	}
	
	//returns element
	public int getElement(){
		if(length() > 0 && getIndex() >= 0){
			return cursor.data; 
			}
		throw new RuntimeException();
	}
	
	//returns true if this List and L are same integer sequence
	public boolean equals(List L){
		node one = front; 
		node two = L.front; 
		while(one!=null && two!=null){
			if(one.data != two.data) return false; 
			one = one.next; 
			two = two.next; 
		}
		if (one != null || two != null) return false; 
		
		return true; 
	}
	
	//Re-sets this List to the empty state.
	public void clear(){
		front = null; 
		back = null; 
		cursor = OFF; 
		length = 0; 
	}
	
	//moves the cursor to the element 
	// at index i
	public void moveTo(int i){
		if (i>=0 && i<= length()-1){
			cursor = front; 
			for(; i>0; i--) cursor = cursor.next; 
		}else {
			cursor = OFF;
		}
	}
	
	//This operation is
	// equivalent to moveTo(getIndex()-1)
	public void movePrev(){
		int index = getIndex();
		if(index >=0 && index<= length()-1){
			cursor = cursor.prev; 
		} else{
			cursor = OFF;
		}
	}

	//moves cursor one step forward
	public void moveNext(){
		int index = getIndex(); 
		if(index >=0 && index < length()-1){
			cursor = cursor.next; 
		} else{
			cursor = OFF; 
		}
	}
	
	//prepend list, inserts new element before front element in this List
	public void prepend(int data){
		length++; 
		node temp = new node(data,null,front); 
		if(front != null){
			front.prev = temp; 
		} else{
			back = temp;
		}
		front = temp;
	}
	
	//appends list, inserts new element after last element in this List
	public void append(int data){
		length ++; 
		node temp = new node(data, back, null); 
		if(back != null){
			back.next= temp; 
		} else{
			front = temp;
		}
		back=temp; 
	}
	
	
	
	
	// Inserts new element before cursor element in the list
	public void insertBefore(int data){
		if(!(length()>0 && getIndex() >=0)) return;
		length ++; 
		node temp = new node(data, cursor.prev, cursor);
		if(cursor.prev != null){
			cursor.prev.next = temp; 
		} else {
			front = temp; 
		}
		cursor.prev = temp; 
	}
	
	// Inserts new element after cursor element in this List
	public void insertAfter (int data){ 
		if(!(length() > 0 && getIndex() >= 0)) return; 
		length ++; 
		node temp = new node(data, cursor, cursor.next);
		if (cursor.next != null){
			cursor.next.prev = temp; 
		} else{
			back = temp; 
		}
		cursor.next = temp; 
	}
	
	//deletes front node
	public void deleteFront(){
		if (length() > 0){
			length--;
			if(cursor == front) cursor = OFF; 
			front = front.next; 
			front.prev = null; 
		}
	}
	
	//deletes backnode
	public void deleteBack(){
		if(length() > 0){
			length--;
			if(cursor == back) cursor = OFF; 
			back = back.prev; 
			back.next = null;
		}
	}
	
	 //Deletes cursor element in this List.
	public void delete(){
		if(length() > 0 && getIndex() >= 0){
			length--; 
			cursor.next.prev = cursor.prev; 
			cursor.prev.next = cursor.next; 
			cursor = OFF; 
		}
		
	}
	
	 //Creates a string 
	 // consisting of a space separated sequence of integers
	 // with front on the left and back on the right
	public String toString(){
		String result =""; 
		node temp = front; 
		while(temp != null){
			result += temp +" "; 
			temp = temp.next; 
		}
		return result; 
	}
	
	// Returns a new list representing the same integer sequence as this
	// list.
	public List copy(){ 
		List copy = new List(); 
		for (node temp = front; temp != null; temp= temp.next){ 
			copy.append(temp.data); 
		}
		return copy;
		}
	
	// Returns a new List which is the concatenation of 
	// this list followed by L. 
	List concat(List L){
		List linked = copy(); 
		for(node temp = L.front; temp != null; temp= temp.next){
			linked.append(temp.data);
		}
		return linked;
	}
 		
 }
 
