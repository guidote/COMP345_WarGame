#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../LoggingObserver/LoggingObserver.h"

using namespace std;
/// Forward declaration of GameEngine
class GameEngine;
/// Forward declaration of Player
class Player;
/// Forward declaration of Territory
class Territory;

/****************************** Order *******************************/
/**
 Abstract Class That is the Base Class off all subsequent types of Orders.
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Order :public Iloggable, public Subject {
    public:
        /**
        Default constructor
        */
        Order();

        /**
        Parameterized Constructor
        @param bool that represents the validated status and a string that is the type of the Order
        */
        Order(bool v, string s);

        /**
        Copy constructor that creates a deep copy
        @param Order reference
        @return Order created
        */
        Order(const Order& o);

        /// Destructor
        virtual ~Order();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Order reference that will be copied and assigned
        @return Order reference
        */
        Order& operator = (const Order& D);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Order as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Order& order);

        /**
        Accessor for the string type of the Order
        @param None
        @return string that is the type of the Order
        */
        virtual string getDescription();

        /**
        Accessor for the boolean validated status of the Order
        @param None
        @return bool that is the validated status
        */
        bool getValidated();

        /**
        Accessor for the static GameEngine member of the class Order
        @param None
        @return GameEngine pointer
        */
        static GameEngine* getGameEngine();

        /**
        Mutator for the type/description of the Order
        @param string that is the type/description of the Order
        @return None
        */
        void setDescription(string d);

        /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
        Mutator for the GameEngine of the Order static data member
        @param GamenEngine pointer
        @return None
        */
        static void setGameEngine(GameEngine* gamePlaying);

        /**
         Pure virtual function to be implemented in all subclasses of Order
         */
        virtual void validate() = 0;

        /**
        Pure virtual function to be implemented in all subclasses of Order
        */
        virtual void execute() = 0;

        /**
        Method inherited from Iloggable, to be implement in subclasses of Order
        */
        string stringToLog();

        /// Status of validation
        bool validated;
        /// Description of the Order
        string description;
        /// Game Engine pointer for Order subclasses execution and validation
        static GameEngine* game;
};

/****************************** Deploy *******************************/
/**
  Order Deploy Class that deploys armies of a Player into a Player's Territory
  Inherits from Order which
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Deploy : public Order {
    public:
        /**
        Default constructor
        */
        Deploy();

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to
        */
        Deploy(Player* p);

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to and Territory pointer
        */
        Deploy(Player* p, Territory* target);

        /**
        Copy constructor that creates a deep copy
        @param Order reference
        @return Order created
        */
        Deploy(const Deploy& original);

        /**
         Destructor
         deletes object in Heap and sets data member pointers to null
         */
        ~Deploy();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Deploy reference that will be copied and assigned
        @return Deploy reference
        */
        Deploy& operator = (const Deploy& D);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Deploy as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Deploy& deploy);

        /**
        Accessor for the string description of the Order subclass
        @param None
        @return string that is the description of the Order subclass
        */
        string getDescription();

        /**
         Accessor for the boolean validated status of the Order subclass
         @param None
         @return bool that is the validated status
         */
        bool getValidated();

        /**
        Accessor for the Territory pointer attribute that is the Target of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getTarget();

        /**
        Accessor for the Player pointer of the Player issuing the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getPlayerIssuing();

        /**
        Accessor for the number of armies to advance
        @param None
        @return int armies
        */
        int getNumToDeploy();

        /**
         Mutator for the description of the Order subclass Object
         @param string that is the description of the Order
         @return None
         */
        void setDescription(string d);

        /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
         Method to validate the Order Subclass Object by checking the parameters of the Object
         Called upon by execute()
         @param none
         @return none
         */
        void validate();

        /**
         Method to execute the Order Subclass Object by checking the parameters of the Object
         Calls validate() before pursuing the execution. Calls StringTolog() once the execution is completed
         @param none
         @return none
         */
        void execute();

        /**
         Method inherited from Iloggable to generate a output when an Order will be executed to
         notify the LogObserver and print an entry in the gamelogOutput.txt file
         */
        string stringToLog();
    private:
        /// Player issuing the current Order subclass object
        Player* playerIssuing;
        /// Territory targeted by the Order subclass object
        Territory* target;
        /// Number of armies to Deploy to the target territory
        int numToDeploy;
};

