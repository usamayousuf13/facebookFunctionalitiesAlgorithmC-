#include "Graph.h"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Graph default Constructor


Graph::Graph()
{
    array=NULL;
    sizeOfMap=0;
}

/* Fetch users data from text file
    and store it in a Map data structure namely "user"
    */

void Graph::storeUsersInMap()
{
    string name="";
    int mapCount=0;
    ifstream fin;
    fin.open("users.txt");
    if(fin==NULL)
    {
        cout<<"File Not Open";
    }

    else
    {

        while (!fin.eof( ))
        {
            fin>>name;
            user[mapCount]=name;
            mapCount++;
        }
    }
}

// returns total size  of map i.e total no. of users

int Graph::totalSizeOfMap()
{
    int totalSize=0;
    totalSize=user.size();
    return totalSize;
}

/* Make a dynamic 1D array of adjList
    Size of that structure would be equal to
    the total size of map.
    This adjList array will be use to point
    first node of link list (friend list) of every vertex (user)
    */


adjList* Graph::makeArray()
{
    int sizeOfArray=totalSizeOfMap();
    array = new adjList[sizeOfArray];

    for (int i=0; i<sizeOfArray; i++)
    {
        array[i].head=NULL;
    }
}


//  Creats a newNode

adjListNode* Graph::newAdjListNode(string dest)
{
    adjListNode* newNode = new adjListNode;
    newNode->data = dest;
    newNode->next = NULL;
    return newNode;
}


/* Our adjcList array uses integer value for index.
    Each array element represents a user.
    Map data structures gives each user a key value i.e in integer.
    This helps in accessing adjList array.

    This function search for the user (string) in map
    and then returns it key value (i.e in integer)
    */

int Graph::convertValueToKey(string item)
{
    int key=0;
    map <int,string>::iterator p=user.begin();
    while(p!=user.end())
    {
        if (p->second == item)
        {
            key=p->first;
        }
        p++;
    }
    return key;
}

/* Make a link list to represnt friend list */


void Graph::addEdge(string src, string dest)
{
    adjListNode* newNode = newAdjListNode(dest);
    int key=0;
    key=convertValueToKey(src);
    newNode->next = array[key].head;
    array[key].head = newNode;

}

/* Fetch data from text file.
    "tempSrc" is the name of a user
    "tempDest" is the name of friends of that user

    This function calls the "addEdge" function to make
    friend list from file
    */



void Graph::makeFriendList()
{
    ifstream fin;
    fin.open("friends.txt");
    if(fin==NULL)
    {
        cout<<"File Not Open";
    }
    else
    {
        while (fin!=0)
        {

            string s;
            getline(fin,s);
            string tempSrc ="-1";
            string tempDest="";
            istringstream iss(s);
            while (iss)
            {

                string sub;
                iss >> sub;
                if (sub=="\0")
                {
                    continue;
                }
                if (tempSrc=="-1")
                {
                    tempSrc=sub;
                }
                else
                {
                    tempDest=sub;
                    addEdge(tempSrc,tempDest);
                }
            }
        }
    }
}


void Graph::suggestFriends ()
{
    bool check=false;
    bool sugCheck=false;

    string userToSuggest="";
    int keyOfUserToSuggest=0;
    int keyOfFriend=0;
    string suggestedFriends[20];
    map <int,string>::iterator p;



    do
    {
        cout << " \nEnter user you want to suggest friends for " <<endl;
        cin >> userToSuggest;
        p=user.begin();
        while(p!=user.end())
        {
            if (p->second == userToSuggest)
            {
                keyOfUserToSuggest=p->first;
                check=true;
            }
            p++;
        }
        if (check==false)
        {
            cout << "\t User Doesnot found. Please enter valid user "<<endl;
        }
    }
    while(check==false);

    cout << "\n\t ===================";
    cout << "\n\t  SUGGESTED  FRIENDS ";
    cout << "\n\t ==================="<<endl;



    adjListNode* userFriendItterator = array[keyOfUserToSuggest].head;
    while (userFriendItterator != NULL ) // until all friends of user are traversed
    {
        string friends = userFriendItterator->data;  // return name of first friend in string


        p=user.begin();
        while (p!=user.end())
        {
            if (p->second == friends)
            {
                keyOfFriend=p->first;   // return key of friend
            }
            p++;
        }

        string friendsOfFriend = array[keyOfFriend].head->data; // return friend of the user's friend
        int i=0;
        adjListNode* temp = array[keyOfUserToSuggest].head;
        while (temp != NULL)
        {

            string friendsOfUser = temp->data;

            if (friendsOfUser == friendsOfFriend || friendsOfFriend == userToSuggest )
            {
                sugCheck=true;
                temp=temp->next;
                break;
            }

            temp=temp->next;

        }



        if (sugCheck==false)
        {
            bool checkForDuplicate=false;
            for (int i=0; i<20; i++)
            {
                if (suggestedFriends[i]==friendsOfFriend)
                {
                    checkForDuplicate=true;
                    break;
                }
            }
            if (checkForDuplicate==false)
            {
                suggestedFriends[i]=friendsOfFriend;
                cout << friendsOfFriend << endl;
                i++;
            }

            //================= OK ==============================
        }
        sugCheck=false;


        userFriendItterator = userFriendItterator->next;
    }


}


