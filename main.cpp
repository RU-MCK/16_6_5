#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int switches_state = 0;
enum switches {
  LIGHTS_INSIDE = 1,
  LIGHTS_OUTSIDE = 2,
  HEATERS = 4,
  WATER_PIPE_HEATING = 8,
  CONDITIONER = 16
};
bool answer() {
  string answer;
  cin >> answer;
  if (answer == "YES")
    return true;
  else
    return false;
}
void check_outsideTemp(int temp) {
  if (temp < 0) {
    if (!(switches_state & WATER_PIPE_HEATING)) {
      switches_state |= WATER_PIPE_HEATING;
      cout << "WATER_PIPE_HEATING < ON >" << endl;
    }
  }
  if (temp > 5) {
    if (switches_state & WATER_PIPE_HEATING) {
      switches_state &= (~WATER_PIPE_HEATING);
      cout << "WATER_PIPE_HEATING < OFF >" << endl;
    }
  }
}
void check_insideTemp(int temp) {
  if (temp < 22) {
    if (!(switches_state & HEATERS)) {
      switches_state |= HEATERS;
      cout << "HEATERS < ON >" << endl;
    }
  }
  if (temp >= 25) {
    if (switches_state & HEATERS) {
      switches_state &= (~HEATERS);
      cout << "HEATERS < OFF >" << endl;
    }
    if ((temp == 25) && (switches_state & CONDITIONER)) {
      switches_state &= (~CONDITIONER);
      cout << "CONDITIONER < OFF >" << endl;
    }
  }
  if (temp >= 30) {
    if (!(switches_state & CONDITIONER)) {
      switches_state |= CONDITIONER;
      cout << "CONDITIONER < ON >" << endl;
    }
  }
}
void check_colorful(int time) {
  if (time >= 0 && time <= 16)
    cout << "Colorful temperature 5000 " << endl;
  if (time == 17)
    cout << "Colorful temperature 4425 " << endl;
  if (time == 18)
    cout << "Colorful temperature 3850 " << endl;
  if (time == 19)
    cout << "Colorful temperature 3275 " << endl;
  if (time >= 20 && time <= 23)
    cout << "Colorful temperature 2700 " << endl;
}
bool check_insideLight(string str) {
  if (str == "ON") {
    if (!(switches_state & LIGHTS_INSIDE)) {
      switches_state |= LIGHTS_INSIDE;
      cout << "LIGHTS_INSIDE < ON >" << endl;
      return true;
    }
  } else {
    if (switches_state & LIGHTS_INSIDE) {
      switches_state &= (~LIGHTS_INSIDE);
      cout << "LIGHTS_INSIDE < OFF >" << endl;
    }
  }
  return false;
}
void check_outsideLight(int time, string str) {
  if (str == "YES" && (time > 16 || time < 5)) {
    if (!(switches_state & LIGHTS_OUTSIDE)) {
      switches_state |= LIGHTS_OUTSIDE;
      cout << "LIGHTS_OUTSIDE < ON >" << endl;
    }
  }
  if (str == "NO" && (time > 16 || time < 5)) {
    if (switches_state & LIGHTS_OUTSIDE) {
      switches_state &= (~LIGHTS_OUTSIDE);
      cout << "LIGHTS_OUTSIDE < OFF >" << endl;
    }
  }
  if (time < 16 && time > 5) {
    if (switches_state & LIGHTS_OUTSIDE) {
      switches_state &= (~LIGHTS_OUTSIDE);
      cout << "LIGHTS_OUTSIDE < OFF >" << endl;
    }
  }
}
int main() {
  cout << "Power up the whole house < YES/NO > :";
  if (!(answer()))
    return 0;
  cout << "Power up the sockets < YES/NO >" << endl;
  if (answer()) {
    switches_state = switches_state | HEATERS | WATER_PIPE_HEATING | CONDITIONER;
  }
  cout << "Power up the lights  < YES/NO >" << endl;
  if (answer()) {
    switches_state = LIGHTS_INSIDE | LIGHTS_OUTSIDE;
  }
  int time = 0;
  int count = 0;
  int outsideTmp = 6;
  int insideTmp = 25;
  string lightsInside = "ON";
  string movingOutside = "YES";
  while (count < 48) {
    check_outsideTemp(outsideTmp);
    check_insideTemp(insideTmp);
    if (check_insideLight(lightsInside))
      check_colorful(time);
    check_outsideLight(time, movingOutside);
    cout << "Current time: " << time << ":00" << endl
         << "Temperature outside: " << outsideTmp << " C" << endl
         << "Temperature inside: " << insideTmp << " C" << endl
         << "Lights inside: " << lightsInside << endl
         << "Moving outside: " << movingOutside << endl
         << "Input current state: " << endl;
    stringstream temp_stream;
    string buffer;
    getline(cin, buffer);
    temp_stream << buffer;
    temp_stream >> outsideTmp >> insideTmp >> lightsInside >> movingOutside;
    time++;
    if (time == 23)
      time = 0;
    count++;
  }

}
