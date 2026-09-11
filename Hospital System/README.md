# Hospital System

A simple C++ console project that manages patient queues in a hospital.

## What it does

There are 20 specializations (like Children, Surgery, etc). Each one can hold up to 5 patients waiting.

- **Add a patient**: you enter the specialization number, the patient's name, and their status (0 for regular, 1 for urgent). Urgent patients go to the front of the line, regular patients go to the back. If the specialization already has 5 patients, it won't accept a new one.

- **Print all patients**: shows all specializations that have patients waiting, with their names and status.

- **Get next patient**: the doctor enters a specialization number, and the first patient in that line gets called. If there are no patients, the doctor is told to wait.

## How to run it

Just build and run `main.cpp`. You'll see a menu like this:
```
1) Add new patient
2) Print all patients
3) Get next patient
4) Exit
```

## Example
```
Enter specialization, name, status: 15 mostafa 0
Patient added successfully

Enter specialization, name, status: 15 belal 1
Patient added successfully

There are 2 patients in specialization 15
belal urgent
mostafa regular
```

## Notes
This was made as a practice project for learning C++ (using vectors and deques).