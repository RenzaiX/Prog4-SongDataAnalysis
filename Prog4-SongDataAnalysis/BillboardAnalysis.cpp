/* ---------------------------------------------
Program 4: Billboard Analysis / *

Course: CS 141, Spring 2022. Tues 11am lab
System: Windows using Visual Studio Code
Author: Mykola Turchak & Rishi Shah
---------------------------------------------
*/

#include <iostream>  // For menu and Output
#include <fstream>   // For file menuut and output
#include <vector>    // menuut file is stored in a vector
#include <cctype>    // Allows using the tolower() function
#include <sstream>   // Allows performing insertion, extraction, and other operations.
#include <algorithm> // defines functions for searching, sorting, counting, manipulating

using namespace std; // So that we don't need to preface cin and cout with std::


// This function displays the menu options for choosing a file.
void displayWelcomeMessage()
{
  cout << "Select file option:" << endl;
  cout << "   1. To analyze charts top 50: 1960 - 1980 data file" << endl;
  cout << "   2. To analyze charts top 50: 1981 - 2000 data file" << endl;
  cout << "   3. To analyze charts top 50: 2001 - 2020 data file" << endl;
  cout << "Your choice --> ";
}

// This function displays the Sub Menu options after selecting a file.
void subMenu()
{
  cout
      << "Select a menu option: \n"
      << "   1. Display overall information about the data\n"
      << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year\n"
      << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year\n"
      << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year\n"
      << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search\n"
      << "   6. Exit\n"
      << "Your choice --> ";
}

// This is a class of songs which represents each row in the CSV File
class Song
{
  // Declaring variables that represent the header row in the CSV File
public:
  int year;
  string date;
  int rank;
  string songName;
  string artistName;
  int lastWeek;
  int peakRank;
  int WeeksOnBoard;
  // Initializing a Constructor which takes a vector of strings
  Song(vector<string> row)
  {
    // Parsing the data from string to Integer
    int yearParsed = stoi(row[0].substr(row[0].size() - 4, 4));
    int lastWeekParsed = stoi(row[4]);
    int peakRandkParsed = stoi(row[5]);
    int weakBoardParsed = stoi(row[6]);
    // Assigning each variable to the corresponding column of data in the CSV File
    this->rank = stoi(row[1]);
    this->date = row[0];
    this->year = yearParsed;
    this->songName = row[2];
    this->artistName = row[3];
    this->lastWeek = lastWeekParsed;
    this->peakRank = peakRandkParsed;
    this->WeeksOnBoard = weakBoardParsed;
  }
}; // end of class

/* This function reads the CSV File and takes the filename as an argument
 * and returns a vector which is an instance of the Song class.
 * Source: https://java2blog.com/read-csv-file-in-cpp/
 */
vector<Song> readLine(string fname)
{
  // Create a vector of the Song class
  vector<Song> content;
  vector<string> row;
  string line, word;
  int i = 0;

  fstream file(fname, ios::in);
  if (file.is_open())
  {

    while (getline(file, line))
    {
      if (i == 0)
      {
        i++;
        continue;
      }
      row.clear();

      stringstream str(line);
      // Seperates each word by a comma (',')
      while (getline(str, word, ','))
      {
        // If the data is missing, put a placeholder of -1
        if (word == "")
        {
          row.push_back("-1");
        }
        else
        {
          row.push_back(word);
        }
      }
      // Creating an object of the Song class.
      Song newEntry = Song(row);
      content.push_back(newEntry);
    }
  }
  return content;
}

// Checks if the letter is either 'D' or 'Y', else asks user to re-enter the letter
char InputLetterCheck(char upperCaseMenu)
{
  char menu;

  // loop runs until letter 'D' or 'Y' is entered
  while (upperCaseMenu != 'D' && upperCaseMenu != 'Y')
  {
    cout << "Invalid entry. Try again.\n";
    cout << "Enter D to select a decade or Y to select a year.\n"
         << "Your choice --> ";
    cin >> menu;
    upperCaseMenu = toupper(menu);

    // if one of the letters is found, break out of the loop
    if (upperCaseMenu == 'D' || upperCaseMenu == 'Y')
    {
      break;
    }
  }

  // return the acceptable letter entered by user
  return upperCaseMenu;
}

// Check if date entered by user is within minYear and maxYear and return boolean value according to it
bool checkYear(int dateInput, int maxYear, int minYear)
{
  // if not within limits, print the statement and return false
  if (dateInput > maxYear || dateInput < minYear)
  {
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen. \n";
    return false;
  }

  // if withing limits return true
  return true;
}

