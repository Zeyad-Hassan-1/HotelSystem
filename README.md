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

## Project Structure

📁 **hotel-management/**
  ├─📁 **src/**
  │  ├─📁 **headerFiles/**
  │  │  ├─📄 colors.h        # Console color definitions and text styling
  │  │  ├─📄 login.h         # User authentication and session management
  │  │  ├─📄 menu.h          # Menu navigation and UI components
  │  │  ├─📄 reservations.h  # Booking system core functionality 
  │  │  ├─📄 tracking.h      # Room status and availability tracking
  │  │  └─📄 validation.h    # Input validation and data verification
  │  │
  │  ├─📄 login.c            # Login system implementation
  │  ├─📄 menu.c             # Menu system and navigation logic
  │  ├─📄 reservations.c     # Room booking and reservation handling
  │  ├─📄 tracking.c         # Room and booking status management
  │  ├─📄 editReservations.c # Modification of existing bookings
  │  ├─📄 check_out.c        # Check-out processing and billing
  │  └─📄 sorting.c          # Data sorting and organization utilities
  │
  ├─📁 **output/**           # Data storage directory
  │  ├─📄 Reservations.txt   # Customer booking records
  │  ├─📄 Room.txt           # Room details and status
  │  └─📄 users.txt          # User authentication data
  │
  └─📄 README.md             # Project documentation


Features:
  1. 🔐 Secure login system
  2. 🏨 Room reservation management
  3. ✅ Check-in/check-out processing
  4. 📊 Room availability tracking
  5. 👥 Customer information management
  6. 🔄 Booking modifications
  7. 📝 Room category management
  8. 📈 Reporting system

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
