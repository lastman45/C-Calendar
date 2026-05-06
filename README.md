# cCalendar

A lightweight command-line calendar generator written in C. Given any year between 1900 and 2100, it prints a full 12-month calendar to the terminal with correct weekday alignment — including proper leap year handling.

---

## Features

- Displays a full year calendar (January through December) in the terminal
- Correctly aligns days to their weekday columns (Sun–Sat)
- Handles leap years automatically
- Validates user input and re-prompts on invalid entries
- Works for any year in the range **1900–2100**
- Sets console text to green for a classic terminal aesthetic (Windows)

---

## Requirements

- A C compiler (GCC, Clang, MSVC, etc.)
- Windows OS (for the `system("color 0A")` green console effect — harmless on other platforms, just ignored)

---

## Building

### Using GCC

```bash
gcc cCalendar.c -o cCalendar
```

### Using Clang

```bash
clang cCalendar.c -o cCalendar
```

### Using MSVC (Windows)

```bash
cl cCalendar.c
```

---

## Usage

Run the compiled binary:

```bash
./cCalendar
```

You will be prompted to enter a year:

```
Enter the Year (between 1900 and 2100): 2025
```

If an invalid year is entered, the program re-prompts:

```
Year must be between 1900 and 2100. Please enter a valid year.
Enter the Year (between 1900 and 2100):
```

### Sample Output

```
----------January----------

  Sun  Mon  Tue  Wed  Thr  Fri  Sat
                1    2    3    4    5
    6    7    8    9   10   11   12
   13   14   15   16   17   18   19
   20   21   22   23   24   25   26
   27   28   29   30   31


----------February----------

  Sun  Mon  Tue  Wed  Thr  Fri  Sat
                               1    2
    3    4    5    6    7    8    9
...
```

---

## How It Works

### 1. Weekday Calculation (`get_1st_weekday`)

The function calculates which day of the week January 1st of the given year falls on, using the formula:

```
day = ((year - 1) * 365 + (year - 1)/4 - (year - 1)/100 + (year - 1)/400 + 1) % 7
```

This accounts for regular years, 4-year leap cycles, century exceptions, and 400-year corrections — essentially a simplified variant of the Doomsday algorithm. The result is a value 0–6 where `0 = Sunday` and `6 = Saturday`.

### 2. Leap Year Detection

February is set to 29 days if the year satisfies:

```c
(year % 4 == 0 && year % 100 != 0) || year % 400 == 0
```

This follows the Gregorian calendar standard.

### 3. Month Rendering

For each month, the program:
1. Prints blank padding cells for the days before the 1st of the month
2. Prints each day number, advancing the weekday counter
3. Inserts a newline after every Saturday (weekday index 6)
4. Passes the final weekday value forward as the starting day for the next month

---

## Code Structure

| Element            | Description                                              |
|--------------------|----------------------------------------------------------|
| `get_1st_weekday`  | Calculates the weekday of January 1st for a given year   |
| `main`             | Handles input, leap year logic, and calendar rendering   |
| `months[]`         | Array of month name strings                              |
| `monthDays[]`      | Array of days per month (February adjusted for leap year)|

---

## Known Limitations

- **Windows-only color**: The `system("color 0A")` call only works on Windows. On Linux/macOS it prints a harmless error or is silently ignored.
- **No month selection**: The program always prints all 12 months; there is no option to display a single month.
- **Fixed range**: Years outside 1900–2100 are rejected. The Gregorian calendar formula is accurate well beyond this range, but the guard is intentional.
- **No input sanitization beyond range**: Non-numeric input to `scanf` can cause undefined behavior. For production use, consider replacing `scanf` with `fgets` + `strtol`.

---

## Possible Improvements

- Add a month selection option (`-m` flag or second prompt)
- Support ANSI escape codes for cross-platform color output
- Accept year as a command-line argument (`./cCalendar 2025`)
- Highlight today's date when displaying the current year
- Replace `scanf` with safer input handling

---

## License

This project is released into the public domain. You are free to use, modify, and distribute it without restriction.
