# ***Money Transactions System***

## Overview:
this system serves as a transactions system where one can send and recieve money via an E-wallet.

## Getting started:
all you need to have in order to run this program is any IDE that supports C++ !
                    
## Use case scenario:
a user will be asked to create an account if they don't have one. A menu pops up showing the programs services.
the user can add any credit card if it has a minimum of 100$. Once the card is added , the user can do any of the transactions shown in the menu.

## UML diagram:
![UML diagram](https://github.com/Heba-Islam/Money-Transactions-System/assets/138635164/84ece959-7f9b-4e16-a2eb-f94e53d8dfbf)

## OOP topics used :
***Inheritance*** :

the *AccountServices* class inherits from the abstract class *IAccountServices*.

![Parent and Child classes](https://github.com/Heba-Islam/Money-Transactions-System/assets/138635164/12cdcefc-1b89-44fd-b6c6-5e951cc5c5dc)

***Composition*** :

the *AccountServices* class uses an instance of *Account* class.

![Composition](https://github.com/Heba-Islam/Money-Transactions-System/assets/138635164/1e0b74f2-c31b-4d1c-b894-023eb6477d09)

***Overloading*** :

the ShowBalance function is overloaded, one version takes no arguments and the other takes a card as an argument.

![overloaded function](https://github.com/Heba-Islam/Money-Transactions-System/assets/138635164/af95c86d-5558-4fbd-a962-9f50addef43a)

***Polymorphism*** :

the extra fees associated with sending money differ depending on the type of card used, so the function *SendMoney* was overriden in classes *MasterCard* and *VisaCard* -both inherit from the interface *ICardPayment*. And in the function *SendMoney* in class *AccountServices*, a pointer of *ICardPayment* was instantiated and the appropriate SendMoney function was applied based on the type of card.

![polymorphism](https://github.com/Heba-Islam/Money-Transactions-System/assets/138635164/73b70a5b-919f-49e5-bafe-d3f5218a8cf7)

# [demonstration](https://drive.google.com/file/d/13JyNvJF-jx46K9zNku52Kk2dEwyag1Vz/view?usp=drivesdkhttps://github.com/Heba-Islam/Money-Transactions-System)










