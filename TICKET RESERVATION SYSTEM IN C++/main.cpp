/**
*** Name - 
*** Date -
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <cmath>


#include "Auditorium.h"
#include "Seat.h"
#include "Node.h"


using namespace std;

struct Ticket{ // Ticket Struct

   int row; // variable that stores the row of the ticket
   char column; // variable that stores the column aka the seat letter of the ticket

   Ticket(int r, char c) // constructor of the ticket
   {
      row = r; // sets the row variable to row parameter
      column = c; // sets the column variable to the seat letter parameter
   }


};

struct Order{ // Order Struct

   int auditoriumNumber; // variable that stores auditorium number
   int adultTotal; // variable that stores the total amount of adult tickets
   int childTotal; // variable that stores the total amount of child tickets
   int seniorTotal; // variable that stores the total amount of senior tickets
   vector<Ticket> adultList; // vector that stores all adult Tickets of the order
   vector<Ticket> childList; // vector that stores all child Tickets of the order
   vector<Ticket> seniorList; // vector that stores all senior Tickets of the order
   int totalTickets;

   Order(int aTotal, int cTotal, int sTotal, int audiNum) // Order struct constructor
   {
      adultTotal = aTotal; // sets the adultTotal variable to the parameter of total adult tickets
      childTotal = cTotal; // sets the childTotal variable to the parameter of total child tickets
      seniorTotal = sTotal; // sets the seniorTotal variable to the parameter of total senior tickets
      auditoriumNumber = audiNum; // sets the auditoriumNumber variable to the parameter of auditorium number
   }

};

// class User{ // User Class

//    public:
//       // constructors
//       User(){username = " "; password = " ";} // default constructor
//       User(string u, string p){username = u; password = p;} // overloaded constructor

//       // accessors
//       vector<Order>& getOrders(){return orders;} // accessor that returns order vector
//       string getUsername(){return username;} // accessor that returns the username of user
//       string getPassword(){return password;} // accessor that returns the password of user

//       // mutators
//       void setUsername(string u){username = u;} // accessor that returns the username of user
//       void setPassword(string p){password = p;} // accessor that returns the password of user

//    private:
//       string username, password; // variable that stores username and password
//       vector<Order> orders; // vector that stores the orders of the user

// };


int cnt_rows(string fn) // counts the total number of rows in the file
{
   ifstream ifs; // inputfilestream
   int totalrow = 0; // variable to store the counter for total rows of auditorium
   string line = " "; // variable to store the line being read in from file

   ifs.open(fn); // open the file with filename fn

   while(getline(ifs, line)) // while can getline() from the file
   {
      totalrow++; // increment the counter by 1
   }
   ifs.close(); // close the file
   return totalrow; // return the total number of rows in the file
}

int cnt_seats(string fn) // counts the total number of seats/columns in the file
{
   ifstream ifs; // inputfilestream
   string line = " "; // variable that stores the line being read in from the file

   ifs.open(fn); // open the file with filename fn
   getline(ifs, line); // get the first line of the file
   ifs.close(); // close the file

   return (int)line.length(); // return the length of the line (which should be total number of seats of the auditorium
}

bool isNumber(string str) // function to check if the user input is a number
{
   for(long long unsigned int i = 0; i < str.length(); i++) // loops through each character in user input
   {
      if(!isdigit(str.at(i))) // if the character is not a digit, then return false
      {
         return false; // return false
      }
   }
   return true; // if all the characters are digits, return true
}

/** Reservations Functions **/

