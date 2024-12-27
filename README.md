# Hotel Management System in C

## Overview
Console-based hotel management system with room booking, customer tracking, and administrative features.

## Requirements
- Windows OS
- C compiler (GCC recommended)
- MinGW for Windows
- Text editor/IDE (VS Code recommended)

## Installation
1. Clone the repository:
```bash
git clone https://github.com/yourusername/hotel-management.git
```
2. Navigate to project directory:
```bash
cd hotel-management
```
3. Compile the project:
```bash
gcc main.c Src/*.c -o hotel.exe -I Src/headerFiles
```
Project Structure:
hotel-management/
├── Src/
│   ├── headerFiles/       # Header files
│   │   ├── colors.h      # Console color definitions
│   │   ├── login.h       # Authentication headers
│   │   ├── menu.h        # Menu system headers
│   │   ├── reservations.h # Booking system headers
│   │   ├── tracking.h    # Room tracking headers
│   │   └── validation.h  # Input validation headers
│   ├── login.c           # Authentication implementation
│   ├── menu.c            # Menu system implementation
│   ├── reservations.c    # Booking system implementation
│   ├── tracking.c        # Room tracking implementation
│   ├── editReservations.c # Booking modification implementation
│   ├── check_out.c       # Check-out process implementation
│   └── sorting.c         # Data sorting utilities
├── output/               # Data storage
│   ├── Reservations.txt  # Customer reservations
│   ├── Room.txt         # Room information
│   └── users.txt        # User credentials
└── README.md

Features:
*🔐 Secure login system
*🏨 Room reservation management
*✅ Check-in/check-out processing
*📊 Room availability tracking
*👥 Customer information management
*🔄 Booking modifications
*📝 Room category management
*📈 Reporting system

Data Organization:
Room.txt Format
```RoomID Status Category Price```
Reservations.txt Format
```ReservationID,RoomID,Status,Name,NationalID,Nights,Date,Email,Phone```
Users.txt Format
```Username Password```
Usage
Run the compiled executable:
```bash
./hotel.exe
```
Login with credentials from users.txt
Navigate using the menu system:
  Arrow keys to move
  Enter to select
  ESC to go back

Main Menu Options
  Reserve a Room
  Check-In
  Cancel Reservation
  Check-Out
  Check Room Availability
  View Customer Details
  Edit Reservation Details
  Query(Search)
  Reservation Report
  Exit

Contributing
  Fork the repository
  Create feature branch
  Commit changes
  Push to branch
  Create Pull Request

License
MIT License

Author
[Zeyad Hasan Sadiq]
