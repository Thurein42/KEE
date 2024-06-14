#include<iostream>
#include<iomanip>
using namespace std;

int plan=0;
int customer=0;
int position=0;

class TrainingPlan {
    string trainingPlanName;
    int sessionPerWeek;
    float feesPerWeek;
    public:
        TrainingPlan()
		{
            trainingPlanName = "";
            sessionPerWeek = 0;
            feesPerWeek = 0;
        }
        TrainingPlan(string n, int s, float FPW)
		{
            trainingPlanName = n;
            sessionPerWeek = s;
            feesPerWeek = FPW;
            plan++;
        }

        void Set_Plan(TrainingPlan plans[])
		{
            cout<<"Enter Plan Name: ";
            cin.get();
            getline(cin, trainingPlanName);
            cout<<"Enter Sesion of per week: ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"Enter Fees of per week: ";
            cin>>feesPerWeek;
            cout<<"Successful create the training plan("<<trainingPlanName<<")!"<<endl;
            cin.get();
            plan++;
        }
        
        void Update_Plan()
		{
            cout<<"Plan name("<<trainingPlanName<<") :"<<endl;
            cout<<"Enter Sessions of per week ("<<sessionPerWeek<<") : ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"Enter Fees of per week ("<<feesPerWeek<<") : ";
            cin>>feesPerWeek;
            cout<<"Successful update the training plan("<<trainingPlanName<<")!"<<endl;
            cin.get();
        } 
        
        string getPlanName() 
		{return trainingPlanName;}
		
        float getFeesPerWeek() 
		{return feesPerWeek;}
		
        int getSessionsPerWeek() 
		{return sessionPerWeek;}
        
        void displayPlan()
		{
            cout<<setw(20)<<trainingPlanName<<setw(20)<<sessionPerWeek<<setw(15)<<feesPerWeek;
        }
};

class Customer{
    string CustomerName;
    TrainingPlan trainingPlan;
    float CurrentWeight;
    int PrivateHours[4];
    bool PrivateHourOnOff[4];
    int LearntPosesCount;
    string LearntPoses[10];
    float Cost;
    public:
        Customer()
		{
            CustomerName = "";
            CurrentWeight = 0;
            Cost = 0;
            LearntPosesCount = 0;
            for(int i=0; i<=3; i++)
			{
                PrivateHours[i] = 0;
                PrivateHourOnOff[i] = 0;
            }
        }
        Customer(string n, TrainingPlan tp, float w, int h[4], bool OnOff[4])
		{
            CustomerName = n;
            trainingPlan = tp;
            CurrentWeight = w;
            Cost = 0;
            LearntPosesCount = 0;
            for(int i=0; i<=3; i++)
			{
                PrivateHours[i] = h[i];
                PrivateHourOnOff[i] = OnOff[i];
            }
            customer++;
        }
        
        void AddLearntPoses(string poses[])
        {
            char learnt = 'y';
            int ind = 0;
            int learntInd = 0;
            cout<<"Already learnt poses? (y/n): ";
            cin>>learnt;
            if(learnt=='y') 
            {
                for(int i=0; i<10; i++)
                {
                    cout<<"("<<i+1<<")"<<poses[i];
                    if(i+1 != 10) cout<<" , ";
                }
                while(true)
                {
                    char more = 'y';
                    cout<<"\nEnter pose index : ";
                    cin>>ind;
                    cout<<"Got more?(y/n) : ";
                    cin>>more;
                    LearntPosesCount++;
                    LearntPoses[learntInd] = poses[ind-1];
                    learntInd++;
                    if(more!='y') break;
                }
            }
            cout<<endl;
        }

        string setCustomer(TrainingPlan plans[])
		{
            int PlanIndex = 0;
            cout<<"Enter Customer name : ";
            cin.get();
            getline(cin, CustomerName);

            TrainingPlanLabel:
            cout<<"Enter Training plan - Free space plans: "<<endl;
            
			for(int i=0; i<plan; i++)
			{
                cout<<"Plan: "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=plan) cout<<endl;
            }
            cout<<"\nChoose the index : ";
            if(PlanIndex < 0 || PlanIndex > plan) 
				goto TrainingPlanLabel;
            cin>>PlanIndex;
            trainingPlan = plans[PlanIndex-1];

            cout<<"Enter User current weight(kg): ";
            cin>>CurrentWeight;