void displayAuditorium(Auditorium &theater, int totalRows, int totalSeats) // function to display theater on console
{
   Node<Seat*>*printablenode = theater.getfirst(); // pointer to head node
   int a = 0; // variable used for loop to move pointer down rows
   int b = 0; // variable used for loop to print out the seats
   int c = 0; // variable used for loop to display theater
   int ch = 65; // variable used to print out seat labels
   int rNum = 1; // variable that stores row number being displayed on auditorium

   cout << "  "; // prints out two spaces on console
   for(int i = 0; i < totalSeats; i++) // loops up till total number of seats in row
   {
      cout << char(ch); // prints out the ASCII -> character
      ch+=1; // increments the ASCII number of ch
   }
   cout << endl; // moves to next line on console

   while(c < totalRows-1) // loops up till the total number of rows in auditorium
   {
      if(c != 0) // if not the first row
      {
         a = 0; // sets the loop counter to 0
         printablenode = theater.getfirst(); // sets node pointer to point to head node
         while(a < c) // moves pointer down a row depending on if seats on previous row are done printing out
         {
            if(printablenode->getdown() != 0) // if there is another row !(nullptr == 0 address)
            {
                printablenode = printablenode->getdown(); // move pointer down the row
            }
            a++; // increment loop counter by 1
         }
      }

      b = 0; // resets b loop counter to 0
      cout << rNum << " "; // prints out the row number
      rNum++; // increments the row number
      while(b < totalSeats) // loop to display seats
      {
        // std::cout<<printablenode->getpayload()->getTT(); 

         if(printablenode->getpayload()->getTT() == 'A' || printablenode->getpayload()->getTT() == 'C' || printablenode->getpayload()->getTT() == 'S') // if seat already reserved
         {
            std::cout<< '#'; // print out a hashtag
         }
         else // else the seat is not reserved
         {
            std::cout<< '.'; // print out '.'
         }
         printablenode = printablenode->getright();

        //  if(b != totalSeats-1) // if not the last seat in row
        //  {
        //      printablenode = printablenode->getright();// move the pointer to right node
        //  }
         

         b++; // increment the b loop counter
        // std::cout <<b;
      }

      std::cout << endl;
      // std::cout << c; // moves to next line
      c++; // increment c loop counter
   }
   
}

int bestAvailable(Auditorium& theater, int &row, int total_quantity, int totalRows, int totalSeats) // Returns best available starting seat
{
   int i = 1; // starting seat = i- 1
   int j = 0; // inner loop counter
   int k = 0; // is the iterator for the while loop that moves the pointer y down in the row loop
   char m; // stores starting seat of the section that is closest to middle
   int r = -1; // stores the row of the seat that is closest to middle
   bool n = false; // stores the boolean value that is used in the if statement to see if the seats checked are empty, true if empty, false if not empty
   double distance  = 999999999.0; // sets as high number, so that the if statement inside the outer loop will set the first distance equal to it (it is used for previousDistance calculated variable)
   double h = 0.0; // the current distance that is calculated (used to compare h with distance variable) distance variable is the previous distance calculated

   Node<Seat*>*y = theater.getfirst(); // pointer used to keep track of starting seat
   Node<Seat*>*yNext = nullptr; // pointer used to keep track and access seats for j loop
   for(int x = 0; x < totalRows; x++) // the loop that iterates each row
   {

      k = 0; // resets the iterator for while loop that move pointer y down in row loop
      while(k < x) // loop that moves the starting seat pointer down a row except for when it points to last row
      {
         if(k != totalRows- 1) // makes sure it does not go out of bounds
         {
            y = y->getdown(); // move down a row
         }

         k++; // increment iterator
      }

      for(i = 1; i < totalSeats - total_quantity + 1+1; i++) // loop through every seat in the row to see if there can be any reservations
      {
         n = true; // sets empty? checker to true
         yNext = y; // sets the position in grid of yNext to y, the starting seat
         for(j = 0; j < total_quantity; j++) // find way to save the middle seat aka the starting seat into variable maybe
         {
            if(yNext->getpayload()->getTT() != '.') // if one of the seats is not empty
            {
               n = false; // seats are not empty? false
               break; // break out of loop
            }

            yNext = yNext->getright(); // move pointer to seat to the right

         }


         if(n) // checks if all seats that are checked in inner loop are empty
         {
            h = fabs(sqrt((pow(((i + (total_quantity - 1)/2.0) - (totalSeats + 1)/2.0),2) + pow(((x + 1) - ((totalRows+1)/2.0)),2)))); // calculate distance of this starting seat (middle of selection) to center of auditorium
            if(h < distance) // h is the previous distance from before; if h is less than the previous distance calculated, set distance to new distance
            {
               m = y->getpayload()->getSeat(); // stores new starting seat letter
               r = y->getpayload()->getRow(); // stores new row number
               distance = h; // distance will save the smallest distance calculated
            }
            else if(h == distance) // if tie
            {
               if(abs(((totalRows+1)/2.0) - y->getpayload()->getRow()) < abs(((totalRows+1)/2.0) - r)) // if calculated distance is closer to the middle row
               {
                  m = y->getpayload()->getSeat(); // starting seat letter
                  r = y->getpayload()->getRow(); // row number
                  distance = h; // distance will save the smallest distance calculated
               }
               else if(abs(((totalRows+1)/2.0) - y->getpayload()->getRow()) == abs(((totalRows+1)/2.0) - r)) // both the calculated distance and the current small distance is same distance from middle, set the row to smallest number
               {
                  if(y->getpayload()->getRow() < r) // if the row of current row is less than the row of the saved distance row, then set the distance to the current distance
                  {
                     m = y->getpayload()->getSeat(); // starting seat letter
                     r = y->getpayload()->getRow(); // row number
                     distance = h; // distance will save the smallest distance calculated
                  }

               }
            }
         }
         y = y->getright(); // move one seat to right

      }
       y = theater.getfirst(); // sets to point to head of auditorium


   }
   if(distance != 999999999.0) // checks if there are seats available on the row
   {
      row = r; // sets row that was passed by reference to the new row r
      return int(m)-65; // returns the starting seat index
   }
   return -1; // if no seats are available on the row, then return -1
}

