# Railway Reservation System

This is a Railway Reservation System project made using C.

The project allows users to view trains, book tickets, search bookings, cancel tickets, and check seat availability.

## Features

- View available trains
- Book a ticket
- View all bookings
- Search a booking using ticket ID
- Cancel a ticket
- Check seat availability
- Automatically assign ticket ID
- Automatically assign seat number
- Save train and booking information in files

## Technologies Used

- C Programming
- Structures
- Functions
- File Handling
- Binary Files

## Project File

The main source code is:

- `railway.c`

When the program runs, it automatically creates:

- `trains.dat` - stores train information
- `bookings.dat` - stores booking information
- `temp.dat` - temporary file used during ticket cancellation

These files do not need to be created manually.

## Train Details

The program contains sample trains with realistic train numbers such as:

- 12844
- 17238
- 12760
- 12603
- 12727

## Requirements

To run this project, you need a C compiler.

You can use:

- GCC
- MinGW on Windows
- Linux GCC
- Clang on macOS

## How to Compile and Run



Open the terminal in the project folder.

Compile:

    gcc railway.c -o railway

Run:

    railway


If `railway` does not work, use:

    .\railway.exe


### Linux

Open the terminal in the project folder.

Compile:

    gcc railway.c -o railway

Run:

    ./railway


### macOS

Open the terminal in the project folder.

Compile:

    gcc railway.c -o railway

Run:

    ./railway


## Main Menu

The program provides the following options:

1. View Trains
2. Book Ticket
3. View All Bookings
4. Search Booking
5. Cancel Ticket
6. Check Seat Availability
7. Exit

## C Concepts Used

This project uses:

- Structures
- Functions
- Loops
- Conditional statements
- File handling
- `fopen()`
- `fclose()`
- `fread()`
- `fwrite()`
- `remove()`
- `rename()`

