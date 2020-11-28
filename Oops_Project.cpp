#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_map>
#include <windows.h>
using namespace std;
int PNR_NUM=999913;

class flight;

class General_Details{
public:
    string name;
    int age;
    string email_address;
    int phone_number;
    General_Details(){
        this->name="\0" ;
        this->age = 0 ;
        this->email_address="\0" ;
        this->phone_number = 0 ;
    }
    General_Details(string name,int age,string email_address,int phone_number){
        this->name=name;
        this->age=age;
        this->email_address=email_address;
        this->phone_number=phone_number;
    }
    void display(){
        cout<<"Name            :- "<<name<<endl;
        cout<<"Age             :- "<<age<<endl;
        cout<<"Email Address   :- "<<email_address<<endl;
        cout<<"Phone Number    :- "<<phone_number<<endl;
    }
};

class passenger:public General_Details{
    int extra_miles;
    int pnr_number;
public:
    string flight_name;
    int seat_type;
    string comp_name;

    passenger(){
        this->extra_miles=0;
        this->flight_name="/0";
        this->pnr_number=0;
        this->seat_type=0;
        this->comp_name="/0";
    }
    passenger(string name,int age,string email_address,int phone_number):General_Details(name,age,email_address,phone_number){
       this->extra_miles=0;
       this->flight_name="/0";
       this->pnr_number=0;
       this->seat_type=0;
       this->comp_name="/0";
    }

    friend class flight;
    friend void payment_options(int,passenger &, flight *);
    friend void print_ticket(passenger);
    friend void unbook_flight(int);
};

unordered_map<string,int>login;
unordered_map<string,passenger>details;

class employee:public General_Details{
    string post;
    int employee_id;
    string company_name;

    public:
        employee(){}
        employee(string name,int age,string email_address,int phone_number,string post,int employee_id,string company_name):General_Details(name,age,email_address,phone_number){
            this->post=post;
            this->employee_id=employee_id;
            this->company_name=company_name;
        }
        void display(){
        cout<<"Name            :- "<<name<<endl;
        cout<<"Age             :- "<<age<<endl;
        cout<<"Email Address   :- "<<email_address<<endl;
        cout<<"Phone Number    :- "<<phone_number<<endl;
    }
};

class flight{
public:
    bool seat_business[3];
    bool seat_economy[3];
    bool seat_executive[3];
    int count1;
    int count2;
    int count3;
   string flight_name;
   string source;
   string destination;
   int arrival_time;
   int departure_time;
   int economy_fare;
   int executive_fare;
   int business_fare;

   passenger passenger_list[9];
   flight(){}
   flight(string flight_name,string source,string destination,int arrival_time,int departure_time,int economy_fare,int executive_fare,int business_fare){
       this->flight_name=flight_name;
       this->source=source;
       this->destination=destination;
       this->arrival_time=arrival_time;
       this->departure_time=departure_time;
       this->economy_fare=economy_fare;
       this->executive_fare=executive_fare;
       this->business_fare=business_fare;
       count1=0;
       count2=0;
       count3=0;
       for(int i=0;i<3;i++){
            seat_business[i]=false;
            seat_economy[i]=false;
            seat_executive[i]=false;
       }
   }
   void display(){
       cout<<flight_name<<"\t\t";
       cout<<source<<"\t";
       cout<<destination<<"\t\t";
       cout<<departure_time<<"\t\t\t";
       cout<<arrival_time<<endl<<endl;
   }
};

class pair1{
public:
    passenger *p;
    flight *f;

    pair1(){}
    pair1(passenger *p,flight *f){
        this->p=p;
        this->f=f;
    }
};
unordered_map<int,pair1>ourMap;      //for unbook flight

class company{
public:
    string company_name;
    flight **total_flights=new flight*[6];
    int num_of_flights;
    employee list_of_employees[6];

    company(){}

    company(string company_name,flight **total_flights,employee *list_of_employees){
        this->company_name=company_name;

        for(int i=0;i<6;i++){
            this->total_flights[i]=total_flights[i];
        }
        num_of_flights=6;

        for(int i=0;i<6;i++){
            this->list_of_employees[i]=list_of_employees[i];
        }
    }
};

class pair2{
public:
    company c;
    flight *f;

