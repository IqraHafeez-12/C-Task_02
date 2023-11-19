#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

class Train {
public:
    std::string departure_time;
    std::string return_time;
    int available_seats;
    int passengers;
    double revenue;

    Train(std::string dep_time, std::string ret_time, int available_seats)
        : departure_time(dep_time), return_time(ret_time),
          available_seats(available_seats), passengers(0), revenue(0.0) {}
};

void display_start_of_day(const std::vector<Train>& trains) {
    std::cout << std::setw(20) << "Departure Time" << std::setw(20) << "Return Time"
              << std::setw(20) << "Available Seats" << std::setw(20) << "Passengers"
              << std::setw(20) << "Revenue" << std::endl;

    for (const Train& train : trains) {
        if (train.available_seats > 0) {
            std::cout << std::setw(20) << train.departure_time << std::setw(20) << train.return_time
                      << std::setw(20) << train.available_seats << std::setw(20) << train.passengers
                      << " $" << std::setw(19) << std::fixed << std::setprecision(2) 
                      << train.revenue<<std :: endl;
        } else {
            std :: cout<<std :: setw ( 20 )<<train.departure_time<<std :: setw ( 20 )<<train.return_time
                      <<"Closed"<<std :: setw ( 20 )<<train.passengers
                      <<" "<<std :: fixed<<std :: setprecision ( 2 )<<train.revenue<<std :: endl;
        }
    }
}

void purchase_tickets(std :: vector<Train>& trains, int train_index, int num_passengers) {
    // Check if the selected train is available
    if (trains[train_index].available_seats <= 0) {
        std :: cout<<"Train is full. Cannot purchase tickets."<<std :: endl;
        return;
    }

    // Calculate total price including group discount
    double ticket_price = 25.0;
    double total_price = num_passengers * ticket_price;
    int free_tickets = num_passengers / 10;  // Calculate free tickets for groups

    // Update available seats and passenger count
    trains[train_index].available_seats -= num_passengers - free_tickets;
    trains[train_index].passengers += num_passengers;
    trains[train_index].revenue += total_price;

    // Display information
    display_start_of_day(trains);

    // Display purchase details
    std :: cout<<"Purchase successful!"<<std :: endl;
std :: cout<<"Number of tickets: "<<num_passengers<<std :: endl;
    std :: cout<<"Total Price: $"<<std :: fixed<<std :: setprecision(2)<<total_price<<std :: endl;
    std::cout << "Free Tickets: " << free_tickets << std::endl;
}

void display_end_of_day(const std::vector<Train>& trains) {
    int total_passengers = 0;
    double total_revenue = 0.0;
    
auto max_passengers_it = std::max_element(trains.begin(), trains.end(),
        [](const Train& a, const Train& b) {
            return a.passengers < b.passengers;
        });

for (const Train& train : trains) {
        total_passengers += train.passengers;
        total_revenue += train.revenue;
}

std::cout << "End-of-Day Summary:" << std::endl;
std::cout << "Total Passengers for the Day: " << total_passengers << std::endl;
std::cout << "Total Revenue for the Day: $" << std::fixed << std::setprecision(2) 
          << total_revenue<<std :: endl;
std :: cout<<"Train Journey with the Most Passengers: "<<max_passengers_it->departure_time
              <<" - "<<max_passengers_it->return_time<<std :: endl;
}

int main() {
    // Initialize train schedule for the start of the day
    std :: vector<Train> trains = {
        Train("09:00", "10:00", 6 * 80),
        Train("11:00", "12:00", 6 * 80),
        Train("13:00", "14:00", 6 * 80),
        Train("15:00", "16:00", 6 * 80 + 2)  // Last train has 2 extra coaches
    };

    // Display start-of-day information
    display_start_of_day(trains);

    // Keep booking running until all tickets are sold
    while (std::any_of(trains.begin(), trains.end(), [](const Train& train) {
        return train.available_seats > 0;
    })) {
        // User input for ticket purchase
        int selected_train;
        std :: cout<<"Enter the index of the train you want to book (0-3): ";
        std :: cin>>selected_train;

        if (!(0 <= selected_train && selected_train < static_cast<int>(trains.size()))) {
            std :: cout<<"Invalid train index. Exiting program."<<std :: endl;
            return 1;
        }

        int num_passengers;
        std :: cout<<"Enter the number of passengers: ";
        std :: cin>>num_passengers;

        // Validate number of passengers
        if (num_passengers <= 0) {
            std :: cout<<"Invalid number of passengers. Exiting program."<<std :: endl;
            return 1;
        }

        // Perform ticket purchase
        purchase_tickets(trains, selected_train, num_passengers);

        // Display end-of-day summary if all tickets are sold
        if (std::all_of(trains.begin(), trains.end(), [](const Train& train) {
            return train.available_seats == 0;
        })) {
            display_end_of_day(trains);
            std :: cout<<"All tickets are sold. Exiting program."<<std :: endl;
            return 0;
        }
    }

    return 0;
}
