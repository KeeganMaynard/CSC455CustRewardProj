/*Customer registration class - will connect with mainMenu.cpp
    user must register to benefit from the reward service
    - user name:
        - consists of at least 8 characters, followed by at most 3 numbers
            - ex: uniqueUser123
            - do we need to prevent special characters?
        - must be unique (cannot already exist)
    - first name:
        - must be a string no longer than 15 characters
        - does not contain any numbers or special characters
    - last name:
        - same as first name
    - date of birth:
        - Must be in MM-DD-YYYY format
            ex: 01-23-2022
        - values must be ints
        - how do we validate? Do we need to check if MM <= 12, DD <=30, YYYY <=2022?
    - credit card number:
        - must be unique (cannot already exist)
        - must follow format xxxx-xxx-xxxx (4-3-4)
            ex: 1234-567-8910
        - must be ints
    - system will assign unique user ID:
        - must be unique (cannot already exist)
        - must start with "CID", follow by 10 digits
            ex: CID1234567890
        - only assign user ID AFTER user input has been validated!!
    - reward points:
        - must be a positive number
        - are we assigning 0 or allowing user to enter points already earned?
    - all user information must be saved in a file named "customers.txt"
        - check assignment.pdf for format
        - only write to file AFTER user input has been validated!!
    - will need to split all inputs into their own functions
        - make logging its own function
        - make validation its own function(s)
*/