// Delete node from graph

void Graph::deleteItem (string item,int myKey)
{
    adjListNode* temp=array[myKey].head;

    if (temp->data==item)
    {
        array[myKey].head=temp->next;
        delete temp;
    }

    else
    {
        while ( temp->next!=NULL &&  item!=temp->next->data )
        {
            temp=temp->next;

        }
        if (temp->next!=NULL)
        {
            adjListNode *target=new adjListNode;
            target=temp->next;

            temp->next=target->next;
            delete target;

        }
        else
            cout << "\nItem Not Found"<<endl;

    }
}


// Delete a friend of user

void Graph::unfriend()
{

    bool check=false;
    bool checkForValidUser=false;
    string myUser="";
    string userToUnfriend="";

    int myKey=-1;
    int keyOfFriend=-1;

    map <int,string>::iterator p;
    do
    {
        cout << " \n Enter your name " <<endl;
        cin >> myUser;
        cout << " \n Whom do you want to unfriend " <<endl;
        cin >> userToUnfriend;

        p=user.begin();
        while(p!=user.end())
        {
            if (p->second == myUser)
            {
                myKey = p->first;
            }
            else if (p->second == userToUnfriend)
            {
                keyOfFriend = p->first;
            }
            p++;
        }
        if (myKey==-1)
        {
            cout << " Please enter Valid User '"<<endl;
        }

    }
    while (myKey==-1);      // Runs until user enter valid name
    adjListNode* temp = array[myKey].head;
    while (temp != NULL )
    {
        if (temp->data== userToUnfriend)
        {
            check =true;
            break;
        }
        temp=temp->next;

    }
    if (check)
    {
        deleteItem(userToUnfriend,myKey);   // Unfriend from user profile
        deleteItem(myUser,keyOfFriend);     // Unfriend user from that "friend's" profile
        cout << "\n=== Unfriend Successful ==="<<endl;
    }
    else
    {
        cout << "Friend to be deleted is Not found" <<endl;
    }
    printToFile();
}





//================================================================================================================


// Print the Graph

void Graph::printGraph()
{
    int v=totalSizeOfMap();
    map <int,string>::iterator p=user.begin();

    for (int i=0; i<v; i++)
    {
        adjListNode* pCrawl = array[i].head;

        cout << "\t\""<<p->second<<"\""<<" ---";
        p++;
        while (pCrawl)
        {
            cout<<"-> "<<pCrawl->data;
            pCrawl = pCrawl->next;
        }
        cout<<"\n"<<endl;
    }
}



/* Use to append the file after delete friend
    function is called */


void Graph::printToFile()
{
    ofstream fout;
    fout.open("friends.txt");

    int v=totalSizeOfMap();
    map <int,string>::iterator p=user.begin();

    for (int i=0; i<v; i++)
    {
        adjListNode* pCrawl = array[i].head;

        fout <<p->second<<"\t\t";
        p++;
        while (pCrawl)
        {
            fout<<pCrawl->data<<"\t";
            pCrawl = pCrawl->next;
        }
        fout<<"\n";
    }
}

// =====================================================================================





void Graph::mutualFriends ()
{
    bool check=false;
    bool sugCheck=false;

    string myuser="";
    string friendToSearchMF="";
    int keyOfUser=0;
    int keyOfFriend=0;
    string mutual_Friends[20];
    map <int,string>::iterator p;



    do
    {
        cout << " \nEnter your name " <<endl;
        cin >> myuser;
        cout << " \nEnter other friend name " <<endl;
        cin >> friendToSearchMF;
        p=user.begin();
        while(p!=user.end())
        {
            if (p->second == myuser)
            {
                keyOfUser=p->first;
                check=true;
            }
            else if (p->second == friendToSearchMF)
            {
                keyOfFriend=p->first;   // return key of friend
                check = true;
            }
            p++;
        }
        if (check==false)
        {
            cout << "\t User Doesnot found. Please enter valid user "<<endl;
        }
    }
    while(check==false);

    cout << "\n\t ===================";
    cout << "\n\t  MUTUAL  FRIENDS ";
    cout << "\n\t ==================="<<endl;

    adjListNode* temp2 = array[keyOfFriend].head;
    while (temp2 != NULL)
    {
        adjListNode* userFriendItterator = array[keyOfUser].head;
        while (userFriendItterator != NULL ) // until all friends of user are traversed
        {
            string friendsOfFriend = temp2->data; // return friend of the user's friend
            int i=0;
            adjListNode* temp = array[keyOfUser].head;
            while (temp != NULL)
            {

                string friendsOfUser = temp->data;

                if (friendsOfUser == friendsOfFriend )
                {
                    sugCheck=true;
                    temp=temp->next;
                    break;
                }

                temp=temp->next;

            }



            if (sugCheck==true)
            {
                bool checkForDuplicate=false;
                for (int i=0; i<20; i++)
                {
                    if (mutual_Friends[i]==friendsOfFriend)
                    {
                        checkForDuplicate=true;
                        break;
                    }
                }
                if (checkForDuplicate==false)
                {
                    mutual_Friends[i]=friendsOfFriend;
                    cout << friendsOfFriend << endl;
                    i++;
                }

            }
            sugCheck=false;


            userFriendItterator = userFriendItterator->next;
        }

        temp2=temp2->next;
    }
}