/****************************** Advance *******************************/
/**
  Order Advance Class that makes armies of a Player move unto a new Territory or Attack an Enemy Territory nearby
  Inherits from Order which
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Advance : public Order {
    public:
        /**
        Default constructor
        */
        Advance();

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to and the string that determines the type of advance
        */
        Advance(Player* p, string input);

        /**
        Parameterized Constructor 2
        @param Player pointer that is the Player to which the Order belongs to and 2 Territory pointers
        */
        Advance(Player* p, Territory* origin, Territory* target);

        /**
        Copy constructor that creates a deep copy
        @param Advance reference
        @return Advance created
        */
        Advance(const Advance& original);

        /**
        Destructor
        deletes object in Heap and sets data member pointers to null
        */
        ~Advance();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Advance reference that will be copied and assigned
        @return Advance reference
        */
        Advance& operator = (const Advance& d);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Advance as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Advance& advance);

        /**
        Supporting function to the execution of the Attack outcome
        */
        int deathCalculation(int qty, double probability);

        /**
        Accessor for the string description of the Order subclass
        @param None
        @return string that is the description of the Order subclass
        */
        string getDescription();

        /**
        Accessor for the boolean validated status of the Order Subclasses
        @param None
        @return bool that is the validated status
        */
        bool getValidated();

        /**
        Accessor for the Territory pointer attribute that is the Target of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getTarget();

        /**
        Accessor for the Territory pointer attribute that is the Origin of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getOrigin();

        /**
        Accessor for the Player pointer of the Player issuing the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getPlayerIssuing();


        /**
        Accessor for the number of armies to advance
        @param None
        @return int armies
        */
        int getNumToAdvance();

        /**
        Mutator for the description of the Order subclass Object
        @param string that is the description of the Order
        @return None
        */
        void setDescription(string d);

        /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
        Method to validate the Order Subclass Object by checking the parameters of the Object
        Called upon by execute()
        @param none
        @return none
        */
        void validate();

        /**
        Method to execute the Order Subclass Object by checking the parameters of the Object
        Calls validate() before pursuing the execution. Calls StringTolog() once the execution is completed
        @param none
        @return none
        */
        void execute();

        /// string to keep track of the results of the Advance Order following the validate()
        string validateResult;

        /**
        Method inherited from Iloggable to generate a output when an Order will be executed to
        notify the LogObserver and print an entry in the gamelogOutput.txt file
        */
        string stringToLog();

    private:
        /// Player issuing the current Order subclass object
        Player* playerIssuing;
        /// Territory where the Order subclass object takes origin from
        Territory* origin;
        /// Territory targeted by the Order subclass object
        Territory* target;
        /// Number of Armies to Advance
        int numToAdvance;
};

/****************************** Airlift *******************************/
/**
  Order Airlift Class that takes armies of a Player from a Territory to another Territory
  Playable only through the use of a Card
  Inherits from Order which
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Airlift : public Order {
    public:
        /**
        Default constructor
        */
        Airlift();

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to
        */
        Airlift(Player* p);

        /**
        Parameterized Constructor 2
        @param Player pointer that is the Player to which the Order belongs to and 2 Territory pointers
        */
        Airlift(Player* p, Territory* origin, Territory* target);

        /**
        Copy constructor that creates a deep copy
        @param Airlift reference
        @return Airlift created
        */
        Airlift(const Airlift& original);

        /**
        Destructor
        deletes object in Heap and sets data member pointers to null
        */
        ~Airlift();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Airlift reference that will be copied and assigned
        @return Airlift reference
        */
        Airlift& operator = (const Airlift &D);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Airlift as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Airlift& airflit);

        /**
        Accessor for the string description of the Order subclass
        @param None
        @return string that is the description of the Order subclass
        */
        string getDescription();

        /**
        Accessor for the boolean validated status of the Order Subclass
        @param None
        @return bool that is the validated status
        */
        bool getValidated();

        /**
        Accessor for the Territory pointer attribute that is the Target of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getTarget();

        /**
        Accessor for the Territory pointer attribute that is the Origin of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getOrigin();

        /**
        Accessor for the Player pointer of the Player issuing the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getPlayerIssuing();

        /**
        Accessor for the number of armies to be Arilifted
        @param None
        @return int armies
        */
        int getNumToAirlift();

        /**
        Mutator for the description of the Order subclass Object
        @param string that is the description of the Order
        @return None
        */
        void setDescription(string d);

        /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
        Method to validate the Order Subclass Object by checking the parameters of the Object
        Called upon by execute()
        @param none
        @return none
        */
        void validate();

        /**
         Method to execute the Order Subclass Object by checking the parameters of the Object
         Calls validate() before pursuing the execution. Calls StringTolog() once the execution is completed
         @param none
         @return none
         */
        void execute();

        /**
        Method inherited from Iloggable to generate a output when an Order will be executed to
        notify the LogObserver and print an entry in the gamelogOutput.txt file
        */
        string stringToLog();

    private:
        /// Player issuing the current Order subclass object
        Player* playerIssuing;
        /// Territory targeted by the Order subclass object
        Territory* target;
        /// Territory where the Order subclass object takes origin from
        Territory* origin;
        /// Number of Armies to Airlift from the origin to the target
        int numToAirlift;
};

