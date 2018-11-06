#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <ctype.h>
#include <process.h>
#include <dos.h>

struct Acc_Num {
  int n1, n2, n3, n4;
  void make_accno() {
    randomize();
    n1 = rand()%9999 + 1000;
    n2 = rand()%9999 + 1000;
    n3 = rand()%9999 + 1000;
    n4 = rand()%9999 + 1000;
  }
};
class account {
  //private:
  public:
    Acc_Num Acc_number;
    char *Holder_name;
    char *Username;
    char *Password;
    long int Expire_Year, CVV ,Cash ,pin, Index, regd;
    void Register_acc();
    account(){regd=0;}
  //public:

}*accs;  //here

void init_graphs();
void Draw_frame();
void Splash_scr();
void Login();
int Validate_Pin(int);  //return 1 when pass, else 0 when fail
int Validate_CVV(int);
void Menu(int);
void information(int);
void Withdraw(int);
void Deposit(int);
void Transfer(int);

void account :: Register_acc() {
  char *pass_conf;
  init_graphs();
  settextstyle(9, 0, 3);  outtextxy(250, 70, "REGISTER");
  gotoxy(16, 10); cout<<"Holder Name: ";  gotoxy(35, 10); gets(Holder_name);   //Holder name
  Acc_number.make_accno();                                                    //Account no.
  randomize();  CVV = rand()%999; Expire_Year = 2018 + rand()%40+10;           //CVV --- Expire Year
  gotoxy(16, 12);  cout<<"Username: ";  gotoxy(35, 12);  cin>>Username;        //Username
  inpin:  gotoxy(16, 14);  cout<<"PIN(4-Digit): ";  gotoxy(35, 14);  cin>>pin;   //Pin
  if (pin > 9999 || pin < 1000) { //pin error (larger or smaller than 4 digits)
    gotoxy(26, 20);  cout<<"Only 4 digit numbers allowed";  gotoxy(28, 21);  cout<<"Press Enter to continue";
    getch();  gotoxy(16, 14); cout<<"PIN(4-Digit): "; for (int i = 0; i < 20; i++) { cout<<char(255);}
    gotoxy(26, 20); for (i = 0; i < 30; i++) { cout<<char(255);}  gotoxy(28, 21); for (i = 0; i < 30; i++) { cout<<char(255);}
    goto inpin;
  }
  inpass:
  gotoxy(16, 16);  cout<<"Password: ";  gotoxy(35, 16);  cin>>Password;        //Password
  gotoxy(16, 18);  cout<<"Confirm Password: ";  gotoxy(35, 18);  cin>>pass_conf;
  if (strcmp(Password, pass_conf) != 0) { //password error (conf_pass != pass)
    gotoxy(24, 20);  cout<<"Confirm Password does not match"; gotoxy(28, 21); cout<<"Press Enter to continue";
    getch(); gotoxy(16, 16); for (int i = 0; i < 35; i++) { cout<<char(255);} gotoxy(16,18); for (i = 0; i < 35; i++) { cout<<char(255);}
    gotoxy(24, 20); for (i = 0; i < 35; i++) { cout<<char(255);}  gotoxy(28, 21); for (i = 0; i < 35; i++) { cout<<char(255);}
    goto inpass;
  }
  //Register successfull
  closegraph();
  init_graphs();
  settextstyle(1, 0, 3);  outtextxy(180, 200, "Registered Successfully");
  gotoxy(24, 21);  cout<<"Your CVV is "<<CVV<<"(Do not forget)";
  gotoxy(26, 22);  cout<<"Press Enter to continue login";  getch();  Login();
}

int main() {
  /*/ default account initialization
  strcpy(accs[0].Username, "admin");
  strcpy(accs[0].Password, "password");
  strcpy(accs[0].Holder_name, "Admin");
  accs[0].Expire_Year = 2028;
  accs[0].CVV = 123;
  accs[0].Acc_number.n1 = 1234;accs[0].Acc_number.n2 = 5678;accs[0].Acc_number.n3 = 9012;accs[0].Acc_number.n4 = 3456;
  accs[0].regd = 1;
  accs[0].Cash = 18300;
  accs[0].pin = 1234;
  accs[0].Index = 0;
  //default account init. over*/
  // init. not working if declared outside
  Splash_scr();
  Login();
  getch();
  closegraph();
  return 0;
}

