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

<table>
<tr>
<td width="50%">
 
### Project Structure

📁 hotel-management/ ├─📁 src/ │ ├─📁 headerFiles/ │ │ ├─📄 colors.h │ │ ├─📄 login.h │ │ ├─📄 menu.h │ │ ├─📄 reservations.h │ │ ├─📄 tracking.h │ │ └─📄 validation.h │ ├─📄 login.c │ ├─📄 menu.c │ ├─📄 reservations.c │ ├─📄 tracking.c │ ├─📄 editReservations.c │ ├─📄 check_out.c │ └─📄 sorting.c └─📁 output/

</td>
<td width="50%">


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
