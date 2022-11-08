/*Product management class - will connect with mainMenu.cpp
    shop manager should be able to add and remove products from inventory
    - product id:
        - must start with a 'P' followed by a 5 digit number
            - ex: P01234
        - must be unit (cannot already exist)
    - product name (description)
    - product price:
        - do we want to store it in the txt file with the $ attached or attach it whenever we retrieve the value?
    - the number of products currently in stock in the store:
        - must be a positive number
    - all products information must be saved in a file named "products.txt"
        - check assignment.pdf for format
        - only write to file AFTER user input has been validated
    - will need to split all inputs into their own functions
        - make logging its own function
        - make validation its own function
    - will need to be able to read PREVIOUS RECORDS
*/