void init_graphs() {
  system("CLS");
  int gd = DETECT, gm, errorcode;
  initgraph (&gd, &gm, "");
  errorcode = graphresult();
  if (errorcode != grOk) {
    cout<<"\nGraphics error: "<<grapherrormsg(errorcode);
    cout<<"\nPress any key to terminate:";
    getch();
    exit(1);
  }
}
void Draw_frame() {
  line(10, 10, 630, 10);  line(10, 14, 630, 14);  //top horizontal
  line(10, 10, 10, 390);  line(14, 10, 14, 390);  //left vertical
  line(10, 390, 630, 390);  line(10, 386, 630, 386);  //bottom horizontal
  line(630, 10, 630, 390); line(626, 10, 626, 390); //right vertical
}
void Splash_scr() {
  init_graphs();
  settextstyle(10, 0, 4); outtextxy(270, 185, "ATM");
  settextstyle(11, 0, 3); outtextxy(260, 250, "Your Money Portal");
  Draw_frame();
  gotoxy(30, 25); cout<<"Press Enter to continue";  getch();  closegraph();
}
void Login() {
  char usrnm[20], passw[20], conf;
  init_graphs();
  Draw_frame();
  settextstyle(9, 0, 3);  outtextxy(250, 70, "LOGIN");
  gotoxy(25, 12); cout<<"Username";  gotoxy(34, 12); cout<<char(179);  cin>>usrnm;  //username
  gotoxy(25, 14);  cout<<"Password";  gotoxy(34, 14);  cout<<char(179);  cin>>passw;  //password
  for (int i = 0; i < 10; i++) {  //find if any of the usrnm and pswd of any account matches and go to menu and end
   if (strcmp(usrnm, accs[i].Username) == 0) {
      if (strcmp(passw, accs[i].Password) == 0) {
        closegraph();
	      Menu(accs[i].Index);
	      break;
      }
    }
  }
  if (i == 10) {  //if loop is over and i == 10 (i.e. all the accounts are checked and no one matches) then show error
    gotoxy(24, 16);  cout<<"Invalid Username or Password";
    gotoxy(16, 17);  cout<<"['r' for register, 't' for retry, 'c' for cancel]";
    gotoxy(35, 18);  cout<<char(179);  cin>>conf;  tolower(conf);
    if (conf == 'r') {//to be edited
      for (int i = 0; accs[i].regd == 1; i++);
      accs[i].Index = i;  accs[i].Register_acc();
    } else if (conf == 't') {
      closegraph(); Login();
    } else if (conf == 'c'){
      gotoxy(30, 25); cout<<"Press any key to exit"; getch();  exit(0);
    }
  }
}
void Menu(int index) {
  init_graphs();
  Draw_frame();
  settextstyle(3, 0, 5);  outtextxy(270, 190, "MENU");
  //menu options output
  settextstyle(6, 0, 1);
  outtextxy(100, 150, "1 Withdraw");  outtextxy(440, 150, "2 Deposit"); outtextxy(100, 250, "3 Transfer");  outtextxy(440, 250, "4 Information");
  outtextxy(30, 420, "5 Exit"); outtextxy(540, 420, "6 Logout");
  int menu_opt;
  menu_opt = getch();
  switch (menu_opt) {
    case 1:{
      int val_pin = 0;  val_pin = Validate_Pin(index);
      if (val_pin == 1) {
        closegraph(); Withdraw(index);
      } else {
        settextstyle(1, 0, 4);  outtextxy(180, 200, "Pin Validation Failed");
        gotoxy(27, 25); cout<<"You have been logged out";
        getch(); Login();
      }
      break;
    }
    case 2:{
      int val_pin = 0;
      val_pin = Validate_Pin(index);
      if (val_pin == 1) {
        closegraph(); Deposit(index);
        getch();  Menu(index);
      } else {
        settextstyle(1, 0, 4);  outtextxy(180, 200, "Pin Validation Failed");
        gotoxy(27, 25); cout<<"You have been logged out";
        getch();  Login();
      }
      break;
    }
    case 3:{
      int val_pin = 0;
      val_pin = Validate_Pin(index);
      if (val_pin == 1) {
        closegraph(); Transfer(index);
        getch();  Menu(index);
      } else {
        settextstyle(1, 0, 4);  outtextxy(180, 200, "Pin Validation Failed");
        gotoxy(27, 25); cout<<"You have been logged out";
        getch();  Login();
      }
      break;
    }
    case 4:{
      int val_pin = 0;
      val_pin = Validate_Pin(index);
      if (val_pin == 1) {
        information(index);
        getch();  closegraph(); Menu(index);
      } else {
        settextstyle(1, 0, 4);  outtextxy(180, 200, "Pin Validation Failed");
        gotoxy(27, 25); cout<<"You have been logged out";
        getch();  Login();
      }
      break;
    }
    case 5:{
      closegraph(); Splash_scr(); exit(0);
      break;
    }
    case 6:{
      closegraph(); Login();
      break;
    }
  }
}
void information(int i) { //i == index of account
  init_graphs();
  cout<<"\n\nHolder Name: "<<accs[i].Holder_name;
  cout<<"\n\nAccount Number: "<<accs[i].Acc_number.n1<<" "<<accs[i].Acc_number.n2<<" "<<accs[i].Acc_number.n3<<" "<<accs[i].Acc_number.n4;
  cout<<"\n\nExpire Year: "<<accs[i].Expire_Year;
  cout<<"\n\nUsername: "<<accs[i].Username;
  cout<<"\n\nCash: $."<<accs[i].Cash;
}
int Validate_Pin(int index) {
  system("CLS");
  int chances = 3;
  do {
    int pin = 0;
    gotoxy(32, 12); cout<<"Enter Pin";  gotoxy(35, 14); cout<<char(196)<<char(196)<<char(196)<<char(196); gotoxy(35, 14); cin>>pin;
    chances--;
    if (pin != accs[index].pin) {
      gotoxy(33, 15); cout<<"Incorrect Pin";
      gotoxy(32, 16); cout<<chances<<" chances left";
      gotoxy(30, 17); cout<<"Press Enter to Retry";
      getch();
    } else if (pin == accs[index].pin) {
      return 1;
    }
  } while(chances > 0);
  return 0;
}
int Validate_CVV(int index) {
  system("CLS");
  int chances = 5;
  do {
    int CVV = 0;
    gotoxy(32, 12); cout<<"Enter CVV";  gotoxy(36, 14); cout<<char(196)<<char(196)<<char(196);  gotoxy(36, 14); cin>>CVV;
    chances--;
    if (CVV != accs[index].CVV) {
      gotoxy(33, 15);
      cout<<"Incorrect CVV";
      gotoxy(32, 16);
      cout<<chances<<" chances left";
      gotoxy(30, 17);
      cout<<"Press Enter to Retry";
      getch();
    } else if (CVV == accs[index].CVV) {
      return 1;
    }
  } while(chances > 0);
  return 0;
}
void Withdraw(int index) {
  long int Withdraw_amt;
  int val_CVV = 0;
  init_graphs();
  Draw_frame();
  settextstyle(9, 0, 3);  outtextxy(210, 70, "WITHDRAW");
  settextstyle(3, 0, 1);  outtextxy(250, 220, "Enter Amount");
  gotoxy(36, 17); cout<<"$."; cin>>Withdraw_amt;
  val_CVV = Validate_CVV(index);
  if (val_CVV == 1) {
    if (accs[index].Cash >= Withdraw_amt) {
      accs[index].Cash -= Withdraw_amt;
      init_graphs();
      settextstyle(5, 0, 5);  outtextxy(175, 200, "Processing Withdraw");
      gotoxy(30, 25); for (int i = 0; i < 24; i++) {  cout<<char(223);  delay(50); } //process bar
      settextstyle(1, 0, 3);  outtextxy(175, 200, "Withdraw Successfull");
      gotoxy(30, 25); cout<<"Withdraw of $."<<Withdraw_amt<<" Successfull";
      getch();  Menu(index);
    } else {
      system("CLS");
      gotoxy(25, 20);
      cout<<"Insufficient Balance in your account";
      getch();
      Menu(index);
    }
  } else {
    settextstyle(4, 0, 4);  outtextxy(190, 200, "Incorrect CVV");
    gotoxy(27, 25); cout<<"You have been logged out";
    getch();  Login();
  }
}
void Deposit(int index) {
  long int Deposit_amt;
  init_graphs();
  Draw_frame();
  settextstyle(9, 0, 3);  outtextxy(210, 70, "DEPOSIT");
  settextstyle(3, 0, 1);  outtextxy(200, 220, "Enter Deposit Amount");
  gotoxy(36, 17); cout<<"$."; cin>>Deposit_amt;
  int val_CVV = 0;
  val_CVV = Validate_CVV(index);
  if (val_CVV == 1) {
    accs[index].Cash += Deposit_amt;
    init_graphs();
    settextstyle(5, 0, 5);  outtextxy(175, 200, "Processing Deposit");
    gotoxy(30, 25); for (int i = 0; i < 24; i++) {  cout<<char(223);  delay(50);} //process bar
    settextstyle(1, 0, 3);  outtextxy(175, 200, "Deposit Successfull");
    gotoxy(30, 25);  cout<<"Deposit of $."<<Deposit_amt<<" Successfull";
  } else {
    settextstyle(4, 0, 4);  outtextxy(190, 200, "Incorrect CVV");
    gotoxy(27, 25); cout<<"You have been logged out";
    getch();  Login();
  }
}
void Transfer(int index) {
  long int Transfer_amt;
  int an1, an2, an3, an4;
  init_graphs();
  Draw_frame();
  settextstyle(9, 0, 3);  outtextxy(210, 70, "TRANSFER");
  settextstyle(3, 0, 1);  outtextxy(200, 220, "Enter Transfer Amount");
  gotoxy(36, 17); cout<<"$."; cin>>Transfer_amt;
  outtextxy(80, 270, "Enter Reciever Account Number [seperate 4 digits by spaces]");
  gotoxy(36, 14); cin>>an1>>an2>>an3>>an4;
  for (int i = 0; accs[i].Acc_number.n1 != an1 && accs[i].Acc_number.n2 != an2 && accs[i].Acc_number.n3 != an3 && accs[i].Acc_number.n4 != an4; i++);
  if (i >= 10) {
    gotoxy(27, 25); cout<<"Account "<<an1<<" "<<an2<<" "<<an3<<" "<<an4<<" not found";
    closegraph(); Menu(index);
  } else {
    int val_CVV = 0;
    val_CVV = Validate_CVV(index);
    if (val_CVV == 1) {
      accs[index].Cash -= Transfer_amt;
      accs[i].Cash += Transfer_amt;
      init_graphs();
      settextstyle(5, 0, 5);  outtextxy(175, 200, "Processing Transfer");
      gotoxy(30, 25); for (int i = 0; i < 24; i++) {  cout<<char(223);  delay(50); }
      init_graphs();
      settextstyle(1, 0, 3);  outtextxy(175, 200, "Transfer Successfull");
      gotoxy(20, 25); cout<<"Transfer of $."<<Transfer_amt<<" to account "<<an1<<" "<<an2<<" "<<an3<<" "<<an4<<" Successfull";
    } else {
      settextstyle(4, 0, 4);  outtextxy(190, 200, "Incorrect CVV");
      gotoxy(27, 25); cout<<"You have been logged out";
      getch();  Login();
    }
  }
}