/****************************** Bomb *******************************/
/**
  Order Bomb Class sends a bomb from a Territory to an Enemy's Territory
  Playable only through the use of a Card
  Inherits from Order which
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Bomb : public Order {
    public:
        /**
        Default constructor
        */
        Bomb();

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to
        */
        Bomb(Player* p);

        /**
        Parameterized Constructor 2
        @param Player pointer that is the Player to which the Order belongs to and 2 Territory pointers
        */
        Bomb(Player* p, Territory* origin, Territory* target);

        /**
        Copy constructor that creates a deep copy
        @param Bomb reference
        @return Bomb created
        */
        Bomb(const Bomb& original);

        /**
        Destructor
        deletes object in Heap and sets data member pointers to null
        */
        ~Bomb();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Bomb reference that will be copied and assigned
        @return Bomb reference
        */
        Bomb& operator = (const Bomb& D);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Bomb as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Bomb& bomb);

        /**
        Accessor for the string description of the Order subclass
        @param None
        @return string that is the description of the Order subclass
        */
        string getDescription();

        /**
        Accessor for the boolean validated status of the Order Subclass
        @param None
        @return bool that is the validated status
        */
        bool getValidated();

        /**
        Accessor for the Territory pointer attribute that is the Target of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getTarget();

        /**
        Accessor for the Territory pointer attribute that is the Origin of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getOrigin();

        /**
        Accessor for the Player pointer of the Player issuing the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getPlayerIssuing();

        /**
         Mutator for the description of the Order subclass Object
         @param string that is the description of the Order
         @return None
         */
        void setDescription(string d);

        /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
         Method to validate the Order Subclass Object by checking the parameters of the Object
         Called upon by execute()
         @param none
         @return none
         */
        void validate();

        /**
         Method to execute the Order Subclass Object by checking the parameters of the Object
         Calls validate() before pursuing the execution. Calls StringTolog() once the execution is completed
         @param none
         @return none
         */
        void execute();

        /**
        Method inherited from Iloggable to generate a output when an Order will be executed to
        notify the LogObserver and print an entry in the gamelogOutput.txt file
        */
         string stringToLog();

    private:
        /// Player issuing the current Order subclass object
        Player* playerIssuing;
        /// Territory where the Order subclass object takes origin from
        Territory* origin;
        /// Territory targeted by the Order subclass object
        Territory* target;
};

/****************************** Blockade *******************************/
/**
  Order Blockade Class that doubles the number of Armies on a Territory and passes its ownership to the Neutral Player
  Playable only through the use of a Card
  Inherits from Order which
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Blockade : public Order {
    public:

        /**
        Default constructor
        */
        Blockade();

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to
        */
        Blockade(Player* p);

        /**
       Parameterized Constructor 2
       @param Player pointer that is the Player to which the Order belongs to and 1 Territory pointer
          */
        Blockade(Player* p, Territory* target);

        /**
        Copy constructor that creates a deep copy
        @param Blockade reference
        @return Blockade created
        */
        Blockade(const Blockade& original);

        /**
        Destructor
        deletes object in Heap and sets data member pointers to null
        */
        ~Blockade();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Blockade reference that will be copied and assigned
        @return Blockade reference
        */
        Blockade& operator = (const Blockade& D);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Blockade as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Blockade& blockade);

        /**
        Accessor for the string description of the Order subclass
        @param None
        @return string that is the description of the Order subclass
        */
        string getDescription();

        /**
        Accessor for the boolean validated status of the Order Subclass
        @param None
        @return bool that is the validated status
        */
        bool getValidated();

        /**
        Accessor for the Player pointer of the Player issuing the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getPlayerIssuing();

        /**
        Accessor for the Territory pointer attribute that is the Target of the Order Subclass Object
        @param None
        @return Territory pointer
        */
        Territory* getTarget();

        /**
        Mutator for the description of the Order subclass Object
        @param string that is the description of the Order
        @return None
        */
        void setDescription(string d);

         /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
         Method to validate the Order Subclass Object by checking the parameters of the Object
         Called upon by execute()
         @param none
         @return none
         */
        void validate();

        /**
        Method to execute the Order Subclass Object by checking the parameters of the Object
        Calls validate() before pursuing the execution. Calls StringTolog() once the execution is completed
        @param none
        @return none
        */
        void execute();

        /**
        Method inherited from Iloggable to generate a output when an Order will be executed to
        notify the LogObserver and print an entry in the gamelogOutput.txt file
        */
         string stringToLog();

    private:
        /// Player issuing the current Order subclass object
        Player* playerIssuing;
        /// Territory targeted by the Order subclass object
        Territory* target;
};