    pair2(){}
    pair2(company c,flight *f){
        this->c=c;
        this->f=f;
    }
};

vector<pair2> get_flight_name(company c[],string source,string destination){
    vector<pair2> v;
    for(int i=0;i<3;i++){      //total companies

        company co=c[i];
        for(int j=0;j<co.num_of_flights;j++){
            flight *f=co.total_flights[j];
             if(f->source==source&&f->destination==destination){
                    pair2 p;
                    p.c=co;
                    p.f=f;
                    v.push_back(p);
            }
        }

    }
return v;
}

void admin(company *total_companies,string flight_name="\0",string company_name="\0"){
    if(flight_name[0]!='\0'){
        for(int i=0;i<3;i++){
                company c=total_companies[i];
                for(int j=0;j<6;j++){
                    flight *f=c.total_flights[j];
                    if(f->flight_name==flight_name){
                        for(int k=0;k<9;k++){
                            passenger p=f->passenger_list[k];
                            p.display();
                            cout<<endl;
                        }
                    }
                }
        }
    }
    else{
        for(int i=0;i<3;i++){
                company c=total_companies[i];

                if(c.company_name==company_name){
                    for(int j=0;j<6;j++){
                        employee e=c.list_of_employees[j];
                        e.display();
                        cout<<endl;
                    }
                }
        }
    }
}

int get_flight_schedule(company c,string source,string destination){
    bool flag=false;
    for(int i=0;i<c.num_of_flights;i++){
        flight *f=c.total_flights[i];
        if(f->source==source&&f->destination==destination){
            cout<<"Company Name:- "<<c.company_name<<endl<<endl;
            cout<<"Flight name\tSource\tDestination\tDeparture timing\tArrival timing"<<endl;
            cout<<endl;
            f->display();
            flag=true;
            cout<<endl;
        }
    }
    if(flag==false){
        cout<<"No flights found in "<<c.company_name<<"."<<endl;
        return 0;
    }
    return 1;
}

void compare_rates(vector<pair2>v){
    for(int i=0;i<v.size();i++){
            if(v.at(i).f->count1+v.at(i).f->count2+v.at(i).f->count3<9){

                cout<<v.at(i).c.company_name<<" "<<v.at(i).f->flight_name<<endl<<endl;
                if(v.at(i).f->count1<3){
                        cout<<"Available tickets in Economy :- "<<3-v.at(i).f->count1;
                        cout<<"\tPrice    :- "<<v.at(i).f->economy_fare<<endl<<endl;
                }
                if(v.at(i).f->count2<3){
                        cout<<"Available tickets in Executive :- "<<3-v.at(i).f->count2;
                        cout<<"\tPrice    :- "<<v.at(i).f->executive_fare<<endl<<endl;
                }
                if(v.at(i).f->count3<3){
                        cout<<"Available tickets in Business :- "<<3-v.at(i).f->count3;
                        cout<<"\tPrice    :- "<<v.at(i).f->business_fare<<endl<<endl;
                }
                cout<<endl;
            }
            else{
                cout<<"All tickets are booked."<<endl;
            }
    }

}
void print_ticket(passenger P){
    if(P.seat_type==1||P.seat_type==2||P.seat_type==3){
        P.display();
        cout<<"PNR number      :- "<<P.pnr_number<<endl;
        cout<<"Extra miles     :- "<<P.extra_miles<<endl;
        cout<<"Company name    :- "<<P.comp_name<<endl ;
        cout<<"Flight name     :- "<<P.flight_name<<endl ;
    }
    if(P.seat_type==1){
        cout<<"Seat type       :- Economy "<<endl ;
    }
    else if(P.seat_type==2){
        cout<<"Seat type       :- Executive "<<endl ;
    }
    else if(P.seat_type==3){
        cout<<"Seat type       :- Business "<<endl ;
    }
    else{
        cout<<"No such type of seats."<<endl;
    }

}

