#include "editing_inputs.h"

// Constructor definition
editingInputs::editingInputs() : red(50), green(50), blue(50) {  // Initialize value to 0
}

// Getter function to read the value
int editingInputs::GetRed() const {
    return red;
}
int editingInputs::GetGreen() const {
    return green;
}
int editingInputs::GetBlue() const {
    return blue;
}

// Setter function to update the value
void editingInputs::SetRed(int newValue) {
    red = newValue;
}
void editingInputs::SetGreen(int newValue) {
    green = newValue;
}
void editingInputs::SetBlue(int newValue) {
    blue = newValue;
}