#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRAIN_FILE "trains.dat"
#define BOOKING_FILE "bookings.dat"
#define TEMP_FILE "temp.dat"

struct Train
{
    int train_no;
    char train_name[50];
    char source[50];
    char destination[50];
    int total_seats;
};

struct Booking
{
    int ticket_id;
    int train_no;
    int seat_no;
    char passenger_name[50];
    int age;
    char gender[10];
};

void initialize_trains();
void view_trains();
void book_ticket();
void view_bookings();
void search_booking();
void cancel_ticket();
void check_seat_availability();

int get_next_ticket_id();
int get_next_seat_number(int train_no);
int train_exists(int train_no);
int is_seat_booked(int train_no, int seat_no);

int main()
{
    int choice;

    initialize_trains();

    while (1)
    {
        printf("\n===============================================\n");
        printf("        RAILWAY RESERVATION SYSTEM\n");
        printf("===============================================\n");
        printf("1. View Trains\n");
        printf("2. Book Ticket\n");
        printf("3. View All Bookings\n");
        printf("4. Search Booking\n");
        printf("5. Cancel Ticket\n");
        printf("6. Check Seat Availability\n");
        printf("7. Exit\n");
        printf("===============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                view_trains();
                break;

            case 2:
                book_ticket();
                break;

            case 3:
                view_bookings();
                break;

            case 4:
                search_booking();
                break;

            case 5:
                cancel_ticket();
                break;

            case 6:
                check_seat_availability();
                break;

            case 7:
                printf("\nThank you for using Railway Reservation System!\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

void initialize_trains()
{
    FILE *file;
    struct Train train;

    file = fopen(TRAIN_FILE, "rb");

    if (file != NULL)
    {
        fclose(file);
        return;
    }

    file = fopen(TRAIN_FILE, "wb");

    if (file == NULL)
    {
        printf("Unable to create train file.\n");
        exit(1);
    }

    train.train_no = 12844;
    strcpy(train.train_name, "Ahmedabad Express");
    strcpy(train.source, "Ahmedabad");
    strcpy(train.destination, "Puri");
    train.total_seats = 50;
    fwrite(&train, sizeof(train), 1, file);

    train.train_no = 17238;
    strcpy(train.train_name, "Bangalore Express");
    strcpy(train.source, "Nagarcoil");
    strcpy(train.destination, "Bangalore");
    train.total_seats = 60;
    fwrite(&train, sizeof(train), 1, file);

    train.train_no = 12760;
    strcpy(train.train_name, "Charminar Express");
    strcpy(train.source, "Hyderabad");
    strcpy(train.destination, "Chennai");
    train.total_seats = 50;
    fwrite(&train, sizeof(train), 1, file);

    train.train_no = 12603;
    strcpy(train.train_name, "Chennai Express");
    strcpy(train.source, "Chennai");
    strcpy(train.destination, "Hyderabad");
    train.total_seats = 60;
    fwrite(&train, sizeof(train), 1, file);

    train.train_no = 12727;
    strcpy(train.train_name, "Godavari Express");
    strcpy(train.source, "Visakhapatnam");
    strcpy(train.destination, "Hyderabad");
    train.total_seats = 50;
    fwrite(&train, sizeof(train), 1, file);

    fclose(file);
}

void view_trains()
{
    FILE *file;
    struct Train train;

    file = fopen(TRAIN_FILE, "rb");

    if (file == NULL)
    {
        printf("\nUnable to open train file.\n");
        return;
    }

    printf("\n================ AVAILABLE TRAINS ================\n");
    printf("%-10s %-22s %-16s %-16s %-10s\n",
           "Number", "Train Name", "From", "To", "Seats");

    printf("--------------------------------------------------------------------------\n");

    while (fread(&train, sizeof(train), 1, file) == 1)
    {
        printf("%-10d %-22s %-16s %-16s %-10d\n",
               train.train_no,
               train.train_name,
               train.source,
               train.destination,
               train.total_seats);
    }

    fclose(file);
}

void book_ticket()
{
    FILE *file;
    struct Booking booking;
    int train_no;
    int seat_no;

    printf("\nEnter train number: ");
    scanf("%d", &train_no);

    if (!train_exists(train_no))
    {
        printf("\nTrain not found.\n");
        return;
    }

    seat_no = get_next_seat_number(train_no);

    if (seat_no == -1)
    {
        printf("\nNo seats available on this train.\n");
        return;
    }

    booking.ticket_id = get_next_ticket_id();
    booking.train_no = train_no;
    booking.seat_no = seat_no;

    printf("Enter passenger name: ");
    scanf(" %[^\n]", booking.passenger_name);

    printf("Enter age: ");
    scanf("%d", &booking.age);

    printf("Enter gender: ");
    scanf("%s", booking.gender);

    file = fopen(BOOKING_FILE, "ab");

    if (file == NULL)
    {
        printf("\nUnable to open booking file.\n");
        return;
    }

    fwrite(&booking, sizeof(booking), 1, file);

    fclose(file);

    printf("\n===============================================\n");
    printf("              TICKET BOOKED\n");
    printf("===============================================\n");
    printf("Ticket ID       : %d\n", booking.ticket_id);
    printf("Passenger Name  : %s\n", booking.passenger_name);
    printf("Age             : %d\n", booking.age);
    printf("Gender          : %s\n", booking.gender);
    printf("Train Number    : %d\n", booking.train_no);
    printf("Seat Number     : %d\n", booking.seat_no);
    printf("===============================================\n");
}

void view_bookings()
{
    FILE *file;
    struct Booking booking;
    int found = 0;

    file = fopen(BOOKING_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo bookings found.\n");
        return;
    }

    printf("\n================ ALL BOOKINGS ================\n");

    while (fread(&booking, sizeof(booking), 1, file) == 1)
    {
        printf("\nTicket ID      : %d\n", booking.ticket_id);
        printf("Passenger Name : %s\n", booking.passenger_name);
        printf("Age            : %d\n", booking.age);
        printf("Gender         : %s\n", booking.gender);
        printf("Train Number   : %d\n", booking.train_no);
        printf("Seat Number    : %d\n", booking.seat_no);
        printf("-----------------------------------------------\n");

        found = 1;
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo bookings found.\n");
    }
}

void search_booking()
{
    FILE *file;
    struct Booking booking;
    int ticket_id;
    int found = 0;

    printf("\nEnter ticket ID: ");
    scanf("%d", &ticket_id);

    file = fopen(BOOKING_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo bookings found.\n");
        return;
    }

    while (fread(&booking, sizeof(booking), 1, file) == 1)
    {
        if (booking.ticket_id == ticket_id)
        {
            printf("\n===============================================\n");
            printf("              BOOKING FOUND\n");
            printf("===============================================\n");
            printf("Ticket ID      : %d\n", booking.ticket_id);
            printf("Passenger Name : %s\n", booking.passenger_name);
            printf("Age            : %d\n", booking.age);
            printf("Gender         : %s\n", booking.gender);
            printf("Train Number   : %d\n", booking.train_no);
            printf("Seat Number    : %d\n", booking.seat_no);
            printf("===============================================\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nTicket ID not found.\n");
    }
}

void cancel_ticket()
{
    FILE *file;
    FILE *temp;
    struct Booking booking;
    int ticket_id;
    int found = 0;

    printf("\nEnter ticket ID to cancel: ");
    scanf("%d", &ticket_id);

    file = fopen(BOOKING_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo bookings found.\n");
        return;
    }

    temp = fopen(TEMP_FILE, "wb");

    if (temp == NULL)
    {
        fclose(file);
        printf("\nUnable to create temporary file.\n");
        return;
    }

    while (fread(&booking, sizeof(booking), 1, file) == 1)
    {
        if (booking.ticket_id == ticket_id)
        {
            found = 1;
        }
        else
        {
            fwrite(&booking, sizeof(booking), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(BOOKING_FILE);
    rename(TEMP_FILE, BOOKING_FILE);

    if (found)
    {
        printf("\nTicket cancelled successfully.\n");
    }
    else
    {
        printf("\nTicket ID not found.\n");
    }
}

void check_seat_availability()
{
    FILE *file;
    FILE *booking_file;
    struct Train train;
    struct Booking booking;
    int train_no;
    int booked = 0;
    int available;

    printf("\nEnter train number: ");
    scanf("%d", &train_no);

    file = fopen(TRAIN_FILE, "rb");

    if (file == NULL)
    {
        printf("\nUnable to open train file.\n");
        return;
    }

    while (fread(&train, sizeof(train), 1, file) == 1)
    {
        if (train.train_no == train_no)
        {
            fclose(file);

            booking_file = fopen(BOOKING_FILE, "rb");

            if (booking_file != NULL)
            {
                while (fread(&booking, sizeof(booking), 1, booking_file) == 1)
                {
                    if (booking.train_no == train_no)
                    {
                        booked++;
                    }
                }

                fclose(booking_file);
            }

            available = train.total_seats - booked;

            printf("\n===============================================\n");
            printf("           SEAT AVAILABILITY\n");
            printf("===============================================\n");
            printf("Train Number    : %d\n", train.train_no);
            printf("Train Name      : %s\n", train.train_name);
            printf("Total Seats     : %d\n", train.total_seats);
            printf("Booked Seats    : %d\n", booked);
            printf("Available Seats : %d\n", available);
            printf("===============================================\n");

            return;
        }
    }

    fclose(file);

    printf("\nTrain not found.\n");
}

int train_exists(int train_no)
{
    FILE *file;
    struct Train train;

    file = fopen(TRAIN_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&train, sizeof(train), 1, file) == 1)
    {
        if (train.train_no == train_no)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}

int get_next_ticket_id()
{
    FILE *file;
    struct Booking booking;
    int max_id = 1000;

    file = fopen(BOOKING_FILE, "rb");

    if (file == NULL)
    {
        return max_id + 1;
    }

    while (fread(&booking, sizeof(booking), 1, file) == 1)
    {
        if (booking.ticket_id > max_id)
        {
            max_id = booking.ticket_id;
        }
    }

    fclose(file);

    return max_id + 1;
}

int is_seat_booked(int train_no, int seat_no)
{
    FILE *file;
    struct Booking booking;

    file = fopen(BOOKING_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&booking, sizeof(booking), 1, file) == 1)
    {
        if (booking.train_no == train_no &&
            booking.seat_no == seat_no)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}

int get_next_seat_number(int train_no)
{
    FILE *file;
    struct Train train;
    int seat_no;

    file = fopen(TRAIN_FILE, "rb");

    if (file == NULL)
    {
        return -1;
    }

    while (fread(&train, sizeof(train), 1, file) == 1)
    {
        if (train.train_no == train_no)
        {
            fclose(file);

            for (seat_no = 1; seat_no <= train.total_seats; seat_no++)
            {
                if (!is_seat_booked(train_no, seat_no))
                {
                    return seat_no;
                }
            }

            return -1;
        }
    }

    fclose(file);

    return -1;
}