void payment_options(int price,passenger &P,flight *f){
    if(P.email_address!="harshitgoel413@gmail.com"&&P.email_address!="diprachaudhry18@gmail.com"){
        cout<<"Press 1 for Net Banking."<<endl;
        cout<<"Press 2 for Debit Card. "<<endl;
        cout<<"Press 3 for Credit Card."<<endl;
        int n;
        cin>>n;
        int discounted_price=price-P.extra_miles/10;
        P.extra_miles=0;
        cout<<discounted_price<<" has been deducted."<<endl;

    }
    P.pnr_number=PNR_NUM;
    PNR_NUM++;
    P.extra_miles= P.extra_miles+price/10;

    pair1 pf(&P,f);
    pair<int ,pair1>p(P.pnr_number,pf);
    ourMap.insert(p);
}

void book_ticket(vector<pair2>v,string Company_name,int digit, passenger &P){
    for(int i=0;i<v.size();i++){
        if(v.at(i).c.company_name==Company_name){
            if(digit==1){
            if(v.at(i).f->count1==3){
                cout<<"No seats left in economy."<<endl;
            }
            else {
                v.at(i).f->seat_economy[v.at(i).f->count1]=true;
                v.at(i).f->count1++;
                P.seat_type=1;
                v.at(i).f->passenger_list[v.at(i).f->count1+v.at(i).f->count2+v.at(i).f->count3-1]=P;
                    payment_options(v.at(i).f->economy_fare,P,v.at(i).f);
                    P.comp_name=Company_name;
            }
        }
        else if(digit==2){
            if(v.at(i).f->count2==3){
                cout<<"No seats left in executive."<<endl;
            }
            else {
                v.at(i).f->seat_executive[v.at(i).f->count2]=true;
                v.at(i).f->count2++;
                P.seat_type=2;
                v.at(i).f->passenger_list[v.at(i).f->count1+v.at(i).f->count2+v.at(i).f->count3-1]=P;
                    payment_options(v.at(i).f->executive_fare,P,v.at(i).f);
                    P.comp_name=Company_name;
            }
        }
        else if(digit==3){
            if(v.at(i).f->count3==3){
                cout<<"No seats left in business."<<endl;
            }
            else {
                v.at(i).f->seat_business[v.at(i).f->count3]=true;
                v.at(i).f->count3++;
                P.seat_type=3;
                v.at(i).f->passenger_list[v.at(i).f->count1+v.at(i).f->count2+v.at(i).f->count3-1]=P;
                    payment_options(v.at(i).f->business_fare,P,v.at(i).f);
                    P.comp_name=Company_name;
            }
        }
        else{
            cout<<"No such type of seats."<<endl;
        }
        P.flight_name=v.at(i).f->flight_name;
        return ;
        }
    }
    return ;
}

void unbook_flight(int PNR_NUMBER){
    if(ourMap.count(PNR_NUMBER)>0){
        pair1 pf=ourMap[PNR_NUMBER];
        passenger *P=pf.p;
        flight *F=pf.f;
        int seat_digit=P->seat_type;

        int index=-1;         //index of the passenger to be deleted in the passenger list

        for(int i=0;i<9;i++){          //deleting passengers from passenger list
            if(P->pnr_number==F->passenger_list[i].pnr_number){
                 index=i;
                 break;
            }
        }
        F->passenger_list[0]=F->passenger_list[1];
        F->passenger_list[1]=F->passenger_list[2];
        F->passenger_list[2]=F->passenger_list[3];
        F->passenger_list[3]=F->passenger_list[4];
        //shifting the array elements
      /*
        for(int j=index;j<8;j++){
            F->passenger_list[j]=F->passenger_list[j+1];
        }*/

      //  passenger h;
      //  F->passenger_list[8]=h;

        P->extra_miles-=100;
        P->pnr_number=0;

        if(seat_digit==1){
            F->seat_economy[F->count1-1]=false;
            F->count1--;
            cout<<"Your ticket has been unbooked."<<endl;
            system("PAUSE");
            system("CLS");
        }
        else if(seat_digit==2){
            F->seat_executive[F->count2-1]=false;
            F->count2--;
            cout<<"Your ticket has been unbooked."<<endl;
            system("PAUSE");
            system("CLS");
        }
        else if(seat_digit==3){
            F->seat_business[F->count3-1]=false;
            F->count3--;
            cout<<"Your ticket has been unbooked."<<endl;
            system("PAUSE");
            system("CLS");
        }else{
            cout<<"No such type of seats."<<endl;
            system("PAUSE");
            system("CLS");
        }
        P->seat_type=0;

        ourMap.erase(PNR_NUMBER);
    }
    else{
    cout<<"Invalid PNR Number."<<endl;

    system("PAUSE");
    system("CLS");
    }

}