            for(int i=0; i<=3; i++)
			{
                char ch = '0';
                PrivateHourLabel:
                cout<<"Enter "<<i+1<<" Week Private Hours: ";
                cin>>PrivateHours[i];
                
                if(PrivateHours[i] < 0 || PrivateHours[i] > 5) 
				{
                    cout<<"More than five or less than zero"<<endl;
                    goto PrivateHourLabel;
                }
                
                OnOffLabel:
                cout<<"Online or Offline(0 or 1): ";
                cin>>ch;
					
                if(ch=='0') 
					PrivateHourOnOff[i] = 0;
					
                else PrivateHourOnOff[i] = 1;
            }
            LearntPosesCount = 0;
            customer++;
            return trainingPlan.getPlanName();
        }
        string UpdateCustomer(TrainingPlan plans[]){
            int PlanIndex = 0;
            cout<<"Customer name("<<CustomerName<<") :"<<endl;

            TrainingPlanLabel:
            cout<<"Enter Training plan - Free space plans :"<<endl;
            for(int i=0; i<plan; i++)
			{
                cout<<"Plan: "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=plan) 
					cout<<endl;
            }
            cout<<"\nChoose the index : ";
            
            if(PlanIndex < 0 || PlanIndex > plan)
				goto TrainingPlanLabel;
            cin>>PlanIndex;
            trainingPlan = plans[PlanIndex-1];

            cout<<"Enter User current weight(kg): ";
            cin>>CurrentWeight;

            LearntPosesCount = 0;
            return trainingPlan.getPlanName();
        }
        float getFinalCost(){
            Cost = 0;
            Cost += trainingPlan.getFeesPerWeek()*4;
            int Count = LearntPosesCount;
            if(Count > 5) Count = 5;
            
            for(int i=0; i<=3; i++)
			{
                if(PrivateHourOnOff[i]) 
					Cost += 15000 * PrivateHours[i];
					
                else Cost += 17000 * PrivateHours[i];
            }
            return Cost - (Cost * Count)/100;
        }
        float getCost() 
		{
            Cost = 0;
            Cost += trainingPlan.getFeesPerWeek() * 4;
            
            for(int i=0; i<=3; i++)
			{
                if(PrivateHourOnOff[i]) 
					Cost += 15000 * PrivateHours[i];
                
                else Cost += 17000 * PrivateHours[i];
            }
            return Cost;
        }
        void displayCustomer()
		{
            int online = 0, offline = 0;
            for(int i=0; i<=3; i++)
			{
                if(PrivateHourOnOff[i]) 
					online++;
                
                else offline++;
  			}
            cout<<setw(20)<<CustomerName<<setw(20)<<trainingPlan.getPlanName()<<setw(20)<<LearntPosesCount<<setw(20)<<offline<<setw(20)<<online<<setw(20)<<getFinalCost();
        }
        void displayCustomerDetails()
		{
            int online = 0, offline = 0;
            int Count = LearntPosesCount;
            if(Count > 5) 
				Count = 5;
            for(int i=0; i<=3; i++)
			{
                if(PrivateHourOnOff[i]) 
					online += PrivateHours[i];
                
                else offline += PrivateHours[i];
  			}
            cout<<setw(30)<<"Customer name: "<<setw(20)<<CustomerName<<endl<<setw(30)<<"Weight: "
				<<setw(20)<<CurrentWeight<<endl<<setw(30)<<"Training plan: "<<setw(20)<<trainingPlan.getPlanName()<<endl
                <<setw(30)<<"Learnt Poses Counts: "<<setw(20)<<LearntPosesCount<<endl;     
            for(int i=0; i<LearntPosesCount; i++) cout<<LearntPoses[i]<<", ";
            cout<<endl<<setw(30)<<"Sessions per week: "
				<<setw(20)<<trainingPlan.getSessionsPerWeek()<<setw(20)<<trainingPlan.getFeesPerWeek() * 4<<endl
                <<setw(30)<<"Private (Online:15000): "<<setw(20)<<online<<setw(20)<< 15000 * online<<endl
                <<setw(30)<<"Private (Offline:17000): "<<setw(20)<<offline<<setw(20)<< 17000 * offline<<endl
                <<setw(30)<<"DISCOUNT(%): "<<setw(20)<<LearntPosesCount<<setw(20)<<getCost() * Count/100<<endl
                <<setw(30)<<"Total Cost: "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
        }
};

