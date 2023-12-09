#include "Manager.h"

Manager::Manager()
{
   
}

Manager::~Manager()
{
    delete MQueue;
    delete TermsList;
    delete NameList;
}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command); //command file open
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    char buffer[100];
    while (!fcmd.eof()) //read file
    {
        fcmd.getline(buffer, 100);
        //cout << buffer << endl; //Ȯ�ο�

        if (strstr(buffer, "LOAD")) //load data.txt 
        {
            LOAD(); //call LOAD function
        }
        else if (strstr(buffer, "ADD")) //add member
        {
            ADD(buffer);
        }
        else if (strstr(buffer, "QPOP")) //pop all members in Queue
        {
            QPOP();
        }
        else if (strstr(buffer, "SEARCH"))  //search specific person
        {
            char name[20] = { '\0' };
            strncpy(name, buffer + 7, strlen(buffer) - 4);
            SEARCH(name);
        }
        else if (strstr(buffer, "PRINT")) //print specific people
        {
            if (strstr(buffer, "NAME"))
                PRINT_NAME();
            else
                PRINT(buffer[6]);
        }
        else if (strstr(buffer, "DELETE"))
        {
           if (strstr(buffer, "NAME"))  //delete specific name
           {
               char name[20] = { '\0' };
               strncpy(name, buffer + 12, strlen(buffer) - 12);
               DELETE_NAME(name);
           }
           else if (strstr(buffer, "DATE")) //delete specific date
           {
               char date[9] = { '\0' };
               for (int i = 0; i < 8; i++)  //store date
               {    
                   if (i >= 0 && i < 4)
                       date[i] = buffer[i + 12] + 17;
                   else if (i == 4 || i == 5)
                       date[i] = buffer[i + 13] + 17;
                   else if (i == 6 || i == 7)
                       date[i] = buffer[i + 14] + 17;
               }
               DELETE_DATE(date);
           }
           else
               PrintErrorCode(600);
        }
        else if (strstr(buffer, "EXIT"))
        {
            PrintSuccess("EXIT");
            break;
        }
        else
            PrintErrorCode(1000);
    }

    //close files
    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

//"data.txt" file data LOAD, error code 100
void Manager::LOAD()
{
    ifstream Qdata;
    Qdata.open("data.txt"); //data.txt ���� �о����
    if (!Qdata)
    {
        PrintErrorCode(100);
    }

    flog << "===== LOAD =====" << endl;

    string buffer;
    while (getline(Qdata, buffer))
    {
        //Queue is full
        if (MQueue->full())
	    {
	    exit(1);
	    }

        int blank = 0;  ///store the position of blank
        int pos = 0;    //start point of next character
        //member infroamtions
        char name[30] = { '\0' };
        int age = 0;
        char date[10] = { '\0' };
        char contract = '\0';

        //store name
        blank = buffer.find(" ");   //find blank
        strcpy(name, (buffer.substr(pos, blank - pos)).c_str());
        pos = blank + 1;    //start point of next character
        
        //store age
        blank = buffer.find(" ", pos);   //find blank
        age = stoi(buffer.substr(pos, blank - pos));  //store in intger
        pos = blank + 1;    //start point of next character
        
        //store date
        int j = 0;
        for (int i = 0; i < 10; i++)
        {
            if (buffer[pos + i] != '-') //omit '-'
                date[j++] = stoi(buffer.substr(pos + i, 1));
        }

        //store contract
        contract = buffer[pos + 11];
        if (contract == '\0')
        {
            PrintErrorCode(100);
            return;
        }

	//print stored information
   	flog << name << '/' << age << '/';
   	for (int i = 0; i < 8; i++)
   	{
            if (i == 4 || i == 6)
                flog << '-';
            flog << char(date[i] + 48);
    	}
        flog << '/' << contract << endl;
        MQueue->push(name, age, date, contract);    //Add memebers
    } //while
    flog << "===============" << endl << endl;
    Qdata.close();  //close file
    return;
}