void reserveSeats(Auditorium& theater, int row, char seat, int adult_quantity, int senior_quantity, int child_quantity, int totalSeats) // reserves user chosen seats
{
  //  std::cout<<"entering"<<endl;
   int A_count = adult_quantity; // total adult tickets
   int S_count = senior_quantity; // total senior tickets
   int C_count = child_quantity; // total child tickets
   int col = int(toupper(seat)) - 65; // converts char seat into the ASCII value of the char, then subtracts from the ASCII value of A to find the distance from column spot 0
   Node<Seat*>*r = theater.getfirst(); // pointer that currently points to head node
   int k = 0; // loop iterator to find correct row to reserve
   while(k < row-1) // positions at correct row
   {
      r = r->getdown(); // move pointer down
      k++; // increase iterator by 1
   }

   for(int i = 0; i < totalSeats; i++) // finds where starting seat is at
   {
      if(r->getpayload()->getSeat() == seat) // if seat located then break out of loop
      {
         break; // break out of loop
      }
      if(i != totalSeats - 1) // if not last seat in row
      {
         r = r->getright(); // move pointer to right
      }

   }

   for(int c = col; c < totalSeats; c++) // iterates through every seat after the starting seat
   {
      if(r->getpayload()->getTT() == '.') // if seat is empty
      {
         if(A_count > 0) // if there are still adult tickets to be reserved, reserve them
         {
           r->getpayload()->setTT('A');// reserves seat
           A_count -= 1; // decreases total adult tickets needed to be reserved by 1

         }
         else if(C_count > 0) // if there are still child tickets to be reserved, reserve them
         {
            r->getpayload()->setTT('C');; // reserves seat
            C_count -= 1; // decreases total child tickets needed to be reserved by 1
         }
         else if(S_count > 0)  // if there are still senior tickets to be reserved, reserve them
         {
            r->getpayload()->setTT('S'); // reserves seat
            S_count -= 1; // decreases total senior tickets needed to be reserved by 1
         }
      
      }
      if(c != totalSeats-1) // if not last seat in row
      {
         r = r->getright(); // move pointer to right node
      }

   }
    // std::cout<<"leaving"<<endl;
    
   
}