void merge(Customer array[], int const left, int const mid, int const right){
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    Customer *leftArray = new Customer[subArrayOne],
         *rightArray = new Customer[subArrayTwo];

    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].getFinalCost()
            <= rightArray[indexOfSubArrayTwo].getFinalCost()) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(Customer array[], int const begin, int const end){
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}
class Position{
    string Name;
    int PoseCount;
    public:
        string PoseType[10];
        string PoseName[10];
        Position()
		{
            Name = "";
            PoseCount = 0;
        }
        Position(string name, string type[10], string names[10], int po)
			{
            	name = name;
                PoseCount = po;
            	for(int i=0; i<=9; i++)
			    {
                	PoseType[i] = type[i];
                	PoseName[i] = names[i];
        		}
            position++;
            }
        void add_Position()
			{
            	cout<<"Position name : "<<Name<<endl;
            	cout<<"Positions: "<<endl;
            	for(int i=0; i<PoseCount; i++) 
					{
                	cout<<PoseName[i];
   						if(i+1 != PoseCount) cout<<" , ";
   						
                		else cout<<endl;
   			 		}
            	if(PoseCount == 10) 
					{
                		cout<<"10 Poses have been added"<<endl;
                		cin.get();
                		return;
            		}
            char m = 'y';
            while(true)
			{
                cin.get();
                if(PoseCount==10) 
					break;

                cout<<"Enter The Position Name("<<PoseCount+1<<") : ";
                getline(cin,PoseName[PoseCount]);
                cout<<"Enter The Position Type("<<PoseCount+1<<") : ";
                getline(cin,PoseType[PoseCount]);
                cout<<"Successfully added("<<PoseName[PoseCount]<<")!!"<<endl;
                PoseCount++;

                cout<<"Want to Add more?(y/n) : ";
                cin>>m;
                if(m == 'n')
					break;
            }
        }
        void Create_Position()
			{
            	cout<<"Enter Position Name : ";
            	cin.get();
            	getline(cin,Name);
                position++;
            	add_Position();
        	}
        void Display_Position()
			{
            	cout<<setw(20)<<Name<<endl;
            	for(int i=0; i<PoseCount; i++)
				{
                	cout<<setw(25)<<""<<setw(20)<<PoseType[i]<<setw(20)<<PoseName[i]<<endl;
            	}
        	}
};
void Display_TrainingPlans(TrainingPlan plans[]);
void Display_YogaPositions(Position poses[]);
void Display_Customers(Customer customers[]);