/****************************** Negotiate *******************************/
/**
  Order Negotiate Class that creates an Alliance between players
  Playable only through the use of a Card
  Inherits from Order which
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class Negotiate : public Order {
    public:

        /**
        Default constructor
        */
        Negotiate();

        /**
        Parameterized Constructor
        @param Player pointer that is the Player to which the Order belongs to
        */
        Negotiate(Player* p);

        /**
        Parameterized Constructor 2
        @param 2 Player pointers
         */
        Negotiate(Player* p, Player* target);

        /**
        Copy constructor that creates a deep copy
        @param Negotiate reference
        @return Negotiate created
        */
        Negotiate(const Negotiate& original);

        /**
         Destructor
         deletes object in Heap and sets data member pointers to null
         */
        ~Negotiate();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Negotiate reference that will be copied and assigned
        @return Negotiate reference
        */
        Negotiate& operator = (const Negotiate& D);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Negotiate as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Negotiate& negotiate);

        /**
        Accessor for the string description of the Order subclass
        @param None
        @return string that is the description of the Order subclass
        */
        string getDescription();

        /**
         Accessor for the boolean validated status of the Order Subclass
         @param None
         @return bool that is the validated status
         */
        bool getValidated();

        /**
        Accessor for the Player pointer of the Player issuing the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getPlayerIssuing();

        /**
        Accessor for the Player pointer of the Player targeted by the Order subclass Object
        @param None
        @return Player pointer
        */
        Player* getTargetPlayer();

        /**
        Mutator for the description of the Order subclass Object
        @param string that is the description of the Order
        @return None
        */
        void setDescription(string d);

        /**
        Mutator for the validated status boolean
        @param bool that is the new validated status
        @return None
        */
        void setValidated(bool v);

        /**
         Method to validate the Order Subclass Object by checking the parameters of the Object
         Called upon by execute()
         @param none
         @return none
         */
        void validate();

        /**
       Method to execute the Order Subclass Object by checking the parameters of the Object
       Calls validate() before pursuing the execution. Calls StringTolog() once the execution is completed
       @param none
       @return none
       */
        void execute();

        /**
       Method inherited from Iloggable to generate a output when an Order will be executed to
       notify the LogObserver and print an entry in the gamelogOutput.txt file
       */
         string stringToLog();

private:
         /// Player issuing the current Order subclass object
        Player* playerIssuing;
        /// Player targeted by the current Order subclass object
        Player* targetPlayer;
};

/****************************** OrdersList *******************************/
/**
  OrdersList Class that contains all of a Player's Orders
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class OrdersList :public Iloggable, public Subject {
    public:
        /**
        Default constructor
        */
        OrdersList();

        /**
        Parameterized Constructor
        @param Vector of Order pointer
        */
        OrdersList(vector<Order*> vo);

        /**
        Copy Constructor for a deep copy of the Vector's Order pointers and pointed Orders
        @param Vector of Order pointer
        */
        OrdersList(const OrdersList& original);

        /**
        Destructor
        Iterates through the Vector deletes object in Heap and sets pointers to null
        */
        virtual ~OrdersList();

        /**
         Accessor of the Vector or Order pointers
         @param none
         @return vector of Order pointer
         */
        vector<Order*> getOrderList();

        /**
         Mutator for the vector of Order pointers
         @param vector of Order pointers
         @return none
         */
        void setOrderList(vector<Order*> vo);

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Negotiate reference that will be copied and assigned
        @return Negotiate reference
        */
        OrdersList operator = (const OrdersList& original);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Negotiate as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const OrdersList& ordersList);

        /**
         Method used to add an order of the OrderList.
        @param Order pointer
         @return none
         */
        void addOrder(Order* order);

        /**
         Remove Method used to remove an order of the OrderList.
        @param int that is the index of the order pointer to be removed
         */
         void remove(int i);

        /**
         Move Method used to move an order at index i into the position of index j.
        @param two int that are the index of the two pointers to be swapped
         */
         void move(int i, int j);

        /**
         Method inherited from Iloggable to generate a string for the LogObserver to output it into the gamelog file
         */
        string stringToLog();

        /// Vector of Order pointer
        vector<Order*> playerOrderList;
};