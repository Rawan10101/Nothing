#include <iostream>
#include <queue>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string email;
   
public:
    Customer(int id, string customerName, string customerEmail) {
        customerId = id;
        name = customerName;
        email = customerEmail;
       
    }

    int getCustomerId() {
        return customerId;
    }

    string getName() {
        return name;
    }

    string getEmail() {
        return email;
    }
};

class Event {
private:
    string name;
    string date;
    int totalTickets;
    queue<string> venues;
  

public:
    Event(string eventName, string eventDate, int tickets) {
        name = eventName;
        date = eventDate;
        totalTickets = tickets;
    }

    string getName() {
        return name;
    }

    string getDate() {
        return date;
    }

    int getAvailableTickets() {
        return totalTickets;
    }

    void addVenue(string venue) {
        venues.push(venue);
    }

   

    

    string getNextVenue() {
        if (!venues.empty()) {
            string venue = venues.front();
            venues.pop();
            return venue;
        }
        return "";
    }

    void displayEvent() {
        cout << "Event Name: " << name << endl;
        cout << "Date: " << date << endl;
        cout << "Available Tickets: " << totalTickets << endl;
        cout << endl;
    }
};

class Ticket {
private:
    int ticketId;
    Event event;
    Customer customer;
    string seatNumber;
    bool isCancelled;

public:
    Ticket(int id, Event eventObj, Customer customerObj, string seat) :
        ticketId(id), event(eventObj), customer(customerObj), seatNumber(seat), isCancelled(false) {} 

    int getTicketId() {
        return ticketId;
    }

    Event getEvent() {
        return event;
    }

    Customer getCustomer() {
        return customer;
    }

    string getSeatNumber() {
        return seatNumber;
    }
    void cancelTicket(queue<Ticket>& ticketQueue) {
        isCancelled = true;

        queue<Ticket> tempQueue;
        while (!ticketQueue.empty()) {
            Ticket ticket = ticketQueue.front();
            ticketQueue.pop();

            if (ticket.getTicketId() != ticketId) {
                tempQueue.push(ticket);
            }
        }

        ticketQueue = tempQueue;
    }

    bool isTicketCancelled() {
        return isCancelled;
    }

    void displayTicket() {
        cout << "Ticket ID: " << ticketId << endl;
        cout << "Event: " << event.getName() << endl;
        cout << "Customer: " << customer.getName() << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << endl;
    }
};

queue<Event> eventQueue;
queue<Customer> customerQueue;
queue<Ticket> ticketQueue;
queue<Customer> waitingListQueue;

void createEvents() {
    Event event1("Amr Diab 1", "2 FEB", 2);
    event1.addVenue("Line 1");
    event1.addVenue("Line 2");
    eventQueue.push(event1);

    Event event2("Amr Diab 2", "3 FEB", 2);
    event2.addVenue("Line 3");
    event2.addVenue("Line 4");
    eventQueue.push(event2);
}

void registerCustomers() {
    Customer customer1(1, "Rawan", "Rawan_Khalid@aucegypt.edu");
    customerQueue.push(customer1);

    Customer customer2(2, "Mohsen", "Mohsen@aucegypt.edu");
    customerQueue.push(customer2);

    Customer customer3(3, "Mango", "Mago@aucegypt.edu");
    customerQueue.push(customer3);

    Customer customer4(4, "Ahman", "ahmad@aucegypt.edu");
    customerQueue.push(customer4);

    Customer customer5(5, "Rawannn", "Rawannn@aucegypt.edu");
    customerQueue.push(customer5);

    Customer customer6(6, "Morsii", "Morsii@aucegypt.edu");
    customerQueue.push(customer6);
}

void displayEvents() {
    cout << "Available Events:" << endl;
    queue<Event> tempQueue = eventQueue;
    while (!tempQueue.empty()) {
        Event event = tempQueue.front();
        event.displayEvent();
        tempQueue.pop();
    }
}

void displayCustomers() {
    cout << "Registered Customers:" << endl;
    queue<Customer> tempQueue = customerQueue;
    while (!tempQueue.empty()) {
        Customer customer = tempQueue.front();
        cout << "Customer ID: " << customer.getCustomerId() << endl;
        cout << "Name: " << customer.getName() << endl;
        cout << "Email: " << customer.getEmail() << endl;
        cout << endl;
        tempQueue.pop();
    }
}

