#include"Interface.h"
#include "Graph.h"
#include<stdlib.h>
#include<iostream>
using namespace std;

void Interface::menu()
{
    char option;
    char choice;
    char op;
    char yes;
    int rate=0;
    char check1;
    char check2;
    char check3;
    char check4;


    /* Following three functions create the network by
        fetching data from text file into a Graph data structure
        */
            storeUsersInMap();
            makeArray();
            makeFriendList();



   cout<<"\n\n\n\t===========================================================\n";
    cout<<"\t...........................................................\n\n";
    cout<<"\t                    WELCOME TO FACEBOOK                        \n\n";
    cout<<"\t...........................................................\n";
    cout<<"\t===========================================================\n";

    do
    {
    cout<<"\n\n\t\t\tEnter ""F"" to view options: ";

    cin>>option;

    if(option=='f' || option=='F')
    {
         label:
        system("cls");


        cout<<"\n\n\t........................THE MENU DISPLAY.......................\n\n";
        cout<<"\n\t\t|..........Press 'V' To View Friends Network .........|\n";
        cout<<"\n\t\t|..........Press 'S' To See Suggestions.......|\n";
        cout<<"\n\t\t|..........Press 'D' to Delete/Unfriend........|\n";
        cout<<"\n\t\t|..........Press 'M' To See Mutual Friends.......|\n";
        cout<<"\n\t\t|..........Press 'E' to Cancel................|\n";
        cout<<"\n\n\t\t\t      Press your choice: ";
        cin>>op;
        switch(op)
        {
        case 'V':
        case 'v':

           system("cls");
            cout<<"\n\n\t\t\t*************************************"<<endl;
            cout<<"\t\t\t............VIEW FRIENDS NETWORK ......"<<endl;;
            cout<<"\t\t\t*************************************\n\n"<<endl;

            printGraph();       // PRINT FRIENDS NETWORK

            cout<<"\n\n\n\n\n\t\t      Do you want to return to main menu(Y/N): ";
            cin>>check1;
            if(check1=='y' || check1=='Y')
            {
                goto label;
            }
            else
            {
                 cout<<"\n\n\n\t\t\t*************THANK YOU************\n\n";
            }
            break;
        case 'S':
        case 's':
            system("cls");
            cout<<"\n\n\t\t******************************************"<<endl;
            cout<<"\t\t.............CHECK SUGGESTIONS............"<<endl;
             cout<<"\t\t******************************************"<<endl;

             suggestFriends();  // Suggest friend for the asked user

            cout<<"\n\n\n\t         Do you want to return to main menu(Y/N): ";
            cin>>check2;
            if(check2=='y' || check2=='Y')
            {
                goto label;
            }
            else
            {
                cout<<"\n\n\n\t\t\t*************THANK YOU************\n\n";
            }
            break;


            case 'M':
        case 'm':
            system("cls");
            cout<<"\n\n\t\t******************************************"<<endl;
            cout<<"\t\t.............CHECK MUTUAL FRIENDS............"<<endl;
             cout<<"\t\t******************************************"<<endl;

             mutualFriends();  // Suggest friend for the asked user

            cout<<"\n\n\n\t         Do you want to return to main menu(Y/N): ";
            cin>>check2;
            if(check2=='y' || check2=='Y')
            {
                goto label;
            }
            else
            {
                cout<<"\n\n\n\t\t\t*************THANK YOU************\n\n";
            }
            break;

        case 'D':
        case 'd':
            system("cls");
            cout<<"\n\n\t\t*********************************************"<<endl;
            cout<<"\t\t...............DELETE / UNFRIEND................"<<endl;
            cout<<"\t\t*********************************************"<<endl;

            unfriend();     // Deletes\unfriend from both sides

            cout<<"\n\n\n\t\t  Do you want to return to main menu(Y/N): ";
            cin>>check1;
            if(check1=='y' || check1=='Y')
            {
                goto label;
            }
            else
            {
                 cout<<"\n\n\n\t\t\t*************THANK YOU************\n\n";
            }
            break;
         case 'E':
        case 'e':
            system("cls");
            cout<<"\n\n\t\t************************************************"<<endl;
            cout<<"\t\t.................EXIT SESSION...................."<<endl;
            cout<<"\t\t*************************************************"<<endl;
            cout<<"\n\n\n\t\t     Are you sure you want to Exit(Y/N): ";
            cin>>yes;
            if(yes=='Y' || yes=='y')
            {

                cout<<"\n\n\n\t\t\t*************THANK YOU************\n\n";
            }
            else
            {
                goto label;
            }
            break;
        default:

            cout<<"\n\n\n\t\t\t\t(INVALID KEY)";
            cout<<"\n\n\t\t Do you want to Enter again(Y/N): ";
            cin>>check4;
            if(check4=='y' || check4=='Y')
            {

                goto label;
            }
            else
            {
                 cout<<"\n\n\n\t\t\t*************THANK YOU************\n\n";
            }


        }
    }
    else
    {
        cout<<"\n\n\t\t\t\t(Invalid key)";
        cout<<"\n\t\t      Do you want to enter again(Y/N): ";
        cin>>choice;
    }
    }while(choice=='Y' || choice=='y');


}