bool checkAvailability(Auditorium& theater, int row, char seat, int total_quantity, int totalSeats) // checks if there are enough empty seats for total seats the user wants to reserve
{
   int col = int(seat) - 65; // converts char seat into the ASCII value of the char, then subtracts from the ASCII value of A to find the distance from column spot 0
   int counter = 0; // count how many available seats
   bool found = false; // if starting seat is found
   if(total_quantity > totalSeats) // if the total tickets exceeds the total seats in the row, return false
   {
      return false; // unable to reserve
   }
   Node<Seat*>*r = theater.getfirst(); // Node ptr that points to first seat node in auditorium
   Node<Seat*>*numCheck = nullptr; // pointer that will be used in a loop to check if there are enough seats after starting seat
   int k = 0; // loop iterator to position correct row of user wanting to reserve
   while(k < row-1) // positions at correct row
   {
      r = r->getdown(); // move pointer down
      k++; // increments iterator
   }
   for(int i = 0; i < totalSeats; i++) // finds where starting seat is at
   {
      if(r->getpayload()->getSeat() == seat) // if seat located then break out of loop
      {
         found = true; // starting seat found
         break; // break out of loop
      }
      if(i != totalSeats - 1) // if not last seat in row
      {
         r = r->getright(); // move pointer to right
      }

   }
   if(found) // if starting seat is found
   {
      numCheck = r; // points numCheck to location of starting seat object
      for(int d = col; d < totalSeats; d++) // makes sure there are enough seats after the starting seat for total tickets
      {
         if(numCheck->getpayload()->getTT() == '.') // if seat is empty
         {
            counter++; // increase counter
         }
         if(numCheck->getright() != 0) // if not last seat in row
         {
            numCheck = numCheck->getright(); // move pointer to right
         }

      }
      if(counter < total_quantity) // if there are not enough empty seats after starting seat
      {
         return false; // then unable to reserve requested seats
      }
      if(r->getpayload()->getTT() == '.') // checks if starting seat is reserved or not
      {
         for(int c = 0; c < total_quantity; c++) // loops through each seats after starting seat
         {
            if(r->getpayload()->getTT() != '.') // if one of them not empty
            {
               return false; // unable to reserve seats requested
            }
            if(r->getright() != 0) // if not last seat in row
            {
               r = r->getright(); // move pointer to the right
            }
         }
         return true; // able to reserve seats
      }

   }

   return false; // if not enough seats available return false

}

void writeFile(Auditorium& theater, int totalRows, int totalSeats, string outputfile) // function to write auditorium into file
{
   ofstream o; // output filestream
   o.open(outputfile); // open A1.txt output file
   if(!o.is_open()) // if unable to open file
   {
      cout << "unable to open output file" << endl; // print out unable to open file
   }
   Node<Seat*>*n = theater.getfirst(); // pointer that points to first node in auditorium
   int a = 0; // a loop iterator
   int b = 0; // b loop iterator
   int c = 0; // c loop iterator

   while(c < totalRows) // loop through each row in auditorium
   {
      if(c != 0) // if not first row
      {
         a = 0; // set a iterator to 0
         n = theater.getfirst(); // sets pointer to head node
         while(a < c) // loop until reach current row
         {
            if(n->getdown() != 0) // if bottom row exists
            {
                n = n->getdown(); // move pointer down
            }
            a++; // increment a iterator by 1
         }
      }

      b = 0; // set b iterator to 0
      while(b < totalSeats) // for every seat in auditorium
      {
         o << n->getpayload()->getTT(); // outputs seat into file
         if(b != totalSeats-1) // if not last seat in row
         {
             n = n->getright(); // move pointer to right node
         }

         b++; // increment b loop iterator by 1

      }
      c++; // increment c loop iterator by 1
      o << endl; // move to next line in file
   }
   o.close(); // close output file
}