Ticket reserveTicket(Customer customer, Event event, string seatNumber) {
    if (event.getAvailableTickets() > 0) {
        Ticket ticket(ticketQueue.size() + 1, event, customer, seatNumber);
        ticketQueue.push(ticket);
        event.addVenue(event.getNextVenue());
        event.displayEvent();
        eventQueue.push(event);
        return ticket;
    }
    else {
        waitingListQueue.push(customer);
    }
}

void cancelTicket(Customer customer) {
    queue<Ticket> tempQueue;
    while (!ticketQueue.empty()) {
        Ticket ticket = ticketQueue.front();
        if (ticket.getCustomer().getCustomerId() != customer.getCustomerId()) {
            tempQueue.push(ticket);
        }
        ticketQueue.pop();
    }
    ticketQueue = tempQueue;
}

void displayTickets() {
    queue<Ticket> tempQueue = ticketQueue;
    cout << "Tickets: " << endl;
    while (!tempQueue.empty()) {
        Ticket ticket = tempQueue.front();
        ticket.displayTicket();
        tempQueue.pop();
    }
}

void displayWaitingList() {
    queue<Customer> tempQueue = waitingListQueue;
    cout << "Waiting List " << endl;
    while (!tempQueue.empty()) {
        Customer customer = tempQueue.front();
        cout << "Customer ID " << customer.getCustomerId() << endl;
        cout << "Name " << customer.getName() << endl;
        cout << "Email " << customer.getEmail() << endl;
        cout << endl;
        tempQueue.pop();
    }
}

int main() {
   
    createEvents();
    cout << "\n";
    registerCustomers();
    cout << "\n";
    displayEvents();
    cout << "\n";
    displayCustomers();
    cout << "\n";

    Customer customer1 = customerQueue.front();
    customerQueue.pop();
    Event event1 = eventQueue.front();
    eventQueue.pop();
    
    cout << "Reserved Ticket:" << endl;
    Ticket reservedTicket = reserveTicket(customer1, event1, "2B1");
    reservedTicket.displayTicket();
    cout << endl;

    cancelTicket(customer1);
    cout << "Tickets after cancellation:" << endl;
    displayTickets();
    cout << endl;

    displayEvents();
    cout << endl;
    displayCustomers();
    cout << endl;

    while (!customerQueue.empty()) {
        if (eventQueue.empty()) {
            cout << "Tickets are not avaliable so the customer will be in waiting list." << endl;
            
        }
        Customer customer = customerQueue.front();
        customerQueue.pop();
        Event event = eventQueue.front();
        eventQueue.pop();
        Ticket reservedTicket = reserveTicket(customer, event, "2B2");
        if (reservedTicket.getTicketId() == 0) {
            cout << "There are not enough tickets " << customer.getName() << endl;
            waitingListQueue.push(customer);
        }
        else {
            cout << "Reserved Ticket for customer: " << customer.getName() << endl;
            reservedTicket.displayTicket();
        }
        cout << endl;
    }

    displayEvents();
    cout << endl;
    displayTickets();
    cout << endl;
    displayWaitingList();
    cout << endl;


    if (!ticketQueue.empty()) {
        Ticket ticketToCancel = ticketQueue.front();
        ticketQueue.pop();
        Customer customerToCancel = ticketToCancel.getCustomer();
        cancelTicket(customerToCancel);
        cout << "canceled for: " << customerToCancel.getName() << endl;
        cout << endl;
    }
    

    while (!waitingListQueue.empty()) {
        if (eventQueue.empty()) {
            cout << "Sold out" << endl;
           
        }
        Customer customer = waitingListQueue.front();
        waitingListQueue.pop();
        Event event = eventQueue.front();
        eventQueue.pop();
        Ticket reservedTicket = reserveTicket(customer, event, "2B3");
        if (reservedTicket.getTicketId() == 0) {
            waitingListQueue.push(customer);
        }
        else {
            cout << "Ticket for : " << customer.getName() << endl;
            reservedTicket.displayTicket();
        }
        cout << endl;
    }

    displayEvents();
    cout << endl;
    displayTickets();
    
 

    return 0;
}