int main()
{
  // Program 4 description
  cout << "Program 4: BillBoard Analysis " << endl;
  cout << "CS 141, Spring 2022, UIC " << endl;
  cout << " " << endl;
  cout << "This program will analyze weekly Billboard data spanning from 1960 - 2020." << endl;
  cout << endl;

  // Displays menu options
  displayWelcomeMessage();

  // Creating a vector of Song and getting input
  vector<Song> fname;
  int maxYear;
  int minYear;

  int menu = 0;
  cin >> menu;
  cout << endl;
  bool isrunning = true; // Boolean variable for checking the condition of while loop

  // Assigning the file name and year limiter based on user input
  if (menu == 1)
  {
    fname = readLine("charts_top50_1960_1980.csv");
    maxYear = 1980;
    minYear = 1960;
  }
  else if (menu == 2)
  {
    fname = readLine("charts_top50_1981_2000.csv");
    maxYear = 2000;
    minYear = 1980;
  }
  else if (menu == 3)
  {
    fname = readLine("charts_top50_2001_2020.csv");
    maxYear = 2020;
    minYear = 2000;
  }
  else
  {
    cout << "Invalid value. Exiting Program.";
    exit(0);
  }

  cout << endl;

  // While loop contains the code for the 6 menu options
  while (isrunning)
  {

    // Displays the Sub Menu and takes user input for menu options (1-6)
    subMenu();
    int subMenu = 0;
    cin >> subMenu;

    // Menu Option 1
    if (subMenu == 1)
    {
      vector<string> songs;

      // Loop through the entire data, find all the unique songs and store them
      for (int i = 0; i < fname.size(); i++)
      {
        if (find(songs.begin(), songs.end(), fname.at(i).songName) == songs.end())
        {
          songs.push_back(fname.at(i).songName);
        }
      }

      // print total number of rows and unique songs in the dataset
      cout << "Total number of rows: " << fname.size() << endl;
      cout << "Number of unique songs represented in the dataset: " << songs.size() << endl;
      continue;
    }

    // Menu Option 2
    else if (subMenu == 2)
    {
      vector<string> songVector;
      vector<string> artistsVector;
      char menu;
      int dateInput;

      // Take user input for decade or year using InputLetterCheck() function
      cout << "Enter D to select a decade or Y to select a year.\n"
           << "Your choice --> ";

      cin >> menu;
      char upperCaseMenu = toupper(menu);
      upperCaseMenu = InputLetterCheck(upperCaseMenu);

      if (upperCaseMenu == 'D')
      {
        // Prompt the user to enter a decade
        cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010).\n";
        cin >> dateInput;
        int yearsOverDecade = dateInput % 10;
        dateInput -= yearsOverDecade;

        // Checks if the user input is within a specific range
        if (checkYear(dateInput, maxYear, minYear) == false)
        {
          continue;
        }

        // Loop through the Dataset and obtain songs/artists within the decade if the rank is #1
        for (int i = 0; i < 10; i++)
        {
          for (int j = 0; j < fname.size(); j++)
          {
            if (dateInput == fname.at(j).year && fname.at(j).rank == 1)
            {
              songVector.push_back(fname.at(j).songName);
              artistsVector.push_back(fname.at(j).artistName);
            }
          }
          dateInput++;
        }

        vector<int> maxCount;
        vector<string> topSong;
        vector<string> artist;
        int count;

        // Nested for loop to count the number of times these songs appeared in #1 spot
        for (int i = 0; i < songVector.size(); i++)
        {
          count = 0;

          for (int j = 0; j < songVector.size(); j++)
          {
            // if song matches, update the count
            if (songVector[i] == songVector[j])
            {
              count++;
            }
          }

          // Determine the song(s) with the highest number of occurences. If count is greater that count of previous song, we update the information
          if (maxCount.size() == 0 || maxCount[0] < count)
          {
            maxCount.clear();
            topSong.clear();
            artist.clear();
            maxCount.push_back(count);
            topSong.push_back(songVector[i]);
            artist.push_back(artistsVector[i]);
          }

          // if two songs have same count, we add that song to the list
          else if (maxCount[0] == count && artist[0] != artistsVector[i])
          {
            if (artist[1] != artistsVector[i])
            {
              maxCount.push_back(count);
              topSong.push_back(songVector[i]);
              artist.push_back(artistsVector[i]);
            }
          }
        }

        // Prints the song(s) with highest number of occurences and artist name
        cout << "\n\nThe song(s) with the most #1 occurrences for selected time period is: \n";

        for (int k = maxCount.size() - 1; k >= 0; k--)
        {
          cout

              << "        Song Title: " << topSong[k] << endl
              << "        Artist: " << artist[k] << endl
              << "        # of occurrences: " << maxCount[k] << endl;
        }

        continue;
      }

      else if (upperCaseMenu == 'Y')
      {
        // Prompt the user to enter an Year
        cout << "Enter the year you would like to choose (e.g. 2001).\n";

        cin >> dateInput;

        // Checks if the user input is within a specific range
        if (checkYear(dateInput, maxYear, minYear) == false)
        {
          continue;
        }

        // Loop through the Dataset and obtain songs/artists within the year if the rank is #1
        for (int j = 0; j < fname.size(); j++)
        {

          if (dateInput == fname.at(j).year && fname.at(j).rank == 1)
          {

            songVector.push_back(fname.at(j).songName);
            artistsVector.push_back(fname.at(j).artistName);
          }
        }

        vector<int> maxCount;
        vector<string> topSong;
        vector<string> artist;
        int count;

        // Nested for loop to count the number of times these songs appeared in #1 spot
        for (int i = 0; i < songVector.size(); i++)
        {
          count = 0;

          for (int j = i; j < songVector.size(); j++)
          {
            // increment if songs match
            if (songVector[i] == songVector[j])
            {
              count++;
            }
          }

          // Determine the song(s) with the highest number of occurences. If count is greater that count of previous song, we update the information
          if (maxCount.size() == 0 || maxCount[0] < count)
          {
            maxCount.clear();
            topSong.clear();
            artist.clear();
            maxCount.push_back(count);
            topSong.push_back(songVector[i]);
            artist.push_back(artistsVector[i]);
          }

          // if two songs have same count, we add that song to the list
          else if (maxCount[0] == count && artist[0] != artistsVector[i])
          {
            if (artist[1] != artistsVector[i])
            {
              maxCount.push_back(count);
              topSong.push_back(songVector[i]);
              artist.push_back(artistsVector[i]);
            }
          }
        }

        // Prints the song(s) with highest number of occurences and artist name
        cout << "\n\nThe song(s) with the most #1 occurrences for selected time period is: \n";

        for (int k = 0; k < maxCount.size(); k++)
        {
          cout
              << "        Song Title: " << topSong[k] << endl
              << "        Artist: " << artist[k] << endl
              << "        # of occurrences: " << maxCount[k] << "\n\n\n";
        }
      }
    }

    // Menu Option 3
    else if (subMenu == 3)
    {

      int weekOnBoardVector = 0;
      string songVector;
      string artistsVector;
      char menu;
      int dateInput;
      // Take user input and validate it using the InputLetterCheck() function
      cout << "Enter D to select a decade or Y to select a year.\n"
           << "Your choice --> ";
      cin >> menu;
      char upperCaseMenu = toupper(menu);

      upperCaseMenu = InputLetterCheck(upperCaseMenu);

      if (upperCaseMenu == 'D')
      {
        cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010).\n";

        cin >> dateInput;
        int yearsOverDecade = dateInput % 10;
        dateInput -= yearsOverDecade;

        // Checks if the user input is within a specific range
        if (checkYear(dateInput, maxYear, minYear) == false)
        {
          continue;
        }
        /* Loop through the dataset and acquire the song name, weeks on board,
           and the artist name in the given period of time and weeks on board is highest*/
        for (int i = 0; i < 10; i++)
        {
          for (int j = 0; j < fname.size(); j++)
          {
            if (dateInput == fname.at(j).year && weekOnBoardVector <= fname.at(j).WeeksOnBoard)
            {
              songVector = fname.at(j).songName;
              weekOnBoardVector = fname.at(j).WeeksOnBoard;
              artistsVector = fname.at(j).artistName;
            }
          }
          dateInput++;
        }

        // print the information in the required format
        cout
            << "The song with the highest number of weeks on the charts is:  \n"
            << "        " << songVector << " by " << artistsVector << " with " << weekOnBoardVector << " weeks on the chart.\n";
      }

      else if (upperCaseMenu == 'Y')
      {
        cout << "Enter the year you would like to choose (e.g. 2001).\n";

        cin >> dateInput;

        // Checks if the user input is within a specific range
        if (checkYear(dateInput, maxYear, minYear) == false)
        {
          continue;
        }

        /* Loop through the dataset and acquire the song name, weeks on board,
           and the artist name in the given period of time and weeks on board is highest*/
        for (int j = 0; j < fname.size(); j++)
        {
          if (dateInput == fname.at(j).year && weekOnBoardVector <= fname.at(j).WeeksOnBoard)
          {
            songVector = fname.at(j).songName;
            weekOnBoardVector = fname.at(j).WeeksOnBoard;
            artistsVector = fname.at(j).artistName;
          }
        }

        // print the information in the required format
        cout
            << "The song with the highest number of weeks on the charts is:  \n"
            << "        " << songVector << " by " << artistsVector << " with " << weekOnBoardVector << " weeks on the chart.\n";
      }

      // print error message if invalid entry
      else
      {
        cout << "Invalid entry. Try again.\n";
      }
    }

    else if (subMenu == 4)
    {
      {
        vector<int> lastWeekVector;
        vector<string> songVector;
        vector<string> artistsVector;
        vector<int> rankVector;
        vector<string> dateVector;
        vector<int> differenceVector;

        char menu;
        int dateInput;
        // Take user input and validate it using the InputLetterCheck() function
        cout << "Enter D to select a decade or Y to select a year.\n"
             << "Your choice --> ";
        cin >> menu;
        char upperCaseMenu = toupper(menu);

        upperCaseMenu = InputLetterCheck(upperCaseMenu);

        if (upperCaseMenu == 'D')
        {
          // Take input for the decade
          cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010).\n";
          cin >> dateInput;
          int yearsOverDecade = dateInput % 10;
          dateInput -= yearsOverDecade;

          // Checks if the user input is within a specific range
          if (checkYear(dateInput, maxYear, minYear) == false)
          {
            continue;
          }
          // Loop through the dataset and acquire the song, last week, artist, rank, date, and difference in rank
          for (int i = 0; i < 10; i++)
          {
            for (int j = 0; j < fname.size(); j++)
            {
              if (dateInput == fname.at(j).year)
              {
                songVector.push_back(fname.at(j).songName);
                lastWeekVector.push_back(fname.at(j).lastWeek);
                artistsVector.push_back(fname.at(j).artistName);
                rankVector.push_back(fname.at(j).rank);
                dateVector.push_back(fname.at(j).date);
                differenceVector.push_back((fname.at(j).lastWeek) - (fname.at(j).rank)); // formula for calclating the highest weekly climb
              }
            }
            dateInput++;
          }

          vector<int> maxCount;
          vector<string> topSong;
          vector<string> artist;
          vector<string> date;
          vector<int> rank;
          vector<int> lastWeek;
          vector<int> difference;

          // Determine which song has the greatest weekly climb. If count is greater that count of previous song, we update the information
          for (int i = 0; i < songVector.size(); i++)
          {

            if (maxCount.size() == 0 || maxCount[0] < differenceVector[i])
            {
              maxCount.clear();
              topSong.clear();
              artist.clear();
              date.clear();
              rank.clear();
              lastWeek.clear();
              difference.clear();

              maxCount.push_back(differenceVector[i]);
              topSong.push_back(songVector[i]);
              artist.push_back(artistsVector[i]);
              date.push_back(dateVector[i]);
              rank.push_back(rankVector[i]);
              lastWeek.push_back(lastWeekVector[i]);
              difference.push_back(differenceVector[i]);
            }

            // if two songs have same count, we add that song to the list
            else if (maxCount[0] == differenceVector[i] && artist[0] != artistsVector[i])
            {
              if (artist[1] != artistsVector[i])
              {
                maxCount.push_back(differenceVector[i]);
                topSong.push_back(songVector[i]);
                artist.push_back(artistsVector[i]);
                date.push_back(dateVector[i]);
                rank.push_back(rankVector[i]);
                lastWeek.push_back(lastWeekVector[i]);
                difference.push_back(differenceVector[i]);
              }
            }
          }

          // Prints the song(s) with highest weekly climb and other information about the song(s)
          cout << "The song(s) with the greatest climb from previous week to current week position:  " << endl;
          for (int k = maxCount.size() - 1; k >= 0; k--)
          {
            cout
                << "        Song Title: " << topSong[k] << endl
                << "         Artist: " << artist[k] << endl
                << "         Week of: " << date[k] << endl
                << "         Previous Week Position: " << lastWeek[k] << endl
                << "         Current Week Position: " << rank[k] << endl
                << "         Difference of " << difference[k] << " between previous week and current week position \n\n";
          }
        }

        else if (upperCaseMenu == 'Y')
        {
          // Prompt the user to enter an Year
          cout << "Enter the year you would like to choose (e.g. 2001).\n";

          cin >> dateInput;

          // Checks if the user input is within a specific range
          if (checkYear(dateInput, maxYear, minYear) == false)
          {
            continue;
          }
          // Loop through the Dataset and obtain songs/artists within the entered year
          for (int j = 0; j < fname.size(); j++)
          {

            if (dateInput == fname.at(j).year)
            {
              songVector.push_back(fname.at(j).songName);
              lastWeekVector.push_back(fname.at(j).lastWeek);
              artistsVector.push_back(fname.at(j).artistName);
              rankVector.push_back(fname.at(j).rank);
              dateVector.push_back(fname.at(j).date);
              differenceVector.push_back((fname.at(j).lastWeek) - (fname.at(j).rank));
            }
          }

          vector<int> maxCount;
          vector<string> topSong;
          vector<string> artist;
          vector<string> date;
          vector<int> rank;
          vector<int> lastWeek;
          vector<int> difference;

          for (int i = 0; i < songVector.size(); i++)
          {
            // Determine which song has the greatest weekly climb. If count is greater that count of previous song, we update the information
            if (maxCount.size() == 0 || maxCount[0] < differenceVector[i])
            {
              maxCount.clear();
              topSong.clear();
              artist.clear();
              date.clear();
              rank.clear();
              lastWeek.clear();
              difference.clear();

              maxCount.push_back(differenceVector[i]);
              topSong.push_back(songVector[i]);
              artist.push_back(artistsVector[i]);
              date.push_back(dateVector[i]);
              rank.push_back(rankVector[i]);
              lastWeek.push_back(lastWeekVector[i]);
              difference.push_back(differenceVector[i]);
            }

            // if two songs have same count, we add that song to the list
            else if (maxCount[0] == differenceVector[i] && artist[0] != artistsVector[i])
            {
              if (artist[1] != artistsVector[i])
              {
                maxCount.push_back(differenceVector[i]);
                topSong.push_back(songVector[i]);
                artist.push_back(artistsVector[i]);
                date.push_back(dateVector[i]);
                rank.push_back(rankVector[i]);
                lastWeek.push_back(lastWeekVector[i]);
                difference.push_back(differenceVector[i]);
              }
            }
          }

          // Prints the song(s) with highest weekly climb and other information about the song(s)
          cout << "\n\nThe song(s) with the greatest climb from previous week to current week position:  " << endl;
          for (int k = 0; k < maxCount.size(); k++)
          {
            cout
                << "        Song Title: " << topSong[k] << endl
                << "         Artist: " << artist[k] << endl
                << "         Week of: " << date[k] << endl
                << "         Previous Week Position: " << lastWeek[k] << endl
                << "         Current Week Position: " << rank[k] << endl
                << "         Difference of " << difference[k] << " between previous week and current week position \n\n";
          }
        }
      }
    }
    // Menu Option 5
    else if (subMenu == 5)
    {
      string artistInput;
      string artistName;
      string lowerCaseArtist;
      int dateInput;
      int count = 0;
      // Prompt user input for artist name
      cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: \n";

      cin.ignore(); // to ignore space
      getline(cin, artistInput);
      // Convers user input to lower case
      transform(artistInput.begin(), artistInput.end(), artistInput.begin(), ::tolower);
      // Loop through the entire dataset and convert artist names to lower case using transform()
      for (int i = 0; i < fname.size(); i++)
      {
        artistName = fname.at(i).artistName;
        lowerCaseArtist = artistName;
        transform(lowerCaseArtist.begin(), lowerCaseArtist.end(), lowerCaseArtist.begin(), ::tolower);
        // Gets the first 10 songs that were #1 on the charts that match the user input's artist name
        if ((lowerCaseArtist.find(artistInput) != string::npos) && (fname.at(i).rank == 1) && (count < 10))
        {
          count++;

          if (count == 1)
          {
            cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
          }
          // Prints the first 10 songs of that artist and prints the date and week position
          cout
              << count << ") Song: " << fname.at(i).songName << endl
              << "    Artist:" << fname.at(i).artistName << endl
              << "    Week of: " << fname.at(i).date << endl
              << "    Week Position: " << fname.at(i).rank << endl
              << endl;
        }
      }
      // If no artists are found
      if (count == 0)
      {
        cout << "No matching artists were found." << endl
             << endl;
      }
    }
    // Menu Option 6
    else if (subMenu == 6)
    {
      // Sets the while loop to false and break out
      isrunning = false;
      break;
    }
    // If user input is invalid (not 1-6) then run the loop again
    else
    {
      cout << "\nInvalid value.  Please re-enter a value from the menu options below." << endl;
      cout << endl;
      continue;
    }
  }

  return 0;
}