int main(){

    flight f1("F1","Delhi","Mumbai",12,10,100,200,300);
    flight f2("F2","Kolkata","Chennai",16,11,1200,2200,3200);
    flight f3("F3","Chennai","Delhi",17,13,1300,2300,3300);
    flight f4("F4","Mumbai","Kolkata",9,6,1600,2600,3600);
    flight f5("F5","Delhi","Kolkata",9,6,1600,2600,3600);
    flight f6("F6","Delhi","Chennai",11,7,2600,3600,4600);
    flight f7("F7","Delhi","Mumbai",14,10,1800,2800,3800);
    flight f8("F8","Kolkata","Chennai",17,13,13200,23200,33200);
    flight f9("F9","Chennai","Delhi",18,13,3300,4300,5300);
    flight f10("F10","Mumbai","Kolkata",19,16,11600,21600,31600);
    flight f11("F11","Delhi","Kolkata",20,17,11600,21600,31600);
    flight f12("F12","Delhi","Chennai",21,16,1500,2500,3500);
    flight f13("F13","Delhi","Mumbai",22,20,1400,2200,1300);
    flight f14("F14","Kolkata","Chennai",14,11,13200,23200,33200);
    flight f15("F15","Chennai","Delhi",17,12,3300,5300,6300);
    flight f16("F16","Mumbai","Kolkata",18,16,1400,2400,3300);
    flight f17("F17","Delhi","Kolkata",4,1,16300,26300,33600);
    flight f18("F18","Delhi","Chennai",5,2,12600,8600,9600);

    flight **total_flights=new flight*[6];
    total_flights[0]=&f1;
    total_flights[1]=&f2;
    total_flights[2]=&f3;
    total_flights[3]=&f4;
    total_flights[4]=&f5;
    total_flights[5]=&f6;

    employee e1("Abhinav",30,"Ab@gmail.com",981177703 ,"Pilot",11,"AirIndia");
    employee e2("Abhi",31,"Ab1@gmail.com",888077703 ,"Co Pilot",12,"AirIndia");
    employee e3("Rahul",29,"Ra@gmail.com",731177703 ,"Crew",13,"AirIndia");
    employee e4("Manan",32,"Ma@gmail.com",981177773 ,"Crew",14,"AirIndia");
    employee e5("Hiten",25,"Hi@gmail.com",80951777 ,"Crew",15,"AirIndia");
    employee e6("Chandeep",36,"Ch@gmail.com",806577773 ,"Crew",16,"AirIndia");

    employee list_of_employees[6];

    list_of_employees[0]=e1;
    list_of_employees[1]=e2;
    list_of_employees[2]=e3;
    list_of_employees[3]=e4;
    list_of_employees[4]=e5;
    list_of_employees[5]=e6;

    company c1("AirIndia",total_flights,list_of_employees);

    total_flights[0]=&f7;
    total_flights[1]=&f8;
    total_flights[2]=&f9;
    total_flights[3]=&f10;
    total_flights[4]=&f11;
    total_flights[5]=&f12;

    employee e7("Nikita",33,"Ni@gmail.com",863277703 ,"Pilot",17,"AirAsia");
    employee e8("Priyanka",27,"Pr@gmail.com",783577773 ,"Co Pilot",18,"AirAsia");
    employee e9("Riya",24,"Ri@gmail.com",809517728 ,"Crew",19,"AirAsia");
    employee e10("Abhiraj",38,"Ab2@gmail.com",806545773 ,"Crew",20,"AirAsia");
    employee e11("Vansh",31,"Va1@gmail.com",863456703 ,"Crew",21,"AirAsia");
    employee e12("Vaanya",24,"Va@gmail.com",783589773 ,"Crew",22,"AirAsia");

    list_of_employees[0]=e7;
    list_of_employees[1]=e8;
    list_of_employees[2]=e9;
    list_of_employees[3]=e10;
    list_of_employees[4]=e11;
    list_of_employees[5]=e12;

    company c2("AirAsia",total_flights,list_of_employees);

    total_flights[0]=&f13;
    total_flights[1]=&f14;
    total_flights[2]=&f15;
    total_flights[3]=&f16;
    total_flights[4]=&f17;
    total_flights[5]=&f18;

    employee e13("Abeer",33,"Ab4@gmail.com",863277703 ,"Pilot",23,"Indigo");
    employee e14("Niharika",27,"Ni1@gmail.com",782377773 ,"Co Pilot",24,"Indigo");
    employee e15("Kshitij",24,"Ks@gmail.com",899578728 ,"Crew",25,"Indigo");
    employee e16("Vanshika",38,"Va3@gmail.com",999845773 ,"Crew",26,"Indigo");
    employee e17("Armaan",31,"Ar@gmail.com",973456703 ,"Crew",27,"Indigo");
    employee e18("Sonali",23,"So@gmail.com",773589773 ,"Crew",28,"Indigo");

    list_of_employees[0]=e13;
    list_of_employees[1]=e14;
    list_of_employees[2]=e15;
    list_of_employees[3]=e16;
    list_of_employees[4]=e17;
    list_of_employees[5]=e18;

    company c3("Indigo",total_flights,list_of_employees);

    company total_company[3];
    total_company[0]=c1;
    total_company[1]=c2;
    total_company[2]=c3;

    login["harshitgoel413@gmail.com"]=58;
    passenger p2("Harshit",19,"harshitgoel413@gmail.com",90347);
    details["harshitgoel413@gmail.com"]=p2;
    vector<pair2> flight_names=get_flight_name(total_company,"Delhi","Chennai");
    book_ticket(flight_names,"AirIndia",2,p2);

    login["diprachaudhry18@gmail.com"]=46;
    passenger p3("Dipra",19,"diprachaudhry18@gmail.com",98798);
    details["diprachaudhry18@gmail.com"]=p3;
    vector<pair2> flight_names1=get_flight_name(total_company,"Delhi","Chennai");
    book_ticket(flight_names,"AirIndia",2,p3);

    int choice=0;
    while(choice!=-1){
        system("Color F3");
        int digit;
        cout<<"\t\t\tWELCOME TO AIR TICKET BOOKING SYSTEM"<<endl<<endl ;
        cout<<"\t\t\t    Select the desired view"<<endl<<endl<<endl<<endl;
        cout<<"Press 1 for customer."<<endl;
        cout<<"Press 2 for admin."<<endl;
        cout<<"Press any other digit to exit."<<endl;
        cin>>digit;

        system("CLS");

        if(digit==1){
            cout<<"Press 1 to login."<<endl;
            cout<<"Press 2 to sign up."<<endl;
            cout<<"Press any other key to exit."<<endl;
            int n;
            cin>>n;

            system("CLS");

            if(n==1){
                string email;
                int password;
                cout<<"Enter email id   :- ";
                cin>>email;
                cout<<endl<<"Enter password    :- ";
                cin>>password;

                //system("PAUSE");
                system("CLS");

                if(login.count(email)>0){
                    if(login[email]==password){
                        cout<<"Logged in successfully!"<<endl<<endl<<endl;
                        cout<<"Press 1 to book a ticket."<<endl;
                        cout<<"Press 2 to print a previously booked ticket."<<endl;
                        cout<<"Press 3 to unbook a ticket."<<endl;
                        int c;
                        cin>>c;

                        system("CLS");
                        if(c==1){
                            passenger p=details[email];
                            string source,destination;
                            cout<<"Enter starting location : " ;
                            cin>>source ;
                            cout<<"Enter destination : " ;
                            cin>>destination ;

                            cout<<endl;
                            vector<pair2>v=get_flight_name(total_company,source,destination);

                            for(int i=0;i<3;i++){
                                int x=get_flight_schedule(total_company[i],source,destination);
                                if(x==0){
                                    continue;
                                }
                            }

                            system("PAUSE") ;
                            system("CLS");

                            cout<<"Enter C to compare flight rates."<<endl<<endl;
                            char x;
                            cin>>x;

                            if(x=='C'){
                                compare_rates(v);
                            }
                            cout<<"Enter company name to book tickets :- "<<endl;
                            string Company_name;
                            cin>>Company_name;

                            system("CLS");
                            cout<<"Enter 1 for Economy "<<endl<<"Enter 2 for Executive "<<endl<<"Enter 3 for Business "<<endl;
                            int digit;
                            cin>>digit;

                            system("PAUSE") ;
                            system("CLS");
                            book_ticket(v,Company_name,digit,p);

                            system("PAUSE") ;
                            system("CLS");
                            cout<<endl<<"Your ticket is :- "<<endl;
                            print_ticket(p);
                            system("PAUSE") ;
                            system("CLS");

                        }
                        else if(c==2){
                            cout<<"Enter pnr number of the ticket. ";
                            int pnr;
                            cin>>pnr;

                            system("CLS");
                            pair1 object=ourMap[pnr];
                            passenger *P=object.p;
                            print_ticket(*P);

                            system("PAUSE");
                            system("CLS");
                        }
                        else if(c==3){
                                int num;
                                cout<<"Enter PNR Number."<<endl;
                                cin>>num;

                                unbook_flight(num);
                        }
                    }
                    else{
                        cout<<"The password is incorrect."<<endl;
                        system("PAUSE");
                        system("CLS");
                    }
                }
                else{
                    cout<<"The email is not registered."<<endl;
                    system("PAUSE");
                    system("CLS");
                }
            }
            else if(n==2){
                                string name,mail,source,destination;
                                int age,phNo,password;
                                cout<<"Enter name : " ;
                                cin>>name ;

                                cout<<"Enter age : " ;
                                cin>>age ;

                                cout<<"Enter email : " ;
                                cin>>mail ;

                                cout<<"Enter password :";
                                cin>>password;

                                if(login.count(mail)>0){
                                    cout<<"Already registered!"<<endl;
                                    continue;
                                }
                                else{
                                    login[mail]=password;
                                }

                                cout<<"Enter phone number : " ;
                                cin>>phNo ;

                                 passenger p1(name , age , mail , phNo ) ;

                                 details[mail]=p1;
                                cout<<"Do you want to book a ticket? Y/N"<<endl;
                            char c;
                            cin>>c;
                            if(c=='Y'){


                                cout<<"Enter starting location : " ;
                                cin>>source ;
                                cout<<"Enter destination : " ;
                                cin>>destination ;

                                cout<<endl;
                                vector<pair2 >v=get_flight_name(total_company,source,destination);


                                system("PAUSE") ;
                                system("CLS");

                                for(int i=0;i<3;i++){
                                   int x= get_flight_schedule(total_company[i],source,destination);
                                   if(x==0){
                                        continue;
                                   }
                                }

                                system("PAUSE") ;
                                system("CLS");

                                cout<<"Enter C to compare flight rates."<<endl<<endl;
                                char x;
                                cin>>x;

                                if(x=='C'){
                                    compare_rates(v);
                                }
                                cout<<"Enter company name to book tickets :- "<<endl;
                                string Company_name;
                                cin>>Company_name;

                                system("CLS");
                                cout<<"Enter 1 for Economy "<<endl<<"Enter 2 for Executive "<<endl<<"Enter 3 for Business "<<endl;
                                int digit;
                                cin>>digit;

                                system("PAUSE") ;
                                system("CLS");
                                book_ticket(v,Company_name,digit,p1);

                                system("PAUSE") ;
                                system("CLS");
                                cout<<endl<<"Your ticket is :- "<<endl;
                                print_ticket(p1);
                                system("PAUSE") ;
                                system("CLS");
                        }
                        system("PAUSE") ;
                        system("CLS");
            }
            else{

                break;
            }
        }
        else if(digit==2){
            cout<<"Want to view passenger details Press Y"<<endl;
            char c;
            cin>>c;
            if(c=='Y'){
                cout<<"Enter flight name."<<endl;
                string flight_name;
                cin>>flight_name;

                system("CLS");
                admin(total_company,flight_name);
            }

            system("PAUSE") ;
            system("CLS");
            cout<<"To view employee details Press Y"<<endl;
            cin>>c;
            if(c=='Y'){
                cout<<"Enter company name."<<endl;
                string comp_name;
                cin>>comp_name;

                system("CLS");
                admin(total_company,"\0",comp_name);
            }
            system("PAUSE") ;
            system("CLS");
        }
        else{
            break;
        }
   }
    system("CLS");
    cout<<"Termination of program."<<endl;
}

