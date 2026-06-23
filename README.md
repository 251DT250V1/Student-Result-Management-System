# Student Result Management System

TDS4223 Group Project

## How to Run

1. Open `Project Code.cpp` in Dev C++ and compile (F11), or run `Project Code.exe` directly.
2. Keep all the `.txt` files in the same folder as the `.exe`.
3. Press Enter at the welcome screen, then choose a role (Student / Admin).

## Test Accounts

| Role    | Username | Password |
|---------|----------|----------|
| Admin   | admin    | admin123 |
| Student | Bro      | bro123   |
| Student | Ali      | ali123   |

You can also register a new account from the menu.

## Data Files

- `student.txt` / `admin.txt` — login accounts
- `result.txt` — student records and subject results
- `courses.txt` — course catalogue
- `summary.txt` / `report.txt` / `classification_report.txt` / `course_report.txt` — generated reports (created automatically by the program)

## Notes

- 3 wrong login attempts in a row will lock the account for that session.
- This program is built for Windows (Dev C++).