int main(){
    int mCode;
    
    Position Pose[5];
    string BasicPType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string BasicPName[10] ={"Archer Pose","Dolphin Pose","Frog Pose","Fallen Triangle","Big Toe Pose","Lion Pose","Airplane Pose","Side Lunge","Side Reclining","Bird Dog Pose"};
    Position Pose1("BASIC",BasicPType,BasicPName,10);
    
    string IntermediatePoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string IntermediatePoseName[10] ={"   Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge","Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position Pose2("INTERMEDIATE",IntermediatePoseType,IntermediatePoseName,10);
    
    Pose[0] = Pose1;
    Pose[1] = Pose2;
    
    TrainingPlan Plan[7];
    TrainingPlan Basic("BASIC",3,25000);
    TrainingPlan Inter("INTERMEDIATE",3,35000);
    TrainingPlan Adv("ADVANCED",2,50000);
    Plan[0] = Basic;
    Plan[1] = Inter;
    Plan[2] = Adv;

    Customer customers[50];
    int c1Private[4] = {1,1,3,2};
    bool c1OnOff[4] = {true,false,true,true};
    int c2Private[4] = {1,1,3,2};
    bool c2OnOff[4] = {true,true,true,false};
    int c3Private[4] = {1,1,3,2};
    bool c3OnOff[4] = {true,true,false,true};
    int c4Private[4] = {1,1,3,2};
    bool c4OnOff[4] = {false,false,true,true};
    int c5Private[4] = {1,1,3,2};
    bool c5OnOff[4] = {true,false,false,true};
    
    Customer c1("Aye Aye",Plan[0],40,c1Private,c1OnOff);
    Customer c2("Mg Mg",Plan[0],55,c2Private,c2OnOff);
    Customer c3("Kyaw Kyaw",Plan[0],60,c3Private,c3OnOff);
    Customer c4("Su Su",Plan[0],45,c4Private,c4OnOff);
    Customer c5("Zaw Zaw",Plan[0],55,c5Private,c5OnOff);
    customers[0] = c1;
    customers[1] = c2;
    customers[2] = c3;
    customers[3] = c4;
    customers[4] = c5;
    
    mLabel:
    cout<<"====================================================="<<endl;
    cout<<"     Welcome from The Amazing Sport Yoga System!     "<<endl;
    cout<<"====================================================="<<endl;
    cout<<setw(20)<<"1. Training plan."<<endl<<setw(15)<<"2. Customers"<<endl<<setw(19)<<"0. Quit program."<<endl;
    cin>>mCode;
    if(mCode==1) 
	{
        tpscreenLabel:
        int tMCode = 0;
        cout<<"1. Add a training plan.\n2. Show all training plans.\n3. Update a training plan.\n4. Add a yoga plan.\n5. Display yoga plans.\n6. Add yoga poses.\n0. Return to main screen."<<endl;
        cin>>tMCode;
      
        if(tMCode < 0 || tMCode > 6) 
			goto tpscreenLabel;
        if(tMCode == 0) 
			goto mLabel;
        else if(tMCode == 1) 
			plan[Plan].Set_Plan(Plan);
        else if(tMCode == 2) 
			Display_TrainingPlans(Plan);
        else if(tMCode == 3) 
		{
            int index = 0;
            Display_TrainingPlans(Plan);
            cout<<"Enter The number to update: ";
            cin>>index;
            Plan[index-1].Update_Plan();
        }
        else if(tMCode == 4) Pose[position].Create_Position();
        else if(tMCode == 5) Display_YogaPositions(Pose);
        else if(tMCode == 6) 
		{
            int index = 0;
            Display_YogaPositions(Pose);
            cout<<"\nEnter yoga plan index to add : ";
            cin>>index;
            Pose[index-1].add_Position();
        }
        goto tpscreenLabel;
    } 
    else if(mCode==2)
	{
        csScreenLabel:
        int csScreenCode = 0;
        cout<<"1. Register a new customer.\n2. View all customers.\n3. Update customer info.\n4. Calculate costs for the customer.\n0. Return to main screen. \n";
        cin>>csScreenCode;
        if(csScreenCode < 0 || csScreenCode > 4) 
			goto csScreenLabel;
      
        if(csScreenCode == 0) 
			goto mLabel;
        else if(csScreenCode == 1) 
		{
            string plan = customers[customer].setCustomer(Plan);
            if(plan=="INTERMEDIATE") customers[customer-1].AddLearntPoses(BasicPName);
            else if(plan=="ADVANCED") customers[customer-1].AddLearntPoses(IntermediatePoseName);
 		}
        else if(csScreenCode == 2) 
		{
            mergeSort(customers, 0, customer-1);
            Display_Customers(customers);
        }
        else if(csScreenCode == 3) 
		{
            int index = 0;
            Display_Customers(customers);
            cout<<"Enter The number to update: ";
            cin>>index;
            string plan = customers[index-1].UpdateCustomer(Plan);
            if(plan=="INTERMEDIATE") customers[index-1].AddLearntPoses(BasicPName);
            else if(plan=="ADVANCED") customers[index-1].AddLearntPoses(IntermediatePoseName);
        }
        else if(csScreenCode == 4) 
		{
            int index = 0;
            Display_Customers(customers);
            cout<<"Enter The number to calculate the costs: ";
            cin>>index;
            customers[index-1].displayCustomerDetails();
        }
        goto csScreenLabel;
    }

    else if(mCode==0)
		return 0;

    else goto mLabel;
}

void Display_TrainingPlans(TrainingPlan plans[]){
    cout<<setw(5)<<"No"<<setw(20)<<"Plan name"<<setw(20)<<"Session per week"<<setw(15)<<"Fees per week"<<endl;
    for(int i=0; i<plan; i++) 
	{
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
}

void Display_YogaPositions(Position poses[]){
    cout<<setw(5)<<"No"<<setw(20)<<"Position names"<<setw(20)<<"Pose type"<<setw(20)<<"Pose name"<<endl;
    for(int i=0; i<position; i++) 
	{
        cout<<setw(5)<<i+1;
        poses[i].Display_Position();
        cout<<endl;
    }
}

void Display_Customers(Customer customers[]){
    cout<<setw(5)<<"No"<<setw(20)<<"Customer name"<<setw(20)<<"Training plan"<<setw(20)<<"Learnt poses count"<<setw(20)<<"Offline hours"<<setw(20)<<"Online hours"<<setw(25)<<"Cost(current month)"<<endl;
    for(int i=0; i<customer; i++) 
	{
        cout<<setw(5)<<i+1;
        customers[i].displayCustomer();
        cout<<endl;
    }
}