// Brij Malhotra
// hw4.cpp
// Purpose: Simulate a queue at an amusement park, simulated time reference 

#include <iostream>
#include <fstream>

using namespace std;

// Class declaration and member functions 

class DynamicQueue {
    
    private :
        struct QueueNode {
            string value;
            QueueNode * next;
            unsigned int time;
        };

        QueueNode * front;
        QueueNode * rear;
        int numItems;
    
    public: 
        DynamicQueue() {
            front = nullptr;
            rear = nullptr;
            numItems = 0;
        }

        ~DynamicQueue() {
            clear();
        }

        void clear(){
            int value;
            string people;
            
            while(!isEmpty()){
                dequeue(people, value);
            }
        }

        void enqueue(string person, int _time) {
            QueueNode * newNode = new QueueNode;
            newNode->value = person;
            newNode->time = _time;
            newNode->next = nullptr;

            if (isEmpty()) {
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }

            numItems++;
        }

        string dequeue(string &person, int &num) {
            if (isEmpty()) {
                cout << " The queue is empty.\n";
                return "";
            } else {
                string value  = front->value;
                QueueNode * temp = front; 
                front = front->next;

                if (front == nullptr) {
                    rear = nullptr;
                }
                
                delete temp;
                numItems--;
                return value;
            }
        }

        bool isEmpty() const { return numItems == 0; }

        int getNumItems(){
            return numItems;
        }
};

int main(){

    DynamicQueue Queue;
    string filename;
    ifstream infile;
    const int arrSize = 10000;  // Max file size that can be run in the program
    string names[arrSize];  // Array to store names
    int secondsArr[arrSize];  // Array to store seconds according to the person

    cout << endl;

    cout << "This program reads from a file and displays contents in terms of a queue." << endl;
    cout << "Please note that the max size of the file can be no more than 10000 lines." << endl << endl;
    
    cout << "Enter a filename to view: ";
    getline(cin, filename);

    infile.open(filename);

    while (!infile){
        cout << endl;
        cout << "Please enter a valid filename: ";
        getline(cin, filename);
        infile.close();
        infile.open(filename);
    }

    for (int i = 0; !infile.eof(); i++){

        string seconds, _name;

        getline(infile, seconds, ' ');  // Parsing the file strings to store time and number into respective arrays
        getline(infile, _name , '\n');
        
        secondsArr[i] = stoi(seconds); // STOI used to convert string time to int time
        names[i] = _name;
    }

    int count = 0;

    for (int i = 0; i < 43200; i++) {

        if (secondsArr[count] >= i){
            string temp = names[count];
            int tempnum = secondsArr[count];
            Queue.enqueue(temp, tempnum);           
            cout << names[count] << endl;    // Fun fact: The names do not get printed out if the endl is not there, strings and ints get confused :D
            cout << "->got in line. Seconds passed: " << secondsArr[count] << endl << endl;
            count++;
        }

        if (i % 180 == 0){   // This entire if statement is to show that every 180 seconds 8 people get dequeued and the ride details are printed out
            
            int j = 0;

            for (j = 0; j < 8 && !Queue.isEmpty(); j++){
                Queue.dequeue(names[count], secondsArr[count]);
            }

            if (j == 0){
                cout << "Not running ride since nobody was in line." << endl;
            } else {
                cout << "Starting ride with " << j << " passengers. Queue size: " << Queue.getNumItems() << "." << endl;
            }
        }
    }

    cout << endl;
    cout << "Park is closing.";
    cout << endl << endl;

    Queue.~DynamicQueue();
    infile.close();
    
    return 0;
}