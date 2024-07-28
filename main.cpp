#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Taxi {
public:
    int id;
    int earnings;
    string location;
    bool available;
    int availableTime;

    Taxi(int id) : id(id), earnings(0), location("A"), available(true), availableTime(0) {}

    void bookTaxi(string pickup, string drop, int time) {
        available = false;
        availableTime = time + abs(location[0] - pickup[0]) * 60 + abs(pickup[0] - drop[0]) * 60;
        location = drop;
        int distance = abs(pickup[0] - drop[0]) * 15;
        earnings += (distance <= 5) ? 100 : 100 + (distance - 5) * 10;
    }

    void releaseTaxi(int currentTime) {
        if (currentTime >= availableTime) {
            available = true;
        }
    }
};

class TaxiSystem {
private:
    vector<Taxi> taxis;

public:
    TaxiSystem(int n) {
        for (int i = 1; i <= n; ++i) {
            taxis.push_back(Taxi(i));
        }
    }

    void bookTaxi(int customerID, string pickup, string drop, int time) {
        for (auto& taxi : taxis) {
            taxi.releaseTaxi(time);
        }

        Taxi* bestTaxi = nullptr;
        int minDistance = INT_MAX;
        int minEarnings = INT_MAX;

        for (auto& taxi : taxis) {
            if (taxi.available) {
                int distance = abs(taxi.location[0] - pickup[0]);
                if (distance < minDistance || (distance == minDistance && taxi.earnings < minEarnings)) {
                    bestTaxi = &taxi;
                    minDistance = distance;
                    minEarnings = taxi.earnings;
                }
            }
        }

        if (bestTaxi) {
            bestTaxi->bookTaxi(pickup, drop, time);
            cout << "Taxi " << bestTaxi->id << " booked for customer " << customerID << " from " << pickup << " to " << drop << " at time " << time << " hrs." << endl;
        } else {
            cout << "Booking rejected for customer " << customerID << " at time " << time << " hrs." << endl;
        }
    }
};

int main() {
    TaxiSystem system(4);

    system.bookTaxi(1, "A", "B", 9);  // Booking at 9 hrs
    system.bookTaxi(2, "A", "C", 10); // Booking at 10 hrs
    system.bookTaxi(3, "B", "D", 11); // Booking at 11 hrs
    system.bookTaxi(4, "D", "F", 12); // Booking at 12 hrs
    system.bookTaxi(5, "A", "B", 9);  // Booking at 9 hrs (should be rejected)

    return 0;
}