/** Sort Ticket Vector **/
void sortTickets(vector<Ticket>& x) // Sorts the tickets in the ticket vectors for Adult, Child and Senior
{
   for(long long unsigned int z = 1; z < x.size(); z++) // loop through the vector
   {
      if(x.at(z).row < x.at(z-1).row) // if the row of the ticket that is before the current ticket is larger than the current ticket row
      {
         Ticket s(x.at(z).row, x.at(z).column); // sets item to temporary variable
         x.erase(x.begin() + z); // removes item not in order
         for(long long unsigned int m = 0; m < z; m ++) // loops through each each element in list before index of item checked and inserts item to appropriate place in list
         {
            if(x.at(m).row > s.row) // if the current Ticket's row is greater than the ticket row to be inserted
            {
               x.insert(x.begin()+ m, s); // insert it at that location
               break;
            }
            else if(x.at(m).row == s.row && x.at(m).column > s.column) // if they have the same row, but different seat letters where the current seat letter is greater than the inserted ticket seat letter
            {
               x.insert(x.begin()+ m, s); // insert the ticket at that spot
               break;
            }
         }

      }
      else if(x.at(z).row == x.at(z-1).row) // if the rows for the current and previous ticket is the same
      {
         if(x.at(z).column < x.at(z-1).column) // compare the columns to see if the column of the previous ticket is seat to right of current seat
         {
            Ticket s(x.at(z).row, x.at(z).column); // sets item to temporary variable
            x.erase(x.begin() + z); // removes item not in order
            for(long long unsigned int m = 0; m < z; m ++) // loops through each each element in list before index of item checked and inserts item to appropriate place in list
            {
               if((x.at(m).row == s.row) && (x.at(m).column > s.column)) // if the tickets are at the same row but the current ticket's seat letter is greater than the inserted ticket's seat letter
               {
                  x.insert(x.begin()+ m, s); // insert the ticket at that spot
                  break;
               }
               else if(x.at(m).row > s.row) // if the row of the current ticket is greater than the inserted ticket's row
               {
                  x.insert(x.begin()+ m, s); // insert the ticket at that spot
                  break;
               }
            }
         }
      }

   }

}


/** Print Report **/
void printReport(Auditorium& theater1, int totalRows1, int totalSeats1) // prints out the report for total sales/tickets sold etc.
{
   int totalOpen = 0; // variable to store total opens seats
   int totalReserved = 0; // variable to store total reserved seats
   int totalAdult = 0; // variable to store total reserved adult seats
   int totalChild = 0; // variable to store total reserved child seats
   int totalSenior = 0; // variable to store total reserved senior seats
   double totalAmountAll = 0.00; // variable to store total money made from all three auditoriums

   int open = 0; // variable to store total opens seats of auditorium
   int reserved = 0; // variable to store total reserved seats of auditorium
   int Adult_Sold = 0; // variable to store total reserved adult seats of auditorium
   int Child_Sold = 0;// variable to store total reserved child seats of auditorium
   int Senior_Sold = 0; // variable to store total reserved senior seats of auditorium
   double totalAmount = 0.00; // variable to store total money made from auditorium

   int c = 0; // loop iterator
   int b = 0; // loop iterator
   int a = 0; // loop iterator
   Node<Seat*>*n = theater1.getfirst(); // pointer to point to current seat being tracked

   // print report for Theater1
   while(c < totalRows1) // loops through every row in auditorium
   {
      if(c != 0) // if not first row
      {
         a = 0; // reset a loop iterator to 0
         n = theater1.getfirst(); // set pointer to point to head node
         while(a < c) // loops until current row is reached
         {
            if(n->getdown() != 0) // if there exists a bottom row; != nullptr instead of 0
            {
                n = n->getdown(); // move pointer down a row
            }
            a++; // increment a iterator
         }
      }

      b = 0; // reset b loop iterator to 0
      while(b < totalSeats1-1)
      {
         if(n->getpayload()->getTT() == 'A') // checks if seat is reserved by an adult
         {
            Adult_Sold += 1; // add 1 to adult tickets sold variable
            reserved += 1; // add 1 to total seats
         }
         else if(n->getpayload()->getTT() == 'C') // checks if seat is reserved by an child
         {
            Child_Sold += 1; // add 1 to child tickets sold variable
            reserved += 1; // add 1 to total seats
         }
         else if(n->getpayload()->getTT() == 'S') // checks if seat is reserved by an senior
         {
            Senior_Sold += 1; // add 1 to senior tickets sold variable
            reserved += 1; // add 1 to total seats
         }
         else if(n->getpayload()->getTT() == '.') // checks if seat is empty
         {
            open += 1; // add 1 to total seats
         }

         if(b != totalSeats1-1) // if not last seat in row
         {
             n = n->getright(); // move pointer to right
         }

         b++; // increase b loop iterator by 1

      }
      c++; // increase c loop iterator by 1

   }

   totalAmount = 10.00*Adult_Sold + 5.00*Child_Sold + 7.50*Senior_Sold; // calculates the current theater's total money made

   totalOpen += open; // adds the current theater's total open seats to the total open seats of all three auditorium
   totalReserved += reserved; // adds the current theater's total open seats to the total open seats of all three auditorium
   totalAdult += Adult_Sold; // adds the current theater's total reserved adult seats to the total reserved adult seats of all three auditorium
   totalChild += Child_Sold;// adds the current theater's total reserved child seats to the total reserved child seats of all three auditorium
   totalSenior += Senior_Sold; // adds the current theater's total reserved senior seats to the total reserved senior seats of all three auditorium
   totalAmountAll += totalAmount; // adds the current theater's total money made to the total money made from all three auditorium

   // Display Report for Auditorium 1
   cout << '\n' <<"• Total Seats :" <<open << '\n' <<"• Total Tickets: "<< reserved << '\n' <<"• Adult Tickets: "<< Adult_Sold << '\n' <<"• Child Tickets: "<< Child_Sold << '\n' << "• Senior Tickets: "<<Senior_Sold << '\n' << "• Total Sales: $" << fixed << setprecision(2) << totalAmount << endl;
  


}

