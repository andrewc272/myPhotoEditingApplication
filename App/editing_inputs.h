#ifndef MYCLASS_H
#define MYCLASS_H

class editingInputs {
public:
    // Constructor
    editingInputs();

    // Getter for value
    int GetRed() const;
    int GetGreen() const;
    int GetBlue() const;

    // Setter for value
    void SetRed(int newValue);
    void SetGreen(int newValue);
    void SetBlue(int newValue);

private:
    int red;  
    int green;
    int blue;
};

#endif