// ADD extra members, error code 200
void Manager::ADD(char buffer[])
{
    //Queue is full
    if (MQueue->full())
    {
        exit(1); //exit program
    }
    string str(buffer);

    int blank = 0;  ///store the position of blank
    int pos = 4;    //start point of next character
    //member infroamtions
    char name[30] = { '\0' };
    int age = 0;
    char date[10] = { '\0' };
    char contract = '\0';

    //store name
    blank = str.find(" ", pos);   //find blank
    strcpy(name, (str.substr(pos, blank - pos)).c_str());
    pos = blank + 1;    //start point of next character

    //store age
    blank = str.find(" ", pos);   //find blank
    age = stoi(str.substr(pos, blank - pos));  //store in intger
    pos = blank + 1;    //start point of next character

    //store date
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        if (buffer[pos + i] != '-') //omit '-'
            date[j++] = stoi(str.substr(pos + i, 1));
    }

    //store contract
    contract = str[pos + 11];
    //print stored information
    flog << "===== ADD =====" << endl;
    flog << name << '/' << age << '/';
    for (int i = 0; i < 8; i++)
    {
	    if (i == 4 || i == 6)
		    flog << '-';
	    flog << char(date[i] + 48);
    }
    flog << '/' << contract << endl;
    MQueue->push(name, age, date, contract);    //Add memebers
    flog << "===============" << endl << endl;

    return;
}

// QPOP
void Manager::QPOP()
{
    //if Queue is empty
    if (MQueue->empty())
    {
	exit(1);
    }
    else //pop all nodes in Queue
    {
        while (!MQueue->empty())
        {
            MemberQueueNode* Qpop = MQueue->pop();
            TermsBSTNode* NewNode = new TermsBSTNode(Qpop->GetName(), Qpop->Getage(), Qpop->Getdate(), Qpop->Getcontract());
            NameBSTNode* NewNode2 = new NameBSTNode(Qpop->GetName(), Qpop->Getage(), Qpop->Getdate(), Qpop->Getcontract());
            //cout << NewNode->GetName() << endl;
            TermsList->insert(NewNode); //store in TermsBST
            NameList->insert(NewNode2); //store in NameBST
            delete Qpop; //delete MemeberQueueNode
        } //while
        PrintSuccess("QPOP");
    } //else
    return;
}

// SEARCH
void Manager::SEARCH(const char* name)
{
    if (!(NameList->search(name, flog)))
        PrintErrorCode(400);
    return;
}

// PRINT
void Manager::PRINT(char ch)
{
    if (!TermsList->getHead()) //if head is nullptr
    {
        PrintErrorCode(500);
        return;
    }
    if (!TermsList->print(ch, flog))
    {
        PrintErrorCode(500);
        return;
    }
    return;
}

// PRINT name bst
void Manager::PRINT_NAME()
{
    if (!NameList->getRoot()) //if root is nullptr
    {
        PrintErrorCode(500);
        return;
    }
    flog << "===== PRINT =====" << endl;
    flog << "Name_BST" << endl;
    NameList->print(NameList->getRoot(), flog);
    flog << "===============" << endl << endl;
    return;
}

// DELETE specific name
void Manager::DELETE_NAME(const char* name)
{
    char* date_ptr = NameList->delete_name(name); //store memory
    if (date_ptr == nullptr) //delete node not found
    {
        PrintErrorCode(600);
        return;
    }
    if (!TermsList->delete_date(name, date_ptr))
    {
        PrintErrorCode(600);
        return;
    }
    PrintSuccess("DELETE");
    return;
}

//delete all nodes before date
void Manager::DELETE_DATE(const char* date)
{
    while (1)
    {
         if (!TermsList->delete_date_v2(date)) //delete from TermsBST
            break;
    } //while
    NameList->delete_name_v2(NameList->getRoot(), nullptr, date); //delete from NameBST
    PrintSuccess("DELETE");
    return;
}