int main()
{
   ifstream ifs; // input file stream
  //  unordered_m/ap<string, User> userMap; // hashmap that stores all the users
   string line = " "; // variable to store the line that is being read from the file
   string username = " "; // variable to store read in username
   string password = " "; // variable to store read in password
   int totalinputpass; // variable to store total attempts
   string menuoption = " "; // variable to store the menu option user inputs

   ofstream ofs; // outputfilestream
   string filename = " "; // variable to store auditorium user input filename
   int rowNum = 0; // row number of user input
   string strrowNum = " "; // user input rowNum in string form
   char startingSeat = ' '; // user input starting seat letter
   string startingSeatstr = " ";
   int numA = 0; // variable to store total requested adult tickets
   int numC = 0; // variable to store total requested child tickets
   int numS = 0; // variable to store total requested senior tickets
   int totalRows = 0; // variable to store totalRows
   int totalSeats = 0; // variable to store totalSeats

   string MainMenuSelect = " "; // Variable for which choice the user chooses (1) reserve seats (2) exit
   int totalTickets = 0; // Variable for total tickets user wants to reserve
   int startingSeatcol = -1; // the index of the starting seat char the user inputs
   int ssNum = 0; // starting seat number variable
   string promptYN = " "; // variable for response Y/N reserve best available seats
   string strnumA = " "; // string version of adult tickets requested by user
   string strnumC = " "; // string version of child tickets requested by user
   string strnumS = " "; // string version of senior tickets requested by user

   Auditorium *theater = nullptr; // ptr to point to current auditorium that is being used
   int auditoriumNumber = 0; // current auditorium number that is being used

   int adultcounter = 0; // variable to store the number of adult tickets
   int childcounter = 0; // variable to store the number of child tickets
   int seniorcounter = 0; // variable to store the number of senior tickets

   // Create Auditoriums
   Auditorium Auditorium1("A1.txt", cnt_rows("A1.txt")); // creates auditorium 1 from the auditorium 1 file

   // STARTING POINT

   while(true) // Customer main menu
         {
            while(true) // Prompt for main menu option
            {
               menuoption = ' '; // resets menu option variable
               cout << "1. Reserve Seats" << endl << "2.Exit" << endl; // prompt customer menu option
               cin >> menuoption; // prompt customer menu option
               if(menuoption == "1" || menuoption == "2") // if input is valid
               {
                  break; // break
               }
            }
            if(menuoption == "1") // Reserve Seats
            {
               string reservationtheateroption = " "; // variable that stores the option user chose for which theater to reserve in
               ///DISPLAY THEATER
                  theater = &Auditorium1; // set the theater ptr to point to auditorium 1
                  totalRows = cnt_rows("A1.txt"); // set the total rows for auditorium 1
                  totalSeats = cnt_seats("A1.txt"); // set the total seats for auditorium 1
                  auditoriumNumber = 1; // set auditoriumNumber variable to 1

               /// RESERVATION HERE!
               totalTickets = 0; // resets total tickets number to 0
               displayAuditorium(*theater, totalRows, totalSeats); // calls function to display theater
               // pointer to head node

              //  std::cout<<"here"<<endl;
               //Prompts for row
               while(true) // loops until valid row number is inputted
               {
                  strrowNum = " ";
                  rowNum = 0; // resets the row number value
                  cout << "Row number: " << endl; // prompts row number
                  cin >> strrowNum; // prompts row number
                  // Validate Row
                  if(isdigit(strrowNum.at(0))) // if input is a digit
                  {
                     rowNum = stoi(strrowNum); //converts input to integer
                     if(rowNum <= totalRows && rowNum > 0) // checks if row number is within the auditorium, if so, break out of loop
                     {
                        break; // break out of loop
                     }
                  }
               }
               while(true) // loops until valid seat letter is inputted
               {
                  startingSeatstr = " ";
                  startingSeat = ' '; // sets starting seat variable to empty char
                  // Prompting Starting Seat
                  cout << "Starting Seat: " << endl; // prompts starting seat letter
                  cin >> startingSeatstr; // prompts user for starting seat letter

                  if(startingSeatstr.length()  == 1)
                  {
                     // Validate Seat
                     startingSeat = startingSeatstr.at(0);
                     startingSeatcol = int(toupper(startingSeat)) - 65; // My thought - this variable compares the ASCII value of the inputted startingSeat to the capital A ASCII value and subtracts them to get the index of the column that the user inputted
                     // This if statement checks if the startingSeat user input is larger or smaller than the number of seats/columns in the auditorium
                     if(startingSeatcol >= 0 && startingSeatcol < totalSeats) // if starting seat is within bounds of thater
                     {
                        break; // break out of loop
                     }

                  }

               }

               while(true)  // loops until valid adult tickets number is inputted
               {
                  strnumA = " "; // sets total number of inputted adult ticket variable to empty string
                  numA = 0; // resets number of adult tickets
                  // Prompt for number of adult tickets
                  cout << "Number of adult tickets: " << endl; // prompts number of requested adult tickets
                  cin >> strnumA; // prompts number of requested adult tickets
                  // Validate ticket number
                  if(isNumber(strnumA)) // if input is a number
                  {
                     numA = stoi(strnumA); // convert string to integer
                     if(numA >= 0 && numA <= totalSeats) // checks if number of adult tickets is not negative
                     {
                        break; // break out of loop

                     }
                  }

               }
               totalTickets += numA; // add total adult tickets requested to total tickets
               while(true)  // loops until valid child number is inputted
               {
                  strnumC = " "; // sets total number of inputted child ticket variable to empty string
                  numC = 0; // resets number of child tickets
                  // Prompt for number of child tickets
                  cout << "Number of child tickets: " << endl; // prompts number of requested child tickets
                  cin >> strnumC; // prompts number of requested child tickets
                  // Validate ticket number
                  if(isNumber(strnumC)) // if input is a number
                  {
                     numC = stoi(strnumC); // convert string to integer
                     if(numC >= 0 && (numC + totalTickets) <= totalSeats) // checks if number of child tickets is not negative
                     {
                        break; // break out loop
                     }
                  }
               }
               totalTickets += numC; // add total child tickets requested to total ticket
               while(true) // loops until valid senior number is inputted
               {
                  strnumS = " "; // sets total number of inputted senior ticket variable to empty string
                  numS = 0;// resets number of senior tickets
                  // Prompt for number of senior tickets
                  cout << "Number of senior tickets: "<<endl; // prompts number of requested senior tickets
                  cin >> strnumS; // prompts number of requested senior tickets
                  // Validate ticket number
                  if(isNumber(strnumS)) // if input is a number
                  {
                     numS = stoi(strnumS); // convert string to integer
                     if(numS >= 0 && (numS + totalTickets) <= totalSeats)// checks if number of senior tickets is not negative
                     {
                        break; // break out loop
                     }
                  }

               }
               totalTickets += numS; // add total senior tickets requested to total ticket
               // Checks if seats are available, if so then reserve the seats, else, call bestAvailable() and if possible ask user if they would like the best available seats
               bool check=checkAvailability(*theater, rowNum,startingSeat,totalTickets, totalSeats);
              //  cout<<check<<endl;   
              if(check) // checks if seats requested are available
               {
                  // vector<Order>* userOrders = &(userMap.find(username)->second.getOrders()); // gets the orders vector
                  adultcounter = numA; // set total number of requested adult tickets to adult counter
                  childcounter = numC; // set total number of requested child tickets to child counter
                  seniorcounter = numS; // set total number of requested senior tickets to senior counter

                  // userOrders->push_back(Order(numA, numC, numS, auditoriumNumber)); //  add the new order to userOrders vector
                  for(int h = 0; h < totalTickets; h++) // loop from 0 to totaltickets
                  {
                     if(adultcounter > 0) // if there is still adult tickets that have not been reserved
                     {
                        // userOrders->at(userOrders->size() - 1).adultList.push_back(Ticket(rowNum, char(int(startingSeat) + h))); // reserve the seat and add it to adult vector
                        adultcounter--; // decrement adult counter
                     }
                     else if(childcounter > 0) // if there is still child tickets that have not been reserved
                     {
                        // userOrders->at(userOrders->size() - 1).childList.push_back(Ticket(rowNum, char(int(startingSeat) + h))); // reserve the seat and add it to child vector
                        childcounter--; // decrement child counter
                     }
                     else if(seniorcounter > 0) // if there is still senior tickets that have not been reserved
                     {
                        // userOrders->at(userOrders->size() - 1).seniorList.push_back(Ticket(rowNum, char(int(startingSeat) + h))); // reserve the seat and add it to senior vector
                        seniorcounter--; // decrement senior counter
                     }
                  }

                  reserveSeats(*theater, rowNum,startingSeat,numA,numS,numC, totalSeats); // if available, reserve those seats
               }
               else // if unable to reserve requested seats
               {
                  ssNum = bestAvailable(*theater, rowNum, totalTickets, totalRows, totalSeats); // calls the bestAvailable function to find best available seats
                  if(ssNum != -1) // checks if there are seats available
                  {
                     if(totalTickets > 1) // if the total tickets requested is greater than 1, print a range
                     {
                        cout << rowNum << char(ssNum + 65) << " - " << rowNum << char(ssNum + 65 - 1 + totalTickets) << endl; //  the char(ssNum + 65) converts the starting seat number to the letter of the seat; same thing with char(ssNum + 65 + total_tickets - 1) which is the end of range of the best available seats; -1 so not to reserve an extra seat since the starting seat is included already
                     }
                     else if(totalTickets == 1) // if the total tickets requested is 1, return a row and letter seat for best available
                     {
                        cout << rowNum << char(ssNum + 65) << endl; // prints out single best available seat
                     }
                     cout << "Reserve Seats? Y/N" << endl; // prompts user to reserve or not reserve seats
                     cin >> promptYN; // prompts user to reserve/not reserve the seats
                     if(promptYN.length() == 1 && promptYN == "Y") // if they reserve the seats
                     {
                        // vector<Order>* userOrders = &(userMap.find(username)->second.getOrders()); // gets the orders vector
                        adultcounter = numA; // set total number of requested adult tickets to adult counter
                        childcounter = numC; // set total number of requested child tickets to child counter
                        seniorcounter = numS; // set total number of requested senior tickets to senior counter

                        // userOrders->push_back(Order(numA, numC, numS, auditoriumNumber)); // add an order to user order vector

                        cout << "Reservation Successful!" << endl; // confirmation message

                        reserveSeats(*theater, rowNum,char(ssNum + 65),numA,numS,numC, totalSeats); // reserves best available seats

                     }
                  }
                  else // else, then no available seats
                  {
                     cout << "no seats available" << endl; // if no best seats available, print this statement
                  }
               }
               
               printReport(Auditorium1, cnt_rows("A1.txt"), cnt_seats("A1.txt"));
               theater = &Auditorium1; // set the theater ptr to point to auditorium 1
              //  displayAuditorium(Auditorium1, cnt_rows("A1.txt"),cnt_seats("A1.txt"));
               writeFile(*theater, cnt_rows("A1.txt"), cnt_seats("A1.txt"), "A1Final.txt"); 

            }else{
              break;
            }
         }


   return 0;
}
